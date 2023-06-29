//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CMVRxchangeService.h"
#include "../mvrxchange/mvrxchange_prefix.h"
#include "../mvrxchange/mvrxchange_client.h"


VectorworksMVR::CMVRxchangeServiceImpl::CMVRxchangeServiceImpl()
{
	fServer_Running = false;
	fServer = nullptr;
}

VectorworksMVR::CMVRxchangeServiceImpl::~CMVRxchangeServiceImpl()
{
}

VCOMError VectorworksMVR::CMVRxchangeServiceImpl::ConnectToLocalService(const ConnectToLocalServiceArgs& services)
{
	//---------------------------------------------------------------------------------------------
	// Start TCP
	this->TCP_Start();

	fMVRGroup = GetMembersOfService(services);

	SendMessageArgs joinMessage;
	joinMessage.Message.Type = MVRxchangeMessageType::MVR_JOIN;
	this->Send_message(joinMessage);

	std::cout << "Port: " << fServer->GetPort() << std::endl;


	//---------------------------------------------------------------------------------------------
	// Start mDNS Service
	fmdns.setServiceHostname(services.Service);
	fmdns.setServicePort(fServer->GetPort());
	fmdns.setServiceName("_mvrxchange._tcp.local."); // XXX TODO: ServiceNam
	fmdns.startService();

	return kVCOMError_NoError;
}


VCOMError VectorworksMVR::CMVRxchangeServiceImpl::LeaveLocalService()
{
	this->TCP_Stop();


	return kVCOMError_NoError;
}


VCOMError VCOM_CALLTYPE  CMVRxchangeServiceImpl::QueryLocalServices(size_t& out_Count)
{
	fQueryLocalServicesResult.clear();

	mdns_cpp::mDNS mdns;

	auto query_res = mdns.executeQuery2(MVRXChange_Service);

	if (query_res.size() == 0)
	{
		return kVCOMError_Failed;
	}

	for (auto& r : query_res) {
		ConnectToLocalServiceArgs localServ;

		strcpy_s(localServ.Service, r.hostNam.c_str());		 
		strcpy_s(localServ.IPv4, r.ipV4_adress.c_str());
		strcpy_s(localServ.IPv6, r.ipV6_adress.c_str());
		localServ.port = r.port;

		fQueryLocalServicesResult.push_back(localServ);
	}

	out_Count = fQueryLocalServicesResult.size();

	return kVCOMError_NoError;
}


VCOMError VCOM_CALLTYPE VectorworksMVR::CMVRxchangeServiceImpl::GetLocalServiceAt(size_t index, ConnectToLocalServiceArgs& outLocalService)
{
	if ( ! fQueryLocalServicesResult.size())
	{
		return kVCOMError_Failed;
	}

	outLocalService = fQueryLocalServicesResult[index];

	return kVCOMError_NoError;
}


VCOMError VectorworksMVR::CMVRxchangeServiceImpl::ConnectToRemoteService(const ConnectToRemoteServiceArgs& service)
{
	return kVCOMError_NoError;
}


VCOMError VectorworksMVR::CMVRxchangeServiceImpl::LeaveRemoteService()
{
	return kVCOMError_NoError;
}

VCOMError VectorworksMVR::CMVRxchangeServiceImpl::OnMessage(OnMessageArgs& messageHandler)
{
	fCallBack = messageHandler;

	return kVCOMError_NoError;
}

VCOMError VectorworksMVR::CMVRxchangeServiceImpl::Send_message(const SendMessageArgs& messageHandler)
{
	//---------------------------------------------------------------------------------------------
	// Start mDNS Service
	{
		MVRxchangeNetwork::MVRxchangePacket msg;
		msg.FromExternalMessage(messageHandler.Message);
		for (const auto& e : fMVRGroup)
		{
			SendMessageToLocalNetworks(e.IP, e.Name, msg);
		}
	}

	return kVCOMError_NoError;
}

//---------------------------------------------------------------------------
// TCP Server - Local Network mode

void CMVRxchangeServiceImpl::TCP_Start()
{
	if (fServer_Running)
	{
		TCP_Stop();
	}

	tcp::endpoint endpoint(tcp::v4(), 0);
	fServer = new MVRxchangeNetwork::MVRxchangeServer(fServer_IO_Context, endpoint, this);
	fServer_Running = true;
	fServer_Thread = std::thread(&CMVRxchangeServiceImpl::TCP_ServerNetworksThread, this);
}

void CMVRxchangeServiceImpl::TCP_Stop()
{
	if (fServer_Thread.joinable())
	{
		fServer_IO_Context.stop();
		fServer_Thread.join();
	}
	fServer_Running = false;
}

void CMVRxchangeServiceImpl::TCP_ServerNetworksThread()
{

	fServer_IO_Context.run();
}

IMVRxchangeService::IMVRxchangeMessage CMVRxchangeServiceImpl::TCP_OnIncommingMessage(const IMVRxchangeService::IMVRxchangeMessage& in)
{
	IMVRxchangeService::IMVRxchangeMessage empty;

	if (fCallBack.Callback)
	{
		empty = (*fCallBack.Callback)(in, fCallBack.Context);
	}

	return empty;
}


void CMVRxchangeServiceImpl::SendMessageToLocalNetworks(const TXString& ip, const TXString& port, const MVRxchangeNetwork::MVRxchangePacket& msg)
{
	MVRxchangeNetwork::MVRxchangeClient c (this, msg);

	c.Connect(ip.GetStdString(), port.GetStdString(), std::chrono::seconds(10));
	c.WriteMessage(std::chrono::seconds(10));
}

std::vector<MVRxchangeGoupMember> CMVRxchangeServiceImpl::GetMembersOfService(const ConnectToLocalServiceArgs& services)
{
	std::vector<MVRxchangeGoupMember> list;

	for(const auto& e : fQueryLocalServicesResult)
	{
		MVRxchangeGoupMember member;
		member.IP   = e.IPv4;
		member.Port = e.port;
		list.push_back(member);
	}

	return list;
}

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
	fQueryLocalServucesResult.clear();

	mdns_cpp::mDNS mdns;

	auto query_res = mdns.executeQuery2(MVRXChange_Service);

	if (query_res.size())
	{
		return kVCOMError_Failed;
	}

	for (auto& r : query_res) {
		ConnectToLocalServiceArgs localServ;
		localServ.Service = r.hostNam;

		fQueryLocalServucesResult.push_back(localServ);
	}

	out_Count = fQueryLocalServucesResult.size();

	return kVCOMError_NoError;
}


VCOMError VCOM_CALLTYPE VectorworksMVR::CMVRxchangeServiceImpl::GetLocalServiceAt(size_t index, MvrString& outLocalService)
{
	if ( ! fQueryLocalServucesResult.size())
	{
		return kVCOMError_Failed;
	}

	outLocalService = fQueryLocalServucesResult[index].Service.c_str();

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
	boost::asio::io_context io_context;

	tcp::resolver resolver(io_context);
	auto endpoints = resolver.resolve(ip.GetCharPtr(), port.GetCharPtr());

	MVRxchangeNetwork::MVRxchangeClient c(io_context, endpoints);
	std::thread t = std::thread([&io_context]() { io_context.run(); });

	c.Deliver(msg);
	c.Close();
	t.join();
}

std::vector<MVRxchangeGoupMember> CMVRxchangeServiceImpl::GetMembersOfService(const ConnectToLocalServiceArgs& services)
{
	std::vector<MVRxchangeGoupMember> list;

	MVRxchangeGoupMember member;
	member.IP = "172.16.0.98";
	member.Port = "96";

	list.push_back(member);

	return list; // XXX implement
}

//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CMVRxchangeService.h"
#include "../mvrxchange/mvrxchange_prefix.h"
#include "../mvrxchange/mvrxchange_client.h"
#include "XmlFileHelper.h"
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


VectorworksMVR::CMVRxchangeServiceImpl::CMVRxchangeServiceImpl()
{
	fServer_Running = false;
	fServer = nullptr;
	fmdns_Thread = std::thread(&CMVRxchangeServiceImpl::mDNS_Client_Start, this);
}

VectorworksMVR::CMVRxchangeServiceImpl::~CMVRxchangeServiceImpl()
{
	this->mDNS_Client_Stop();
}

VCOMError VectorworksMVR::CMVRxchangeServiceImpl::ConnectToLocalService(const ConnectToLocalServiceArgs& service)
{
	//---------------------------------------------------------------------------------------------
	// Start TCP
	fCurrentService = service;
	this->TCP_Start();

	this->mDNS_Client_Task();

	//---------------------------------------------------------------------------------------------
	// Start mDNS Service
	std::string txt;
	txt += "StationName=";
	txt += fCurrentService.StationName.fBuffer;
	txt += ";";
	txt += "StationUUID=";
	txt += SceneData::GdtfConverter::ConvertUUID(VWUUID(fCurrentService.StationUUID.a, fCurrentService.StationUUID.b, fCurrentService.StationUUID.c, fCurrentService.StationUUID.d)).GetStdString();
	
	fmdns.setServiceHostname(std::string(fCurrentService.Service.fBuffer));
	fmdns.setServicePort(fServer->GetPort());
	fmdns.setServiceName(MVRXChange_Service);
	fmdns.setServiceTxtRecord(txt);
	fmdns.startService();

	fMVRGroup = GetMembersOfService(fCurrentService);
	
	//---------------------------------------------------------------------------------------------
	// Start mDNS Service
	SendMessageArgs joinMessage;
	joinMessage.Message.Type = MVRxchangeMessageType::MVR_JOIN;
	strcpy(joinMessage.Message.JOIN.StationName, fCurrentService.StationName);		
	strcpy(joinMessage.Message.JOIN.Provider, fCurrentService.Provider);		
	joinMessage.Message.JOIN.VersionMajor = fCurrentService.VersionMajor;
	joinMessage.Message.JOIN.VersionMinor = fCurrentService.VersionMinor;
	joinMessage.Message.JOIN.StationUUID  = fCurrentService.StationUUID;
	this->Send_message(joinMessage);




	return kVCOMError_NoError;
}


VCOMError VectorworksMVR::CMVRxchangeServiceImpl::LeaveLocalService()
{
	this->TCP_Stop();


	return kVCOMError_NoError;
}


VCOMError VCOM_CALLTYPE  CMVRxchangeServiceImpl::QueryLocalServices(size_t& out_Count)
{
	std::lock_guard<std::mutex> lock (fQueryLocalServicesResult_mtx);
	out_Count = fQueryLocalServicesResult.size();

	return kVCOMError_NoError;
}


VCOMError VCOM_CALLTYPE VectorworksMVR::CMVRxchangeServiceImpl::GetLocalServiceAt(size_t index, ConnectToLocalServiceArgs& outLocalService)
{
	std::lock_guard<std::mutex> lock (fQueryLocalServicesResult_mtx);
	if ( fQueryLocalServicesResult.size() < index)
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
			SendMessageToLocalNetworks(e.IP, e.Port, msg);
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
    
    if(in.Type == MVRxchangeMessageType::MVR_JOIN)
    {
        size_t count = 0;
        this->mDNS_Client_Task();
        fMVRGroup = GetMembersOfService(fCurrentService);
    }

	if (fCallBack.Callback)
	{
		empty = (*fCallBack.Callback)(in, fCallBack.Context);
	}

	return empty;
}


void CMVRxchangeServiceImpl::SendMessageToLocalNetworks(const TXString& ip, uint16_t p, const MVRxchangeNetwork::MVRxchangePacket& msg)
{
	MVRxchangeNetwork::MVRxchangeClient c (this, msg);
	
	char str[80];
	sprintf(str, "%u", p);
	std::string port =str;

	c.Connect(ip.GetStdString(), port, std::chrono::seconds(10));
	c.WriteMessage(std::chrono::seconds(10));
}

std::vector<MVRxchangeGoupMember> CMVRxchangeServiceImpl::GetMembersOfService(const ConnectToLocalServiceArgs& services)
{
	std::vector<MVRxchangeGoupMember> list;
	
	std::lock_guard<std::mutex> lock (fQueryLocalServicesResult_mtx);
	for(const auto& e : fQueryLocalServicesResult)
	{
		if(std::string(e.Service.fBuffer) != (std::string(fCurrentService.Service.fBuffer) + "."  + std::string(MVRXChange_Service)))
		{
			MVRxchangeGoupMember member;
			member.IP   = e.IPv4;
			member.Port = e.Port;
			list.push_back(member);
		}

	}

	return list;
}

void Func(const boost::system::error_code& /*e*/, boost::asio::deadline_timer* t, CMVRxchangeServiceImpl* imp)
{
	std::cout << std::endl<< std::endl << std::endl << " mDNS_Client_Task " << std::endl<< std::endl<< std::endl;
	imp->mDNS_Client_Task();

	t->async_wait(boost::bind(Func, boost::asio::placeholders::error, t, imp));
}

void CMVRxchangeServiceImpl::mDNS_Client_Start()
{
	boost::asio::deadline_timer t(fmdns_IO_Context, boost::posix_time::seconds(120));
	t.async_wait(boost::bind(Func, boost::asio::placeholders::error, &t, this));

	fmdns_IO_Context.run();
}

void CMVRxchangeServiceImpl::mDNS_Client_Stop()
{
	if (fmdns_Thread.joinable())
	{
		fmdns_IO_Context.stop();
		fmdns_Thread.join();
	}
}

void CMVRxchangeServiceImpl::mDNS_Client_Task()
{
	mdns_cpp::mDNS mdns;
	auto query_res = mdns.executeQuery2(MVRXChange_Service);

	std::vector<ConnectToLocalServiceArgs> result;
	for (auto& r : query_res) 
	{
		ConnectToLocalServiceArgs localServ;

		strcpy(localServ.Service, r.hostNam.c_str());		 
		strcpy(localServ.IPv4, r.ipV4_adress.c_str());
		strcpy(localServ.IPv6, r.ipV6_adress.c_str());
		localServ.Port = r.port;

		result.push_back(localServ);
	}

	{
		std::lock_guard<std::mutex> lock (fQueryLocalServicesResult_mtx);
		fQueryLocalServicesResult = result;
	}

}
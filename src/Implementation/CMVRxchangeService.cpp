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
	this->LeaveLocalService();
	//---------------------------------------------------------------------------------------------
	// Start TCP
	fCurrentService = service;
	this->TCP_Start();


	//---------------------------------------------------------------------------------------------
	// Start mDNS Service
	std::string txt1;
	txt1 += "StationName=";
	txt1 += fCurrentService.StationName.fBuffer;
	std::string txt2;
	txt2 += "StationUUID=";
	txt2 += SceneData::GdtfConverter::ConvertUUID(VWUUID(fCurrentService.StationUUID.a, fCurrentService.StationUUID.b, fCurrentService.StationUUID.c, fCurrentService.StationUUID.d)).GetStdString();
	
	std::string txt;
	txt += (uint8_t)txt1.size();
	txt += txt1;
	txt += (uint8_t)txt2.size();
	txt += txt2;

	mdns_cpp::mDNS q;
	fmdns.clear();
	for(auto& s : fmdns)
    {
        s->stopService();
    }
	for(std::pair<std::string, uint32_t> e : q.getInterfaces())
	{
		// Bitmasking IP Address to check if it is 127.x.x.x, which is a loopback adress
		/*
		if(e.second & 4278190080 == 2130706432) {
			continue;
		}
		*/
	
		mdns_cpp::mDNS* s = new mdns_cpp::mDNS();
		s->setServiceHostname(std::string(fCurrentService.Service.fBuffer));
		s->setServicePort(fServer->GetPort());
		s->setServiceIP(e.second);
		s->setServiceName(MVRXChange_Service);
		s->setServiceTxtRecord(txt);
		s->startService();
		fmdns.emplace_back(s);	// Pointer is now managed by the unique ptr and deleted upon fmdns going out of scope
	}


	this->mDNS_Client_Task();

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
    
	SendMessageArgs leaveMessage;
	leaveMessage.Message.Type = MVRxchangeMessageType::MVR_LEAVE;
	leaveMessage.Message.LEAVE.FromStationUUID = fCurrentService.StationUUID;
	this->Send_message(leaveMessage);

    for(auto& s : fmdns)
    {
        s->stopService();
    }
    fmdns.clear();


	return kVCOMError_NoError;
}


VCOMError VCOM_CALLTYPE  CMVRxchangeServiceImpl::QueryLocalServices(size_t& out_Count)
{
    this->mDNS_Client_Task();
    
    {
        std::lock_guard<std::mutex> lock (fQueryLocalServicesResult_mtx);
        out_Count = fQueryLocalServicesResult.size();
    }
	

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
        this->mDNS_Client_Task(); // Run, in case client was faster than task

		MVRxchangeGroupMember newItem;
		if(GetSingleMemberOfService(in.JOIN.StationUUID, newItem) == kVCOMError_NoError)
		{
			// In case Station sent message twice (e.g. to change their name)
			auto it = std::find_if(fMVRGroup.begin(), fMVRGroup.end(), [&newItem](const MVRxchangeGroupMember& it){
				return it.IP == newItem.IP && it.Port == newItem.Port;
			});
			
			if(it != fMVRGroup.end())
			{
				*it = newItem; // changed name
			}else
			{
				fMVRGroup.push_back(newItem);
			}
		}
		else
		{
			// could not locate station
		}
    }
	else if(in.Type == MVRxchangeMessageType::MVR_LEAVE)
	{
		MVRxchangeGroupMember newItem;
		if(GetSingleMemberOfService(in.LEAVE.FromStationUUID, newItem) == kVCOMError_NoError)
		{
			std::remove_if(fMVRGroup.begin(), fMVRGroup.end(), [&newItem](const MVRxchangeGroupMember& it){
				return it.IP == newItem.IP && it.Port == newItem.Port;
			});
		}
	}

	if (fCallBack.Callback)
	{
		empty = (*fCallBack.Callback)(in, fCallBack.Context);
	}

	return empty;
}


bool CMVRxchangeServiceImpl::SendMessageToLocalNetworks(const TXString& ip, uint16_t p, const MVRxchangeNetwork::MVRxchangePacket& msg)
{
	MVRxchangeNetwork::MVRxchangeClient c (this, msg);
	
	char str[80];
	sprintf(str, "%u", p);
	std::string port =str;

	bool ok = false;
	if(c.Connect(ip.GetStdString(), port, std::chrono::seconds(1)))
	{
		ok = c.WriteMessage(std::chrono::seconds(10));
	}

	return ok;
}

std::vector<MVRxchangeGroupMember> CMVRxchangeServiceImpl::GetMembersOfService(const ConnectToLocalServiceArgs& services)
{
	std::vector<MVRxchangeGroupMember> list;
	
	std::lock_guard<std::mutex> lock (fQueryLocalServicesResult_mtx);
	for(const auto& e : fQueryLocalServicesResult)
	{
		std::string service(e.Service.fBuffer);

        if(service == std::string(services.Service))
		{
			MVRxchangeGroupMember member;
			member.IP   = e.IPv4;
			member.Port = e.Port;
			member.Name = e.StationName;
			list.push_back(member);
		}

	}

	return list;
}

VCOMError CMVRxchangeServiceImpl::GetSingleMemberOfService(const MvrUUID& stationUUID, MVRxchangeGroupMember& out){
	std::lock_guard<std::mutex> lock (fQueryLocalServicesResult_mtx);


	for(const auto& e : fQueryLocalServicesResult)
	{
        if(e.StationUUID == stationUUID)
		{
			MVRxchangeGroupMember member;
			member.IP   = e.IPv4;
			member.Port = e.Port;
			member.Name = e.StationName;
			out = member;
			return kVCOMError_NoError;
		}

	}

	return kVCOMError_Failed;
}


void Func(const boost::system::error_code& /*e*/, boost::asio::deadline_timer* t, CMVRxchangeServiceImpl* imp)
{
	std::cout << std::endl<< std::endl << std::endl << " mDNS_Client_Task " << std::endl<< std::endl<< std::endl;
	imp->mDNS_Client_Task();

	t->async_wait(boost::bind(Func, boost::asio::placeholders::error, t, imp));
}

void CMVRxchangeServiceImpl::mDNS_Client_Start()
{
	boost::asio::deadline_timer t_short(fmdns_IO_Context, boost::posix_time::seconds(1));
	boost::asio::deadline_timer t_long (fmdns_IO_Context, boost::posix_time::seconds(120));
	t_short.async_wait(boost::bind(Func, boost::asio::placeholders::error, &t_long, this));

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
	std::string serviceAsString(MVRXChange_Service);
	std::vector<ConnectToLocalServiceArgs> result;
	
	for (auto& r : query_res) 
	{
		if(
			r.hostNam.size() < strlen(MVRXChange_Service) ||
			!std::equal(serviceAsString.rbegin(), serviceAsString.rend(), r.hostNam.rbegin())
		) {
			// mdns not only retuns query results of the selected service, but also services that broadcasted during query, so filter them out here
			continue;
		}

		ConnectToLocalServiceArgs localServ;

		strcpy(localServ.Service, r.hostNam.c_str());		 
		strcpy(localServ.IPv4, r.ipV4_adress.c_str());
		strcpy(localServ.IPv6, r.ipV6_adress.c_str());
		localServ.Port = r.port;

		// StationName=sdfsd;StationUUID=XXXXX-
		TXString txt  = r.txt;
		TXString uuid;
		TXString name;

		ptrdiff_t pos_name = txt.Find("StationName=");
		if(pos_name != size_t(-1))
		{
			name = txt.Mid(pos_name, txt.Find(';', pos_name));

		}
		ptrdiff_t pos_uuid = txt.Find("StationUUID=");
		if(pos_uuid != size_t(-1))
		{
			uuid = txt.Mid(pos_uuid, txt.Find(';', pos_name));
		}

		SceneData::GdtfConverter::ConvertUUID(uuid, localServ.StationUUID);
		strcpy(localServ.StationName, name.GetCharPtr());


		result.push_back(localServ);
	}

	{
		std::lock_guard<std::mutex> lock (fQueryLocalServicesResult_mtx);
		fQueryLocalServicesResult = result;
	}

}

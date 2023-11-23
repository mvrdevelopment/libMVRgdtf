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
}

VectorworksMVR::CMVRxchangeServiceImpl::~CMVRxchangeServiceImpl()
{
	this->mDNS_Client_Stop();
	this->TCP_Stop();
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

	for(std::pair<std::string, uint32_t> e : mdns_cpp::mDNS().getInterfaces())
	{
		// Bitmasking IP Address to check if it is 127.x.x.x
		// We dont want to start the mDNS Server on loopback addresses
		// If two programs on the same device want to connect, they can use one of the other interfaces as well
		if((e.second & 4278190080) == 2130706432) {
			continue;
		}
	
		mdns_cpp::mDNS* s = new mdns_cpp::mDNS();
		s->setServiceHostname(std::string(fCurrentService.Service.fBuffer));
		s->setServicePort(fServer->GetPort());
		s->setServiceIP(e.second);
		s->setServiceName(MVRXChange_Service);
		s->setServiceTxtRecord(txt);
		s->startService();
		fmdns.emplace_back(s);	// Pointer is now managed by the unique ptr and deleted upon fmdns going out of scope
	}

	bool doInit = false; // avoid deadlock with temp variable
	{
		std::lock_guard<std::mutex> lock(fQueryLocalServicesResult_mtx);
		doInit = !fIsInitialized;
	}

	if(doInit)
	{
		this->mDNS_Client_Task();
	}

	{
		std::lock_guard<std::mutex> lock(fMvrGroupMutex);
		fMVRGroup = GetMembersOfService(fCurrentService);
	}
	
	//---------------------------------------------------------------------------------------------
	// Start mDNS Service
	SendMessageArgs joinMessage;
	joinMessage.Message.Type = MVRxchangeMessageType::MVR_JOIN;
	strcpy(joinMessage.Message.JOIN.StationName, fCurrentService.StationName);		
	strcpy(joinMessage.Message.JOIN.Provider, fCurrentService.Provider);		
	joinMessage.Message.JOIN.VersionMajor 	= fCurrentService.VersionMajor;
	joinMessage.Message.JOIN.VersionMinor 	= fCurrentService.VersionMinor;
	joinMessage.Message.JOIN.StationUUID  	= fCurrentService.StationUUID;
	joinMessage.Message.JOIN.Files			= fCurrentService.InitialFiles;
	this->Send_message(joinMessage);

	if (fmdns_Thread.joinable())
	{
		fmdns_IO_Context.stop();
		fmdns_Thread.join();
	}
	fmdns_Thread = std::thread(&CMVRxchangeServiceImpl::mDNS_Client_Start, this);

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
	std::vector<MvrUUID> recipientFilter;

	{
		using ServiceType = VectorworksMVR::IMVRxchangeService::MVRxchangeMessageType;
		if(messageHandler.Message.Type == ServiceType::MVR_COMMIT)
		{
			recipientFilter.insert(
				recipientFilter.end(), 
				messageHandler.Message.COMMIT.ForStationsUUID.begin(),
				messageHandler.Message.COMMIT.ForStationsUUID.end()
			);
		}
		else if(messageHandler.Message.Type == ServiceType::MVR_REQUEST)
		{
			recipientFilter.insert(
				recipientFilter.end(), 
				messageHandler.Message.REQUEST.FromStationUUID.begin(),
				messageHandler.Message.REQUEST.FromStationUUID.end()
			);
		}
	}

	//---------------------------------------------------------------------------------------------
	// Start mDNS Service
	{
		MVRxchangeNetwork::MVRxchangePacket msg;
		msg.FromExternalMessage(messageHandler.Message);
		std::lock_guard<std::mutex> lock(fMvrGroupMutex);
		for (const auto& e : fMVRGroup)
		{
			if(recipientFilter.size() != 0 && std::find(recipientFilter.begin(), recipientFilter.end(), e.stationUUID) == recipientFilter.end()){
				continue;
			}
			SendMessageToLocalNetworks(e.IP, e.Port, msg);
		}
	}

	delete[] messageHandler.Message.BufferToFile;

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

IMVRxchangeService::IMVRxchangeMessage CMVRxchangeServiceImpl::TCP_OnIncommingMessage(const IMVRxchangeService::IMVRxchangeMessage& in, const TCPMessageInfo& data)
{
	IMVRxchangeService::IMVRxchangeMessage empty;
    
    if(in.Type == MVRxchangeMessageType::MVR_JOIN)
    {

		MVRxchangeGroupMember newItem;
		if(GetSingleMemberOfService(in.JOIN.StationUUID, newItem) == kVCOMError_NoError)
		{
			std::lock_guard<std::mutex> lock(fMvrGroupMutex);
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
			auto& uuid = in.JOIN.StationUUID;
			boost::asio::post(fmdns_IO_Context, [this, uuid](){
				this->mDNS_Client_Task(); // Run, in case client was faster than task
				MVRxchangeGroupMember newItem;
				if(GetSingleMemberOfService(uuid, newItem) == kVCOMError_NoError)
				{
					std::lock_guard<std::mutex> lock(fMvrGroupMutex);
					fMVRGroup.push_back(newItem);
				}

			});
		}
    }
	else if(in.Type == MVRxchangeMessageType::MVR_LEAVE)
	{
		MVRxchangeGroupMember newItem;
		if(GetSingleMemberOfService(in.LEAVE.FromStationUUID, newItem) != kVCOMError_NoError)
		{
			newItem.IP = data.ip;
			newItem.Port = data.port;
		}
		std::lock_guard<std::mutex> lock(fMvrGroupMutex);
		std::remove_if(fMVRGroup.begin(), fMVRGroup.end(), [&newItem](const MVRxchangeGroupMember& it){
			return it.IP == newItem.IP && it.Port == newItem.Port;
		});
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

	std::string port = std::to_string(p);

	bool ok = false;
	if(c.Connect(ip.GetStdString(), port, std::chrono::seconds(1)))
	{
		ok = c.WriteMessage(std::chrono::seconds(10)); // Write & Read each
	}

	return ok;
}

std::vector<MVRxchangeGroupMember> CMVRxchangeServiceImpl::GetMembersOfService(const ConnectToLocalServiceArgs& services)
{
	std::vector<MVRxchangeGroupMember> list;
	std::string serviceAsString(MVRXChange_Service);

	std::lock_guard<std::mutex> lock (fQueryLocalServicesResult_mtx);
	for(const auto& e : fQueryLocalServicesResult)
	{
		std::string service(e.Service.fBuffer);

        if(service == (std::string(services.Service) + '.' + serviceAsString))
		{
			MVRxchangeGroupMember member;
			member.IP   = e.IPv4;
			member.Port = e.Port;
			member.Name = e.StationName;
			member.stationUUID = e.StationUUID;
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
			member.stationUUID = stationUUID;
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
	boost::asio::deadline_timer t_long (fmdns_IO_Context, boost::posix_time::seconds(45));
	{
		boost::asio::deadline_timer t_short(fmdns_IO_Context, boost::posix_time::seconds(1));
		t_short.async_wait(boost::bind(Func, boost::asio::placeholders::error, &t_long, this));
	}
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

mdns_cpp::QueryResList CMVRxchangeServiceImpl::mDNS_Filter_Queries(mdns_cpp::QueryResList &input)
{
	mdns_cpp::QueryResList out;

	std::string serviceAsString(MVRXChange_Service);

	for (auto &i : input)
	{
		auto it = std::find_if(out.begin(), out.end(), [&i](mdns_cpp::Query_result &result)
							   { return i.ipV4_adress == result.ipV4_adress && i.ipV6_adress == result.ipV6_adress && i.port && result.port; });

		if (it != out.end())		{continue;}	// filter multiple
		if (!i.ipV4_adress.size())	{continue;}	// filter empty

		// IPv6 is currently not supported
		//if (!i.ipV6_adress.size())	{continue;} // filter empty

		bool found = false;
		std::string ipPort = i.ipV4_adress + ':' + std::to_string(i.port);

		for (auto &socket : fmdns)
		{
			std::string o = socket->getServiceIPPort();
			if (ipPort == o)
			{
				found = true;
			}
		}

		if (found)
		{
			// filter own ips
			continue;
		}

		if (
			i.service_name.size() < serviceAsString.size() ||
			!std::equal(serviceAsString.rbegin(), serviceAsString.rend(), i.service_name.rbegin()))
		{
			// mdns not only retuns query results of the selected service, but also services that broadcasted during query, so filter them out here
			// as an alternative, filtering could be done directly in the mdns lib, so that the timeout is only resetted when the selected service answered
			continue;
		}

		out.push_back(std::move(i));
	}

	return out;
}

void CMVRxchangeServiceImpl::mDNS_Client_Task()
{

	
	mdns_cpp::mDNS mdns;
	auto query_res = mdns.executeQuery2(MVRXChange_Service);
	std::vector<ConnectToLocalServiceArgs> result;
	
	query_res = this->mDNS_Filter_Queries(query_res);

	for (auto& r : query_res) 
	{
		result.emplace_back();
		ConnectToLocalServiceArgs& localServ = result.back();

		strcpy(localServ.Service, r.canonical_hostname.c_str());		 
		strcpy(localServ.IPv4, r.ipV4_adress.c_str());
		strcpy(localServ.IPv6, r.ipV6_adress.c_str());
		localServ.Port = r.port;

		const char* length1  = r.txt.data();
		const char* length2  = r.txt.data() + *length1 + 1 ;

		TXString name (length1+1, *length1);
		TXString uuid (length2+1, *length2);
        
        name.Replace("StationName=", "");
		uuid.Replace("StationUUID=", "");

		SceneData::GdtfConverter::ConvertUUID(uuid, localServ.StationUUID);
		strcpy(localServ.StationName, name.GetCharPtr());
	}

	{
		std::lock_guard<std::mutex> lock (fQueryLocalServicesResult_mtx);
		fQueryLocalServicesResult = result;
		fIsInitialized = true;
	}

}

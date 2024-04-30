//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "../Prefix/StdAfx.h"
#include "CMVRxchangeService.h"
#include "../mvrxchange/mvrxchange_prefix.h"
#include "../mvrxchange/mvrxchange_client.h"
#include "../XmlFileHelper.h"
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <unordered_map>
#include <thread>
#include <regex>

VectorworksMVR::CMVRxchangeServiceImpl::CMVRxchangeServiceImpl(): fmdns_long_timer(fmdns_IO_Context)
{
	fServer = nullptr;
}

VectorworksMVR::CMVRxchangeServiceImpl::~CMVRxchangeServiceImpl()
{
	this->mDNS_Client_Stop();
	if(fmdns_Thread.joinable())
	{
		fmdns_Thread.join();
	}
	this->TCP_Stop();
}

void FilterServiceName(MVRxchangeString& service)
{
	std::string s(service.fBuffer);
	std::string out;
    
	if(s.empty())
	{
		return;
	}

	std::regex_replace(std::back_inserter(out), s.begin(), s.end(), std::regex("[^a-zA-Z0-9\\-_]"), "");

	service = out.c_str();
}


VCOMError VectorworksMVR::CMVRxchangeServiceImpl::ConnectToLocalService(const ConnectToLocalServiceArgs& service)
{
	this->LeaveLocalService();
	//---------------------------------------------------------------------------------------------
	// Start TCP
	fCurrentService = service;
	this->TCP_Start();

	FilterServiceName(fCurrentService.Service);

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
		fMVRGroup = GetMembersOfService(fCurrentService.Service);
	}
	
	//---------------------------------------------------------------------------------------------
	// Start mDNS Service
	SendMessageArgs joinMessage;
	joinMessage.Message.Type = MVRxchangeMessageType::MVR_JOIN;
	joinMessage.Message.JOIN.StationName 	= fCurrentService.StationName;		
	joinMessage.Message.JOIN.Provider		= fCurrentService.Provider;		
	joinMessage.Message.JOIN.VersionMajor 	= fCurrentService.VersionMajor;
	joinMessage.Message.JOIN.VersionMinor 	= fCurrentService.VersionMinor;
	joinMessage.Message.JOIN.StationUUID  	= fCurrentService.StationUUID;
	joinMessage.Message.JOIN.Commits		= fCurrentService.InitialFiles;
	this->Send_message(joinMessage);

	if (fmdns_Thread.joinable())
	{
		mDNS_Client_Stop();
	}

	mDNS_Client_Start();

	return kVCOMError_NoError;
}


VCOMError VectorworksMVR::CMVRxchangeServiceImpl::LeaveLocalService()
{
	this->TCP_Stop();
    
	SendMessageArgs leaveMessage;
	leaveMessage.Message.Type = MVRxchangeMessageType::MVR_LEAVE;
	leaveMessage.Message.LEAVE.FromStationUUID = fCurrentService.StationUUID;
	this->Send_message(leaveMessage);
	mDNS_Client_Stop();

    for(auto& s : fmdns)
    {
        s->stopService();
    }
    fmdns.clear();


	return kVCOMError_NoError;
}


VCOMError VCOM_CALLTYPE  CMVRxchangeServiceImpl::QueryLocalServices(size_t& out_Count)
{

	if(fmdns_Thread.joinable())
	{
		std::condition_variable cv;
		std::mutex mut;
		std::unique_lock<std::mutex> lock(mut);
		boost::asio::post(fmdns_IO_Context, [this, &cv](){
			this->mDNS_Client_Task();
			cv.notify_all();
		});
		cv.wait(lock);
	}else{
		this->mDNS_Client_Task();
	}

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
	// Send Message async to speed things up
	std::vector<std::future<MVRxchangeNetwork::MVRxchangeClient::SendResult>> toAwait;
	MVRxchangeNetwork::MVRxchangePacket out;
	out.FromExternalMessage(messageHandler.Message);
	{
		std::lock_guard<std::mutex> lock(fMvrGroupMutex);

		for (const auto& e : fMVRGroup)
		{
			if(recipientFilter.size() != 0 && std::find(recipientFilter.begin(), recipientFilter.end(), e.stationUUID) == recipientFilter.end()){
				continue;
			}

			uint16_t port = e.Port;
			for(auto& ip : e.IP)
			{
				toAwait.push_back(std::async(std::launch::async, 
				[this, ip, port, &out](){
					MVRxchangeNetwork::MVRxchangeClient::SendResult ret;
					SendMessageToLocalNetworks(ip, port, out, ret);
					return ret;
				}));
			}
		}
	}

	for(auto& i : toAwait)
	{
		MVRxchangeNetwork::MVRxchangeClient::SendResult result = i.get();
		if(result.success)
		{
			IMVRxchangeService::IMVRxchangeMessage in;
			result.message.ToExternalMessage(in);
			TCP_OnReturningMessage(messageHandler, in, result.messageInfo);
			delete[] in.BufferToFile;
		}else{
			MVRXCHANGE_ERROR(result.error.message());
		}
	}
	
	delete[] messageHandler.Message.BufferToFile;

	return kVCOMError_NoError;
}

//---------------------------------------------------------------------------
// TCP Server - Local Network mode

void CMVRxchangeServiceImpl::TCP_Start()
{
	if (fServer)
	{
		TCP_Stop();
	}

	fServer = new MVRxchangeNetwork::MVRxchangeServer(this);
}

void CMVRxchangeServiceImpl::TCP_Stop()
{
	delete fServer;
	fServer = nullptr;
}

IMVRxchangeService::IMVRxchangeMessage CMVRxchangeServiceImpl::TCP_OnIncommingMessage(const IMVRxchangeService::IMVRxchangeMessage& in, const TCPMessageInfo& data)
{
    
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
			std::lock_guard<std::mutex> lock(fMvrGroupMutex);
			fMVRGroup.erase(
				std::remove_if(fMVRGroup.begin(), fMVRGroup.end(), [&newItem](const MVRxchangeGroupMember& it){
					return it.stationUUID == newItem.stationUUID;
				}),
				fMVRGroup.end()
			);
		}
	}

	IMVRxchangeService::IMVRxchangeMessage ret;
	if (fCallBack.IncomingCallback)
	{
		ret = fCallBack.IncomingCallback(in, fCallBack.Context);
	}


	return ret;
}


void CMVRxchangeServiceImpl::TCP_OnReturningMessage(
	const SendMessageArgs& messageArgs,
	const IMVRxchangeService::IMVRxchangeMessage& in, 
	const TCPMessageInfo& data)
{
	if(messageArgs.CustomReturnCallback)
	{
		messageArgs.CustomReturnCallback(messageArgs.Message, in, messageArgs.CustomReturnContext);
	}else if (fCallBack.ReturningCallback)
	{
		fCallBack.ReturningCallback(messageArgs.Message, in, fCallBack.Context);
	}
}

bool CMVRxchangeServiceImpl::SendMessageToLocalNetworks(const TXString& ip, uint16_t p, const MVRxchangeNetwork::MVRxchangePacket& msg, MVRxchangeNetwork::MVRxchangeClient::SendResult& retVal)
{
	MVRxchangeNetwork::MVRxchangeClient c (msg);

	std::string port = std::to_string(p);

	MVRXCHANGE_DEBUG("sending message to " << ip.GetStdString() << ":" << port);
	if(c.Connect(retVal, ip.GetStdString(), port, std::chrono::seconds(1)))
	{
		retVal = c.SendMessage(std::chrono::seconds(10)); // Write & Read each
	}

	return retVal.success;
}

std::vector<MVRxchangeGroupMember> CMVRxchangeServiceImpl::GetMembersOfService(const MVRxchangeString& serviceName)
{
	std::vector<MVRxchangeGroupMember> list;
	std::string serviceAsString(MVRXChange_Service);

	std::lock_guard<std::mutex> lock (fQueryLocalServicesResult_mtx);
	for(const auto& e : fQueryLocalServicesResult)
	{
		std::string service(e.Service.fBuffer);

        if(service == (std::string(serviceName.fBuffer) + '.' + serviceAsString))
		{
			MVRxchangeGroupMember member;
			for(auto& i : e.IPv4_list)
			{
				member.IP.emplace_back(i);
			}
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
			for(auto& i : e.IPv4_list)
			{
				member.IP.emplace_back(i);
			}
			member.Port = e.Port;
			member.Name = e.StationName;
			member.stationUUID = stationUUID;
			out = member;
			return kVCOMError_NoError;
		}

	}

	return kVCOMError_Failed;
}

void CMVRxchangeServiceImpl::mDNS_Client_Tick()
{
	MVRXCHANGE_DEBUG("mDNS_Client_Tick");
	mDNS_Client_Task();

	fmdns_long_timer.expires_from_now(boost::posix_time::seconds(45));
	fmdns_long_timer.async_wait(boost::bind(&CMVRxchangeServiceImpl::mDNS_Client_Tick, this));
}

void CMVRxchangeServiceImpl::mDNS_Client_RFun()
{	
	while(!fmdns_stop_flag)
	{
		fmdns_IO_Context.run_for(std::chrono::seconds(1));
	}
}

void CMVRxchangeServiceImpl::mDNS_Client_Start()
{
	fmdns_stop_flag = false;
	boost::asio::post(fmdns_IO_Context, boost::bind(&CMVRxchangeServiceImpl::mDNS_Client_Tick, this));
	fmdns_Thread = std::thread(&CMVRxchangeServiceImpl::mDNS_Client_RFun, this);
}

void CMVRxchangeServiceImpl::mDNS_Client_Stop()
{
	fmdns_stop_flag = true;
	if(fmdns_Thread.joinable())
	{
		fmdns_Thread.join();
	}
}


mdns_cpp::QueryResList CMVRxchangeServiceImpl::mDNS_Filter_Queries(mdns_cpp::QueryResList &input)
{
	// IPv6 is currently not supported

	mdns_cpp::QueryResList out;

	std::string serviceAsString(MVRXChange_Service);

	for (auto &i : input)
	{
		// filter multiple
		auto it = std::find_if(out.begin(), out.end(), 
		[&i](mdns_cpp::Query_result &result)
		{ 
			return i.port == result.port && i.ipV4_address == result.ipV4_address && i.ipV6_address == result.ipV6_address; 
		});

		if (it != out.end())		{continue;}	

		if (!i.ipV4_address.size())	{continue;}	// filter empty

		bool found = false;

		// filter own addresses
		for(std::string /*no ref on purpose*/ ipPort : i.ipV4_address)
		{
			ipPort += ':' + std::to_string(i.port);

			for (auto &socket : fmdns)
			{
				std::string o = socket->getServiceIPPort();
				if (ipPort == o)
				{
					found = true;
					break;
				}
			}

			if(found) {
				break;
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
	
	MVRXCHANGE_DEBUG("found (" << query_res.size() << ") unfiltered services");
	query_res = this->mDNS_Filter_Queries(query_res);

	MVRXCHANGE_DEBUG("filtered (" << query_res.size() << "):");

	for (auto& r : query_res) 
	{
		result.emplace_back();
		ConnectToLocalServiceArgs& localServ = result.back();

		localServ.Service = r.canonical_hostname.c_str();	

		for(auto& ip : r.ipV4_address)
		{
			localServ.IPv4_list.emplace_back();
			localServ.IPv4_list.back() = ip.c_str();
		}

		for(auto& ip : r.ipV6_address)
		{
			localServ.IPv6_list.emplace_back();
			localServ.IPv6_list.back() = ip.c_str();
		}
		localServ.Port = r.port;

		TXString name;
		TXString uuid;

		size_t ptr = 0;
		do{
			uint8_t len = r.txt[ptr];

			std::string t = r.txt.substr(ptr + 1, len);
			size_t eqIdx = t.find('=');
			if(eqIdx == std::string::npos)
			{
				continue;
			}

			if(t.rfind("StationName=") == 0)
			{
				name = t.substr(eqIdx + 1);
			}
			else if(t.rfind("StationUUID=") == 0)
			{
				uuid = t.substr(eqIdx + 1);
			}

			ptr += len + 1;
		}while(ptr < r.txt.size());

		SceneData::GdtfConverter::ConvertUUID(uuid, localServ.StationUUID);
		strcpy(localServ.StationName, name.GetCharPtr());

		#ifndef NDEBUG
			std::string out;

			out += std::string(localServ.Service) + " | ";
			for(auto& i : localServ.IPv4_list)
			{
				out += std::string(i.fBuffer) + " | ";
			}

			MVRXCHANGE_DEBUG(out);
		#endif
	}

	{
		std::lock_guard<std::mutex> lock (fQueryLocalServicesResult_mtx);
		fQueryLocalServicesResult = result;
		fIsInitialized = true;
	}

}

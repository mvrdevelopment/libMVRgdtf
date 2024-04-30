//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "mdns_cpp/mdns.hpp"
#include "../mvrxchange/mvrxchange_prefix.h"
#include "../mvrxchange/mvrxchange_server.h"
#include "../mvrxchange/mvrxchange_client.h"


namespace VectorworksMVR
{
	struct MVRxchangeGroupMember
	{
		TXStringArray IP;	  // One Member can broadcast on multiple adapters
		uint16_t Port;
		TXString Name;
		MvrUUID  stationUUID;
	};

	using TCPMessageInfo = MVRxchangeNetwork::TCPMessageInfo;

	//----------------------------------------------------------------------------------------
	class CMVRxchangeServiceImpl : public VCOMImpl<IMVRxchangeService>
	{
	public:
		CMVRxchangeServiceImpl();
		virtual ~CMVRxchangeServiceImpl();
		
		//Interface
	public:
        virtual VCOMError VCOM_CALLTYPE     ConnectToLocalService(const ConnectToLocalServiceArgs& service);
        virtual VCOMError VCOM_CALLTYPE     LeaveLocalService();
		
		virtual VCOMError VCOM_CALLTYPE		QueryLocalServices(size_t& out_Count);        
		virtual VCOMError VCOM_CALLTYPE     GetLocalServiceAt(size_t index, ConnectToLocalServiceArgs& outLocalService);

		virtual VCOMError VCOM_CALLTYPE     ConnectToRemoteService(const ConnectToRemoteServiceArgs& service);
		virtual VCOMError VCOM_CALLTYPE     LeaveRemoteService();

		virtual VCOMError VCOM_CALLTYPE     OnMessage(OnMessageArgs& messageHandler);
		virtual VCOMError VCOM_CALLTYPE     Send_message(const SendMessageArgs& messageHandler);

	private:
		void mDNS_Client_Task();	// actual mdns task
		
		void mDNS_Client_Tick();	// mdns tick function (executed by RFun function)
		void mDNS_Client_RFun();	// thread function (executed by fmdns_Thread)

		void mDNS_Client_Stop();
		void mDNS_Client_Start();


        
		std::vector<std::unique_ptr<mdns_cpp::mDNS>>	fmdns;
		std::thread 									fmdns_Thread;
		boost::asio::io_context 						fmdns_IO_Context;
		boost::asio::deadline_timer						fmdns_long_timer;
		std::atomic<bool>								fmdns_stop_flag;

		std::mutex 										fQueryLocalServicesResult_mtx;
		std::vector<ConnectToLocalServiceArgs> 			fQueryLocalServicesResult;
		bool											fIsInitialized = false;

		MVRxchangeNetwork::MVRxchangeServer*			fServer;
		ConnectToLocalServiceArgs						fCurrentService;

		void TCP_Start();
		void TCP_Stop();
	public:
		IMVRxchangeMessage TCP_OnIncommingMessage(const IMVRxchangeMessage&, const TCPMessageInfo&);
		void 			   TCP_OnReturningMessage(const SendMessageArgs&, const IMVRxchangeMessage&, const TCPMessageInfo&);

		std::mutex fMvrGroupMutex;
		std::vector<MVRxchangeGroupMember>			fMVRGroup;
	private:

		OnMessageArgs  fCallBack;
		//---------------------------------------------------------------------------
		// TCP Client - Local Network mode

		bool SendMessageToLocalNetworks(const TXString& ip, uint16_t p, const MVRxchangeNetwork::MVRxchangePacket& msg, MVRxchangeNetwork::MVRxchangeClient::SendResult& retVal);


		//---------------------------------------------------------------------------
		// mDNS Functions

		// Get Services for a certain name
		// [serviceName] is the name without _mvrxchange._tcp.local. ; e.g. for TestService._mvrxchange._tcp.local. use TestService as [serviceName]
		std::vector<MVRxchangeGroupMember> 			GetMembersOfService(const MVRxchangeString& serviceName);
		inline std::vector<MVRxchangeGroupMember> 	GetMembersOfService(const TXString& serviceName) {
			MVRxchangeString t;
			t = serviceName.GetCharPtr();
			return GetMembersOfService(t);
		}

		VCOMError 							GetSingleMemberOfService(const MvrUUID& stationUUID, MVRxchangeGroupMember& out);

		// Filters duplicates and own mDNS-sockets
		// this function is moving objects from [input]. Do not use [input] after this call
		mdns_cpp::QueryResList 				mDNS_Filter_Queries(mdns_cpp::QueryResList& input);
	};
}

//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "mdns_cpp/mdns.hpp"
#include "../mvrxchange/mvrxchange_prefix.h"
#include "../mvrxchange/mvrxchange_server.h"


namespace VectorworksMVR
{
	struct MVRxchangeGoupMember
	{
		TXString IP;
		uint16_t Port;
		TXString Name;
	};
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
		mdns_cpp::mDNS 			fmdns;
		std::vector<ConnectToLocalServiceArgs> fQueryLocalServicesResult;

		//---------------------------------------------------------------------------
		// TCP Server - Local Network mode
		boost::asio::io_context 					fServer_IO_Context;
		MVRxchangeNetwork::MVRxchangeServer*	    fServer;
		std::thread									fServer_Thread;
		std::atomic<bool>							fServer_Running;

		void TCP_Start();
		void TCP_Stop();
		void TCP_ServerNetworksThread();
	public:
		IMVRxchangeMessage TCP_OnIncommingMessage(const IMVRxchangeMessage&);

	private:
		std::vector<MVRxchangeGoupMember>			fMVRGroup;

		OnMessageArgs  fCallBack;
		//---------------------------------------------------------------------------
		// TCP Client - Local Network mode

		void SendMessageToLocalNetworks(const TXString& ip, uint16_t p, const MVRxchangeNetwork::MVRxchangePacket& msg);


		//---------------------------------------------------------------------------
		// mDNS Functions
		std::vector<MVRxchangeGoupMember> GetMembersOfService(const ConnectToLocalServiceArgs& services);
	};
}

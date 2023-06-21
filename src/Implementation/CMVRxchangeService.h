//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "Include/IMediaRessourceVectorInterface.h"
#include "mdns_cpp/mdns.hpp"
#include "../mvrxchange/mvrxchange_prefix.h"


namespace VectorworksMVR
{
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
        virtual VCOMError VCOM_CALLTYPE     GetLocalServices(GetLocalServicesArgs& arg);

		virtual VCOMError VCOM_CALLTYPE     ConnectToRemoteService(const ConnectToRemoteServiceArgs& service);
		virtual VCOMError VCOM_CALLTYPE     LeaveRemoteService();

		virtual VCOMError VCOM_CALLTYPE     OnMessage(MVRxchangeMessageHandler& messageHandler);
		virtual VCOMError VCOM_CALLTYPE     SendMessage(const SendMessageArgs& messageHandler);


	private:
		mdns_cpp::mDNS 			fmdns;

		//---------------------------------------------------------------------------
		// TCP Server - Local Network mode
		boost::asio::io_context 					fServer_IO_Context;
		MVRxchangeNetwork::MVRxchangeServer*	    fServer;
		std::thread									fServer_Thread;
		std::atomic<bool>							fServer_Running;

		void TCP_Start();
		void TCP_Stop();
		void TCP_ServerNetworksThread();

		//---------------------------------------------------------------------------
		// TCP Client - Local Network mode

		void SendMessageToLocalNetworks(const TXString& ip, const TXString& port, const MVRxchangeMessage& msg);





	private:


	};
}

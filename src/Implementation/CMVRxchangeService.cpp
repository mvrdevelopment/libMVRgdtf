//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CMVRxchangeService.h"


VectorworksMVR::CMVRxchangeServiceImpl::CMVRxchangeServiceImpl()
{
  fServer_Running = false;
  fServer         = nullptr;
}

VectorworksMVR::CMVRxchangeServiceImpl::~CMVRxchangeServiceImpl()
{
}

VCOMError VectorworksMVR::CMVRxchangeServiceImpl::ConnectToLocalService(const ConnectToLocalServiceArgs& services)
{
  //---------------------------------------------------------------------------------------------
  // Start TCP
  this->TCP_Start();



  //---------------------------------------------------------------------------------------------
  // Start mDNS Service
  fmdns.setServiceHostname("AirForce1");
  fmdns.setServicePort(5000);
  fmdns.setServiceName("AirForce1");
  fmdns.startService();

  return kVCOMError_NoError;
}


VCOMError VectorworksMVR::CMVRxchangeServiceImpl::LeaveLocalService()
{
  //---------------------------------------------------------------------------------------------
  // End TCP
  this->TCP_Stop();


  //---------------------------------------------------------------------------------------------
  // Stop mDNS Service
	fmdns.stopService();
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

VCOMError VectorworksMVR::CMVRxchangeServiceImpl::OnMessage(MVRxchangeMessageHandler& messageHandler)
{
  return kVCOMError_NoError;
}

VCOMError VectorworksMVR::CMVRxchangeServiceImpl::SendMessage(const SendMessageArgs& messageHandler)
{
  //---------------------------------------------------------------------------------------------
  // Start mDNS Service
  {
    MVRxchangeMessage msg;
    for(const auto& e : fMVRGroup)
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
  if(fServer_Running)
  {
    TCP_Stop();
  }
  
  fServer_Running = true;
  fServer_Thread = std::thread(&CMVRxchangeServiceImpl::TCP_ServerNetworksThread, this);

}


void CMVRxchangeServiceImpl::TCP_Stop()
{
  if(fServer_Thread.joinable())
  {
      fServer_IO_Context.stop();
      fServer_Thread.join();
  }
  fServer_Running = false;
}

void CMVRxchangeServiceImpl::TCP_ServerNetworksThread()
{
  tcp::endpoint endpoint(tcp::v4(), 0);
  fServer = new MVRxchangeNetwork::MVRxchangeServer(fServer_IO_Context, endpoint);
  fServer_IO_Context.run();
}



void CMVRxchangeServiceImpl::SendMessageToLocalNetworks(const TXString& ip, const TXString& port, const MVRxchangeMessage& msg)
{
  boost::asio::io_context io_context;

  tcp::resolver resolver(io_context);
  auto endpoints = resolver.resolve(ip.GetCharPtr(), port.GetCharPtr());

  MVRxchangeNetwork::MVRxchangeClient c (io_context, endpoints);
  std::thread t = std::thread([&io_context](){ io_context.run(); });

  //c.Deliver(msg);
  c.Close();
  t.join();

}
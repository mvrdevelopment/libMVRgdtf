//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CMVRxchangeService.h"


VectorworksMVR::CMVRxchangeServiceImpl::CMVRxchangeServiceImpl()
{
}

VectorworksMVR::CMVRxchangeServiceImpl::~CMVRxchangeServiceImpl()
{
}

VCOMError VectorworksMVR::CMVRxchangeServiceImpl::ConnectToLocalService(const ConnectToLocalServiceArgs& services)
{
  fmdns.setServiceHostname("AirForce1");
  fmdns.setServicePort(5000);
  fmdns.setServiceName("AirForce1");
  fmdns.startService();

  return kVCOMError_NoError;
}


VCOMError VectorworksMVR::CMVRxchangeServiceImpl::LeaveLocalService()
{
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
  return kVCOMError_NoError;
}
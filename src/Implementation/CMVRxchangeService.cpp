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

VCOMError VectorworksMVR::CAlignmentImpl::ConnectToLocalService(const ConnectToLocalServiceArgs& services)
{
  fmdns.setServiceHostname("AirForce1");
  fmdns.setServicePort("AirForce1");
  fmdns.setServiceName("AirForce1");
  fmdns.startService();

}


VCOMError VectorworksMVR::CAlignmentImpl::LeaveLocalService()
{
	fmdns.leaveService();
}


VCOMError VectorworksMVR::CAlignmentImpl::ConnectToRemoteService(const ConnectToRemoteServiceArgs& service)
{
}


VCOMError VectorworksMVR::CAlignmentImpl::LeaveRemoteService()
{
}

VCOMError VectorworksMVR::CAlignmentImpl::OnMessage(MVRxchangeMessageHandler& messageHandler)
{
}

VCOMError VectorworksMVR::CAlignmentImpl::SendMessage(const SendMessageArgs& messageHandler)
{
}
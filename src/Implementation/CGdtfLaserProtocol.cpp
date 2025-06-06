//-----------------------------------------------------------------------------
//----- Copyright MVR Group
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfLaserProtocol.h"
#include "Utility.h"

using namespace VectorworksMVR::Filing;

VectorworksMVR::CGdtfLaserProtocolImpl::CGdtfLaserProtocolImpl()
{
	fLaserProtocol = nullptr;
};

VectorworksMVR::CGdtfLaserProtocolImpl::~CGdtfLaserProtocolImpl()
{
    
};

MvrString VectorworksMVR::CGdtfLaserProtocolImpl::GetName()
{
	// Check Pointer
	if ( ! fLaserProtocol) { return ""; }
	
    return fLaserProtocol->GetName().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfLaserProtocolImpl::SetName(MvrString name)
{
	if( ! fLaserProtocol) return kVCOMError_NotInitialized;	
	
	TXString vwName ( name );
	GdtfUtil::DoesNameContainInvalidChars( vwName );

    fLaserProtocol->SetName(name);

   	return kVCOMError_NoError;    
}

void VectorworksMVR::CGdtfLaserProtocolImpl::SetPointer(SceneData::GdtfLaserProtocol* laserProtocol)
{
    fLaserProtocol = laserProtocol;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfLaserProtocolImpl::BindToObject(void* objAddr)
{
	// Check if valid
	if(!fLaserProtocol) return kVCOMError_NotInitialized;
	
	fLaserProtocol->SetBind(objAddr);
	
	return kVCOMError_NoError;
}

void* VectorworksMVR::CGdtfLaserProtocolImpl::GetBoundObject()
{
	// Check if valid
	if(!fLaserProtocol) return nullptr;
	
	return fLaserProtocol->GetBind();
}

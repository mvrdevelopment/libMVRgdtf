//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfBreak.h"


using namespace VectorworksMVR::Filing;

VectorworksMVR::CGdtfBreakImpl::CGdtfBreakImpl()
{
	fBreak = nullptr;
};

VectorworksMVR::CGdtfBreakImpl::~CGdtfBreakImpl()
{
    
};

VectorworksMVR::VCOMError VectorworksMVR::CGdtfBreakImpl::GetDmxBreak(Sint32 &dmxBreak)
{
	// Check Pointer
	if ( ! fBreak) return kVCOMError_NotInitialized;
	
    dmxBreak = fBreak->GetDmxBreak();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfBreakImpl::GetDmxAddress(DMXAddress &dmxAdress)
{
	// Check Pointer
	if ( ! fBreak) return kVCOMError_NotInitialized;
	
    dmxAdress = fBreak->GetDmxAddress();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfBreakImpl::SetDmxBreak(Sint32 dmxBreak)
{
	// Check Pointer
	if( ! fBreak) return kVCOMError_NotInitialized;

    fBreak->SetDmxBreak(dmxBreak);

	return kVCOMError_NoError;    
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfBreakImpl::SetDmxAddress(DMXAddress dmxAdress)
{
	// Check Pointer
	if( ! fBreak) return kVCOMError_NotInitialized;
	
    fBreak->SetDmxAddress(dmxAdress);

	return kVCOMError_NoError;    
}

void VectorworksMVR::CGdtfBreakImpl::setPointer(SceneData::GdtfBreak *breakp)
{
    fBreak = breakp;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfBreakImpl::BindToObject(void* objAddr)
{
	// Check if valid
	if(!fBreak) return kVCOMError_NotInitialized;
	
	fBreak->SetBind(objAddr);
	
	return kVCOMError_NoError;
}

void* VectorworksMVR::CGdtfBreakImpl::GetBoundObject()
{
	// Check if valid
	if(!fBreak) return nullptr;
	
	return fBreak->GetBind();
}

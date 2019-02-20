//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfDMXPersonality.h"

VectorworksMVR::CGdtfDMXPersonalityImpl::CGdtfDMXPersonalityImpl()
{
}

VectorworksMVR::CGdtfDMXPersonalityImpl::~CGdtfDMXPersonalityImpl()
{
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfDMXPersonalityImpl::BindToObject(void * objAddr)
{   
    // Check if valid
    if ( ! fDMXPersonality) return kVCOMError_NotInitialized;

    fDMXPersonality->SetBind(objAddr);
    return kVCOMError_NoError;
}

void *VCOM_CALLTYPE VectorworksMVR::CGdtfDMXPersonalityImpl::GetBoundObject()
{  
    // Check if valid
    if ( ! fDMXPersonality) return nullptr;

    return fDMXPersonality->GetBind();
}

void VectorworksMVR::CGdtfDMXPersonalityImpl::SetPointer(SceneData::GdtfDMXPersonality * dmxPersonality)
{
    fDMXPersonality = dmxPersonality;
}

SceneData::GdtfDMXPersonality * VectorworksMVR::CGdtfDMXPersonalityImpl::GetPointer()
{
    return fDMXPersonality;
}
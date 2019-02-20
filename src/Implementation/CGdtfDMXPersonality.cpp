//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfDMXPersonality.h"

using namespace VectorworksMVR;

CGdtfDMXPersonalityImpl::CGdtfDMXPersonalityImpl()
{
    fDMXPersonality = nullptr;
}

CGdtfDMXPersonalityImpl::~CGdtfDMXPersonalityImpl()
{
}

VCOMError VCOM_CALLTYPE CGdtfDMXPersonalityImpl::GetValue(size_t& outValue) const
{
    // Check Data
    if (!fDMXPersonality) return kVCOMError_NotInitialized;

    outValue = fDMXPersonality->GetValue();

    return kVCOMError_NoError;    
}

MvrString VCOM_CALLTYPE CGdtfDMXPersonalityImpl::GetDMXMode() const
{
    // Check Data
    if (!fDMXPersonality) { return ""; }

    return  fDMXPersonality->GetDMXMode().GetCharPtr();    
}

VCOMError VCOM_CALLTYPE CGdtfDMXPersonalityImpl::SetValue(size_t val)
{
    // Check Pointer
    if (!fDMXPersonality) return kVCOMError_NotInitialized;

    fDMXPersonality->SetValue(val);

    return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE CGdtfDMXPersonalityImpl::SetDMXMode(MvrString modeName)
{
    // Check Pointer
    if (!fDMXPersonality) return kVCOMError_NotInitialized;

    fDMXPersonality->SetDMXMode (modeName);

    return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE CGdtfDMXPersonalityImpl::BindToObject(void * objAddr)
{   
    // Check if valid
    if ( ! fDMXPersonality) return kVCOMError_NotInitialized;

    fDMXPersonality->SetBind(objAddr);
    return kVCOMError_NoError;
}

void *VCOM_CALLTYPE CGdtfDMXPersonalityImpl::GetBoundObject()
{  
    // Check if valid
    if ( ! fDMXPersonality) return nullptr;

    return fDMXPersonality->GetBind();
}

void CGdtfDMXPersonalityImpl::SetPointer(SceneData::GdtfDMXPersonality * dmxPersonality)
{
    fDMXPersonality = dmxPersonality;
}

SceneData::GdtfDMXPersonality * CGdtfDMXPersonalityImpl::GetPointer()
{
    return fDMXPersonality;
}
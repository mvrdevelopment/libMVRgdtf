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

VCOMError VCOM_CALLTYPE CGdtfDMXPersonalityImpl::GetDmxMode(IGdtfDmxMode **outDmxMode)
{
    // Check Pointer
    if (!fDMXPersonality) { return kVCOMError_NotInitialized; }

    //---------------------------------------------------------------------------
    // Initialize Object
    SceneData::GdtfDmxMode*	gdtfDmxMode = fDMXPersonality->GetDMXMode();
    if (!gdtfDmxMode) { return kVCOMError_NotSet; }

    CGdtfDmxModeImpl*		pDmxModeObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDmxMode, (IVWUnknown**)& pDmxModeObj)))
    {
        // Check Casting
        CGdtfDmxModeImpl* pResultInterface = static_cast<CGdtfDmxModeImpl*>(pDmxModeObj);
        if (pResultInterface)
        {
            pResultInterface->setPointer(gdtfDmxMode);
        }
        else
        {
            pResultInterface->Release();
            pResultInterface = nullptr;
            return kVCOMError_NoInterface;
        }
    }

    //---------------------------------------------------------------------------
    // Check Incomming Object
    if (*outDmxMode)
    {
        (*outDmxMode)->Release();
        *outDmxMode = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *outDmxMode = pDmxModeObj;

    return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE CGdtfDMXPersonalityImpl::SetValue(size_t val)
{
    // Check Pointer
    if (!fDMXPersonality) return kVCOMError_NotInitialized;

    fDMXPersonality->SetValue(val);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDMXPersonalityImpl::SetDmxMode (IGdtfDmxMode * newDmxMode)
{
    if (!fDMXPersonality) { return kVCOMError_NotInitialized; }
    if (!newDmxMode) { return kVCOMError_InvalidArg; }

    // Cast
    CGdtfDmxModeImpl* DmxModeImpl = static_cast<CGdtfDmxModeImpl*>(newDmxMode);
    if (!DmxModeImpl) { return kVCOMError_Failed; }

    // Set Object
    SceneData::GdtfDmxMode* gdtfDmxMode = DmxModeImpl->getPointer();

    if (!gdtfDmxMode) { return kVCOMError_Failed; }

    fDMXPersonality->SetDMXMode (gdtfDmxMode);

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
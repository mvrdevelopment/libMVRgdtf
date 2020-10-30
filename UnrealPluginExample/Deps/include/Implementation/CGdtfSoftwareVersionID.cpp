//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfSoftwareVersionID.h"
#include "CGdtfDMXPersonality.h"

using namespace VectorworksMVR;

CGdtfSoftwareVersionIDImpl::CGdtfSoftwareVersionIDImpl()
{
    fSoftwareVersionID = nullptr;
}

CGdtfSoftwareVersionIDImpl::~CGdtfSoftwareVersionIDImpl()
{
}

VCOMError CGdtfSoftwareVersionIDImpl::GetValue(size_t& outVal)
{
    // Check Data
    if (!fSoftwareVersionID) return kVCOMError_NotInitialized;

    outVal = fSoftwareVersionID->GetValue();

    return kVCOMError_NoError;
}


VCOMError CGdtfSoftwareVersionIDImpl::SetValue(size_t value)
{
    // Check Pointer
    if (!fSoftwareVersionID) return kVCOMError_NotInitialized;

    fSoftwareVersionID->SetValue(value);

    return kVCOMError_NoError;
}


VCOMError VCOM_CALLTYPE CGdtfSoftwareVersionIDImpl::GetDMXPersonalityCount(size_t & outCount)
{
    if (!fSoftwareVersionID) { return kVCOMError_NotInitialized; }
                                
    outCount = fSoftwareVersionID->GetDMXPersonalityArray().size();

    return kVCOMError_NoError;
}


VCOMError VCOM_CALLTYPE CGdtfSoftwareVersionIDImpl::GetDMXPersonalityAt(size_t at, IGdtfDMXPersonality** outValue)
{
    // Check if Set
    if (!fSoftwareVersionID) { return kVCOMError_NotInitialized; }

    // Check if no Overflow
    if (at >= fSoftwareVersionID->GetDMXPersonalityArray().size()) { return kVCOMError_OutOfBounds; }


    SceneData::GdtfDMXPersonality* gdtfDMXPersonality = fSoftwareVersionID->GetDMXPersonalityArray()[at];


    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfDMXPersonalityImpl* pDMXPersonalityObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDMXPersonality, (IVWUnknown**)& pDMXPersonalityObj)))
    {
        // Check Casting
        CGdtfDMXPersonalityImpl* pResultInterface = static_cast<CGdtfDMXPersonalityImpl*>(pDMXPersonalityObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfDMXPersonality);
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
    if (*outValue)
    {
        (*outValue)->Release();
        *outValue = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *outValue = pDMXPersonalityObj;

    return kVCOMError_NoError;
}


VCOMError VCOM_CALLTYPE CGdtfSoftwareVersionIDImpl::CreateDMXPersonality(size_t dmxPersonalityValue, IGdtfDmxMode* dmxMode, IGdtfDMXPersonality **outVal)
{
    // Check if Set
    if (!fSoftwareVersionID) { return kVCOMError_NotInitialized; }


    CGdtfDmxModeImpl* mode = static_cast<CGdtfDmxModeImpl*>(dmxMode);

    SceneData::GdtfDMXPersonality* gdtfDMXPersonality = fSoftwareVersionID->AddDMXPersonality(dmxPersonalityValue, mode->getPointer() );

    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfDMXPersonalityImpl* pDMXPersonalityObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDMXPersonality, (IVWUnknown**)& pDMXPersonalityObj)))
    {
        // Check Casting
        CGdtfDMXPersonalityImpl* pResultInterface = static_cast<CGdtfDMXPersonalityImpl*>(pDMXPersonalityObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfDMXPersonality);
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
    if (*outVal)
    {
        (*outVal)->Release();
        *outVal = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *outVal = pDMXPersonalityObj;

    return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE CGdtfSoftwareVersionIDImpl::BindToObject(void * objAddr)
{
    // Check if valid
    if (!fSoftwareVersionID) return kVCOMError_NotInitialized;

    fSoftwareVersionID->SetBind(objAddr);

    return kVCOMError_NoError;
}

void *VCOM_CALLTYPE CGdtfSoftwareVersionIDImpl::GetBoundObject()
{
    // Check if valid
    if (!fSoftwareVersionID) return nullptr;

    return fSoftwareVersionID->GetBind();
}

void CGdtfSoftwareVersionIDImpl::SetPointer(SceneData::GdtfSoftwareVersionID * softwareVersionID)
{
    fSoftwareVersionID = softwareVersionID;
}

SceneData::GdtfSoftwareVersionID * CGdtfSoftwareVersionIDImpl::GetPointer()
{
    return fSoftwareVersionID;
}

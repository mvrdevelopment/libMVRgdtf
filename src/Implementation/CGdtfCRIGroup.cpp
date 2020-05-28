//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfCRIGroup.h"
#include "CGdtfCRI.h"

VectorworksMVR::CGdtfCRIGroupImpl::CGdtfCRIGroupImpl()
{
}

VectorworksMVR::CGdtfCRIGroupImpl::~CGdtfCRIGroupImpl()
{
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfCRIGroupImpl::GetColorTemperature(double& outVal)
{
    // Check Data
    if (!fCRIGroup) return kVCOMError_NotInitialized;

    outVal = fCRIGroup->GetColorTemperature();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfCRIGroupImpl::SetColorTemperature(double value)
{
    // Check Pointer
    if (!fCRIGroup) return kVCOMError_NotInitialized;

    fCRIGroup->SetColorTemperature(value);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfCRIGroupImpl::GetCRICount(size_t &count)
{
    if (!fCRIGroup) { return kVCOMError_NotInitialized; }

    count = fCRIGroup->GetCRI_Array().size();

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfCRIGroupImpl::GetCRIAt(size_t at, VectorworksMVR::IGdtfCRI** value)
{
    // Check if Set
    if (!fCRIGroup) { return kVCOMError_NotInitialized; }

    // Check if no Overflow
    if (at >= fCRIGroup->GetCRI_Array().size()) { return kVCOMError_OutOfBounds; }


    SceneData::GdtfCRI* gdtfCRI = fCRIGroup->GetCRI_Array()[at];

    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfCRIImpl* pCRIObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfCRI, (IVWUnknown**)& pCRIObj)))
    {
        // Check Casting
        CGdtfCRIImpl* pResultInterface = static_cast<CGdtfCRIImpl*>(pCRIObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfCRI);
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
    if (*value)
    {
        (*value)->Release();
        *value = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *value = pCRIObj;

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfCRIGroupImpl::CreateCRI(EGdtfColorSample ces, Sint32 colorTemp, VectorworksMVR::IGdtfCRI **outVal)
{
    // Check if Set
    if (!fCRIGroup) { return kVCOMError_NotInitialized; }


    SceneData::GdtfCRI* gdtfCRI = fCRIGroup->Add_CRI( ces, colorTemp);

    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfCRIImpl* pCRIObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfCRI, (IVWUnknown**)& pCRIObj)))
    {
        // Check Casting
        CGdtfCRIImpl* pResultInterface = static_cast<CGdtfCRIImpl*>(pCRIObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfCRI);
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
    *outVal = pCRIObj;

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfCRIGroupImpl::BindToObject(void * objAddr)
{
    // Check if valid
    if (!fCRIGroup) return kVCOMError_NotInitialized;

    fCRIGroup->SetBind(objAddr);

    return kVCOMError_NoError;
}

void * VectorworksMVR::CGdtfCRIGroupImpl::GetBoundObject()
{
    // Check if valid
    if (!fCRIGroup) return nullptr;

    return fCRIGroup->GetBind();
}

void VectorworksMVR::CGdtfCRIGroupImpl::SetPointer(SceneData::GdtfCRIGroup * CRIGroup)
{
    fCRIGroup = CRIGroup;
}

SceneData::GdtfCRIGroup * VectorworksMVR::CGdtfCRIGroupImpl::GetPointer()
{
    return fCRIGroup;
}

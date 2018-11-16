//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "VectorworksMVR.h"
#include "CGdtfRDMParameterNotification.h"
#include "CGdtfRDMParameterValue.h"


VectorworksMVR::CGdtfRDMParameterNotificationImpl::CGdtfRDMParameterNotificationImpl()
{
	fParamNotification = nullptr;
};

VectorworksMVR::CGdtfRDMParameterNotificationImpl::~CGdtfRDMParameterNotificationImpl()
{
    
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterNotificationImpl::GetPID(Sint32& outVal)
{
    // Check Data
    if (!fParamNotification) return kVCOMError_NotInitialized;

    outVal = fParamNotification->GetPID();

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterNotificationImpl::SetPID(Sint32 value)
{
    // Check Pointer
    if (!fParamNotification) return kVCOMError_NotInitialized;

    fParamNotification->SetPID(value);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterNotificationImpl::GetRDMParameterValueCount(size_t &count)
{
    if (!fParamNotification) { return kVCOMError_NotInitialized; }

    count = fParamNotification->GetParameterValueArray().size();

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterNotificationImpl::GetRDMParameterValueAt(size_t at, VectorworksMVR::IGdtfRDMParameterValue** value)
{
    // Check if Set
    if (!fParamNotification) { return kVCOMError_NotInitialized; }

    // Check if no Overflow
    if (at >= fParamNotification->GetParameterValueArray().size()) { return kVCOMError_OutOfBounds; }

    SceneData::GdtfRDMParameterValue* gdtfRDMParameterValue = fParamNotification->GetParameterValueArray()[at];


    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfRDMParameterValueImpl* pRDMParameterValueObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfRDMParameterValue, (IVWUnknown**)& pRDMParameterValueObj)))
    {
        // Check Casting
        CGdtfRDMParameterValueImpl* pResultInterface = dynamic_cast<CGdtfRDMParameterValueImpl*>(pRDMParameterValueObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfRDMParameterValue);
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
    *value = pRDMParameterValueObj;

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterNotificationImpl::CreateRDMParameterValue(EGdtfObjectType type, VectorworksMVR::IGdtfRDMParameterValue **outVal)
{
    // Check if Set
    if (!fParamNotification) { return kVCOMError_NotInitialized; }

    //
    SceneData::GdtfRDMParameterValue* gdtfRDMParameterValue = nullptr;

    switch (type)
    {
    //case eGdtfRDMParameterValue_Numeric:	        gdtfRDMParameterValue = fParamNotification->AddRDMNumericValue();           break;
    case eGdtfRDMValueBool:	                        gdtfRDMParameterValue = fParamNotification->AddRMDValueBool();              break;
    case eGdtfRDMValue_REAL_TIME_CLOCK:             gdtfRDMParameterValue = fParamNotification->AddRealTimeClock();             break;

    default:
        return kVCOMError_InvalidArg;
        break;
    }

    if (!gdtfRDMParameterValue) { return kVCOMError_Failed; }

    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfRDMParameterValueImpl* pRDMParameterValueObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfRDMParameterValue, (IVWUnknown**)& pRDMParameterValueObj)))
    {
        // Check Casting
        CGdtfRDMParameterValueImpl* pResultInterface = dynamic_cast<CGdtfRDMParameterValueImpl*>(pRDMParameterValueObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfRDMParameterValue);
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
    *outVal = pRDMParameterValueObj;
    //
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfRDMParameterNotificationImpl::BindToObject(void * objAddr)
{
    // Check if valid
    if (!fParamNotification) return kVCOMError_NotInitialized;

    fParamNotification->SetBind(objAddr);

    return kVCOMError_NoError;
}

void *VCOM_CALLTYPE VectorworksMVR::CGdtfRDMParameterNotificationImpl::GetBoundObject()
{
    // Check if valid
    if (!fParamNotification) return nullptr;

    return fParamNotification->GetBind();
}

void VectorworksMVR::CGdtfRDMParameterNotificationImpl::SetPointer(SceneData::GdtfRDMParameterNotification * value)
{
    fParamNotification = value;
}

SceneData::GdtfRDMParameterNotification * VectorworksMVR::CGdtfRDMParameterNotificationImpl::GetPointer()
{
    return fParamNotification;
}

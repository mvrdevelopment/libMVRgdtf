//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "VectorworksMVR.h"
#include "CGdtfRDMSensorNotification.h"
#include "CGdtfRDMValueSensor.h"

VectorworksMVR::CGdtfRDMSensorNotificationImpl::CGdtfRDMSensorNotificationImpl()
{
	fSensorNotification = nullptr;
}

VectorworksMVR::CGdtfRDMSensorNotificationImpl::~CGdtfRDMSensorNotificationImpl()
{
    
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMSensorNotificationImpl::GetSensorOffset(Sint32& outVal)
{
    // Check Data
    if (!fSensorNotification) return kVCOMError_NotInitialized;

    outVal = fSensorNotification->GetSensorOffset();

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMSensorNotificationImpl::SetSensorOffset(Sint32 value)
{
    // Check Pointer
    if (!fSensorNotification) return kVCOMError_NotInitialized;

    fSensorNotification->SetSensorOffset(value);

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMSensorNotificationImpl::GetValueSensorCount(size_t &count)
{
    if (!fSensorNotification) { return kVCOMError_NotInitialized; }

    count = fSensorNotification->GetSensorValueArray().size();

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMSensorNotificationImpl::GetValueSensorAt(size_t at, IGdtfRDMValueSensor** value)
{
    // Check if Set
    if (!fSensorNotification) { return kVCOMError_NotInitialized; }

    // Check if no Overflow
    if (at >= fSensorNotification ->GetSensorValueArray().size()) { return kVCOMError_OutOfBounds; }
    
    SceneData::GdtfRDMValueSensor* gdtfSENSOR_DEFINITION = fSensorNotification->GetSensorValueArray()[at];
    
    //---------------------------------------------------------------------------
    // Initialize Object    
    CGdtfRDMValueSensorImpl* pValueSensorObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfRDMValueSensor, (IVWUnknown**)& pValueSensorObj)))
    {
        // Check Casting
        CGdtfRDMValueSensorImpl* pResultInterface = dynamic_cast<CGdtfRDMValueSensorImpl*>(pValueSensorObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfSENSOR_DEFINITION);
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
    *value = pValueSensorObj;

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMSensorNotificationImpl::CreateValueSensor(Sint32 value,
                                                                                            Sint32 lowest,
                                                                                            Sint32 highest,
                                                                                            Sint32 recorded,
                                                                                            EGdtf_RDMValue_ThresholdOperator thresholdOperator,
                                                                                            IGdtfRDMValueSensor** outVal)
{
    // Check if Set
    if (!fSensorNotification) { return kVCOMError_NotInitialized; }


    SceneData::GdtfRDMValueSensor* gdtfSENSOR_DEFINITION = fSensorNotification->AddValueSensor(value, lowest, highest, recorded, thresholdOperator);

    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfRDMValueSensorImpl* pValueSensorObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfRDMValueSensor, (IVWUnknown**)& pValueSensorObj)))
    {
        // Check Casting
        CGdtfRDMValueSensorImpl* pResultInterface = dynamic_cast<CGdtfRDMValueSensorImpl*>(pValueSensorObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfSENSOR_DEFINITION);
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
    *outVal = pValueSensorObj;

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfRDMSensorNotificationImpl::BindToObject(void * objAddr)
{
    // Check if valid
    if (!fSensorNotification) return kVCOMError_NotInitialized;

    fSensorNotification->SetBind(objAddr);

    return kVCOMError_NoError;
}

void *VCOM_CALLTYPE VectorworksMVR::CGdtfRDMSensorNotificationImpl::GetBoundObject()
{
    // Check if valid
    if (!fSensorNotification) return nullptr;

    return fSensorNotification->GetBind();

}
void VectorworksMVR::CGdtfRDMSensorNotificationImpl::SetPointer(SceneData::GdtfRDMSensorNotification * value)
{
    fSensorNotification = value;
}

SceneData::GdtfRDMSensorNotification * VectorworksMVR::CGdtfRDMSensorNotificationImpl::GetPointer()
{
    return fSensorNotification;
}

//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "VectorworksMVR.h"
#include "CGdtfRDMValueSensor.h"

VectorworksMVR::CGdtfRDMValueSensorImpl::CGdtfRDMValueSensorImpl()
{
    fRDMValueSensor = nullptr;
};

VectorworksMVR::CGdtfRDMValueSensorImpl::~CGdtfRDMValueSensorImpl()
{
    
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMValueSensorImpl::GetValue(Sint32 & outVal)
{
    // Check if valid
    if (!fRDMValueSensor) return kVCOMError_NotInitialized;

    outVal = fRDMValueSensor->GetValue();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMValueSensorImpl::GetLowest(Sint32 & outVal)
{
    // Check if valid
    if (!fRDMValueSensor) return kVCOMError_NotInitialized;

    outVal = fRDMValueSensor->GetLowest();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMValueSensorImpl::GetHighest(Sint32 & outVal)
{
    // Check if valid
    if (!fRDMValueSensor) return kVCOMError_NotInitialized;

    outVal = fRDMValueSensor->GetHighest();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMValueSensorImpl::GetRecorded(Sint32 & outVal)
{
    // Check if valid
    if (!fRDMValueSensor) return kVCOMError_NotInitialized;

    outVal = fRDMValueSensor->GetRecorded();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMValueSensorImpl::GetThresholdOperator(EGdtf_RDMValue_ThresholdOperator & outVal)
{
    // Check if valid
    if (!fRDMValueSensor) return kVCOMError_NotInitialized;

    outVal = fRDMValueSensor->GetThresholdOperator();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMValueSensorImpl::SetValue(Sint32 val)
{
    // Check if valid
    if (!fRDMValueSensor) return kVCOMError_NotInitialized;

    fRDMValueSensor->SetValue(val);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMValueSensorImpl::SetLowest(Sint32 val)
{
    // Check if valid
    if (!fRDMValueSensor) return kVCOMError_NotInitialized;

    fRDMValueSensor->SetLowest(val);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMValueSensorImpl::SetHighest(Sint32 val)
{
    // Check if valid
    if (!fRDMValueSensor) return kVCOMError_NotInitialized;

    fRDMValueSensor->SetHighest(val);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMValueSensorImpl::SetRecorded(Sint32 val)
{
    // Check if valid
    if (!fRDMValueSensor) return kVCOMError_NotInitialized;

    fRDMValueSensor->SetRecorded(val);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMValueSensorImpl::SetThresholdOperator(EGdtf_RDMValue_ThresholdOperator val)
{
    // Check if valid
    if (!fRDMValueSensor) return kVCOMError_NotInitialized;

    fRDMValueSensor->SetThresholdOperator(val);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMValueSensorImpl::BindToObject(void * objAddr)
{
    // Check if valid
    if (!fRDMValueSensor) return kVCOMError_NotInitialized;

    fRDMValueSensor->SetBind(objAddr);

    return kVCOMError_NoError;
}

void *VCOM_CALLTYPE VectorworksMVR::CGdtfRDMValueSensorImpl::GetBoundObject()
{
    // Check if valid
    if (!fRDMValueSensor) return nullptr;

    return fRDMValueSensor->GetBind();
}

void VectorworksMVR::CGdtfRDMValueSensorImpl::SetPointer(SceneData::GdtfRDMValueSensor * rdmValueSensor)
{
    fRDMValueSensor = rdmValueSensor;
}

SceneData::GdtfRDMValueSensor * VectorworksMVR::CGdtfRDMValueSensorImpl::GetPointer()
{
    return fRDMValueSensor;
}

//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "VectorworksMVR.h"
#include "CGdtfRDMParameterValue.h"


VectorworksMVR::CGdtfRDMParameterValueImpl::CGdtfRDMParameterValueImpl()
{
	fParamValue = nullptr;
};

VectorworksMVR::CGdtfRDMParameterValueImpl::~CGdtfRDMParameterValueImpl()
{
    
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterValueImpl::GetRDMValueType(EGdtfObjectType& type)
{
    // Check Pointer
    if (!fParamValue) { return kVCOMError_NotInitialized; }

    type = fRDMParamValueType;
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterValueImpl::GetThresholdOperator(EGdtf_RDMValue_ThresholdOperator value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    // In this special case there several types that share these function.

	/* TODO
    if (fRDMParamValueType == EGdtfObjectType::eGdtfRDMParameterValue_Numeric)
    {
        SceneData::GdtfRDMParameterValue_Numeric* numVal = dynamic_cast<SceneData::GdtfRDMParameterValue_Numeric*>(fRDMParamValue);
        if (!numVal) { return kVCOMError_Failed; }

        value = numVal->GetThresholdOperator();
    }
    else*/ if (fRDMParamValueType == EGdtfObjectType::eGdtfRDMValueBool)
    {
        SceneData::GdtfRDMValueBool* valBool = dynamic_cast<SceneData::GdtfRDMValueBool*>(fRDMParamValue);
        if (!valBool) { return kVCOMError_Failed; }

        value = valBool->GetThresholdOperator();
    }
    else if (fRDMParamValueType == EGdtfObjectType::eGdtfRDMValue_REAL_TIME_CLOCK)
    {
        SceneData::GdtfRDMValue_RealTimeClock* clock = dynamic_cast<SceneData::GdtfRDMValue_RealTimeClock*>(fRDMParamValue);
        if (!clock) { return kVCOMError_Failed; }

        value = clock->GetThresholdOperator();
    }
    else 
    {
        return kVCOMError_WrongRDMParameterValueType;
    }
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterValueImpl::SetThresholdOperator(EGdtf_RDMValue_ThresholdOperator value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    // In this special case there several types that share these function.

	/* TODO
    if (fRDMParamValueType == EGdtfObjectType::eGdtfRDMParameterValue_Numeric)
    {
        SceneData::GdtfRDMParameterValue_Numeric* numVal = dynamic_cast<SceneData::GdtfRDMParameterValue_Numeric*>(fRDMParamValue);
        if (!numVal) { return kVCOMError_Failed; }

        numVal->SetThresholdOperator(value);
    }
    else */if (fRDMParamValueType == EGdtfObjectType::eGdtfRDMValueBool)
    {
        SceneData::GdtfRDMValueBool* valBool = dynamic_cast<SceneData::GdtfRDMValueBool*>(fRDMParamValue);
        if (!valBool) { return kVCOMError_Failed; }

        valBool->SetThresholdOperator(value);
    }
    else if (fRDMParamValueType == EGdtfObjectType::eGdtfRDMValue_REAL_TIME_CLOCK)
    {
        SceneData::GdtfRDMValue_RealTimeClock* clock = dynamic_cast<SceneData::GdtfRDMValue_RealTimeClock*>(fRDMParamValue);
        if (!clock) { return kVCOMError_Failed; }

        clock->SetThresholdOperator(value);
    }
    else
    {
        return kVCOMError_WrongRDMParameterValueType;
    }

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError  VectorworksMVR::CGdtfRDMParameterValueImpl::GetValue(Sint32 & value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    // TODO if (fRDMParamValueType != EGdtfObjectType::eGdtfRDMParameterValue_Numeric) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMParameterValue_Numeric* rdmNumValue = dynamic_cast<SceneData::GdtfRDMParameterValue_Numeric*>(fRDMParamValue);
    if (!rdmNumValue) { return kVCOMError_Failed; }

    value = rdmNumValue->GetValue();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError  VectorworksMVR::CGdtfRDMParameterValueImpl::SetValue(Sint32 value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    // TODO if (fRDMParamValueType != EGdtfObjectType::eGdtfRDMParameterValue_Numeric) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMParameterValue_Numeric* rdmNumValue = dynamic_cast<SceneData::GdtfRDMParameterValue_Numeric*>(fRDMParamValue);
    if (!rdmNumValue) { return kVCOMError_Failed; }

    rdmNumValue->SetValue (value);
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterValueImpl::GetBoolValue(EGdtf_RDMValueBool_Value & value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eGdtfRDMValueBool) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValueBool* RDMValueBool = dynamic_cast<SceneData::GdtfRDMValueBool*>(fRDMParamValue);
    if (!RDMValueBool) { return kVCOMError_Failed; }

    value = RDMValueBool->GetValue();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError  VectorworksMVR::CGdtfRDMParameterValueImpl::SetBoolValue(EGdtf_RDMValueBool_Value value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eGdtfRDMValueBool) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValueBool* RDMValueBool = dynamic_cast<SceneData::GdtfRDMValueBool*>(fRDMParamValue);
    if (!RDMValueBool) { return kVCOMError_Failed; }

    RDMValueBool->SetValue(value);
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError  VectorworksMVR::CGdtfRDMParameterValueImpl::GetFootPrint(Sint32 & value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION* RDMValue_DMX_PERSONALITY_DESCRIPTION = dynamic_cast<SceneData::GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION*>(fRDMParamValue);
    if (!RDMValue_DMX_PERSONALITY_DESCRIPTION) { return kVCOMError_Failed; }

    value = RDMValue_DMX_PERSONALITY_DESCRIPTION->GetFootPrint();
    return kVCOMError_NoError;
}

MvrString  VectorworksMVR::CGdtfRDMParameterValueImpl::GetPersonalityDescription()
{
    // Check Pointer
    if (!fRDMParamValue) return "";

    // Check if it is the right type
    if (fRDMParamValueType == EGdtfObjectType::eGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION) 
    {
        SceneData::GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION* pers = dynamic_cast<SceneData::GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION*>(fRDMParamValue);
        if (!pers) { return ""; }

        return pers->GetDescription().GetCharPtr();
    }
    else if (fRDMParamValueType == EGdtfObjectType::eGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION)
    {
        SceneData::GdtfRDMValue_SENSOR_DEFINITION* sensor = dynamic_cast<SceneData::GdtfRDMValue_SENSOR_DEFINITION*>(fRDMParamValue);
        if (!sensor) { return ""; }

        return sensor->GetDescription().GetCharPtr();
    }

    return "";
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterValueImpl::SetSensorDefiniType(EGdtf_RDMValue_SENSOR_DEFINITION_TYPE value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eRDMValue_SENSOR_DEFINITION) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_SENSOR_DEFINITION* sensorDefini = dynamic_cast<SceneData::GdtfRDMValue_SENSOR_DEFINITION*>(fRDMParamValue);
    if (!sensorDefini) { return kVCOMError_Failed; }

    sensorDefini->SetType(value);
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterValueImpl::SetSensorUnit(EGdtf_RDMParam_SensorUnit value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eRDMValue_SENSOR_DEFINITION) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_SENSOR_DEFINITION* sensorDefini = dynamic_cast<SceneData::GdtfRDMValue_SENSOR_DEFINITION*>(fRDMParamValue);
    if (!sensorDefini) { return kVCOMError_Failed; }

    sensorDefini->SetUnit(value);
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterValueImpl::SetSensorUnitPrefix(EGdtf_RDMParam_SensorUnitPrefix value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eRDMValue_SENSOR_DEFINITION) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_SENSOR_DEFINITION* sensorDefini = dynamic_cast<SceneData::GdtfRDMValue_SENSOR_DEFINITION*>(fRDMParamValue);
    if (!sensorDefini) { return kVCOMError_Failed; }

    sensorDefini->SetPrefix(value);
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterValueImpl::SetRangeMinValue(Sint32 value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eRDMValue_SENSOR_DEFINITION) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_SENSOR_DEFINITION* sensorDefini = dynamic_cast<SceneData::GdtfRDMValue_SENSOR_DEFINITION*>(fRDMParamValue);
    if (!sensorDefini) { return kVCOMError_Failed; }

    sensorDefini->SetRangeMinValue(value);
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterValueImpl::SetRangeMaxValue(Sint32 value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eRDMValue_SENSOR_DEFINITION) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_SENSOR_DEFINITION* sensorDefini = dynamic_cast<SceneData::GdtfRDMValue_SENSOR_DEFINITION*>(fRDMParamValue);
    if (!sensorDefini) { return kVCOMError_Failed; }

    value = sensorDefini->GetRangeMaxValue();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterValueImpl::SetNormalMinValue(Sint32 value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eRDMValue_SENSOR_DEFINITION) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_SENSOR_DEFINITION* sensorDefini = dynamic_cast<SceneData::GdtfRDMValue_SENSOR_DEFINITION*>(fRDMParamValue);
    if (!sensorDefini) { return kVCOMError_Failed; }

    sensorDefini->SetNormalMinValue(value);
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterValueImpl::SetNormalMaxValue(Sint32 value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eRDMValue_SENSOR_DEFINITION) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_SENSOR_DEFINITION* sensorDefini = dynamic_cast<SceneData::GdtfRDMValue_SENSOR_DEFINITION*>(fRDMParamValue);
    if (!sensorDefini) { return kVCOMError_Failed; }

    sensorDefini->SetNormalMaxValueype(value);
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterValueImpl::SetLowesHighestDetectionSupported(EGdtf_RDMValue_LowesHighestDetectionSupported value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eRDMValue_SENSOR_DEFINITION) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_SENSOR_DEFINITION* sensorDefini = dynamic_cast<SceneData::GdtfRDMValue_SENSOR_DEFINITION*>(fRDMParamValue);
    if (!sensorDefini) { return kVCOMError_Failed; }

    sensorDefini->SetLowesHighestDetectionSupported(value);    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterValueImpl::SetRecordValueSupported(EGdtf_RDMValue_RecordValueSupported value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eRDMValue_SENSOR_DEFINITION) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_SENSOR_DEFINITION* sensorDefini = dynamic_cast<SceneData::GdtfRDMValue_SENSOR_DEFINITION*>(fRDMParamValue);
    if (!sensorDefini) { return kVCOMError_Failed; }

    sensorDefini->SetRecordValueSupported(value);
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError  VectorworksMVR::CGdtfRDMParameterValueImpl::GetDmxOffset(Sint32 & value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eGdtfRDMValue_SLOT_INFO) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_SLOT_INFO* slot_Info = dynamic_cast<SceneData::GdtfRDMValue_SLOT_INFO*>(fRDMParamValue);
    if (!slot_Info) { return kVCOMError_Failed; }

    value = slot_Info->GetOffset();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError  VectorworksMVR::CGdtfRDMParameterValueImpl::GetSlotInfoType(EGdtf_RDMValue_SLOT_INFO_Type & value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eGdtfRDMValue_SLOT_INFO) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_SLOT_INFO* slot_Info = dynamic_cast<SceneData::GdtfRDMValue_SLOT_INFO*>(fRDMParamValue);
    if (!slot_Info) { return kVCOMError_Failed; }

    value = slot_Info->GetType();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError  VectorworksMVR::CGdtfRDMParameterValueImpl::GetSlotLabelID(EGdtf_RDMValue_SLOT_INFO_SlotLabelID & value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eGdtfRDMValue_SLOT_INFO) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_SLOT_INFO* slot_Info = dynamic_cast<SceneData::GdtfRDMValue_SLOT_INFO*>(fRDMParamValue);
    if (!slot_Info) { return kVCOMError_Failed; }

    value = slot_Info->GetSlotLabelID();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError  VectorworksMVR::CGdtfRDMParameterValueImpl::SetDmxOffset(Sint32 value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eGdtfRDMValue_SLOT_INFO) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_SLOT_INFO* slot_Info = dynamic_cast<SceneData::GdtfRDMValue_SLOT_INFO*>(fRDMParamValue);
    if (!slot_Info) { return kVCOMError_Failed; }

    slot_Info->SetOffset(value);
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError  VectorworksMVR::CGdtfRDMParameterValueImpl::SetSlotInfoType(EGdtf_RDMValue_SLOT_INFO_Type value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eGdtfRDMValue_SLOT_INFO) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_SLOT_INFO* slot_Info = dynamic_cast<SceneData::GdtfRDMValue_SLOT_INFO*>(fRDMParamValue);
    if (!slot_Info) { return kVCOMError_Failed; }

    slot_Info->SetType(value);
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError  VectorworksMVR::CGdtfRDMParameterValueImpl::SetSlotLabelID(EGdtf_RDMValue_SLOT_INFO_SlotLabelID value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eGdtfRDMValue_SLOT_INFO) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_SLOT_INFO* slot_Info = dynamic_cast<SceneData::GdtfRDMValue_SLOT_INFO*>(fRDMParamValue);
    if (!slot_Info) { return kVCOMError_Failed; }

    slot_Info->SetSlotLabelID(value);
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError  VectorworksMVR::CGdtfRDMParameterValueImpl::GetStatusID(StatusID & value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eRDMValue_STATUS_ID_DESCRIPTION) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_STATUS_ID_DESCRIPTION* statusID_description = dynamic_cast<SceneData::GdtfRDMValue_STATUS_ID_DESCRIPTION*>(fRDMParamValue);
    if (!statusID_description) { return kVCOMError_Failed; }

    value = statusID_description->GetStatusID();
    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError  VectorworksMVR::CGdtfRDMParameterValueImpl::GetStatusDescription(TXString & value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eRDMValue_STATUS_ID_DESCRIPTION) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_STATUS_ID_DESCRIPTION* statusID_description = dynamic_cast<SceneData::GdtfRDMValue_STATUS_ID_DESCRIPTION*>(fRDMParamValue);
    if (!statusID_description) { return kVCOMError_Failed; }

    value = statusID_description->GetDescription();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError  VectorworksMVR::CGdtfRDMParameterValueImpl::SetStatusID(StatusID value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eRDMValue_STATUS_ID_DESCRIPTION) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_STATUS_ID_DESCRIPTION* statusID_description = dynamic_cast<SceneData::GdtfRDMValue_STATUS_ID_DESCRIPTION*>(fRDMParamValue);
    if (!statusID_description) { return kVCOMError_Failed; }

    statusID_description->SetStatusID(value);
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError  VectorworksMVR::CGdtfRDMParameterValueImpl::SetStatusDescription(TXString & value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eRDMValue_STATUS_ID_DESCRIPTION) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_STATUS_ID_DESCRIPTION* statusID_description = dynamic_cast<SceneData::GdtfRDMValue_STATUS_ID_DESCRIPTION*>(fRDMParamValue);
    if (!statusID_description) { return kVCOMError_Failed; }

    statusID_description->SetDescription(value);
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError  VectorworksMVR::CGdtfRDMParameterValueImpl::GetYear(Sint32 & value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eGdtfRDMValue_REAL_TIME_CLOCK) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_RealTimeClock* clock = dynamic_cast<SceneData::GdtfRDMValue_RealTimeClock*>(fRDMParamValue);
    if (!clock) { return kVCOMError_Failed; }

    value = clock->GetYear();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError  VectorworksMVR::CGdtfRDMParameterValueImpl::GetMonth(Sint32 & value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eGdtfRDMValue_REAL_TIME_CLOCK) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_RealTimeClock* clock = dynamic_cast<SceneData::GdtfRDMValue_RealTimeClock*>(fRDMParamValue);
    if (!clock) { return kVCOMError_Failed; }

    value = clock->GetMonth();
    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError  VectorworksMVR::CGdtfRDMParameterValueImpl::GetDay(Sint32 & value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eGdtfRDMValue_REAL_TIME_CLOCK) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_RealTimeClock* clock = dynamic_cast<SceneData::GdtfRDMValue_RealTimeClock*>(fRDMParamValue);
    if (!clock) { return kVCOMError_Failed; }

    value = clock->GetDay();
    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError  VectorworksMVR::CGdtfRDMParameterValueImpl::GetHours(Sint32 & value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eGdtfRDMValue_REAL_TIME_CLOCK) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_RealTimeClock* clock = dynamic_cast<SceneData::GdtfRDMValue_RealTimeClock*>(fRDMParamValue);
    if (!clock) { return kVCOMError_Failed; }

    value = clock->GetHours();
    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError  VectorworksMVR::CGdtfRDMParameterValueImpl::GetMinute(Sint32 & value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eGdtfRDMValue_REAL_TIME_CLOCK) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_RealTimeClock* clock = dynamic_cast<SceneData::GdtfRDMValue_RealTimeClock*>(fRDMParamValue);
    if (!clock) { return kVCOMError_Failed; }

    value = clock->GetMinute();
    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError  VectorworksMVR::CGdtfRDMParameterValueImpl::GetSecond(Sint32 & value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eGdtfRDMValue_REAL_TIME_CLOCK) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_RealTimeClock* clock = dynamic_cast<SceneData::GdtfRDMValue_RealTimeClock*>(fRDMParamValue);
    if (!clock) { return kVCOMError_Failed; }

    value = clock->GetSecond();
    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError  VectorworksMVR::CGdtfRDMParameterValueImpl::SetYear(Sint32 value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eGdtfRDMValue_REAL_TIME_CLOCK) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_RealTimeClock* clock = dynamic_cast<SceneData::GdtfRDMValue_RealTimeClock*>(fRDMParamValue);
    if (!clock) { return kVCOMError_Failed; }

    clock->SetYear(value);
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError  VectorworksMVR::CGdtfRDMParameterValueImpl::SetMonth(Sint32 value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eGdtfRDMValue_REAL_TIME_CLOCK) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_RealTimeClock* clock = dynamic_cast<SceneData::GdtfRDMValue_RealTimeClock*>(fRDMParamValue);
    if (!clock) { return kVCOMError_Failed; }

    clock->SetMonth(value);
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError  VectorworksMVR::CGdtfRDMParameterValueImpl::SetDay(Sint32 value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eGdtfRDMValue_REAL_TIME_CLOCK) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_RealTimeClock* clock = dynamic_cast<SceneData::GdtfRDMValue_RealTimeClock*>(fRDMParamValue);
    if (!clock) { return kVCOMError_Failed; }

    clock->SetDay(value);
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError  VectorworksMVR::CGdtfRDMParameterValueImpl::SetHours(Sint32 value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eGdtfRDMValue_REAL_TIME_CLOCK) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_RealTimeClock* clock = dynamic_cast<SceneData::GdtfRDMValue_RealTimeClock*>(fRDMParamValue);
    if (!clock) { return kVCOMError_Failed; }

    clock->SetHours(value);
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError  VectorworksMVR::CGdtfRDMParameterValueImpl::SetMinute(Sint32 value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eGdtfRDMValue_REAL_TIME_CLOCK) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_RealTimeClock* clock = dynamic_cast<SceneData::GdtfRDMValue_RealTimeClock*>(fRDMParamValue);
    if (!clock) { return kVCOMError_Failed; }

    clock->SetMinute(value);
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError  VectorworksMVR::CGdtfRDMParameterValueImpl::SetSecond(Sint32 value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eGdtfRDMValue_REAL_TIME_CLOCK) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_RealTimeClock* clock = dynamic_cast<SceneData::GdtfRDMValue_RealTimeClock*>(fRDMParamValue);
    if (!clock) { return kVCOMError_Failed; }

    clock->SetSecond(value);
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterValueImpl::BindToObject(void * objAddr)
{
    // Check if valid
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    fRDMParamValue->SetBind(objAddr);

    return kVCOMError_NoError;
}

void * VectorworksMVR::CGdtfRDMParameterValueImpl::GetBoundObject()
{
    // Check if valid
    if (!fRDMParamValue) return nullptr;

    return fRDMParamValue->GetBind();
}

VectorworksMVR::VCOMError  VectorworksMVR::CGdtfRDMParameterValueImpl::SetFootPrint(Sint32 value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION* RDMValue_DMX_PERSONALITY_DESCRIPTION = dynamic_cast<SceneData::GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION*>(fRDMParamValue);
    if (!RDMValue_DMX_PERSONALITY_DESCRIPTION) { return kVCOMError_Failed; }

    RDMValue_DMX_PERSONALITY_DESCRIPTION->SetFootPrint(value);
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError  VectorworksMVR::CGdtfRDMParameterValueImpl::SetPersonalityDescription(MvrString value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION* perso = dynamic_cast<SceneData::GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION*>(fRDMParamValue);
    if (!perso) { return kVCOMError_Failed; }

	TXString name (value);
	
    perso->SetDescription(name);
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterValueImpl::GetSensorDefiniType(EGdtf_RDMValue_SENSOR_DEFINITION_TYPE & value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eRDMValue_SENSOR_DEFINITION) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_SENSOR_DEFINITION* sensorDefini = dynamic_cast<SceneData::GdtfRDMValue_SENSOR_DEFINITION*>(fRDMParamValue);
    if (!sensorDefini) { return kVCOMError_Failed; }

    value = sensorDefini->GetType();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterValueImpl::GetSensorUnit(EGdtf_RDMParam_SensorUnit & value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eRDMValue_SENSOR_DEFINITION) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_SENSOR_DEFINITION* sensorDefini = dynamic_cast<SceneData::GdtfRDMValue_SENSOR_DEFINITION*>(fRDMParamValue);
    if (!sensorDefini) { return kVCOMError_Failed; }

    value = sensorDefini->GetUnit();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterValueImpl::GetSensorUnitPrefix(EGdtf_RDMParam_SensorUnitPrefix & value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eRDMValue_SENSOR_DEFINITION) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_SENSOR_DEFINITION* sensorDefini = dynamic_cast<SceneData::GdtfRDMValue_SENSOR_DEFINITION*>(fRDMParamValue);
    if (!sensorDefini) { return kVCOMError_Failed; }

    value = sensorDefini->GetPrefix();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterValueImpl::GetRangeMinValue(Sint32 & value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eRDMValue_SENSOR_DEFINITION) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_SENSOR_DEFINITION* sensorDefini = dynamic_cast<SceneData::GdtfRDMValue_SENSOR_DEFINITION*>(fRDMParamValue);
    if (!sensorDefini) { return kVCOMError_Failed; }

    value = sensorDefini->GetRangeMinValue();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterValueImpl::GetRangeMaxValue(Sint32 & value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eRDMValue_SENSOR_DEFINITION) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_SENSOR_DEFINITION* sensorDefini = dynamic_cast<SceneData::GdtfRDMValue_SENSOR_DEFINITION*>(fRDMParamValue);
    if (!sensorDefini) { return kVCOMError_Failed; }

    value = sensorDefini->GetRangeMaxValue();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterValueImpl::GetNormalMinValue(Sint32 & value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eRDMValue_SENSOR_DEFINITION) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_SENSOR_DEFINITION* sensorDefini = dynamic_cast<SceneData::GdtfRDMValue_SENSOR_DEFINITION*>(fRDMParamValue);
    if (!sensorDefini) { return kVCOMError_Failed; }

    value = sensorDefini->GetNormalMinValue();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterValueImpl::GetNormalMaxValue(Sint32 & value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eRDMValue_SENSOR_DEFINITION) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_SENSOR_DEFINITION* sensorDefini = dynamic_cast<SceneData::GdtfRDMValue_SENSOR_DEFINITION*>(fRDMParamValue);
    if (!sensorDefini) { return kVCOMError_Failed; }

    value = sensorDefini->GetNormalMaxValueype();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterValueImpl::GetLowesHighestDetectionSupported(EGdtf_RDMValue_LowesHighestDetectionSupported & value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eRDMValue_SENSOR_DEFINITION) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_SENSOR_DEFINITION* sensorDefini = dynamic_cast<SceneData::GdtfRDMValue_SENSOR_DEFINITION*>(fRDMParamValue);
    if (!sensorDefini) { return kVCOMError_Failed; }

    value = sensorDefini->GetLowesHighestDetectionSupported();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterValueImpl::GetRecordValueSupported(EGdtf_RDMValue_RecordValueSupported & value)
{
    // Check Pointer
    if (!fRDMParamValue) return kVCOMError_NotInitialized;

    // Check if it is the right type
    if (fRDMParamValueType != EGdtfObjectType::eRDMValue_SENSOR_DEFINITION) return kVCOMError_WrongRDMParameterValueType;

    SceneData::GdtfRDMValue_SENSOR_DEFINITION* sensorDefini = dynamic_cast<SceneData::GdtfRDMValue_SENSOR_DEFINITION*>(fRDMParamValue);
    if (!sensorDefini) { return kVCOMError_Failed; }

    value = sensorDefini->GetRecordValueSupported();
    return kVCOMError_NoError;
}

//-----------------------------------------------------------------------------
void VectorworksMVR::CGdtfRDMParameterValueImpl::SetPointer(SceneData::GdtfRDMParameterValue * value)
{
    fParamValue        = value;
    fRDMParamValueType = value->GetObjectType();
}


SceneData::GdtfRDMParameterValue * VectorworksMVR::CGdtfRDMParameterValueImpl::GetPointer()
{
    return fParamValue;
}


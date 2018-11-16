//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "GDTFManager.h"

namespace VectorworksMVR
{
    class CGdtfRDMParameterValueImpl : public VCOMImpl<IGdtfRDMParameterValue>
    {    
    public:
        CGdtfRDMParameterValueImpl();
        virtual ~CGdtfRDMParameterValueImpl();
        
    private:
        SceneData::GdtfRDMParameterValue* fParamValue;

    public:
        virtual VCOMError VCOM_CALLTYPE  GetRDMValueType(EGdtfObjectType& type);

        // ThresholdOperator is a attribute NUMERIC_VALUES and RDMValueBool and RDMValue_REAL_TIME_CLOCK. So it can be used by both types. 
        virtual VCOMError VCOM_CALLTYPE  GetThresholdOperator(EGdtf_RDMValue_ThresholdOperator value);
        virtual VCOMError VCOM_CALLTYPE  SetThresholdOperator(EGdtf_RDMValue_ThresholdOperator value);

        // PersonalityDescription is an attribut of RDMValue_DMX_PERSONALITY_DESCRIPTION and RDMValue_SENSOR_DEFINITION
        virtual MvrString VCOM_CALLTYPE  GetPersonalityDescription();
        virtual VCOMError VCOM_CALLTYPE  SetPersonalityDescription(MvrString value);

        /* NUMERIC_VALUES 
            RDMValue_UNSIGNED_BYTE
            RDMValue_SIGNED_BYTE
            RDMValue_UNSIGNED_WORD
            RDMValue_SIGNED_WORD
            RDMValue_UNSIGNED_DWORD
            RDMValue_SIGNED_DWORD
            RDMValue_ASCII */
        
       virtual VCOMError VCOM_CALLTYPE  GetValue(Sint32& value);
       virtual VCOMError VCOM_CALLTYPE  SetValue(Sint32 value);       
       
        //-----------------------------------------------------------------------------
        //RDMValueBool
       virtual VCOMError VCOM_CALLTYPE  GetBoolValue(EGdtf_RDMValueBool_Value& value);        
       virtual VCOMError VCOM_CALLTYPE  SetBoolValue(EGdtf_RDMValueBool_Value value);       
        //-----------------------------------------------------------------------------
        //RDMValue_DMX_PERSONALITY_DESCRIPTION        
       virtual VCOMError VCOM_CALLTYPE  GetFootPrint(Sint32& value );
        
       virtual VCOMError VCOM_CALLTYPE  SetFootPrint(Sint32 value);
        //-----------------------------------------------------------------------------
        //RDMValue_SENSOR_DEFINITION
        // Getter   
       virtual VCOMError VCOM_CALLTYPE  GetSensorDefiniType(EGdtf_RDMValue_SENSOR_DEFINITION_TYPE& value ) ;
       virtual VCOMError VCOM_CALLTYPE  GetSensorUnit(EGdtf_RDMParam_SensorUnit& value) ;
       virtual VCOMError VCOM_CALLTYPE  GetSensorUnitPrefix(EGdtf_RDMParam_SensorUnitPrefix& value) ;
       virtual VCOMError VCOM_CALLTYPE  GetRangeMinValue(Sint32& value) ;
       virtual VCOMError VCOM_CALLTYPE  GetRangeMaxValue(Sint32& value) ;
       virtual VCOMError VCOM_CALLTYPE  GetNormalMinValue(Sint32& value) ;
       virtual VCOMError VCOM_CALLTYPE  GetNormalMaxValue(Sint32& value) ;
       virtual VCOMError VCOM_CALLTYPE  GetLowesHighestDetectionSupported(EGdtf_RDMValue_LowesHighestDetectionSupported& value) ;
       virtual VCOMError VCOM_CALLTYPE  GetRecordValueSupported(EGdtf_RDMValue_RecordValueSupported& value);
        // Setter       
       virtual VCOMError VCOM_CALLTYPE  SetSensorDefiniType(EGdtf_RDMValue_SENSOR_DEFINITION_TYPE value);
       virtual VCOMError VCOM_CALLTYPE  SetSensorUnit(EGdtf_RDMParam_SensorUnit value);
       virtual VCOMError VCOM_CALLTYPE  SetSensorUnitPrefix(EGdtf_RDMParam_SensorUnitPrefix value);
       virtual VCOMError VCOM_CALLTYPE  SetRangeMinValue(Sint32 value);
       virtual VCOMError VCOM_CALLTYPE  SetRangeMaxValue(Sint32 value);
       virtual VCOMError VCOM_CALLTYPE  SetNormalMinValue(Sint32 value);
       virtual VCOMError VCOM_CALLTYPE  SetNormalMaxValue(Sint32 value);
       virtual VCOMError VCOM_CALLTYPE  SetLowesHighestDetectionSupported(EGdtf_RDMValue_LowesHighestDetectionSupported value);
       virtual VCOMError VCOM_CALLTYPE  SetRecordValueSupported(EGdtf_RDMValue_RecordValueSupported value);
        //-----------------------------------------------------------------------------
        //RDMValue_SLOT_INFO
        //  Getter        
       virtual VCOMError VCOM_CALLTYPE  GetDmxOffset(Sint32& value);
       virtual VCOMError VCOM_CALLTYPE  GetSlotInfoType(EGdtf_RDMValue_SLOT_INFO_Type& value );
       virtual VCOMError VCOM_CALLTYPE  GetSlotLabelID(EGdtf_RDMValue_SLOT_INFO_SlotLabelID& value);
        //  Setter       
       virtual VCOMError VCOM_CALLTYPE  SetDmxOffset(Sint32 value);
       virtual VCOMError VCOM_CALLTYPE  SetSlotInfoType(EGdtf_RDMValue_SLOT_INFO_Type value);
       virtual VCOMError VCOM_CALLTYPE  SetSlotLabelID(EGdtf_RDMValue_SLOT_INFO_SlotLabelID value);
        //-----------------------------------------------------------------------------
        //RDMValue_STATUS_ID_DESCRIPTION
        //  Getter        
       virtual VCOMError VCOM_CALLTYPE  GetStatusID(StatusID& value) ;
       virtual VCOMError VCOM_CALLTYPE  GetStatusDescription(TXString& value) ;
        //  Setter       
       virtual VCOMError VCOM_CALLTYPE  SetStatusID(StatusID value);
       virtual VCOMError VCOM_CALLTYPE  SetStatusDescription( TXString& value);
        //-----------------------------------------------------------------------------
        //RDMValue_REAL_TIME_CLOCK
        //  Getter        
       virtual VCOMError VCOM_CALLTYPE  GetYear(Sint32& value);
       virtual VCOMError VCOM_CALLTYPE  GetMonth(Sint32& value);
       virtual VCOMError VCOM_CALLTYPE  GetDay(Sint32& value);
       virtual VCOMError VCOM_CALLTYPE  GetHours(Sint32& value);
       virtual VCOMError VCOM_CALLTYPE  GetMinute(Sint32& value);
       virtual VCOMError VCOM_CALLTYPE  GetSecond(Sint32& value);
        //  Setter
       virtual VCOMError VCOM_CALLTYPE  SetYear(Sint32 value);
       virtual VCOMError VCOM_CALLTYPE  SetMonth(Sint32 value);
       virtual VCOMError VCOM_CALLTYPE  SetDay(Sint32 value);
       virtual VCOMError VCOM_CALLTYPE  SetHours(Sint32 value);
       virtual VCOMError VCOM_CALLTYPE  SetMinute(Sint32 value);
       virtual VCOMError VCOM_CALLTYPE  SetSecond(Sint32 value);

        //-----------------------------------------------------------------------------
       virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
       virtual void*	  VCOM_CALLTYPE    GetBoundObject();
       //
       void SetPointer(SceneData::GdtfRDMParameterValue* value);
       SceneData::GdtfRDMParameterValue*	GetPointer();
private:
    SceneData::GdtfRDMParameterValue* fRDMParamValue;
    EGdtfObjectType				      fRDMParamValueType;
};

    const VWIID IID_GdtfRDMParameterValue = { 0x1d70e880, 0xaf7a, 0x4d03, {0x88, 0xde, 0x50, 0xb7, 0x8f, 0x7e, 0x81, 0xba}};
}

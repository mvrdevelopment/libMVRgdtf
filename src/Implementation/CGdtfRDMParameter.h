//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "CGeometryProviderWrapper.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    class CGdtfRDMParameterImpl : public VectorworksMVR::VCOMImpl<IGdtfRDMParameter>
    {
    public:
        CGdtfRDMParameterImpl();
        virtual ~CGdtfRDMParameterImpl();

        // Getter
        virtual VCOMError VCOM_CALLTYPE GetName(MvrString& outVal);
        virtual VCOMError VCOM_CALLTYPE GetPID(Sint32& outVal);
        virtual VCOMError VCOM_CALLTYPE GetType(EGdtf_RDMParam_Type& outVal);
        virtual VCOMError VCOM_CALLTYPE GetDataType(EGdtf_RDMParam_DataType& outVal);
        virtual VCOMError VCOM_CALLTYPE GetCommand(EGdtf_RDMParam_Command& outVal);
        virtual VCOMError VCOM_CALLTYPE GetSensorUnit(EGdtf_RDMParam_SensorUnit& outVal);
        virtual VCOMError VCOM_CALLTYPE GetSensorUnitPrefix(EGdtf_RDMParam_SensorUnitPrefix& outVal);
        virtual VCOMError VCOM_CALLTYPE GetMinValue(Sint32& outVal);
        virtual VCOMError VCOM_CALLTYPE GetMaxValue(Sint32& outVal);
        virtual VCOMError VCOM_CALLTYPE GetDescription(MvrString& outVal);
        // Setter
        virtual VCOMError VCOM_CALLTYPE SetName(const MvrString& value);
        virtual VCOMError VCOM_CALLTYPE SetPID(Sint32 value);
        virtual VCOMError VCOM_CALLTYPE SetType(EGdtf_RDMParam_Type value);
        virtual VCOMError VCOM_CALLTYPE SetDataType(EGdtf_RDMParam_DataType value);
        virtual VCOMError VCOM_CALLTYPE SetCommand(EGdtf_RDMParam_Command value);        
        virtual VCOMError VCOM_CALLTYPE SetSensorUnit(EGdtf_RDMParam_SensorUnit value);
        virtual VCOMError VCOM_CALLTYPE SetSensorUnitPrefix(EGdtf_RDMParam_SensorUnitPrefix value);
        virtual VCOMError VCOM_CALLTYPE SetMinValue(Sint32 value);
        virtual VCOMError VCOM_CALLTYPE SetMaxValue(Sint32 value);
        virtual VCOMError VCOM_CALLTYPE GetPDLSize(Sint32& outVal);
        virtual VCOMError VCOM_CALLTYPE SetPDLSize(Sint32 value);
        virtual VCOMError VCOM_CALLTYPE SetDescription(const MvrString& value);
        // Arrays
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetRDMParameterValueCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE CreateRDMParameterValue(EGdtfObjectType type, VectorworksMVR::IGdtfRDMParameterValue** outVal);
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetRDMParameterValueAt(size_t at, VectorworksMVR::IGdtfRDMParameterValue** value);
        //        

        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
        virtual void*	  VCOM_CALLTYPE     GetBoundObject();

    private:
        SceneData::GdtfRDMParameter* fParameter;

    public:
        void			                SetPointer(SceneData::GdtfRDMParameter* value);
        SceneData::GdtfRDMParameter*	GetPointer();
    };

    const VWIID IID_GdtfRDMParameter = { 0x9a53bb8b, 0x8806, 0x468e, {0xbd, 0x37, 0x1a, 0xb6, 0x12, 0x68, 0x46, 0x1b}};

}



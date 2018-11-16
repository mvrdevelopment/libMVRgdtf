//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfRDMParameter.h"
#include "CGdtfRDMParameterValue.h"

VectorworksMVR::CGdtfRDMParameterImpl::CGdtfRDMParameterImpl()
{
	fParameter = nullptr;
};

VectorworksMVR::CGdtfRDMParameterImpl::~CGdtfRDMParameterImpl()
{
    
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterImpl::GetName(MvrString& outVal)
{
    // Check Data
    if (!fParameter) return kVCOMError_NotInitialized;

    outVal = fParameter->GetName();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterImpl::SetName(const MvrString& value)
{
    // Check Pointer
    if (!fParameter) return kVCOMError_NotInitialized;

    fParameter->SetName(value);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterImpl::GetPID(Sint32& outVal)
{
    // Check Data
    if (!fParameter) return kVCOMError_NotInitialized;

    outVal = fParameter->GetPID();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterImpl::SetPID(Sint32 value)
{
    // Check Pointer
    if (!fParameter) return kVCOMError_NotInitialized;

    fParameter->SetPID(value);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterImpl::GetType(EGdtf_RDMParam_Type& outVal)
{
    // Check Data
    if (!fParameter) return kVCOMError_NotInitialized;

    outVal = fParameter->GetType();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterImpl::SetType(EGdtf_RDMParam_Type value)
{
    // Check Pointer
    if (!fParameter) return kVCOMError_NotInitialized;

    fParameter->SetType(value);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterImpl::GetDataType(EGdtf_RDMParam_DataType& outVal)
{
    // Check Data
    if (!fParameter) return kVCOMError_NotInitialized;

    outVal = fParameter->GetDataType();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterImpl::SetDataType(EGdtf_RDMParam_DataType value)
{
    // Check Pointer
    if (!fParameter) return kVCOMError_NotInitialized;

    fParameter->SetDataType(value);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterImpl::GetCommand(EGdtf_RDMParam_Command& outVal)
{
    // Check Data
    if (!fParameter) return kVCOMError_NotInitialized;

    outVal = fParameter->GetCommand();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterImpl::SetCommand(EGdtf_RDMParam_Command value)
{
    // Check Pointer
    if (!fParameter) return kVCOMError_NotInitialized;

    fParameter->SetCommand(value);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterImpl::GetSensorUnit(EGdtf_RDMParam_SensorUnit& outVal)
{
    // Check Data
    if (!fParameter) return kVCOMError_NotInitialized;

    outVal = fParameter->GetSensorUnit();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterImpl::SetSensorUnit(EGdtf_RDMParam_SensorUnit value)
{
    // Check Pointer
    if (!fParameter) return kVCOMError_NotInitialized;

    fParameter->SetSensorUnit(value);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterImpl::GetSensorUnitPrefix(EGdtf_RDMParam_SensorUnitPrefix& outVal)
{
    // Check Data
    if (!fParameter) return kVCOMError_NotInitialized;

    outVal = fParameter->GetSensorUnitPrefix();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterImpl::SetSensorUnitPrefix(EGdtf_RDMParam_SensorUnitPrefix value)
{
    // Check Pointer
    if (!fParameter) return kVCOMError_NotInitialized;

    fParameter->SetSensorUnitPrefix(value);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterImpl::GetMinValue(Sint32& outVal)
{
    // Check Data
    if (!fParameter) return kVCOMError_NotInitialized;

    outVal = fParameter->GetMinValue();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterImpl::SetMinValue(Sint32 value)
{
    // Check Pointer
    if (!fParameter) return kVCOMError_NotInitialized;

    fParameter->SetMinValue(value);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterImpl::GetMaxValue(Sint32& outVal)
{
    // Check Data
    if (!fParameter) return kVCOMError_NotInitialized;

    outVal = fParameter->GetMaxValue();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterImpl::SetMaxValue(Sint32 value)
{
    // Check Pointer
    if (!fParameter) return kVCOMError_NotInitialized;

    fParameter->SetMaxValue(value);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterImpl::GetPDLSize(Sint32& outVal)
{
    // Check Data
    if (!fParameter) return kVCOMError_NotInitialized;

    outVal = fParameter->GetPDLSize();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterImpl::SetPDLSize(Sint32 value)
{
    // Check Pointer
    if (!fParameter) return kVCOMError_NotInitialized;

    fParameter->SetPDLSize(value);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfRDMParameterImpl::BindToObject(void * objAddr)
{
    // Check if valid
    if (!fParameter) return kVCOMError_NotInitialized;

    fParameter->SetBind(objAddr);

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterImpl::GetDescription(MvrString& outVal)
{
    // Check Data
    if (!fParameter) return kVCOMError_NotInitialized;

    outVal = fParameter->GetDescription();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterImpl::SetDescription(const MvrString& value)
{
    // Check Pointer
    if (!fParameter) return kVCOMError_NotInitialized;

    fParameter->SetDescription(value);

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterImpl::GetRDMParameterValueCount(size_t &count)
{
    if (!fParameter) { return kVCOMError_NotInitialized; }

    count = fParameter ->GetParameterValueArray().size();

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterImpl::GetRDMParameterValueAt(size_t at, VectorworksMVR::IGdtfRDMParameterValue** value)
{
    // Check if Set
    if (!fParameter) { return kVCOMError_NotInitialized; }

    // Check if no Overflow
    if (at >= fParameter->GetParameterValueArray().size()) { return kVCOMError_OutOfBounds; }
    
    SceneData::GdtfRDMParameterValue* gdtfRDMParameterValue = fParameter->GetParameterValueArray()[at];


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


VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMParameterImpl::CreateRDMParameterValue(EGdtfObjectType type, VectorworksMVR::IGdtfRDMParameterValue **outVal)
{
    // Check if Set
    if (!fParameter) { return kVCOMError_NotInitialized; }
    
    //
    SceneData::GdtfRDMParameterValue* gdtfRDMParameterValue = nullptr;

    switch (type)
    {
    //TODO case eGdtfRDMParameterValue_Numeric:	        gdtfRDMParameterValue = fParameter->AddRDMNumericValue();           break;
    case eGdtfRDMValueBool:	                        gdtfRDMParameterValue = fParameter->AddRMDValueBool();              break;
    case eGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION:	gdtfRDMParameterValue = fParameter->AddDmxPersoalityDescription();  break;
    case eRDMValue_SENSOR_DEFINITION:	            gdtfRDMParameterValue = fParameter->AddSensorDefinition();          break;
    case eGdtfRDMValue_SLOT_INFO:	                gdtfRDMParameterValue = fParameter->AddSlotInfo();                  break;
    case eRDMValue_STATUS_ID_DESCRIPTION:	        gdtfRDMParameterValue = fParameter->AddStatusID_Desciption();       break;

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


void *VCOM_CALLTYPE VectorworksMVR::CGdtfRDMParameterImpl::GetBoundObject()
{
    // Check if valid
    if (!fParameter) return nullptr;

    return fParameter->GetBind();
}

void VectorworksMVR::CGdtfRDMParameterImpl::SetPointer(SceneData::GdtfRDMParameter * value)
{
    fParameter = value;
}

SceneData::GdtfRDMParameter * VectorworksMVR::CGdtfRDMParameterImpl::GetPointer()
{
    return fParameter;
}

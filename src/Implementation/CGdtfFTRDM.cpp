//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfFTRDM.h"
#include "CGdtfRDMParameter.h"
#include "CGdtfRDMNotifications.h"

VectorworksMVR::CGdtf_FTRDMImpl::CGdtf_FTRDMImpl()
{
	f_FtRDM = nullptr;
};

VectorworksMVR::CGdtf_FTRDMImpl::~CGdtf_FTRDMImpl()
{
    
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtf_FTRDMImpl::GetManufacturerID(Sint32& outVal)
{
    // Check Data
    if (!f_FtRDM) return kVCOMError_NotInitialized;

    outVal = f_FtRDM->GetManufacturerID();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtf_FTRDMImpl::SetManufacturerID(Sint32 value)
{
    // Check Pointer
    if (!f_FtRDM) return kVCOMError_NotInitialized;

    f_FtRDM->SetManufacturerID (value);

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtf_FTRDMImpl::BindToObject(void * objAddr)
{
    // Check if valid
    if (!f_FtRDM) return kVCOMError_NotInitialized;

    f_FtRDM->SetBind(objAddr);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtf_FTRDMImpl::GetDeviceModelID(Sint32& outVal)
{

    // Check Data
    if (!f_FtRDM) return kVCOMError_NotInitialized;

    outVal = f_FtRDM->GetDeviceModelID();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtf_FTRDMImpl::SetDeviceModelID(Sint32 value)
{
    // Check Pointer
    if (!f_FtRDM) return kVCOMError_NotInitialized;

    f_FtRDM->SetDeviceModelID (value);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtf_FTRDMImpl::GetSoftwareIDCount(size_t& count)
{
    // Check Data
    if (!f_FtRDM) return kVCOMError_NotInitialized;

    count = f_FtRDM->GetSoftwareVersIDs().size();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtf_FTRDMImpl::GetSoftwareIDAt(size_t at, Sint32& outVal)
{
	// Check Data
	if (!f_FtRDM) return kVCOMError_NotInitialized;
	
	if(f_FtRDM->GetSoftwareVersIDs().size() <= (at + 1)) { return  kVCOMError_OutOfBounds; }
	
	outVal = f_FtRDM->GetSoftwareVersIDs().at(at);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtf_FTRDMImpl::AddSoftwareID(Sint32 softID)
{
    // Check Pointer
    if (!f_FtRDM) return kVCOMError_NotInitialized;

    f_FtRDM->AddSoftwareVersID(softID);

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtf_FTRDMImpl::GetRDMParameterCount(size_t &count)
{
    if (!f_FtRDM) { return kVCOMError_NotInitialized; }

    count = f_FtRDM->GetRDMParametersArray().size();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtf_FTRDMImpl::GetRDMParameterAt(size_t at, VectorworksMVR::IGdtfRDMParameter **RDMParameter)
{
    // Check if Set
    if (!f_FtRDM) { return kVCOMError_NotInitialized; }

    // Check if no Overflow
    if (at >= f_FtRDM->GetRDMParametersArray().size()) { return kVCOMError_OutOfBounds; }


    SceneData::GdtfRDMParameter* gdtfRDMParameter = f_FtRDM->GetRDMParametersArray()[at];
    
    //---------------------------------------------------------------------------
    // Initialize Object    
    CGdtfRDMParameterImpl* pRDMParameterObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfRDMParameter, (IVWUnknown**)& pRDMParameterObj)))
    {
        // Check Casting
        CGdtfRDMParameterImpl* pResultInterface = dynamic_cast<CGdtfRDMParameterImpl*>(pRDMParameterObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfRDMParameter);
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
    if (*RDMParameter)
    {
        (*RDMParameter)->Release();
        *RDMParameter = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *RDMParameter = pRDMParameterObj;

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtf_FTRDMImpl::CreateRDMParameter(VectorworksMVR::IGdtfRDMParameter **outVal,
                MvrString name,
                Sint32 PID, 
                GdtfDefines::EGdtf_RDMParam_Type Type,
                GdtfDefines::EGdtf_RDMParam_DataType dataType,
                GdtfDefines::EGdtf_RDMParam_Command command,
                GdtfDefines::EGdtf_RDMParam_SensorUnit sensorUnit,
                GdtfDefines::EGdtf_RDMParam_SensorUnitPrefix sensorUnitPrefix,
                Sint32 minValue,
                Sint32 maxValue, 
                Sint32 PDLSize, 
                MvrString description)
{
    // Check if Set
    if (!f_FtRDM) { return kVCOMError_NotInitialized; }

    
    SceneData::GdtfRDMParameter* gdtfRDMParameter = f_FtRDM->AddRDMParameter(
        name, 
        PID, 
        Type, 
        dataType, 
        command,
        sensorUnit, 
        sensorUnitPrefix, 
        minValue, 
        maxValue, 
        PDLSize, 
        description);

    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfRDMParameterImpl* pRDMParameterObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfRDMParameter, (IVWUnknown**)& pRDMParameterObj)))
    {
        // Check Casting
        CGdtfRDMParameterImpl* pResultInterface = dynamic_cast<CGdtfRDMParameterImpl*>(pRDMParameterObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfRDMParameter);
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
    *outVal = pRDMParameterObj;

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtf_FTRDMImpl::GetRDMNotifications(VectorworksMVR::IGdtfRDMNotifications **outRDMNotifications)
{
    // Check Pointer
    if (!f_FtRDM) { return kVCOMError_NotInitialized; }

    //---------------------------------------------------------------------------
    // Initialize Object             
    SceneData::GdtfRDMNotifications*	gdtfRDMNotifications = f_FtRDM->GetRDMNotifications();
    if (!gdtfRDMNotifications) { return kVCOMError_NotSet; }

    CGdtfRDMNotificationsImpl*		pRDMNotificationsObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfRDMNotifications, (IVWUnknown**)& pRDMNotificationsObj)))
    {
        // Check Casting
        CGdtfRDMNotificationsImpl* pResultInterface = dynamic_cast<CGdtfRDMNotificationsImpl*>(pRDMNotificationsObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfRDMNotifications);
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
    if (*outRDMNotifications)
    {
        (*outRDMNotifications)->Release();
        *outRDMNotifications = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *outRDMNotifications = pRDMNotificationsObj;

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtf_FTRDMImpl::SetRDMNotifications(IGdtfRDMNotifications * newRDMNotifications)
{
    if (!f_FtRDM) { return kVCOMError_NotInitialized; }
    if (!newRDMNotifications) { return kVCOMError_InvalidArg; }

    // Cast
    CGdtfRDMNotificationsImpl* RDMNotificationsImpl = dynamic_cast<CGdtfRDMNotificationsImpl*>(newRDMNotifications);
    if (!RDMNotificationsImpl) { return kVCOMError_Failed; }

    // Set Object
    SceneData::GdtfRDMNotifications* gdtfRDMNotifications = RDMNotificationsImpl->GetPointer();
    if (!gdtfRDMNotifications) { return kVCOMError_Failed; }

    f_FtRDM->SetRDMNotifications(gdtfRDMNotifications);

    return kVCOMError_NoError;
}


void *VCOM_CALLTYPE VectorworksMVR::CGdtf_FTRDMImpl::GetBoundObject()
{
    // Check if valid
    if (!f_FtRDM) return nullptr;

    return f_FtRDM->GetBind();
}

void VectorworksMVR::CGdtf_FTRDMImpl::SetPointer(SceneData::GdtfFTRDM * value)
{
    f_FtRDM = value;
}

SceneData::GdtfFTRDM * VectorworksMVR::CGdtf_FTRDMImpl::GetPointer()
{
    return f_FtRDM;
}

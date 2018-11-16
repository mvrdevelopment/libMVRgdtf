//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "VectorworksMVR.h"
#include "CGdtfRDMNotifications.h"
#include "CGdtfRDMParameterNotification.h"
#include "CGdtfRDMSensorNotification.h"
#include "CGdtfRDMAbsentNotification.h"

VectorworksMVR::CGdtfRDMNotificationsImpl::CGdtfRDMNotificationsImpl()
{
	fNotifications = nullptr;
};

VectorworksMVR::CGdtfRDMNotificationsImpl::~CGdtfRDMNotificationsImpl()
{
    
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMNotificationsImpl::GetRDMAbsentNotification(VectorworksMVR::IGdtfRDMAbsentNotification **outRDMAbsentNotification)
{
    // Check Pointer
    if (!fNotifications) { return kVCOMError_NotInitialized; }

    //---------------------------------------------------------------------------
    // Initialize Object
    SceneData::GdtfRDMAbsentNotification*	gdtfRDMAbsentNotification = fNotifications->GetAbsentNotification();
    if (!gdtfRDMAbsentNotification) { return kVCOMError_NotSet; }
    
    CGdtfRDMAbsentNotificationImpl*		pRDMAbsentNotificationObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfRDMAbsentNotification, (IVWUnknown**)& pRDMAbsentNotificationObj)))
    {
        // Check Casting
        CGdtfRDMAbsentNotificationImpl* pResultInterface = dynamic_cast<CGdtfRDMAbsentNotificationImpl*>(pRDMAbsentNotificationObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfRDMAbsentNotification);
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
    if (*outRDMAbsentNotification)
    {
        (*outRDMAbsentNotification)->Release();
        *outRDMAbsentNotification = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *outRDMAbsentNotification = pRDMAbsentNotificationObj;

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMNotificationsImpl::SetRDMAbsentNotification(IGdtfRDMAbsentNotification * newRDMAbsentNotification)
{
    if (!fNotifications) { return kVCOMError_NotInitialized; }
    if (!newRDMAbsentNotification) { return kVCOMError_InvalidArg; }

    // Cast
    CGdtfRDMAbsentNotificationImpl* RDMAbsentNotificationImpl = dynamic_cast<CGdtfRDMAbsentNotificationImpl*>(newRDMAbsentNotification);
    if (!RDMAbsentNotificationImpl) { return kVCOMError_Failed; }

    // Set Object
    SceneData::GdtfRDMAbsentNotification* gdtfRDMAbsentNotification = RDMAbsentNotificationImpl->GetPointer();
    if (!gdtfRDMAbsentNotification) { return kVCOMError_Failed; }

    fNotifications->SetAbsentNotification(gdtfRDMAbsentNotification);

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMNotificationsImpl::GetRDMParameterNotificationCount(size_t& count)
{
    if (!fNotifications) { return kVCOMError_NotInitialized; }

    count = fNotifications->GetParameterNotificationArray().size();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMNotificationsImpl::GetRDMParameterNotificationAt(size_t at, VectorworksMVR::IGdtfRDMParameterNotification** value)
{
    // Check if Set
    if (!fNotifications) { return kVCOMError_NotInitialized; }

    // Check if no Overflow
    if (at >= fNotifications ->GetParameterNotificationArray().size()) { return kVCOMError_OutOfBounds; }
    
    SceneData::GdtfRDMParameterNotification* gdtfParamNotif = fNotifications ->GetParameterNotificationArray()[at];
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfRDMParameterNotificationImpl* pRDMParameterNotificationObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfRDMNotifications, (IVWUnknown**)& pRDMParameterNotificationObj)))
    {
        // Check Casting
        CGdtfRDMParameterNotificationImpl* pResultInterface = dynamic_cast<CGdtfRDMParameterNotificationImpl*>(pRDMParameterNotificationObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfParamNotif);
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
    *value = pRDMParameterNotificationObj;

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMNotificationsImpl::GetSensorNotificationCount(size_t &count)
{
    if (!fNotifications) { return kVCOMError_NotInitialized; }

    count = fNotifications ->GetSensorNotificationArray().size();

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMNotificationsImpl::GetSensorNotificationAt(size_t at, VectorworksMVR::IGdtfRDMSensorNotification** value)
{
    // Check if Set
    if (!fNotifications) { return kVCOMError_NotInitialized; }

    // Check if no Overflow
    if (at >= fNotifications->GetSensorNotificationArray().size()) { return kVCOMError_OutOfBounds; }
    
    SceneData::GdtfRDMSensorNotification* gdtfSensorNotification = fNotifications->GetSensorNotificationArray()[at];


    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfRDMSensorNotificationImpl* pSensorNotificationObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfRDMSensorNotification, (IVWUnknown**)& pSensorNotificationObj)))
    {
        // Check Casting
        CGdtfRDMSensorNotificationImpl* pResultInterface = dynamic_cast<CGdtfRDMSensorNotificationImpl*>(pSensorNotificationObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfSensorNotification);
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
    *value = pSensorNotificationObj;

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMNotificationsImpl::CreateSensorNotification(Sint32 sensorOffset, VectorworksMVR::IGdtfRDMSensorNotification** outVal)
{
    // Check if Set
    if (!fNotifications) { return kVCOMError_NotInitialized; }
    
    SceneData::GdtfRDMSensorNotification* gdtfSensorNotification = fNotifications->AddDMSensorNotification(sensorOffset);

    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfRDMSensorNotificationImpl* pSensorNotificationObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfRDMSensorNotification, (IVWUnknown**)& pSensorNotificationObj)))
    {
        // Check Casting
        CGdtfRDMSensorNotificationImpl* pResultInterface = dynamic_cast<CGdtfRDMSensorNotificationImpl*>(pSensorNotificationObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfSensorNotification);
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
    *outVal = pSensorNotificationObj;

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMNotificationsImpl::CreateRDMParameterNotification(Sint32 PID, VectorworksMVR::IGdtfRDMParameterNotification** outVal)
{
    // Check if Set
    if (!fNotifications) { return kVCOMError_NotInitialized; }
    
    SceneData::GdtfRDMParameterNotification* gdtfPramNotification = fNotifications->AddRDMParameterNotification(PID);

    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfRDMParameterNotificationImpl* pRDMParameterNotificationObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfRDMParameterNotification, (IVWUnknown**)& pRDMParameterNotificationObj)))
    {
        // Check Casting
        CGdtfRDMParameterNotificationImpl* pResultInterface = dynamic_cast<CGdtfRDMParameterNotificationImpl*>(pRDMParameterNotificationObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfPramNotification);
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
    *outVal = pRDMParameterNotificationObj;

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfRDMNotificationsImpl::BindToObject(void * objAddr)
{
    // Check if valid
    if (!fNotifications) return kVCOMError_NotInitialized;

    fNotifications->SetBind(objAddr);

    return kVCOMError_NoError;
}

void *VCOM_CALLTYPE VectorworksMVR::CGdtfRDMNotificationsImpl::GetBoundObject()
{
    // Check if valid
    if (!fNotifications) return nullptr;

    return fNotifications->GetBind();
}

void VectorworksMVR::CGdtfRDMNotificationsImpl::SetPointer(SceneData::GdtfRDMNotifications * value)
{
    fNotifications = value;
}

SceneData::GdtfRDMNotifications * VectorworksMVR::CGdtfRDMNotificationsImpl::GetPointer()
{
    return fNotifications;
}

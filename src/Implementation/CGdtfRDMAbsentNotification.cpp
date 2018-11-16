//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "VectorworksMVR.h"
#include "CGdtfRDMAbsentNotification.h"

VectorworksMVR::CGdtfRDMAbsentNotificationImpl::CGdtfRDMAbsentNotificationImpl()
{
	fAbsentNotification = nullptr;
};

VectorworksMVR::CGdtfRDMAbsentNotificationImpl::~CGdtfRDMAbsentNotificationImpl()
{
    
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRDMAbsentNotificationImpl::BindToObject(void * objAddr)
{
    // Check if valid
    if (!fAbsentNotification) return kVCOMError_NotInitialized;

    fAbsentNotification->SetBind(objAddr);

    return kVCOMError_NoError;
}

void * VectorworksMVR::CGdtfRDMAbsentNotificationImpl::GetBoundObject()
{
    // Check if valid
    if (!fAbsentNotification) return nullptr;

    return fAbsentNotification->GetBind();
}

void VectorworksMVR::CGdtfRDMAbsentNotificationImpl::SetPointer(SceneData::GdtfRDMAbsentNotification * value)
{
    fAbsentNotification = value;
}

SceneData::GdtfRDMAbsentNotification * VectorworksMVR::CGdtfRDMAbsentNotificationImpl::GetPointer()
{
    return fAbsentNotification;
}

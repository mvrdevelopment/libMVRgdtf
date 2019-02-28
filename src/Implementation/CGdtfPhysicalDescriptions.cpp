//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfPhysicalDescriptions.h"


CGdtfPhysicalDescriptionsImpl::CGdtfPhysicalDescriptionsImpl()
{
    fPhysicalDescriptions = nullptr;
}

CGdtfPhysicalDescriptionsImpl::~CGdtfPhysicalDescriptionsImpl()
{
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfPhysicalDescriptionsImpl::BindToObject(void * objAddr)
{
    // Check if valid
    if (!fPhysicalDescriptions) return kVCOMError_NotInitialized;

    fPhysicalDescriptions->SetBind(objAddr);

    return kVCOMError_NoError;
}

void *VCOM_CALLTYPE VectorworksMVR::CGdtfPhysicalDescriptionsImpl::GetBoundObject()
{
    // Check if valid
    if (!fPhysicalDescriptions) return nullptr;

    return fPhysicalDescriptions->GetBind();
}

void VectorworksMVR::CGdtfPhysicalDescriptionsImpl::SetPointer(SceneData::GdtfPhysicalDescriptions* val)
{
    fPhysicalDescriptions = val;
}

SceneData::GdtfPhysicalDescriptions * VectorworksMVR::CGdtfPhysicalDescriptionsImpl::GetPointer()
{
    return fPhysicalDescriptions;
}


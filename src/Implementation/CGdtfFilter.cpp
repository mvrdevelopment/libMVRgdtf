//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfFilter.h"

using namespace VectorworksMVR;


CGdtfFilterImpl::CGdtfFilterImpl()
{
    fFilter = nullptr;
}

VectorworksMVR::CGdtfFilterImpl::~CGdtfFilterImpl()
{
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfFilterImpl::BindToObject(void * objAddr)
{
    // Check if valid
    if (!fFilter) return kVCOMError_NotInitialized;

    fFilter->SetBind(objAddr);

    return kVCOMError_NoError;
}

void *VCOM_CALLTYPE VectorworksMVR::CGdtfFilterImpl::GetBoundObject()
{
    // Check if valid
    if (!fFilter) return nullptr;

    return fFilter->GetBind();
}

void VectorworksMVR::CGdtfFilterImpl::SetPointer(SceneData::GdtfFilter * val)
{
    fFilter = val;
}

SceneData::GdtfFilter * VectorworksMVR::CGdtfFilterImpl::GetPointer()
{
    return fFilter;
}



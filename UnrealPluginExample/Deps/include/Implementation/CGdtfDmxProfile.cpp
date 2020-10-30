//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfDmxProfile.h"

VectorworksMVR::CGdtfDMXProfileImpl::CGdtfDMXProfileImpl()
{
}

VectorworksMVR::CGdtfDMXProfileImpl::~CGdtfDMXProfileImpl()
{
    fDMXProfile = nullptr;
}

VectorworksMVR::VCOMError  VectorworksMVR::CGdtfDMXProfileImpl::BindToObject(void * objAddr)
{
    // Check if valid
    if (!fDMXProfile) return kVCOMError_NotInitialized;

    fDMXProfile->SetBind(objAddr);

    return kVCOMError_NoError;
}

void * VectorworksMVR::CGdtfDMXProfileImpl::GetBoundObject()
{
    // Check if valid
    if (!fDMXProfile) return nullptr;

    return fDMXProfile->GetBind();
}

void VectorworksMVR::CGdtfDMXProfileImpl::SetPointer(SceneData::GdtfDMXProfile * dmxProfile)
{
    fDMXProfile = dmxProfile;
}

SceneData::GdtfDMXProfile * VectorworksMVR::CGdtfDMXProfileImpl::GetPointer()
{ 
    return fDMXProfile;
}

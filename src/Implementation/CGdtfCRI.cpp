//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Include/VectorworksMVR.h"
#include "CGdtfCRI.h"

VectorworksMVR::CGdtfCRIImpl::CGdtfCRIImpl()
{
}

VectorworksMVR::CGdtfCRIImpl::~CGdtfCRIImpl()
{
}

VectorworksMVR::VCOMError  VectorworksMVR::CGdtfCRIImpl::GetColorSample(EGdtfColorSample outVal)
{
    // Check Data
    if (!fCRI) return kVCOMError_NotInitialized;

    outVal = fCRI->GetColorSample();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError  VectorworksMVR::CGdtfCRIImpl::GetColorRenderingIndex(Uint8& outVal)
{
    // Check Data
    if (!fCRI) return kVCOMError_NotInitialized;

    outVal = fCRI->GetColorRenderingIndex();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError  VectorworksMVR::CGdtfCRIImpl::SetColorSample(EGdtfColorSample val)
{
    // Check Pointer
    if (!fCRI) return kVCOMError_NotInitialized;

    fCRI->SetColorSample(val);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError  VectorworksMVR::CGdtfCRIImpl::SetColorRenderingIndex(Uint8 val)
{
    // Check Pointer
    if (!fCRI) return kVCOMError_NotInitialized;

    fCRI->SetColorRenderingIndex(val);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError  VectorworksMVR::CGdtfCRIImpl::BindToObject(void * objAddr)
{
    // Check if valid
    if (!fCRI) return kVCOMError_NotInitialized;

    fCRI->SetBind(objAddr);

    return kVCOMError_NoError;
}

void * VectorworksMVR::CGdtfCRIImpl::GetBoundObject()
{
    // Check if valid
    if (!fCRI) return nullptr;

    return fCRI->GetBind();
}

void VectorworksMVR::CGdtfCRIImpl::SetPointer(SceneData::GdtfCRI * CRI)
{
    fCRI = CRI;
}

SceneData::GdtfCRI * VectorworksMVR::CGdtfCRIImpl::GetPointer()
{ 
    return fCRI;
}

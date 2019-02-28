//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfPhysicalDescriptions.h"
#include "CGdtfColorSpace.h"
#include "CGdtfPhysicalEmitter.h" 

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


VectorworksMVR::VCOMError VectorworksMVR::CGdtfPhysicalDescriptionsImpl::GetColorSpace(VectorworksMVR::IGdtfColorSpace **outColorSpace)
{
    // Check Pointer
    if (!fPhysicalDescriptions) { return kVCOMError_NotInitialized; }

    //---------------------------------------------------------------------------
    // Initialize Object
    SceneData::GdtfColorSpace*	gdtfColorSpace = fPhysicalDescriptions->GetColorSpace();
    if (!gdtfColorSpace) { return kVCOMError_NotSet; }

    CGdtfColorSpaceImpl*		pColorSpaceObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfColorSpace, (IVWUnknown**)& pColorSpaceObj)))
    {
        // Check Casting
        CGdtfColorSpaceImpl* pResultInterface = dynamic_cast<CGdtfColorSpaceImpl*>(pColorSpaceObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfColorSpace);
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
    if (*outColorSpace)
    {
        (*outColorSpace)->Release();
        *outColorSpace = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *outColorSpace = pColorSpaceObj;

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfPhysicalDescriptionsImpl::SetColorSpace (IGdtfColorSpace * newColorSpace)
{
    if (!fPhysicalDescriptions) { return kVCOMError_NotInitialized; }
    if (!newColorSpace) { return kVCOMError_InvalidArg; }

    // Cast
    CGdtfColorSpaceImpl* ColorSpaceImpl = dynamic_cast<CGdtfColorSpaceImpl*>(newColorSpace);
    if (!ColorSpaceImpl) { return kVCOMError_Failed; }

    // Set Object
    SceneData::GdtfColorSpace* gdtfColorSpace = ColorSpaceImpl->GetPointer();
    if (!gdtfColorSpace) { return kVCOMError_Failed; }

    fPhysicalDescriptions->SetColorSpace (gdtfColorSpace);

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfPhysicalDescriptionsImpl::GetEmitterCount(size_t &count)
{
    if (!fPhysicalDescriptions) { return kVCOMError_NotInitialized; }

    count = fPhysicalDescriptions->GetPhysicalEmitterArray().size();

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfPhysicalDescriptionsImpl::GetEmitterAt(size_t at, VectorworksMVR::IGdtfPhysicalEmitter** value)
{
    // Check if Set
    if (!fPhysicalDescriptions) { return kVCOMError_NotInitialized; }

    // Check if no Overflow
    if (at >= fPhysicalDescriptions->GetPhysicalEmitterArray().size()) { return kVCOMError_OutOfBounds; }


    SceneData::GdtfPhysicalEmitter* gdtfEmitter = fPhysicalDescriptions->GetPhysicalEmitterArray()[at];
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfPhysicalEmitterImpl* pEmitterObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfPhysicalEmitter, (IVWUnknown**)& pEmitterObj)))
    {
        // Check Casting
        CGdtfPhysicalEmitterImpl* pResultInterface = dynamic_cast<CGdtfPhysicalEmitterImpl*>(pEmitterObj);
        if (pResultInterface)
        {
            pResultInterface->setPointer(gdtfEmitter);
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
    *value = pEmitterObj;

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfPhysicalDescriptionsImpl::CreateEmitter(MvrString name, VectorworksMVR::IGdtfPhysicalEmitter **outVal)
{
    // Check if Set
    if (!fPhysicalDescriptions) { return kVCOMError_NotInitialized; }


    SceneData::GdtfPhysicalEmitter* gdtfEmitter = fPhysicalDescriptions->AddEmitter(name);

    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfPhysicalEmitterImpl* pEmitterObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfPhysicalEmitter, (IVWUnknown**)& pEmitterObj)))
    {
        // Check Casting
        CGdtfPhysicalEmitterImpl* pResultInterface = dynamic_cast<CGdtfPhysicalEmitterImpl*>(pEmitterObj);
        if (pResultInterface)
        {
            pResultInterface->setPointer(gdtfEmitter);
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
    *outVal = pEmitterObj;

    return kVCOMError_NoError;
}





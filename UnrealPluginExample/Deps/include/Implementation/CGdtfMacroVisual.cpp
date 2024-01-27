//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfBreak.h"
#include "CGdtfMacroVisual.h"
#include "CGdtfMacroVisualStep.h"


VectorworksMVR::CGdtfMacroVisualImpl::CGdtfMacroVisualImpl()
{
}

VectorworksMVR::CGdtfMacroVisualImpl::~CGdtfMacroVisualImpl()
{
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMacroVisualImpl::GetVisualStepCount(size_t & outCount)
{    
    if (!fMacroVisual) { return kVCOMError_NotInitialized; }

    outCount = fMacroVisual->GetVisualStepArray().size();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMacroVisualImpl::GetVisualStepAt(size_t at, IGdtfMacroVisualStep ** outVal)
{
    // Check if Set
    if (!fMacroVisual) { return kVCOMError_NotInitialized; }

    // Check if no Overflow
    if (at >= fMacroVisual->GetVisualStepArray().size()) { return kVCOMError_OutOfBounds; }


    SceneData::GdtfMacroVisualStep* gdtfMacroVisStep = fMacroVisual->GetVisualStepArray()[at];
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfMacroVisualStepImpl * pVisualStep= nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfMacroVisualStep, (IVWUnknown**)& pVisualStep)))
    {
        // Check Casting
        CGdtfMacroVisualStepImpl* pResultInterface = static_cast<CGdtfMacroVisualStepImpl*>(pVisualStep);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfMacroVisStep);
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
    *outVal = pVisualStep;

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfMacroVisualImpl::CreateVisualStep(IGdtfMacroVisualStep ** outVal)
{    
    // Check if Set
    if (!fMacroVisual) { return kVCOMError_NotInitialized; }

    SceneData::GdtfMacroVisualStep* gdtfVisualStep = fMacroVisual->AddVisualStep();
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfMacroVisualStepImpl* pVisualStep = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfMacroVisualStep, (IVWUnknown**)& pVisualStep)))
    {
        // Check Casting
        CGdtfMacroVisualStepImpl* pResultInterface = static_cast<CGdtfMacroVisualStepImpl*>(pVisualStep);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfVisualStep);
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
    *outVal = pVisualStep;

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfMacroVisualImpl::BindToObject(void * objAddr)
{
    // Check if valid
    if (!fMacroVisual) return kVCOMError_NotInitialized;

    fMacroVisual->SetBind(objAddr);

    return kVCOMError_NoError;
}

void *VCOM_CALLTYPE VectorworksMVR::CGdtfMacroVisualImpl::GetBoundObject()
{
    // Check if valid
    if (!fMacroVisual) return nullptr;

    return fMacroVisual->GetBind();
}

void VectorworksMVR::CGdtfMacroVisualImpl::SetPointer(SceneData::GdtfMacroVisual * macroVisual)
{
    fMacroVisual = macroVisual;
}

SceneData::GdtfMacroVisual * VectorworksMVR::CGdtfMacroVisualImpl::GetPointer()
{    
    return fMacroVisual;
}

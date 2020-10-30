//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfMacroVisualStep.h"
#include "CGdtfMacroVisualValue.h"
#include "CGdtfDmxChannelFunction.h"

VectorworksMVR::CGdtfMacroVisualStepImpl::CGdtfMacroVisualStepImpl()
{
}

VectorworksMVR::CGdtfMacroVisualStepImpl::~CGdtfMacroVisualStepImpl()
{
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMacroVisualStepImpl::GetDuration(double & duration)
{
    // Check Data
    if (!fMacroVisualStep) return kVCOMError_NotInitialized;

    duration = fMacroVisualStep->getDuration();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMacroVisualStepImpl::GetFade(double & fade)
{
    // Check Data
    if (!fMacroVisualStep) return kVCOMError_NotInitialized;

    fade = fMacroVisualStep->getFade();

    return kVCOMError_NoError;

}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMacroVisualStepImpl::GetDelay(double & delay)
{
    // Check Data
    if (!fMacroVisualStep) return kVCOMError_NotInitialized;

     delay = fMacroVisualStep->getDelay();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMacroVisualStepImpl::SetDuration(double d)
{
    // Check Data
    if (!fMacroVisualStep) return kVCOMError_NotInitialized;
    
    fMacroVisualStep->setDuration(d);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMacroVisualStepImpl::SetFade(double f)
{
    // Check Data
    if (!fMacroVisualStep) return kVCOMError_NotInitialized;
    
    fMacroVisualStep->setFade(f);

   return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMacroVisualStepImpl::SetDelay(double d)
{
    // Check Data
    if (!fMacroVisualStep) return kVCOMError_NotInitialized;
    
    fMacroVisualStep->setDelay(d);
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMacroVisualStepImpl::GetVisualValueCount(size_t& outCount)
{
        if (!fMacroVisualStep) { return kVCOMError_NotInitialized; }

        outCount = fMacroVisualStep->GetVisualValueArray().size();

        return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfMacroVisualStepImpl::GetVisualValueAt(size_t at, IGdtfMacroVisualValue ** outVal)
{ 
    // Check if Set
    if (!fMacroVisualStep) { return kVCOMError_NotInitialized; }

    // Check if no Overflow
    if (at >= fMacroVisualStep->GetVisualValueArray().size()) { return kVCOMError_OutOfBounds; }


    SceneData::GdtfMacroVisualValue* gdtfMacro = fMacroVisualStep->GetVisualValueArray()[at];
    
    //---------------------------------------------------------------------------    
    // Initialize Object
    CGdtfMacroVisualValueImpl* pVisualValue = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfMacroVisualValue, (IVWUnknown**)& pVisualValue)))
    {
        // Check Casting
        CGdtfMacroVisualValueImpl* pResultInterface = static_cast<CGdtfMacroVisualValueImpl*>(pVisualValue);
        
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfMacro);
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
    *outVal = pVisualValue;
    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfMacroVisualStepImpl::CreateVisualValue(DmxValue dmxVal, IGdtfDmxChannelFunction* channelFunction, IGdtfMacroVisualValue ** outVal)
{   
    // Check if Set
    if (!fMacroVisualStep) { return kVCOMError_NotInitialized; }

    //---------------------------------------------------------------------------
    // Cast the ChannelFunction
    if (!channelFunction) { return kVCOMError_InvalidArg; }

    CGdtfDmxChannelFunctionImpl* chnlFuncImpl = static_cast<CGdtfDmxChannelFunctionImpl*>(channelFunction);
    if (!chnlFuncImpl) { return kVCOMError_Failed; }

    // Set Object
    SceneData::GdtfDmxChannelFunction* gdtfDMXChannel = chnlFuncImpl->getPointer();
    if (!gdtfDMXChannel) { return kVCOMError_Failed; }
    //---------------------------------------------------------------------------
    SceneData::GdtfMacroVisualValue* gdtfMacroVisualValue = fMacroVisualStep->AddVisualValue(dmxVal, gdtfDMXChannel);

    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfMacroVisualValueImpl* pMacroVisualValueObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfMacroVisualValue, (IVWUnknown**)& pMacroVisualValueObj)))
    {
        // Check Casting
        CGdtfMacroVisualValueImpl* pResultInterface = static_cast<CGdtfMacroVisualValueImpl*>(pMacroVisualValueObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfMacroVisualValue);
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
    *outVal = pMacroVisualValueObj;

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfMacroVisualStepImpl::BindToObject(void * objAddr)
{
    // Check if valid
    if (!fMacroVisualStep) return kVCOMError_NotInitialized;

    fMacroVisualStep->SetBind(objAddr);

    return kVCOMError_NoError;
}

void *VCOM_CALLTYPE VectorworksMVR::CGdtfMacroVisualStepImpl::GetBoundObject()
{
    // Check if valid
    if (!fMacroVisualStep) return nullptr;

    return fMacroVisualStep->GetBind();
}

void VectorworksMVR::CGdtfMacroVisualStepImpl::SetPointer(SceneData::GdtfMacroVisualStep * macroVisualStep)
{
    fMacroVisualStep = macroVisualStep;
}

SceneData::GdtfMacroVisualStep * VectorworksMVR::CGdtfMacroVisualStepImpl::GetPointer()
{
    return fMacroVisualStep;
}




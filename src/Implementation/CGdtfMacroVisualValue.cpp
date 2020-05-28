//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfMacroVisualValue.h"
#include "CGdtfDmxChannelFunction.h"


VectorworksMVR::CGdtfMacroVisualValueImpl::CGdtfMacroVisualValueImpl()
{
}

VectorworksMVR::CGdtfMacroVisualValueImpl::~CGdtfMacroVisualValueImpl()
{
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMacroVisualValueImpl::GetDmxValue(DmxValue& outValue)
{
    // Check Data
    if (!fMacroVisualValue) return kVCOMError_NotInitialized;

    outValue = fMacroVisualValue->GetDmxValue();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfMacroVisualValueImpl::GetDmxChannel(IGdtfDmxChannelFunction** outValue)
{
    // Check Data
    if (!fMacroVisualValue) return kVCOMError_NotInitialized;

    SceneData::GdtfDmxChannelFunction* gdtfDmxChannel = fMacroVisualValue->GetChannelFunctionRef();
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfDmxChannelFunctionImpl* pChannelFunc = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDmxChannelFunction, (IVWUnknown**)& pChannelFunc)))
    {
        // Check Casting
        CGdtfDmxChannelFunctionImpl* pResultInterface = static_cast<CGdtfDmxChannelFunctionImpl* >(pChannelFunc);
        if (pResultInterface)
        {
            pResultInterface->setPointer(gdtfDmxChannel);
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
    if (*outValue)
    {
        (*outValue)->Release();
        *outValue = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *outValue = pChannelFunc;

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfMacroVisualValueImpl::SetDmxValue(DmxValue newValue)
{
    // Check Data
    if (!fMacroVisualValue) return kVCOMError_NotInitialized;

    fMacroVisualValue->SetDmxValue(newValue);

    return kVCOMError_NoError;    
}

VectorworksMVR::VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfMacroVisualValueImpl::SetDmxChannel(IGdtfDmxChannelFunction* newValue)
{
    //Check Pointer
    if (!fMacroVisualValue)		return kVCOMError_NotInitialized;

    // Check Arg
    if (!newValue)	return kVCOMError_InvalidArg;

    // Cast
    CGdtfDmxChannelFunctionImpl* channelFuncImplem = static_cast<CGdtfDmxChannelFunctionImpl*>(newValue);
    if (!channelFuncImplem)		return kVCOMError_Failed;

    // Now set
    SceneData::GdtfDmxChannelFunctionPtr gdtfChannFunc = channelFuncImplem->getPointer();
    if (!gdtfChannFunc)		return kVCOMError_Failed;

    fMacroVisualValue->SetChannelFunction (gdtfChannFunc);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfMacroVisualValueImpl::BindToObject(void * objAddr)
{
    // Check if valid
    if (!fMacroVisualValue) return kVCOMError_NotInitialized;

    fMacroVisualValue->SetBind(objAddr);

    return kVCOMError_NoError;
}

void *VCOM_CALLTYPE VectorworksMVR::CGdtfMacroVisualValueImpl::GetBoundObject()
{
    // Check if valid
    if (!fMacroVisualValue) return nullptr;

    return fMacroVisualValue->GetBind();
}

void VectorworksMVR::CGdtfMacroVisualValueImpl::SetPointer(SceneData::GdtfMacroVisualValue * macroVisualValue)
{
    fMacroVisualValue = macroVisualValue;
}

SceneData::GdtfMacroVisualValue * VectorworksMVR::CGdtfMacroVisualValueImpl::GetPointer()
{
    return fMacroVisualValue;
}

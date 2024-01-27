//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfMacroDMXStep.h"
#include "CGdtfMacroDMXValue.h"
#include "CGdtfDmxChannel.h"


VectorworksMVR::CGdtfMacroDMXStepImpl::CGdtfMacroDMXStepImpl()
{
}

VectorworksMVR::CGdtfMacroDMXStepImpl::~CGdtfMacroDMXStepImpl()
{
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMacroDMXStepImpl::GetDuration(double& outDur)
{
    // Check Data
    if (!fMacroDMXStep) return kVCOMError_NotInitialized;

    outDur = fMacroDMXStep->GetDuration();

    return kVCOMError_NoError;
}

void VectorworksMVR::CGdtfMacroDMXStepImpl::SetPointer(SceneData::GdtfMacroDMXStep * macroStep)
{
    fMacroDMXStep = macroStep;
}

SceneData::GdtfMacroDMXStep * VectorworksMVR::CGdtfMacroDMXStepImpl::GetPointer()
{
    return fMacroDMXStep;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMacroDMXStepImpl::GetDMXValueCount(size_t &count)
{
    if (!fMacroDMXStep) { return kVCOMError_NotInitialized; }

    count = fMacroDMXStep->GetDMXValueArray().size();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMacroDMXStepImpl::GetDMXValueAt(size_t at, IGdtfMacroDMXValue ** outVal)
{
    // Check if Set
    if (!fMacroDMXStep) { return kVCOMError_NotInitialized; }

    // Check if no Overflow
    if (at >= fMacroDMXStep->GetDMXValueArray().size()) { return kVCOMError_OutOfBounds; }

    SceneData::GdtfMacroDMXValue* gdtfDmxValue = fMacroDMXStep->GetDMXValueArray()[at];
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfMacroDMXValueImpl* pDmxVal = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfMacroDMXValue, (IVWUnknown**)& pDmxVal)))
    {
        // Check Casting
        CGdtfMacroDMXValueImpl* pResultInterface = static_cast<CGdtfMacroDMXValueImpl* >(pDmxVal);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfDmxValue);
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
    *outVal = pDmxVal;

    return kVCOMError_NoError;
}
                                                                 
VectorworksMVR::VCOMError VectorworksMVR::CGdtfMacroDMXStepImpl::CreateDMXValue(DmxValue dmxVal, IGdtfDmxChannel* dmxChannel, IGdtfMacroDMXValue** outVal)
{
    // Check if Set
    if (!fMacroDMXStep) { return kVCOMError_NotInitialized; }

    // Cast the DmxChannel
        
    if (!dmxChannel) { return kVCOMError_InvalidArg; }
        
    CGdtfDmxChannelImpl* DMXChannelImpl = static_cast<CGdtfDmxChannelImpl*>(dmxChannel);
    if (!DMXChannelImpl) { return kVCOMError_Failed; }

    // Set Object
    SceneData::GdtfDmxChannel* gdtfDMXChannel = DMXChannelImpl->getPointer();
    if (!gdtfDMXChannel) { return kVCOMError_Failed; }    
    //---------------------------------------------------------------------------

    SceneData::GdtfMacroDMXValue* gdtfDmxValue = fMacroDMXStep->AddDmxValue(dmxVal, gdtfDMXChannel);

    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfMacroDMXValueImpl* pDmxVal = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfMacroDMXValue, (IVWUnknown**)& pDmxVal)))
    {
        // Check Casting
        CGdtfMacroDMXValueImpl* pResultInterface = static_cast<CGdtfMacroDMXValueImpl*>(pDmxVal);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfDmxValue);
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
    *outVal = pDmxVal;

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMacroDMXStepImpl::BindToObject(void * objAddr)
{
    // Check if valid
    if (!fMacroDMXStep) return kVCOMError_NotInitialized;

    fMacroDMXStep->SetBind(objAddr);

    return kVCOMError_NoError;
}

void *VCOM_CALLTYPE VectorworksMVR::CGdtfMacroDMXStepImpl::GetBoundObject()
{
    // Check if valid
    if (!fMacroDMXStep) return nullptr;

    return fMacroDMXStep->GetBind();
}

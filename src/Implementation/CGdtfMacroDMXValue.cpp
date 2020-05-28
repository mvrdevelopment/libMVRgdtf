//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfMacroDMXValue.h"
#include "CGdtfDmxChannel.h"

VectorworksMVR::CGdtfMacroDMXValueImpl::CGdtfMacroDMXValueImpl()
{
}

VectorworksMVR::CGdtfMacroDMXValueImpl::~CGdtfMacroDMXValueImpl()
{
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMacroDMXValueImpl::BindToObject(void * objAddr)
{    
    // Check if valid
    if (!fMacroDMXValue ) return kVCOMError_NotInitialized;

    fMacroDMXValue->SetBind(objAddr);

    return kVCOMError_NoError;
}


void* VectorworksMVR::CGdtfMacroDMXValueImpl::GetBoundObject()
{
    // Check if valid
    if (!fMacroDMXValue) return nullptr;

    return fMacroDMXValue->GetBind();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMacroDMXValueImpl::GetDmxValue(DmxValue& outValue)
{
    // Check Data
    if (!fMacroDMXValue) return kVCOMError_NotInitialized;

    outValue = fMacroDMXValue->GetValue();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfMacroDMXValueImpl::GetDmxChannel(IGdtfDmxChannel** outValue)
{
    // Check Data
    if (!fMacroDMXValue) return kVCOMError_NotInitialized;

    SceneData::GdtfDmxChannel* gdtfDmxChannel = fMacroDMXValue->GetDMXChannel();
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfDmxChannelImpl* pDmxChannel = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDmxChannel, (IVWUnknown**)& pDmxChannel)))
    {
        // Check Casting
        CGdtfDmxChannelImpl* pResultInterface = static_cast<CGdtfDmxChannelImpl* >(pDmxChannel);
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
    *outValue = pDmxChannel;

    return kVCOMError_NoError;
}

void VectorworksMVR::CGdtfMacroDMXValueImpl::SetPointer(SceneData::GdtfMacroDMXValue * MacroDMXValue)
{
    fMacroDMXValue = MacroDMXValue;
}

SceneData::GdtfMacroDMXValue * VectorworksMVR::CGdtfMacroDMXValueImpl::GetPointer()
{
    return fMacroDMXValue;
}

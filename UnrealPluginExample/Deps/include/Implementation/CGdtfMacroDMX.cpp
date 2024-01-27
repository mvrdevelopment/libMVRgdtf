//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfBreak.h"
#include "CGdtfMacroDMX.h"
#include "CGdtfMacroDMXStep.h"

VectorworksMVR::CGdtfMacroDMXImpl::CGdtfMacroDMXImpl()
{
}

VectorworksMVR::CGdtfMacroDMXImpl::~CGdtfMacroDMXImpl()
{
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMacroDMXImpl::GetStepCount(size_t& count)
{
    if (!fMacroDMX) { return kVCOMError_NotInitialized; }

    count = fMacroDMX->GetStepArray().size();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMacroDMXImpl::CreateStep(double& macroDuration, IGdtfMacroDMXStep ** outStep)
{
    // Check if Set
    if (!fMacroDMX) { return kVCOMError_NotInitialized; }
        
    SceneData::GdtfMacroDMXStep* gdtfMacroStep = fMacroDMX->AddDmxStep(macroDuration);
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfMacroDMXStepImpl* pMAcroStepObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfMacroDMXStep, (IVWUnknown**)& pMAcroStepObj)))
    {
        // Check Casting
        CGdtfMacroDMXStepImpl* pResultInterface = static_cast<CGdtfMacroDMXStepImpl* >(pMAcroStepObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfMacroStep);
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
    if (*outStep)
    {
        (*outStep)->Release();
        *outStep = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *outStep = pMAcroStepObj;

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMacroDMXImpl::BindToObject(void * objAddr)
{
    // Check if valid
    if (!fMacroDMX) return kVCOMError_NotInitialized;

    fMacroDMX->SetBind(objAddr);

    return kVCOMError_NoError;
}

void* VectorworksMVR::CGdtfMacroDMXImpl::GetBoundObject()
{
    // Check if valid
    if (!fMacroDMX) return nullptr;

    return fMacroDMX->GetBind();
}

void VectorworksMVR::CGdtfMacroDMXImpl::SetPointer(SceneData::GdtfMacroDMX * macroDMX)
{
    fMacroDMX = macroDMX;
}

SceneData::GdtfMacroDMX* VectorworksMVR::CGdtfMacroDMXImpl::GetPointer()
{
    return fMacroDMX;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMacroDMXImpl::GetStepAt(size_t at, IGdtfMacroDMXStep** outStep)
{
    // Check if Set
    if (!fMacroDMX) { return kVCOMError_NotInitialized; }

    // Check if no Overflow
    if (at >= fMacroDMX->GetStepArray().size()) { return kVCOMError_OutOfBounds; }
    
    SceneData::GdtfMacroDMXStep* gdtfMacroStep = fMacroDMX->GetStepArray()[at];

    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfMacroDMXStepImpl* pMacroObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfMacroDMXStep, (IVWUnknown**)& pMacroObj)))
    {
        // Check Casting
        CGdtfMacroDMXStepImpl* pResultInterface = static_cast<CGdtfMacroDMXStepImpl* >(pMacroObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfMacroStep);
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
    if (*outStep)
    {
        (*outStep)->Release();
        *outStep = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *outStep = pMacroObj;

    return kVCOMError_NoError;
}

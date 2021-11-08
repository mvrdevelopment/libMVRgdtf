//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfDmxProfile.h"
#include "CGdtfPoint.h"

VectorworksMVR::CGdtfDMXProfileImpl::CGdtfDMXProfileImpl()
{
}

VectorworksMVR::CGdtfDMXProfileImpl::~CGdtfDMXProfileImpl()
{
    fDMXProfile = nullptr;
}

MvrString VectorworksMVR::CGdtfDMXProfileImpl::GetName()
{
    if(!fDMXProfile) {return "";}
	
    return fDMXProfile->GetName().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDMXProfileImpl::SetName(MvrString name)
{
	if(!fDMXProfile) {return kVCOMError_NotInitialized;}
	
	TXString vwName (name);
	fDMXProfile->SetName(vwName);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDMXProfileImpl::GetPointCount(size_t& count)
{
    if (!fDMXProfile) { return kVCOMError_NotInitialized; }

    count = fDMXProfile->GetPointArray().size();

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfDMXProfileImpl::GetPointAt(size_t at, IGdtfPoint** point)
{
    // Check if Set
    if (!fDMXProfile) { return kVCOMError_NotInitialized; }

    // Check if no Overflow
    if (at >= fDMXProfile->GetPointArray().size()) { return kVCOMError_OutOfBounds; }


    SceneData::GdtfPoint* gdtfPoint = fDMXProfile->GetPointArray()[at];
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfPointImpl* pPointObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfPoint, (IVWUnknown**)& pPointObj)))
    {
        // Check Casting
        CGdtfPointImpl* pResultInterface = static_cast<CGdtfPointImpl*>(pPointObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfPoint);
        }
        else
        {
            pResultInterface->Release();
            pResultInterface = nullptr;
            return kVCOMError_NoInterface;
        }
    }

    //---------------------------------------------------------------------------
    // Check Incoming Object
    if (*point)
    {
        (*point)->Release();
        *point = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *point = pPointObj;

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfDMXProfileImpl::CreatePoint(double DMXPercentage, double CFC3, double CFC2, double CFC1, double CFC0, IGdtfPoint** point)
{
    // Check if Set
    if (!fDMXProfile) { return kVCOMError_NotInitialized; }


    SceneData::GdtfPoint* gdtfPoint = fDMXProfile->AddPoint(DMXPercentage, CFC3, CFC2, CFC1, CFC0);

    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfPointImpl* pPointObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfPoint, (IVWUnknown**)& pPointObj)))
    {
        // Check Casting
        CGdtfPointImpl* pResultInterface = static_cast<CGdtfPointImpl*>(pPointObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfPoint);
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
    if (*point)
    {
        (*point)->Release();
        *point = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *point = pPointObj;

    return kVCOMError_NoError;
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

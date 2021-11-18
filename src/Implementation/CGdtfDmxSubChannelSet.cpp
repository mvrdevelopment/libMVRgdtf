//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "Include/VectorworksMVR.h"
#include "CGdtfDmxSubChannelSet.h"
#include "CGdtfSubPhysicalUnit.h"
#include "CGdtfDmxProfile.h"

using namespace VectorworksMVR::Filing;

VectorworksMVR::CGdtfDmxSubChannelSetImpl::CGdtfDmxSubChannelSetImpl()
{
	fSubChannelSet = nullptr;
};

VectorworksMVR::CGdtfDmxSubChannelSetImpl::~CGdtfDmxSubChannelSetImpl()
{
    
};

MvrString VectorworksMVR::CGdtfDmxSubChannelSetImpl::GetName()
{
	// Check Pointer
	if ( ! fSubChannelSet) { return ""; }
    
    return fSubChannelSet->GetName().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxSubChannelSetImpl::GetPhysicalFrom(double& from)
{
	// Check Pointer
	if ( ! fSubChannelSet) { return kVCOMError_NotInitialized; }
	
    from = fSubChannelSet->GetPhysicalFrom();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxSubChannelSetImpl::GetPhysicalTo(double& to)
{
	// Check Pointer
	if ( ! fSubChannelSet) { return kVCOMError_NotInitialized; }
	
    to = fSubChannelSet->GetPhysicalTo();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxSubChannelSetImpl::GetSubPhysicalUnit(IGdtfSubPhysicalUnit** subPhysicalUnit)
{
	// Check Pointer
    if (!fSubChannelSet) { return kVCOMError_NotInitialized; }

    //---------------------------------------------------------------------------
    // Initialize Object
    SceneData::GdtfSubPhysicalUnit* gdtfSubPhysicalUnit = fSubChannelSet->GetSubPhysicalUnit();
    if (!gdtfSubPhysicalUnit) { return kVCOMError_NotSet; }

    CGdtfSubPhysicalUnitImpl* pSubPhysicalUnitObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfSubPhysicalUnit, (IVWUnknown**)& pSubPhysicalUnitObj)))
    {
        // Check Casting
        CGdtfSubPhysicalUnitImpl* pResultInterface = static_cast<CGdtfSubPhysicalUnitImpl*>(pSubPhysicalUnitObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfSubPhysicalUnit);
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
    if (*subPhysicalUnit)
    {
        (*subPhysicalUnit)->Release();
        *subPhysicalUnit = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *subPhysicalUnit = pSubPhysicalUnitObj;

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxSubChannelSetImpl::GetDMXProfile(IGdtfDMXProfile** dmxProfile)
{
	// Check Pointer
    if (!fSubChannelSet) { return kVCOMError_NotInitialized; }

    //---------------------------------------------------------------------------
    // Initialize Object
    SceneData::GdtfDMXProfile* gdtfDMXProfile = fSubChannelSet->GetDMXProfile();
    if (!gdtfDMXProfile) { return kVCOMError_NotSet; }

    CGdtfDMXProfileImpl* pDMXProfileObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDMXProfile, (IVWUnknown**)& pDMXProfileObj)))
    {
        // Check Casting
        CGdtfDMXProfileImpl* pResultInterface = static_cast<CGdtfDMXProfileImpl*>(pDMXProfileObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfDMXProfile);
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
    if (*dmxProfile)
    {
        (*dmxProfile)->Release();
        *dmxProfile = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *dmxProfile = pDMXProfileObj;

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxSubChannelSetImpl::SetName(MvrString name)
{
	if( ! fSubChannelSet) return kVCOMError_NotInitialized;	
	
    fSubChannelSet->SetName(name);

   	return kVCOMError_NoError;    
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxSubChannelSetImpl::SetPhysicalFrom(double from)
{
	// Check Pointer
	if ( ! fSubChannelSet) { return kVCOMError_NotInitialized; }
	
	fSubChannelSet->SetPhysicalFrom(from);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxSubChannelSetImpl::SetPhysicalTo(double to)
{
	// Check Pointer
	if ( ! fSubChannelSet) { return kVCOMError_NotInitialized; }
	
	fSubChannelSet->SetPhysicalTo(to);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxSubChannelSetImpl::SetSubPhysicalUnit(IGdtfSubPhysicalUnit* subPhysicalUnit)
{
	if (!fSubChannelSet) { return kVCOMError_NotInitialized; }
    if (!subPhysicalUnit) { return kVCOMError_InvalidArg; }

    // Cast
    CGdtfSubPhysicalUnitImpl* subPhysicalUnitImpl = static_cast<CGdtfSubPhysicalUnitImpl*>(subPhysicalUnit);
    if (!subPhysicalUnitImpl) { return kVCOMError_Failed; }

    // Set Object
    SceneData::GdtfSubPhysicalUnit* gdtfSubPhysicalUnit = subPhysicalUnitImpl->GetPointer();
    if (!gdtfSubPhysicalUnit) { return kVCOMError_Failed; }

    fSubChannelSet->SetSubPhysicalUnit(gdtfSubPhysicalUnit);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxSubChannelSetImpl::SetDMXProfile(IGdtfDMXProfile* dmxProfile)
{
	if (!fSubChannelSet) { return kVCOMError_NotInitialized; }
    if (!dmxProfile) { return kVCOMError_InvalidArg; }

    // Cast
    CGdtfDMXProfileImpl* dmxProfileImpl = static_cast<CGdtfDMXProfileImpl*>(dmxProfile);
    if (!dmxProfileImpl) { return kVCOMError_Failed; }

    // Set Object
    SceneData::GdtfDMXProfile* gdtfDMXProfile = dmxProfileImpl->GetPointer();
    if (!gdtfDMXProfile) { return kVCOMError_Failed; }

    fSubChannelSet->SetDMXProfile(gdtfDMXProfile);

    return kVCOMError_NoError;
}

void VectorworksMVR::CGdtfDmxSubChannelSetImpl::SetPointer(SceneData::GdtfDmxSubChannelSet* subChannelSet)
{
    fSubChannelSet = subChannelSet;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxSubChannelSetImpl::BindToObject(void* objAddr)
{
	// Check if valid
	if(!fSubChannelSet) return kVCOMError_NotInitialized;
	
	fSubChannelSet->SetBind(objAddr);
	
	return kVCOMError_NoError;
}

void* VectorworksMVR::CGdtfDmxSubChannelSetImpl::GetBoundObject()
{
	// Check if valid
	if(!fSubChannelSet) return nullptr;
	
	return fSubChannelSet->GetBind();
}

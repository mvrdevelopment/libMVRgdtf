//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "Include/VectorworksMVR.h"
#include "CGdtfDmxChannelSet.h"
#include "CGdtfWheelSlot.h"

using namespace VectorworksMVR::Filing;

VectorworksMVR::CGdtfDmxChannelSetImpl::CGdtfDmxChannelSetImpl()
{
	fChannelSet = nullptr;
};

VectorworksMVR::CGdtfDmxChannelSetImpl::~CGdtfDmxChannelSetImpl()
{
    
};

MvrString VectorworksMVR::CGdtfDmxChannelSetImpl::GetName()
{
	// Check Pointer
	if ( ! fChannelSet) { return ""; }
    
    return fChannelSet->GetName().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelSetImpl::GetDmxStartAddress(DmxValue &address)
{
	// Check Pointer
	if ( ! fChannelSet) { return kVCOMError_NotInitialized; }
	
    address = fChannelSet->GetDmxStart();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelSetImpl::GetDmxEndAddress(DmxValue &address)
{
	// Check Pointer
	if ( ! fChannelSet) { return kVCOMError_NotInitialized; }
	
    address = fChannelSet->GetDmxEnd();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelSetImpl::GetPhysicalStart(double &start)
{
	// Check Pointer
	if ( ! fChannelSet) { return kVCOMError_NotInitialized; }
	
    start = fChannelSet->GetPhysicalStart();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelSetImpl::GetPhysicalEnd(double &end)
{
	// Check Pointer
	if ( ! fChannelSet) { return kVCOMError_NotInitialized; }
	
    end = fChannelSet->GetPhysicalEnd();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelSetImpl::GetWheelSlot(Sint32& WheelSlotIdx)
{
	// Check Pointer
	if ( ! fChannelSet) { return kVCOMError_NotInitialized; }
	
	WheelSlotIdx = fChannelSet->GetWheelSlot();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelSetImpl::GetUsePhysicalFromParent(bool& outUse)
{
	// Check Pointer
	if ( ! fChannelSet) { return kVCOMError_NotInitialized; }
	
	outUse = fChannelSet->GetUsePhysicalFromParent();
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelSetImpl::SetPhysicalStart(double start)
{
	// Check Pointer
	if ( ! fChannelSet) { return kVCOMError_NotInitialized; }
	
	fChannelSet->SetPhysicalStart(start);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelSetImpl::SetPhysicalEnd(double end)
{
	// Check Pointer
	if ( ! fChannelSet) { return kVCOMError_NotInitialized; }
	
	fChannelSet->SetPhysicalEnd(end);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelSetImpl::SetWheelSlot(Sint32 wheelSlotIdx)
{
	// Check Pointer
	if ( ! fChannelSet) { return kVCOMError_NotInitialized; }
	
	fChannelSet->SetWheelSlot(wheelSlotIdx);
	
	return kVCOMError_NoError;
}

void VectorworksMVR::CGdtfDmxChannelSetImpl::setPointer(SceneData::GdtfDmxChannelSet *channelSet)
{
    fChannelSet = channelSet;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelSetImpl::BindToObject(void* objAddr)
{
	// Check if valid
	if(!fChannelSet) return kVCOMError_NotInitialized;
	
	fChannelSet->SetBind(objAddr);
	
	return kVCOMError_NoError;
}

void* VectorworksMVR::CGdtfDmxChannelSetImpl::GetBoundObject()
{
	// Check if valid
	if(!fChannelSet) return nullptr;
	
	return fChannelSet->GetBind();
}

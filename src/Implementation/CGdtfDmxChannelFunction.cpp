//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfDmxChannelFunction.h"
#include "CGdtfAttribute.h"
#include "CGdtfWheel.h"
#include "CGdtfDmxChannelSet.h"
#include "CGdtfDmxSubChannelSet.h"
#include "CGdtfPhysicalEmitter.h"
#include "CGdtfDmxChannel.h"
#include "CGdtfDmxLogicalChannel.h"
#include "CGdtfFilter.h"
#include "CGdtfColorSpace.h"
#include "CGdtfGamut.h"
#include "CGdtfDmxProfile.h"
#include "CGdtfSubPhysicalUnit.h"

using namespace VectorworksMVR::Filing;

VectorworksMVR::CGdtfDmxChannelFunctionImpl::CGdtfDmxChannelFunctionImpl()
{
	fFunction = nullptr;
};

VectorworksMVR::CGdtfDmxChannelFunctionImpl::~CGdtfDmxChannelFunctionImpl()
{
    
};

MvrString VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetName()
{
	// Check Pointer
	if ( ! fFunction) { return ""; }
	
    return fFunction->GetName().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetAttribute(VectorworksMVR::IGdtfAttribute** attribute)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
    //---------------------------------------------------------------------------
    // Initialize Object
	SceneData::GdtfAttribute*	gdtfAttribute = fFunction->GetAttribute();
	if ( ! gdtfAttribute)	{ return kVCOMError_NotSet; }
	
    CGdtfAttributeImpl*			pAttributeObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfAttribute, (IVWUnknown**) & pAttributeObj)))
    {
        // Check Casting
        CGdtfAttributeImpl* pResultInterface = static_cast<CGdtfAttributeImpl* >(pAttributeObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfAttribute);
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
    if (*attribute)
    {
        (*attribute)->Release();
        *attribute		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *attribute	= pAttributeObj;
    
    return kVCOMError_NoError;
}

MvrString VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetOriginalAttribute()
{
	// Check Pointer
	if ( ! fFunction) { return ""; }
	
	//---------------------------------------------------------------------------
	// Initialize Object
	return fFunction->GetOriginalAttribute().GetCharPtr();

}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetDefaultValue(DmxValue &defaultValue)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
    defaultValue = fFunction->GetDefaultValue();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetStartAddress(DmxValue& address)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
    address = fFunction->GetStartAdress();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetEndAddress(DmxValue& address)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
    address = fFunction->GetEndAdress();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetPhysicalStart(double &start)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
	start = fFunction->GetPhysicalStart();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetPhysicalEnd(double &end)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
    end = fFunction->GetPhysicalEnd();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetRealFade(double &fade)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
    fade = fFunction->GetRealFade();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetRealAcceleration(double& value)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
    value = fFunction->GetRealAcceleration();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetOnWheel(VectorworksMVR::IGdtfWheel **wheel)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfWheelImpl*			pWheelObj = nullptr;
	SceneData::GdtfWheelPtr gdtfWheel = fFunction->GetOnWheel();
	if ( ! gdtfWheel)	{ return kVCOMError_NotSet; }
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfWheel, (IVWUnknown**) & pWheelObj)))
    {
        // Check Casting
        CGdtfWheelImpl* pResultInterface = static_cast<CGdtfWheelImpl* >(pWheelObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfWheel);
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
    if (*wheel)
    {
        (*wheel)->Release();
        *wheel		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *wheel	= pWheelObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetEmitter(IGdtfPhysicalEmitter ** emitter)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfPhysicalEmitterImpl*			pEmitter= nullptr;
	SceneData::GdtfPhysicalEmitter* gdtfEmitter = fFunction->GetEmitter();
	if ( ! gdtfEmitter)	{ return kVCOMError_NotSet; }
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfPhysicalEmitter, (IVWUnknown**) & pEmitter)))
    {
        // Check Casting
        CGdtfPhysicalEmitterImpl* pResultInterface = static_cast<CGdtfPhysicalEmitterImpl* >(pEmitter);
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
    if (*emitter)
    {
        (*emitter)->Release();
        *emitter		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *emitter	= pEmitter;
    
    return kVCOMError_NoError;    
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetFilter(IGdtfFilter** outVal) 
{
    // Check Pointer
    if (!fFunction) { return kVCOMError_NotInitialized; }

    //---------------------------------------------------------------------------
    // Initialize Object
    SceneData::GdtfFilter*	gdtfFilter = fFunction->GetFilter();
    if (!gdtfFilter) { return kVCOMError_NotSet; }

    CGdtfFilterImpl*		pFilterObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfFilter, (IVWUnknown**)& pFilterObj)))
    {
        // Check Casting
        CGdtfFilterImpl* pResultInterface = static_cast<CGdtfFilterImpl*>(pFilterObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfFilter);
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
    if (*outVal)
    {
        (*outVal)->Release();
        *outVal = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *outVal = pFilterObj;

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetResolution(GdtfDefines::EGdtfChannelBitResolution & resolution)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
	resolution = fFunction->GetParentDMXChannel()->GetChannelBitResolution();
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetColorSpace(IGdtfColorSpace** colorSpace) 
{
    // Check Pointer
    if (!fFunction) { return kVCOMError_NotInitialized; }

    //---------------------------------------------------------------------------
    // Initialize Object
    SceneData::GdtfColorSpace* gdtfColorSpace = fFunction->GetColorSpace();
    if (!gdtfColorSpace) { return kVCOMError_NotSet; }

    CGdtfColorSpaceImpl* pColorSpaceObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfColorSpace, (IVWUnknown**)& pColorSpaceObj)))
    {
        // Check Casting
        CGdtfColorSpaceImpl* pResultInterface = static_cast<CGdtfColorSpaceImpl*>(pColorSpaceObj);
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
    // Check Incoming Object
    if (*colorSpace)
    {
        (*colorSpace)->Release();
        *colorSpace = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *colorSpace = pColorSpaceObj;

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetGamut(IGdtfGamut** gamut) 
{
    // Check Pointer
    if (!fFunction) { return kVCOMError_NotInitialized; }

    //---------------------------------------------------------------------------
    // Initialize Object
    SceneData::GdtfGamut* gdtfGamut = fFunction->GetGamut();
    if (!gdtfGamut) { return kVCOMError_NotSet; }

    CGdtfGamutImpl* pGamutObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfGamut, (IVWUnknown**)& pGamutObj)))
    {
        // Check Casting
        CGdtfGamutImpl* pResultInterface = static_cast<CGdtfGamutImpl*>(pGamutObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfGamut);
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
    if (*gamut)
    {
        (*gamut)->Release();
        *gamut = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *gamut = pGamutObj;

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetDMXProfile(IGdtfDMXProfile** dmxProfile) 
{
    // Check Pointer
    if (!fFunction) { return kVCOMError_NotInitialized; }

    //---------------------------------------------------------------------------
    // Initialize Object
    SceneData::GdtfDMXProfile* gdtfDMXProfile = fFunction->GetDMXProfile();
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

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetMin(double& min)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
	min = fFunction->GetMin();
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetMax(double& max)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
	max = fFunction->GetMax();
	
	return kVCOMError_NoError;
}

MvrString VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetCustomName()
{
	// Check Pointer
	if ( ! fFunction) { return ""; }
	
    return fFunction->GetCustomName().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::SetAttribute(IGdtfAttribute* attribute)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	if ( ! attribute) { return kVCOMError_InvalidArg; }
	
	// Cast
	CGdtfAttributeImpl* subAttrImpl = static_cast<CGdtfAttributeImpl*>(attribute);
	if ( ! subAttrImpl) { return kVCOMError_Failed; }
	
	//
	SceneData::GdtfAttributePtr ptr = nullptr;
	ptr = subAttrImpl->GetPointer();
	if( ! ptr) { return kVCOMError_Failed; }
	
	fFunction->SetAttribute(ptr);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::SetOriginalAttribute(MvrString attr)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	

	TXString vwAttr ( attr );
	fFunction->SetOriginalAttribute(vwAttr);
	
	return kVCOMError_NoError;
	
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::SetDefaultValue(DmxValue defaultValue)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
	fFunction->SetDefaultValue(defaultValue);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::SetStartAddress(DmxValue address)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
	fFunction->SetStartAddress(address);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::SetPhysicalStart(double start)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
	fFunction->SetPhysicalStart(start);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::SetPhysicalEnd(double end)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
	fFunction->SetPhysicalEnd(end);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::SetRealFade(double fade)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
	fFunction->SetRealFade(fade);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::SetRealAcceleration(double value)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
    fFunction->SetRealAcceleration(value);
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::SetOnWheel(IGdtfWheel* wheel)
{
	// Check Pointer
	if ( ! fFunction)	{ return kVCOMError_NotInitialized; }
	if ( ! wheel)		{ return kVCOMError_InvalidArg; }
	
	CGdtfWheelImpl* wheelImpl = static_cast<CGdtfWheelImpl*>(wheel);
	if ( ! wheelImpl)	{ return kVCOMError_Failed; }
	
	SceneData::GdtfWheelPtr scWheel = wheelImpl->GetPointer();
	if ( ! scWheel)		{ return kVCOMError_Failed; }
	
	fFunction->SetWheel(scWheel);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::SetEmitter(IGdtfPhysicalEmitter * emitter)
{
	// Check Pointer
	if ( ! fFunction)	{ return kVCOMError_NotInitialized; }
	if ( ! emitter)		{ return kVCOMError_InvalidArg; }
	
	CGdtfPhysicalEmitterImpl* emitterImpl = static_cast<CGdtfPhysicalEmitterImpl*>(emitter);
	if ( ! emitterImpl)	{ return kVCOMError_Failed; }
	
	SceneData::GdtfPhysicalEmitter* gdtfEmitter = emitterImpl->GetPointer();
	if ( ! gdtfEmitter)		{ return kVCOMError_Failed; }
	
	fFunction->SetEmitter (gdtfEmitter);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::SetFilter (IGdtfFilter * newFilter)
{
    if (!fFunction) { return kVCOMError_NotInitialized; }
    if (!newFilter) { return kVCOMError_InvalidArg; }

    // Cast
    CGdtfFilterImpl* FilterImpl = static_cast<CGdtfFilterImpl*>(newFilter);
    if (!FilterImpl) { return kVCOMError_Failed; }

    // Set Object
    SceneData::GdtfFilter* gdtfFilter = FilterImpl->GetPointer();
    if (!gdtfFilter) { return kVCOMError_Failed; }

    fFunction->SetFilter (gdtfFilter);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::SetColorSpace(IGdtfColorSpace* colorSpace)
{
    if (!fFunction) { return kVCOMError_NotInitialized; }
    if (!colorSpace) { return kVCOMError_InvalidArg; }

    // Cast
    CGdtfColorSpaceImpl* colorSpaceImpl = static_cast<CGdtfColorSpaceImpl*>(colorSpace);
    if (!colorSpaceImpl) { return kVCOMError_Failed; }

    // Set Object
    SceneData::GdtfColorSpace* gdtfColorSpace = colorSpaceImpl->GetPointer();
    if (!gdtfColorSpace) { return kVCOMError_Failed; }

    fFunction->SetColorSpace(gdtfColorSpace);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::SetGamut(IGdtfGamut* gamut)
{
    if (!fFunction) { return kVCOMError_NotInitialized; }
    if (!gamut) { return kVCOMError_InvalidArg; }

    // Cast
    CGdtfGamutImpl* gamutImpl = static_cast<CGdtfGamutImpl*>(gamut);
    if (!gamutImpl) { return kVCOMError_Failed; }

    // Set Object
    SceneData::GdtfGamut* gdtfGamut = gamutImpl->GetPointer();
    if (!gdtfGamut) { return kVCOMError_Failed; }

    fFunction->SetGamut(gdtfGamut);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::SetDMXProfile(IGdtfDMXProfile* dmxProfile)
{
    if (!fFunction) { return kVCOMError_NotInitialized; }
    if (!dmxProfile) { return kVCOMError_InvalidArg; }

    // Cast
    CGdtfDMXProfileImpl* dmxProfileImpl = static_cast<CGdtfDMXProfileImpl*>(dmxProfile);
    if (!dmxProfileImpl) { return kVCOMError_Failed; }

    // Set Object
    SceneData::GdtfDMXProfile* gdtfDMXProfile = dmxProfileImpl->GetPointer();
    if (!gdtfDMXProfile) { return kVCOMError_Failed; }

    fFunction->SetDMXProfile(gdtfDMXProfile);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::SetMin(double min)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
	fFunction->SetMin(min);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::SetMax(double max)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
	fFunction->SetMax(max);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::SetCustomName(MvrString name)
{
  	// Check if valid
	if( ! fFunction) return kVCOMError_NotInitialized;

    fFunction->SetCustomName(name);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetDmxChannelSetCount(size_t &count)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
    count = fFunction->GetChannelSets().size();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetDmxChannelSetAt(size_t at, VectorworksMVR::IGdtfDmxChannelSet **set)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
	// Check bounds
	if ( at >= fFunction->GetChannelSets().size()) { return kVCOMError_OutOfBounds; }
    
    
    //---------------------------------------------------------------------------
    // Initialize Object
	SceneData::GdtfDmxChannelSet*	gdtfChannelSet = fFunction->GetChannelSets()[at];
    CGdtfDmxChannelSetImpl*			pChannelSetObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDmxChannelSet, (IVWUnknown**) & pChannelSetObj)))
    {
        // Check Casting
        CGdtfDmxChannelSetImpl* pResultInterface = static_cast<CGdtfDmxChannelSetImpl* >(pChannelSetObj);
        if (pResultInterface)
        {
            pResultInterface->setPointer(gdtfChannelSet);
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
    if (*set)
    {
        (*set)->Release();
        *set		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *set	= pChannelSetObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::CreateDmxChannelSet(MvrString name, DmxValue start, DmxValue end, IGdtfDmxChannelSet** set)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	TXString vwName (name);
	
	SceneData::GdtfDmxChannelSet*	gdtfChannelSet = fFunction->AddChannelSet(vwName);
	gdtfChannelSet->SetDmxStart(start);
	gdtfChannelSet->SetDmxEnd(end);
	
	// Query Interface
	CGdtfDmxChannelSetImpl*			pChannelSetObj = nullptr;
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDmxChannelSet, (IVWUnknown**) & pChannelSetObj)))
	{
		// Check Casting
		CGdtfDmxChannelSetImpl* pResultInterface = static_cast<CGdtfDmxChannelSetImpl* >(pChannelSetObj);
		if (pResultInterface)
		{
			pResultInterface->setPointer(gdtfChannelSet);
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
	if (*set)
	{
		(*set)->Release();
		*set		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*set	= pChannelSetObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetDmxSubChannelSetCount(size_t &count)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
    count = fFunction->GetSubChannelSets().size();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetDmxSubChannelSetAt(size_t at, VectorworksMVR::IGdtfDmxSubChannelSet** subChannelSet)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
	// Check bounds
	if ( at >= fFunction->GetSubChannelSets().size()) { return kVCOMError_OutOfBounds; }
    
    //---------------------------------------------------------------------------
    // Initialize Object
	SceneData::GdtfDmxSubChannelSet*	gdtfSubChannelSet = fFunction->GetSubChannelSets()[at];
    CGdtfDmxSubChannelSetImpl*			pSubChannelSetObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDmxSubChannelSet, (IVWUnknown**) & pSubChannelSetObj)))
    {
        // Check Casting
        CGdtfDmxSubChannelSetImpl* pResultInterface = static_cast<CGdtfDmxSubChannelSetImpl* >(pSubChannelSetObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfSubChannelSet);
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
    if (*subChannelSet)
    {
        (*subChannelSet)->Release();
        *subChannelSet = NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *subChannelSet = pSubChannelSetObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::CreateDmxSubChannelSet(MvrString name, IGdtfSubPhysicalUnit* subPhysicalUnit, IGdtfDmxSubChannelSet** subChannelSet)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
	CGdtfSubPhysicalUnitImpl* pSubPhysicalUnitObj = static_cast<CGdtfSubPhysicalUnitImpl*>(subPhysicalUnit);
	if(!pSubPhysicalUnitObj) { return kVCOMError_InvalidArg; }

    //---------------------------------------------------------------------------
    // Initialize Object
    SceneData::GdtfSubPhysicalUnit* gdtfSubPhysicalUnit = pSubPhysicalUnitObj->GetPointer();
	SceneData::GdtfDmxSubChannelSet* gdtfSubChannelSet  = fFunction->AddSubChannelSet(gdtfSubPhysicalUnit, name);
    
    CGdtfDmxSubChannelSetImpl* pSubChannelSetObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDmxSubChannelSet, (IVWUnknown**) & pSubChannelSetObj)))
    {
        // Check Casting
        CGdtfDmxSubChannelSetImpl* pResultInterface = static_cast<CGdtfDmxSubChannelSetImpl* >(pSubChannelSetObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfSubChannelSet);
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
    if (*subChannelSet)
    {
        (*subChannelSet)->Release();
        *subChannelSet = NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *subChannelSet = pSubChannelSetObj;
    
    return kVCOMError_NoError;
}

void VectorworksMVR::CGdtfDmxChannelFunctionImpl::setPointer(SceneData::GdtfDmxChannelFunction *function)
{
    fFunction = function;
}

SceneData::GdtfDmxChannelFunction* VectorworksMVR::CGdtfDmxChannelFunctionImpl::getPointer()
{
    return fFunction;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::BindToObject(void* objAddr)
{
	// Check if valid
	if(!fFunction) return kVCOMError_NotInitialized;
	
	fFunction->SetBind(objAddr);
	
	return kVCOMError_NoError;
}

void* VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetBoundObject()
{
	// Check if valid
	if(!fFunction) return nullptr;
	
	return fFunction->GetBind();
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetModeMasterChannel(IGdtfDmxChannel** outChannel, DmxValue& start, DmxValue& end)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	SceneData::GdtfDmxChannelPtr	gdtfChannel = fFunction->GetModeMaster_Channel();
    if( ! gdtfChannel) { return kVCOMError_NotSet;}

    start   = fFunction->GetModeMasterDmxStart();
    end     = fFunction->GetModeMasterDmxEnd();
	
	// Query Interface
	CGdtfDmxChannelImpl*			pChannelImpl = nullptr;
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDmxChannel, (IVWUnknown**) & pChannelImpl)))
	{
		// Check Casting
		CGdtfDmxChannelImpl* pResultInterface = static_cast<CGdtfDmxChannelImpl* >(pChannelImpl);
		if (pResultInterface)
		{
			pResultInterface->setPointer(gdtfChannel);
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
	if (*outChannel)
	{
		(*outChannel)->Release();
		*outChannel		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outChannel	= pChannelImpl;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetModeMasterFunction(IGdtfDmxChannelFunction** outFunction, DmxValue& start, DmxValue& end)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	SceneData::GdtfDmxChannelFunctionPtr	gdtfFunction = fFunction->GetModeMaster_Function();
    if( ! gdtfFunction) { return kVCOMError_NotSet;}

    start   = fFunction->GetModeMasterDmxStart();
    end     = fFunction->GetModeMasterDmxEnd();
	
	// Query Interface
	CGdtfDmxChannelFunctionImpl*			pFunctionImpl = nullptr;
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDmxChannelFunction, (IVWUnknown**) & pFunctionImpl)))
	{
		// Check Casting
		CGdtfDmxChannelFunctionImpl* pResultInterface = static_cast<CGdtfDmxChannelFunctionImpl* >(pFunctionImpl);
		if (pResultInterface)
		{
			pResultInterface->setPointer(gdtfFunction);
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
	if (*outFunction)
	{
		(*outFunction)->Release();
		*outFunction		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outFunction	= pFunctionImpl;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::SetModeMasterChannel(IGdtfDmxChannel* channel, DmxValue start, DmxValue end)
{
	// Check Pointer
	if ( ! fFunction)	{ return kVCOMError_NotInitialized; }
	if ( ! channel)		{ return kVCOMError_InvalidArg; }
	
	CGdtfDmxChannelImpl* channelImpl = static_cast<CGdtfDmxChannelImpl*>(channel);
	if ( ! channelImpl)	{ return kVCOMError_Failed; }
	
	SceneData::GdtfDmxChannelPtr scChannel = channelImpl->getPointer();
	if ( ! scChannel)		{ return kVCOMError_Failed; }
	
	fFunction->SetModeMaster_Channel(scChannel);
    fFunction->SetModeMasterDmxStart(start);
    fFunction->SetModeMasterDmxEnd(end);

	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::SetModeMasterFunction(IGdtfDmxChannelFunction* function, DmxValue start, DmxValue end)
{
	// Check Pointer
	if ( ! fFunction)	{ return kVCOMError_NotInitialized; }
	if ( ! function)		{ return kVCOMError_InvalidArg; }
	
	CGdtfDmxChannelFunctionImpl* functionImpl = static_cast<CGdtfDmxChannelFunctionImpl*>(function);
	if ( ! functionImpl)	{ return kVCOMError_Failed; }
	
	SceneData::GdtfDmxChannelFunctionPtr scFunction = functionImpl->getPointer();
	if ( ! scFunction)		{ return kVCOMError_Failed; }
	
	fFunction->SetModeMaster_Function(scFunction);
    fFunction->SetModeMasterDmxStart(start);
    fFunction->SetModeMasterDmxEnd(end);

	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetParentLogicalChannel(IGdtfDmxLogicalChannel** parent)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
    
    //---------------------------------------------------------------------------
    // Initialize Object
	SceneData::GdtfDmxLogicalChannelPtr	gdtfLogicalChannel = fFunction->GetParentLogicalChannel();
	if ( ! gdtfLogicalChannel)	{ return kVCOMError_Failed; }
	
    CGdtfDmxLogicalChannelImpl*			pLogicalChannel = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDmxLogicalChannel, (IVWUnknown**) & pLogicalChannel)))
    {
        // Check Casting
        CGdtfDmxLogicalChannelImpl* pResultInterface = static_cast<CGdtfDmxLogicalChannelImpl* >(pLogicalChannel);
        if (pResultInterface)
        {
            pResultInterface->setPointer(gdtfLogicalChannel);
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
    if (*parent)
    {
        (*parent)->Release();
        *parent		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *parent	= pLogicalChannel;
    
    return kVCOMError_NoError;
}
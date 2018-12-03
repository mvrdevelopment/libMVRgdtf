//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfDmxChannelFunction.h"
#include "CGdtfAttribute.h"
#include "CGdtfWheel.h"
#include "CGdtfDmxChannelSet.h"
#include "CGdtfPhysicalEmitter.h"
#include "CGdtfDmxChannel.h"

using namespace VectorWorks::Filing;

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
        CGdtfAttributeImpl* pResultInterface = dynamic_cast<CGdtfAttributeImpl* >(pAttributeObj);
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
        CGdtfWheelImpl* pResultInterface = dynamic_cast<CGdtfWheelImpl* >(pWheelObj);
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
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfWheel, (IVWUnknown**) & pEmitter)))
    {
        // Check Casting
        CGdtfPhysicalEmitterImpl* pResultInterface = dynamic_cast<CGdtfPhysicalEmitterImpl* >(pEmitter);
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

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetDMXInvert(EGDTFDmxInvert & dmxInvert)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
    dmxInvert = fFunction->GetDmxInvert();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::GetEncoderInvert(EGDTFEncoderInvert & encoderInvert)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
    encoderInvert = fFunction->GetEncoderInvert();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::SetAttribute(IGdtfAttribute* attribute)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	if ( ! attribute) { return kVCOMError_InvalidArg; }
	
	// Cast
	CGdtfAttributeImpl* subAttrImpl = dynamic_cast<CGdtfAttributeImpl*>(attribute);
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

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::SetStartAddress(DMXAddress address)
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

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::SetOnWheel(IGdtfWheel* wheel)
{
	// Check Pointer
	if ( ! fFunction)	{ return kVCOMError_NotInitialized; }
	if ( ! wheel)		{ return kVCOMError_InvalidArg; }
	
	CGdtfWheelImpl* wheelImpl = dynamic_cast<CGdtfWheelImpl*>(wheel);
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
	
	CGdtfPhysicalEmitterImpl* emitterImpl = dynamic_cast<CGdtfPhysicalEmitterImpl*>(emitter);
	if ( ! emitterImpl)	{ return kVCOMError_Failed; }
	
	SceneData::GdtfPhysicalEmitter* gdtfEmitter = emitterImpl->GetPointer();
	if ( ! gdtfEmitter)		{ return kVCOMError_Failed; }
	
	fFunction->SetEmitter (gdtfEmitter);
	
	return kVCOMError_NoError;}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::SetDMXInvert(EGDTFDmxInvert dmxInvert)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
    fFunction->SetDmxInvert(dmxInvert);
	
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::SetEncoderInvert(EGDTFEncoderInvert encoderInvert)
{
	// Check Pointer
	if ( ! fFunction) { return kVCOMError_NotInitialized; }
	
    fFunction->SetEncoderInvert(encoderInvert);
	
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
        CGdtfDmxChannelSetImpl* pResultInterface = dynamic_cast<CGdtfDmxChannelSetImpl* >(pChannelSetObj);
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

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::CreateDmxChannelSet(MvrString name, DMXAddress start, DMXAddress end, IGdtfDmxChannelSet** set)
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
		CGdtfDmxChannelSetImpl* pResultInterface = dynamic_cast<CGdtfDmxChannelSetImpl* >(pChannelSetObj);
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
		CGdtfDmxChannelImpl* pResultInterface = dynamic_cast<CGdtfDmxChannelImpl* >(pChannelImpl);
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
		CGdtfDmxChannelFunctionImpl* pResultInterface = dynamic_cast<CGdtfDmxChannelFunctionImpl* >(pFunctionImpl);
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
	
	CGdtfDmxChannelImpl* channelImpl = dynamic_cast<CGdtfDmxChannelImpl*>(channel);
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
	
	CGdtfDmxChannelFunctionImpl* functionImpl = dynamic_cast<CGdtfDmxChannelFunctionImpl*>(function);
	if ( ! functionImpl)	{ return kVCOMError_Failed; }
	
	SceneData::GdtfDmxChannelFunctionPtr scFunction = functionImpl->getPointer();
	if ( ! scFunction)		{ return kVCOMError_Failed; }
	
	fFunction->SetModeMaster_Function(scFunction);
    fFunction->SetModeMasterDmxStart(start);
    fFunction->SetModeMasterDmxEnd(end);

	
	return kVCOMError_NoError;
}
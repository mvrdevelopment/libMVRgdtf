//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfDmxLogicalChannel.h"
#include "CGdtfAttribute.h"
#include "CGdtfDmxChannelFunction.h"
#include "CGdtfDmxChannel.h"

using namespace VectorworksMVR::Filing;

VectorworksMVR::CGdtfDmxLogicalChannelImpl::CGdtfDmxLogicalChannelImpl()
{
	fLogicalChannel = nullptr;
};

VectorworksMVR::CGdtfDmxLogicalChannelImpl::~CGdtfDmxLogicalChannelImpl()
{
    
};

MvrString VectorworksMVR::CGdtfDmxLogicalChannelImpl::GetName()
{
	// Check Pointer
	if ( ! fLogicalChannel) { return ""; }
    
    return fLogicalChannel->GetName().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxLogicalChannelImpl::GetAttribute(VectorworksMVR::IGdtfAttribute **attribute)
{
	// Check Pointer
	if ( ! fLogicalChannel) { return kVCOMError_NotInitialized; }
    
    //---------------------------------------------------------------------------
    // Initialize Object
	SceneData::GdtfAttribute*	gdtfAttribute = fLogicalChannel->GetAttribute();
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

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxLogicalChannelImpl::SetAttribute(IGdtfAttribute* attribute)
{
	// Check Pointer
	if ( ! fLogicalChannel) { return kVCOMError_NotInitialized; }
	if ( ! attribute)		{ return kVCOMError_InvalidArg; }
	
	// Cast Interface
	CGdtfAttributeImpl* attrImpl = static_cast<CGdtfAttributeImpl*>(attribute);
	if ( ! attrImpl) { return kVCOMError_Failed; }
	
	// Get Pointer
	SceneData::GdtfAttributePtr attr = attrImpl->GetPointer();
	if ( ! attr) { return kVCOMError_Failed; }
	
	// Set Attr
	fLogicalChannel->SetAttribute(attr);

	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxLogicalChannelImpl::GetDmxSnap(EGdtfDmxSnap &snap)
{
	// Check Pointer
	if ( ! fLogicalChannel) { return kVCOMError_NotInitialized; }
	
    snap = fLogicalChannel->GetDmxSnap();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxLogicalChannelImpl::GetDmxMaster(EGdtfDmxMaster &master)
{
	// Check Pointer
	if ( ! fLogicalChannel) { return kVCOMError_NotInitialized; }
	
    master = fLogicalChannel->GetDmxMaster();
    return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfDmxLogicalChannelImpl::GetMoveInBlackFrames(double & frames)
{
	// Check Pointer
	if ( ! fLogicalChannel) { return kVCOMError_NotInitialized; }
	
    frames = fLogicalChannel->GetMoveInBlackFrames();
    
    return kVCOMError_NoError; 
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfDmxLogicalChannelImpl::GetDmxChangeTimeLimit(double & changeTimeLimit)
{
	// Check Pointer
	if ( ! fLogicalChannel) { return kVCOMError_NotInitialized; }
	
    changeTimeLimit = fLogicalChannel->GetDmxChangeTimeLimit();
    
    return kVCOMError_NoError; 
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxLogicalChannelImpl::SetDmxSnap(EGdtfDmxSnap snap)
{
	// Check Pointer
	if ( ! fLogicalChannel) { return kVCOMError_NotInitialized; }
	
	fLogicalChannel->SetDmxSnap(snap);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxLogicalChannelImpl::SetDmxMaster(EGdtfDmxMaster master)
{
	// Check Pointer
	if ( ! fLogicalChannel) { return kVCOMError_NotInitialized; }
	
	fLogicalChannel->SetDmxMaster(master);
	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfDmxLogicalChannelImpl::SetMoveInBlackFrames(double frames)
{
	// Check Pointer
	if ( ! fLogicalChannel) { return kVCOMError_NotInitialized; }
	
	fLogicalChannel->SetMoveInBlackFrames(frames);
	
	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfDmxLogicalChannelImpl::SetDmxChangeTimeLimit(double changeTimeLimit)
{
	// Check Pointer
	if ( ! fLogicalChannel) { return kVCOMError_NotInitialized; }
	
	fLogicalChannel->SetDmxChangeTimeLimit(changeTimeLimit);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxLogicalChannelImpl::GetDmxFunctionCount(size_t &count)
{
	// Check Pointer
	if ( ! fLogicalChannel) { return kVCOMError_NotInitialized; }
	
    count = fLogicalChannel->GetDmxChannelFunctions().size();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxLogicalChannelImpl::GetDmxFunctionAt(size_t at, VectorworksMVR::IGdtfDmxChannelFunction **function)
{
	// Check Pointer
	if ( ! fLogicalChannel) { return kVCOMError_NotInitialized; }
	
    // Check if no Overflow
    if (at >=  fLogicalChannel->GetDmxChannelFunctions().size()) { return kVCOMError_OutOfBounds;  }
	
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfDmxChannelFunctionImpl*		pFunctionObj = nullptr;
	SceneData::GdtfDmxChannelFunctionPtr	gdtfFunction = fLogicalChannel->GetDmxChannelFunctions()[at];
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDmxChannelFunction, (IVWUnknown**) & pFunctionObj)))
    {
        // Check Casting
        CGdtfDmxChannelFunctionImpl* pResultInterface = static_cast<CGdtfDmxChannelFunctionImpl* >(pFunctionObj);
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
    if (*function)
    {
        (*function)->Release();
        *function		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *function	= pFunctionObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxLogicalChannelImpl::CreateDmxFunction(MvrString name, IGdtfDmxChannelFunction** function)
{
	// Check Pointer
	if ( ! fLogicalChannel) { return kVCOMError_NotInitialized; }
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	TXString vwName (name);
	
	SceneData::GdtfDmxChannelFunctionPtr	gdtfFunction = fLogicalChannel->AddDmxChannelFunction(vwName);
	
	// Query Interface
	CGdtfDmxChannelFunctionImpl*		pFunctionObj = nullptr;
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDmxChannelFunction, (IVWUnknown**) & pFunctionObj)))
	{
		// Check Casting
		CGdtfDmxChannelFunctionImpl* pResultInterface = static_cast<CGdtfDmxChannelFunctionImpl* >(pFunctionObj);
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
	if (*function)
	{
		(*function)->Release();
		*function		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*function	= pFunctionObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxLogicalChannelImpl::GetParentDmxChannel(IGdtfDmxChannel** parent)
{
	// Check Pointer
	if ( ! fLogicalChannel) { return kVCOMError_NotInitialized; }
    
    //---------------------------------------------------------------------------
    // Initialize Object
	SceneData::GdtfDmxChannel*	gdtDmxChannel = fLogicalChannel->GetParentDMXChannel();
	if ( ! gdtDmxChannel)	{ return kVCOMError_Failed; }
	
    CGdtfDmxChannelImpl*			pDmxChannel = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDmxChannel, (IVWUnknown**) & pDmxChannel)))
    {
        // Check Casting
        CGdtfDmxChannelImpl* pResultInterface = static_cast<CGdtfDmxChannelImpl* >(pDmxChannel);
        if (pResultInterface)
        {
            pResultInterface->setPointer(gdtDmxChannel);
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
    *parent	= pDmxChannel;
    
    return kVCOMError_NoError;
}

void VectorworksMVR::CGdtfDmxLogicalChannelImpl::setPointer(SceneData::GdtfDmxLogicalChannel *logicalChannel)
{
    fLogicalChannel = logicalChannel;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxLogicalChannelImpl::BindToObject(void* objAddr)
{
	// Check if valid
	if(!fLogicalChannel) return kVCOMError_NotInitialized;
	
	fLogicalChannel->SetBind(objAddr);
	
	return kVCOMError_NoError;
}

void* VectorworksMVR::CGdtfDmxLogicalChannelImpl::GetBoundObject()
{
	// Check if valid
	if(!fLogicalChannel) return nullptr;
	
	return fLogicalChannel->GetBind();
}

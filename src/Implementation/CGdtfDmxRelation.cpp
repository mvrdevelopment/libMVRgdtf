//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfDmxRelation.h"
#include "CGdtfDmxChannel.h"
#include "CGdtfDmxChannelFunction.h"

using namespace VectorWorks::Filing;

VectorworksMVR::CGdtfDmxRelationImpl::CGdtfDmxRelationImpl()
{
	fRelation = nullptr;
};

VectorworksMVR::CGdtfDmxRelationImpl::~CGdtfDmxRelationImpl()
{
    
};

MvrString VectorworksMVR::CGdtfDmxRelationImpl::GetName()
{
	// Check Pointer
	if ( ! fRelation) { return ""; }
	
	return fRelation->GetName().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxRelationImpl::GetMasterChannel(VectorworksMVR::IGdtfDmxChannel **master)
{
	// Check Pointer
	if ( ! fRelation) { return kVCOMError_NotInitialized; }

    //---------------------------------------------------------------------------
    // Initialize Object
	SceneData::GdtfDmxChannel*	gdtfDmxChannel = fRelation->GetMasterChannel();
	if ( ! gdtfDmxChannel)	{ return kVCOMError_NotSet; }
	
    CGdtfDmxChannelImpl*		pDmxChannelObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDmxChannel, (IVWUnknown**) & pDmxChannelObj)))
    {
        // Check Casting
        CGdtfDmxChannelImpl* pResultInterface = dynamic_cast<CGdtfDmxChannelImpl* >(pDmxChannelObj);
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
    if (*master)
    {
        (*master)->Release();
        *master		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *master		= pDmxChannelObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxRelationImpl::GetSlaveChannel(VectorworksMVR::IGdtfDmxChannelFunction **slave)
{
	// Check Pointer
	if ( ! fRelation) { return kVCOMError_NotInitialized; }
    
    //---------------------------------------------------------------------------
    // Initialize Object
	SceneData::GdtfDmxChannelFunctionPtr	gdtfDmxFunction = fRelation->GetSlaveChannel();
	if ( ! gdtfDmxFunction)	{ return kVCOMError_NotSet; }
	
    CGdtfDmxChannelFunctionImpl*		pDmxFunction = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDmxChannelFunction, (IVWUnknown**) & pDmxFunction)))
    {
        // Check Casting
        CGdtfDmxChannelFunctionImpl* pResultInterface = dynamic_cast<CGdtfDmxChannelFunctionImpl* >(pDmxFunction);
        if (pResultInterface)
        {
            pResultInterface->setPointer(gdtfDmxFunction);
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
    if (*slave)
    {
        (*slave)->Release();
        *slave		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *slave		= pDmxFunction;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxRelationImpl::GetRelationType(EGdtfDmxRelationType &relation)
{
	// Check Pointer
	if ( ! fRelation) { return kVCOMError_NotInitialized; }
	
    relation = fRelation->GetRelationType();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxRelationImpl::GetDmxStart(Sint32 &start)
{
	// Check Pointer
	if ( ! fRelation) { return kVCOMError_NotInitialized; }
	
    start = fRelation->GetDmxStart();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxRelationImpl::GetDmxEnd(Sint32 &end)
{
	// Check Pointer
	if ( ! fRelation) { return kVCOMError_NotInitialized; }
	
    end = fRelation->GetDmxEnd();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxRelationImpl::SetName(MvrString name)
{
	if ( ! fRelation) { return kVCOMError_NotInitialized; }

    fRelation->SetName(name);
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxRelationImpl::SetMasterChannel(IGdtfDmxChannel * newMaster)
{
	if ( ! fRelation) { return kVCOMError_NotInitialized; }
	if ( ! newMaster) { return kVCOMError_InvalidArg; }
        
	// Cast
	CGdtfDmxChannelImpl* dmxChanImpl = dynamic_cast<CGdtfDmxChannelImpl*>(newMaster);
	if ( ! dmxChanImpl)		{ return kVCOMError_Failed; }
	
	// Set Object
	SceneData::GdtfDmxChannel* gdtfDmxChan= dmxChanImpl->getPointer();
	if ( ! gdtfDmxChan) { return kVCOMError_Failed; }    

    fRelation->SetMasterChannel(gdtfDmxChan);
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxRelationImpl::SetSlaveChannel(IGdtfDmxChannelFunction * newSlave)
{
	if ( ! fRelation) { return kVCOMError_NotInitialized; }
    if ( ! newSlave)  { return kVCOMError_InvalidArg; }

	// Cast
	CGdtfDmxChannelFunctionImpl* dmxFunctionImpl = dynamic_cast<CGdtfDmxChannelFunctionImpl*>(newSlave);
	if ( ! dmxFunctionImpl)		{ return kVCOMError_Failed; }
	
	// Set Object
	SceneData::GdtfDmxChannelFunction* gdtfFunc= dmxFunctionImpl->getPointer();
	if ( ! gdtfFunc) { return kVCOMError_Failed; } 
    
    fRelation->SetSlaveChannel(gdtfFunc);
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxRelationImpl::SetRelationType(GdtfDefines::EGdtfDmxRelationType type)
{
	if ( ! fRelation) { return kVCOMError_NotInitialized; }
	
    fRelation->SetRelationType(type);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxRelationImpl::SetDmxStart(DmxValue start)
{
	if ( ! fRelation) { return kVCOMError_NotInitialized; }
	
    fRelation->SetDmxStart(start);
        
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxRelationImpl::SetDmxEnd(DmxValue end)
{
	if ( ! fRelation) { return kVCOMError_NotInitialized; }
	    
    fRelation->SetDmxEnd(end);

    return kVCOMError_NoError;    
}

void VectorworksMVR::CGdtfDmxRelationImpl::setPointer(SceneData::GdtfDmxRelation *relation)
{
    fRelation = relation;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxRelationImpl::BindToObject(void* objAddr)
{
	// Check if valid
	if(!fRelation) return kVCOMError_NotInitialized;
	
	fRelation->SetBind(objAddr);
	
	return kVCOMError_NoError;
}

void* VectorworksMVR::CGdtfDmxRelationImpl::GetBoundObject()
{
	// Check if valid
	if(!fRelation) return nullptr;
	
	return fRelation->GetBind();
}

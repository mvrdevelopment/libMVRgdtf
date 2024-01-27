//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfDmxRelation.h"
#include "CGdtfDmxChannel.h"
#include "CGdtfDmxChannelFunction.h"

using namespace VectorworksMVR::Filing;

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
        CGdtfDmxChannelImpl* pResultInterface = static_cast<CGdtfDmxChannelImpl* >(pDmxChannelObj);
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
        CGdtfDmxChannelFunctionImpl* pResultInterface = static_cast<CGdtfDmxChannelFunctionImpl* >(pDmxFunction);
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

//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfDmxMode.h"
#include "CGdtfGeometry.h"
#include "CGdtfDmxChannel.h"
#include "CGdtfDmxRelation.h"


using namespace VectorWorks::Filing;

VectorworksMVR::CGdtfDmxModeImpl::CGdtfDmxModeImpl()
{
	fDmxMode = nullptr;
};

VectorworksMVR::CGdtfDmxModeImpl::~CGdtfDmxModeImpl()
{
    
};

MvrString VectorworksMVR::CGdtfDmxModeImpl::GetName()
{
	// Check Pointer
	if ( ! fDmxMode) return "";
	
    return fDmxMode->GetModeName().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxModeImpl::GetGeometry(VectorworksMVR::IGdtfGeometry **geo)
{
	// Check Pointer
	if ( ! fDmxMode) return kVCOMError_NotInitialized;

	 //---------------------------------------------------------------------------
    // Initialize Object
	SceneData::GdtfGeometry* gdtfGeo = fDmxMode->GetGeomRef();
	if ( ! gdtfGeo) { return kVCOMError_Failed; }
    
	CGdtfGeometryImpl*		 pGeoObj = nullptr;
    
    // Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfGeometry, (IVWUnknown**) & pGeoObj)))
    {
        // Check Casting
        CGdtfGeometryImpl* pResultInterface = dynamic_cast<CGdtfGeometryImpl*>(pGeoObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfGeo);
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
    if (*geo)
    {
        (*geo)->Release();
        *geo = NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
	*geo = pGeoObj; 
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxModeImpl::SetGeometry(IGdtfGeometry* model)
{
	// Check Pointer
	if ( ! fDmxMode)	{ return kVCOMError_NotInitialized; }
	if ( ! model)		{ return kVCOMError_InvalidArg; }
	
	// Cast
	CGdtfGeometryImpl* geoImpl = dynamic_cast<CGdtfGeometryImpl*>(model);
	if ( ! geoImpl)		{ return kVCOMError_Failed; }
	
	// Set Object
	SceneData::GdtfGeometryPtr scGeo = geoImpl->GetPointer();
	if ( ! scGeo) { return kVCOMError_Failed; }
	
	fDmxMode->SetGeomRef(scGeo);
	
	return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxModeImpl::GetDmxChannelCount(size_t &count)
{
	// Check Pointer
	if ( ! fDmxMode) return kVCOMError_NotInitialized;
	
    count = fDmxMode->GetChannelArray().size();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxModeImpl::GetDmxChannelAt(size_t at, VectorworksMVR::IGdtfDmxChannel **channel)
{
	// Check Pointer
	if ( ! fDmxMode) return kVCOMError_NotInitialized;
	
    // Check if no Overflow
    if (at >=  fDmxMode->GetChannelArray().size()) { return kVCOMError_OutOfBounds;  }

	
    //---------------------------------------------------------------------------
    // Initialize Object
	SceneData::GdtfDmxChannel*	gdtfDmxChannel = fDmxMode->GetChannelArray()[at];
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
    if (*channel)
    {
        (*channel)->Release();
        *channel		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *channel		= pDmxChannelObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxModeImpl::CreateDmxChannel(MvrString name, IGdtfDmxChannel** channel)
{
	// Check Pointer
	if ( ! fDmxMode) return kVCOMError_NotInitialized;
	
	// Check if no Overflow
	TXString vwName (name);
	SceneData::GdtfDmxChannel*	gdtfDmxChannel = fDmxMode->AddChannel(vwName);
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfDmxChannelImpl*		pDmxChannelObj = nullptr;
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
	if (*channel)
	{
		(*channel)->Release();
		*channel		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*channel		= pDmxChannelObj;
	
	return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxModeImpl::GetDmxRelationCount(size_t &count)
{
	// Check Pointer
	if ( ! fDmxMode) return kVCOMError_NotInitialized;
	
    count = fDmxMode->GetDmxRelations().size();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxModeImpl::GetDmxRelationAt(size_t at, VectorworksMVR::IGdtfDmxRelation **relation)
{
	// Check Pointer
	if ( ! fDmxMode) return kVCOMError_NotInitialized;
	
    // Check if no Overflow
    if (at >=  fDmxMode->GetDmxRelations().size()) { return kVCOMError_OutOfBounds;  }
    
    
	
    
    
    //---------------------------------------------------------------------------
    // Initialize Object
	SceneData::GdtfDmxRelation* gdtfDmxRelation = fDmxMode->GetDmxRelations()[at];
    CGdtfDmxRelationImpl*		pDmxRelationObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDmxRelation, (IVWUnknown**) & pDmxRelationObj)))
    {
        // Check Casting
        CGdtfDmxRelationImpl* pResultInterface = dynamic_cast<CGdtfDmxRelationImpl* >(pDmxRelationObj);
        if (pResultInterface)
        {
            pResultInterface->setPointer(gdtfDmxRelation);
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
    if (*relation)
    {
        (*relation)->Release();
        *relation		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *relation		= pDmxRelationObj;
    
    return kVCOMError_NoError;
}

void VectorworksMVR::CGdtfDmxModeImpl::setPointer(SceneData::GdtfDmxMode *dmxMode)
{
    fDmxMode = dmxMode;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxModeImpl::BindToObject(void* objAddr)
{
	// Check if valid
	if(!fDmxMode) return kVCOMError_NotInitialized;
	
	fDmxMode->SetBind(objAddr);
	
	return kVCOMError_NoError;
}

void* VectorworksMVR::CGdtfDmxModeImpl::GetBoundObject()
{
	// Check if valid
	if(!fDmxMode) return nullptr;
	
	return fDmxMode->GetBind();
}

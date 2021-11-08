//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfDmxMode.h"
#include "CGdtfGeometry.h"
#include "CGdtfDmxChannel.h"
#include "CGdtfDmxRelation.h"
#include "CGdtfMacro.h"
#include "CGdtfDmxChannelFunction.h"
#include "CGdtfDmxChannel.h"


using namespace VectorworksMVR::Filing;

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

MvrString VectorworksMVR::CGdtfDmxModeImpl::GetDescription()
{
	// Check Pointer
	if ( ! fDmxMode) return "";
	
    return fDmxMode->GetDescription().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxModeImpl::SetDescription(MvrString description)
{
	// Check if valid
	if(!fDmxMode) { return kVCOMError_NotInitialized; }
    
    fDmxMode->SetDescription(description);

    return kVCOMError_NoError;
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
        CGdtfGeometryImpl* pResultInterface = static_cast<CGdtfGeometryImpl*>(pGeoObj);
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
	CGdtfGeometryImpl* geoImpl = static_cast<CGdtfGeometryImpl*>(model);
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

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxModeImpl::CreateDmxChannel(IGdtfGeometry* geometry, IGdtfDmxChannel** channel)
{
	// Check Pointer
	if ( ! fDmxMode) return kVCOMError_NotInitialized;
    if( ! geometry)  return kVCOMError_InvalidArg;

    CGdtfGeometryImpl* geometryImpl = static_cast<CGdtfGeometryImpl*>(geometry);
    if(! geometryImpl) return kVCOMError_Failed;

    SceneData::GdtfGeometry* gdtfGeometry = geometryImpl->GetPointer();
    if(!gdtfGeometry) { return kVCOMError_Failed; }
	
	// Check if no Overflow
 	SceneData::GdtfDmxChannel*	gdtfDmxChannel = fDmxMode->AddChannel();
    gdtfDmxChannel->SetGeomRef(gdtfGeometry);
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfDmxChannelImpl*		pDmxChannelObj = nullptr;
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
        CGdtfDmxRelationImpl* pResultInterface = static_cast<CGdtfDmxRelationImpl* >(pDmxRelationObj);
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

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxModeImpl::CreateDmxRelation(MvrString name, GdtfDefines::EGdtfDmxRelationType type, IGdtfDmxChannel* master, IGdtfDmxChannelFunction* slave, IGdtfDmxRelation** relation)
{
    // Check incomming values
    if ( ! master) { return kVCOMError_InvalidArg; }
    if ( ! slave)  { return kVCOMError_InvalidArg; }
        
	// Cast
	CGdtfDmxChannelImpl* dmxChanImpl = static_cast<CGdtfDmxChannelImpl*>(master);
	if ( ! dmxChanImpl)		{ return kVCOMError_Failed; }

	CGdtfDmxChannelFunctionImpl* dmxFunctionImpl = static_cast<CGdtfDmxChannelFunctionImpl*>(slave);
	if ( ! dmxFunctionImpl)		{ return kVCOMError_Failed; }
	
	// Get Scene Objects
	SceneData::GdtfDmxChannel* gdtfDmxChan= dmxChanImpl->getPointer();
	if ( ! gdtfDmxChan) { return kVCOMError_Failed; }  

	SceneData::GdtfDmxChannelFunction* gdtfFunc= dmxFunctionImpl->getPointer();
	if ( ! gdtfFunc) { return kVCOMError_Failed; }   

    // Check Pointers
    if(gdtfDmxChan->GetParentMode() != fDmxMode)                        { return kVCOMError_SlaveMasterNotInSameMode; }
    if(gdtfFunc->GetParentDMXChannel()->GetParentMode() != fDmxMode)    { return kVCOMError_SlaveMasterNotInSameMode; }

    // Now Create the new Relatation
    TXString vwName (name);

    SceneData::GdtfDmxRelation* gdtfDmxRelation = fDmxMode->AddDmxRelation(gdtfDmxChan, gdtfFunc, vwName);
    gdtfDmxRelation->SetRelationType(type);

     
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfDmxRelationImpl*		pDmxRelationObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDmxRelation, (IVWUnknown**) & pDmxRelationObj)))
    {
        // Check Casting
        CGdtfDmxRelationImpl* pResultInterface = static_cast<CGdtfDmxRelationImpl* >(pDmxRelationObj);
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

VectorworksMVR::VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfDmxModeImpl::GetDmxMacroCount(size_t & count)
{
	// Check Pointer
	if (!fDmxMode) return kVCOMError_NotInitialized;

	count = fDmxMode->GetDmxMacrosArray().size();

	return kVCOMError_NoError;

}

VectorworksMVR::VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfDmxModeImpl::GetDmxMacroAt(size_t at, IGdtfMacro ** macro)
{
	// Check Pointer
	if (!fDmxMode) return kVCOMError_NotInitialized;

	// Check if no Overflow
	if (at >= fDmxMode->GetDmxMacrosArray().size()) { return kVCOMError_OutOfBounds; }





	//---------------------------------------------------------------------------
	// Initialize Object
	SceneData::GdtfMacro* gdtfDmxMacro = fDmxMode->GetDmxMacrosArray()[at];
	CGdtfMacroImpl*		  pDmxMacroObj = nullptr;

	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfMacro, (IVWUnknown**)& pDmxMacroObj)))
	{
		// Check Casting
		CGdtfMacroImpl* pResultInterface = static_cast<CGdtfMacroImpl*>(pDmxMacroObj);
		if (pResultInterface)
		{
			pResultInterface->setPointer(gdtfDmxMacro);
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
	if (*macro)
	{
		(*macro)->Release();
		*macro = NULL;
	}

	//---------------------------------------------------------------------------
	// Set Out Value
	*macro = pDmxMacroObj;

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfDmxModeImpl::CreateDmxMacro(MvrString name, IGdtfMacro ** macro)
{
	// Create the new Macro
	TXString vwName(name);

	SceneData::GdtfMacro* gdtfDmxMacro = fDmxMode->AddMacro(vwName);

	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfMacroImpl*		  pDmxMacroObj = nullptr;

	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfMacro, (IVWUnknown**)& pDmxMacroObj)))
	{
		// Check Casting
		CGdtfMacroImpl* pResultInterface = static_cast<CGdtfMacroImpl*>(pDmxMacroObj);
		if (pResultInterface)
		{
			pResultInterface->setPointer(gdtfDmxMacro);
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
	if (*macro)
	{
		(*macro)->Release();
		*macro = NULL;
	}

	//---------------------------------------------------------------------------
	// Set Out Value
	*macro = pDmxMacroObj;

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxModeImpl::GetBreakCount(size_t & count)
{
	if(fDmxMode)
	{
		count = fDmxMode->GetBreakArray().size();
		return kVCOMError_NoError;
	}
    
	return kVCOMError_Failed;
    
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxModeImpl::GetBreakAt(size_t at, size_t& breakId)
{
    if(at >= fDmxMode->GetBreakArray().size())
    {
        return kVCOMError_OutOfBounds;
    }

    breakId = fDmxMode->GetBreakArray()[at];

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxModeImpl::GetFootprintForBreak(size_t inBreak, size_t& footprint)
{
    footprint = fDmxMode->GetFootPrintForBreak(inBreak);
    return kVCOMError_NoError;
}

SceneData::GdtfDmxMode* VectorworksMVR::CGdtfDmxModeImpl::getPointer()
{
    return fDmxMode;
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

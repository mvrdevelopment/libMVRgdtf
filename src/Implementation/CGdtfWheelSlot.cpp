//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfWheelSlot.h"
#include "CGdtfWheelSlotPrismFacet.h"
#include "CGdtfWheelSlotAnimationSystem.h"
#include "CGdtfFilter.h"

using namespace VectorworksMVR::Filing;

VectorworksMVR::CGdtfWheelSlotImpl::CGdtfWheelSlotImpl()
{
	fWheelSlot = nullptr;
};

VectorworksMVR::CGdtfWheelSlotImpl::~CGdtfWheelSlotImpl()
{
    
};

MvrString VectorworksMVR::CGdtfWheelSlotImpl::GetName()
{
	// Check Data
	if( ! fWheelSlot) return "";
	
    return fWheelSlot->GetName().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotImpl::GetColor(VectorworksMVR::CieColor &color)
{
	// Check Data
	if( ! fWheelSlot) return kVCOMError_NotInitialized;
	
    color.fx   = fWheelSlot->GetColor().Get_x();
    color.fy   = fWheelSlot->GetColor().Get_y();
    color.f_Y  = fWheelSlot->GetColor().Get_Y_luminance();
    return kVCOMError_NoError;
}

MvrString VectorworksMVR::CGdtfWheelSlotImpl::GetGobo()
{
	// Check Data
	if( ! fWheelSlot) return "";
	
    return fWheelSlot->GetGobo().GetCharPtr();
}

MvrString VectorworksMVR::CGdtfWheelSlotImpl::GetGoboFileFullPath()
{
	// Check Data
	if( ! fWheelSlot) return "";
	
	return fWheelSlot->GetGoboFileFullPath().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotImpl::SetName(MvrString name)
{
	// Check Pointer
	if( ! fWheelSlot) return kVCOMError_NotInitialized;

	fWheelSlot->SetName(name);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotImpl::SetColor(const CieColor& color)
{
	// Check Data
	if( ! fWheelSlot) return kVCOMError_NotInitialized;
	
	CCieColor cieCol (color.fx, color.fy, color.f_Y);
	fWheelSlot->SetColor(cieCol);
	
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotImpl::SetGobo(MvrString path)
{
	// Check Data
	if( ! fWheelSlot) return kVCOMError_NotInitialized;
	
	TXString vwPath (path);
	fWheelSlot->SetGobo(vwPath);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotImpl::GetPrismFacetCount(size_t &outCount)
{
	// Check Data
	if( ! fWheelSlot) return kVCOMError_NotInitialized;
	
    outCount = fWheelSlot->GetPrismFacets().size();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotImpl::GetPrismFacetAt(size_t &at, VectorworksMVR::IGdtfWheelSlotPrismFacet **outPosition)
{
	// Check Data
	if( ! fWheelSlot) return kVCOMError_NotInitialized;
	
    if (at >=  fWheelSlot->GetPrismFacets().size()) { return kVCOMError_OutOfBounds;  }
    
    
    SceneData::GdtfWheelSlotPrismFacet* gdtfPrismFacet = fWheelSlot->GetPrismFacets()[at];
    
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfWheelSlotPrismFacetImpl* pPrismFacetObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfWheelSlotPrismFacet, (IVWUnknown**) & pPrismFacetObj)))
    {
        // Check Casting
        CGdtfWheelSlotPrismFacetImpl* pResultInterface = static_cast<CGdtfWheelSlotPrismFacetImpl* >(pPrismFacetObj);
        if (pResultInterface)
        {
            pResultInterface->setPointer(gdtfPrismFacet);
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
    if (*outPosition)
    {
        (*outPosition)->Release();
        *outPosition		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *outPosition		= pPrismFacetObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotImpl::CreatePrismFacet(const STransformMatrix& m, IGdtfWheelSlotPrismFacet** outFacet)
{
	// Check Data
	if( ! fWheelSlot) return kVCOMError_NotInitialized;
	
	VWTransformMatrix ma;
	ma.SetUVector(m.ux, m.uy, m.uz);
	ma.SetVVector(m.vx, m.vy, m.vz);
	ma.SetWVector(m.wx, m.wy, m.wz);
	
	SceneData::GdtfWheelSlotPrismFacet* gdtfPrismFacet = fWheelSlot->AddPrismFacet();
	gdtfPrismFacet->SetTransformMatrix(ma);
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfWheelSlotPrismFacetImpl* pPrismFacetObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfWheelSlotPrismFacet, (IVWUnknown**) & pPrismFacetObj)))
	{
		// Check Casting
		CGdtfWheelSlotPrismFacetImpl* pResultInterface = static_cast<CGdtfWheelSlotPrismFacetImpl* >(pPrismFacetObj);
		if (pResultInterface)
		{
			pResultInterface->setPointer(gdtfPrismFacet);
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
	if (*outFacet)
	{
		(*outFacet)->Release();
		*outFacet		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outFacet		= pPrismFacetObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotImpl::GetAnimationSystem(VectorworksMVR::IGdtfWheelSlotAnimationSystem** outAnimationSystem)
{
	// Check Data
	if( ! fWheelSlot) return kVCOMError_NotInitialized;    
    
    SceneData::GdtfWheelSlotAnimationSystem* gdtfAnimationSystem = fWheelSlot->GetAnimationSystem();

    if (!gdtfAnimationSystem) { return kVCOMError_NotSet; }    
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfWheelSlotAnimationSystemImpl* pAnimationSystemObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfWheelSlotAnimationSystem, (IVWUnknown**) & pAnimationSystemObj)))
    {
        // Check Casting
        CGdtfWheelSlotAnimationSystemImpl* pResultInterface = static_cast<CGdtfWheelSlotAnimationSystemImpl* >(pAnimationSystemObj);
        if (pResultInterface)
        {
            pResultInterface->setPointer(gdtfAnimationSystem);
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
    if (*outAnimationSystem)
    {
        (*outAnimationSystem)->Release();
        *outAnimationSystem		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *outAnimationSystem		= pAnimationSystemObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotImpl::CreateAnimationSystem(double p1_X, double p1_Y, double p2_X, double p2_Y, double p3_X, double p3_Y, double radius, IGdtfWheelSlotAnimationSystem** outAnimationSystem)
{
	// Check Data
	if( ! fWheelSlot) return kVCOMError_NotInitialized;
	
	SceneData::GdtfWheelSlotAnimationSystem* gdtfAnimationSystem = fWheelSlot->AddAnimationSystem();
    gdtfAnimationSystem->SetP1_X(p1_X);
    gdtfAnimationSystem->SetP1_Y(p1_Y);
    gdtfAnimationSystem->SetP2_X(p2_X);
    gdtfAnimationSystem->SetP2_Y(p2_Y);
    gdtfAnimationSystem->SetP3_X(p3_X);
    gdtfAnimationSystem->SetP3_Y(p3_Y);
    gdtfAnimationSystem->SetRadius(radius);
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfWheelSlotAnimationSystemImpl* pAnimationSystemObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfWheelSlotAnimationSystem, (IVWUnknown**) & pAnimationSystemObj)))
	{
		// Check Casting
		CGdtfWheelSlotAnimationSystemImpl* pResultInterface = static_cast<CGdtfWheelSlotAnimationSystemImpl* >(pAnimationSystemObj);
		if (pResultInterface)
		{
			pResultInterface->setPointer(gdtfAnimationSystem);
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
	if (*outAnimationSystem)
	{
		(*outAnimationSystem)->Release();
		*outAnimationSystem	= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outAnimationSystem	= pAnimationSystemObj;
	
	return kVCOMError_NoError;
}


void VectorworksMVR::CGdtfWheelSlotImpl::setPointer(SceneData::GdtfWheelSlot *wheelSlot)
{
    fWheelSlot = wheelSlot;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotImpl::BindToObject(void* objAddr)
{
	// Check if valid
	if(!fWheelSlot) return kVCOMError_NotInitialized;
	
	fWheelSlot->SetBind(objAddr);
	
	return kVCOMError_NoError;
}

void* VectorworksMVR::CGdtfWheelSlotImpl::GetBoundObject()
{
	// Check if valid
	if(!fWheelSlot) return nullptr;
	
	return fWheelSlot->GetBind();
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotImpl::GetFilter(IGdtfFilter** outVal) 
{
    // Check Pointer
    if (!fWheelSlot) { return kVCOMError_NotInitialized; }

    //---------------------------------------------------------------------------
    // Initialize Object
    SceneData::GdtfFilter*	gdtfFilter = fWheelSlot->GetFilter();
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
    // Check Incomming Object
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

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotImpl::SetFilter (IGdtfFilter * newFilter)
{
    if (!fWheelSlot) { return kVCOMError_NotInitialized; }
    if (!newFilter) { return kVCOMError_InvalidArg; }

    // Cast
    CGdtfFilterImpl* FilterImpl = static_cast<CGdtfFilterImpl*>(newFilter);
    if (!FilterImpl) { return kVCOMError_Failed; }

    // Set Object
    SceneData::GdtfFilter* gdtfFilter = FilterImpl->GetPointer();
    if (!gdtfFilter) { return kVCOMError_Failed; }

    fWheelSlot->SetFilter (gdtfFilter);

    return kVCOMError_NoError;
}

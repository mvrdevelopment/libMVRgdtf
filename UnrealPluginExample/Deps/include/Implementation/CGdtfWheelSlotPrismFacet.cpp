//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfWheelSlotPrismFacet.h"
#include "Utility.h"

using namespace VectorworksMVR::Filing;

VectorworksMVR::CGdtfWheelSlotPrismFacetImpl::CGdtfWheelSlotPrismFacetImpl()
{
	fPrismFacet = nullptr;
};

VectorworksMVR::CGdtfWheelSlotPrismFacetImpl::~CGdtfWheelSlotPrismFacetImpl()
{
    
};

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotPrismFacetImpl::GetColor(VectorworksMVR::CieColor &color)
{
	// Check Data
	if( ! fPrismFacet) return kVCOMError_NotInitialized;
	
    color.fx = fPrismFacet->GetColor().Get_x();
    color.fy  = fPrismFacet->GetColor().Get_y();
    color.f_Y  = fPrismFacet->GetColor().Get_Y_luminance();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotPrismFacetImpl::GetTransformMatrix(VectorworksMVR::STransformMatrix &transformMatrix)
{
	// Check Data
	if( ! fPrismFacet) return kVCOMError_NotInitialized;
    
    GdtfUtil::ConvertMatrix(fPrismFacet->GetTransformMatrix(), transformMatrix);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotPrismFacetImpl::SetColor(const CieColor& color)
{
	// Check Data
	if( ! fPrismFacet) return kVCOMError_NotInitialized;
	
	CCieColor cie (color.fx, color.fy, color.f_Y);
	
	fPrismFacet->SetColor(cie);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotPrismFacetImpl::SetTransformMatrix(const STransformMatrix & transformMatrix)
{
    // Check Data
	if( ! fPrismFacet) return kVCOMError_NotInitialized;
	
    VWTransformMatrix vwMatrix;
    GdtfUtil::ConvertMatrix(transformMatrix, vwMatrix);

    fPrismFacet->SetTransformMatrix(vwMatrix);

    return kVCOMError_NoError;
}

void VectorworksMVR::CGdtfWheelSlotPrismFacetImpl::setPointer(SceneData::GdtfWheelSlotPrismFacet *prismFacet)
{
    fPrismFacet = prismFacet;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotPrismFacetImpl::BindToObject(void* objAddr)
{
	// Check if valid
	if(!fPrismFacet) return kVCOMError_NotInitialized;
	
	fPrismFacet->SetBind(objAddr);
	
	return kVCOMError_NoError;
}

void* VectorworksMVR::CGdtfWheelSlotPrismFacetImpl::GetBoundObject()
{
	// Check if valid
	if(!fPrismFacet) return nullptr;
	
	return fPrismFacet->GetBind();
}

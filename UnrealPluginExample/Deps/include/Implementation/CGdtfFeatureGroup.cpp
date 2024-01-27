//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfFeatureGroup.h"
#include "CGdtfFeature.h"

using namespace VectorworksMVR::Filing;

VectorworksMVR::CGdtfFeatureGroupImpl::CGdtfFeatureGroupImpl()
{
	fFeatureGroup = nullptr;
};

VectorworksMVR::CGdtfFeatureGroupImpl::~CGdtfFeatureGroupImpl()
{
    
};

MvrString VectorworksMVR::CGdtfFeatureGroupImpl::GetName()
{
	if( ! fFeatureGroup) return "";
	
    return fFeatureGroup->GetName();
}

MvrString VectorworksMVR::CGdtfFeatureGroupImpl::GetPrettyName()
{
	if( ! fFeatureGroup) return "";
	
    return fFeatureGroup->GetPrettyName();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFeatureGroupImpl::SetPrettyName(MvrString name) 
{
	// Check Pointer
	if( ! fFeatureGroup) return kVCOMError_NotInitialized;

	fFeatureGroup->SetPrettyName(name);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFeatureGroupImpl::GetFeatureCount(size_t &count)
{
	// Check Pointer
	if( ! fFeatureGroup) return kVCOMError_NotInitialized;
	
    count = fFeatureGroup->GetFeatureArray().size();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFeatureGroupImpl::GetFeatureAt(size_t at, VectorworksMVR::IGdtfFeature **feature)
{
	// Check Pointer
	if( ! fFeatureGroup) return kVCOMError_NotInitialized;
	
    // Check if no Overflow
    if (at >=  fFeatureGroup->GetFeatureArray().size()) { return kVCOMError_OutOfBounds;  }
    
    
    SceneData::GdtfFeature* gdtfFeature = fFeatureGroup->GetFeatureArray()[at];
    
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfFeatureImpl* pFeatureObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfFeature, (IVWUnknown**) & pFeatureObj)))
    {
        // Check Casting
        CGdtfFeatureImpl* pResultInterface = static_cast<CGdtfFeatureImpl* >(pFeatureObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfFeature);
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
    if (*feature)
    {
        (*feature)->Release();
        *feature		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *feature	= pFeatureObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFeatureGroupImpl::CreateFeature(MvrString name, IGdtfFeature** feature)
{
	// Check Pointer
	if( ! fFeatureGroup) return kVCOMError_NotInitialized;
	
	TXString vwName (name);
	
	SceneData::GdtfFeature* gdtfFeature = fFeatureGroup->AddFeature(vwName);
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfFeatureImpl* pFeatureObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfFeature, (IVWUnknown**) & pFeatureObj)))
	{
		// Check Casting
		CGdtfFeatureImpl* pResultInterface = static_cast<CGdtfFeatureImpl* >(pFeatureObj);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(gdtfFeature);
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
	if (*feature)
	{
		(*feature)->Release();
		*feature		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*feature	= pFeatureObj;
	
	return kVCOMError_NoError;
}

void VectorworksMVR::CGdtfFeatureGroupImpl::setPointer(SceneData::GdtfFeatureGroup *featureGroup)
{
    fFeatureGroup = featureGroup;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFeatureGroupImpl::BindToObject(void* objAddr)
{
	// Check if valid
	if(!fFeatureGroup) return kVCOMError_NotInitialized;
	
	fFeatureGroup->SetBind(objAddr);
	
	return kVCOMError_NoError;
}

void* VectorworksMVR::CGdtfFeatureGroupImpl::GetBoundObject()
{
	// Check if valid
	if(!fFeatureGroup) return nullptr;
	
	return fFeatureGroup->GetBind();
}

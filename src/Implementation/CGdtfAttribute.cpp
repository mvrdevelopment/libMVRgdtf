//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfAttribute.h"
#include "CGdtfActivationGroup.h"
#include "CGdtfFeatureGroup.h"
#include "CGdtfFeature.h"

using namespace VectorWorks::Filing;

VectorworksMVR::CGdtfAttributeImpl::CGdtfAttributeImpl()
{
	fAttribute = nullptr;
};

VectorworksMVR::CGdtfAttributeImpl::~CGdtfAttributeImpl()
{
    
};

MvrString VectorworksMVR::CGdtfAttributeImpl::GetName()
{
	if( ! fAttribute) return "";
	
	return fAttribute->GetName().GetCharPtr();;
}

MvrString VectorworksMVR::CGdtfAttributeImpl::GetPrettyName()
{
	if( ! fAttribute) return "";
	
    return fAttribute->GetPrettyName().GetCharPtr();;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfAttributeImpl::GetActivationGroup(VectorworksMVR::IGdtfActivationGroup **activationGroup)
{
	//Check Pointer
	if( ! fAttribute) return kVCOMError_NotInitialized;
	
	
    SceneData::GdtfActivationGroup* gdtfActivationGroup = fAttribute->GetActivationGroup();
	
	if ( ! gdtfActivationGroup) { return kVCOMError_NotSet; }
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfActivationGroupImpl* pActivationGroupObj = nullptr;
	
	if (!pActivationGroupObj) { return kVCOMError_NotSet; }
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfActivationGroup, (IVWUnknown**) & pActivationGroupObj)))
    {
        // Check Casting
        CGdtfActivationGroupImpl* pResultInterface = dynamic_cast<CGdtfActivationGroupImpl* >(pActivationGroupObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfActivationGroup);
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
    if (*activationGroup)
    {
        (*activationGroup)->Release();
        *activationGroup		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *activationGroup	= pActivationGroupObj;
    
    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfAttributeImpl::GetFeature(VectorworksMVR::IGdtfFeature ** feature)
{
	//Check Pointer
	if( ! fAttribute) return kVCOMError_NotInitialized;

	SceneData::GdtfFeaturePtr gdtfFeature = fAttribute->GetFeature();
	
	if ( ! gdtfFeature) { return kVCOMError_NotSet; }
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfFeatureImpl* pFeatureObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfFeature, (IVWUnknown**) & pFeatureObj)))
    {
        // Check Casting
        CGdtfFeatureImpl* pResultInterface = dynamic_cast<CGdtfFeatureImpl* >(pFeatureObj);
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

VectorworksMVR::VCOMError VectorworksMVR::CGdtfAttributeImpl::GetMainAttribute(IGdtfAttribute ** mainAttrib)
{
	// Check Data
	if( ! fAttribute) return kVCOMError_NotInitialized;
	
	//---------------------------------------------------------------------------
	// Initialize Object
	SceneData::GdtfAttribute*	gdtfAttribute = fAttribute->GetMainAttribute();
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
    if (*mainAttrib)
    {
        (*mainAttrib)->Release();
        *mainAttrib		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *mainAttrib	= pAttributeObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfAttributeImpl::GetPhysicalUnit(GdtfDefines::EGdtfPhysicalUnit & unit)
{
	//Check Pointer
	if( ! fAttribute) return kVCOMError_NotInitialized;
    
    unit = fAttribute->GetPhysicalUnit();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfAttributeImpl::GetColor(CieColor & col)
{
	// Check Data
	if( ! fAttribute)             return kVCOMError_NotInitialized;
    if( ! fAttribute->HasColor()) return kVCOMError_NotSet;
		
    col.fx   = fAttribute->GetColor().Get_x();
    col.fy   = fAttribute->GetColor().Get_y();
    col.f_Y  = fAttribute->GetColor().Get_Y_luminance();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfAttributeImpl::SetActivationGroup(IGdtfActivationGroup* activationGroup)
{
	//Check Pointer
	if( ! fAttribute)		return kVCOMError_NotInitialized;
	
	// Check Arg
	if( ! activationGroup)	return kVCOMError_InvalidArg;
	
	// Cast Act Group
	CGdtfActivationGroupImpl* actGoupImpl = dynamic_cast<CGdtfActivationGroupImpl*>(activationGroup);
	if( ! actGoupImpl)		return kVCOMError_Failed;
	
	// Now set
	SceneData::GdtfActivationGroupPtr scActGroup = actGoupImpl->GetPointer();
	if (!scActGroup)		return kVCOMError_Failed;
	
	fAttribute->SetActivationGroup(scActGroup);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfAttributeImpl::SetFeature(IGdtfFeature* feature)
{
	//Check Pointer
	if( ! fAttribute)		return kVCOMError_NotInitialized;
	
	// Check Arg
	if( ! feature)	return kVCOMError_InvalidArg;
	
	// Cast Act Group
	CGdtfFeatureImpl* featureImpl = dynamic_cast<CGdtfFeatureImpl*>(feature);
	if( ! featureImpl)		return kVCOMError_Failed;
	
	// Now set
	SceneData::GdtfFeaturePtr scFeature = featureImpl->GetPointer();
	if (!scFeature)		return kVCOMError_Failed;
	
	fAttribute->SetFeature(scFeature);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfAttributeImpl::SetMainAttribute(IGdtfAttribute* mainAttrib)
{ 
    	//Check Pointer
	if( ! fAttribute)		return kVCOMError_NotInitialized;
	
	// Check Arg
	if( ! mainAttrib)	return kVCOMError_InvalidArg;
	
	// Cast Act Group
	CGdtfAttributeImpl* attrImpl = dynamic_cast<CGdtfAttributeImpl*>(mainAttrib);
	if( ! attrImpl)		return kVCOMError_Failed;
	
	// Now set
	SceneData::GdtfAttributePtr scAttribute = attrImpl->GetPointer();
	if (!scAttribute)		return kVCOMError_Failed;
	
	fAttribute->SetMainAttribute(scAttribute);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfAttributeImpl::SetPhysicalUnit(GdtfDefines::EGdtfPhysicalUnit unit)
{
	// Check Pointer
	if( ! fAttribute) return kVCOMError_NotInitialized;
	
	fAttribute->SetPhysicalUnit(unit);
	
	return kVCOMError_NoError; 
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfAttributeImpl::SetColor(const CieColor & col)
{
	// Check Data
	if( ! fAttribute) return kVCOMError_NotInitialized;
	
	CCieColor cieCol (col.fx, col.fy, col.f_Y);
	fAttribute->SetColor(cieCol);
	
    return kVCOMError_NoError; 
}

void VectorworksMVR::CGdtfAttributeImpl::SetPointer(SceneData::GdtfAttribute *attribute)
{
    fAttribute = attribute;
}

SceneData::GdtfAttribute* VectorworksMVR::CGdtfAttributeImpl::GetPointer()
{
	return fAttribute;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfAttributeImpl::BindToObject(void* objAddr)
{
	// Check if valid
	if(!fAttribute) return kVCOMError_NotInitialized;
	
	fAttribute->SetBind(objAddr);
	
	return kVCOMError_NoError;
}

void* VectorworksMVR::CGdtfAttributeImpl::GetBoundObject()
{
	// Check if valid
	if(!fAttribute) return nullptr;
	
	return fAttribute->GetBind();
}

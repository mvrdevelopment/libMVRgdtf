//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfPinPatch.h"
#include "CGdtfGeometry.h"


using namespace VectorworksMVR::Filing;

VectorworksMVR::CGdtfPinPatchImpl::CGdtfPinPatchImpl()
{
	fPinPatch = nullptr;
};

VectorworksMVR::CGdtfPinPatchImpl::~CGdtfPinPatchImpl()
{
    
};

VectorworksMVR::VCOMError VectorworksMVR::CGdtfPinPatchImpl::GetLinkedWiringObject(IGdtfGeometry** toWiringObject)
{
	// Check Pointer
	if ( ! fPinPatch) { return kVCOMError_NotInitialized; }
	
    //---------------------------------------------------------------------------
	// Initialize Object
	CGdtfGeometryImpl*						pGeoObj				= nullptr;
	SceneData::GdtfGeometryWiringObject*	gdtfWiringObject 	= fPinPatch->GetToWiringObject();

	if(!gdtfWiringObject) { return kVCOMError_NotSet; }
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfGeometry, (IVWUnknown**) & pGeoObj)))
	{
		// Check Casting
		CGdtfGeometryImpl* pResultInterface = static_cast<CGdtfGeometryImpl* >(pGeoObj);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(gdtfWiringObject);
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
	if (*toWiringObject)
	{
		(*toWiringObject)->Release();
		*toWiringObject	= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*toWiringObject = pGeoObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfPinPatchImpl::GetFromPin(size_t& fromPin)
{
	// Check Pointer
	if ( ! fPinPatch) return kVCOMError_NotInitialized;
	
    fromPin = fPinPatch->GetFromPin();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfPinPatchImpl::GetToPin(size_t& toPin)
{
	// Check Pointer
	if ( ! fPinPatch) return kVCOMError_NotInitialized;
	
    toPin = fPinPatch->GetToPin();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfPinPatchImpl::SetLinkedWiringObject(IGdtfGeometry* toWiringObject)
{
	// Check Pointer
	if ( ! fPinPatch) 		{ return kVCOMError_NotInitialized; }
	if ( ! toWiringObject) 	{ return kVCOMError_InvalidArg; }
	
	/// Check the argument type
	if ( ! toWiringObject) { return kVCOMError_InvalidArg; }

	CGdtfGeometryImpl* toWiringObjectImpl = static_cast<CGdtfGeometryImpl*>(toWiringObject);
	if ( ! toWiringObjectImpl)	{ return kVCOMError_InvalidArg; }

	SceneData::GdtfGeometryPtr gdtfGeometry = toWiringObjectImpl->GetPointer();

	if ( gdtfGeometry->GetObjectType() != EGdtfObjectType::eGdtfGeometryWiringObject) { return kVCOMError_InvalidArg; }

	SceneData::GdtfGeometryWiringObjectPtr gdtfToWiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(gdtfGeometry);
	if ( ! gdtfToWiringObject)		{ return kVCOMError_InvalidArg; }
	
	fPinPatch->SetToWiringObject(gdtfToWiringObject);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfPinPatchImpl::SetFromPin(size_t fromPin)
{
	// Check Pointer
	if( ! fPinPatch) return kVCOMError_NotInitialized;

    fPinPatch->SetFromPin(fromPin);

	return kVCOMError_NoError;    
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfPinPatchImpl::SetToPin(size_t toPin)
{
	// Check Pointer
	if( ! fPinPatch) return kVCOMError_NotInitialized;
	
    fPinPatch->SetToPin(toPin);

	return kVCOMError_NoError;    
}

void VectorworksMVR::CGdtfPinPatchImpl::SetPointer(SceneData::GdtfPinPatch* pinPatch)
{
    fPinPatch = pinPatch;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfPinPatchImpl::BindToObject(void* objAddr)
{
	// Check if valid
	if(!fPinPatch) return kVCOMError_NotInitialized;
	
	fPinPatch->SetBind(objAddr);
	
	return kVCOMError_NoError;
}

void* VectorworksMVR::CGdtfPinPatchImpl::GetBoundObject()
{
	// Check if valid
	if(!fPinPatch) return nullptr;
	
	return fPinPatch->GetBind();
}

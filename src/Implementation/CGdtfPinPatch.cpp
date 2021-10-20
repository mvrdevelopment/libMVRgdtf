//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfPinPatch.h"


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

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelFunctionImpl::SetLinkedWiringObject(IGdtfGeometry* toWiringObject)
{
	// Check Pointer
	if ( ! fPinPatch) 		{ return kVCOMError_NotInitialized; }
	if ( ! toWiringObject) 	{ return kVCOMError_InvalidArg; }
	
	// Cast
	CGdtfGeometryImpl* wiringObjImpl = static_cast<CGdtfGeometryImpl*>(attribute);
	if ( ! wiringObjImpl) { return kVCOMError_Failed; }
	
	//
	SceneData::GdtfGeometryWiringObject wiringObject = nullptr;
	wiringObject = wiringObjImpl->GetPointer();
	if( ! wiringObject) { return kVCOMError_Failed; }
	
	fPinPatch->SetToWiringObject(wiringObject);
	
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

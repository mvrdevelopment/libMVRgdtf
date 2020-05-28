//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfActivationGroup.h"
#include "CGdtfAttribute.h"


using namespace VectorworksMVR::Filing;

VectorworksMVR::CGdtfActivationGroupImpl::CGdtfActivationGroupImpl()
{
    fActivationGroup = nullptr;
};

VectorworksMVR::CGdtfActivationGroupImpl::~CGdtfActivationGroupImpl()
{
};

MvrString VectorworksMVR::CGdtfActivationGroupImpl::GetName()
{
	if( ! fActivationGroup) return "";
	
	return fActivationGroup->GetName().GetCharPtr();
}

void VectorworksMVR::CGdtfActivationGroupImpl::SetPointer(SceneData::GdtfActivationGroup *activationGroup)
{
    fActivationGroup = activationGroup;
}

SceneData::GdtfActivationGroup* VectorworksMVR::CGdtfActivationGroupImpl::GetPointer()
{
	 return fActivationGroup;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfActivationGroupImpl::BindToObject(void* objAddr)
{
	// Check if valid
	if(!fActivationGroup) return kVCOMError_NotInitialized;
	
	fActivationGroup->SetBind(objAddr);
	
	return kVCOMError_NoError;
}

void* VectorworksMVR::CGdtfActivationGroupImpl::GetBoundObject()
{
	// Check if valid
	if(!fActivationGroup) return nullptr;
	
	return fActivationGroup->GetBind();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfActivationGroupImpl::GetAttributeCount(size_t &count)
{
	if(!fActivationGroup) {return kVCOMError_NotInitialized;}
	
	count = fActivationGroup->GetLinkedAttributes().size();
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfActivationGroupImpl::GetAttributeAt(size_t at, VectorworksMVR::IGdtfAttribute **attribute)
{
	// Check if Set
	if(!fActivationGroup) {return kVCOMError_NotInitialized;}
	
	// Check if no Overflow
	if (at >=  fActivationGroup->GetLinkedAttributes().size()) { return kVCOMError_OutOfBounds;  }
	
	
	SceneData::GdtfAttribute* gdtfAttribute = fActivationGroup->GetLinkedAttributes()[at];
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfAttributeImpl* pAttributeObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfAttribute, (IVWUnknown**) & pAttributeObj)))
	{
		// Check Casting
		CGdtfAttributeImpl* pResultInterface = static_cast<CGdtfAttributeImpl* >(pAttributeObj);
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
	if (*attribute)
	{
		(*attribute)->Release();
		*attribute		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*attribute	= pAttributeObj;
	
	return kVCOMError_NoError;
}

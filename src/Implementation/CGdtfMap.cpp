//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfMap.h"


using namespace VectorworksMVR::Filing;

VectorworksMVR::CGdtfMapImpl::CGdtfMapImpl()
{
	fMap = nullptr;
};

VectorworksMVR::CGdtfMapImpl::~CGdtfMapImpl()
{
    
};

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMapImpl::GetKey(Uint32& key)
{
	// Check Pointer
	if ( ! fMap) return kVCOMError_NotInitialized;
	
    key = fMap->GetKey();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMapImpl::GetValue(Uint32& value)
{
	// Check Pointer
	if ( ! fMap) return kVCOMError_NotInitialized;
	
    value = fMap->GetValue();
    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfMapImpl::SetKey(Uint32 key)
{
	// Check Pointer
	if( ! fMap) return kVCOMError_NotInitialized;

    fMap->SetKey(key);

	return kVCOMError_NoError;    
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMapImpl::SetValue(Uint32 value)
{
	// Check Pointer
	if( ! fMap) return kVCOMError_NotInitialized;
	
    fMap->SetValue(value);

	return kVCOMError_NoError;    
}

void VectorworksMVR::CGdtfMapImpl::SetPointer(SceneData::GdtfMap* map)
{
    fMap = map;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMapImpl::BindToObject(void* objAddr)
{
	// Check if valid
	if(!fMap) return kVCOMError_NotInitialized;
	
	fMap->SetBind(objAddr);
	
	return kVCOMError_NoError;
}

void* VectorworksMVR::CGdtfMapImpl::GetBoundObject()
{
	// Check if valid
	if(!fMap) return nullptr;
	
	return fMap->GetBind();
}

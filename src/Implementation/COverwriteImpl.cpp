//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "COverwriteImpl.h"


VectorworksMVR::COverwriteImpl::COverwriteImpl()
{
	fPtr = nullptr;
}

VectorworksMVR::COverwriteImpl::~COverwriteImpl()
{
	fPtr = nullptr;
}

MvrString VectorworksMVR::COverwriteImpl::GetUniversal()
{
	// Check if this is initialized
	ASSERTN(kEveryone, fPtr);
	if( ! fPtr) return "";
	
	// Otherwise return data
	return fPtr->GetUniversal().GetCharPtr();
}

MvrString VectorworksMVR::COverwriteImpl::GetTarget()
{
	// Check if this is initialized
	ASSERTN(kEveryone, fPtr);
	if( ! fPtr) return "";
	
	// Otherwise return data
	return fPtr->GetTarget().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::COverwriteImpl::SetUniversal(const MvrString& universal)
{
	// Check if this is initialized
	ASSERTN(kEveryone, fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	fPtr->SetUniversal(universal);

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::COverwriteImpl::SetTarget(const MvrString& target)
{
	// Check if this is initialized
	ASSERTN(kEveryone, fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	fPtr->SetTarget(target);

	return kVCOMError_NoError;
}


void VectorworksMVR::COverwriteImpl::SetPointer(SceneData::SceneDataOverwritePtr pointer)
{
	fPtr = pointer;
}

void VectorworksMVR::COverwriteImpl::GetPointer(SceneData::SceneDataOverwritePtr& pointer)
{
	pointer = fPtr;
}

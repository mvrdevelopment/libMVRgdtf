//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CMediaRessourceVectorImpl.h"


using namespace VectorworksMVR::Filing;


VectorworksMVR::CSourceImpl::CSourceImpl()
{
	fPtr = nullptr;
}

VectorworksMVR::CSourceImpl::~CSourceImpl()
{
	fPtr = nullptr;
}

MvrString VectorworksMVR::CSourceImpl::GetValue()
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return "";
	
	return fPtr->GetValue().GetCharPtr();
}

MvrString VectorworksMVR::CSourceImpl::GetLinkedGeometry()
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return "";
	
	return fPtr->GetLinkedGeometry().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CSourceImpl::GetType(GdtfDefines::ESourceType& sourceType)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherise return data
	sourceType = fPtr->GetType();

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSourceImpl::SetValue(MvrString value)
{
	// Check if this is initialized
	ASSERTN(kEveryone, fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	fPtr->SetValue(value);

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSourceImpl::SetLinkedGeometry(MvrString linkedGeometry)
{
	// Check if this is initialized
	ASSERTN(kEveryone, fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	fPtr->SetLinkedGeometry(linkedGeometry);

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSourceImpl::SetType(GdtfDefines::ESourceType sourceType)
{
	// Check if this is initialized
	ASSERTN(kEveryone, fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherise return data
	fPtr->SetType(sourceType);

	return kVCOMError_NoError;
}

void VectorworksMVR::CSourceImpl::SetPointer(SceneData::SceneDataSourceObjPtr pointer)
{
	fPtr = pointer;
}

void VectorworksMVR::CSourceImpl::GetPointer(SceneData::SceneDataSourceObjPtr& pointer)
{
	pointer = fPtr;
}

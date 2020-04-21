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

MvrString VectorworksMVR::CSourceImpl::GetLinkedGeometry()
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return "";
	
	return fPtr->GetLinkedGeometry().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CSourceImpl::GetType(ESourceType& sourceType)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherise return data
	sourceType = fPtr->GetType();

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

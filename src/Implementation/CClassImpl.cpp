//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "VectorworksMVR.h"


#include "CMediaRessourceVectorImpl.h"


using namespace VectorWorks::Filing;


VectorworksMVR::CClassImpl::CClassImpl()
{
	fPtr		= nullptr;
}

VectorworksMVR::CClassImpl::~CClassImpl()
{
	fPtr		= nullptr;
}

MvrString VectorworksMVR::CClassImpl::GetName()
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return "";
	
	return fPtr->getName().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CClassImpl::GetGuid(UUID& outGuid)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherise return data
	fPtr->getGuid().GetUuidObj().GetUUID(outGuid.a, outGuid.b, outGuid.c, outGuid.d);
	
	
	return kVCOMError_NoError;
}

void VectorworksMVR::CClassImpl::SetPointer(SceneData::SceneDataClassObjPtr pointer)
{
	fPtr		= pointer;
}

void VectorworksMVR::CClassImpl::GetPointer(SceneData::SceneDataClassObjPtr& pointer)
{
	pointer = fPtr;
}

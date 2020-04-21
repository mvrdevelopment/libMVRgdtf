//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CMediaRessourceVectorImpl.h"


using namespace VectorworksMVR::Filing;


VectorworksMVR::CMappingDefinitionImpl::CMappingDefinitionImpl()
{
	fPtr = nullptr;
}

VectorworksMVR::CMappingDefinitionImpl::~CMappingDefinitionImpl()
{
	fPtr = nullptr;
}

MvrString VectorworksMVR::CMappingDefinitionImpl::GetName()
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return "";
	
	
	return fPtr->getName().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CMappingDefinitionImpl::GetGuid(MvrUUID& outGuid)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherise return data
	fPtr->getGuid().GetUuidObj().GetUUID(outGuid.a, outGuid.b, outGuid.c, outGuid.d);

	
	return kVCOMError_NoError;
}

void VectorworksMVR::CMappingDefinitionImpl::SetPointer(SceneData::SceneDataMappingDefinitionObjPtr pointer)
{
	fPtr = pointer;
}

void VectorworksMVR::CMappingDefinitionImpl::GetPointer(SceneData::SceneDataMappingDefinitionObjPtr& pointer)
{
	pointer = fPtr;
}

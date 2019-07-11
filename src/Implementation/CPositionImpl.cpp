//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CMediaRessourceVectorImpl.h"


using namespace VectorworksMVR::Filing;


VectorworksMVR::CPositionImpl::CPositionImpl()
{
	fPtr = nullptr;
}

VectorworksMVR::CPositionImpl::~CPositionImpl()
{
	fPtr = nullptr;
}

MvrString VectorworksMVR::CPositionImpl::GetName()
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return "";
	
	
	return fPtr->getName().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CPositionImpl::GetGuid(MvrUUID& outGuid)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherise return data
	fPtr->getGuid().GetUuidObj().GetUUID(outGuid.a, outGuid.b, outGuid.c, outGuid.d);

	
	return kVCOMError_NoError;
}

void VectorworksMVR::CPositionImpl::SetPointer(SceneData::SceneDataPositionObjPtr pointer)
{
	fPtr = pointer;
}

void VectorworksMVR::CPositionImpl::GetPointer(SceneData::SceneDataPositionObjPtr& pointer)
{
	pointer = fPtr;
}

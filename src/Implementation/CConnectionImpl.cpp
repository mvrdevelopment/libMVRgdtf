//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CConnectionImpl.h"


using namespace VectorworksMVR::Filing;


VectorworksMVR::CConnectionImpl::CConnectionImpl()
{
	fPtr = nullptr;
}

VectorworksMVR::CConnectionImpl::~CConnectionImpl()
{
}

VectorworksMVR::VCOMError VectorworksMVR::CConnectionImpl::GetToObject(MvrUUID& objUUID)
{
	// Check if this is initialized
	ASSERTN(kEveryone, fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherise return data
	fPtr->GetToObject().GetUuidObj().GetUUID(objUUID.a, objUUID.b, objUUID.c, objUUID.d);

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CConnectionImpl::SetToObject(MvrUUID objUUID)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	fPtr->SetToObject(SceneData::SceneDataGUID(VWUUID(objUUID.a, objUUID.b, objUUID.c, objUUID.d)));

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CConnectionImpl::SetOwn(MvrString value)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	TXString t(value);
	fPtr->SetOwn(t);

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CConnectionImpl::SetOther(MvrString value)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	TXString t(value);
	fPtr->SetOther(t);

	return kVCOMError_NoError;
}

MvrString VectorworksMVR::CConnectionImpl::GetOwn()
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if ( ! fPtr) { return ""; }
	
	// Otherwise return data
	return fPtr->GetOwn().GetCharPtr();
}

MvrString VectorworksMVR::CConnectionImpl::GetOther()
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if ( ! fPtr) { return ""; }
	
	// Otherwise return data
	return fPtr->GetOther().GetCharPtr();
}


void VectorworksMVR::CConnectionImpl::SetPointer(SceneData::SceneDataConnectionObjPtr pointer)
{
	fPtr = pointer;
}

void VectorworksMVR::CConnectionImpl::GetPointer(SceneData::SceneDataConnectionObjPtr& pointer)
{
	pointer = fPtr;
}

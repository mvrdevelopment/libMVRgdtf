//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CMediaRessourceVectorImpl.h"
#include "CConnectionImpl.h"


using namespace VectorworksMVR::Filing;


VectorworksMVR::CMappingImpl::CMappingImpl()
{
	fPtr = nullptr;
}

VectorworksMVR::CMappingImpl::~CMappingImpl()
{
	fPtr = nullptr;
}

VectorworksMVR::VCOMError VectorworksMVR::CMappingImpl::GetLinkedDefUuid(MvrUUID& linkedDefUuid)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherise return data
	fPtr->GetLinkedDefUuid().GetUuidObj().GetUUID(linkedDefUuid.a, linkedDefUuid.b, linkedDefUuid.c, linkedDefUuid.d);

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMappingImpl::GetUx(Uint32& outValue)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	outValue = fPtr->GetUx();

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMappingImpl::GetUy(Uint32& outValue)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	outValue = fPtr->GetUy();

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMappingImpl::GetOx(Uint32& outValue)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	outValue = fPtr->GetOx();

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMappingImpl::GetOy(Uint32& outValue)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	outValue = fPtr->GetOy();

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMappingImpl::GetRz(double& outValue)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	outValue = fPtr->GetRz();

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMappingImpl::SetLinkedDefUuid(MvrUUID linkedDefUuid)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	fPtr->SetLinkedDefUuid(SceneData::SceneDataGUID(VWUUID(linkedDefUuid.a, linkedDefUuid.b, linkedDefUuid.c, linkedDefUuid.d)));

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMappingImpl::SetUx(Uint32 value)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	fPtr->SetUx(value);

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMappingImpl::SetUy(Uint32 value)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	fPtr->SetUy(value);

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMappingImpl::SetOx(Uint32 value)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	fPtr->SetOx(value);

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMappingImpl::SetOy(Uint32 value)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	fPtr->SetOy(value);

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMappingImpl::SetRz(double value)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	fPtr->SetRz(value);

	return kVCOMError_NoError;
}


void VectorworksMVR::CMappingImpl::SetPointer(SceneData::SceneDataMappingObjPtr pointer)
{
	fPtr = pointer;
}

void VectorworksMVR::CMappingImpl::GetPointer(SceneData::SceneDataMappingObjPtr& pointer)
{
	pointer = fPtr;
}

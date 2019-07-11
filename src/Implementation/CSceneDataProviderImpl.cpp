//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CMediaRessourceVectorImpl.h"


using namespace VectorworksMVR::Filing;


VectorworksMVR::CSceneDataProviderImpl::CSceneDataProviderImpl()
{
	fPtr = nullptr;
}

VectorworksMVR::CSceneDataProviderImpl::~CSceneDataProviderImpl ()
{
	fPtr = nullptr;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneDataProviderImpl::AddKeyValue(MvrString key, MvrString value)
{
	//------------------------------------------------------------------------------------------
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	//------------------------------------------------------------------------------------------
	// Add to object
	TXString txKey (key);
	TXString txVal (value);
	
	fPtr->AddEntry(txKey, txVal);
	
	// Return No Error
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneDataProviderImpl::GetKeyValueCount(size_t& outVal)
{
	//------------------------------------------------------------------------------------------
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	//------------------------------------------------------------------------------------------
	// Get Count
	outVal = fPtr->GetEntryCount();
	
	// Return No Error
	return kVCOMError_NoError;
}

MvrString VectorworksMVR::CSceneDataProviderImpl::GetKeyAt(size_t at)
{
	//------------------------------------------------------------------------------------------
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return "";
	
	//------------------------------------------------------------------------------------------
	// Get Value
	
	if (fPtr->GetEntryCount() > at)
	{
		return fPtr->GetKeyAt(at).GetCharPtr();
	}
	
	// Otherwise return false
	return "";
	
}

MvrString VectorworksMVR::CSceneDataProviderImpl::GetProviderName()
{
	//------------------------------------------------------------------------------------------
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return "";
	
	//------------------------------------------------------------------------------------------
	// Get Value
	return fPtr->GetProvider().GetCharPtr();;
	
}

MvrString VectorworksMVR::CSceneDataProviderImpl::GetVersion()
{
	//------------------------------------------------------------------------------------------
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return "";
	
	//------------------------------------------------------------------------------------------
	// Get Value
	return fPtr->GetVersion().GetCharPtr();;
	
}

MvrString VectorworksMVR::CSceneDataProviderImpl::GetValueAt(size_t at)
{
	//------------------------------------------------------------------------------------------
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return "";
	
	//------------------------------------------------------------------------------------------
	// Get Count
	if (fPtr->GetEntryCount() > at)
	{
		return fPtr->GetValueAt(at).GetCharPtr();
	}
	
	// Otherwise return false
	return "";
	
}

void VectorworksMVR::CSceneDataProviderImpl::SetPointer(SceneData::SceneDataProviderObjPtr pointer)
{
	fPtr = pointer;
}

//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CCustomCommandImpl.h"


VectorworksMVR::CCustomCommandImpl::CCustomCommandImpl()
{
	fPtr = nullptr;
}

VectorworksMVR::CCustomCommandImpl::~CCustomCommandImpl()
{
	fPtr = nullptr;
}

MvrString VectorworksMVR::CCustomCommandImpl::GetChannelFunction()
{
	// Check if this is initialized
	ASSERTN(kEveryone, fPtr);
	if( ! fPtr) return "";
	
	// Otherwise return data
	return fPtr->GetChannelFunction().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CCustomCommandImpl::IsPercentage(bool& isPercentage)
{
	// Check if this is initialized
	ASSERTN(kEveryone, fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	isPercentage = fPtr->IsPercentage();

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CCustomCommandImpl::GetValue(double& outValue)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	outValue = fPtr->GetValue();

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CCustomCommandImpl::SetChannelFunction(const MvrString& channelFunction)
{
	// Check if this is initialized
	ASSERTN(kEveryone, fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	fPtr->SetChannelFunction(channelFunction);

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CCustomCommandImpl::SetIsPercentage(bool isPercentage)
{
	// Check if this is initialized
	ASSERTN(kEveryone, fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	fPtr->SetIsPercentage(isPercentage);

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CCustomCommandImpl::SetValue(double value)
{
	// Check if this is initialized
	ASSERTN(kEveryone, fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	fPtr->SetValue(value);

	return kVCOMError_NoError;
}


void VectorworksMVR::CCustomCommandImpl::SetPointer(SceneData::SceneDataCustomCommandPtr pointer)
{
	fPtr = pointer;
}

void VectorworksMVR::CCustomCommandImpl::GetPointer(SceneData::SceneDataCustomCommandPtr& pointer)
{
	pointer = fPtr;
}

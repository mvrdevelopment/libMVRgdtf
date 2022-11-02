//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CMediaRessourceVectorImpl.h"
#include "CGdtfXmlParsingError.h"


using namespace VectorworksMVR::Filing;


VectorworksMVR::CGdtfXmlParsingErrorImpl::CGdtfXmlParsingErrorImpl()
{
	fPtr		= nullptr;
}

VectorworksMVR::CGdtfXmlParsingErrorImpl::~CGdtfXmlParsingErrorImpl()
{
	fPtr		= nullptr;
}

VCOMError VectorworksMVR::CGdtfXmlParsingErrorImpl::GetErrorType(GdtfDefines::EGdtfParsingError& error)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_Failed;
	
	error =  fPtr->GetError();

	return kVCOMError_NoError;
}

MvrString VectorworksMVR::CGdtfXmlParsingErrorImpl::GetErrorMessage()
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return "";
	
	return fPtr->GetErrorMessage().GetCharPtr();

}

MvrString VectorworksMVR::CGdtfXmlParsingErrorImpl::GetNodeName()
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return "";
	
	return fPtr->GetNodeName().GetCharPtr();
}

VCOMError VectorworksMVR::CGdtfXmlParsingErrorImpl::GetLineAndColumnNumber(size_t& line, size_t& column)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_Failed;
	
	line   =  fPtr->GetLineNumber();
	column =  fPtr->GetColumnNumber();

	return kVCOMError_NoError;
}

MvrString VectorworksMVR::CGdtfXmlParsingErrorImpl::GetObjectName()
{
	// Check if this is initialized
	ASSERTN(kEveryone, fPtr);
	if( ! fPtr) return "";
	
	return fPtr->GetObjectName().GetCharPtr();
}

void VectorworksMVR::CGdtfXmlParsingErrorImpl::SetPointer(GdtfParsingError* pointer)
{
	fPtr		= pointer;
}

void VectorworksMVR::CGdtfXmlParsingErrorImpl::GetPointer(GdtfParsingError*& pointer)
{
	pointer = fPtr;
}

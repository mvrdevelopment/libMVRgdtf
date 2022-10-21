//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "Prefix/StdAfx.h"
#include "Include/GDTFPrefix.h"

using namespace VectorworksMVR::Filing;

//------------------------------------------------------------------------------------
// Parsing Errors
namespace VectorworksMVR
{

class GdtfParsingError
{
public:
	GdtfParsingError(GdtfDefines::EGdtfParsingError type);
	GdtfParsingError(GdtfDefines::EGdtfParsingError type, size_t lineNumber, size_t column);
	GdtfParsingError(GdtfDefines::EGdtfParsingError type, const IXMLFileNodePtr& node);
    ~GdtfParsingError();
	
private:
	GdtfDefines::EGdtfParsingError fErrorType;
	TXString					   fErrorMessage;
	TXString					   fNodeName;
	size_t						   fLineNumber;
	size_t						   fColumn;
	TXString					   fObjectName;
	
public:
	GdtfDefines::EGdtfParsingError	GetError() const;
	const TXString&					GetErrorMessage() const;
	const TXString&					GetNodeName() const;
	size_t							GetLineNumber() const;
	size_t							GetColumnNumber() const;
	const TXString& 				GetObjectName() const;

public:
	static void	CheckNodeAttributes(IXMLFileNodePtr pNode, const TXStringArray& needed, const TXStringArray& optional);
};

typedef std::vector<GdtfParsingError> TGdtfParsingErrorArray;

}
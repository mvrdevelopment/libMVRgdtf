//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "Prefix/StdAfx.h"
#include "Include/GDTFPrefix.h"

using namespace VectorWorks::Filing;

//------------------------------------------------------------------------------------
// Parsing Errors
class GdtfParsingError
{
public:
	GdtfParsingError(GdtfDefines::EGdtfParsingError type);
	GdtfParsingError(GdtfDefines::EGdtfParsingError type, size_t lineNumber, size_t column);
    ~GdtfParsingError();
	
private:
	GdtfDefines::EGdtfParsingError fErrorType;
	TXString					   fAttributeNodeName;
	size_t						   fLineNumber;
	size_t						   fColumn;
	
	void	CheckValidValue()	const;

public:
	GdtfDefines::EGdtfParsingError	GetError() const;
	const TXString&					GetErrorMessage() const;
	size_t							GetLineNumber() const;
	size_t							GetColumnNumber() const;
public:
	static void	CheckNodeAttributes(IXMLFileNodePtr pNode, const TXStringArray& needed, const TXStringArray& optional);
};

typedef std::vector<GdtfParsingError> TGdtfParsingErrorArray;

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
    ~GdtfParsingError();
	
private:
	GdtfDefines::EGdtfParsingError fErrorType;
	TXString					   fAttributeNodeName;
	
	void	CheckValidValue()	const;

public:
	GdtfDefines::EGdtfParsingError	GetError() const;
	const TXString&					GetErrorMessage() const;
	
public:
	static void	CheckNodeAttributes(IXMLFileNodePtr pNode, const TXStringArray& needed, const TXStringArray& optional);
};

typedef std::vector<GdtfParsingError> TGdtfParsingErrorArray;

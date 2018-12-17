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
	GdtfParsingError();
    ~GdtfParsingError();
	
private:
	GdtfDefines::EGdtfParsingError fErrorType;
	
	void	CheckValidValue()	const;
	
public:
	static void	CheckNodeAttributes(IXMLFileNodePtr pNode, const TXStringArray& needed, const TXStringArray& optional);
};

typedef std::vector<GdtfParsingError> TGdtfParsingErrorArray;

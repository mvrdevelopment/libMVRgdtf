//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "Prefix/StdAfx.h"
#include "Include/GDTFPrefix.h"

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
	static void	CheckAttributesList(IXMLFileNodePtr pNode, const TXStringArray& needed, const TXStringArray& optional) const;
};

typedef std::vector<GdtfParsingError> TGdtfParsingErrorArray;

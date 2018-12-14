//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

//------------------------------------------------------------------------------------
// Parsing Errors
class GdtfParsingError
{
public:
	GdtfParsingError();
    ~GdtfParsingError();
	
private:
	GdtfDefines::EGdtfParsingError fErrorType;
	
};

typedef std::vector<GdtfParsingError> TGdtfParsingErrorArray;

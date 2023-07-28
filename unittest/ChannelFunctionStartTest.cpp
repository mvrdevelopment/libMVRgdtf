//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include "ChannelFunctionStartTest.h"
#include <iostream>
#include "Utility.h"
#include "Include/VectorworksMVR.h"
using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;


#define __checkVCOM(x) this->checkVCOM(x, #x)
#define __checkVCOM_NotSet(x) this->checkVCOM_NotSet(x, #x)

ChannelFunctionStartTest::ChannelFunctionStartTest(const std::string& currentDir)
{
}

ChannelFunctionStartTest::~ChannelFunctionStartTest()
{  
}

bool ChannelFunctionStartTest::ExecuteTest()
{
	std::cout << "=                         ChannelFunctionStartTest Unit Test                           =" << std::endl;

    std::string path = UnitTestUtil::GetTestResourceFolder() + kSeparator + "Robe lighting s.r.o.@BMFL Spot@cannot assign 0 to frost function.gdtf";

    IGdtfFixturePtr gdtfFile (IID_IGdtfFixture);

    if(__checkVCOM(gdtfFile->ReadFromFile(path.c_str())))
    {
        IGdtfXmlParsingErrorPtr error;
		__checkVCOM(gdtfFile->GetParsingErrorAt(0, & error));
        ReadError(error, 887, 172, GdtfDefines::EGdtfParsingError::eChannelFunctionNotStartingWithZero);

		__checkVCOM(gdtfFile->GetParsingErrorAt(1, & error));
        ReadError(error, 1037, 75, GdtfDefines::EGdtfParsingError::eValueError_DmxValueHasWrongValue);

		__checkVCOM(gdtfFile->GetParsingErrorAt(2, & error));
        ReadError(error, 1663, 172, GdtfDefines::EGdtfParsingError::eChannelFunctionNotStartingWithZero);


    }
    return true;
}

void ChannelFunctionStartTest::ReadError(IGdtfXmlParsingErrorPtr& error, size_t lineNumber, size_t colNumber, GdtfDefines::EGdtfParsingError errorType)
{
	size_t thisLineNumber  = 0;
	size_t thisColNumber   = 0;
	if(__checkVCOM(error->GetLineAndColumnNumber(thisLineNumber, thisColNumber)))
	{
		this->checkifEqual("lineNumber ", 	thisLineNumber, lineNumber);
		#ifndef DONT_USE_XERCES_AS_XMLLIB
		this->checkifEqual("colNumber ", 	thisColNumber, 	colNumber); 
		#endif
	}

	GdtfDefines::EGdtfParsingError thisErrorType;
	if(__checkVCOM(error->GetErrorType(thisErrorType))) { this->checkifEqual("errorType ", (Sint32)thisErrorType, (Sint32)errorType); }
}
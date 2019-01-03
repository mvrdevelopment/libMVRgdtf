//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include "GdtfXmlError.h"
#include <iostream>

#include "Include/VectorworksMVR.h"
using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;


#define __checkVCOM(x) this->checkVCOM(x, #x)
#define __checkVCOMFailed(x) this->checkVCOM_Failed(x, #x)

GdtfXmlErrorTest::GdtfXmlErrorTest(const std::string& currentDir)
{
    fPath = currentDir;
#ifdef _WINDOWS
    fPath = std::string(GITPATH);
    fPath += std::string("\\files\\XMLBroken.gdtf");
#else
	fPath = std::string(GITPATH);
	fPath += "/unittest/files/XMLBroken.gdtf";
#endif


    std::cout << "Export File to " << fPath << std::endl; 
}

GdtfXmlErrorTest::~GdtfXmlErrorTest()
{
}

bool GdtfXmlErrorTest::ExecuteTest()
{
	std::cout << "=                                        GdtfXMLErrorTest                                  =" << std::endl;
    ReadDamagedFile();
	ReadNonExistingFile();

    return true;
}

void GdtfXmlErrorTest::ReadDamagedFile()
{
	//------------------------------------------------------------------------------    
	// Read Existing File with damaged structure
	IGdtfFixturePtr gdtfRead (IID_IGdtfFixture);
    __checkVCOM(gdtfRead->ReadFromFile(fPath.c_str()));

	size_t countErrors = 0;
	__checkVCOM(gdtfRead->GetParsingErrorCount(countErrors));
	checkifEqual("Count Errors", countErrors, (size_t)3);

	for(size_t i = 0; i < countErrors; i++)
	{
		IGdtfXmlParsingErrorPtr error;
		__checkVCOM(gdtfRead->GetParsingErrorAt(i, & error));


		if(i == 0) { ReadError(error, 0, 0, GdtfDefines::EGdtfParsingError::eChecksumError); }
		if(i == 1) { ReadError(error, 27, 7, GdtfDefines::EGdtfParsingError::eXmlParsingError); }
		if(i == 2) { ReadError(error, 0, 0, GdtfDefines::EGdtfParsingError::eValueError_MatrixFormatError); }
	}
	
}

void GdtfXmlErrorTest::ReadNonExistingFile()
{
	//------------------------------------------------------------------------------    
	// Read Existing File with damaged structure
	IGdtfFixturePtr gdtfRead (IID_IGdtfFixture);
    __checkVCOMFailed(gdtfRead->ReadFromFile(""));

	size_t countErrors = 0;
	__checkVCOM(gdtfRead->GetParsingErrorCount(countErrors));
	checkifEqual("Count Errors", countErrors, (size_t)0);

	for(size_t i = 0; i < countErrors; i++)
	{
		IGdtfXmlParsingErrorPtr error;
		__checkVCOM(gdtfRead->GetParsingErrorAt(i, & error));

		if(i == 0) { ReadError(error, 0, 0, GdtfDefines::EGdtfParsingError::eMissingFile); }
	}
	
}

void GdtfXmlErrorTest::ReadError(IGdtfXmlParsingErrorPtr& error, size_t lineNumber, size_t colNumber, GdtfDefines::EGdtfParsingError errorType)
{
	size_t thisLineNumber  = 0;
	size_t thisColNumber   = 0;
	if(__checkVCOM(error->GetLineAndColumnNumber(thisLineNumber, thisColNumber)))
	{
		this->checkifEqual("lineNumber ", 	thisLineNumber, lineNumber);
		this->checkifEqual("colNumber ", 	thisColNumber, 	colNumber); 
	}

	GdtfDefines::EGdtfParsingError thisErrorType;
	if(__checkVCOM(error->GetErrorType(thisErrorType))) { this->checkifEqual("errorType ", (Sint32)thisErrorType, (Sint32)errorType); }
}
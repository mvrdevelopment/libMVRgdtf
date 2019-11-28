//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include "DmxChannelSetBug.h"
#include <iostream>
#include "Utility.h"
#include "Include/VectorworksMVR.h"
using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;


#define __checkVCOM(x) this->checkVCOM(x, #x)
#define __checkVCOM_NotSet(x) this->checkVCOM_NotSet(x, #x)

GdtfDmxChannelSetBug::GdtfDmxChannelSetBug(const std::string& currentDir)
{
}

GdtfDmxChannelSetBug::~GdtfDmxChannelSetBug()
{  
}

bool GdtfDmxChannelSetBug::ExecuteTest()
{
	std::cout << "=                         GdtfDmxChannelSetBug Unit Test                           =" << std::endl;

    std::string path = UnitTestUtil::GetTestResourceFolder() + kSeparator + "BugInChannelSetDmxJumps.gdtf";

    IGdtfFixturePtr gdtfFile (IID_IGdtfFixture);

    if(__checkVCOM(gdtfFile->ReadFromFile(path.c_str())))
    {
        size_t countErrors = 0;
        __checkVCOM(gdtfFile->GetParsingErrorCount(countErrors));
        checkifEqual("Count Errors", countErrors, (size_t)5);


		 IGdtfXmlParsingErrorPtr error;
		__checkVCOM(gdtfFile->GetParsingErrorAt(0, & error));
        ReadError(error, 4091,88,GdtfDefines::EGdtfParsingError::eValueError_DmxValueHasWrongValue);

		__checkVCOM(gdtfFile->GetParsingErrorAt(1, & error));
        ReadError(error, 4092,88,GdtfDefines::EGdtfParsingError::eValueError_DmxValueHasWrongValue);
		
		__checkVCOM(gdtfFile->GetParsingErrorAt(2, & error));
        ReadError(error, 4093,88,GdtfDefines::EGdtfParsingError::eValueError_DmxValueHasWrongValue);
		
		__checkVCOM(gdtfFile->GetParsingErrorAt(3, & error));
        ReadError(error, 4094,71,GdtfDefines::EGdtfParsingError::eValueError_DmxValueHasWrongValue);
		
		__checkVCOM(gdtfFile->GetParsingErrorAt(4, & error));
        ReadError(error, 4534,75,GdtfDefines::EGdtfParsingError::eValueError_DmxValueHasWrongValue);


    }
    return true;
}

void GdtfDmxChannelSetBug::ReadError(IGdtfXmlParsingErrorPtr& error, size_t lineNumber, size_t colNumber, GdtfDefines::EGdtfParsingError errorType)
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

void GdtfDmxChannelSetBug::CheckChannelSet(VectorworksMVR::IGdtfDmxChannelSetPtr& channelSet, std::string name, VectorworksMVR::GdtfDefines::DmxValue start, VectorworksMVR::GdtfDefines::DmxValue end)
{
	this->checkifEqual("Check Name ", name, channelSet->GetName());

	DmxValue thisStart = 0;
	__checkVCOM(channelSet->GetDmxStartAddress(thisStart));
	this->checkifEqual("Check Start ", start, thisStart);

	DmxValue thisEnd = 0;
	__checkVCOM(channelSet->GetDmxEndAddress(thisEnd));
	this->checkifEqual("Check End ",  end, thisEnd);
}
//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include "DmxValueBug.h"
#include <iostream>
#include "Utility.h"
#include "Include/VectorworksMVR.h"
using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;


#define __checkVCOM(x) this->checkVCOM(x, #x)
#define __checkVCOM_NotSet(x) this->checkVCOM_NotSet(x, #x)

GdtfValueBug::GdtfValueBug(const std::string& currentDir)
{
}

GdtfValueBug::~GdtfValueBug()
{  
}

bool GdtfValueBug::ExecuteTest()
{
	std::cout << "=                                     GdtfValueBug Unit Test                           =" << std::endl;

    std::string path = UnitTestUtil::GetTestResourceFolder() + kSeparator + "BugInDmxWithHex.gdtf";

    IGdtfFixturePtr gdtfFile (IID_IGdtfFixture);

    if(__checkVCOM(gdtfFile->ReadFromFile(path.c_str())))
    {
        	size_t countErrors = 0;
        __checkVCOM(gdtfFile->GetParsingErrorCount(countErrors));
        checkifEqual("Count Errors", countErrors, (size_t)1);

        IGdtfXmlParsingErrorPtr error;
		__checkVCOM(gdtfFile->GetParsingErrorAt(0, & error));
        ReadError(error, 367,64,GdtfDefines::EGdtfParsingError::eValueError_DmxValueHasWrongValue);

        IGdtfDmxModePtr mode;
        __checkVCOM(gdtfFile->GetDmxModeAt(0, & mode));


        IGdtfDmxChannelPtr channel;
        __checkVCOM(mode->GetDmxChannelAt(0, & channel));

        IGdtfDmxLogicalChannelPtr logicalChannel;
        __checkVCOM(channel->GetLogicalChannelAt(0, & logicalChannel));


        IGdtfDmxChannelFunctionPtr function;
        __checkVCOM(logicalChannel->GetDmxFunctionAt(0, & function));

        size_t countChannelSets = 0;
        __checkVCOM(function->GetDmxChannelSetCount(countChannelSets));

        for (size_t i = 0; i < countChannelSets; i++)
        {
            IGdtfDmxChannelSetPtr channelSet;
            __checkVCOM(function->GetDmxChannelSetAt(i,&channelSet));

            CheckChannelSet(channelSet);

        }
        



    }
    return true;
}

void GdtfValueBug::ReadError(IGdtfXmlParsingErrorPtr& error, size_t lineNumber, size_t colNumber, GdtfDefines::EGdtfParsingError errorType)
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

void GdtfValueBug::CheckChannelSet(VectorworksMVR::IGdtfDmxChannelSetPtr channelSet)
{

}
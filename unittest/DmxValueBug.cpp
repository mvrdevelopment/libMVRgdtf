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
        __checkVCOM(mode->GetDmxChannelAt(6, & channel));

        IGdtfDmxLogicalChannelPtr logicalChannel;
        __checkVCOM(channel->GetLogicalChannelAt(0, & logicalChannel));


        IGdtfDmxChannelFunctionPtr function;
        __checkVCOM(logicalChannel->GetDmxFunctionAt(3, & function));

        size_t countChannelSets = 0;
        __checkVCOM(function->GetDmxChannelSetCount(countChannelSets));
		this->checkifEqual("Check Count Channel Set", countChannelSets, size_t(2));


        for (size_t i = 0; i < countChannelSets; i++)
        {
            IGdtfDmxChannelSetPtr channelSet;
            __checkVCOM(function->GetDmxChannelSetAt(i,&channelSet));

            if(i==0) { CheckChannelSet(channelSet, "min Pulse", 108,206); }
            if(i==1) { CheckChannelSet(channelSet, "max Pulse", 207,207); }

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
        #ifndef DONT_USE_XERCES_AS_XMLLIB
		this->checkifEqual("colNumber ", 	thisColNumber, 	colNumber); 
        #endif
	}

	GdtfDefines::EGdtfParsingError thisErrorType;
	if(__checkVCOM(error->GetErrorType(thisErrorType))) { this->checkifEqual("errorType ", (Sint32)thisErrorType, (Sint32)errorType); }
}

void GdtfValueBug::CheckChannelSet(VectorworksMVR::IGdtfDmxChannelSetPtr& channelSet, std::string name, VectorworksMVR::GdtfDefines::DmxValue start, VectorworksMVR::GdtfDefines::DmxValue end)
{
	this->checkifEqual("Check Name ", name, channelSet->GetName());

	DmxValue thisStart = 0;
	__checkVCOM(channelSet->GetDmxStartAddress(thisStart));
	this->checkifEqual("Check Start ", start, thisStart);

	DmxValue thisEnd = 0;
	__checkVCOM(channelSet->GetDmxEndAddress(thisEnd));
	this->checkifEqual("Check End ",  end, thisEnd);
}
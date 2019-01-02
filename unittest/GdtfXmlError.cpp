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
    fPath += std::string("\\XMLBroken.gdtf");
#else
    fPath = std::string("/Users/moritzstaffel/Documents/DEV/libVectorworksMvrGdtf/unittest/files/XMLBroken.gdtf");
#endif


    std::cout << "Export File to" << fPath << std::endl; 
}

GdtfXmlErrorTest::~GdtfXmlErrorTest()
{
}

bool GdtfXmlErrorTest::ExecuteTest()
{
	std::cout << "=                                        GdtfErrorTest                                      =" << std::endl;
    ReadFile();

    return true;
}

void GdtfXmlErrorTest::ReadFile()
{
	//------------------------------------------------------------------------------    
	// Read Fixture Information
	IGdtfFixturePtr gdtfRead (IID_IGdtfFixture);
    __checkVCOMFailed(gdtfRead->ReadFromFile(fPath.c_str()));

	size_t countErrors = 0;
	__checkVCOM(gdtfRead->GetParsingErrorCount(countErrors));

	checkifEqual("Count Errors", countErrors, (size_t)1);

	
	for(size_t i = 0; i < countErrors; i++)
	{
		IGdtfXmlParsingErrorPtr error;
		__checkVCOM(gdtfRead->GetParsingErrorAt(i, & error));

		GdtfDefines::EGdtfParsingError type;
		__checkVCOM(error->GetErrorType(type));

		if(i == 0)
		{

		}

		if(i == 1)
		{

		}


		std::cout <<  "Error Code "<< (Sint32)type << std::endl;
	}
	
}
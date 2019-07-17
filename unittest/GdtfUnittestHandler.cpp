//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Unittest.h"

#include "Include/VectorworksMVR.h"
#include "GdtfUnittestHandler.h"
#include <iostream>

using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;


#define __checkVCOM(x) this->checkVCOM(x, #x)
#define __checkVCOM_NotSet(x) this->checkVCOM_NotSet(x, #x)

GdtfUnitTest::GdtfUnitTest(const std::string& currentDir)
{
	fPath = currentDir;
}

GdtfUnitTest::~GdtfUnitTest()
{  
}

bool GdtfUnitTest::ExecuteTest()
{
#ifdef _WINDOWS
    fPath += std::string("\\");
#else
    fPath += std::string("/");
#endif
	fPath += this->GetUnitTestName();
	fPath += std::string(".gdtf");

	std::cout << "=                              GdtfUnitTest::" << this->GetUnitTestName() << "                           " << std::endl;
	std::cout << "Export File to " << fPath << std::endl; 


	// Prepare Write Fixture
	IGdtfFixturePtr writeFixture (IID_IGdtfFixture);
	MvrUUID uuid (225204211, 177198167, 1575790, 96627);
    __checkVCOM(writeFixture->OpenForWrite(fPath.c_str(),"My FixtureName","My Manufacturer", uuid));
    WriteFile(writeFixture);
	__checkVCOM(writeFixture->Close());

	// Prepare Read Fixture
	IGdtfFixturePtr readFixture (IID_IGdtfFixture);
	__checkVCOM(readFixture->ReadFromFile(fPath.c_str()));
    ReadFile(readFixture);
	PrintParsingErrorList(readFixture);

    return true;
}



//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include "GdtfBufferTest.h"
#include <iostream>
#include "Utility.h"
#include "Include/VectorworksMVR.h"
using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;

#include <cstdio>

#ifdef GS_LIN
#include <unistd.h>
#include <stdio.h>
#endif


#define __checkVCOM(x) this->checkVCOM(x, #x)
#define __checkVCOM_NotSet(x) this->checkVCOM_NotSet(x, #x)


GdtfBufferTest::GdtfBufferTest(const std::string& currentDir)
{
	
}

GdtfBufferTest::~GdtfBufferTest()
{
}

bool GdtfBufferTest::ExecuteTest()
{
	std::cout << "=                                        GdtfBufferTest                                      =" << std::endl;

	std::string path 		= UnitTestUtil::GetTestResourceFolder() + kSeparator + "allWorking.gdtf";
	std::FILE*	gdtfFile 	= std::fopen( path.c_str(), "rb" );
	
	// Get Buffer
	size_t length = 0;
	if ( std::fseek( gdtfFile, 0, SEEK_END ) == 0 )
	{
		length = std::ftell( gdtfFile );
	}

	// Get Buffer
	char*  buffer  = new char[length + 1];
	if ( std::fseek( gdtfFile, 0, SEEK_SET ) == 0 )
	{
		std::fread( buffer, 1, length, gdtfFile );		
	}


	// Try to Read It
	IGdtfFixturePtr gdtfFixture (IID_IGdtfFixture);
	if(__checkVCOM(gdtfFixture->FromBuffer(buffer, length)))
	{
		checkifEqual("Name Fixture Type", "Alpha Spot QWO 800",  gdtfFixture->GetName());
	}

    return true;
}

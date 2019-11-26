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


    return true;
}

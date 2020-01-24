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


    }
    return true;
}

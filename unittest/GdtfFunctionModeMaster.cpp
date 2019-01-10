//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------

#include "Include/VectorworksMVR.h"
#include "GdtfFunctionModeMaster.h"
#include <iostream>

using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;


#define __checkVCOM(x) this->checkVCOM(x, #x)
#define __checkVCOM_NotSet(x) this->checkVCOM_NotSet(x, #x)

GdtfFunctionModeMasterTest::GdtfFunctionModeMasterTest(const std::string& currentDir) : GdtfUnitTest(currentDir)
{
}

GdtfFunctionModeMasterTest::~GdtfFunctionModeMasterTest()
{  
}


std::string GdtfFunctionModeMasterTest::GetUnitTestName()
{  
    return  std::string("GdtfFunctionModeMasterTest");
}

void GdtfFunctionModeMasterTest::WriteFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{  

}

void GdtfFunctionModeMasterTest::ReadFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{  

}

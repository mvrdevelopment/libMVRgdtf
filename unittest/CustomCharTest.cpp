//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------

#include "Include/VectorworksMVR.h"
#include "CustomCharTest.h"

using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;


#define __checkVCOM(x) this->checkVCOM(x, #x)
#define __checkVCOM_NotSet(x) this->checkVCOM_NotSet(x, #x)

GdtfCustomCharTest::GdtfCustomCharTest(const std::string& currentDir) : GdtfUnitTest(currentDir)
{
}

GdtfCustomCharTest::~GdtfCustomCharTest()
{  
}


std::string GdtfCustomCharTest::GetUnitTestName()
{  
    return  std::string("GdtfCustomCharTest");
}

void GdtfCustomCharTest::WriteFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{  

}

void GdtfCustomCharTest::ReadFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{  

}

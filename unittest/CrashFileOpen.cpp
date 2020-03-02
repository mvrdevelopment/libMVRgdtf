//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include "CrashFileOpen.h"
#include <iostream>
#include "Utility.h"
#include "Include/VectorworksMVR.h"
using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;


#define __checkVCOMFailed(x) this->checkVCOM_Failed(x, #x)

GdtfCrashFileOpen::GdtfCrashFileOpen(const std::string& currentDir)
{
}

GdtfCrashFileOpen::~GdtfCrashFileOpen()
{  
}

bool GdtfCrashFileOpen::ExecuteTest()
{
	std::cout << "=                         GdtfCrashFileOpen Unit Test                           =" << std::endl;

    std::string path = UnitTestUtil::GetTestResourceFolder() + kSeparator + "CrashWhileOpen.gdtf";

    IGdtfFixturePtr gdtfFile (IID_IGdtfFixture);

    if(__checkVCOMFailed(gdtfFile->ReadFromFile(path.c_str())))
    {

    }
    return true;
}

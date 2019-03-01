//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include <iostream>
#include "Include/VectorworksMVR.h"
#include "Unittest.h"
#include "MvrUnittest.h"
#include "GdtfUnittest.h"
#include "GdtfDmxUnittest.h"
#include "GdtfXmlError.h"
#include "GdtfFunctionModeMaster.h"
#include "Utility.h"
#include "EmptyGeometryUnitTest.h"
#include "CustomColorSpaceTest.h"




using namespace VectorworksMVR;					

int main(int argc, char* argv[])
{
	// Get Current dir    
    std::string base;   
    UnitTestUtil::GetFolderAppDataLocal( base);

	GdtfUnittest gdtfTest(base);
	bool gdtfFailed = gdtfTest.RunTest();

	GdtfDmxUnittest gdtfDmxTest(base);
	bool gdtfDmxFailed = gdtfDmxTest.RunTest();

	MvrUnittest mvrTest(base);
	bool mvrFailed = mvrTest.RunTest();

	GdtfXmlErrorTest errorTest(base);
	bool errorFailed = errorTest.RunTest();

	GdtfFunctionModeMasterTest modeMasterTest(base);
	bool modeMasterFailed = modeMasterTest.RunTest();

    GdtfEmptyModelTest test1 (base);
	bool test1_ok = test1.RunTest();

	GdtfCustomColorSpaceTest test2 (base);
	bool test2_ok = test2.RunTest();

    return  (mvrFailed || gdtfFailed || gdtfDmxFailed || errorFailed || modeMasterFailed || test1_ok || test2_ok);
}



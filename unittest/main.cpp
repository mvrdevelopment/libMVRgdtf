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
#include "EmptyAttributeTest.h"
#include "EmptyAttributeTest2.h"
#include "EmptyAttributeTest3.h"
#include "EmptyAttributeTest4.h"
#include "XmlConversionTest.h"



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

	EmptyAttributeTest test3 (base);
	bool test3_ok = test3.RunTest();

	EmptyAttributeTest2 test4 (base);
	bool test4_ok = test4.RunTest();

	EmptyAttributeTest3 test5 (base);
	bool test5_ok = test5.RunTest();

	EmptyAttributeTest4 test6 (base);
	bool test6_ok = test6.RunTest();

	XmlConversionTest test7 (base);
	bool test7_ok = test7.RunTest();

    return  (mvrFailed || gdtfFailed || gdtfDmxFailed || errorFailed || modeMasterFailed || test1_ok || test2_ok|| test3_ok || test4_ok || test5_ok || test6_ok || test7_ok);
}



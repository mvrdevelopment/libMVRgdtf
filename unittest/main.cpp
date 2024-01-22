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
#include "GdtfLineNumberParseErrorTest.h"
#include "Utility.h"
#include "EmptyGeometryUnitTest.h"
#include "CustomColorSpaceTest.h"
#include "EmptyAttributeTest.h"
#include "EmptyAttributeTest2.h"
#include "EmptyAttributeTest3.h"
#include "EmptyAttributeTest4.h"
#include "XmlConversionTest.h"
#include "CustomCharTest.h"
#include "UtilityTest.h"
#include "GetCountOfChannels.h"
#include "MacroTest.h"
#include "MvrXchange.h"
#include "DmxValueBug.h"
#include "DmxChannelSetBug.h"
#include "GdtfBufferTest.h"
#include "DmxChannelSetFormating.h"
#include "ChannelFunctionStartTest.h"
#include "CrashFileOpen.h"
#include "GdtfBufferWrite.h"
#include "GdtfRefreshBufferTest.h"
#include "GdtfVirtualChannelTest.h"

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

	GdtfCustomCharTest test8 (base);
	bool test8_ok = test8.RunTest();

	UtilityTest test9 (base);
	bool test9_ok = test9.RunTest();

	GdtfLineNumberParseErrorTest test10(base);
	bool test10_ok = test10.RunTest();

	GdtfGetCountOfLinkedChannelsForGeometry test11(base);
	bool test11_ok = test11.RunTest();

	GdtfMacroTest test12(base);
	bool test12_ok = test12.RunTest();

	GdtfValueBug test13(base);
	bool test13_ok = test13.RunTest();

	GdtfBufferTest test14(base);
	bool test14_ok = test14.RunTest();

	GdtfDmxChannelSetBug test15(base);
	bool test15_ok = test15.RunTest();

	DmxChannelSetFormatingTest test16(base);
	bool test16_ok = test16.RunTest();

	ChannelFunctionStartTest test17(base);
	bool test17_ok = test17.RunTest();

	GdtfCrashFileOpen test18(base);
	bool test18_ok = test18.RunTest();

	GdtfBufferWrite test19(base);
	bool test19_ok = test19.RunTest();

	GdtfRefreshBufferTest test20(base);
	bool test20_ok = test20.RunTest();

	GdtfVirtualChannelTest test21(base);
	bool test21_ok = test21.RunTest();

	MvrXChangeUnitTest test22(base);
	bool test22_ok = test22.RunTest();


    return  (mvrFailed || gdtfFailed || gdtfDmxFailed || errorFailed || modeMasterFailed || test1_ok || test2_ok|| test3_ok || test4_ok || test5_ok || test6_ok || test7_ok || test8_ok || test9_ok || test10_ok || test11_ok || test12_ok || test13_ok || test14_ok || test15_ok || test16_ok || test17_ok || test18_ok || test19_ok || test21_ok || test22_ok);
}



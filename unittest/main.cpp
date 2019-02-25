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



using namespace VectorworksMVR;					

int main(int argc, char* argv[])
{
	// Get Current dir    
    std::string gdtfBase = UnitTestUtil::GetFolderAppData_GdtfFolder();
    std::string mvrBase;   UnitTestUtil::GetFolderAppDataLocal( mvrBase);

    std::cout << "The gdtf base is: " << gdtfBase << std::endl; // XXX TEST
    std::cout << "The MVR base is:  " << mvrBase<< std::endl;   // XXX TEST

	GdtfUnittest gdtfTest(gdtfBase);
	bool gdtfFailed = gdtfTest.RunTest();

	GdtfDmxUnittest gdtfDmxTest(gdtfBase);
	bool gdtfDmxFailed = gdtfDmxTest.RunTest();

	MvrUnittest mvrTest(mvrBase);
	bool mvrFailed = mvrTest.RunTest();

	GdtfXmlErrorTest errorTest(gdtfBase);
	bool errorFailed = errorTest.RunTest();

	GdtfFunctionModeMasterTest modeMasterTest(gdtfBase);
	bool modeMasterFailed = modeMasterTest.RunTest();

    GdtfEmptyModelTest test1 (gdtfBase);
	bool test1_ok = test1.RunTest();

    return  (mvrFailed || gdtfFailed || gdtfDmxFailed || errorFailed || modeMasterFailed || test1_ok);
}



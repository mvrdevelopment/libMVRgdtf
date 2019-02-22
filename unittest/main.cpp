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


using namespace VectorworksMVR;					

int main(int argc, char* argv[])
{
	// Get Current dir    
	std::string base; UnitTestUtil::GetFolderAppDataPath(base);

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
    
    bool errorOcurred = (mvrFailed || gdtfFailed || gdtfDmxFailed || errorFailed || modeMasterFailed);

    if (! errorOcurred) 
    {
        UnitTestUtil::print_Ascii_DEER();
    }
    else 
    {
        UnitTestUtil::print_Ascii_BUG();        
    }

    return errorOcurred;
}



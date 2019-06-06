//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include "UtilityTest.h"
#include <iostream>

#include "Include/VectorworksMVR.h"
using namespace VectorworksMVR;


UtilityTest::UtilityTest(const std::string& currentDir)
{
}

UtilityTest::~UtilityTest()
{
}

bool UtilityTest::ExecuteTest()
{
	std::cout << "=                                        UtilTest                                       =" << std::endl;

	IIUtilityPtr util (IID_IUtility);

    return true;
}

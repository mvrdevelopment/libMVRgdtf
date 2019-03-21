//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include "XmlConversionTest.h"
#include <iostream>

#include "Prefix/StdAfx.h"
#include "XmlFileHelper.h"

using namespace SceneData;
using namespace VectorworksMVR::GdtfDefines;

XmlConversionTest::XmlConversionTest(const std::string& currentDir)
{
}

XmlConversionTest::~XmlConversionTest()
{
}

bool XmlConversionTest::ExecuteTest()
{
	std::cout << "=                                        XmlConversionTest                             =" << std::endl;
    RunTests();

    return true;
}

void XmlConversionTest::RunTests()
{
	GdtfConverter::ConvertDMXValue(15, EGdtfChannelBitResolution::eGdtfChannelBitResolution_8);
}

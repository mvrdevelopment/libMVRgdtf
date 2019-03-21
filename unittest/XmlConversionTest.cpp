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

void CheckDmxValue(const char* string, DmxValue result, EGdtfChannelBitResolution targetResolution, XmlConversionTest* ref)
{
	DmxValue value = 0;
	ref->checkifTrue("DMX Conversion faild" ,GdtfConverter::ConvertDMXValue(string, nullptr, targetResolution, value) );
	ref->checkifEqual("DmxValue", value, result);
};

void XmlConversionTest::RunTests()
{
	CheckDmxValue("255/1", 255, EGdtfChannelBitResolution::eGdtfChannelBitResolution_8, this);
}

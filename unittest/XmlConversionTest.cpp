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
	std::cout << "=                                        XmlConversionTest                                 =" << std::endl;
    RunTests();

    return true;
}

void CheckDmxValue(const char* string, DmxValue result, EGdtfChannelBitResolution targetResolution, XmlConversionTest* ref)
{
#ifndef _WINDOWS
	DmxValue value = 0;
	ref->checkifTrue("DMX Conversion failed" ,GdtfConverter::ConvertDMXValue(string, nullptr, targetResolution, value) );
	ref->checkifEqual("DmxValue", value, result);
#endif
};

void XmlConversionTest::RunTests()
{
	// Full Range
	CheckDmxValue("255/1", 255, 					EGdtfChannelBitResolution::eGdtfChannelBitResolution_8,  this);
	CheckDmxValue("255/1", 255*256, 				EGdtfChannelBitResolution::eGdtfChannelBitResolution_16, this);
	CheckDmxValue("255/1", 255*256*256, 			EGdtfChannelBitResolution::eGdtfChannelBitResolution_24, this);
	CheckDmxValue("255/1", long(255)*256*256*256, 	EGdtfChannelBitResolution::eGdtfChannelBitResolution_32, this);

	
	CheckDmxValue("65535/2", 255, 					EGdtfChannelBitResolution::eGdtfChannelBitResolution_8,  this);
	CheckDmxValue("65535/2", 65535, 				EGdtfChannelBitResolution::eGdtfChannelBitResolution_16, this);
	CheckDmxValue("65535/2", 65535*256, 			EGdtfChannelBitResolution::eGdtfChannelBitResolution_24, this);
	CheckDmxValue("65535/2", long(65535)*256*256, 	EGdtfChannelBitResolution::eGdtfChannelBitResolution_32, this);

	CheckDmxValue("16777215/3", 255, 				EGdtfChannelBitResolution::eGdtfChannelBitResolution_8,  this);
	CheckDmxValue("16777215/3", 65535, 				EGdtfChannelBitResolution::eGdtfChannelBitResolution_16, this);
	CheckDmxValue("16777215/3", 16777215, 			EGdtfChannelBitResolution::eGdtfChannelBitResolution_24, this);
	CheckDmxValue("16777215/3", long(16777215)*256, EGdtfChannelBitResolution::eGdtfChannelBitResolution_32, this);

	CheckDmxValue("4294967295/4", 255, 			EGdtfChannelBitResolution::eGdtfChannelBitResolution_8,  this);
	CheckDmxValue("4294967295/4", 65535, 		EGdtfChannelBitResolution::eGdtfChannelBitResolution_16, this);
	CheckDmxValue("4294967295/4", 16777215, 	EGdtfChannelBitResolution::eGdtfChannelBitResolution_24, this);
	CheckDmxValue("4294967295/4", 4294967295, 	EGdtfChannelBitResolution::eGdtfChannelBitResolution_32, this);

	// First Value
	CheckDmxValue("1/1", 1, 			EGdtfChannelBitResolution::eGdtfChannelBitResolution_8,  this);
	CheckDmxValue("1/1", 256, 			EGdtfChannelBitResolution::eGdtfChannelBitResolution_16, this);
	CheckDmxValue("1/1", 256*256, 		EGdtfChannelBitResolution::eGdtfChannelBitResolution_24, this);
	CheckDmxValue("1/1", 256*256*256, 	EGdtfChannelBitResolution::eGdtfChannelBitResolution_32, this);

}

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

void CheckDmxAddress(const char* string, DMXAddress result, XmlConversionTest* ref)
{
#ifndef _WINDOWS
	DMXAddress value = 0;
	ref->checkifTrue("DMX Address Conversion failed", GdtfConverter::ConvertDMXAdress(string, nullptr, value) );
	ref->checkifEqual("DmxAddress", value, result);
#endif
};


void XmlConversionTest::RunTests()
{
	//----------------------------------------------------------------------------------------------------------
	//Byte Mirroring

	// Full Range
	CheckDmxValue("255/1", 255, 		EGdtfChannelBitResolution::eGdtfChannelBitResolution_8,  this); // 							  11111111
	CheckDmxValue("255/1", 65535, 		EGdtfChannelBitResolution::eGdtfChannelBitResolution_16, this); // 					 11111111 11111111
	CheckDmxValue("255/1", 16777215, 	EGdtfChannelBitResolution::eGdtfChannelBitResolution_24, this); // 			11111111 11111111 11111111
	CheckDmxValue("255/1", 4294967295, 	EGdtfChannelBitResolution::eGdtfChannelBitResolution_32, this); // 11111111 11111111 11111111 11111111

	CheckDmxValue("65535/2", 255, 			EGdtfChannelBitResolution::eGdtfChannelBitResolution_8,  this); // 							  11111111
	CheckDmxValue("65535/2", 65535, 		EGdtfChannelBitResolution::eGdtfChannelBitResolution_16, this); // 					 11111111 11111111
	CheckDmxValue("65535/2", 16777215, 		EGdtfChannelBitResolution::eGdtfChannelBitResolution_24, this); // 			11111111 11111111 11111111
	CheckDmxValue("65535/2", 4294967295, 	EGdtfChannelBitResolution::eGdtfChannelBitResolution_32, this); // 11111111 11111111 11111111 11111111

	CheckDmxValue("16777215/3", 255, 		EGdtfChannelBitResolution::eGdtfChannelBitResolution_8,  this); // 							  11111111
	CheckDmxValue("16777215/3", 65535, 		EGdtfChannelBitResolution::eGdtfChannelBitResolution_16, this); // 					 11111111 11111111
	CheckDmxValue("16777215/3", 16777215, 	EGdtfChannelBitResolution::eGdtfChannelBitResolution_24, this); // 			11111111 11111111 11111111
	CheckDmxValue("16777215/3", 4294967295, EGdtfChannelBitResolution::eGdtfChannelBitResolution_32, this); // 11111111 11111111 11111111 11111111

	CheckDmxValue("4294967295/4", 255, 			EGdtfChannelBitResolution::eGdtfChannelBitResolution_8,  this); // 							  11111111
	CheckDmxValue("4294967295/4", 65535, 		EGdtfChannelBitResolution::eGdtfChannelBitResolution_16, this); // 					 11111111 11111111
	CheckDmxValue("4294967295/4", 16777215, 	EGdtfChannelBitResolution::eGdtfChannelBitResolution_24, this); // 			11111111 11111111 11111111
	CheckDmxValue("4294967295/4", 4294967295, 	EGdtfChannelBitResolution::eGdtfChannelBitResolution_32, this); // 11111111 11111111 11111111 11111111

	// First Value
	CheckDmxValue("1/1", 1, 		EGdtfChannelBitResolution::eGdtfChannelBitResolution_8,  this); // 							  00000001
	CheckDmxValue("1/1", 257, 		EGdtfChannelBitResolution::eGdtfChannelBitResolution_16, this); // 					 00000001 00000001
	CheckDmxValue("1/1", 65793, 	EGdtfChannelBitResolution::eGdtfChannelBitResolution_24, this); // 			00000001 00000001 00000001
	CheckDmxValue("1/1", 16843009, 	EGdtfChannelBitResolution::eGdtfChannelBitResolution_32, this); // 00000001 00000001 00000001 00000001

	//----------------------------------------------------------------------------------------------------------
	//Byte Shifting

	// Full Range
	CheckDmxValue("255/1s", 255, 		EGdtfChannelBitResolution::eGdtfChannelBitResolution_8,  this); // 							  11111111
	CheckDmxValue("255/1s", 65280, 		EGdtfChannelBitResolution::eGdtfChannelBitResolution_16, this);	// 					 11111111 00000000
	CheckDmxValue("255/1s", 16711680, 	EGdtfChannelBitResolution::eGdtfChannelBitResolution_24, this);	// 			11111111 00000000 00000000
	CheckDmxValue("255/1s", 4278190080, EGdtfChannelBitResolution::eGdtfChannelBitResolution_32, this); // 11111111 00000000 00000000 00000000

	CheckDmxValue("65535/2s", 255, 			EGdtfChannelBitResolution::eGdtfChannelBitResolution_8,  this); // 							  11111111
	CheckDmxValue("65535/2s", 65535, 		EGdtfChannelBitResolution::eGdtfChannelBitResolution_16, this); // 					 11111111 11111111
	CheckDmxValue("65535/2s", 16776960, 	EGdtfChannelBitResolution::eGdtfChannelBitResolution_24, this);	// 			11111111 11111111 00000000
	CheckDmxValue("65535/2s", 4294901760, 	EGdtfChannelBitResolution::eGdtfChannelBitResolution_32, this); // 11111111 11111111 00000000 00000000

	CheckDmxValue("16777215/3s", 255, 			EGdtfChannelBitResolution::eGdtfChannelBitResolution_8,  this); // 							  11111111
	CheckDmxValue("16777215/3s", 65535, 		EGdtfChannelBitResolution::eGdtfChannelBitResolution_16, this); // 					 11111111 11111111
	CheckDmxValue("16777215/3s", 16777215, 		EGdtfChannelBitResolution::eGdtfChannelBitResolution_24, this); // 			11111111 11111111 11111111
	CheckDmxValue("16777215/3s", 4294967040,	EGdtfChannelBitResolution::eGdtfChannelBitResolution_32, this); // 11111111 11111111 11111111 00000000

	CheckDmxValue("4294967295/4s", 255, 		EGdtfChannelBitResolution::eGdtfChannelBitResolution_8,  this); // 							  11111111
	CheckDmxValue("4294967295/4s", 65535, 		EGdtfChannelBitResolution::eGdtfChannelBitResolution_16, this); // 					 11111111 11111111
	CheckDmxValue("4294967295/4s", 16777215, 	EGdtfChannelBitResolution::eGdtfChannelBitResolution_24, this); // 			11111111 11111111 11111111
	CheckDmxValue("4294967295/4s", 4294967295, 	EGdtfChannelBitResolution::eGdtfChannelBitResolution_32, this); // 11111111 11111111 11111111 11111111

	// First Value
	CheckDmxValue("1/1s", 1, 		EGdtfChannelBitResolution::eGdtfChannelBitResolution_8,  this); // 							  00000001
	CheckDmxValue("1/1s", 256, 		EGdtfChannelBitResolution::eGdtfChannelBitResolution_16, this); // 					 00000001 00000000
	CheckDmxValue("1/1s", 65536, 	EGdtfChannelBitResolution::eGdtfChannelBitResolution_24, this); // 			00000001 00000000 00000000
	CheckDmxValue("1/1s", 16777216, EGdtfChannelBitResolution::eGdtfChannelBitResolution_32, this); // 00000001 00000000 00000000 00000000


	CheckDmxAddress("15", 15, this);
	CheckDmxAddress("2.128", 640, this);
	CheckDmxAddress("5.17", 2065, this);
	CheckDmxAddress("1035", 1035, this);
}

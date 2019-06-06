//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include "UtilityTest.h"
#include <iostream>

#include "Include/VectorworksMVR.h"
using namespace VectorworksMVR;
#define __checkVCOM(x) checkVCOM(x, #x)


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

	RGBColor rgb;
	rgb.r = 255;
	rgb.g = 255;
	rgb.b = 255;
	CieColor cie;
	__checkVCOM(util->RgBToCie(rgb, cie));
	__checkVCOM(util->CieToRgb(cie, rgb));

	this->checkifEqual("R", rgb.r, (Uint8)255 );
	this->checkifEqual("G", rgb.g, (Uint8)255 );
	this->checkifEqual("B", rgb.b, (Uint8)255 );

    return true;
}

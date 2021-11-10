//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------

#include "Include/VectorworksMVR.h"
#include "CustomColorSpaceTest.h"

using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;


#define __checkVCOM(x) this->checkVCOM(x, #x)
#define __checkVCOM_NotSet(x) this->checkVCOM_NotSet(x, #x)

GdtfCustomColorSpaceTest::GdtfCustomColorSpaceTest(const std::string& currentDir) : GdtfUnitTest(currentDir)
{
}

GdtfCustomColorSpaceTest::~GdtfCustomColorSpaceTest()
{  
}


std::string GdtfCustomColorSpaceTest::GetUnitTestName()
{  
    return  std::string("GdtfCustomColorSpace");
}

void GdtfCustomColorSpaceTest::WriteFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{  
    IGdtfColorSpacePtr colorSpace;
    __checkVCOM(fixture->GetColorSpace(&colorSpace));

    __checkVCOM(colorSpace->SetName("My ColorSpace"));

   __checkVCOM(colorSpace->SetColorSpace(EGdtfColorSpace::Custom));
    	
    CieColor in_Red;	in_Red.fx   = 1; 	in_Red.fy   = 2;	in_Red.f_Y   = 3;
    CieColor in_Green;	in_Green.fx = 4;	in_Green.fy = 5; 	in_Green.f_Y = 6;
    CieColor in_Blue;	in_Blue.fx  = 7; 	in_Blue.fy  = 8; 	in_Blue.f_Y  = 9;
    CieColor in_White;	in_White.fx = 10; 	in_White.fy = 11;	in_White.f_Y = 12;

    __checkVCOM(colorSpace->SetRed(in_Red));
    __checkVCOM(colorSpace->SetGreen(in_Green));
    __checkVCOM(colorSpace->SetBlue(in_Blue));
    __checkVCOM(colorSpace->SetWhite(in_White));

}

void GdtfCustomColorSpaceTest::ReadFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{  
    IGdtfColorSpacePtr colorSpace;
    __checkVCOM(fixture->GetColorSpace(&colorSpace));

    checkifEqual("ColorSpace Name", colorSpace->GetName(), "My ColorSpace");

    EGdtfColorSpace colorSpaceEnum;
   __checkVCOM(colorSpace->GetColorSpace(colorSpaceEnum));
   	checkifEqual("ColorSpace", (size_t)colorSpaceEnum, (size_t)EGdtfColorSpace::Custom);
    	
    CieColor out_Red;		
    CieColor out_Green;	
    CieColor out_Blue;	
    CieColor out_White;	

    __checkVCOM(colorSpace->GetRed(out_Red));
    __checkVCOM(colorSpace->GetGreen(out_Green));
    __checkVCOM(colorSpace->GetBlue(out_Blue));
    __checkVCOM(colorSpace->GetWhite(out_White));

    CieColor in_Red;	in_Red.fx   = 1; 	in_Red.fy   = 2;	in_Red.f_Y   = 3;
    CieColor in_Green;	in_Green.fx = 4;	in_Green.fy = 5; 	in_Green.f_Y = 6;
    CieColor in_Blue;	in_Blue.fx  = 7; 	in_Blue.fy  = 8; 	in_Blue.f_Y  = 9;
    CieColor in_White;	in_White.fx = 10; 	in_White.fy = 11;	in_White.f_Y = 12;


    checkifEqual("Custom Color Red", 	in_Red, 	out_Red);
    checkifEqual("Custom Color Green", 	in_Green, 	out_Green);
    checkifEqual("Custom Color Blue", 	in_Blue, 	out_Blue);
    checkifEqual("Custom Color White", 	in_White,	out_White);

}

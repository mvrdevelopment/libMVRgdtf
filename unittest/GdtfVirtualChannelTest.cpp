//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include "GdtfVirtualChannelTest.h"
#include "Utility.h"
#include <iostream>

#include "Include/VectorworksMVR.h"
using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;


#define __checkVCOM(x) this->checkVCOM(x, #x)
#define __checkVCOM_NotSet(x) this->checkVCOM_NotSet(x, #x)

GdtfVirtualChannelTest::GdtfVirtualChannelTest(const std::string& currentDir)
{
	fPath = UnitTestUtil::GetTestResourceFolder() + kSeparator + "virtual_channel.gdtf";

    std::cout << "Read File from " << fPath << std::endl; 
}

GdtfVirtualChannelTest::~GdtfVirtualChannelTest()
{
}

bool GdtfVirtualChannelTest::ExecuteTest()
{
	std::cout << "=                                     GdtfVirtualChannelTest                           =" << std::endl;
    ReadFile();

    return true;
}

void GdtfVirtualChannelTest::ReadFile()
{
	//------------------------------------------------------------------------------------------------
	// Create Pointer to GDTF Interface from MVR file
	IGdtfFixturePtr gdtfRead (IID_IGdtfFixture);
	if(__checkVCOM(gdtfRead->ReadFromFile(fPath.c_str())))
    {
		

				IGdtfDmxModePtr mode;
				__checkVCOM(gdtfRead->GetDmxModeAt(0, &mode));
				
				size_t countChannels2 = 0;
				__checkVCOM(mode->GetDmxChannelCount(countChannels2));
				this->checkifEqual("Check Count DMX Channels 2", countChannels2, size_t(3));

				size_t footprint = 0;
				__checkVCOM(mode->GetFootprintForBreak(1, footprint));
				this->checkifEqual("Check the footprint1", footprint, size_t(2));

	
	}
	    
}

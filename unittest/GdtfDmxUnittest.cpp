//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include "GdtfDmxUnittest.h"
#include <iostream>

#include "Include/VectorworksMVR.h"
using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;


#define __checkVCOM(x) this->checkVCOM(x, #x)

GdtfDmxUnittest::GdtfDmxUnittest(const std::string& currentDir)
{
    fPath = currentDir;
    fPath += std::string("/testDmx.gdtf");

    std::cout << "Export File to" << fPath << std::endl; 
}

GdtfDmxUnittest::~GdtfDmxUnittest()
{
    
}

bool GdtfDmxUnittest::ExecuteTest()
{
	std::cout << "=                                     GdtfUnittest DMX Unit Test                           =" << std::endl;
    WriteFile();
    ReadFile();

    return true;
}

void GdtfDmxUnittest::WriteFile()
{
	//------------------------------------------------------------------------------------------------
	// Create Pointer to GDTF Interface
	IGdtfFixturePtr gdtfWrite (IID_IGdtfFixture);

    MvrUUID uuid (225204211, 177198167, 1575790, 96627);
    if(__checkVCOM(gdtfWrite->OpenForWrite(fPath.c_str(),"My FixtureName","My Manufacturer", uuid)))
    {
		//----------------------------------------------------------------
		// Create Model
		IGdtfModelPtr model;
		__checkVCOM(gdtfWrite->CreateModel("Model", &model));

		IGdtfGeometryPtr geometry;
		__checkVCOM(gdtfWrite->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "Geometry", model, STransformMatrix(), &geometry));

		IGdtfDmxModePtr mode;
		__checkVCOM(gdtfWrite->CreateDmxMode("Mode", &mode));
		__checkVCOM(mode->SetGeometry(geometry));

		//----------------------------------------------------------------
		// Write 8 bit Channel
		IGdtfDmxChannelPtr bit8channel;
		__checkVCOM(mode->CreateDmxChannel("8bit Channel", &bit8channel));
		bit8channel->SetCoarse(1);

		IGdtfDmxLogicalChannelPtr bit8LogicalChannel;
		bit8channel->CreateLogicalChannel("Log1", &bit8LogicalChannel);

		IGdtfDmxChannelFunctionPtr bit8Function;
		bit8LogicalChannel->CreateDmxFunction("Function", &bit8Function);

		IGdtfDmxChannelSetPtr bit8ChannelSet1;
		bit8Function->CreateDmxChannelSet("My Name", 15, 60, &bit8ChannelSet1);

		IGdtfDmxChannelSetPtr bit8ChannelSet2;
		bit8Function->CreateDmxChannelSet("My Name", 61, 90, &bit8ChannelSet2);

		IGdtfDmxChannelSetPtr bit8ChannelSet3;
		bit8Function->CreateDmxChannelSet("My Name", 128, 230, &bit8ChannelSet3);


        __checkVCOM(gdtfWrite->Close());
    }
}

void GdtfDmxUnittest::ReadFile()
{
	//------------------------------------------------------------------------------------------------
	// Create Pointer to GDTF Interface
    IGdtfFixturePtr gdtfRead (IID_IGdtfFixture);
    if(__checkVCOM(gdtfRead->ReadFromFile(fPath.c_str())))
    {
		//------------------------------------------------------------------
		// Get DMX Mode
		size_t countDmxModes;
		__checkVCOM(gdtfRead->GetDmxModeCount(countDmxModes));
		this->checkifEqual("Check Count DMX Modes", 1, countDmxModes);

		IGdtfDmxModePtr mode;
		__checkVCOM(gdtfRead->GetDmxModeAt(0, &mode));

		size_t countChannels = 0;
		__checkVCOM(mode->GetDmxChannelCount(countChannels));
		this->checkifEqual("Check Count DMX Channels", 1, countChannels);
		

		//----------------------------------------------------------------
		// Write 8 bit Channel
		IGdtfDmxChannelPtr bit8channel;
		__checkVCOM(mode->GetDmxChannelAt(0, &bit8channel));

		IGdtfDmxLogicalChannelPtr bit8LogicalChannel;
		__checkVCOM(bit8channel->GetLogicalChannelAt(0, &bit8LogicalChannel));

		IGdtfDmxChannelFunctionPtr bit8Function;
		__checkVCOM(bit8LogicalChannel->GetDmxFunctionAt(0, &bit8Function));

		// Check DMX Channel Sets
		size_t countChannelSets = 0;
		__checkVCOM(bit8Function->GetDmxChannelSetCount(countChannelSets));
		this->checkifEqual("Check Count DMX Channels", 6, countChannelSets);

		IGdtfDmxChannelSetPtr bit8ChannelSet1;
		__checkVCOM(bit8Function->GetDmxChannelSetAt(0, &bit8ChannelSet1));

		IGdtfDmxChannelSetPtr bit8ChannelSet2;
		__checkVCOM(bit8Function->GetDmxChannelSetAt(1, &bit8ChannelSet2));

		IGdtfDmxChannelSetPtr bit8ChannelSet3;
		__checkVCOM(bit8Function->GetDmxChannelSetAt(2, &bit8ChannelSet3));

		IGdtfDmxChannelSetPtr bit8ChannelSet4;
		__checkVCOM(bit8Function->GetDmxChannelSetAt(3, &bit8ChannelSet4));

		IGdtfDmxChannelSetPtr bit8ChannelSet5;
		__checkVCOM(bit8Function->GetDmxChannelSetAt(4, &bit8ChannelSet5));

		IGdtfDmxChannelSetPtr bit8ChannelSet6;
		__checkVCOM(bit8Function->GetDmxChannelSetAt(5, &bit8ChannelSet6));


	}

}
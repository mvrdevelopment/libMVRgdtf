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
		__checkVCOM(bit8channel->SetGeometry(geometry));
		bit8channel->SetCoarse(1);

		// First Logical Channel
		IGdtfDmxLogicalChannelPtr bit8LogicalChannel1;
		bit8channel->CreateLogicalChannel("Log1", &bit8LogicalChannel1);

		IGdtfDmxChannelFunctionPtr bit8Function1;
		bit8LogicalChannel1->CreateDmxFunction("Function1", &bit8Function1);
		bit8Function1->SetStartAddress(0);

		IGdtfDmxChannelSetPtr bit8ChannelSet1;
		bit8Function1->CreateDmxChannelSet("My Name1", 15, 60, &bit8ChannelSet1);

		IGdtfDmxChannelSetPtr bit8ChannelSet2;
		bit8Function1->CreateDmxChannelSet("My Name2", 61, 90, &bit8ChannelSet2);

		IGdtfDmxChannelSetPtr bit8ChannelSet3;
		bit8Function1->CreateDmxChannelSet("My Name3", 91, 92, &bit8ChannelSet3);

		// Second Channel Function
		IGdtfDmxChannelFunctionPtr bit8Function2;
		bit8LogicalChannel1->CreateDmxFunction("Function2", &bit8Function2);
		bit8Function2->SetStartAddress(100);

		IGdtfDmxChannelSetPtr bit8ChannelSet4;
		bit8Function2->CreateDmxChannelSet("My Name4", 100, 120, &bit8ChannelSet4);

		IGdtfDmxChannelSetPtr bit8ChannelSet5;
		bit8Function2->CreateDmxChannelSet("My Name5", 121, 130, &bit8ChannelSet5);

		IGdtfDmxChannelSetPtr bit8ChannelSet6;
		bit8Function2->CreateDmxChannelSet("My Name6", 160, 165, &bit8ChannelSet6);

		// Second Logical Channel
		IGdtfDmxLogicalChannelPtr bit8LogicalChannel2;
		bit8channel->CreateLogicalChannel("Log2", &bit8LogicalChannel2);

		IGdtfDmxChannelFunctionPtr bit8Function3;
		bit8LogicalChannel2->CreateDmxFunction("Function3", &bit8Function3);
		bit8Function3->SetStartAddress(170);

		IGdtfDmxChannelSetPtr bit8ChannelSet7;
		bit8Function3->CreateDmxChannelSet("My Name7", 170, 170, &bit8ChannelSet7);

		IGdtfDmxChannelSetPtr bit8ChannelSet8;
		bit8Function3->CreateDmxChannelSet("My Name8", 180, 180, &bit8ChannelSet8);

		IGdtfDmxChannelSetPtr bit8ChannelSet9;
		bit8Function3->CreateDmxChannelSet("My Name9", 181, 198, &bit8ChannelSet9);

		// Second Channel Function
		IGdtfDmxChannelFunctionPtr bit8Function4;
		bit8LogicalChannel2->CreateDmxFunction("Function4", &bit8Function4);
		bit8Function4->SetStartAddress(200);

		IGdtfDmxChannelSetPtr bit8ChannelSet10;
		bit8Function4->CreateDmxChannelSet("My Name10", 210, 210, &bit8ChannelSet10);

		IGdtfDmxChannelSetPtr bit8ChannelSet11;
		bit8Function4->CreateDmxChannelSet("My Name11", 220, 225, &bit8ChannelSet11);

		IGdtfDmxChannelSetPtr bit8ChannelSet12;
		bit8Function4->CreateDmxChannelSet("My Name12", 200, 255, &bit8ChannelSet12);

		//----------------------------------------------------------------
		// Write 16 bit Channel
		IGdtfDmxChannelPtr bit16channel;
		__checkVCOM(mode->CreateDmxChannel("8bit Channel", &bit16channel));
		__checkVCOM(bit16channel->SetGeometry(geometry));
		bit16channel->SetCoarse(1);
		bit16channel->SetFine(2);

		IGdtfDmxLogicalChannelPtr bit16LogicalChannel;
		bit16channel->CreateLogicalChannel("Log1", &bit16LogicalChannel);

		IGdtfDmxChannelFunctionPtr bit16Function;
		bit16LogicalChannel->CreateDmxFunction("Function", &bit16Function);

		IGdtfDmxChannelSetPtr bit16ChannelSet1;
		bit16Function->CreateDmxChannelSet("My Name1", 15, 60, &bit16ChannelSet1);

		IGdtfDmxChannelSetPtr bit16ChannelSet;
		bit16Function->CreateDmxChannelSet("My Name2", 61, 90, &bit16ChannelSet);

		IGdtfDmxChannelSetPtr bit16ChannelSet3;
		bit16Function->CreateDmxChannelSet("My Name3", 128, 4501, &bit16ChannelSet3);


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
		this->checkifEqual("Check Count DMX Channels", 2, countChannels);
		

		//----------------------------------------------------------------
		// Read 8 bit Channel
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



		//----------------------------------------------------------------
		// Read 16 bit Channel
		IGdtfDmxChannelPtr bit16channel;
		__checkVCOM(mode->GetDmxChannelAt(1, &bit16channel));

		IGdtfDmxLogicalChannelPtr bit16LogicalChannel;
		__checkVCOM(bit16channel->GetLogicalChannelAt(0, &bit16LogicalChannel));

		IGdtfDmxChannelFunctionPtr bit16Function;
		__checkVCOM(bit16LogicalChannel->GetDmxFunctionAt(0, &bit16Function));

		// Check DMX Channel Sets
		__checkVCOM(bit16Function->GetDmxChannelSetCount(countChannelSets));
		this->checkifEqual("Check Count DMX Channels", 6, countChannelSets);

		IGdtfDmxChannelSetPtr bit16ChannelSet1;
		__checkVCOM(bit16Function->GetDmxChannelSetAt(0, &bit16ChannelSet1)); 
		this->CheckChannelSet(bit16ChannelSet1, "",0,14);

		IGdtfDmxChannelSetPtr bit16ChannelSet2;
		__checkVCOM(bit16Function->GetDmxChannelSetAt(1, &bit16ChannelSet2));
		this->CheckChannelSet(bit16ChannelSet2, "My Name1",15,60);

		IGdtfDmxChannelSetPtr bit16ChannelSet3;
		__checkVCOM(bit16Function->GetDmxChannelSetAt(2, &bit16ChannelSet3));
		this->CheckChannelSet(bit16ChannelSet3, "My Name2",61,90);

		IGdtfDmxChannelSetPtr bit16ChannelSet4;
		__checkVCOM(bit16Function->GetDmxChannelSetAt(3, &bit16ChannelSet4));
		this->CheckChannelSet(bit16ChannelSet4, "",91,127);

		IGdtfDmxChannelSetPtr bit16ChannelSet5;
		__checkVCOM(bit16Function->GetDmxChannelSetAt(4, &bit16ChannelSet5));
		this->CheckChannelSet(bit16ChannelSet5, "My Name3",128,4501);

		IGdtfDmxChannelSetPtr bit16ChannelSet6;
		__checkVCOM(bit16Function->GetDmxChannelSetAt(5, &bit16ChannelSet6));
		this->CheckChannelSet(bit16ChannelSet6, "",4502,65535);

	}

}

void GdtfDmxUnittest::CheckChannelSet(IGdtfDmxChannelSetPtr& channelSet, std::string name, DmxValue start, DmxValue end)
{
	this->checkifEqual("Check Name ", name, channelSet->GetName());

	DmxValue thisStart = 0;
	__checkVCOM(channelSet->GetDmxStartAddress(thisStart));
	this->checkifEqual("Check Start ", start, thisStart);

	DmxValue thisEnd = 0;
	__checkVCOM(channelSet->GetDmxEndAddress(thisEnd));
	this->checkifEqual("Check End ",  end, thisEnd);
}
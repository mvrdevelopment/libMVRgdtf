//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------

#include "Include/VectorworksMVR.h"
#include "DmxChannelSetFormating.h"
#include "Utility.h"


using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;


#define __checkVCOM(x) this->checkVCOM(x, #x)
#define __checkVCOM_NotSet(x) this->checkVCOM_NotSet(x, #x)

DmxChannelSetFormatingTest::DmxChannelSetFormatingTest(const std::string& currentDir) : GdtfUnitTest(currentDir)
{
}

DmxChannelSetFormatingTest::~DmxChannelSetFormatingTest()
{  
}


std::string DmxChannelSetFormatingTest::GetUnitTestName()
{  
    return  std::string("DmxChannelSetFormatingTest");
}

void DmxChannelSetFormatingTest::WriteFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{  
		// Feature Groups
		IGdtfFeatureGroupPtr featureGroup;
		__checkVCOM(fixture->CreateFeatureGroup("FeatureGroup","FeatureGroup", &featureGroup));


		IGdtfFeaturePtr feature;
		__checkVCOM(featureGroup->CreateFeature("Feature", & feature));

		//----------------------------------------------------------------
		// Create Attribute
		IGdtfAttributePtr attribute1;
		__checkVCOM(fixture->CreateAttribute("Attribute1","Pretty", &attribute1));
		attribute1->SetFeature(feature);


		//----------------------------------------------------------------
		// Create Geometry
		IGdtfModelPtr model;
		__checkVCOM(fixture->CreateModel("Model", &model));

		IGdtfGeometryPtr geometry;
		__checkVCOM(fixture->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "Geometry", model, STransformMatrix(), &geometry));


        //----------------------------------------------------------------
		// Create Geometry
		IGdtfDmxModePtr mode;
		__checkVCOM(fixture->CreateDmxMode("Mode", &mode));
		__checkVCOM(mode->SetGeometry(geometry));



        //----------------------------------------------------------------
		// Write 8 bit Channel
		IGdtfDmxChannelPtr bit8channel;
		__checkVCOM(mode->CreateDmxChannel(geometry, &bit8channel));
		__checkVCOM(bit8channel->SetGeometry(geometry));
		bit8channel->SetCoarse(1);
        bit8channel->SetFine(2);

		// First Logical Channel
		IGdtfDmxLogicalChannelPtr bit8LogicalChannel1;
		bit8channel->CreateLogicalChannel(attribute1, &bit8LogicalChannel1);
		bit8LogicalChannel1->SetAttribute(attribute1);
		

		IGdtfDmxChannelFunctionPtr bit8Function4;
		bit8LogicalChannel1->CreateDmxFunction("Function4", &bit8Function4);
		bit8Function4->SetStartAddress(0);
		bit8Function4->SetAttribute(attribute1);

		IGdtfDmxChannelFunctionPtr bit8Function1;
		bit8LogicalChannel1->CreateDmxFunction("Function1", &bit8Function1);
		bit8Function1->SetStartAddress(600);
		bit8Function1->SetAttribute(attribute1);

		IGdtfDmxChannelSetPtr bit8ChannelSet1;
		bit8Function1->CreateDmxChannelSet("My Name1", 600, 600, &bit8ChannelSet1);
		bit8Function1->CreateDmxChannelSet("My Name1", 601, 32130, &bit8ChannelSet1);
		bit8Function1->CreateDmxChannelSet("My Name1", 32131, 32895, &bit8ChannelSet1);
		bit8Function1->CreateDmxChannelSet("My Name1", 32896, 64514, &bit8ChannelSet1);
		bit8Function1->CreateDmxChannelSet("My Name1", 64515, 65535, &bit8ChannelSet1);

		IGdtfDmxChannelFunctionPtr bit8Function2;
		bit8LogicalChannel1->CreateDmxFunction("Function2", &bit8Function2);
		bit8Function2->SetStartAddress(700);
		bit8Function2->SetAttribute(attribute1);

		IGdtfDmxChannelSetPtr bit8ChannelSet2;
		bit8Function2->CreateDmxChannelSet("My Name1", 750, 799, &bit8ChannelSet2);


		IGdtfDmxChannelFunctionPtr bit8Function3;
		bit8LogicalChannel1->CreateDmxFunction("Function3", &bit8Function3);
		bit8Function3->SetStartAddress(800);
		bit8Function3->SetAttribute(attribute1);

		IGdtfDmxChannelSetPtr bit8ChannelSet3;
		bit8Function3->CreateDmxChannelSet("My Name1", 850, 65535, &bit8ChannelSet3);
		

}

void DmxChannelSetFormatingTest::ReadFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{  

	IGdtfDmxModePtr mode;
	__checkVCOM(fixture->GetDmxModeAt(0, &mode));
	
	IGdtfDmxChannelPtr bit8channel;
	__checkVCOM(mode->GetDmxChannelAt(0, &bit8channel));

	IGdtfDmxLogicalChannelPtr bit8LogicalChannel1;
	__checkVCOM(bit8channel->GetLogicalChannelAt(0, &bit8LogicalChannel1));


	IGdtfDmxChannelFunctionPtr bit8Function2;
	__checkVCOM(bit8LogicalChannel1->GetDmxFunctionAt(2, &bit8Function2));
	CheckFunction(bit8Function2, 700, 799);

	IGdtfDmxChannelFunctionPtr bit8Function3;
	__checkVCOM(bit8LogicalChannel1->GetDmxFunctionAt(3, &bit8Function3));
	CheckFunction(bit8Function3, 800, 65535);

}

void DmxChannelSetFormatingTest::CheckFunction(IGdtfDmxChannelFunctionPtr bit8Function1, VectorworksMVR::GdtfDefines::DmxValue start, VectorworksMVR::GdtfDefines::DmxValue end)
{
	size_t count;
	__checkVCOM(bit8Function1->GetDmxChannelSetCount(count));
	this->checkifEqual("bit8Function1 Count Channel Set", count, size_t(2));

	IGdtfDmxChannelSetPtr bit8ChannelSet1;
	__checkVCOM(bit8Function1->GetDmxChannelSetAt(0, &bit8ChannelSet1));
	this->CheckChannelSet(bit8ChannelSet1, "", start, start+49);

	IGdtfDmxChannelSetPtr bit8ChannelSet2;
	__checkVCOM(bit8Function1->GetDmxChannelSetAt(1, &bit8ChannelSet2));
	this->CheckChannelSet(bit8ChannelSet2, "My Name1", start+50, end);
}


void DmxChannelSetFormatingTest::CheckChannelSet(IGdtfDmxChannelSetPtr& channelSet, std::string name, DmxValue start, DmxValue end)
{
	if( ! channelSet) { this->checkifTrue("CheckChannelSet ok", channelSet != nullptr); return;}
	this->checkifEqual("Check Name ", name, channelSet->GetName());

	DmxValue thisStart = 0;
	__checkVCOM(channelSet->GetDmxStartAddress(thisStart));
	this->checkifEqual("Check Start ", start, thisStart);

	DmxValue thisEnd = 0;
	__checkVCOM(channelSet->GetDmxEndAddress(thisEnd));
	this->checkifEqual("Check End ",  end, thisEnd);
}
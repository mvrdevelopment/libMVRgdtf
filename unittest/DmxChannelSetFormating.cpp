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

		IGdtfDmxChannelFunctionPtr bit8Function1;
		bit8LogicalChannel1->CreateDmxFunction("Function1", &bit8Function1);
		bit8Function1->SetStartAddress(0);
		bit8Function1->SetAttribute(attribute1);

		IGdtfDmxChannelSetPtr bit8ChannelSet1;
		bit8Function1->CreateDmxChannelSet("My Name1", 32768, 35535, &bit8ChannelSet1);

}

void DmxChannelSetFormatingTest::ReadFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{  


}

//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------

#include "Include/VectorworksMVR.h"
#include "EmptyAttributeTest.h"

using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;


#define __checkVCOM(x) this->checkVCOM(x, #x)
#define __checkVCOM_NotSet(x) this->checkVCOM_NotSet(x, #x)

EmptyAttributeTest::EmptyAttributeTest(const std::string& currentDir) : GdtfUnitTest(currentDir)
{
}

EmptyAttributeTest::~EmptyAttributeTest()
{  
}


std::string EmptyAttributeTest::GetUnitTestName()
{  
    return  std::string("EmptyAttributeTest");
}

void EmptyAttributeTest::WriteFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{  
    //----------------------------------------------------------------
    // Create Attribute
    IGdtfFeatureGroupPtr featureGroup;
    __checkVCOM(fixture->CreateFeatureGroup("FeatureGroup","FeatureGroup", &featureGroup));

    IGdtfFeaturePtr feature;
    __checkVCOM(featureGroup->CreateFeature("Feature", & feature));

    
    IGdtfAttributePtr attribute1;
    __checkVCOM(fixture->CreateAttribute("Attribute1","Pretty", &attribute1));
    attribute1->SetFeature(feature);

    IGdtfGeometryPtr geometry;
    __checkVCOM(fixture->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "Geometry", nullptr, STransformMatrix(), &geometry));

    IGdtfDmxModePtr mode;
    __checkVCOM(fixture->CreateDmxMode("Mode", &mode));
    __checkVCOM(mode->SetGeometry(geometry));

    IGdtfDmxChannelPtr channel;
    __checkVCOM(mode->CreateDmxChannel(geometry, &channel));
    __checkVCOM(channel->SetGeometry(geometry));
    channel->SetCoarse(1);

    IGdtfDmxLogicalChannelPtr logicalChannel;
    __checkVCOM(channel->CreateLogicalChannel(attribute1, &logicalChannel));

    IGdtfDmxChannelFunctionPtr function;
	logicalChannel->CreateDmxFunction("Function1", &function);



}

void EmptyAttributeTest::ReadFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{  
    
}

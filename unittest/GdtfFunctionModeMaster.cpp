//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------

#include "Include/VectorworksMVR.h"
#include "GdtfFunctionModeMaster.h"
#include <iostream>

using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;


#define __checkVCOM(x) this->checkVCOM(x, #x)
#define __checkVCOM_NotSet(x) this->checkVCOM_NotSet(x, #x)

GdtfFunctionModeMasterTest::GdtfFunctionModeMasterTest(const std::string& currentDir) : GdtfUnitTest(currentDir)
{
}

GdtfFunctionModeMasterTest::~GdtfFunctionModeMasterTest()
{  
}


std::string GdtfFunctionModeMasterTest::GetUnitTestName()
{  
    return  std::string("GdtfFunctionModeMasterTest");
}

void GdtfFunctionModeMasterTest::WriteFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{  
    //--------------------------------------------------------------------------------------------------------
    // Create Needed Stuff

    IGdtfFeatureGroupPtr group;
    fixture->CreateFeatureGroup("Group", "Group", &group);

    IGdtfFeaturePtr feature;
    group->CreateFeature("Feature", &feature);


    IGdtfAttributePtr attribute;
    fixture->CreateAttribute("Attribute", "Attribute", &attribute);
    attribute->SetFeature(feature);

    IGdtfModelPtr model;
    fixture->CreateModel("Model", &model);

    IGdtfGeometryPtr geometry1;
    fixture->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "Geometry1", model, STransformMatrix(), &geometry1);

    IGdtfGeometryPtr geometry2;
    fixture->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "Geometry2", model, STransformMatrix(), &geometry2);

    IGdtfDmxModePtr mode;
    fixture->CreateDmxMode("Mode1", & mode);    
    mode->SetGeometry(geometry1);

    //--------------------------------------------------------------------------------------------------------
    // Channel 1
    IGdtfDmxChannelPtr channel1;
    mode->CreateDmxChannel(geometry1, &channel1);

    IGdtfDmxLogicalChannelPtr log1;
    channel1->CreateLogicalChannel(attribute, &log1);
    log1->SetAttribute(attribute);


    IGdtfDmxChannelFunctionPtr func1;
    log1->CreateDmxFunction("", &func1);
    func1->SetAttribute(attribute);

    //--------------------------------------------------------------------------------------------------------
    // Channel 2
    IGdtfDmxChannelPtr channel2;
    mode->CreateDmxChannel(geometry2, &channel2);

    IGdtfDmxLogicalChannelPtr log_2;
    channel2->CreateLogicalChannel(attribute, &log_2);
    log_2->SetAttribute(attribute);


    IGdtfDmxChannelFunctionPtr func2;
    log_2->CreateDmxFunction("", &func2);
    func2->SetAttribute(attribute);

    //--------------------------------------------------------------------------------------------------------
    // Add Mode Relation
    func2->SetModeMasterFunction(func1, 0,0);
    func1->SetModeMasterFunction(func2, 0,0);
}

void GdtfFunctionModeMasterTest::ReadFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{  

}

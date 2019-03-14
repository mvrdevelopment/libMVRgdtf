//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------

#include "Include/VectorworksMVR.h"
#include "EmptyAttributeTest2.h"

using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;


#define __checkVCOM(x) this->checkVCOM(x, #x)
#define __checkVCOM_NotSet(x) this->checkVCOM_NotSet(x, #x)

EmptyAttributeTest2::EmptyAttributeTest2(const std::string& currentDir) : GdtfUnitTest(currentDir)
{
}

EmptyAttributeTest2::~EmptyAttributeTest2()
{  
}


std::string EmptyAttributeTest2::GetUnitTestName()
{  
    return  std::string("EmptyAttributeTest2");
}

void EmptyAttributeTest2::WriteFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{  
    //----------------------------------------------------------------
    // Create Attribute
    IGdtfFeatureGroupPtr featureGroup;
    __checkVCOM(fixture->CreateFeatureGroup("Control","Control", &featureGroup));

    IGdtfFeaturePtr feature;
    __checkVCOM(featureGroup->CreateFeature("Feature", & feature));

    
    IGdtfAttributePtr attribute1;
    __checkVCOM(fixture->CreateAttribute("Attribute1","Pretty", &attribute1));
    attribute1->SetFeature(feature);

    //----------------------------------------------------------------
    // Create Geometry
    IGdtfGeometryPtr geometry;
    __checkVCOM(fixture->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "Geometry", nullptr, STransformMatrix(), &geometry));

    //----------------------------------------------------------------
    // Create DMX
    IGdtfDmxModePtr mode;
    __checkVCOM(fixture->CreateDmxMode("Mode", &mode));
    __checkVCOM(mode->SetGeometry(geometry));

    IGdtfDmxChannelPtr channel;
    __checkVCOM(mode->CreateDmxChannel(geometry, &channel));
    __checkVCOM(channel->SetGeometry(geometry));
    channel->SetCoarse(1);

    IGdtfDmxLogicalChannelPtr logicalChannel;
    __checkVCOM(channel->CreateLogicalChannel(attribute1, &logicalChannel));

    //----------------------------------------------------------------
    // Functions
    IGdtfDmxChannelFunctionPtr function1;
	__checkVCOM(logicalChannel->CreateDmxFunction("Function1", &function1));

    IGdtfDmxChannelFunctionPtr function2;
	__checkVCOM(logicalChannel->CreateDmxFunction("Function2", &function2));
    __checkVCOM(function2->SetStartAddress(100));

    IGdtfDmxChannelFunctionPtr function3;
	__checkVCOM(logicalChannel->CreateDmxFunction("Function3", &function3));
    __checkVCOM(function3->SetStartAddress(200));

}

void EmptyAttributeTest2::ReadFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{  
    //----------------------------------------------------------------
    // Check Attributes
    size_t attributeCount = 0;
    __checkVCOM(fixture->GetAttributeCount(attributeCount));
    checkifEqual("Attribte Count", attributeCount, size_t(2));


     size_t featureGroupCount = 0;
    __checkVCOM(fixture->GetFeatureGroupCount(featureGroupCount));
    checkifEqual("GetFeatureGroupCount", featureGroupCount, size_t(1));

    IGdtfFeatureGroupPtr group;
    __checkVCOM(fixture->GetFeatureGroupAt(0, & group));

     size_t featureCount = 0;
    __checkVCOM(group->GetFeatureCount(featureCount));
    checkifEqual("GetFeatureCount", featureCount, size_t(2));


     //----------------------------------------------------------------
    // Check Attributes
    IGdtfDmxModePtr mode;
    __checkVCOM(fixture->GetDmxModeAt(0, &mode));

    IGdtfDmxChannelPtr channel;
    __checkVCOM(mode->GetDmxChannelAt(0, &channel));

    IGdtfDmxLogicalChannelPtr logicalChannel;
    __checkVCOM(channel->GetLogicalChannelAt(0, &logicalChannel));

    //----------------------------------------------------------------
    // Functions
    IGdtfDmxChannelFunctionPtr function1;
	__checkVCOM(logicalChannel->GetDmxFunctionAt(0, &function1));
    TestFunction(function1);

    IGdtfDmxChannelFunctionPtr function2;
	__checkVCOM(logicalChannel->GetDmxFunctionAt(1, &function2));
    TestFunction(function2);

    IGdtfDmxChannelFunctionPtr function3;
	__checkVCOM(logicalChannel->GetDmxFunctionAt(2, &function3));
    TestFunction(function3);


}

void EmptyAttributeTest2::TestFunction(VectorworksMVR::IGdtfDmxChannelFunctionPtr& function)
{
    IGdtfAttributePtr attribute;
    __checkVCOM(function->GetAttribute(&attribute));
    checkifEqual("AttributeName" , attribute->GetName(), "NoFeature");

    IGdtfFeaturePtr linkedFeature;
    __checkVCOM(attribute->GetFeature(&linkedFeature));
    if(linkedFeature)
    {
        checkifEqual("LinkedFeature Name" , linkedFeature->GetName(), "Control");
    }
    

}
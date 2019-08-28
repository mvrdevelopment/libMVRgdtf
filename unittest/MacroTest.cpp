//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2019 www.deersoft.de
//-----------------------------------------------------------------------------

#include "Include/VectorworksMVR.h"
#include "MacroTest.h"
#include "Utility.h"


using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;


#define __checkVCOM(x) this->checkVCOM(x, #x)
#define __checkVCOM_NotSet(x) this->checkVCOM_NotSet(x, #x)

GdtfMacroTest::GdtfMacroTest(const std::string& currentDir) : GdtfUnitTest(currentDir)
{
    fTestData = {
        {       1,      -1,     3},
        {       74,     56,     -1},
        {       255,    33,     -1}
    };
}

GdtfMacroTest::~GdtfMacroTest()
{  
}


std::string GdtfMacroTest::GetUnitTestName()
{  
    return  std::string("GdtfMacroTest");
}

void GdtfMacroTest::WriteFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{  
    IGdtfModelPtr model;
    fixture->CreateModel("model", & model);

    IGdtfGeometryPtr geometry;
    STransformMatrix matrix = STransformMatrix();
    fixture->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "geometry", model, matrix, &geometry);

    IGdtfFeatureGroupPtr featureGroup;
    fixture->CreateFeatureGroup("featureGroup", "featureGroup", & featureGroup);

    IGdtfFeaturePtr feature;
    featureGroup->CreateFeature("feature", &feature);

    IGdtfAttributePtr attribute;
    fixture->CreateAttribute("attribute", "attribute", &attribute);
    attribute->SetFeature(feature);

     IGdtfAttributePtr attribute2;
    fixture->CreateAttribute("attribute2", "attribute2", &attribute2);
    attribute2->SetFeature(feature);

    IGdtfDmxModePtr dmxMode;
    fixture->CreateDmxMode("dmxMode", &dmxMode);
    dmxMode->SetGeometry(geometry);

    IGdtfDmxChannelPtr channel1;
    dmxMode->CreateDmxChannel(geometry, &channel1);
    channel1->SetCoarse(1);

    IGdtfDmxLogicalChannelPtr logicalChannel1;
    channel1->CreateLogicalChannel(attribute, &logicalChannel1);

    IGdtfDmxChannelFunctionPtr channelFunction1;
    logicalChannel1->CreateDmxFunction("function", &channelFunction1);

    IGdtfDmxChannelPtr channel2;
    dmxMode->CreateDmxChannel(geometry, &channel2);
    channel2->SetCoarse(2);
    channel2->SetFine(3);

    IGdtfDmxLogicalChannelPtr logicalChannel2;
    channel2->CreateLogicalChannel(attribute2, &logicalChannel2);

    IGdtfDmxChannelFunctionPtr channelFunction2;
    logicalChannel2->CreateDmxFunction("function", &channelFunction2);

    IGdtfMacroPtr macro1;
    dmxMode->CreateDmxMacro("macro1", &macro1);

    IGdtfMacroDMXPtr macro1dmx;
    macro1->CreateMacroDMX(&macro1dmx);

    Sint32 duration = 3;
    IGdtfMacroDMXStepPtr macro1dmxStep;
    macro1dmx->CreateStep(duration ,&macro1dmxStep);

    IGdtfMacroDMXValuePtr macro1dmxValue;
    macro1dmxStep->CreateDMXValue(128, channel1, &macro1dmxValue);

    IGdtfMacroPtr macro2;
    dmxMode->CreateDmxMacro("macro2", &macro2);

    IGdtfMacroVisualPtr macro2Visual;
    macro2->CreateMacroVisual(&macro2Visual);

    IGdtfMacroVisualStepPtr macro2VisualStep;
    macro2Visual->CreateVisualStep(&macro2VisualStep);

    IGdtfMacroVisualValuePtr macro2VisualValue;
    macro2VisualStep->CreateVisualValue(128, channelFunction1, &macro2VisualValue);
}

void GdtfMacroTest::ReadFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{  
    IGdtfDmxModePtr mode;
    fixture->GetDmxModeAt(0, &mode);

    IGdtfDmxChannelPtr channel1;
    mode->GetDmxChannelAt(0, &channel1);

    IGdtfMacroPtr macro1;
    mode->GetDmxMacroAt(0, &macro1);
    checkifEqual("Macro Name", macro1->GetName(), "macro1");

    IGdtfMacroDMXPtr macro1dmx;
    macro1->GetMacroDMX(&macro1dmx);

    IGdtfMacroDMXStepPtr macro1dmxStep;
    macro1dmx->GetStepAt(0, &macro1dmxStep);

    Sint32 duration;
    macro1dmxStep->GetDuration(duration);
    checkifEqual("Step Duration", duration, 3);
    
    IGdtfMacroDMXValuePtr macro1dmxValue;
    macro1dmxStep->GetDMXValueAt(0, &macro1dmxValue);
    DmxValue dmxValue;
    macro1dmxValue->GetDmxValue(dmxValue);
    checkifEqual("DMX Value", (size_t)dmxValue, (size_t)128);

    IGdtfDmxChannelPtr channelToTest;
    macro1dmxValue->GetDmxChannel(&channelToTest);
    checkifEqual("DMX Channel", channel1->GetName(), channelToTest->GetName());
}

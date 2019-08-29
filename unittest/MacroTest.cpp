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
    macro2VisualStep->SetFade(2);
    macro2VisualStep->SetDelay(3);

    IGdtfMacroVisualValuePtr macro2VisualValue;
    macro2VisualStep->CreateVisualValue(64, channelFunction2, &macro2VisualValue);
}

void GdtfMacroTest::ReadFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{  
    IGdtfDmxModePtr mode;
    fixture->GetDmxModeAt(0, &mode);

    IGdtfDmxChannelPtr channel1;
    mode->GetDmxChannelAt(0, &channel1);

    IGdtfDmxChannelPtr channel2;
    mode->GetDmxChannelAt(1, &channel2);
    
    IGdtfDmxLogicalChannelPtr logChannel;
    channel2->GetLogicalChannelAt(0, &logChannel);
    
    IGdtfDmxChannelFunctionPtr channelFunction;
    logChannel->GetDmxFunctionAt(0, &channelFunction);

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
    checkifEqualPtr("DMX Channel", channel1->GetBoundObject(), channelToTest->GetBoundObject());

    IGdtfMacroPtr macro2;
    mode->GetDmxMacroAt(1, &macro2);

    IGdtfMacroVisualPtr macro2visual;
    macro2->GetMacroVisual(&macro2visual);

    IGdtfMacroVisualStepPtr macro2visualStep;
    macro2visual->GetVisualStepAt(0, & macro2visualStep);

    double delay;
    macro2visualStep->GetDelay(delay);
    checkifEqual("Delay", delay, 3.0);

    double fade;
    macro2visualStep->GetFade(fade);
    checkifEqual("Fade", fade, 2.0);

    Sint32 duration2;
    macro2visualStep->GetDuration(duration2);
    checkifEqual("Duration",  duration2, 1);

    IGdtfMacroVisualValuePtr macro2visualValue;
    macro2visualStep->GetVisualValueAt(0, &macro2visualValue);

    DmxValue dmxValue2;
    macro2visualValue->GetDmxValue(dmxValue2);
    checkifEqual("DMX Value", (size_t)dmxValue2, (size_t)64);

    IGdtfDmxChannelFunctionPtr channelFuncToTest;
    macro2visualValue->GetDmxChannel(&channelFuncToTest);
    checkifEqualPtr("DMX ChannelFunction", channelFuncToTest->GetBoundObject(), channelFunction->GetBoundObject());
}

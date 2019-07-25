//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------

#include "Include/VectorworksMVR.h"
#include "GetCountOfChannels.h"

using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;


#define __checkVCOM(x) this->checkVCOM(x, #x)
#define __checkVCOM_Failed(x) this->checkVCOM_Failed(x, #x)
#define __checkVCOM_NotSet(x) this->checkVCOM_NotSet(x, #x)

GdtfGetCountOfLinkedChannelsForGeometry::GdtfGetCountOfLinkedChannelsForGeometry(const std::string& currentDir) : GdtfUnitTest(currentDir)
{
}

GdtfGetCountOfLinkedChannelsForGeometry::~GdtfGetCountOfLinkedChannelsForGeometry()
{  
}


std::string GdtfGetCountOfLinkedChannelsForGeometry::GetUnitTestName()
{  
    return  std::string("GdtfGetCountOfLinkedChannelsForGeometry");
}

void GdtfGetCountOfLinkedChannelsForGeometry::WriteFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{  
    //--------------------------------------------------------------------------------------------------------
    // Create Needed Stuff
    IGdtfFeatureGroupPtr group;
    __checkVCOM(fixture->CreateFeatureGroup("Group", "Group", &group));

    IGdtfFeaturePtr feature;
    __checkVCOM(group->CreateFeature("Feature", &feature));

    IGdtfAttributePtr attributeMode1;
    __checkVCOM(fixture->CreateAttribute("Attribute1", "Attribute1", &attributeMode1));
    __checkVCOM(attributeMode1->SetFeature(feature));

    IGdtfAttributePtr attributeMode2;
    __checkVCOM(fixture->CreateAttribute("Attribute2", "Attribute2", &attributeMode2));
    __checkVCOM(attributeMode2->SetFeature(feature));


    IGdtfGeometryPtr geometry1;
    __checkVCOM(fixture->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "Geometry1", nullptr, STransformMatrix(), &geometry1));

    IGdtfGeometryPtr geometry2;
    __checkVCOM(fixture->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "Geometry2", nullptr, STransformMatrix(), &geometry2));


    //--------------------------------------------------------------------------------------------------------
    // Mode 1
    IGdtfDmxModePtr mode1;
    __checkVCOM(fixture->CreateDmxMode("Mode1", & mode1));    
    __checkVCOM(mode1->SetGeometry(geometry1));

    IGdtfDmxChannelPtr m1_channel;
    __checkVCOM(mode1->CreateDmxChannel(geometry1, &m1_channel));

    IGdtfDmxLogicalChannelPtr m1_log;
    __checkVCOM(m1_channel->CreateLogicalChannel(attributeMode1, &m1_log));
    __checkVCOM(m1_log->SetAttribute(attributeMode1));


    IGdtfDmxChannelFunctionPtr m1_func;
    __checkVCOM(m1_log->CreateDmxFunction("", &m1_func));
    __checkVCOM(m1_func->SetAttribute(attributeMode1));


    //--------------------------------------------------------------------------------------------------------
    // Mode 1
    IGdtfDmxModePtr mode2;
    __checkVCOM(fixture->CreateDmxMode("Mode2", & mode2));    
    __checkVCOM(mode2->SetGeometry(geometry1));

    IGdtfDmxChannelPtr m2_channel;
    __checkVCOM(mode2->CreateDmxChannel(geometry1, &m2_channel));

    IGdtfDmxLogicalChannelPtr m2_log;
    __checkVCOM(m2_channel->CreateLogicalChannel(attributeMode2, &m2_log));
    __checkVCOM(m2_log->SetAttribute(attributeMode2));


    IGdtfDmxChannelFunctionPtr m2_func;
    __checkVCOM(m2_log->CreateDmxFunction("", &m2_func));
    __checkVCOM(m2_func->SetAttribute(attributeMode2));
}

void GdtfGetCountOfLinkedChannelsForGeometry::ReadFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{  
    //--------------------------------------------------------------------------------------------------------
    // Get Stuff
    IGdtfDmxModePtr mode1;
    __checkVCOM(fixture->GetDmxModeAt(0, &mode1));

    IGdtfDmxModePtr mode2;
    __checkVCOM(fixture->GetDmxModeAt(1, &mode2));

    IGdtfGeometryPtr geometry1;
    __checkVCOM(fixture->GetGeometryAt(0, &geometry1));

     IGdtfGeometryPtr geometry2;
    __checkVCOM(fixture->GetGeometryAt(1, &geometry2));

    //--------------------------------------------------------------------------------------------------------
    // Check Linked Channel Count
    size_t count_m1_g1 = 0;
    __checkVCOM(geometry1->GetCountLinkedDmxChannel(count_m1_g1, mode1));
    checkifEqual("count_m1_g1", count_m1_g1, size_t(1));

    size_t count_m1_g2 = 0;
    __checkVCOM(geometry2->GetCountLinkedDmxChannel(count_m1_g2, mode1));
    checkifEqual("count_m1_g2", count_m1_g2, size_t(0));

    size_t count_m2_g1 = 0;
    __checkVCOM(geometry1->GetCountLinkedDmxChannel(count_m2_g1, mode2));
    checkifEqual("count_m2_g1", count_m2_g1, size_t(1));

    size_t count_m2_g2 = 0;
    __checkVCOM(geometry2->GetCountLinkedDmxChannel(count_m2_g2, mode2));
    checkifEqual("count_m2_g2", count_m2_g2, size_t(0));

    //--------------------------------------------------------------------------------------------------------
    // Check Pointer
    IGdtfDmxChannelPtr failChannel;
    __checkVCOM_Failed(geometry2->GetLinkedDmxChannelAt(0, &failChannel, mode1));
    __checkVCOM_Failed(geometry2->GetLinkedDmxChannelAt(0, &failChannel, mode2));

    IGdtfDmxChannelPtr channel1;
    __checkVCOM(geometry1->GetLinkedDmxChannelAt(0, &channel1, mode1));
    checkifEqual("ChannelName 1", channel1->GetName(), "Geometry1_Attribute1");

    IGdtfDmxChannelPtr channel2;
    __checkVCOM(geometry1->GetLinkedDmxChannelAt(0, &channel2, mode2));
    checkifEqual("ChannelName 2", channel2->GetName(), "Geometry1_Attribute2"); 







}

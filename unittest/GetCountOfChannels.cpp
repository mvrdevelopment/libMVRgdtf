//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------

#include "Include/VectorworksMVR.h"
#include "GetCountOfChannels.h"

using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;


#define __checkVCOM(x) this->checkVCOM(x, #x)
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

    IGdtfAttributePtr attribute;
    __checkVCOM(fixture->CreateAttribute("Attribute", "Attribute", &attribute));
    __checkVCOM(attribute->SetFeature(feature));

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
    __checkVCOM(m1_channel->CreateLogicalChannel(attribute, &m1_log));
    __checkVCOM(m1_log->SetAttribute(attribute));


    IGdtfDmxChannelFunctionPtr m1_func;
    __checkVCOM(m1_log->CreateDmxFunction("", &m1_func));
    __checkVCOM(m1_func->SetAttribute(attribute));


    //--------------------------------------------------------------------------------------------------------
    // Mode 1
    IGdtfDmxModePtr mode2;
    __checkVCOM(fixture->CreateDmxMode("Mode2", & mode2));    
    __checkVCOM(mode2->SetGeometry(geometry1));

    IGdtfDmxChannelPtr m2_channel;
    __checkVCOM(mode2->CreateDmxChannel(geometry1, &m2_channel));

    IGdtfDmxLogicalChannelPtr m2_log;
    __checkVCOM(m2_channel->CreateLogicalChannel(attribute, &m2_log));
    __checkVCOM(m2_log->SetAttribute(attribute));


    IGdtfDmxChannelFunctionPtr m2_func;
    __checkVCOM(m2_log->CreateDmxFunction("", &m2_func));
    __checkVCOM(m2_func->SetAttribute(attribute));
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
    checkifEqual("count_m1_g1", count_m1_g1, size_t(0));

    size_t count_m1_g2 = 0;
    __checkVCOM(geometry2->GetCountLinkedDmxChannel(count_m1_g2, mode1));
    checkifEqual("count_m1_g2", count_m1_g2, size_t(0));


    size_t count_m2_g1 = 0;
    __checkVCOM(geometry1->GetCountLinkedDmxChannel(count_m2_g1, mode2));
    checkifEqual("count_m2_g1", count_m2_g1, size_t(0));

    size_t count_m2_g2 = 0;
    __checkVCOM(geometry2->GetCountLinkedDmxChannel(count_m2_g2, mode2));
    checkifEqual("count_m2_g2", count_m2_g2, size_t(0));

}

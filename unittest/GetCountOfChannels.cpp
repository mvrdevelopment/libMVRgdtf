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
    fixture->CreateFeatureGroup("Group", "Group", &group);

    IGdtfFeaturePtr feature;
    group->CreateFeature("Feature", &feature);

    IGdtfAttributePtr attribute;
    fixture->CreateAttribute("Attribute", "Attribute", &attribute);
    attribute->SetFeature(feature);

    IGdtfGeometryPtr geometry1;
    fixture->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "Geometry1", nullptr, STransformMatrix(), &geometry1);

    IGdtfGeometryPtr geometry2;
    fixture->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "Geometry2", nullptr, STransformMatrix(), &geometry2);


    //--------------------------------------------------------------------------------------------------------
    // Mode 1
    IGdtfDmxModePtr mode1;
    fixture->CreateDmxMode("Mode1", & mode1);    
    mode1->SetGeometry(geometry1);

    IGdtfDmxChannelPtr m1_channel;
    mode1->CreateDmxChannel(geometry1, &m1_channel);

    IGdtfDmxLogicalChannelPtr m1_log;
    m1_channel->CreateLogicalChannel(attribute, &m1_log);
    m1_log->SetAttribute(attribute);


    IGdtfDmxChannelFunctionPtr m1_func;
    m1_log->CreateDmxFunction("", &m1_func);
    m1_func->SetAttribute(attribute);


    //--------------------------------------------------------------------------------------------------------
    // Mode 1
    IGdtfDmxModePtr mode2;
    fixture->CreateDmxMode("Mode2", & mode2);    
    mode2->SetGeometry(geometry1);

    IGdtfDmxChannelPtr m2_channel;
    mode2->CreateDmxChannel(geometry1, &m2_channel);

    IGdtfDmxLogicalChannelPtr m2_log;
    m2_channel->CreateLogicalChannel(attribute, &m2_log);
    m2_log->SetAttribute(attribute);


    IGdtfDmxChannelFunctionPtr m2_func;
    m2_log->CreateDmxFunction("", &m2_func);
    m2_func->SetAttribute(attribute);
}

void GdtfGetCountOfLinkedChannelsForGeometry::ReadFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{  


}

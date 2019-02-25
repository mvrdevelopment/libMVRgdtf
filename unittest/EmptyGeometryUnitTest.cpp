//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------

#include "Include/VectorworksMVR.h"
#include "EmptyGeometryUnitTest.h"
#include <iostream>

using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;


#define __checkVCOM(x) this->checkVCOM(x, #x)
#define __checkVCOM_NotSet(x) this->checkVCOM_NotSet(x, #x)

GdtfEmptyModelTest::GdtfEmptyModelTest(const std::string& currentDir) : GdtfUnitTest(currentDir)
{
}

GdtfEmptyModelTest::~GdtfEmptyModelTest()
{  
}


std::string GdtfEmptyModelTest::GetUnitTestName()
{  
    return  std::string("GdtfEmptyModel");
}

void GdtfEmptyModelTest::WriteFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{  
    //--------------------------------------------------------------------------------------------------------
    // Create Needed Stuff

    
    IGdtfGeometryPtr geometry1;
    __checkVCOM(fixture->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "Geometry1", nullptr, STransformMatrix(), &geometry1));

    if(geometry1)
    {
        IGdtfGeometryPtr geometry2;
        __checkVCOM(geometry1->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "Geometry2", nullptr, STransformMatrix(), &geometry2));

    }

}

void GdtfEmptyModelTest::ReadFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{  
    size_t count_top_Level = 0;
    __checkVCOM(fixture->GetGeometryCount(count_top_Level));
    checkifEqual("Top Level Geometry Count", count_top_Level, (size_t)1);

    if(count_top_Level == 1)
    {
        IGdtfGeometryPtr geometry1;
        __checkVCOM(fixture->GetGeometryAt(0, &geometry1));
        checkifEqual("Second Level Geometry Name", geometry1->GetName(), "Geometry2");


        size_t second_level = 0;
        __checkVCOM(geometry1->GetInternalGeometryCount(second_level));
        checkifEqual("Second Level Geometry Count", second_level, (size_t)1);

        if(second_level == 1)
        {
            IGdtfGeometryPtr geometry2;
            __checkVCOM(geometry1->GetInternalGeometryAt(0, &geometry2));
            checkifEqual("Second Level Geometry Name", geometry2->GetName(), "Geometry2");

        }
    }

}

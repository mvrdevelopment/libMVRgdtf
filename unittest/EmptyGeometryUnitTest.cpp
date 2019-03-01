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
    IGdtfModelPtr       filledModel;
     __checkVCOM(fixture->CreateModel("Model",&filledModel));

    
    IGdtfGeometryPtr geometry1;
    __checkVCOM(fixture->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "Geometry1", nullptr, STransformMatrix(), &geometry1));

    if(geometry1)
    {
        IGdtfGeometryPtr     geometry2;
        IGdtfModelPtr       model;
        __checkVCOM(geometry1->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "Geometry2", model, STransformMatrix(), &geometry2));

        IGdtfGeometryPtr     geometry3;
        
        __checkVCOM(geometry1->CreateGeometry(EGdtfObjectType::eGdtfGeometryReference, "Geometry3", filledModel, STransformMatrix(), &geometry3));
        __checkVCOM(geometry3->SetGeometryReference(geometry1));
    }

}

void GdtfEmptyModelTest::ReadFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{  
    size_t count_top_Level = 0;
    __checkVCOM(fixture->GetGeometryCount(count_top_Level));
    checkifEqual("Top Level Geometry Count", count_top_Level, (size_t)1);

    IGdtfModelPtr model;

    if(count_top_Level == 1)
    {
        IGdtfGeometryPtr geometry1;
        __checkVCOM(fixture->GetGeometryAt(0, &geometry1));
        checkifEqual("Second Level Geometry Name", geometry1->GetName(), "Geometry1");
        __checkVCOM_NotSet(geometry1->GetModel( & model));


        size_t second_level = 0;
        __checkVCOM(geometry1->GetInternalGeometryCount(second_level));
        checkifEqual("Second Level Geometry Count", second_level, (size_t)2);

        if(second_level == 2)
        {
            IGdtfGeometryPtr geometry2;
            __checkVCOM(geometry1->GetInternalGeometryAt(0, &geometry2));
            checkifEqual("Second Level Geometry Name", geometry2->GetName(), "Geometry2");
            __checkVCOM_NotSet(geometry2->GetModel( & model));

            IGdtfGeometryPtr geometry3;
            __checkVCOM(geometry1->GetInternalGeometryAt(1, &geometry3));
            checkifEqual("Second Level Geometry Name", geometry3->GetName(), "Geometry3");
            
            IGdtfModelPtr linkedModel;
            
            __checkVCOM(geometry3->GetModel( & linkedModel));
             checkifEqual("Model Name", linkedModel->GetName(), "Model");



        }
    }

}
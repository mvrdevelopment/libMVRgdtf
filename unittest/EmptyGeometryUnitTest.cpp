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
    __checkVCOM(fixture->CreateGeometry(EGdtfObjectType::eGdtfGeometryLamp, "Geometry1", nullptr, STransformMatrix(), &geometry1));

    geometry1->SetLampType(EGdtfLampType::eGdtfLampType_LED);

    if(geometry1)
    {
        IGdtfGeometryPtr     geometry2;
        IGdtfModelPtr       model;
        __checkVCOM(geometry1->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "Geometry2", model, STransformMatrix(), &geometry2));

        IGdtfGeometryPtr     geometry3;
        
        __checkVCOM(geometry1->CreateGeometry(EGdtfObjectType::eGdtfGeometryReference, "Geometry3", filledModel, STransformMatrix(), &geometry3));
        __checkVCOM(geometry3->SetGeometryReference(geometry1));

        IGdtfGeometryPtr    geometry4;
        __checkVCOM(geometry1->CreateGeometry(EGdtfObjectType::eGdtfGeometryDisplay, "Geometry4", filledModel, STransformMatrix(), &geometry4));
        __checkVCOM(geometry4->SetTexture("Texture.png"));

        // Magnet
        IGdtfGeometryPtr    geometry5;
        __checkVCOM(geometry1->CreateGeometry(EGdtfObjectType::eGdtfGeometryMagnet, "Geometry5 Magnet", filledModel, STransformMatrix(), &geometry5));

        // Laser
        IGdtfGeometryPtr    geometry6;
        __checkVCOM(geometry1->CreateGeometry(EGdtfObjectType::eGdtfGeometryLaser, "Geometry6 Laser", filledModel, STransformMatrix(), &geometry6));

        __checkVCOM(geometry6->SetColorType(EGdtfLaserColorType::SingleWaveLength));
        __checkVCOM(geometry6->SetLaserColor(1.1));
        __checkVCOM(geometry6->SetOutputStrength(1.2));
        __checkVCOM(geometry6->SetBeamDiameter(1.3));
        __checkVCOM(geometry6->SetBeamDivergenceMin(1.4));
        __checkVCOM(geometry6->SetBeamDivergenceMax(1.5));
        __checkVCOM(geometry6->SetScanAnglePan(1.6));
        __checkVCOM(geometry6->SetScanAngleTilt(1.7));
        __checkVCOM(geometry6->SetScanSpeed(1.8));
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

        EGdtfLampType lampType = EGdtfLampType::eGdtfLampType_Dischange;
        __checkVCOM(geometry1->GetLampType(lampType));
        checkifEqual("Check Lamp Type", lampType, EGdtfLampType::eGdtfLampType_LED);



        size_t second_level = 0;
        __checkVCOM(geometry1->GetInternalGeometryCount(second_level));
        checkifEqual("Second Level Geometry Count", second_level, (size_t)5);

        if(second_level == 5)
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

            IGdtfGeometryPtr geometry4;
            __checkVCOM(geometry1->GetInternalGeometryAt(2, &geometry4));
            checkifEqual("Second Level Geometry Name", geometry4->GetName(), "Geometry4");

            checkifEqual("Check Texture", geometry4->GetTexture(), "Texture.png");

            // Magnet
            IGdtfGeometryPtr geoMagnet;
            __checkVCOM(geometry1->GetInternalGeometryAt(3, &geoMagnet));
            checkifEqual("Magnet Geometry Name", geoMagnet->GetName(), "Geometry5 Magnet");

            // Laser
            IGdtfGeometryPtr geoLaser;
            __checkVCOM(geometry1->GetInternalGeometryAt(4, &geoLaser));
            checkifEqual("Laser Geometry Name", geoLaser->GetName(), "Geometry6 Laser");

            EGdtfLaserColorType colorType = EGdtfLaserColorType::RGB;
            __checkVCOM(geoLaser->GetColorType(colorType));
            checkifEqual("Laser ColorType", (size_t)colorType, (size_t)EGdtfLaserColorType::SingleWaveLength);

            double colorWaveLength = 0.0;
            __checkVCOM(geoLaser->GetLaserColor(colorWaveLength));
            checkifEqual("Laser Color", colorWaveLength, 1.1);

            double outputStrength = 0.0;
            __checkVCOM(geoLaser->GetOutputStrength(outputStrength));
            checkifEqual("Laser OutputStrength", outputStrength, 1.2);

            double beamDiameter = 0.0;
            __checkVCOM(geoLaser->GetBeamDiameter(beamDiameter));
            checkifEqual("Laser BeamDiameter", beamDiameter, 1.3);

            double beamDivergenceMin = 0.0;
            __checkVCOM(geoLaser->GetBeamDivergenceMin(beamDivergenceMin));
            checkifEqual("Laser BeamDivergenceMin", beamDivergenceMin, 1.4);

            double beamDivergenceMax = 0.0;
            __checkVCOM(geoLaser->GetBeamDivergenceMax(beamDivergenceMax));
            checkifEqual("Laser BeamDivergenceMax", beamDivergenceMax, 1.5);

            double scanAnglePan = 0.0;
            __checkVCOM(geoLaser->GetScanAnglePan(scanAnglePan));
            checkifEqual("Laser ScanAnglePan", scanAnglePan, 1.6);

            double scanAngleTilt = 0.0;
            __checkVCOM(geoLaser->GetScanAngleTilt(scanAngleTilt));
            checkifEqual("Laser ScanAngleTilt", scanAngleTilt, 1.7);

            double scanSpeed = 0.0;
            __checkVCOM(geoLaser->GetScanSpeed(scanSpeed));
            checkifEqual("Laser ScanSpeed", scanSpeed, 1.8);
        }
    }

}

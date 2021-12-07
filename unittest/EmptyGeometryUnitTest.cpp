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
        IGdtfGeometryPtr    geometry2;
        IGdtfModelPtr       model;
        __checkVCOM(geometry1->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "Geometry2", model, STransformMatrix(), &geometry2));

        IGdtfGeometryPtr geometry3;
        
        __checkVCOM(geometry1->CreateGeometry(EGdtfObjectType::eGdtfGeometryReference, "Geometry3", filledModel, STransformMatrix(), &geometry3));
        __checkVCOM(geometry3->SetGeometryReference(geometry1));

        IGdtfGeometryPtr geometry4;
        __checkVCOM(geometry1->CreateGeometry(EGdtfObjectType::eGdtfGeometryDisplay, "Geometry4", filledModel, STransformMatrix(), &geometry4));
        __checkVCOM(geometry4->SetTexture("Texture.png"));

        // Magnet
        IGdtfGeometryPtr geometry5;
        __checkVCOM(geometry1->CreateGeometry(EGdtfObjectType::eGdtfGeometryMagnet, "Geometry5 Magnet", filledModel, STransformMatrix(), &geometry5));

        // Laser
        IGdtfGeometryPtr geometry6;
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

        IGdtfLaserProtocolPtr laserProtocol1;
        __checkVCOM(geometry6->CreateLaserProtocol("My Laser Protocol 1", &laserProtocol1));

        IGdtfLaserProtocolPtr laserProtocol2;
        __checkVCOM(geometry6->CreateLaserProtocol("You shouldn't be seeing this", &laserProtocol2));
        __checkVCOM(laserProtocol2->SetName("My Laser Protocol 2"));

        // WiringObject
        IGdtfGeometryPtr geometry7;
        __checkVCOM(geometry1->CreateGeometry(EGdtfObjectType::eGdtfGeometryWiringObject, "Geometry7 WiringObject", filledModel, STransformMatrix(), &geometry7));

        __checkVCOM(geometry7->SetConnectorType("My ConnectorType"));
        __checkVCOM(geometry7->SetComponentType(EGdtfComponentType::Consumer));
        __checkVCOM(geometry7->SetSignalType("My SignalType"));
        __checkVCOM(geometry7->SetPinCount(3));
        __checkVCOM(geometry7->SetSignalLayer(1));
        __checkVCOM(geometry7->SetOrientation(EGdtfOrientation::Top));
        __checkVCOM(geometry7->SetWireGroup("My WireGroup"));
        __checkVCOM(geometry7->SetElectricalPayLoad(1.1));
        __checkVCOM(geometry7->SetVoltageRangeMin(1.2));
        __checkVCOM(geometry7->SetVoltageRangeMax(1.3));
        __checkVCOM(geometry7->SetFrequencyRangeMin(1.4));
        __checkVCOM(geometry7->SetFrequencyRangeMax(1.5));
        __checkVCOM(geometry7->SetCosPhi(1.6));
        __checkVCOM(geometry7->SetMaxPayLoad(1.7));
        __checkVCOM(geometry7->SetVoltage(1.8));
        __checkVCOM(geometry7->SetFuseCurrent(1.9));
        __checkVCOM(geometry7->SetFuseRating(EGdtfFuseRating::Z));

        IGdtfGeometryPtr toWiringObject8;
        __checkVCOM(geometry1->CreateGeometry(EGdtfObjectType::eGdtfGeometryWiringObject, "toWiringObject8", filledModel, STransformMatrix(), &toWiringObject8));

        IGdtfPinPatchPtr pinPatch1;
        __checkVCOM(geometry7->CreatePinPatch(toWiringObject8, 1, 2, &pinPatch1));

        IGdtfGeometryPtr toWiringObject9;
        __checkVCOM(geometry1->CreateGeometry(EGdtfObjectType::eGdtfGeometryWiringObject, "toWiringObject9", filledModel, STransformMatrix(), &toWiringObject9));

        IGdtfPinPatchPtr pinPatch2;
        __checkVCOM(geometry7->CreatePinPatch(toWiringObject8, 1, 2, &pinPatch2));
        pinPatch2->SetLinkedWiringObject(toWiringObject9);
        pinPatch2->SetFromPin(3);
        pinPatch2->SetToPin(4);

        // Inventory
        IGdtfGeometryPtr geometry10;
        __checkVCOM(geometry1->CreateGeometry(EGdtfObjectType::eGdtfGeometryInventory, "Geometry10 Inventory", filledModel, STransformMatrix(), &geometry10));
        __checkVCOM(geometry10->SetInventoryCount(10));

        // Structure
        IGdtfGeometryPtr geometry11;
        __checkVCOM(geometry1->CreateGeometry(EGdtfObjectType::eGdtfGeometryStructure, "Geometry11 Structure", filledModel, STransformMatrix(), &geometry11));
        __checkVCOM(geometry11->SetStructureLinkedGeometry(geometry10));
        __checkVCOM(geometry11->SetStructureType(EGdtfStructureType::Detail));
        __checkVCOM(geometry11->SetCrossSectionType(EGdtfCrossSectionType::TrussFramework));
        __checkVCOM(geometry11->SetCrossSectionHeight(1.1));
        __checkVCOM(geometry11->SetCrossSectionWallThickness(1.2));
        __checkVCOM(geometry11->SetTrussCrossSection("My TrussCrossSection"));

        // Support
        IGdtfGeometryPtr geometry12;
        __checkVCOM(geometry1->CreateGeometry(EGdtfObjectType::eGdtfGeometrySupport, "Geometry12 Support", filledModel, STransformMatrix(), &geometry12));
        __checkVCOM(geometry12->SetSupportType(EGdtfSupportType::GroundSupport));
        __checkVCOM(geometry12->SetCapacityX(1.1));
        __checkVCOM(geometry12->SetCapacityY(1.2));
        __checkVCOM(geometry12->SetCapacityZ(1.3));
        __checkVCOM(geometry12->SetCapacityXX(1.4));
        __checkVCOM(geometry12->SetCapacityYY(1.5));
        __checkVCOM(geometry12->SetCapacityZZ(1.6));
        __checkVCOM(geometry12->SetRopeCrossSection("My RopeCrossSection"));
        __checkVCOM(geometry12->SetRopeOffset(0.1, 0.2, 0.3));
        __checkVCOM(geometry12->SetResistanceX(2.1));
        __checkVCOM(geometry12->SetResistanceY(2.2));
        __checkVCOM(geometry12->SetResistanceZ(2.3));
        __checkVCOM(geometry12->SetResistanceXX(2.4));
        __checkVCOM(geometry12->SetResistanceYY(2.5));
        __checkVCOM(geometry12->SetResistanceZZ(2.6));
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
        checkifEqual("Second Level Geometry Count", second_level, (size_t)11);


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

        //-------------------------------------------------------------------------------------------------
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

        size_t laserProtocolCount = 0;
        __checkVCOM(geoLaser->GetLaserProtocolCount(laserProtocolCount));
        checkifEqual("LaserProtocol count", laserProtocolCount, (size_t)2);

        IGdtfLaserProtocolPtr laserProtocol1;
        __checkVCOM(geoLaser->GetLaserProtocolAt(0, &laserProtocol1));
        checkifEqual("LaserProtocol 1 Name", laserProtocol1->GetName(), "My Laser Protocol 1");

        IGdtfLaserProtocolPtr laserProtocol2;
        __checkVCOM(geoLaser->GetLaserProtocolAt(1, &laserProtocol2));
        checkifEqual("LaserProtocol 2 Name", laserProtocol2->GetName(), "My Laser Protocol 2");


        //-------------------------------------------------------------------------------------------------
        // WiringObject
        IGdtfGeometryPtr geoWiringObject;
        __checkVCOM(geometry1->GetInternalGeometryAt(5, &geoWiringObject));
        checkifEqual("WiringObject Geometry Name", geoWiringObject->GetName(), "Geometry7 WiringObject");

        checkifEqual("WiringObject ConnectorType", geoWiringObject->GetConnectorType(), "My ConnectorType");

        EGdtfComponentType componentType = EGdtfComponentType::Input;
        __checkVCOM(geoWiringObject->GetComponentType(componentType));
        checkifEqual("WiringObject ComponentType", (size_t)componentType, (size_t)EGdtfComponentType::Consumer);

        checkifEqual("WiringObject SignalType", geoWiringObject->GetSignalType(), "My SignalType");

        size_t pinCount = 0;
        __checkVCOM(geoWiringObject->GetPinCount(pinCount));
        checkifEqual("WiringObject PinCount", pinCount, (size_t)3);

        size_t signalLayer = 0;
        __checkVCOM(geoWiringObject->GetSignalLayer(signalLayer));
        checkifEqual("WiringObject SignalLayer", signalLayer, (size_t)1);

        EGdtfOrientation orientation = EGdtfOrientation::Left;
        __checkVCOM(geoWiringObject->GetOrientation(orientation));
        checkifEqual("WiringObject Orientation", (size_t)orientation, (size_t)EGdtfOrientation::Top);

        checkifEqual("WiringObject WireGroup", geoWiringObject->GetWireGroup(), "My WireGroup");

        double electricalPayLoad = 0.0;
        __checkVCOM(geoWiringObject->GetElectricalPayLoad(electricalPayLoad));
        checkifEqual("WiringObject ElectricalPayLoad", electricalPayLoad, 1.1);

        double voltageRangeMin = 0.0;
        __checkVCOM(geoWiringObject->GetVoltageRangeMin(voltageRangeMin));
        checkifEqual("WiringObject VoltageRangeMin", voltageRangeMin, 1.2);

        double voltageRangeMax = 0.0;
        __checkVCOM(geoWiringObject->GetVoltageRangeMax(voltageRangeMax));
        checkifEqual("WiringObject VoltageRangeMax", voltageRangeMax, 1.3);

        double frequencyRangeMin = 0.0;
        __checkVCOM(geoWiringObject->GetFrequencyRangeMin(frequencyRangeMin));
        checkifEqual("WiringObject FrequencyRangeMin", frequencyRangeMin, 1.4);

        double frequencyRangeMax = 0.0;
        __checkVCOM(geoWiringObject->GetFrequencyRangeMax(frequencyRangeMax));
        checkifEqual("WiringObject FrequencyRangeMax", frequencyRangeMax, 1.5);

        double cosPhi = 0.0;
        __checkVCOM(geoWiringObject->GetCosPhi(cosPhi));
        checkifEqual("WiringObject CosPhi", cosPhi, 1.6);

        double maxPayLoad = 0.0;
        __checkVCOM(geoWiringObject->GetMaxPayLoad(maxPayLoad));
        checkifEqual("WiringObject MaxPayLoad", maxPayLoad, 1.7);

        double voltage = 0.0;
        __checkVCOM(geoWiringObject->GetVoltage(voltage));
        checkifEqual("WiringObject Voltage", voltage, 1.8);

        double fuseCurrent = 0.0;
        __checkVCOM(geoWiringObject->GetFuseCurrent(fuseCurrent));
        checkifEqual("WiringObject FuseCurrent", fuseCurrent, 1.9);

        EGdtfFuseRating fuseRating = EGdtfFuseRating::B;
        __checkVCOM(geoWiringObject->GetFuseRating(fuseRating));
        checkifEqual("WiringObject FuseRating", (size_t)fuseRating, (size_t)EGdtfFuseRating::Z);


        size_t pinPatchCount = 0;
        __checkVCOM(geoWiringObject->GetPinPatchCount(pinPatchCount));
        checkifEqual("WiringObject PinPatch count", pinPatchCount, (size_t)2);

        IGdtfPinPatchPtr pinPatch1;
        __checkVCOM(geoWiringObject->GetPinPatchAt(0, &pinPatch1));

        IGdtfGeometryPtr toWiringObject1;
        __checkVCOM(pinPatch1->GetLinkedWiringObject(&toWiringObject1));
        checkifEqual("PinPatch1 toWiringObject name", toWiringObject1->GetName(), "toWiringObject8");

        size_t fromPin1 = 0;
        __checkVCOM(pinPatch1->GetFromPin(fromPin1));
        checkifEqual("PinPatch1 fromPin", fromPin1, (size_t)1);

        size_t toPin1 = 0;
        __checkVCOM(pinPatch1->GetToPin(toPin1));
        checkifEqual("PinPatch1 toPin", toPin1, (size_t)2);
        
        IGdtfPinPatchPtr pinPatch2;
        __checkVCOM(geoWiringObject->GetPinPatchAt(1, &pinPatch2));

        IGdtfGeometryPtr toWiringObject2;
        __checkVCOM(pinPatch2->GetLinkedWiringObject(&toWiringObject2));
        checkifEqual("PinPatch2 toWiringObject name", toWiringObject2->GetName(), "toWiringObject9");

        size_t fromPin2 = 0;
        __checkVCOM(pinPatch2->GetFromPin(fromPin2));
        checkifEqual("PinPatch2 fromPin", fromPin2, (size_t)3);

        size_t toPin2 = 0;
        __checkVCOM(pinPatch2->GetToPin(toPin2));
        checkifEqual("PinPatch2 toPin", toPin2, (size_t)4);

        //-------------------------------------------------------------------------------------------------
        // Inventory
        IGdtfGeometryPtr geoInventory;
        __checkVCOM(geometry1->GetInternalGeometryAt(8, &geoInventory));
        checkifEqual("Inventory Geometry Name", geoInventory->GetName(), "Geometry10 Inventory");

        size_t inventoryCount = 0;
        __checkVCOM(geoInventory->GetInventoryCount(inventoryCount));
        checkifEqual("Inventory Count", inventoryCount, (size_t)10);

        //-------------------------------------------------------------------------------------------------
        // Structure
        IGdtfGeometryPtr geoStructure;
        __checkVCOM(geometry1->GetInternalGeometryAt(9, &geoStructure));
        checkifEqual("Structure Geometry Name", geoStructure->GetName(), "Geometry11 Structure");

        IGdtfGeometryPtr structureLinkedGeometry;
        __checkVCOM(geoStructure->GetStructureLinkedGeometry(&structureLinkedGeometry));
        checkifEqual("Structure linked geometry name", structureLinkedGeometry->GetName(), "Geometry10 Inventory");

        EGdtfStructureType structureType = EGdtfStructureType::CenterLineBased;
        __checkVCOM(geoStructure->GetStructureType(structureType));
        checkifEqual("Structure StructureType", (size_t)structureType, (size_t)EGdtfStructureType::Detail);

        EGdtfCrossSectionType crossSectionType = EGdtfCrossSectionType::Tube;
        __checkVCOM(geoStructure->GetCrossSectionType(crossSectionType));
        checkifEqual("Structure CrossSectionType", (size_t)crossSectionType, (size_t)EGdtfCrossSectionType::TrussFramework);

        double crossSectionHeight = 0.0;
        __checkVCOM(geoStructure->GetCrossSectionHeight(crossSectionHeight));
        checkifEqual("Structure CrossSectionHeight", crossSectionHeight, 1.1);

        double crossSectionWallThickness = 0.0;
        __checkVCOM(geoStructure->GetCrossSectionWallThickness(crossSectionWallThickness));
        checkifEqual("Structure CrossSectionWallThickness", crossSectionWallThickness, 1.2);

        checkifEqual("Structure TrussCrossSection", geoStructure->GetTrussCrossSection(), "My TrussCrossSection");

        //-------------------------------------------------------------------------------------------------
        // Support
        IGdtfGeometryPtr geoSupport;
        __checkVCOM(geometry1->GetInternalGeometryAt(10, &geoSupport));
        checkifEqual("Support Geometry Name", geoSupport->GetName(), "Geometry12 Support");

        EGdtfSupportType supportType = EGdtfSupportType::Rope;
        __checkVCOM(geoSupport->GetSupportType(supportType));
        checkifEqual("Support SupportType", (size_t)supportType, (size_t)EGdtfSupportType::GroundSupport);

        double capacityX = 0.0;
        __checkVCOM(geoSupport->GetCapacityX(capacityX));
        checkifEqual("Support CapacityX", capacityX, 1.1);

        double capacityY = 0.0;
        __checkVCOM(geoSupport->GetCapacityY(capacityY));
        checkifEqual("Support CapacityY", capacityY, 1.2);

        double capacityZ = 0.0;
        __checkVCOM(geoSupport->GetCapacityZ(capacityZ));
        checkifEqual("Support CapacityZ", capacityZ, 1.3);

        double capacityXX = 0.0;
        __checkVCOM(geoSupport->GetCapacityXX(capacityXX));
        checkifEqual("Support CapacityXX", capacityXX, 1.4);

        double capacityYY = 0.0;
        __checkVCOM(geoSupport->GetCapacityYY(capacityYY));
        checkifEqual("Support CapacityYY", capacityYY, 1.5);

        double capacityZZ = 0.0;
        __checkVCOM(geoSupport->GetCapacityZZ(capacityZZ));
        checkifEqual("Support CapacityZZ", capacityZZ, 1.6);

        checkifEqual("Support RopeCrossSection", geoSupport->GetRopeCrossSection(), "My RopeCrossSection");

        SVector3 ropeOffset;
        __checkVCOM(geoSupport->GetRopeOffset(ropeOffset));
        checkifEqual("Support RopeOffset X", ropeOffset.x, 0.1);
        checkifEqual("Support RopeOffset Y", ropeOffset.y, 0.2);
        checkifEqual("Support RopeOffset Z", ropeOffset.z, 0.3);

        double resistanceX = 0.0;
        __checkVCOM(geoSupport->GetResistanceX(resistanceX));
        checkifEqual("Support ResistanceX", resistanceX, 2.1);

        double resistanceY = 0.0;
        __checkVCOM(geoSupport->GetResistanceY(resistanceY));
        checkifEqual("Support ResistanceY", resistanceY, 2.2);

        double resistanceZ = 0.0;
        __checkVCOM(geoSupport->GetResistanceZ(resistanceZ));
        checkifEqual("Support ResistanceZ", resistanceZ, 2.3);

        double resistanceXX = 0.0;
        __checkVCOM(geoSupport->GetResistanceXX(resistanceXX));
        checkifEqual("Support ResistanceXX", resistanceXX, 2.4);

        double resistanceYY = 0.0;
        __checkVCOM(geoSupport->GetResistanceYY(resistanceYY));
        checkifEqual("Support ResistanceYY", resistanceYY, 2.5);

        double resistanceZZ = 0.0;
        __checkVCOM(geoSupport->GetResistanceZZ(resistanceZZ));
        checkifEqual("Support ResistanceZZ", resistanceZZ, 2.6);
    }

}

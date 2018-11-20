//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include "GdtfUnittest.h"
#include <iostream>

#include "Include/VectorworksMVR.h"
using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;


#define __checkVCOM(x) this->checkVCOM(x, #x)

GdtfUnittest::GdtfUnittest(const std::string& currentDir)
{
    fPath = currentDir;
    fPath += std::string("/testGdtf.gdtf");

    std::cout << "Export File to" << fPath << std::endl; 
}

GdtfUnittest::~GdtfUnittest()
{
    
}

bool GdtfUnittest::ExecuteTest()
{
	std::cout << "=                                        GdtfUnittest                                      =" << std::endl;
    WriteFile();
    ReadFile();

    return true;
}

void GdtfUnittest::WriteFile()
{
	//------------------------------------------------------------------------------------------------
	// Create Pointer to GDTF Interface
	IGdtfFixturePtr gdtfWrite (IID_IGdtfFixture);

    MvrUUID uuid (225204211, 177198167, 1575790, 96627);
	MvrUUID linkedUuid (2227440, 1542265, 1573622, 2328410);
    if(__checkVCOM(gdtfWrite->OpenForWrite(fPath.c_str(),"My FixtureName","My Manufacturer", uuid)))
    {
		__checkVCOM(gdtfWrite->SetFixtureTypeDescription("My Description"));
		__checkVCOM(gdtfWrite->SetShortName("My shortName"));
		__checkVCOM(gdtfWrite->SetFixtureThumbnail("My thumbnail"));
		__checkVCOM(gdtfWrite->SetLinkedFixtureGUID(linkedUuid));

		IGdtfActivationGroupPtr gdtfActGroup;
		IGdtfFeaturePtr			gdtfFeature;
		__checkVCOM(gdtfWrite->CreateActivationGroup("My actGroupName", &gdtfActGroup));

		IGdtfFeatureGroupPtr gdtfFeatureGroup;
		if (__checkVCOM(gdtfWrite->CreateFeatureGroup("My featureGroupName", "My featureGroupPrettyName", &gdtfFeatureGroup)))
		{
			
			__checkVCOM(gdtfFeatureGroup->CreateFeature("My featureName", &gdtfFeature));
		}
		
		IGdtfAttributePtr gdtfAttribute;
		if (__checkVCOM(gdtfWrite->CreateAttribute("My nameAttribute", "My prettyNameAttribute", &gdtfAttribute)))
		{
			__checkVCOM(gdtfAttribute->SetActivationGroup(gdtfActGroup));
			__checkVCOM(gdtfAttribute->SetFeature(gdtfFeature));

			__checkVCOM(gdtfAttribute->SetPhysicalUnit(EGdtfPhysicalUnit::Angle));

			CieColor cieCol;
			cieCol.fx  = 1.0;
			cieCol.fy  = 0.5;
			cieCol.f_Y = 0.4242424242;
			__checkVCOM(gdtfAttribute->SetColor(cieCol));	//TODO maybe

			// Child TODO maybe
		}

		IGdtfWheelPtr wheel1;
		if (__checkVCOM(gdtfWrite->CreateWheel("My Wheel1", &wheel1)))
		{
			IGdtfWheelSlotPtr wheel1Slot;
			if (__checkVCOM(wheel1->CreateWheelSlot("My WheelSlot1Wheel1", &wheel1Slot)))
			{
				CieColor cieCol;
				cieCol.fx  = 0.5;
				cieCol.fy  = 0.4242424242;
				cieCol.f_Y = 1.0;
				__checkVCOM(wheel1Slot->SetColor(cieCol));

				STransformMatrix ma;
				ma.ux = 1;
				ma.uy = 2;
				ma.uz = 3;

				ma.vx = 4;
				ma.vy = 5;
				ma.vz = 6;

				ma.wx = 7;
				ma.wy = 8;
				ma.wz = 9;

				ma.ox = 10;
				ma.oy = 11;
				ma.oz = 12;

				CieColor facetCol;
				facetCol.fx  = 0.4242424242;
				facetCol.fy  = 1.0;
				facetCol.f_Y = 0.5;

				IGdtfWheelSlotPrismFacetPtr gdtfFacet;
				if (__checkVCOM(wheel1Slot->CreatePrismFacet(ma, &gdtfFacet)))
				{
					__checkVCOM(gdtfFacet->SetColor(facetCol));
				}
			}
		}

		IGdtfPhysicalEmitterPtr gdtfEmitter;
		CieColor color;
		color.fx = 1.0;
		color.fy = 0.5;
		color.f_Y = 0.4242424242;
		if (__checkVCOM(gdtfWrite->CreateEmitter("My nameEmitter", color, &gdtfEmitter)))
		{
			IGdtfMeasurementPointPtr gdtfMeasurement;
			__checkVCOM(gdtfEmitter->CreateMeasurementPoint(100, 200, &gdtfMeasurement));
		}

		//------------------------------------------------------------------------------------------------------------------
		// Handle Models
		IGdtfModelPtr gdtfModel;
		if (__checkVCOM(gdtfWrite->CreateModel("My nameModel", &gdtfModel)))
		{
			__checkVCOM(gdtfModel->Set3DSGeometryFile("My file3DSGeometry"));
			__checkVCOM(gdtfModel->SetHeight(10));
			__checkVCOM(gdtfModel->SetWidth(20));
			__checkVCOM(gdtfModel->SetLength(30));
			__checkVCOM(gdtfModel->SetPrimitiveType(EGdtfModel_PrimitiveType::eGdtfModel_PrimitiveType_Sphere));
		}

		//------------------------------------------------------------------------------------------------------------------
		// Handle Geometry
		
		STransformMatrix ma;
		ma.ux = 1;ma.vx = 4;ma.wx = 7;ma.ox = 10;
		ma.uy = 2;ma.vy = 5;ma.wy = 8;ma.oy = 11;
		ma.uz = 3;ma.vz = 6;ma.wz = 9;ma.oz = 12;

		// Create First child
		IGdtfGeometryPtr childGeo;
		__checkVCOM(gdtfWrite->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "My nameGeometry", gdtfModel, ma, &childGeo));

		// Create Child in Child
		IGdtfGeometryPtr innerChild;
		__checkVCOM(childGeo->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "My Inner Geo", gdtfModel, ma, &innerChild));

		IGdtfGeometryPtr geoRef1;
		__checkVCOM(gdtfWrite->CreateGeometry(EGdtfObjectType::eGdtfGeometryReference, "My Reference", gdtfModel, ma, &geoRef1));
		__checkVCOM(geoRef1->SetGeometryReference(childGeo));

		IGdtfGeometryPtr geoRef2;
		__checkVCOM(gdtfWrite->CreateGeometry(EGdtfObjectType::eGdtfGeometryReference, "My Ref to Inner Obj", gdtfModel, ma, &geoRef2));
		__checkVCOM(geoRef2->SetGeometryReference(innerChild));


		IGdtfDmxModePtr gdtfDmxMode;
		if (__checkVCOM(gdtfWrite->CreateDmxMode("My nameDmxMode", &gdtfDmxMode)))
		{
			__checkVCOM(gdtfDmxMode->SetGeometry(childGeo));
			
			IGdtfDmxChannelPtr gdtfDmxChannel;
			if (__checkVCOM(gdtfDmxMode->CreateDmxChannel("My nameDmxChannel", &gdtfDmxChannel)))
			{
				__checkVCOM(gdtfDmxChannel->SetCoarse(1));
				__checkVCOM(gdtfDmxChannel->SetFine(2));
				__checkVCOM(gdtfDmxChannel->SetUltra(3));
				__checkVCOM(gdtfDmxChannel->SetUber(4));
				__checkVCOM(gdtfDmxChannel->SetDmxFrequency(EGdtfDmxFrequency::eGdtfDmxFrequency_30));
				__checkVCOM(gdtfDmxChannel->SetDefaultValue(5));
				__checkVCOM(gdtfDmxChannel->SetHighlight(6));
				__checkVCOM(gdtfDmxChannel->SetDmxBreak(7));
				__checkVCOM(gdtfDmxChannel->SetMoveInBlackFrames(8));
				__checkVCOM(gdtfDmxChannel->SetDmxChangeTimeLimit(9));
				__checkVCOM(gdtfDmxChannel->SetGeometry(childGeo));

				IGdtfDmxLogicalChannelPtr gdtfLogicalChannel;
				if (__checkVCOM(gdtfDmxChannel->CreateLogicalChannel("My nameLogicalChannel", &gdtfLogicalChannel)))
				{
					__checkVCOM(gdtfLogicalChannel->SetAttribute(gdtfAttribute));
					__checkVCOM(gdtfLogicalChannel->SetDmxMaster(EGdtfDmxMaster::eGdtfDmxMaster_Grand));
					__checkVCOM(gdtfLogicalChannel->SetDmxSnap(EGdtfDmxSnap::eGdtfDmxMaster_On));

					IGdtfDmxChannelFunctionPtr gdftChannelFunction;
					if (__checkVCOM(gdtfLogicalChannel->CreateDmxFunction("My nameDmxFunction", &gdftChannelFunction)))
					{
						IGdtfAttributePtr attribute;
						__checkVCOM(gdftChannelFunction->SetAttribute(gdtfAttribute));
						__checkVCOM(gdftChannelFunction->SetOriginalAttribute("My orginalAttribute"));
						__checkVCOM(gdftChannelFunction->SetStartAddress(1));
						__checkVCOM(gdftChannelFunction->SetPhysicalStart(2));
						__checkVCOM(gdftChannelFunction->SetPhysicalEnd(3));
						__checkVCOM(gdftChannelFunction->SetRealFade(4));
						__checkVCOM(gdftChannelFunction->SetDMXInvert(EGDTFDmxInvert::eGDTFDmxInvert_No));
						__checkVCOM(gdftChannelFunction->SetEncoderInvert(EGDTFEncoderInvert::eGDTFEncoderInvert_Yes));

						IGdtfDmxChannelSetPtr gdtfChannelSet;
						if (__checkVCOM(gdftChannelFunction->CreateDmxChannelSet("My nameDmxChannelSet", 1, 2, &gdtfChannelSet)))
						{
							__checkVCOM(gdtfChannelSet->SetPhysicalEnd(20));
							__checkVCOM(gdtfChannelSet->SetPhysicalStart(10));
							__checkVCOM(gdtfChannelSet->SetWheelSlot(11));
						}
					}
				}
			}
		}

        __checkVCOM(gdtfWrite->Close());
    }
}

void GdtfUnittest::ReadFile()
{
	//------------------------------------------------------------------------------------------------
	// Create Pointer to GDTF Interface
    IGdtfFixturePtr gdtfRead (IID_IGdtfFixture);
    if(__checkVCOM(gdtfRead->ReadFromFile(fPath.c_str())))
    {
		// Check Fixture Name
		MvrString fixtureName = gdtfRead->GetName();
		this->checkifEqual("GetName", fixtureName, "My FixtureName");

		MvrString fixtureShortName = gdtfRead->GetShortName();
		this->checkifEqual("GetShortName", fixtureShortName, "My shortName");

		MvrString manufacturer = gdtfRead->GetManufacturer();
		this->checkifEqual("GetManufacturer", manufacturer, "My Manufacturer");

		MvrString description = gdtfRead->GetFixtureTypeDescription();
		this->checkifEqual("GetFixtureTypeDescription", description, "My Description");

		MvrUUID fixtureId(0,0,0,0);
		__checkVCOM(gdtfRead->GetFixtureGUID(fixtureId));
		this->checkifEqual("GetFixtureGUID uuid.a", fixtureId.a, 225204211);
		this->checkifEqual("GetFixtureGUID uuid.b", fixtureId.b, 177198167);
		this->checkifEqual("GetFixtureGUID uuid.c", fixtureId.c, 1575790);
		this->checkifEqual("GetFixtureGUID uuid.d", fixtureId.d, 96627);
		
		MvrString pngFileName = gdtfRead->GetFixtureThumbnail();
		this->checkifEqual("GetFixtureThumbnail", pngFileName, "My thumbnail");

		// TODO, how does the path to look exactly, i guess nothing fancy
		MvrString fullPath = gdtfRead->GetFixtureThumbnail();
		this->checkifEqual("GetFixtureThumbnail", fullPath, "My thumbnail");

		MvrUUID linkedUuid(0, 0, 0, 0);
		bool hasLinkedFixture = false;
		__checkVCOM(gdtfRead->HasLinkedFixtureGUID(hasLinkedFixture));
		__checkVCOM(gdtfRead->GetLinkedFixtureGUID(linkedUuid));
		this->checkifEqual("GetFixtureGUID linkedUuid.a", linkedUuid.a, 2227440);
		this->checkifEqual("GetFixtureGUID linkedUuid.b", linkedUuid.b, 1542265);
		this->checkifEqual("GetFixtureGUID linkedUuid.c", linkedUuid.c, 1573622);
		this->checkifEqual("GetFixtureGUID linkedUuid.d", linkedUuid.d, 2328410);

		//--------------------------------------------------------------------------------
		// Wheel Section
		size_t countWheels = 0;
		__checkVCOM(gdtfRead->GetWheelCount(countWheels));
		{
			for (size_t i = 0; i < countWheels; i++)
			{
				IGdtfWheelPtr gdtfWheel;
				if (__checkVCOM(gdtfRead->GetWheelAt(i, &gdtfWheel)))
				{
					MvrString wheelName = gdtfWheel->GetName();
					this->checkifEqual("GetGdtfWheelName", wheelName, "My Wheel1");

					size_t countSlots = 0;
					__checkVCOM(gdtfWheel->GetWheelSlotCount(countSlots));
					for (size_t j = 0; j < countSlots; j++)
					{
						IGdtfWheelSlotPtr gdtfSlot;
						__checkVCOM(gdtfWheel->GetWheelSlotAt(j, &gdtfSlot));

						MvrString slotName = gdtfSlot->GetName();
						this->checkifEqual("GetGdtfSlotName", slotName, "My WheelSlot1Wheel1");

						size_t prismFacetCount = 0;
						__checkVCOM(gdtfSlot->GetPrismFacetCount(prismFacetCount));
						for (size_t k = 0; k < prismFacetCount; k++)
						{
							IGdtfWheelSlotPrismFacetPtr prismFacet;
							if (__checkVCOM(gdtfSlot->GetPrismFacetAt(k, &prismFacet)))
							{
								CieColor color;
								color.fx = 0;
								color.fy = 0;
								color.f_Y = 0;
								__checkVCOM(prismFacet->GetColor(color));
								/*this->checkifEqual("GetWheelSlotPrismFacetColorFx",color.fx, 0.424242);
								this->checkifEqual("GetWheelSlotPrismFacetColorFy",color.fy, 1.000000);
								this->checkifEqual("GeWheelSlotPrismFacetColorFY", color.f_Y, 0.500000);*/
							}
							

						}
					}

				}

			}
		}

		//--------------------------------------------------------------------------------
		// Geometry Section Section
		size_t countGeo = 0;
		__checkVCOM(gdtfRead->GetGeometryCount(countGeo));
		this->checkifEqual("Geometry Count", countGeo, 3);

		IGdtfGeometryPtr geo1;
		__checkVCOM(gdtfRead->GetGeometryAt(0, &geo1));

		IGdtfGeometryPtr geo2;
		__checkVCOM(gdtfRead->GetGeometryAt(1, &geo2));

		IGdtfGeometryPtr geo3;
		__checkVCOM(gdtfRead->GetGeometryAt(2, &geo3));

		if(geo1 && geo2)
		{
			IGdtfGeometryPtr refedGeo;
			if(__checkVCOM(geo2->GetGeometryReference(&refedGeo)))
			{
				this->checkifEqual("Geo Link", geo1->GetName(), refedGeo->GetName());
			}			
		}

		if(geo3)
		{
			IGdtfGeometryPtr refedGeo;
			if(__checkVCOM(geo3->GetGeometryReference(&refedGeo)))
			{
				this->checkifEqual("Geo Link Inner", "My Inner Geo", refedGeo->GetName());
			}
		}

    }
}
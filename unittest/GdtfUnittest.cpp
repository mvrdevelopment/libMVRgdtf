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
	std::cout << "=                    GdtfUnittest                    =" << std::endl;
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
    if(__checkVCOM(gdtfWrite->OpenForWrite(fPath.c_str(),"FixtureName","Manufacturer", uuid)))
    {
		__checkVCOM(gdtfWrite->SetFixtureTypeDescription("Description"));
		__checkVCOM(gdtfWrite->SetShortName("shortName"));
		__checkVCOM(gdtfWrite->SetFixtureThumbnail("thumbnail"));
		__checkVCOM(gdtfWrite->SetLinkedFixtureGUID(linkedUuid));

		IGdtfActivationGroupPtr gdtfActGroup;
		__checkVCOM(gdtfWrite->CreateActivationGroup("actGroupName", &gdtfActGroup));

		IGdtfFeatureGroupPtr gdtfFeatureGroup;
		if (__checkVCOM(gdtfWrite->CreateFeatureGroup("featureGroupName", "featureGroupPrettyName", &gdtfFeatureGroup)))
		{
			IGdtfFeaturePtr gdtfFeature;
			__checkVCOM(gdtfFeatureGroup->CreateFeature("featureName", &gdtfFeature));
		}
		
		IGdtfAttributePtr gdtfAttribute;
		if (__checkVCOM(gdtfWrite->CreateAttribute("nameAttribute", "prettyNameAttribute", &gdtfAttribute)))
		{
			IGdtfActivationGroupPtr gdtfActivattionGroupLink;
			__checkVCOM(gdtfAttribute->SetActivationGroup(gdtfActivattionGroupLink));

			IGdtfFeaturePtr gdtfFeatureLink;
			__checkVCOM(gdtfAttribute->SetFeature(gdtfFeatureLink));

			EGdtfPhysicalUnit unit = EGdtfPhysicalUnit::Angle;
			__checkVCOM(gdtfAttribute->SetPhysicalUnit(unit));

			CieColor cieCol;
			cieCol.fx  = 1.0;
			cieCol.fy  = 0.5;
			cieCol.f_Y = 0.4242424242;
			__checkVCOM(gdtfAttribute->SetColor(cieCol));	//TODO maybe

			// Child TODO maybe
		}

		IGdtfWheelPtr wheel1;
		if (__checkVCOM(gdtfWrite->CreateWheel("Wheel 1", &wheel1)))
		{
			IGdtfWheelSlotPtr wheel1Slot;
			if (__checkVCOM(wheel1->CreateWheelSlot("WheelSlot1 Wheel1", &wheel1Slot)))
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
		if (__checkVCOM(gdtfWrite->CreateEmitter("nameEmitter", color, &gdtfEmitter)))
		{
			IGdtfMeasurementPointPtr gdtfMeasurement;
			__checkVCOM(gdtfEmitter->CreateMeasurementPoint(100, 200, &gdtfMeasurement));
		}

		IGdtfModelPtr gdtfModel;
		if (__checkVCOM(gdtfWrite->CreateModel("nameModel", &gdtfModel)))
		{
			__checkVCOM(gdtfModel->Set3DSGeometryFile("file3DSGeometry"));
			__checkVCOM(gdtfModel->SetHeight(10));
			__checkVCOM(gdtfModel->SetWidth(20));
			__checkVCOM(gdtfModel->SetLength(30));
			EGdtfModel_PrimitiveType primType = EGdtfModel_PrimitiveType::eGdtfModel_PrimitiveType_Sphere;
			__checkVCOM(gdtfModel->SetPrimitiveType(primType));
		}

		IGdtfModelPtr model;
		IGdtfGeometryPtr childGeo;
		EGdtfObjectType objectType = EGdtfObjectType::eGdtfRDMValue_UNSIGNED_BYTE;
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
		__checkVCOM(gdtfWrite->CreateGeometry(objectType, "nameGeometry", model, ma, &childGeo));

		IGdtfDmxModePtr gdtfDmxMode;
		if (__checkVCOM(gdtfWrite->CreateDmxMode("nameDmxMode", &gdtfDmxMode)))
		{
			IGdtfGeometryPtr geometry;
			__checkVCOM(gdtfDmxMode->SetGeometry(geometry));
			
			IGdtfDmxChannelPtr gdtfDmxChannel;
			if (__checkVCOM(gdtfDmxMode->CreateDmxChannel("nameDmxChannel", &gdtfDmxChannel)))
			{
				__checkVCOM(gdtfDmxChannel->SetCoarse(1));
				__checkVCOM(gdtfDmxChannel->SetFine(2));
				__checkVCOM(gdtfDmxChannel->SetUltra(3));
				__checkVCOM(gdtfDmxChannel->SetUber(4));
				EGdtfDmxFrequency dmxFrequency = EGdtfDmxFrequency::eGdtfDmxFrequency_30;
				__checkVCOM(gdtfDmxChannel->SetDmxFrequency(dmxFrequency));
				__checkVCOM(gdtfDmxChannel->SetDefaultValue(5));
				__checkVCOM(gdtfDmxChannel->SetHighlight(6));
				__checkVCOM(gdtfDmxChannel->SetDmxBreak(7));
				__checkVCOM(gdtfDmxChannel->SetMoveInBlackFrames(8));
				__checkVCOM(gdtfDmxChannel->SetDmxChangeTimeLimit(9));
				IGdtfGeometryPtr geometry;
				__checkVCOM(gdtfDmxChannel->SetGeometry(geometry));

				IGdtfDmxLogicalChannelPtr gdtfLogicalChannel;
				if (__checkVCOM(gdtfDmxChannel->CreateLogicalChannel("nameLogicalChannel", &gdtfLogicalChannel)))
				{
					IGdtfAttributePtr attribute;
					__checkVCOM(gdtfLogicalChannel->SetAttribute(attribute));
					EGdtfDmxMaster master = EGdtfDmxMaster::eGdtfDmxMaster_Grand;
					__checkVCOM(gdtfLogicalChannel->SetDmxMaster(master));
					EGdtfDmxSnap snap = EGdtfDmxSnap::eGdtfDmxMaster_On;
					__checkVCOM(gdtfLogicalChannel->SetDmxSnap(snap));

					IGdtfDmxChannelFunctionPtr gdftChannelFunction;
					if (__checkVCOM(gdtfLogicalChannel->CreateDmxFunction("nameDmxFunction", &gdftChannelFunction)))
					{
						IGdtfAttributePtr attribute;
						__checkVCOM(gdftChannelFunction->SetAttribute(attribute));
						__checkVCOM(gdftChannelFunction->SetOriginalAttribute("orginalAttribute"));
						__checkVCOM(gdftChannelFunction->SetStartAddress(1));
						__checkVCOM(gdftChannelFunction->SetPhysicalStart(2));
						__checkVCOM(gdftChannelFunction->SetPhysicalEnd(3));
						__checkVCOM(gdftChannelFunction->SetRealFade(4));
						EGDTFDmxInvert dmxInvert = EGDTFDmxInvert::eGDTFDmxInvert_No;
						__checkVCOM(gdftChannelFunction->SetDMXInvert(dmxInvert));
						EGDTFEncoderInvert encoderInvert = EGDTFEncoderInvert::eGDTFEncoderInvert_Yes;
						__checkVCOM(gdftChannelFunction->SetEncoderInvert(encoderInvert));

						IGdtfDmxChannelSetPtr gdtfChannelSet;
						if (__checkVCOM(gdftChannelFunction->CreateDmxChannelSet("nameDmxChannelSet", 1, 2, &gdtfChannelSet)))
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
        this->checkifEqual("GetName", fixtureName, "FixtureName");
        
    }

	
}
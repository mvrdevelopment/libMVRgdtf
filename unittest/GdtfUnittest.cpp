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

    MvrUUID uuid		(225204211	, 177198167	, 1575790	, 96627);
	MvrUUID linkedUuid	(2227440	, 1542265	, 1573622	, 2328410);
    if(__checkVCOM(gdtfWrite->OpenForWrite(fPath.c_str(),"My FixtureName","My Manufacturer", uuid)))
    {
		__checkVCOM(gdtfWrite->SetFixtureTypeDescription("My Description"));
		__checkVCOM(gdtfWrite->SetShortName("My shortName"));
		__checkVCOM(gdtfWrite->SetFixtureThumbnail("My thumbnail"));
		__checkVCOM(gdtfWrite->SetLinkedFixtureGUID(linkedUuid));

		//------------------------------------------------------------------------------    
		// Set Attributes
		IGdtfActivationGroupPtr gdtfActGroup;
		__checkVCOM(gdtfWrite->CreateActivationGroup("My actGroupName", &gdtfActGroup));

		IGdtfFeatureGroupPtr	gdtfFeatureGroup;
		IGdtfFeaturePtr			gdtfFeature;
		if (__checkVCOM(gdtfWrite->CreateFeatureGroup("My featureGroupName", "My featureGroupPrettyName", &gdtfFeatureGroup)))
		{
			__checkVCOM(gdtfFeatureGroup->CreateFeature("My featureName", &gdtfFeature));
		}

		IGdtfAttributePtr		gdtfMainAttribute;
		if (__checkVCOM(gdtfWrite->CreateAttribute("My MainAttributeName", "My MainAttributePrettyName", &gdtfMainAttribute)))
		{
			__checkVCOM(gdtfMainAttribute->SetActivationGroup(gdtfActGroup));
			__checkVCOM(gdtfMainAttribute->SetFeature(gdtfFeature));
			__checkVCOM(gdtfMainAttribute->SetPhysicalUnit(EGdtfPhysicalUnit::Acceleration));

			CieColor cieCol;
			cieCol.fx	= 0.1;
			cieCol.fy	= 0.2;
			cieCol.f_Y	= 0.3;
			__checkVCOM(gdtfMainAttribute->SetColor(cieCol));
		}
		
		IGdtfAttributePtr		gdtfAttribute;
		if (__checkVCOM(gdtfWrite->CreateAttribute("My attributeName", "My attributePrettyName", &gdtfAttribute)))
		{
			__checkVCOM(gdtfAttribute->SetActivationGroup(gdtfActGroup));
			__checkVCOM(gdtfAttribute->SetFeature(gdtfFeature));
			__checkVCOM(gdtfAttribute->SetPhysicalUnit(EGdtfPhysicalUnit::Angle));

			CieColor cieCol;
			cieCol.fx  = 1.0;
			cieCol.fy  = 0.5;
			cieCol.f_Y = 0.424242;
			__checkVCOM(gdtfAttribute->SetColor(cieCol));

			__checkVCOM(gdtfAttribute->SetMainAttribute(gdtfMainAttribute));
			// TODO: CHeck if this comes thru
		}

		//------------------------------------------------------------------------------    
		// Set Wheels
		IGdtfWheelPtr gdtfWheelObj;
		if (__checkVCOM(gdtfWrite->CreateWheel("My Wheel1", &gdtfWheelObj)))
		{
			IGdtfWheelSlotPtr wheelSlotContainer;
			if (__checkVCOM(gdtfWheelObj->CreateWheelSlot("My WheelSlot1Wheel1", &wheelSlotContainer)))
			{
				CieColor cieCol;
				cieCol.fx  = 0.5;
				cieCol.fy  = 0.424242;
				cieCol.f_Y = 1.0;
				__checkVCOM(wheelSlotContainer->SetColor(cieCol));

				// no "ox, oy, oz" entries here
				STransformMatrix ma;
				ma.ux = 1;ma.vx = 4;ma.wx = 7;
				ma.uy = 2;ma.vy = 5;ma.wy = 8;
				ma.uz = 3;ma.vz = 6;ma.wz = 9;

				CieColor facetCol;
				facetCol.fx  = 0.424242;
				facetCol.fy  = 1.0;
				facetCol.f_Y = 0.5;

				IGdtfWheelSlotPrismFacetPtr gdtfFacet;
				if (__checkVCOM(wheelSlotContainer->CreatePrismFacet(ma, &gdtfFacet)))
				{
					__checkVCOM(gdtfFacet->SetColor(facetCol));
				}
			}
		}


		//------------------------------------------------------------------------------    
		// Set Emitter
		IGdtfPhysicalEmitterPtr gdtfEmitter;
		CieColor color;
		color.fx = 1.0;
		color.fy = 0.5;
		color.f_Y = 0.424242;
		if (__checkVCOM(gdtfWrite->CreateEmitter("My emitterName", color, &gdtfEmitter)))
		{
			IGdtfMeasurementPointPtr gdtfMeasurement;
			__checkVCOM(gdtfEmitter->CreateMeasurementPoint(100, 200, &gdtfMeasurement));
		}


		//------------------------------------------------------------------------------------------------------------------
		// Handle Models
		IGdtfModelPtr gdtfModel;
		if (__checkVCOM(gdtfWrite->CreateModel("My modelName", &gdtfModel)))
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


		//------------------------------------------------------------------------------
		// Get dmxModes
		IGdtfDmxModePtr gdtfDmxMode;
		if (__checkVCOM(gdtfWrite->CreateDmxMode("My DmxModeName", &gdtfDmxMode)))
		{
			__checkVCOM(gdtfDmxMode->SetGeometry(childGeo));
			
			IGdtfDmxChannelPtr gdtfDmxChannel;
			if (__checkVCOM(gdtfDmxMode->CreateDmxChannel("My DmxChannelName", &gdtfDmxChannel)))
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


		//------------------------------------------------------------------------------    
		// Close the stream and dump to disk
        __checkVCOM(gdtfWrite->Close());
    }
}

void GdtfUnittest::ReadFile()
{
	//------------------------------------------------------------------------------    
	// Read Fixture Information
	IGdtfFixturePtr gdtfRead (IID_IGdtfFixture);
    if(__checkVCOM(gdtfRead->ReadFromFile(fPath.c_str())))
    {
		// Check Fixture Name
		MvrString fixtureName		= gdtfRead->GetName();
		MvrString fixtureShortName	= gdtfRead->GetShortName();
		MvrString manufacturer		= gdtfRead->GetManufacturer();
		MvrString description		= gdtfRead->GetFixtureTypeDescription();
		this->checkifEqual("GetName "					, fixtureName		, "My FixtureName");
		this->checkifEqual("GetShortName "				, fixtureShortName	, "My shortName");
		this->checkifEqual("GetManufacturer "			, manufacturer		, "My Manufacturer");
		this->checkifEqual("GetFixtureTypeDescription "	, description		, "My Description");

		MvrUUID fixtureId(0,0,0,0);
		__checkVCOM(gdtfRead->GetFixtureGUID(fixtureId));
		this->checkifEqual("GetFixtureGUID uuid.a "		, fixtureId.a		, 225204211);
		this->checkifEqual("GetFixtureGUID uuid.b "		, fixtureId.b		, 177198167);
		this->checkifEqual("GetFixtureGUID uuid.c "		, fixtureId.c		, 1575790);
		this->checkifEqual("GetFixtureGUID uuid.d "		, fixtureId.d		, 96627);
		
		// Get the Image from GDTF File
		MvrString pngFileName		= gdtfRead->GetFixtureThumbnail();
		MvrString fullPath			= gdtfRead->GetFixtureThumbnail();
		this->checkifEqual("GetFixtureThumbnail "		, pngFileName		, "My thumbnail");
		this->checkifEqual("GetFixtureThumbnail "		, fullPath			, "My thumbnail");

		MvrUUID linkedUuid(0, 0, 0, 0);
		bool hasLinkedFixture = false;
		__checkVCOM(gdtfRead->HasLinkedFixtureGUID(hasLinkedFixture));
		__checkVCOM(gdtfRead->GetLinkedFixtureGUID(linkedUuid));
		this->checkifEqual("GetFixtureGUID linkedUuid.a ", linkedUuid.a, 2227440);
		this->checkifEqual("GetFixtureGUID linkedUuid.b ", linkedUuid.b, 1542265);
		this->checkifEqual("GetFixtureGUID linkedUuid.c ", linkedUuid.c, 1573622);
		this->checkifEqual("GetFixtureGUID linkedUuid.d ", linkedUuid.d, 2328410);


		//--------------------------------------------------------------------------------
		// Read Wheels
		size_t countWheels = 0;
		__checkVCOM(gdtfRead->GetWheelCount(countWheels));
		{
			// Wheels loop
			for (size_t i = 0; i < countWheels; i++)
			{
				IGdtfWheelPtr gdtfWheel;
				if (__checkVCOM(gdtfRead->GetWheelAt(i, &gdtfWheel)))
				{
					MvrString wheelName = gdtfWheel->GetName();
					this->checkifEqual("GetGdtfWheelName ", wheelName, "My Wheel1");

					// WheelSlot loop
					size_t countSlots = 0;
					__checkVCOM(gdtfWheel->GetWheelSlotCount(countSlots));
					for (size_t j = 0; j < countSlots; j++)
					{
						IGdtfWheelSlotPtr gdtfSlot;
						__checkVCOM(gdtfWheel->GetWheelSlotAt(j, &gdtfSlot));

						MvrString slotName = gdtfSlot->GetName();
						this->checkifEqual("GetGdtfSlotName ", slotName, "My WheelSlot1Wheel1");

						CieColor color;
						color.fx = 0;
						color.fy = 0;
						color.f_Y = 0;
						__checkVCOM(gdtfSlot->GetColor(color));
						this->checkifEqual("GetWheelSlot1Wheel1ColorFx ",color.fx, 0.500000);
						this->checkifEqual("GetWheelSlot1Wheel1ColorFy ",color.fy, 0.424242);
						this->checkifEqual("GetWheelSlot1Wheel1ColorFY ",color.f_Y, 1.000000);

						// PrismFacets loop
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
								this->checkifEqual("GetWheelSlotPrismFacetColorFx ",color.fx, 0.424242);
								this->checkifEqual("GetWheelSlotPrismFacetColorFy ",color.fy, 1.000000);
								this->checkifEqual("GetWheelSlotPrismFacetColorFY ",color.f_Y, 0.500000);

								// no "ox, oy, oz" entries here
								STransformMatrix matrix;
								__checkVCOM(prismFacet->GetTransformMatrix(matrix));
								this->checkifEqual("GetTransformMatrix.ux ", matrix.ux, 1);
								this->checkifEqual("GetTransformMatrix.uy ", matrix.uy, 2);
								this->checkifEqual("GetTransformMatrix.uz ", matrix.uz, 3);

								this->checkifEqual("GetTransformMatrix.vx ", matrix.vx, 4);
								this->checkifEqual("GetTransformMatrix.vy ", matrix.vy, 5);
								this->checkifEqual("GetTransformMatrix.vz ", matrix.vz, 6);

								this->checkifEqual("GetTransformMatrix.wx ", matrix.wx, 7);
								this->checkifEqual("GetTransformMatrix.wy ", matrix.wy, 8);
								this->checkifEqual("GetTransformMatrix.wz ", matrix.wz, 9);
							}
						} // PrismFacets loop
					} // WheelSlot loop
				}
			} // Wheels loop
		}

		
		//------------------------------------------------------------------------------    
		// Read Emitters
		size_t emitterCount = 0;
		__checkVCOM(gdtfRead->GetEmitterCount(emitterCount));
		for (size_t i = 0; i < emitterCount; i++)
		{
			IGdtfPhysicalEmitterPtr gdtfEmitter;
			if (__checkVCOM(gdtfRead->GetEmitterAt(i, &gdtfEmitter)))
			{
				MvrString emitterName = gdtfEmitter->GetName();
				this->checkifEqual("gdtfEmitterGetName ", emitterName, "My emitterName");

				CieColor color;
				color.fx = 0;
				color.fy = 0;
				color.f_Y = 0;
				gdtfEmitter->GetColor(color);
				this->checkifEqual("gdtfEmitterColorFx ", color.fx, 1.0);
				this->checkifEqual("gdtfEmitterColorFy ", color.fy, 0.5);
				this->checkifEqual("gdtfEmitterColorFY ", color.f_Y, 0.424242);

				size_t measurementsCount = 0;
				__checkVCOM(gdtfEmitter->GetMeasurementPointCount(measurementsCount));
				for (size_t j = 0; j < measurementsCount; j++)
				{
					IGdtfMeasurementPointPtr emitterMeasurement;
					if (__checkVCOM(gdtfEmitter->GetMeasurementPointAt(j, &emitterMeasurement)))
					{
						double waveLength_Val = 0;
						__checkVCOM(emitterMeasurement->GetWaveLength(waveLength_Val));
						this->checkifEqual("GetWaveLength ", waveLength_Val, 100);		// only for object valid, because of hardcoded wavelength and energy

						double energy_Val = 0;
						__checkVCOM(emitterMeasurement->GetEnergy(energy_Val));
						this->checkifEqual("GetEnergy ", energy_Val, 200);				// only for object valid, because of hardcoded wavelength and energy
					}
				} // measurements loop
			}
		} // emitter loop


		//------------------------------------------------------------------------------    
		// Fill Activation Groups Section
		size_t countActivationsGroups = 0;
		__checkVCOM(gdtfRead->GetActivationGroupCount(countActivationsGroups));
		for (size_t i = 0; i < countActivationsGroups; i++)
		{
			IGdtfActivationGroupPtr gdtfActivationGroups;
			if (__checkVCOM(gdtfRead->GetActivationGroupAt(i, &gdtfActivationGroups)))
			{
				// Set the name
				MvrString activationGroupName = gdtfActivationGroups->GetName();
				this->checkifEqual("gdtfActivationGroupsGetName ", activationGroupName, "My actGroupName");

				//------------------------------------------------------------------------------ 
				// Add the Attributes
				size_t countMainAttributes = 0;
				__checkVCOM(gdtfActivationGroups->GetAttributeCount(countMainAttributes));
				for (size_t i = 0; i < countMainAttributes; i++)
				{
					IGdtfAttributePtr	gdtfMainAttribute;
					__checkVCOM(gdtfActivationGroups->GetAttributeAt(i, &gdtfMainAttribute));

					MvrString attributeName			= gdtfMainAttribute->GetName();
					MvrString attributePrettyName	= gdtfMainAttribute->GetPrettyName();
					this->checkifEqual("gdtfMainAttributeGetName "		, attributeName			, "My MainAttributeName");
					this->checkifEqual("gdtfMainAttributeGetPrettyName ", attributePrettyName	, "My MainAttributePrettyName");
				}


				size_t countAttributes = 0;
				__checkVCOM(gdtfActivationGroups->GetAttributeCount(countAttributes));
				for (size_t i = 0; i < countAttributes; i++)
				{
					IGdtfAttributePtr gdtfAttribute;
					__checkVCOM(gdtfActivationGroups->GetAttributeAt(i, &gdtfAttribute));

					MvrString attributeName			= gdtfAttribute->GetName();
					MvrString attributePrettyName	= gdtfAttribute->GetPrettyName();
					this->checkifEqual("gdtfAttributeGetName "		, attributeName			, "My attributeName");
					this->checkifEqual("gdtfAttributeGetPrettyName ", attributePrettyName	, "My attributePrettyName");
				}
			}
		} // ActivationsGroups loop


		//------------------------------------------------------------------------------    
		// Fill Feature Groups
		size_t acountFeatureGroups = 0;
		__checkVCOM(gdtfRead->GetFeatureGroupCount(acountFeatureGroups));
		for (size_t i = 0; i < acountFeatureGroups; i++)
		{
			IGdtfFeatureGroupPtr gdtfFeatureGroup;
			if (__checkVCOM(gdtfRead->GetFeatureGroupAt(i, &gdtfFeatureGroup)))
			{
				MvrString featureGroupName	= gdtfFeatureGroup->GetName();
				MvrString prettyName		= gdtfFeatureGroup->GetPrettyName();
				this->checkifEqual("gdtfFeatureGroupGetName "		, featureGroupName	, "My featureGroupName");
				this->checkifEqual("gdtfFeatureGroupGetPrettyName "	, prettyName		, "My featureGroupPrettyName");

				//------------------------------------------------------------------------------ 
				// Add the Features
				size_t countFeatures = 0;
				__checkVCOM(gdtfFeatureGroup->GetFeatureCount(countFeatures));
				for (size_t i = 0; i < countFeatures; i++)
				{
					IGdtfFeaturePtr gdtfFeature;
					__checkVCOM(gdtfFeatureGroup->GetFeatureAt(i, &gdtfFeature));

					// Set the name
					MvrString featureName = gdtfFeature->GetName();
					this->checkifEqual("gdtfFeatureGetName ", featureName, "My featureName");
				}
			}
		} // FeatureGroups loops


		//------------------------------------------------------------------------------    
		// Extract Geometry & Models
		size_t countModels = 0;
		__checkVCOM(gdtfRead->GetModelCount(countModels));
		for (size_t i = 0; i < countModels; i++)
		{
			IGdtfModelPtr gdtfModel;
			if (__checkVCOM(gdtfRead->GetModelAt(i, &gdtfModel)))
			{
				MvrString  modelName	= gdtfModel->GetName();
				MvrString geometryFile	= gdtfModel->Get3DSGeometryFile();
				this->checkifEqual("gdtfModelGetName "				, modelName		, "My modelName");
				this->checkifEqual("gdtfModelGet3DSGeometryFile "	, geometryFile	, "My file3DSGeometry");

				// Height
				double heightVal = 0.0;
				__checkVCOM(gdtfModel->GetHeight(heightVal));
				this->checkifEqual("gdtfModelGetHeight ", heightVal, 10);

				// Width
				double widthVal = 0.0;
				__checkVCOM(gdtfModel->GetWidth(widthVal));
				this->checkifEqual("gdtfModelGetWidth ", widthVal, 20);

				// Length
				double lengthVal = 0.0;
				__checkVCOM(gdtfModel->GetLength(lengthVal));
				this->checkifEqual("gdtfModelGetLength ", lengthVal, 30);

				// PrimitiveType
				EGdtfModel_PrimitiveType primitiveType = EGdtfModel_PrimitiveType::eGdtfModel_PrimitiveType_Undefined;
				__checkVCOM(gdtfModel->GetPrimitiveType(primitiveType));
				this->checkifEqual("gdtfModelGetPrimitiveType ", primitiveType, EGdtfModel_PrimitiveType::eGdtfModel_PrimitiveType_Sphere);
			}
		} // Models loop


		//--------------------------------------------------------------------------------
		// Geometry Section
		size_t countGeo = 0;
		__checkVCOM(gdtfRead->GetGeometryCount(countGeo));
		this->checkifEqual("Geometry Count ", countGeo, 3);

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
				this->checkifEqual("Geo Link ", geo1->GetName(), refedGeo->GetName());
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
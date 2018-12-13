//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include "MvrUnittest.h"
#include <iostream>

#include "Include/VectorworksMVR.h"
using namespace VectorworksMVR;

#define __checkVCOM(x) checkVCOM(x, #x)
#define __checkVCOM_Failed(x) this->checkVCOM_NotSet(x, #x)

MvrUnittest::MvrUnittest(const std::string& currentDir)
{
    fPath = currentDir;
    fPath += std::string("/testMvr.mvr");
	gdtfPath = currentDir;

    std::cout << "Export File to" << fPath << std::endl; 
}

MvrUnittest::~MvrUnittest()
{
}

bool MvrUnittest::ExecuteTest()
{
	std::cout << "=                                        MvrUnittest                                       =" << std::endl;
    WriteFile();
    ReadFile();

    return true;
}

void MvrUnittest::WriteFile()
{
	//------------------------------------------------------------------------------------------------
	// Create Pointer to MVR Interface
	IMediaRessourceVectorInterfacePtr mvrWrite( IID_MediaRessourceVectorInterface );

	// Set the libary folder for GDTF files, during export the Interface will look in this
	// folder if there is gdtf file that is needed by MVR, and then add it to the ZIP file
	__checkVCOM(mvrWrite->AddGdtfFolderLocation(gdtfPath.c_str()));

	//------------------------------------------------------------------------------------------------
	// Open file for write
    if(__checkVCOM(mvrWrite->OpenForWrite(fPath.c_str())))
    {
        //------------------------------------------------------------------------------------------------
        // Add Custom data
        ISceneDataProviderPtr obj;
        if(__checkVCOM(mvrWrite->CreateDataProviderObject("Test Data", "1", &obj)))
        {
            __checkVCOM(obj->AddKeyValue("Key", "Value"));
        }
        
        //------------------------------------------------------------------------------------------------
        // Write globals
        IPositionPtr position = nullptr;
        __checkVCOM(mvrWrite->CreatePositionObject(MvrUUID(688696821, 558449194, 2115941252, 1809800703), "My Position", & position));


        ISymDefPtr symDef1 = nullptr;
        if(__checkVCOM(mvrWrite->CreateSymDefObject(MvrUUID(122079618, 11832014, 669376348, 947930087), "Symbol Definition for the FocusPoint", & symDef1)))
        {
            __checkVCOM(symDef1->AddGeometry(STransformMatrix(), "My3DSFile"));
        }
        
        IClassPtr clas1 = nullptr;
        __checkVCOM(mvrWrite->CreateClassObject(MvrUUID(122074618, 11852014, 669377348, 947530087), "My first Class", & clas1));

        IClassPtr clas2 = nullptr;
        __checkVCOM(mvrWrite->CreateClassObject(MvrUUID(122774618, 11892014, 669397348, 947530057), "My second Class", & clas2));

        //------------------------------------------------------------------------------------------------
        // Now write content
        ISceneObjPtr layer1 = nullptr;
		__checkVCOM(mvrWrite->CreateLayerObject(MvrUUID(465143117, 742747285, 1361655924, 1172316535), "My Layer 1", &layer1));

		// Create Focus Point
		ISceneObjPtr focusPoint = nullptr;
		if (__checkVCOM(mvrWrite->CreateFocusPoint(MvrUUID(1998334672, 457193269, 1786021763, 1463564339), STransformMatrix(), "My FocusPoint", layer1, &focusPoint)))
		{
			__checkVCOM(focusPoint->AddSymbol(STransformMatrix(), symDef1));
			__checkVCOM(focusPoint->SetClass(clas1));
		}
			
		// And place some fixtures on it
		ISceneObjPtr fixture1 = nullptr;
		if (__checkVCOM(mvrWrite->CreateFixture(MvrUUID(1808353427, 683171502, 518343034, 1766902383), STransformMatrix(), "My Fixture1 Name", layer1, &fixture1)))
		{
			__checkVCOM(fixture1->SetGdtfName("Martin@Mac Aura XB1"));
			__checkVCOM(fixture1->SetGdtfMode("Mode 1 v1.1"));
			__checkVCOM(fixture1->AddAdress(1542, 0));
			__checkVCOM(fixture1->AddAdress(25, 1));
			__checkVCOM(fixture1->SetFocusPoint(focusPoint));
			__checkVCOM(fixture1->SetPosition(position));
			__checkVCOM(fixture1->SetClass(clas2));
		}

		// And another fixture
		ISceneObjPtr fixture2 = nullptr;
		if (__checkVCOM(mvrWrite->CreateFixture(MvrUUID(1136161871, 1699151080, 751939975, 1748783014), STransformMatrix(), "My Fixture2 Name", layer1, &fixture2)))
		{
			__checkVCOM(fixture2->SetGdtfName("Martin@Mac Aura XB2"));
			__checkVCOM(fixture2->SetGdtfMode("My fancy other GDTF DMX Mode"));
			__checkVCOM(fixture2->AddAdress(352, 0));
			__checkVCOM(fixture2->AddAdress(5684, 1));
			__checkVCOM(fixture2->SetFocusPoint(focusPoint));
		}

		// Create second Layer
		ISceneObjPtr layer2 = nullptr;
		__checkVCOM(mvrWrite->CreateLayerObject(MvrUUID(465143117, 742747285, 1361655924, 1172316525), "My Layer 2", &layer2));

		ISceneObjPtr fixture3 = nullptr;
		if (__checkVCOM(mvrWrite->CreateFixture(MvrUUID(1136161871, 1699151080, 751939975, 1748773014), STransformMatrix(), "My Fixture3 Name", layer2, &fixture3)))
		{
			__checkVCOM(fixture3->SetGdtfName("Martin@Mac Aura XB3"));
			__checkVCOM(fixture3->SetGdtfMode("My fancy other GDTF DMX Mode2"));
			__checkVCOM(fixture3->AddAdress(352, 0));
			__checkVCOM(fixture3->AddAdress(5684, 1));
			__checkVCOM(fixture3->SetFocusPoint(focusPoint));
		}
    }
	__checkVCOM(mvrWrite->Close());
}

void MvrUnittest::ReadFile()
{
	//------------------------------------------------------------------------------------------------
	// Create Pointer to MVR Interface
	IMediaRessourceVectorInterfacePtr mvrRead( IID_MediaRessourceVectorInterface );
    if(__checkVCOM(mvrRead->OpenForRead(fPath.c_str())))
    {
		//Check those written UUIDs
		MvrUUID positionUUID	(688696821, 558449194, 2115941252, 1809800703);
		MvrUUID symdefUUID		(122079618, 11832014, 669376348, 947930087);
		MvrUUID layerUUID1		(465143117, 742747285, 1361655924, 1172316535);
		MvrUUID layerUUID2		(465143117, 742747285, 1361655924, 1172316525);
		MvrUUID classUUID1		(122074618, 11852014, 669377348, 947530087);
		MvrUUID classUUID2		(122774618, 11892014, 669397348, 947530057);
		MvrUUID focusPointUUID	(1998334672, 457193269, 1786021763, 1463564339);
		MvrUUID fixtureUUID1	(1808353427, 683171502, 518343034, 1766902383);
		MvrUUID fixtureUUID2	(1136161871, 1699151080, 751939975, 1748783014);
		MvrUUID fixtureUUID3	(1136161871, 1699151080, 751939975, 1748773014);
		MvrUUID resultUUID		(0,0,0,0);

        size_t count = 0;
        __checkVCOM(mvrRead->GetDataProviderObjectCount(count));
        checkifEqual("CountProvider ",count, size_t(1));

        for(size_t i = 0; i <count; i++)
        {
            ISceneDataProviderPtr obj;
            if(__checkVCOM(mvrRead->GetDataProviderObjectAt(i, &obj)))
            {
                MvrString key   = obj->GetKeyAt(0);
                MvrString value = obj->GetValueAt(0);

                checkifEqual("Check Key "  ,"Key"  , key);
                checkifEqual("Check Value ","Value", value);
            }
        }

		//------------------------------------------------------------------------------------------------
		// Read Layers
		ISceneObjPtr readLayer = nullptr;
		__checkVCOM(mvrRead->GetFirstLayer(&readLayer));

		int i(0);
		while (readLayer)
		{
			ISceneObjPtr sceneObj = nullptr;
			__checkVCOM(mvrRead->GetFirstChild(readLayer, &sceneObj));
			
			//Get Data Layer 1
			if (i==0)
			{
				checkifEqual("Layer name", readLayer->GetName(), "My Layer 1");
				__checkVCOM(readLayer->GetGuid(resultUUID));
				this->checkifEqual("GetLayerGuid uuid.a ", resultUUID.a, layerUUID1.a);
				this->checkifEqual("GetLayerGuid uuid.b ", resultUUID.b, layerUUID1.b);
				this->checkifEqual("GetLayerGuid uuid.c ", resultUUID.c, layerUUID1.c);
				this->checkifEqual("GetLayerGuid uuid.d ", resultUUID.d, layerUUID1.d);
			}
			
			//Get Data Layer 2
			if (i==1)
			{
				checkifEqual("Layer name", readLayer->GetName(), "My Layer 2");
				__checkVCOM(readLayer->GetGuid(resultUUID));
				this->checkifEqual("GetLayerGuid uuid.a ", resultUUID.a, layerUUID2.a);
				this->checkifEqual("GetLayerGuid uuid.b ", resultUUID.b, layerUUID2.b);
				this->checkifEqual("GetLayerGuid uuid.c ", resultUUID.c, layerUUID2.c);
				this->checkifEqual("GetLayerGuid uuid.d ", resultUUID.d, layerUUID2.d);
			}
			
			int j(0);
			while (sceneObj)
			{
				ESceneObjType type;
				__checkVCOM(sceneObj->GetType(type));
				if (type == ESceneObjType::FocusPoint)
				{
					ISceneObjPtr focusPointObj;
					__checkVCOM_Failed(sceneObj->GetFocusPoint(&focusPointObj));
					if(i==0 && j==0)
					{		
						checkifEqual("GetFocusPoint name", sceneObj->GetName(), "My FocusPoint");
						__checkVCOM(sceneObj->GetGuid(resultUUID));
						this->checkifEqual("GetFocusPointGuid uuid.a ", resultUUID.a, focusPointUUID.a);
						this->checkifEqual("GetFocusPointGuid uuid.b ", resultUUID.b, focusPointUUID.b);
						this->checkifEqual("GetFocusPointGuid uuid.c ", resultUUID.c, focusPointUUID.c);
						this->checkifEqual("GetFocusPointGuid uuid.d ", resultUUID.d, focusPointUUID.d);
					}
				}

				//if (type == ESceneObjType::Fixture)
				//{
				// 	// Read the GDTF File
				// 	IGdtfFixturePtr fixture;
				// 	if (__checkVCOM(sceneObj->GetGdtfFixture( & fixture)))
				// 	{
						
				// 		if (i==0 && j==1)
				// 		{	
				// 			// Get Fixture1
				// 			checkifEqual("Fixture1 name ", fixture->GetName(), "My Fixture1 Name");
				// 			__checkVCOM(fixture->GetFixtureGUID(resultUUID));
				// 			this->checkifEqual("GetFixtureGuid uuid.a ", resultUUID.a, fixtureUUID1.a);
				// 			this->checkifEqual("GetFixtureGuid uuid.b ", resultUUID.b, fixtureUUID1.b);
				// 			this->checkifEqual("GetFixtureGuid uuid.c ", resultUUID.c, fixtureUUID1.c);
				// 			this->checkifEqual("GetFixtureGuid uuid.d ", resultUUID.d, fixtureUUID1.d);
				// 			checkifEqual("GetGdtfName", 	 sceneObj->GetGdtfName(), "Martin@Mac Aura XB1");
				// 			checkifEqual("GetGdtfMode", 	 sceneObj->GetGdtfMode(), "Mode 1 v1.1");
				// 			ISceneObjPtr focusObj;
				// 			checkifEqual("GetFocusPoint", 	 sceneObj->GetFocusPoint(&sceneObj), );
				// 			IPositionPtr position = nullptr;
				// 			checkifEqual("GetPosition", 	 sceneObj->GetPosition(&position),);
				// 			// Sint32 unitNumb;
				// 			// checkifEqual("GetUnitNumber", 	 sceneObj->GetUnitNumber(unitNumb, );
				// 			// CieColor color;
				// 			// checkifEqual("GetColor", 		 sceneObj->GetColor(color), );
				// 			// Sint8 fixtureTypeId;
				// 			// checkifEqual("GetFixtureTypeId",  sceneObj->GetFixtureTypeId(fixtureTypeId), );
				// 			// size_t customId;
				// 			// checkifEqual("GetCustomId", 	 	 sceneObj->GetCustomId(customId), );
				// 			size_t addressCount = 0;
				// 			__checkVCOM(sceneObj->GetAdressCount(addressCount));
				// 			for (size_t i = 0; i < addressCount; i++)
				// 			{
				// 				if (__checkVCOM(sceneObj->GetAdressAt(i, SDmxAdress& adress)))
				// 				{
				// 					// TODO
				// 				}
				// 			}
				// 		}
						
				// 		if (i==0 && j==2)
				// 		{
				// 			// Get Fixture2
				// 			checkifEqual("Fixture1 name ", fixture->GetName(), "My Fixture2 Name");
				// 			__checkVCOM(fixture->GetFixtureGUID(resultUUID));
				// 			this->checkifEqual("GetFixtureGuid uuid.a ", resultUUID.a, fixtureUUID2.a);
				// 			this->checkifEqual("GetFixtureGuid uuid.b ", resultUUID.b, fixtureUUID2.b);
				// 			this->checkifEqual("GetFixtureGuid uuid.c ", resultUUID.c, fixtureUUID2.c);
				// 			this->checkifEqual("GetFixtureGuid uuid.d ", resultUUID.d, fixtureUUID2.d);
				// 			checkifEqual("GetGdtfName", 	 sceneObj->GetGdtfName(), "Martin@Mac Aura XB2");
				// 			checkifEqual("GetGdtfMode", 	 sceneObj->GetGdtfMode(), "My fancy other GDTF DMX Mode");
				// 			ISceneObjPtr focusObj;
				// 			checkifEqual("GetFocusPoint", 	 sceneObj->GetFocusPoint(&sceneObj), );
				// 			IPositionPtr position = nullptr;
				// 			checkifEqual("GetPosition", 	 sceneObj->GetPosition(&position),);
				// 			// Sint32 unitNumb;
				// 			// checkifEqual("GetUnitNumber", 	 sceneObj->GetUnitNumber(unitNumb, );
				// 			// CieColor color;
				// 			// checkifEqual("GetColor", 		 sceneObj->GetColor(color), );
				// 			// Sint8 fixtureTypeId;
				// 			// checkifEqual("GetFixtureTypeId",  sceneObj->GetFixtureTypeId(fixtureTypeId), );
				// 			// size_t customId;
				// 			// checkifEqual("GetCustomId", 	 	 sceneObj->GetCustomId(customId), );
				// 			size_t addressCount = 0;
				// 			__checkVCOM(sceneObj->GetAdressCount(addressCount));
				// 			for (size_t i = 0; i < addressCount; i++)
				// 			{
				// 				if (__checkVCOM(sceneObj->GetAdressAt(i, SDmxAdress& adress)))
				// 				{
				// 					// TODO
				// 				}
				// 			}
				// 		}
						
				// 		if (i==1 && j==0)
				// 		{
				// 			// Get Fixture3
				// 			checkifEqual("Fixture1 name ", fixture->GetName(), "My Fixture3 Name");
				// 			__checkVCOM(fixture->GetFixtureGUID(resultUUID));
				// 			this->checkifEqual("GetFixtureGuid uuid.a ", resultUUID.a, fixtureUUID3.a);
				// 			this->checkifEqual("GetFixtureGuid uuid.b ", resultUUID.b, fixtureUUID3.b);
				// 			this->checkifEqual("GetFixtureGuid uuid.c ", resultUUID.c, fixtureUUID3.c);
				// 			this->checkifEqual("GetFixtureGuid uuid.d ", resultUUID.d, fixtureUUID3.d);
				// 			checkifEqual("GetGdtfName", 	 sceneObj->GetGdtfName(), "Martin@Mac Aura XB3");
				// 			checkifEqual("GetGdtfMode", 	 sceneObj->GetGdtfMode(), "My fancy other GDTF DMX Mode2");
				// 			ISceneObjPtr focusObj;
				// 			checkifEqual("GetFocusPoint", 	 sceneObj->GetFocusPoint(&sceneObj), );
				// 			IPositionPtr position = nullptr;
				// 			checkifEqual("GetPosition", 	 sceneObj->GetPosition(&position),);
				// 			// Sint32 unitNumb;
				// 			// checkifEqual("GetUnitNumber", 	 sceneObj->GetUnitNumber(unitNumb, );
				// 			// CieColor color;
				// 			// checkifEqual("GetColor", 		 sceneObj->GetColor(color), );
				// 			// Sint8 fixtureTypeId;
				// 			// checkifEqual("GetFixtureTypeId",  sceneObj->GetFixtureTypeId(fixtureTypeId), );
				// 			// size_t customId;
				// 			// checkifEqual("GetCustomId", 	 	 sceneObj->GetCustomId(customId), );
				// 			size_t addressCount = 0;
				// 			__checkVCOM(sceneObj->GetAdressCount(addressCount));
				// 			for (size_t i = 0; i < addressCount; i++)
				// 			{
				// 				if (__checkVCOM(sceneObj->GetAdressAt(i, SDmxAdress& adress)))
				// 				{
				// 					// TODO
				// 				}
				// 			}
				// 		}
				// 	} // End Read Gdtf File
				//}
							
				//------------------------------------------------------------------------
				// Step to next Obj
				j++;
				ISceneObjPtr next = nullptr;
				__checkVCOM(mvrRead->GetNextObject(sceneObj, &next));
				sceneObj = next;
			}
			
			i++;
			ISceneObjPtr nextLayer = nullptr;
			__checkVCOM(mvrRead->GetNextObject(readLayer, &nextLayer));
			readLayer = nextLayer;
		}

       // TODO
		if (__checkVCOM(mvrRead->GetSymDefCount(count)))
		{
			checkifEqual("CountSymDef ", count, size_t(1));

			// TODO
			__checkVCOM(mvrRead->GetPositionObjectCount(count));
			checkifEqual("CountPosition ", count, size_t(1));

		}
		//------------------------------------------------------------------------------------------------
		// Traverse SymbolDefs
		//	TODO Symdef Position Class UUID?

		size_t  countSymbols = 0;
		__checkVCOM(mvrRead->GetSymDefCount(countSymbols));
		
		for (size_t i = 0; i <countSymbols; i++)
		{
			ISymDefPtr symDef = nullptr;
			__checkVCOM(mvrRead->GetSymDefAt(i, & symDef));
			
			checkifEqual("GetSymDef name", symDef->GetName(), "Symbol Definition for the FocusPoint");

			size_t geoCount = 0;
			__checkVCOM(symDef->GetGeometryCount(geoCount));
			
			for (size_t j = 0; j < geoCount; j++)
			{
				IGeometryReferencePtr geoRef = nullptr;
				__checkVCOM(symDef->GetGeometryAt(j, & geoRef));

				
				// First way to get a file is to just get the path to the file
				// You can use the own importer to read this file
				checkifEqual("Get GeometryFileName", geoRef->GetFileForGeometry(), "empty.3ds");
				//_P(fileForGeom);
			}

		}
    }
}
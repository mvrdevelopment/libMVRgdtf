//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include "MvrUnittest.h"
#include <iostream>
#include "Utility.h"


#include "Include/VectorworksMVR.h"
using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;

#define __checkVCOM(x) checkVCOM(x, #x)
#define __checkVCOM_Failed(x) this->checkVCOM_NotSet(x, #x)

MvrUnittest::MvrUnittest(const std::string& currentDir)
{
    fPath = currentDir;
#ifdef _WINDOWS
    fPath += std::string("\\testMvr.mvr");
#else
    fPath += std::string("/testMvr.mvr");
#endif

    gdtfPath = currentDir;
    std::cout << "GDTF Search Path " << gdtfPath << std::endl;
    std::cout << "Export File to "   << fPath    << std::endl; 
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
        // Add Buffer File
		std::string path 		= UnitTestUtil::GetTestResourceFolder() + kSeparator + "allWorking.gdtf";

		IGdtfFixturePtr fixture (IID_IGdtfFixture);
		if(__checkVCOM(fixture->ReadFromFile(path.c_str())))
		{
			size_t bufferLength = 0;
			fixture->GetBufferLength(bufferLength);

			char* buffer = new char[bufferLength + 1];
			__checkVCOM(fixture->ToBuffer(buffer));
			__checkVCOM(mvrWrite->AddBufferToMvrFile("gdtfTestFile.gdtf", buffer, bufferLength));
			delete [] buffer;
		}
		
        //------------------------------------------------------------------------------------------------
        // Add Custom data
        ISceneDataProviderPtr obj;
        if(__checkVCOM(mvrWrite->CreateDataProviderObject("Test Data", "1.1.2", &obj)))
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
			STransformMatrix mx;
			mx.ox = 1;
			mx.oy = 2;
			mx.oz = 3;
			mx.ux = 4;
			mx.uy = 5;
			mx.uz = 6;
			mx.vx = 7;
			mx.vy = 8;
			mx.vz = 9;
			mx.wx = 10;
			mx.wy = 11;
			mx.wz = 12;
            __checkVCOM(symDef1->AddGeometry(mx, "My3DSFile.3ds"));
        }

		ISymDefPtr symDef2 = nullptr;
        if(__checkVCOM(mvrWrite->CreateSymDefObject(MvrUUID(0, 0, 0, 0), "Symbol Definition for the UUID Creation Check", & symDef2)))
        {
			STransformMatrix mx;
            MvrUUID symUID(121062618, 11752014, 669377348, 947530087);
			symDef2->AddSymbol( symUID, mx, symDef1);
        }
        
        IClassPtr clas1 = nullptr;
        __checkVCOM(mvrWrite->CreateClassObject(MvrUUID(122074618, 11852014, 669377348, 947530087), "My first Class", & clas1));

        IClassPtr clas2 = nullptr;
        __checkVCOM(mvrWrite->CreateClassObject(MvrUUID(122774618, 11892014, 669397348, 947530057), "My second Class", & clas2));


		MvrUUID mappingDefinition1UUID(1808353427, 683171502, 518343034, 0000000002);
		MvrUUID mappingDefinition2UUID(1808353427, 683171502, 518343034, 0000000003);

		IMappingDefinitionPtr mapdef1 = nullptr;
        if(__checkVCOM(mvrWrite->CreateMappingDefinitionObject(mappingDefinition1UUID, "My MappingDefinition1", &mapdef1)))
		{
			__checkVCOM(mapdef1->SetSizeX(1920));
			__checkVCOM(mapdef1->SetSizeY(1080));
			__checkVCOM(mapdef1->SetSource("mapDef1SourceValue", "mapDef1SourceLinkedGeo", ESourceType::File));
			__checkVCOM(mapdef1->SetScaleHandling(EScaleHandlingType::KeepSizeCenter));
		}

		IMappingDefinitionPtr mapdef2 = nullptr;
        if(__checkVCOM(mvrWrite->CreateMappingDefinitionObject(mappingDefinition2UUID, "My MappingDefinition2", &mapdef2)))
		{
			__checkVCOM(mapdef2->SetSizeX(1280));
			__checkVCOM(mapdef2->SetSizeY(720));
			__checkVCOM(mapdef2->SetSource("mapDef2SourceValue", "mapDef2SourceLinkedGeo", ESourceType::CaptureDevice));
		}

        //------------------------------------------------------------------------------------------------
        // Now write content
        ISceneObjPtr layer1 = nullptr;
		__checkVCOM(mvrWrite->CreateLayerObject(MvrUUID(465143117, 742747285, 1361655924, 1172316535), "My Layer 1", &layer1));

		// Create Focus Point
		ISceneObjPtr focusPoint = nullptr;
		if (__checkVCOM(mvrWrite->CreateFocusPoint(MvrUUID(1998334672, 457193269, 1786021763, 1463564339), STransformMatrix(), "My FocusPoint", layer1, &focusPoint)))
		{
            MvrUUID symUID2(121062618, 11752014, 669377348, 837520086);
			__checkVCOM(focusPoint->AddSymbol( symUID2, STransformMatrix(), symDef1)); 
			__checkVCOM(focusPoint->SetClass(clas1));
		}
			
		// And place some fixtures on it
		ISceneObjPtr fixture1 = nullptr;
		if (__checkVCOM(mvrWrite->CreateFixture(MvrUUID(1808353427, 683171502, 518343034, 1766902383), STransformMatrix(), "My Fixture1 Name", layer1, &fixture1)))
		{
			__checkVCOM(fixture1->SetGdtfName("testGdtf.gdtf"));
			__checkVCOM(fixture1->SetGdtfMode("My DmxModeName"));
			__checkVCOM(fixture1->AddAdress(1542, 0));
			__checkVCOM(fixture1->AddAdress(25, 1));
			__checkVCOM(fixture1->SetFocusPoint(focusPoint));
			__checkVCOM(fixture1->SetPosition(position));
			__checkVCOM(fixture1->SetClass(clas2));
			__checkVCOM(fixture1->SetCastShadow(true));
			//Mappings
			__checkVCOM(fixture1->AddMapping(mappingDefinition1UUID));
			IMappingPtr mapping1;
			if(__checkVCOM(fixture1->GetMappingAt(0, &mapping1)))
			{
				__checkVCOM(mapping1->SetUx(1));
				__checkVCOM(mapping1->SetUy(2));
				__checkVCOM(mapping1->SetOx(3));
				__checkVCOM(mapping1->SetOy(4));
				__checkVCOM(mapping1->SetRz(5.6));
			}

			__checkVCOM(fixture1->CreateConnection("ConnectionFrom", "ConnectionTo", MvrUUID(1136161871, 1699151080, 751939975, 1748783014) /* fixture2*/, nullptr)); 
		
			fixture1->SetFunction("TestFunction");
			
			//CustomCommands
			ICustomCommandPtr customCommand1, customCommand2;
			__checkVCOM(fixture1->CreateCustomCommand("My ChannelFunction 1", false, -1.2, &customCommand1));
			__checkVCOM(fixture1->CreateCustomCommand("My ChannelFunction 1", false, -1.2, &customCommand2));

			__checkVCOM(customCommand2->SetChannelFunction("My ChannelFunction 2"));
			__checkVCOM(customCommand2->SetIsPercentage(true));
			__checkVCOM(customCommand2->SetValue(-3.4));
			

			//Alignments
			IAlignmentPtr alignment1, alignment2;
			SVector3 upVector1 = {0, 0, 1};
			SVector3 direction1 = {0.1, 2.3, -4.5};
			__checkVCOM(fixture1->CreateAlignment("My beamGeometry 1", upVector1, direction1, &alignment1));
			__checkVCOM(fixture1->CreateAlignment("My beamGeometry 1", upVector1, direction1, &alignment2));

			__checkVCOM(alignment2->SetBeamGeometry("My beamGeometry 2"));
			__checkVCOM(alignment2->SetUpVector(0, -2, 0));
			__checkVCOM(alignment2->SetDirection(-6.7, 8.9, 10.11));

			//Overwrites
			IOverwritePtr overwrite1, overwrite2;
			__checkVCOM(fixture1->CreateOverwrite("My universal 1", "My target 1", &overwrite1));
			__checkVCOM(fixture1->CreateOverwrite("My universal 1", "My target 1", &overwrite2));

			__checkVCOM(overwrite2->SetUniversal("My universal 2"));
			__checkVCOM(overwrite2->SetTarget("My target 2"));
		}

		// And another fixture
		ISceneObjPtr fixture2 = nullptr;
		if (__checkVCOM(mvrWrite->CreateFixture(MvrUUID(1136161871, 1699151080, 751939975, 1748783014), STransformMatrix(), "My Fixture2 Name", layer1, &fixture2)))
		{
			__checkVCOM(fixture2->SetGdtfName("testGdtf.gdtf"));
			__checkVCOM(fixture2->SetGdtfMode("My DmxModeName"));
			__checkVCOM(fixture2->AddAdress(352, 0));
			__checkVCOM(fixture2->AddAdress(5684, 1));
			__checkVCOM(fixture2->SetFocusPoint(focusPoint));
			__checkVCOM(fixture2->SetGoboRotation(32.87));
			__checkVCOM(fixture2->SetGobo("MWheel_Img1"));
			__checkVCOM(fixture2->SetCastShadow(false));
			//Mappings
			__checkVCOM(fixture2->AddMapping(mappingDefinition1UUID));
			IMappingPtr mapping1;
			if(__checkVCOM(fixture2->GetMappingAt(0, &mapping1)))
			{
				__checkVCOM(mapping1->SetUx(7));
				__checkVCOM(mapping1->SetUy(8));
				__checkVCOM(mapping1->SetOx(9));
				__checkVCOM(mapping1->SetOy(10));
				__checkVCOM(mapping1->SetRz(11.12));
			}
			__checkVCOM(fixture2->AddMapping(mappingDefinition2UUID));
			IMappingPtr mapping2;
			if(__checkVCOM(fixture2->GetMappingAt(1, &mapping2)))
			{
				__checkVCOM(mapping2->SetUx(13));
				__checkVCOM(mapping2->SetUy(14));
				__checkVCOM(mapping2->SetOx(15));
				__checkVCOM(mapping2->SetOy(16));
				__checkVCOM(mapping2->SetRz(17.18));
			}
		}

		ISceneObjPtr fixture4 = nullptr;
		__checkVCOM(mvrWrite->CreateFixture(MvrUUID(1136161871, 1699151080, 751939975, 1748783014), STransformMatrix(), "My Fixture4 Name", layer1, &fixture4));

		// Group
		MvrUUID groupUUID(1808353427, 683171502, 518343034, 0000000005);
		ISceneObjPtr group = nullptr;
        __checkVCOM(mvrWrite->CreateGroupObject(groupUUID, STransformMatrix(), "My Group Name", layer1, &group));              
        
        ISceneObjPtr truss = nullptr;
        mvrWrite->CreateTruss(MvrUUID(1126151872, 1699151080, 751939975, 1748783014), STransformMatrix(), "Truss in Group", group, &truss);

		MvrUUID empty_groupUUID(1808353427, 683171502, 518343012, 0000000002);
		ISceneObjPtr empty_group = nullptr;
        __checkVCOM(mvrWrite->CreateGroupObject(empty_groupUUID, STransformMatrix(), "EmptyGroup", layer1, &empty_group));

        ISceneObjPtr firstChild = nullptr;
        __checkVCOM(mvrWrite->GetFirstChild( group, &firstChild));        

		// Create second Layer
		ISceneObjPtr layer2 = nullptr;
		__checkVCOM(mvrWrite->CreateLayerObject(MvrUUID(465143117, 742747285, 1361655924, 1172316525), "My Layer 2", &layer2));

		ISceneObjPtr fixture3 = nullptr;
		if (__checkVCOM(mvrWrite->CreateFixture(MvrUUID(1136161871, 1699151080, 751939975, 1748773014), STransformMatrix(), "My Fixture3 Name", layer2, &fixture3)))
		{
			__checkVCOM(fixture3->SetGdtfName("testGdtf.gdtf"));
			__checkVCOM(fixture3->SetGdtfMode("My DmxModeName"));
			__checkVCOM(fixture3->AddAdress(352, 0));
			__checkVCOM(fixture3->AddAdress(5684, 1));
			__checkVCOM(fixture3->SetFocusPoint(focusPoint));
			__checkVCOM(fixture3->SetGobo("MWheel_Img1"));


			mvrWrite->AddFileToMvrFile(GetTestWheel_PNG(false).c_str());
		}

		// Truss
		ISceneObjPtr trussObject = nullptr;
		__checkVCOM(mvrWrite->CreateTruss(MvrUUID(1136161271, 1699351080, 75193997, 1748573014), STransformMatrix(), "MyTrussName", layer2, &trussObject));

		// Create Video Screen
		ISceneObjPtr videoScreen;
		if (__checkVCOM(mvrWrite->CreateVideoScreen(MvrUUID(1808353427, 683171502, 518343034, 0000000001), STransformMatrix(), "My VideoScreen Name", layer2, &videoScreen)))
		{
			__checkVCOM(videoScreen->SetVideoScreenSource("myValue1", "myLinkedGeometry1", ESourceType::File));
		}

		// Create projector
		ISceneObjPtr projector;
		if (__checkVCOM(mvrWrite->CreateProjector(MvrUUID(1808353427, 683171502, 518343034, 0000000004), STransformMatrix(), "My projector Name", layer2, &projector)))
		{
			__checkVCOM(projector->SetProjectorSource("myValueP", "myLinkedGeometryP", ESourceType::File));
			__checkVCOM(projector->SetScaleHandling(EScaleHandlingType::ScaleIgnoreRatio));

		}

		// Support
		ISceneObjPtr supportObject = nullptr;
		__checkVCOM(mvrWrite->CreateSupport(MvrUUID(1808353427, 683171502, 518343034, 0000000007), STransformMatrix(), "MySupportName", layer2, &supportObject));

        Write_NestedObjects( mvrWrite, layer1);

		// Check Next Object behavoir
		ISceneObjPtr firstLayerWritten;
		if(__checkVCOM(mvrWrite->GetFirstLayer( & firstLayerWritten)))
		{
			checkifEqual("Layer One Name", firstLayerWritten->GetName(), "My Layer 1");
			
			// Get first Object
			ISceneObjPtr firstChild;
			if(__checkVCOM(mvrWrite->GetFirstChild(firstLayerWritten, & firstChild)))
			{
				checkifEqual("Check First Child", firstChild->GetName(), "My FocusPoint");

				ISceneObjPtr secondChild;
				if(__checkVCOM(mvrWrite->GetNextObject(firstChild, & secondChild)))
				{
					checkifEqual("Check Second Child", secondChild->GetName(), "My Fixture1 Name");
				}		
			}

			ISceneObjPtr secondLayerWritten;
			if(__checkVCOM(mvrWrite->GetNextObject(firstLayerWritten, & secondLayerWritten)))
			{
				checkifEqual("Layer Two Name", secondLayerWritten->GetName(), "My Layer 2");
			}
		}


    }
	__checkVCOM(mvrWrite->Close());
}

void MvrUnittest::ReadFile()
{

	CieColor defaultColor;
	defaultColor.fx  = 0.312712;
	defaultColor.fy  = 0.329008;
	defaultColor.f_Y = 100.0;

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
		MvrUUID fixtureUUID4	(1136161871, 1699151080, 751939975, 1748783014);//This uuid is the same as fixtureUUID2 to test duplicated uuids;
		MvrUUID videoScreenUUID	(1808353427, 683171502, 518343034, 0000000001);
		MvrUUID mappingDefinition1UUID(1808353427, 683171502, 518343034, 0000000002);
		MvrUUID mappingDefinition2UUID(1808353427, 683171502, 518343034, 0000000003);
		MvrUUID projectorUUID	(1808353427, 683171502, 518343034, 0000000004);
		MvrUUID groupUUID		(1808353427, 683171502, 518343034, 0000000005);
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

			checkifEqual("Provider Name", "Test Data", obj->GetProviderName());
			checkifEqual("Provider Version", "1.1.2", obj->GetVersion());
        }

		// Check Object
		size_t count_Objects = 0;
		__checkVCOM(mvrRead->GetSceneObjectCount(count_Objects));

        this->checkifEqual("Check Global Object Count", count_Objects, size_t(18));

		//------------------------------------------------------------------------------------------------
		// Check File Getters
		size_t countFiles = size_t(-1);
		__checkVCOM(mvrRead->GetAttachedFileCount(countFiles));
		checkifEqual("Check File Count in MVR",countFiles , size_t(3) );


		std::string path = gdtfPath;
#ifdef _WINDOWS
		path += "\\MVR_Export\\";
#elif GS_MAC
		path += "/Library/Application Support/mvrexchange/MVR_Export/";
#else
		path += "/MVR_Export/";
#endif
		std::string file0 = path + std::string("MWheel_Img1.png");
		std::string file1 = path + std::string("gdtfTestFile.gdtf");
		std::string file2 = path + std::string("testGdtf.gdtf");

		checkifEqual("File 0 Name", mvrRead->GetAttachedFileCountAt(0), file0.c_str());
		checkifEqual("File 1 Name", mvrRead->GetAttachedFileCountAt(1), file1.c_str());
		checkifEqual("File 2 Name", mvrRead->GetAttachedFileCountAt(2), file2.c_str());


		IGdtfFixturePtr fixtureFromBuffer (IID_IGdtfFixture);
		__checkVCOM(fixtureFromBuffer->ReadFromFile(file1.c_str()));


		//------------------------------------------------------------------------------------------------
		// Read Layers
		ISceneObjPtr readLayer = nullptr;
		__checkVCOM(mvrRead->GetFirstLayer(&readLayer));

		int layer_index(0);
		while (readLayer)
		{
			ISceneObjPtr sceneObj = nullptr;
			__checkVCOM(mvrRead->GetFirstChild(readLayer, &sceneObj));
			
			//Get Data Layer 1
			if (layer_index==0)
			{
				checkifEqual("Layer name", readLayer->GetName(), "My Layer 1");
				__checkVCOM(readLayer->GetGuid(resultUUID));
				this->checkifEqual("GetLayerGuid layerUUID1 ", resultUUID, layerUUID1);
			}

            if (layer_index==0)
            {
                Read_NestedObjects(mvrRead, readLayer);
                Read_TestGroup(mvrRead, readLayer);
            }
			
			//Get Data Layer 2
			if (layer_index==1)
			{
				checkifEqual("Layer name", readLayer->GetName(), "My Layer 2");
				__checkVCOM(readLayer->GetGuid(resultUUID));
				this->checkifEqual("GetLayerGuid uuid ", resultUUID, layerUUID2);
			}
			
			int obj_index(0);
			while (sceneObj)
			{
				ESceneObjType type;
				__checkVCOM(sceneObj->GetType(type));

				// ------------------------------------------------------------------------------
				// Get Focus Point1
				if(layer_index==0 && obj_index==0)
				{	
					
					checkifEqual("ESceneObjType Type ", (Sint32)type ,(Sint32)ESceneObjType::FocusPoint);
					checkifEqual("GetFocusPoint name", sceneObj->GetName(), "My FocusPoint");
					__checkVCOM(sceneObj->GetGuid(resultUUID));
					this->checkifEqual("GetFocusPointGuid focusPointUUID ", resultUUID, focusPointUUID);

					// Check Geometry
					size_t geometryCount = 0;
					__checkVCOM(sceneObj->GetGeometryCount(geometryCount));
					checkifEqual("Focus Point Geometry Count ", geometryCount, size_t(1));

					IGeometryReferencePtr geoRef;
					__checkVCOM(sceneObj->GetGeometryAt(0, &geoRef));

					bool isSymbol = false;
					__checkVCOM(geoRef->GetIsSymbol(isSymbol));
					checkifTrue("Is Symbol", isSymbol);

					ISymDefPtr linkedSymDef;
					__checkVCOM(geoRef->GetSymDef(&linkedSymDef));
					if(linkedSymDef)
					{
						checkifEqual("SymbolDef for Focus Point", linkedSymDef->GetName(), "Symbol Definition for the FocusPoint");					
					}
				}
				

				// ------------------------------------------------------------------------------
				// Get Fixture1
				if (layer_index==0 && obj_index==1)
				{	
					checkifEqual("ESceneObjType Type ", (Sint32)type ,(Sint32)ESceneObjType::Fixture);
					checkifEqual("Fixture1 name ",		sceneObj->GetName(), 	 "My Fixture1 Name");
					__checkVCOM(sceneObj->GetGuid(resultUUID));
					this->checkifEqual("GetFixtureGuid fixtureUUID1 ", resultUUID, fixtureUUID1);
					checkifEqual("GetGdtfName", 	 	sceneObj->GetGdtfName(), "testGdtf.gdtf");
					checkifEqual("GetGdtfMode", 	 	sceneObj->GetGdtfMode(), "My DmxModeName");
					checkifEqual("GetFunction", 	 	sceneObj->GetFunction(), "TestFunction");

					ISceneObjPtr focus;
					if(__checkVCOM(sceneObj->GetFocusPoint( & focus)))
					{
						checkifEqual("GetFocusPoint", focus->GetName(), "My FocusPoint");
					}

					IPositionPtr position;
					if(__checkVCOM(sceneObj->GetPosition(&position)))
					{
						checkifEqual("GetPosition", position->GetName(), "My Position");
					}

					Sint32 unitNumb;
					sceneObj->GetUnitNumber(unitNumb);
					checkifEqual("GetUnitNumber", unitNumb, 0);

					CieColor resultColor;
					sceneObj->GetColor(resultColor);
					checkifEqual("GetColor", resultColor, defaultColor);

					Sint8 fixtureTypeId;
					sceneObj->GetFixtureTypeId(fixtureTypeId);
					checkifEqual("GetFixtureTypeId", fixtureTypeId, 0);

					size_t customId;
					sceneObj->GetCustomId(customId);
					checkifEqual("GetCustomId", customId, (size_t)0);

					bool castShadow;
					sceneObj->GetCastShadow(castShadow);
					checkifEqual("GetCastShadow", castShadow, true);

					size_t addressCount = 0;
					__checkVCOM(sceneObj->GetAdressCount(addressCount));
					for (size_t z = 0; z < addressCount; z++)
					{
						SDmxAdress adress;
						if (__checkVCOM( sceneObj->GetAdressAt(z, adress) ))
						{
							if(z==0)
							{
								checkifEqual("Check fAbsuluteAdress ",	adress.fAbsuluteAdress, (size_t)1542);
								checkifEqual("Check fBreakId ", 	 	adress.fBreakId, 		(size_t)0);
							}
							else if(z==1)
							{
								checkifEqual("Check fAbsuluteAdress ",	adress.fAbsuluteAdress, (size_t)25);
								checkifEqual("Check fBreakId ", 	 	adress.fBreakId, 		(size_t)1);
							}
						}
					}

					//Mappings
					size_t mappingCount;
					__checkVCOM(sceneObj->GetMappingCount(mappingCount));
					checkifEqual("GetMappingCount", mappingCount, (size_t)1);

					IMappingPtr mapping1;
					if(__checkVCOM(sceneObj->GetMappingAt(0, &mapping1)))
					{
						Uint32 ux, uy, ox, oy;
						double rz;
						__checkVCOM(mapping1->GetUx(ux));
						__checkVCOM(mapping1->GetUy(uy));
						__checkVCOM(mapping1->GetOx(ox));
						__checkVCOM(mapping1->GetOy(oy));
						__checkVCOM(mapping1->GetRz(rz));

						checkifEqual("Check GetUx ", (size_t)ux, 	(size_t)1);
						checkifEqual("Check GetUy ", (size_t)uy, 	(size_t)2);
						checkifEqual("Check GetOx ", (size_t)ox, 	(size_t)3);
						checkifEqual("Check GetOy ", (size_t)oy, 	(size_t)4);
						checkifEqual("Check GetRz ", 		 rz, 			5.6);
					}

					//CustomCommands
					size_t customCommandCount;
					__checkVCOM(sceneObj->GetCustomCommandCount(customCommandCount));
					checkifEqual("GetCustomCommandCount", customCommandCount, (size_t)2);

					ICustomCommandPtr customCommand1, customCommand2;
					if(__checkVCOM(sceneObj->GetCustomCommandAt(0, &customCommand1)))
					{
						bool isPercentage = false;
						double value = 0.0;
						__checkVCOM(customCommand1->IsPercentage(isPercentage));
						__checkVCOM(customCommand1->GetValue(value));

						checkifEqual("Check GetChannelFunction ", customCommand1->GetChannelFunction(), "My ChannelFunction 1");
						checkifEqual("Check IsPercentage ", isPercentage, false);
						checkifEqual("Check GetValue ", value, -1.2);
					}
					if(__checkVCOM(sceneObj->GetCustomCommandAt(1, &customCommand2)))
					{
						bool isPercentage = false;
						double value = 0.0;
						__checkVCOM(customCommand2->IsPercentage(isPercentage));
						__checkVCOM(customCommand2->GetValue(value));

						checkifEqual("Check GetChannelFunction ", customCommand2->GetChannelFunction(), "My ChannelFunction 2");
						checkifEqual("Check IsPercentage ", isPercentage, true);
						checkifEqual("Check GetValue ", value, -3.4);
					}

					//Alignments
					size_t alignmentCount;
					__checkVCOM(sceneObj->GetAlignmentCount(alignmentCount));
					checkifEqual("GetAlignmentCount", alignmentCount, (size_t)2);

					IAlignmentPtr alignment1, alignment2;
					if(__checkVCOM(sceneObj->GetAlignmentAt(0, &alignment1)))
					{
						SVector3 upVector1, direction1;
						__checkVCOM(alignment1->GetUpVector(upVector1));
						__checkVCOM(alignment1->GetDirection(direction1));

						checkifEqual("Check GetBeamGeometry ", alignment1->GetBeamGeometry(), "My beamGeometry 1");
						checkifEqual("Check GetUpVector X", upVector1.x, 0.0);
						checkifEqual("Check GetUpVector Y", upVector1.y, 0.0);
						checkifEqual("Check GetUpVector Z", upVector1.z, 1.0);
						checkifEqual("Check GetDirection X", direction1.x, 0.1);
						checkifEqual("Check GetDirection Y", direction1.y, 2.3);
						checkifEqual("Check GetDirection Z", direction1.z, -4.5);
					}
					if(__checkVCOM(sceneObj->GetAlignmentAt(1, &alignment2)))
					{
						SVector3 upVector2, direction2;
						__checkVCOM(alignment2->GetUpVector(upVector2));
						__checkVCOM(alignment2->GetDirection(direction2));

						checkifEqual("Check GetBeamGeometry ", alignment2->GetBeamGeometry(), "My beamGeometry 2");
						checkifEqual("Check GetUpVector X", upVector2.x, 0.0);
						checkifEqual("Check GetUpVector Y", upVector2.y, -2.0);
						checkifEqual("Check GetUpVector Z", upVector2.z, 0.0);
						checkifEqual("Check GetDirection X", direction2.x, -6.7);
						checkifEqual("Check GetDirection Y", direction2.y, 8.9);
						checkifEqual("Check GetDirection Z", direction2.z, 10.11);
					}

					//Overwrites
					size_t overwriteCount;
					__checkVCOM(sceneObj->GetOverwriteCount(overwriteCount));
					checkifEqual("GetOverwriteCount", overwriteCount, (size_t)2);

					IOverwritePtr overwrite1, overwrite2;
					if(__checkVCOM(sceneObj->GetOverwriteAt(0, &overwrite1)))
					{
						checkifEqual("Check GetUniversal ", overwrite1->GetUniversal(), "My universal 1");
						checkifEqual("Check GetTarget ", overwrite1->GetTarget(), "My target 1");
					}
					if(__checkVCOM(sceneObj->GetOverwriteAt(1, &overwrite2)))
					{
						checkifEqual("Check GetUniversal ", overwrite2->GetUniversal(), "My universal 2");
						checkifEqual("Check GetTarget ", overwrite2->GetTarget(), "My target 2");
					}

					//Linked Fixture
					IGdtfFixturePtr gdtfLinkedFixture;
					__checkVCOM(sceneObj->GetGdtfFixture( & gdtfLinkedFixture));

					size_t bufferLength = 0;
					__checkVCOM(gdtfLinkedFixture->GetBufferLength(bufferLength));

					char* buffer = new char[bufferLength + 1];
					__checkVCOM(gdtfLinkedFixture->ToBuffer(buffer));
					delete[] buffer;

					//Connections
					
					size_t connCount;
					sceneObj->GetConnectionCount(connCount);
					checkifEqual("GetConnectionCount", connCount, (size_t)1);
					if(connCount == 1){
						IConnectionPtr conn;
						sceneObj->GetConnectionAt(0, &conn);
						checkifEqual("Connection->GetOwn()", conn->GetOwn(), "ConnectionFrom");
						checkifEqual("Connection->GetOther()", conn->GetOther(), "ConnectionTo");
						MvrUUID ToObj(0, 0, 0, 0);
						conn->GetToObject(ToObj);
						checkifEqual("Connection->GetToObject()", ToObj, MvrUUID(1136161871, 1699151080, 751939975, 1748783014));
					}

				}
				
				// ------------------------------------------------------------------------------
				// Get Fixture2
				if (layer_index==0 && obj_index==2)
				{
					checkifEqual("ESceneObjType Type ", (Sint32)type ,(Sint32)ESceneObjType::Fixture);
					checkifEqual("Fixture2 name ",		sceneObj->GetName(), 	 "My Fixture2 Name");
					__checkVCOM(sceneObj->GetGuid(resultUUID));
					this->checkifEqual("GetFixtureGuid fixtureUUID2 ", resultUUID, fixtureUUID2);
					checkifEqual("GetGdtfName", 	 	sceneObj->GetGdtfName(), "testGdtf.gdtf");
					checkifEqual("GetGdtfMode", 	 	sceneObj->GetGdtfMode(), "My DmxModeName");
					
					ISceneObjPtr focus;
					if(__checkVCOM(sceneObj->GetFocusPoint( & focus)))
					{
						checkifEqual("GetFocusPoint", focus->GetName(), "My FocusPoint");
					}

					double goboRotation = -1.0;
					__checkVCOM(sceneObj->GetGoboRotation(goboRotation));
					checkifEqual("sceneObj->GetGoboRotation", goboRotation, 32.87);

					Sint32 unitNumb;
					sceneObj->GetUnitNumber(unitNumb);
					checkifEqual("GetUnitNumber", unitNumb, 0);

					CieColor resultColor;
					sceneObj->GetColor(resultColor);
					checkifEqual("GetColor", resultColor, defaultColor);

					Sint8 fixtureTypeId;
					sceneObj->GetFixtureTypeId(fixtureTypeId);
					checkifEqual("GetFixtureTypeId", fixtureTypeId, 0);

					size_t customId;
					sceneObj->GetCustomId(customId);
					checkifEqual("GetCustomId", customId, (size_t)0);

					bool castShadow = true;
					sceneObj->GetCastShadow(castShadow);
					checkifEqual("GetCastShadow", castShadow, false);
					
					size_t addressCount = 0;
					__checkVCOM(sceneObj->GetAdressCount(addressCount));
					for (size_t z = 0; z < addressCount; z++)
					{
						SDmxAdress adress;
						if (__checkVCOM( sceneObj->GetAdressAt(z, adress) ))
						{
							if(z==0)
							{
								checkifEqual("Check fAbsuluteAdress ",	adress.fAbsuluteAdress, (size_t)352);
								checkifEqual("Check fBreakId ", 	 	adress.fBreakId, 		(size_t)0);
							}
							else if(z==1)
							{
								checkifEqual("Check fAbsuluteAdress ",	adress.fAbsuluteAdress, (size_t)5684);
								checkifEqual("Check fBreakId ", 	 	adress.fBreakId, 		(size_t)1);
							}
						}
					}

					//Mappings
					size_t mappingCount;
					__checkVCOM(sceneObj->GetMappingCount(mappingCount));
					checkifEqual("GetMappingCount", mappingCount, (size_t)2);

					IMappingPtr mapping1;
					if(__checkVCOM(sceneObj->GetMappingAt(0, &mapping1)))
					{
						Uint32 ux, uy, ox, oy;
						double rz;
						__checkVCOM(mapping1->GetUx(ux));
						__checkVCOM(mapping1->GetUy(uy));
						__checkVCOM(mapping1->GetOx(ox));
						__checkVCOM(mapping1->GetOy(oy));
						__checkVCOM(mapping1->GetRz(rz));

						checkifEqual("Check GetUx ", (size_t)ux, 	(size_t)7);
						checkifEqual("Check GetUy ", (size_t)uy, 	(size_t)8);
						checkifEqual("Check GetOx ", (size_t)ox, 	(size_t)9);
						checkifEqual("Check GetOy ", (size_t)oy, 	(size_t)10);
						checkifEqual("Check GetRz ", 		 rz, 			11.12);
					}

					IMappingPtr mapping2;
					if(__checkVCOM(sceneObj->GetMappingAt(1, &mapping2)))
					{
						Uint32 ux, uy, ox, oy;
						double rz;
						__checkVCOM(mapping2->GetUx(ux));
						__checkVCOM(mapping2->GetUy(uy));
						__checkVCOM(mapping2->GetOx(ox));
						__checkVCOM(mapping2->GetOy(oy));
						__checkVCOM(mapping2->GetRz(rz));

						checkifEqual("Check GetUx ", (size_t)ux, 	(size_t)13);
						checkifEqual("Check GetUy ", (size_t)uy, 	(size_t)14);
						checkifEqual("Check GetOx ", (size_t)ox, 	(size_t)15);
						checkifEqual("Check GetOy ", (size_t)oy, 	(size_t)16);
						checkifEqual("Check GetRz ", 		 rz, 			17.18);
					}
				}
				// ------------------------------------------------------------------------------
				// Get Fixture4
				if (layer_index==0 && obj_index==3)
				{
					checkifEqual("Fixture4 name ", 		sceneObj->GetName(), 	 "My Fixture4 Name");

					bool duplicatedUuids = false;
					__checkVCOM(mvrRead->GetDuplicatedUuids(duplicatedUuids));
					checkifEqual("Duplicated Uuids", duplicatedUuids, true);
				}
				
				// ------------------------------------------------------------------------------
				// Get Fixture3
				if (layer_index==1 && obj_index==0)
				{
					checkifEqual("ESceneObjType Type ", (Sint32)type ,(Sint32)ESceneObjType::Fixture);
					checkifEqual("Fixture3 name ", 		sceneObj->GetName(), 	 "My Fixture3 Name");
					__checkVCOM(sceneObj->GetGuid(resultUUID));
					this->checkifEqual("GetFixtureGuid fixtureUUID3 ", resultUUID, fixtureUUID3);
					checkifEqual("GetGdtfName", 	 	sceneObj->GetGdtfName(), "testGdtf.gdtf");
					checkifEqual("GetGdtfMode", 	 	sceneObj->GetGdtfMode(), "My DmxModeName");
					checkifEqual("GetGobo", 	 		sceneObj->GetGobo(), "MWheel_Img1");

					std::string goboFullPath = sceneObj->GetGoboFullPath();
					checkifTrue("GetGoboFullPath is not empty", !goboFullPath.empty());

					double goboRotation = -1.0;
					__checkVCOM(sceneObj->GetGoboRotation(goboRotation));
					checkifEqual("sceneObj->GetGoboRotation", goboRotation, 0.0);
					
					IClassPtr mvrClass;
					__checkVCOM_Failed(sceneObj->GetClass(& mvrClass));
					
					ISceneObjPtr focus;
					if(__checkVCOM(sceneObj->GetFocusPoint( & focus)))
					{
						checkifEqual("GetFocusPoint", focus->GetName(), "My FocusPoint");
					}

					Sint32 unitNumb;
					sceneObj->GetUnitNumber(unitNumb);
					checkifEqual("GetUnitNumber", unitNumb, 0);

					CieColor resultColor;
					sceneObj->GetColor(resultColor);
					checkifEqual("GetColor", resultColor, defaultColor);

					Sint8 fixtureTypeId;
					sceneObj->GetFixtureTypeId(fixtureTypeId);
					checkifEqual("GetFixtureTypeId", fixtureTypeId, 0);

					size_t customId;
					sceneObj->GetCustomId(customId);
					checkifEqual("GetCustomId", customId, (size_t)0);

					bool castShadow = true;
					sceneObj->GetCastShadow(castShadow);
					checkifEqual("GetCastShadow", castShadow, false);
					
					size_t addressCount = 0;
					__checkVCOM(sceneObj->GetAdressCount(addressCount));
					for (size_t z = 0; z < addressCount; z++)
					{
						SDmxAdress adress;
						if (__checkVCOM( sceneObj->GetAdressAt(z, adress) ))
						{
							if(z==0)
							{
								checkifEqual("Check fAbsuluteAdress ",	adress.fAbsuluteAdress, (size_t)352);
								checkifEqual("Check fBreakId ", 	 	adress.fBreakId, 		(size_t)0);
							}
							else if(z==1)
							{
								checkifEqual("Check fAbsuluteAdress ",	adress.fAbsuluteAdress, (size_t)5684);
								checkifEqual("Check fBreakId ", 	 	adress.fBreakId, 		(size_t)1);
							}
						}
					}
				}

				if (layer_index==1 && obj_index==1)
				{
					checkifEqual("ESceneObjType Type ", (Sint32)type ,(Sint32)ESceneObjType::Truss);
				}

				if (layer_index==1 && obj_index==2)
				{
					checkifEqual("ESceneObjType Type ", (Sint32)type ,(Sint32)ESceneObjType::VideoScreen);

					ISourcePtr source1;
					if(__checkVCOM(sceneObj->GetVideoScreenSource(&source1)))
					{
						checkifEqual("Check Source1 value", 			source1->GetValue(), 			"myValue1");
						checkifEqual("Check Source1 linkedGeometry", 	source1->GetLinkedGeometry(), 	"myLinkedGeometry1");

						GdtfDefines::ESourceType type;
						__checkVCOM(source1->GetType(type));
						checkifEqual("Check Source1 type", (size_t)type, (size_t)ESourceType::File);
					}
				}

				if (layer_index==1 && obj_index==3)
				{
					checkifEqual("ESceneObjType Type ", (Sint32)type ,(Sint32)ESceneObjType::Projector);
					ISourcePtr source1;
					if(__checkVCOM(sceneObj->GetProjectorSource(&source1)))
					{
						checkifEqual("Check SourceP value", 			source1->GetValue(), 			"myValueP");
						checkifEqual("Check SourceP linkedGeometry", 	source1->GetLinkedGeometry(), 	"myLinkedGeometryP");

						GdtfDefines::ESourceType type;
						__checkVCOM(source1->GetType(type));
						checkifEqual("Check SourceP type", (size_t)type, (size_t)ESourceType::File);
					}

					EScaleHandlingType scaleHandlingType;
					__checkVCOM(sceneObj->GetScaleHandling(scaleHandlingType));
					checkifEqual("Check Projector ScaleHandling", (size_t)scaleHandlingType, (size_t)EScaleHandlingType::ScaleIgnoreRatio);
				}

				if (layer_index==1 && obj_index==4)
				{
					checkifEqual("ESceneObjType Type ", (Sint32)type ,(Sint32)ESceneObjType::Support);
				}
							
				//------------------------------------------------------------------------
				// Step to next Obj
				obj_index++;
				ISceneObjPtr next = nullptr;
				mvrRead->GetNextObject(sceneObj, &next);
				sceneObj = next;
			}
			
            layer_index++;

			ISceneObjPtr nextLayer = nullptr;
			mvrRead->GetNextObject(readLayer, &nextLayer);
			readLayer = nextLayer;
		}

		//------------------------------------------------------------------------------------------------
		// Traverse SymbolDefs
		// Symdef Position Class UUID?

		size_t  countSymbols = 0;
		__checkVCOM(mvrRead->GetSymDefCount(countSymbols));
		checkifEqual("Count Symbol Defs", countSymbols, size_t(2));

		// First Sym Def
		ISymDefPtr symDef = nullptr;
		__checkVCOM(mvrRead->GetSymDefAt(0, & symDef));
		
        if(symDef){
            
		checkifEqual("GetSymDef name", symDef->GetName(), "Symbol Definition for the FocusPoint");

		size_t geoCount = 0;
		__checkVCOM(symDef->GetGeometryCount(geoCount));
		
		for (size_t j = 0; j < geoCount; j++)
		{
			IGeometryReferencePtr geoRef = nullptr;
			__checkVCOM(symDef->GetGeometryAt(j, & geoRef));

			
			// First way to get a file is to just get the path to the file
			// You can use the own importer to read this file
			std::string path = gdtfPath;
#ifdef _WINDOWS
			path += "\\MVR_Export\\My3DSFile.3ds";
#elif GS_MAC
		path += "/Library/Application Support/mvrexchange/MVR_Export/My3DSFile.3ds";
#else
			path += "/MVR_Export/My3DSFile.3ds";
#endif

			
			checkifEqual("Get GeometryFileName", geoRef->GetFileForGeometry(), path);

			STransformMatrix mx;
			__checkVCOM(geoRef->GetTransfromMatrix(mx));
			
			checkifEqual("mx.ox", mx.ox, (double)1);
			checkifEqual("mx.oy", mx.oy, (double)2);
			checkifEqual("mx.oz", mx.oz, (double)3);
			checkifEqual("mx.ux", mx.ux, (double)4);
			checkifEqual("mx.uy", mx.uy, (double)5);
			checkifEqual("mx.uz", mx.uz, (double)6);
			checkifEqual("mx.vx", mx.vx, (double)7);
			checkifEqual("mx.vy", mx.vy, (double)8);
			checkifEqual("mx.vz", mx.vz, (double)9);
			checkifEqual("mx.wx", mx.wx, (double)10);
			checkifEqual("mx.wy", mx.wy, (double)11);
			checkifEqual("mx.wz", mx.wz, (double)12);
		}

		// Second Sym Def
		ISymDefPtr symDef2 = nullptr;
		__checkVCOM(mvrRead->GetSymDefAt(1, & symDef2));
		if(symDef2)
		{
			VectorworksMVR::MvrUUID uuid (0,0,0,0);
			VectorworksMVR::MvrUUID emptyuuid (0,0,0,0);
			__checkVCOM(symDef2->GetGuid(uuid));

			checkifUnEqual("UUID for Sym Def", uuid, emptyuuid );

			size_t symDef2_count = 0;
			__checkVCOM(symDef2->GetGeometryCount(symDef2_count));
			checkifEqual("Geometry Count Symbol Def 2", symDef2_count, size_t(1));

			IGeometryReferencePtr symDef2_geoRef;
			__checkVCOM(symDef2->GetGeometryAt(0, &symDef2_geoRef));

			bool isSymbol = false;
			__checkVCOM(symDef2_geoRef->GetIsSymbol(isSymbol));
			checkifTrue("symDef2_geoRef isSymbol", isSymbol);

			ISymDefPtr linkedSymDef;
			__checkVCOM(symDef2_geoRef->GetSymDef(&linkedSymDef));

			checkifEqual("Sym Def Link", linkedSymDef->GetName(), symDef->GetName());

		}
        }


		size_t countClasses = 0;
		__checkVCOM(mvrRead->GetClassCount(countClasses));
		IClassPtr clas = nullptr;
		for (size_t c = 0; c < countClasses; c++)
		{
			__checkVCOM(mvrRead->GetClassAt(c, & clas));
			__checkVCOM(clas->GetGuid(resultUUID));

			if(c==0)
			{
				checkifEqual("GetClassName", clas->GetName(), "My first Class");
				checkifEqual("GetClassUUID", resultUUID, classUUID1);
			}
			else if(c==1)
			{
				checkifEqual("GetClassName", clas->GetName(), "My second Class");
				checkifEqual("GetClassUUID", resultUUID, classUUID2);
			}
		}

		size_t mapDefCount = 0;
		__checkVCOM(mvrRead->GetMappingDefinitionCount(mapDefCount));
		
		checkifEqual("GetMappingDefinitionCount", mapDefCount, (size_t)2);
		
		IMappingDefinitionPtr mapDef1 = nullptr;
		if(__checkVCOM(mvrRead->GetMappingDefinitionAt(0, &mapDef1)))
		{
			__checkVCOM(mapDef1->GetGuid(resultUUID));
			checkifEqual("GetMapDefUUID", resultUUID, mappingDefinition1UUID);

			Uint32 sizeX = 0;
			__checkVCOM(mapDef1->GetSizeX(sizeX));
			checkifEqual("GetSizeX", (size_t)sizeX, (size_t)1920);

			Uint32 sizeY = 0;
			__checkVCOM(mapDef1->GetSizeY(sizeY));
			checkifEqual("GetSizeY", (size_t)sizeY, (size_t)1080);

			EScaleHandlingType type;
			__checkVCOM(mapDef1->GetScaleHandling(type));
			checkifEqual("GetScaleHandling", (size_t)type, (size_t)EScaleHandlingType::KeepSizeCenter);

			ISourcePtr source = nullptr;
			if(__checkVCOM(mapDef1->GetSource(&source)))
			{
				checkifEqual("Check mapDef1Source value", 			source->GetValue(), 			"mapDef1SourceValue");
				checkifEqual("Check mapDef1Source linkedGeometry", 	source->GetLinkedGeometry(), 	"mapDef1SourceLinkedGeo");

				GdtfDefines::ESourceType type;
				__checkVCOM(source->GetType(type));
				checkifEqual("Check Source1 type", (size_t)type, (size_t)ESourceType::File);
			}
		}

		IMappingDefinitionPtr mapDef2 = nullptr;
		if(__checkVCOM(mvrRead->GetMappingDefinitionAt(1, &mapDef2)))
		{
			__checkVCOM(mapDef2->GetGuid(resultUUID));
			checkifEqual("GetMapDefUUID", resultUUID, mappingDefinition2UUID);

			Uint32 sizeX = 0;
			__checkVCOM(mapDef2->GetSizeX(sizeX));
			checkifEqual("GetSizeX", (size_t)sizeX, (size_t)1280);

			Uint32 sizeY = 0;
			__checkVCOM(mapDef2->GetSizeY(sizeY));
			checkifEqual("GetSizeY", (size_t)sizeY, (size_t)720);

			EScaleHandlingType type;
			__checkVCOM(mapDef2->GetScaleHandling(type));
			checkifEqual("GetScaleHandling", (size_t)type, (size_t)EScaleHandlingType::ScaleKeepRatio);

			ISourcePtr source = nullptr;
			if(__checkVCOM(mapDef2->GetSource(&source)))
			{
				checkifEqual("Check mapDef2Source value", 			source->GetValue(), 			"mapDef2SourceValue");
				checkifEqual("Check mapDef2Source linkedGeometry", 	source->GetLinkedGeometry(), 	"mapDef2SourceLinkedGeo");

				GdtfDefines::ESourceType type;
				__checkVCOM(source->GetType(type));
				checkifEqual("Check mapDef2Source type", (size_t)type, (size_t)ESourceType::CaptureDevice);
			}
		}
    }
}

std::string MvrUnittest::GetTestWheel_PNG(bool readLocation)
{
	std::string path;
	if(readLocation)	{ path =fPath + kSeparator + "GdtfMvrUnitTest" + kSeparator + "wheels" + kSeparator; }
	else 				{ path = UnitTestUtil::GetTestResourceFolder() + kSeparator; }
    path += "MWheel_Img1.png";
    return path;
}

void MvrUnittest::Write_NestedObjects(IMediaRessourceVectorInterfacePtr intfc, ISceneObjPtr layer)
{    
    MvrUUID trussUUID(1808353898, 683171502, 518343034, 0000000005);        
    ISceneObjPtr trussObj1 = nullptr;
	__checkVCOM(intfc->CreateTruss( trussUUID, STransformMatrix(), "Truss with childs", layer, &trussObj1));

    MvrUUID fixtUUID(1808353111, 683171502, 518343035, 0000000005);
    ISceneObjPtr fixtObject = nullptr;
    __checkVCOM(intfc->CreateFixture( fixtUUID, STransformMatrix(), "Fixture Inside a Truss", trussObj1, &fixtObject));
        
    MvrUUID focuesPtUUID(1808353111, 683171502, 527343035, 0000000005);
    ISceneObjPtr focuesPtObject = nullptr;
    __checkVCOM(intfc->CreateFocusPoint( focuesPtUUID, STransformMatrix(), "FocusPt in Fixture", fixtObject, &focuesPtObject));

    MvrUUID projUUID(1808353111, 683171502, 515243035, 0000000005);
    ISceneObjPtr projObject = nullptr;
    __checkVCOM(intfc->CreateProjector( projUUID, STransformMatrix(), "Projector in FocuesPt", focuesPtObject, &projObject));

    MvrUUID videoScreenUUID(1808353111, 683171502, 533343035, 0000000005);
    ISceneObjPtr videoScreenObject = nullptr;
    __checkVCOM(intfc->CreateVideoScreen( videoScreenUUID, STransformMatrix(), "VideoScreen in Projector", projObject, &videoScreenObject));

    MvrUUID supportUUID(1808353111, 683171502, 518344435, 0000000005);
    ISceneObjPtr supportObject = nullptr;
    __checkVCOM(intfc->CreateSupport( supportUUID, STransformMatrix(), "Support in VideoScreen", videoScreenObject, &supportObject));
    
    MvrUUID sceneObjUUID(1808353111, 683171502, 544443035, 0000000005);
    ISceneObjPtr sceneObject = nullptr;
    __checkVCOM(intfc->CreateSceneObject( sceneObjUUID, STransformMatrix(), "SceneObj in SupportObj", supportObject, &sceneObject));
    
    MvrUUID truss2_UUID(1808353112, 683171402, 888343025, 0000000001);
    ISceneObjPtr trussObj2 = nullptr;
    __checkVCOM(intfc->CreateTruss( truss2_UUID, STransformMatrix(), "Truss in SceneObj", sceneObject, &trussObj2));
}

bool FindObjByName(IMediaRessourceVectorInterfacePtr interf, ISceneObjPtr container, MvrString objNam, ISceneObj** outObj)
{
    ISceneObj* child = nullptr;
    interf->GetFirstChild( container, &child);

    while (child)
    {        
        std::string nam = child->GetName();
        
        if ( nam == objNam)
        {
            *outObj = child;
            
            return true;
        }        

        interf->GetNextObject(child, &child);
    }   

    return false;
}

void MvrUnittest::Read_TestGroup(IMediaRessourceVectorInterfacePtr interf, ISceneObjPtr layer)
{
    bool succes = false;
    
    ISceneObjPtr grp;    
    bool found = FindObjByName(interf, layer, "My Group Name", &grp);
    
    if (found)
    {
        ISceneObjPtr firstChld;
        interf->GetFirstChild(grp, &firstChld);

        if (firstChld)
        {
            std::string nam = firstChld->GetName();
            succes = (nam == "Truss in Group");
        }
    }

    checkifTrue( "Read_TestGroup", succes);
}

void MvrUnittest::Read_NestedObjects(IMediaRessourceVectorInterfacePtr interf, ISceneObjPtr layer)
{   
    bool success = false;

    ISceneObjPtr truss;    
    bool found = FindObjByName(interf, layer, "Truss with childs", &truss);
    
    if (found)
    {        
        success = Read_NestedObjectsInTruss(interf, truss);
    }
    
    checkifTrue( "Read_NestedObjects", success);
}

bool MvrUnittest::verifyFirstChildType( IMediaRessourceVectorInterfacePtr interf, ISceneObjPtr obj, ESceneObjType exptectedTyp)
{    
    bool success = false;

    if (obj)
    {    
        ISceneObjPtr chld;
        interf->GetFirstChild( obj, &chld);
    
        if (chld)
        {        
            ESceneObjType child_typ;
            chld->GetType(child_typ);        

            success = exptectedTyp == child_typ;        
        }
    }   

    return success;
}

bool MvrUnittest::Read_NestedObjectsInTruss(IMediaRessourceVectorInterfacePtr interf, ISceneObjPtr truss)
{
    bool success = true; // Must be inited with true to make the & operations work properly below.

    success &= verifyFirstChildType( interf, truss, ESceneObjType::Fixture);
    ISceneObjPtr chld;
    interf->GetFirstChild( truss, &chld);
    
    success &= verifyFirstChildType( interf, chld, ESceneObjType::FocusPoint);    
    interf->GetFirstChild( chld, &chld);
    
    success &= verifyFirstChildType( interf, chld, ESceneObjType::Projector);    
    interf->GetFirstChild( chld, &chld);
    
    success &= verifyFirstChildType( interf, chld, ESceneObjType::VideoScreen);    
    interf->GetFirstChild( chld, &chld);

    success &= verifyFirstChildType( interf, chld, ESceneObjType::Support);    
    interf->GetFirstChild( chld, &chld);

    success &= verifyFirstChildType( interf, chld, ESceneObjType::SceneObj);    
    interf->GetFirstChild( chld, &chld);

    success &= verifyFirstChildType( interf, chld, ESceneObjType::Truss);

    return success;
}

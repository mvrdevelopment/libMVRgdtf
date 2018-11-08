//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include <iostream>
#include "TXStringUnittest.h"
#include "MvrUnittest.h"
#include "Include/VectorworksMVR.h"

using namespace VectorworksMVR;

#define 	FILE_NAME				"/home/redblue/Dokumente/DEV/libVectorworksMvrGdtf/testfiles/unittestOutput.mvr"
#define 	GDTFFOLDER				"/home/redblue/Dokumente/DEV/libVectorworksMvrGdtf/testfiles/"
#define		VCOM_SUCCEEDED(x)		(x == 0)
#define		VCOM_FAILED(x)			(x != 0)

void WriteMVR();

int main()
{
	std::cout << "Start Unit Test" << std::endl; 
	//TXStringUnitTest txStringTest;
	//bool ret  = txStringTest.RunTest();

	WriteMVR();
	return 0;
}

void WriteMVR()
{
	std::cout << "======================================================" << std::endl;
	std::cout << "=                 writing mvr file                   =" << std::endl;
	std::cout << "======================================================" << std::endl;
	
	//------------------------------------------------------------------------------------------------
	// Create Pointer to MVR Interface
	IMediaRessourceVectorInterfacePtr mvrFileWrite( IID_MediaRessourceVectorInterface );
	
	//------------------------------------------------------------------------------------------------
	// Open file for write
	VCOM_SUCCEEDED(mvrFileWrite->OpenForWrite(FILE_NAME));
	
	
	// Set the libary folder for GDTF files, during export the Interface will look in this
	// folder if there is gdtf file that is needed by MVR, and then add it to the ZIP file
	VCOM_SUCCEEDED(mvrFileWrite->AddGdtfFolderLocation(GDTFFOLDER));
	
	//------------------------------------------------------------------------------------------------
	// Open file for write
	ISceneDataProviderPtr obj;
	VCOM_SUCCEEDED(mvrFileWrite->CreateDataProviderObject("Test Data", "1", &obj));
	
	VCOM_SUCCEEDED(obj->AddKeyValue("Key", "Value"));
	
	//------------------------------------------------------------------------------------------------
	// Now write positions and symdefs
	IPositionPtr position = nullptr;
	VCOM_SUCCEEDED(mvrFileWrite->CreatePositionObject(UUID(688696821, 558449194, 2115941252, 1809800703), "My Position", & position));
	
	
	ISymDefPtr symDef1 = nullptr;
	VCOM_SUCCEEDED(mvrFileWrite->CreateSymDefObject(UUID(122079618, 11832014, 669376348, 947930087), "Symbol Definition for the FocusPoint", & symDef1));
	

	
	VCOM_SUCCEEDED(symDef1->AddGeometry(STransformMatrix()));
	
	
	
	//------------------------------------------------------------------------------------------------
	// Now write content
	
	// First create a layer
	ISceneObjPtr layer1 = nullptr;
	VCOM_SUCCEEDED(mvrFileWrite->CreateLayerObject(UUID(465143117, 742747285, 1361655924, 1172316535), "My Layer 1", & layer1));
	
	// Create two classes
	IClassPtr clas1 = nullptr;
	VCOM_SUCCEEDED(mvrFileWrite->CreateClassObject(UUID(122074618, 11852014, 669377348, 947530087), "My first Class", & clas1));
	
	// Create two classes
	IClassPtr clas2 = nullptr;
	VCOM_SUCCEEDED(mvrFileWrite->CreateClassObject(UUID(122774618, 11892014, 669397348, 947530057), "My second Class", & clas2));
	
	
	// Create Focus Point
	ISceneObjPtr focusPoint = nullptr;
	VCOM_SUCCEEDED(mvrFileWrite->CreateFocusPoint(UUID(1998334672, 457193269, 1786021763, 1463564339), STransformMatrix(), "My FocusPoint", layer1, & focusPoint));
	VCOM_SUCCEEDED(focusPoint->AddSymbol(STransformMatrix(), symDef1));
	VCOM_SUCCEEDED(focusPoint->SetClass(clas1));
	
	// And place some fixtures on it
	ISceneObjPtr fixture1 = nullptr;
	VCOM_SUCCEEDED(mvrFileWrite->CreateFixture(UUID(1808353427, 683171502, 518343034, 1766902383), STransformMatrix(), "My Fixture Name", layer1, & fixture1));
	
	VCOM_SUCCEEDED(fixture1->SetGdtfName("Martin@Mac Aura XB"));
	VCOM_SUCCEEDED(fixture1->SetGdtfMode("Mode 1 v1.1"));
	VCOM_SUCCEEDED(fixture1->AddAdress(1542, 0));
	VCOM_SUCCEEDED(fixture1->AddAdress(25, 1));
	VCOM_SUCCEEDED(fixture1->SetFocusPoint(focusPoint));
	VCOM_SUCCEEDED(fixture1->SetPosition(position));
	VCOM_SUCCEEDED(fixture1->SetClass(clas2));
	
	// And another fixture
	ISceneObjPtr fixture2 = nullptr;
	VCOM_SUCCEEDED(mvrFileWrite->CreateFixture(UUID(1136161871, 1699151080, 751939975, 1748783014), STransformMatrix(), "My Fixture Name", layer1, & fixture2));
	
	VCOM_SUCCEEDED(fixture2->SetGdtfName("Martin@Mac Aura XB"));
	VCOM_SUCCEEDED(fixture2->SetGdtfMode("My fancy other GDTF DMX Mode"));
	VCOM_SUCCEEDED(fixture2->AddAdress(352, 0));
	VCOM_SUCCEEDED(fixture2->AddAdress(5684, 1));
	VCOM_SUCCEEDED(fixture2->SetFocusPoint(focusPoint));
	
	// Create second Layer
	ISceneObjPtr layer2 = nullptr;
	VCOM_SUCCEEDED(mvrFileWrite->CreateLayerObject(UUID(465143117, 742747285, 1361655924, 1172316535), "My Layer 2", & layer2));
	
	
	ISceneObjPtr fixture3= nullptr;
	VCOM_SUCCEEDED(mvrFileWrite->CreateFixture(UUID(1136161871, 1699151080, 751939975, 1748783014), STransformMatrix(), "My Fixture Name", layer2, & fixture3));
	
	VCOM_SUCCEEDED(fixture3->SetGdtfName("Martin@Mac Aura XB"));
	VCOM_SUCCEEDED(fixture3->SetGdtfMode("My fancy other GDTF DMX Mode"));
	VCOM_SUCCEEDED(fixture3->AddAdress(352, 0));
	VCOM_SUCCEEDED(fixture3->AddAdress(5684, 1));
	VCOM_SUCCEEDED(fixture3->SetFocusPoint(focusPoint));
	
	//------------------------------------------------------------------------------------------------
	// At the end just call close
	std::cout << "writing file..." << std::endl;
	VCOM_SUCCEEDED(mvrFileWrite->Close());
	std::cout << "finished" << std::endl;
	
	//------------------------------------------------------------------------------------------------
	// Create Pointer to MVR Interface
	IMediaRessourceVectorInterfacePtr mvrFileRead( IID_MediaRessourceVectorInterface );
	
	std::cout << "======================================================" << std::endl;
	std::cout << "=                 reading mvr file                   =" << std::endl;
	std::cout << "======================================================" << std::endl;
	
	//------------------------------------------------------------------------------------------------
	// Open file for read
	VCOM_SUCCEEDED(mvrFileRead->OpenForRead(FILE_NAME));
	
	//------------------------------------------------------------------------------------------------
	// Traverse SymbolDefs
	size_t  countSymbols = 0;
	VCOM_SUCCEEDED(mvrFileRead->GetSymDefCount(countSymbols));
	
	MvrString fileForGeom;
	for (size_t i = 0; i <countSymbols; i++)
	{
		ISymDefPtr symDef = nullptr;
		VCOM_SUCCEEDED(mvrFileRead->GetSymDefAt(i, & symDef));
		
		size_t geoCount = 0;
		VCOM_SUCCEEDED(symDef->GetGeometryCount(geoCount));
		
		for (size_t j = 0; j < geoCount; j++)
		{
			IGeometryReferencePtr geoRef = nullptr;
			VCOM_SUCCEEDED(symDef->GetGeometryAt(j, & geoRef));

			
			// First way to get a file is to just get the path to the file
			// You can use the own importer to read this file
			fileForGeom = geoRef->GetFileForGeometry();
			//_P(fileForGeom);
			
			
			// This is a little bit tricky, because during the GetGeometry call all the
			// calls from the GeometryRecivers are called.
			// So there are no getters in there but you have to listen to the calls.
		}
	}
	
	
	//------------------------------------------------------------------------------------------------
	// Read Layers
	ISceneObjPtr readLayer = nullptr;
	VCOM_SUCCEEDED(mvrFileRead->GetFirstLayer(&readLayer));
	
	while (readLayer)
	{
		ISceneObjPtr sceneObj = nullptr;
		VCOM_SUCCEEDED(mvrFileRead->GetFirstChild(readLayer, &sceneObj));
		
		_P(readLayer->GetName());
		
		while (sceneObj)
		{
			ESceneObjType type;
			VCOM_SUCCEEDED(sceneObj->GetType(type));
			
			if (type == ESceneObjType::Fixture)
			{
				// Do stuff here
				//_P(sceneObj->GetGdtfName());
				//_P(sceneObj->GetGdtfMode());
				
				// Read the GDTF File
				IGdtfFixturePtr fixture;
				if (VCOM_SUCCEEDED(sceneObj->GetGdtfFixture( & fixture)))
				{
					//_P(fixture->GetName());
				}
			}
			
			_P(sceneObj->GetName());
			
			//------------------------------------------------------------------------
			// Step to next Obj
			ISceneObjPtr next = nullptr;
			VCOM_SUCCEEDED(mvrFileRead->GetNextObject(sceneObj, &next));
			sceneObj = next;
		}
		
		ISceneObjPtr nextLayer = nullptr;
		VCOM_SUCCEEDED(mvrFileRead->GetNextObject(readLayer, &nextLayer));
		readLayer = nextLayer;
	}
}
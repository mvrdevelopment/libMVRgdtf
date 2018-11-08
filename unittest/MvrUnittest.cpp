//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include "MvrUnittest.h"

#include "Include/VectorworksMVR.h"

#define 	FILE_NAME				"/home/redblue/Dokumente/DEV/libVectorworksMvrGdtf/testfiles/unittestOutput.mvr"
#define 	GDTFFOLDER				"/home/redblue/Dokumente/DEV/libVectorworksMvrGdtf/testfiles/"

using namespace VectorworksMVR;

#define __checkVCOM(x) checkVCOM(x, #x)

MvrUnittest::MvrUnittest()
{

}

MvrUnittest::~MvrUnittest()
{
    
}

bool MvrUnittest::ExecuteTest()
{
    WriteFile();
    ReadFile();

    return true;
}

void MvrUnittest::WriteFile()
{
	//------------------------------------------------------------------------------------------------
	// Create Pointer to MVR Interface
	IMediaRessourceVectorInterfacePtr mvrFileWrite( IID_MediaRessourceVectorInterface );

	//------------------------------------------------------------------------------------------------
	// Open file for write
    if(__checkVCOM(mvrFileWrite->OpenForWrite(FILE_NAME)))
    {
        //------------------------------------------------------------------------------------------------
        // Open file for write
        ISceneDataProviderPtr obj;
        if(__checkVCOM(mvrFileWrite->CreateDataProviderObject("Test Data", "1", &obj)))
        {
            __checkVCOM(obj->AddKeyValue("Key", "Value"));
        }
        
        //------------------------------------------------------------------------------------------------
        // Now write positions and symdefs
        IPositionPtr position = nullptr;
        if(__checkVCOM(mvrFileWrite->CreatePositionObject(UUID(688696821, 558449194, 2115941252, 1809800703), "My Position", & position)))
        {
        }

        ISymDefPtr symDef1 = nullptr;
        if(__checkVCOM(mvrFileWrite->CreateSymDefObject(UUID(122079618, 11832014, 669376348, 947930087), "Symbol Definition for the FocusPoint", & symDef1)))
        {
        }
        
        if(__checkVCOM(symDef1->AddGeometry(STransformMatrix())))
        {
        }

        //------------------------------------------------------------------------------------------------
        // Now write content

        // First create a layer
        ISceneObjPtr layer1 = nullptr;
        if(__checkVCOM(mvrFileWrite->CreateLayerObject(UUID(465143117, 742747285, 1361655924, 1172316535), "My Layer 1", & layer1)))
        {
        }
	
        // Create two classes
        IClassPtr clas1 = nullptr;
        if(__checkVCOM(mvrFileWrite->CreateClassObject(UUID(122074618, 11852014, 669377348, 947530087), "My first Class", & clas1)))
        {
        }
        
        // Create two classes
        IClassPtr clas2 = nullptr;
        if(__checkVCOM(mvrFileWrite->CreateClassObject(UUID(122774618, 11892014, 669397348, 947530057), "My second Class", & clas2)))
        {
        }
        
        // Create Focus Point
        ISceneObjPtr focusPoint = nullptr;
        if(__checkVCOM(mvrFileWrite->CreateFocusPoint(UUID(1998334672, 457193269, 1786021763, 1463564339), STransformMatrix(), "My FocusPoint", layer1, & focusPoint)))
        {
        }

        if(__checkVCOM(focusPoint->AddSymbol(STransformMatrix(), symDef1)))
        {
        }

        if(__checkVCOM(focusPoint->SetClass(clas1)))
        {
        }

        // And place some fixtures on it
        ISceneObjPtr fixture1 = nullptr;
        if(__checkVCOM(mvrFileWrite->CreateFixture(UUID(1808353427, 683171502, 518343034, 1766902383), STransformMatrix(), "My Fixture Name", layer1, & fixture1)))
        {
        }
        
        if(__checkVCOM(fixture1->SetGdtfName("Martin@Mac Aura XB")))
        {
        }

        if(__checkVCOM(fixture1->SetGdtfMode("Mode 1 v1.1")))
        {
        }

        if(__checkVCOM(fixture1->AddAdress(1542, 0)))
        {
        }

        if(__checkVCOM(fixture1->AddAdress(25, 1)))
        {
        }

        if(__checkVCOM(fixture1->SetFocusPoint(focusPoint)))
        {
        }

        if(__checkVCOM(fixture1->SetPosition(position)))
        {
        }

        if(__checkVCOM(fixture1->SetClass(clas2)))
        {
        }
        
        // And another fixture
        ISceneObjPtr fixture2 = nullptr;
        if(__checkVCOM(mvrFileWrite->CreateFixture(UUID(1136161871, 1699151080, 751939975, 1748783014), STransformMatrix(), "My Fixture Name", layer1, & fixture2)))
        {
        }
        
        if(__checkVCOM(fixture2->SetGdtfName("Martin@Mac Aura XB")))
        {
        }

        if(__checkVCOM(fixture2->SetGdtfMode("My fancy other GDTF DMX Mode")))
        {
        }

        if(__checkVCOM(fixture2->AddAdress(352, 0)))
        {
        }

        if(__checkVCOM(fixture2->AddAdress(5684, 1)))
        {
        }

	    if(__checkVCOM(fixture2->SetFocusPoint(focusPoint)))
        {
        }


    }
    mvrFileWrite->Close();	
}

void MvrUnittest::ReadFile()
{
	//------------------------------------------------------------------------------------------------
	// Create Pointer to MVR Interface
	IMediaRessourceVectorInterfacePtr mvrRead( IID_MediaRessourceVectorInterface );

    if(__checkVCOM(mvrRead->OpenForRead(FILE_NAME)))
    {
        size_t count = 0;
        __checkVCOM(mvrRead->GetDataProviderObjectCount(count));
        checkifEqual("CountProvider ",count, 1);

        for(size_t i = 0; i <count; i++)
        {
            ISceneDataProviderPtr obj;
            if(__checkVCOM(mvrRead->GetDataProviderObjectAt(i, &obj)))
            {
                checkifEqual("Check Key ", obj->GetKeyAt(0), "Key");
                checkifEqual("Check Value ", obj->GetValueAt(0), "Value");
            }
        }

        // TODO
        __checkVCOM(mvrRead->GetSymDefCount(count));
        checkifEqual("CountSymDef ",count, 1);

        // TODO
        __checkVCOM(mvrRead->GetPositionObjectCount(count));
        checkifEqual("CountPosition ",count, 1);

        //------------------------------------------------------------------------------------------------
	    // Read Layers
	    ISceneObjPtr readLayer = nullptr;
        if(__checkVCOM(mvrRead->GetFirstLayer(&readLayer)))
        {
            checkifEqual("Layer name", readLayer->GetName(), "My Layer 1");
        }
	    

    }
}
//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include "MvrUnittest.h"
#include <iostream>

#include "Include/VectorworksMVR.h"
using namespace VectorworksMVR;

#define __checkVCOM(x) checkVCOM(x, #x)

MvrUnittest::MvrUnittest(const std::string& currentDir)
{
    fPath = currentDir;
    fPath += std::string("/testMvr.mvr");

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
	IMediaRessourceVectorInterfacePtr mvrFileWrite( IID_MediaRessourceVectorInterface );

	//------------------------------------------------------------------------------------------------
	// Open file for write
    if(__checkVCOM(mvrFileWrite->OpenForWrite(fPath.c_str())))
    {
        //------------------------------------------------------------------------------------------------
        // Add Custom data
        ISceneDataProviderPtr obj;
        if(__checkVCOM(mvrFileWrite->CreateDataProviderObject("Test Data", "1", &obj)))
        {
            __checkVCOM(obj->AddKeyValue("Key", "Value"));
        }
        
        //------------------------------------------------------------------------------------------------
        // Write globals
        IPositionPtr position = nullptr;
        __checkVCOM(mvrFileWrite->CreatePositionObject(MvrUUID(688696821, 558449194, 2115941252, 1809800703), "My Position", & position));


        ISymDefPtr symDef1 = nullptr;
        if(__checkVCOM(mvrFileWrite->CreateSymDefObject(MvrUUID(122079618, 11832014, 669376348, 947930087), "Symbol Definition for the FocusPoint", & symDef1)))
        {
            __checkVCOM(symDef1->AddGeometry(STransformMatrix()));
        }
        
        IClassPtr clas1 = nullptr;
        __checkVCOM(mvrFileWrite->CreateClassObject(MvrUUID(122074618, 11852014, 669377348, 947530087), "My first Class", & clas1));

        
        IClassPtr clas2 = nullptr;
        __checkVCOM(mvrFileWrite->CreateClassObject(MvrUUID(122774618, 11892014, 669397348, 947530057), "My second Class", & clas2));

        //------------------------------------------------------------------------------------------------
        // Now write content
        ISceneObjPtr layer1 = nullptr;
        if(__checkVCOM(mvrFileWrite->CreateLayerObject(MvrUUID(465143117, 742747285, 1361655924, 1172316535), "My Layer 1", & layer1)))
        {

            // Create Focus Point
            ISceneObjPtr focusPoint = nullptr;
            if(__checkVCOM(mvrFileWrite->CreateFocusPoint(MvrUUID(1998334672, 457193269, 1786021763, 1463564339), STransformMatrix(), "My FocusPoint", layer1, & focusPoint)))
            {
                __checkVCOM(focusPoint->AddSymbol(STransformMatrix(), symDef1));
                __checkVCOM(focusPoint->SetClass(clas1));
            }

            // And place some fixtures on it
            ISceneObjPtr fixture1 = nullptr;
            if(__checkVCOM(mvrFileWrite->CreateFixture(MvrUUID(1808353427, 683171502, 518343034, 1766902383), STransformMatrix(), "My Fixture Name", layer1, & fixture1)))
            {
                __checkVCOM(fixture1->SetGdtfName("Martin@Mac Aura XB"));
                __checkVCOM(fixture1->SetGdtfMode("My fancy other GDTF DMX Mode"));
                __checkVCOM(fixture1->AddAdress(352, 0));
                __checkVCOM(fixture1->AddAdress(5684, 1));
                __checkVCOM(fixture1->SetFocusPoint(focusPoint));
            }
        }

    }
    mvrFileWrite->Close();
}

void MvrUnittest::ReadFile()
{
	//------------------------------------------------------------------------------------------------
	// Create Pointer to MVR Interface
	IMediaRessourceVectorInterfacePtr mvrRead( IID_MediaRessourceVectorInterface );

    if(__checkVCOM(mvrRead->OpenForRead(fPath.c_str())))
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
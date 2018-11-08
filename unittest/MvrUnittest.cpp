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
}

void MvrUnittest::WriteFile()
{
	//------------------------------------------------------------------------------------------------
	// Create Pointer to MVR Interface
	IMediaRessourceVectorInterfacePtr mvrFileWrite( IID_MediaRessourceVectorInterface );

    if(__checkVCOM(mvrFileWrite->OpenForWrite(FILE_NAME)))
    {
        	ISceneDataProviderPtr obj;
            if(__checkVCOM(mvrFileWrite->CreateDataProviderObject("Test Data", "1", &obj)))
            {
                __checkVCOM(obj->AddKeyValue("Key", "Value"));
            }
            
            // First create a layer
	        ISceneObjPtr layer1 = nullptr;
            if(__checkVCOM(mvrFileWrite->CreateLayerObject(UUID(465143117, 742747285, 1361655924, 1172316535), "My Layer 1", & layer1)))
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
                checkifEqual("Check Key", obj->GetKeyAt(0), "Key");
                checkifEqual("Check Value", obj->GetValueAt(0), "Value");
            }
        }

        //------------------------------------------------------------------------------------------------
	    // Read Layers
	    ISceneObjPtr readLayer = nullptr;
        if(__checkVCOM(mvrRead->GetFirstLayer(&readLayer)))
        {
            checkifEqual("Layer name", readLayer->GetName(), "My Layer 1");
        }
	    

    }
}
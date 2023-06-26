//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include "GdtfRefreshBufferTest.h"
#include "Utility.h"
#include <iostream>

#include "Include/VectorworksMVR.h"
using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;


#define __checkVCOM(x) this->checkVCOM(x, #x)
#define __checkVCOM_NotSet(x) this->checkVCOM_NotSet(x, #x)

GdtfRefreshBufferTest::GdtfRefreshBufferTest(const std::string& currentDir)
{
    fPath = currentDir;
#ifdef _WINDOWS
    fPath += std::string("\\testDmx.gdtf");
#else
    fPath += std::string("/testtest.gdtf");
#endif

	fMvrPath = currentDir;
	fMvrPath += std::string("/testtestMVR.mvr");

    std::cout << "Export File to " << fPath << std::endl; 
}

GdtfRefreshBufferTest::~GdtfRefreshBufferTest()
{
}

bool GdtfRefreshBufferTest::ExecuteTest()
{
	std::cout << "=                                     GdtfRefreshBufferTest                           =" << std::endl;
    WriteFile();
    ReadFile();

    return true;
}

void GdtfRefreshBufferTest::WriteFile()
{
	std::string path 		= UnitTestUtil::GetTestResourceFolder() + kSeparator + "allWorking.gdtf";
	std::FILE*	gdtfFile 	= std::fopen( path.c_str(), "rb" );
	
	// Get Buffer
	size_t length = 0;
	if ( std::fseek( gdtfFile, 0, SEEK_END ) == 0 )
	{
		length = std::ftell( gdtfFile );
	}

	// Get Buffer
	char*  buffer  = new char[length + 1];
	if ( std::fseek( gdtfFile, 0, SEEK_SET ) == 0 )
	{
		std::fread( buffer, 1, length, gdtfFile );		
	}

	// Try to Read It
	IGdtfFixturePtr gdtfWrite (IID_IGdtfFixture);
	if(__checkVCOM(gdtfWrite->FromBuffer(buffer, length)))
	{
		checkifEqual("Name Fixture Type", "Alpha Spot QWO 800",  gdtfWrite->GetName());
	}

	delete[] buffer;

	AddMode(gdtfWrite);

	size_t bufferLength = 0;
	IMediaRessourceVectorInterfacePtr fFileWriter (IID_MediaRessourceVectorInterface);
	
    if(__checkVCOM(fFileWriter->OpenForWrite(fMvrPath.c_str()))) 
    {
		// Now write content
        ISceneObjPtr layer1 = nullptr;
		__checkVCOM(fFileWriter->CreateLayerObject(MvrUUID(465143117, 742747285, 1361655924, 1172316535), "My Layer 1", &layer1));
			
		// And place some fixtures on it
		ISceneObjPtr fixture1 = nullptr;
		if (__checkVCOM(fFileWriter->CreateFixture(MvrUUID(1808353427, 683171502, 518343034, 1766902383), STransformMatrix(), "My Fixture1 Name", layer1, &fixture1)))
		{
			__checkVCOM(fixture1->SetGdtfName("testtest2.gdtf"));
			__checkVCOM(fixture1->SetGdtfMode("Standard Mode (32 ch)"));
			__checkVCOM(fixture1->SetCastShadow(true));
		}

		__checkVCOM(gdtfWrite->RefreshBuffer());

		if(__checkVCOM(gdtfWrite->GetBufferLength(bufferLength)) && bufferLength > 0)
		{			
			char* buffer = new char[bufferLength];
			__checkVCOM(gdtfWrite->ToBuffer(buffer));
			fFileWriter->AddBufferToMvrFile("testtest2.gdtf", buffer, bufferLength);
			delete[] buffer;
		}

    }

    __checkVCOM(fFileWriter->Close());

}

void GdtfRefreshBufferTest::ReadFile()
{
	//------------------------------------------------------------------------------------------------
	// Create Pointer to GDTF Interface from MVR file
	IMediaRessourceVectorInterfacePtr mvrRead(IID_MediaRessourceVectorInterface);
	if(__checkVCOM(mvrRead->OpenForRead(fMvrPath.c_str())))
    {
		//------------------------------------------------------------------------------------------------
		// Read Layers
		ISceneObjPtr readLayer = nullptr;
		__checkVCOM(mvrRead->GetFirstLayer(&readLayer));

		while (readLayer)
		{
			ISceneObjPtr sceneObj = nullptr;
			__checkVCOM(mvrRead->GetFirstChild(readLayer, &sceneObj));

			while (sceneObj)
			{
				ESceneObjType type;
				__checkVCOM(sceneObj->GetType(type));
				
				// ------------------------------------------------------------------------------
				// Get Fixture
				if (type == ESceneObjType::Fixture)
				{
					//Linked Fixture
					IGdtfFixturePtr gdtfLinkedFixture;
					__checkVCOM(sceneObj->GetGdtfFixture( &gdtfLinkedFixture));

					//------------------------------------------------------------------
					// Get DMX Mode
					size_t countDmxModes;
					__checkVCOM(gdtfLinkedFixture->GetDmxModeCount(countDmxModes));
					this->checkifEqual("Check Count DMX Modes", countDmxModes, size_t(2));

					//------------------------------------------------------------------
					// Get DMX Mode TEST

					IGdtfDmxModePtr mode;
					__checkVCOM(gdtfLinkedFixture->GetDmxModeAt(1, &mode));
					
					size_t countChannels2 = 0;
					__checkVCOM(mode->GetDmxChannelCount(countChannels2));
					this->checkifEqual("Check Count DMX Channels 2", countChannels2, size_t(4));

					size_t countBreaks2 = 0;
					__checkVCOM(mode->GetBreakCount(countBreaks2));
					this->checkifEqual("Check Count DMX Breaks 2", countBreaks2, size_t(4));

					IGdtfDmxChannelPtr channel1;
					__checkVCOM(mode->GetDmxChannelAt(0, &channel1));
					CheckDmxChannel(channel1, 1, 1, 4);

					IGdtfDmxChannelPtr channel2;
					__checkVCOM(mode->GetDmxChannelAt(1, &channel2));
					CheckDmxChannel(channel2, 2, 1, 6);

					IGdtfDmxChannelPtr channel3;
					__checkVCOM(mode->GetDmxChannelAt(2, &channel3));
					CheckDmxChannel(channel3, 3, 1, 8);

					IGdtfDmxChannelPtr channel4;
					__checkVCOM(mode->GetDmxChannelAt(3, &channel4));
					CheckDmxChannel(channel4, 4, 1, 10);

					size_t footprint = 0;
					__checkVCOM(mode->GetFootprintForBreak(1, footprint));
					this->checkifEqual("Check the footprint1", footprint, size_t(4));

					footprint = 0;
					__checkVCOM(mode->GetFootprintForBreak(2, footprint));
					this->checkifEqual("Check the footprint2", footprint, size_t(6));

					footprint = 0;
					__checkVCOM(mode->GetFootprintForBreak(3, footprint));
					this->checkifEqual("Check the footprint3", footprint, size_t(8));

					footprint = 0;
					__checkVCOM(mode->GetFootprintForBreak(4, footprint));
					this->checkifEqual("Check the footprint4", footprint, size_t(10));

					PrintParsingErrorList(gdtfLinkedFixture);
				}

				ISceneObjPtr next = nullptr;
				mvrRead->GetNextObject(sceneObj, &next);
				sceneObj = next;
			}

			ISceneObjPtr nextLayer = nullptr;
			mvrRead->GetNextObject(readLayer, &nextLayer);
			readLayer = nextLayer;		
		}

		__checkVCOM(mvrRead->Close());
	}	
    
}


void GdtfRefreshBufferTest::CheckDmxChannel(VectorworksMVR::IGdtfDmxChannelPtr& dmxChannel, Sint32 dmxBreak, Sint32 coarse, Sint32 fine)
{
	Sint32 thisDmxBreak = 0;
	__checkVCOM(dmxChannel->GetDmxBreak(thisDmxBreak));
	this->checkifEqual("Check DmxChannel DMXBreak - Default: 1 ", dmxBreak, thisDmxBreak);

	Sint32 thisDmxCoarse = 0;
	__checkVCOM(dmxChannel->GetCoarse(thisDmxCoarse));
	this->checkifEqual("Check DmxChannel Coarse - Default: \"None\" ", coarse, thisDmxCoarse);

	Sint32 thisDmxFine = 0;
	__checkVCOM(dmxChannel->GetFine(thisDmxFine));
	this->checkifEqual("Check DmxChannel Fine - Default: \"None\"  ", fine, thisDmxFine);
}

void GdtfRefreshBufferTest::AddMode(IGdtfFixturePtr gdtfWrite)
{
	// Feature Groups
	IGdtfFeatureGroupPtr featureGroup;
	__checkVCOM(gdtfWrite->CreateFeatureGroup("FeatureGroup","FeatureGroup", &featureGroup));

	IGdtfFeaturePtr feature;
	__checkVCOM(featureGroup->CreateFeature("Feature", & feature));

	//----------------------------------------------------------------
	// Create Attribute
	IGdtfAttributePtr attribute1;
	__checkVCOM(gdtfWrite->CreateAttribute("Attribute1", "Pretty", &attribute1));
	attribute1->SetFeature(feature);

	IGdtfAttributePtr attribute2;
	__checkVCOM(gdtfWrite->CreateAttribute("Attribute2", "Pretty", &attribute2));
	attribute2->SetFeature(feature);

	IGdtfAttributePtr attribute3;
	__checkVCOM(gdtfWrite->CreateAttribute("Attribute3", "Pretty", &attribute3));
	attribute3->SetFeature(feature);

	IGdtfAttributePtr attribute4;
	__checkVCOM(gdtfWrite->CreateAttribute("Attribute4", "Pretty", &attribute4));
	attribute4->SetFeature(feature);

	//----------------------------------------------------------------
	// Create Model
	IGdtfModelPtr model;
	__checkVCOM(gdtfWrite->CreateModel("Model", &model));

	IGdtfGeometryPtr geometry;
	__checkVCOM(gdtfWrite->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "Geometry", model, STransformMatrix(), &geometry));

	//----------------------------------------------------------------
	for(size_t i = 1; i < 2; i++)
	{
		IGdtfDmxModePtr gdtfMode;
		__checkVCOM(gdtfWrite->CreateDmxMode("Mode TEST", &gdtfMode));
		{
			gdtfMode->SetGeometry(geometry);

			Sint32 footprint1 = 4;
			if(footprint1 > 0)
			{
				IGdtfDmxChannelPtr gdtfChannel2;
				__checkVCOM(gdtfMode->CreateDmxChannel(geometry, &gdtfChannel2));
				gdtfChannel2->SetDmxBreak(1);
				gdtfChannel2->SetCoarse(1);
				gdtfChannel2->SetFine(footprint1);

				// First Logical Channel
				IGdtfDmxLogicalChannelPtr gdtfLogicalChannel;
				gdtfChannel2->CreateLogicalChannel(attribute1, &gdtfLogicalChannel);
				gdtfLogicalChannel->SetAttribute(attribute1);

				IGdtfDmxChannelFunctionPtr gdtfFunction;
				gdtfLogicalChannel->CreateDmxFunction("FunctionTest", &gdtfFunction);
				gdtfFunction->SetStartAddress(0);
				gdtfFunction->SetAttribute(attribute1);
			}

			Sint32 footprint2 = 6;
			if(footprint2 > 0)
			{
				IGdtfDmxChannelPtr gdtfChannel2;
				__checkVCOM(gdtfMode->CreateDmxChannel(geometry, &gdtfChannel2));
				gdtfChannel2->SetDmxBreak(2);
				gdtfChannel2->SetCoarse(1);
				gdtfChannel2->SetFine(footprint2);

				// First Logical Channel
				IGdtfDmxLogicalChannelPtr gdtfLogicalChannel;
				gdtfChannel2->CreateLogicalChannel(attribute2, &gdtfLogicalChannel);
				gdtfLogicalChannel->SetAttribute(attribute2);

				IGdtfDmxChannelFunctionPtr gdtfFunction;
				gdtfLogicalChannel->CreateDmxFunction("FunctionTest", &gdtfFunction);
				gdtfFunction->SetStartAddress(0);
				gdtfFunction->SetAttribute(attribute2);
			}

			Sint32 footprint3 = 8;
			if(footprint3 > 0)
			{
				IGdtfDmxChannelPtr gdtfChannel2;
				__checkVCOM(gdtfMode->CreateDmxChannel(geometry, &gdtfChannel2));
				
				gdtfChannel2->SetDmxBreak(3);
				gdtfChannel2->SetCoarse(1);
				gdtfChannel2->SetFine(footprint3);

				// First Logical Channel
				IGdtfDmxLogicalChannelPtr gdtfLogicalChannel;
				gdtfChannel2->CreateLogicalChannel(attribute3, &gdtfLogicalChannel);
				gdtfLogicalChannel->SetAttribute(attribute3);

				IGdtfDmxChannelFunctionPtr gdtfFunction;
				gdtfLogicalChannel->CreateDmxFunction("FunctionTest", &gdtfFunction);
				gdtfFunction->SetStartAddress(0);
				gdtfFunction->SetAttribute(attribute3);                              
				
			}

			Sint32 footprint4 = 10;
			if(footprint4 > 0)
			{
				IGdtfDmxChannelPtr gdtfChannel2;
				__checkVCOM(gdtfMode->CreateDmxChannel(geometry, &gdtfChannel2));
				gdtfChannel2->SetDmxBreak(4);
				gdtfChannel2->SetCoarse(1);
				gdtfChannel2->SetFine(footprint4);

				// First Logical Channel
				IGdtfDmxLogicalChannelPtr gdtfLogicalChannel;
				gdtfChannel2->CreateLogicalChannel(attribute4, &gdtfLogicalChannel);
				gdtfLogicalChannel->SetAttribute(attribute4);

				IGdtfDmxChannelFunctionPtr gdtfFunction;
				gdtfLogicalChannel->CreateDmxFunction("FunctionTest", &gdtfFunction);
				gdtfFunction->SetStartAddress(0);
				gdtfFunction->SetAttribute(attribute4);                             
				
			}

			
		}
		//----------------------------------------------------------------

    }
}
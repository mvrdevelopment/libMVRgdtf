//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include "GdtfDmxUnittest.h"
#include <iostream>

#include "Include/VectorworksMVR.h"
using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;


#define __checkVCOM(x) this->checkVCOM(x, #x)
#define __checkVCOM_NotSet(x) this->checkVCOM_NotSet(x, #x)

GdtfDmxUnittest::GdtfDmxUnittest(const std::string& currentDir)
{
    fPath = currentDir;
#ifdef _WINDOWS
    fPath += std::string("\\testDmx.gdtf");
#else
    fPath += std::string("/testDmx.gdtf");
#endif

    std::cout << "Export File to " << fPath << std::endl; 
}

GdtfDmxUnittest::~GdtfDmxUnittest()
{  
}

bool GdtfDmxUnittest::ExecuteTest()
{
	std::cout << "=                                     GdtfDmxUnittest                                      =" << std::endl;
    WriteFile();
    ReadFile();

    return true;
}

void GdtfDmxUnittest::WriteFile()
{
	//------------------------------------------------------------------------------------------------
	// Create Pointer to GDTF Interface
	IGdtfFixturePtr gdtfWrite (IID_IGdtfFixture);

    MvrUUID uuid (225204211, 177198167, 1575790, 96627);
    if(__checkVCOM(gdtfWrite->OpenForWrite(fPath.c_str(),"My FixtureName","My Manufacturer", uuid)))
    {
		// Feature Groups
		IGdtfFeatureGroupPtr featureGroup;
		__checkVCOM(gdtfWrite->CreateFeatureGroup("FeatureGroup","FeatureGroup", &featureGroup));

		IGdtfFeaturePtr feature;
		__checkVCOM(featureGroup->CreateFeature("Feature", & feature));

		//----------------------------------------------------------------
		// Create Attribute
		IGdtfAttributePtr attribute1;
		__checkVCOM(gdtfWrite->CreateAttribute("Attribute1","Pretty", &attribute1));
		attribute1->SetFeature(feature);

		IGdtfAttributePtr attribute2;
		__checkVCOM(gdtfWrite->CreateAttribute("Attribute2","Pretty", &attribute2));
		attribute2->SetFeature(feature);

		IGdtfAttributePtr attribute3;
		__checkVCOM(gdtfWrite->CreateAttribute("Attribute3","Pretty", &attribute3));
		attribute3->SetFeature(feature);

		IGdtfAttributePtr attribute4;
		__checkVCOM(gdtfWrite->CreateAttribute("Attribute4","Pretty", &attribute4));
		attribute4->SetFeature(feature);

		IGdtfAttributePtr attribute5;
		__checkVCOM(gdtfWrite->CreateAttribute("Attribute5","Pretty", &attribute5));
		attribute5->SetFeature(feature);

		IGdtfAttributePtr attribute6;
		__checkVCOM(gdtfWrite->CreateAttribute("Attribute6","Pretty", &attribute6));
		attribute6->SetFeature(feature);

		//----------------------------------------------------------------
		// Create Model
		IGdtfModelPtr model;
		__checkVCOM(gdtfWrite->CreateModel("Model", &model));

		IGdtfGeometryPtr geometry;
		__checkVCOM(gdtfWrite->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "Geometry", model, STransformMatrix(), &geometry));

		IGdtfGeometryPtr geoToRef;
		__checkVCOM(gdtfWrite->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "Geometry to ref", model, STransformMatrix(), &geoToRef));

		IGdtfGeometryPtr geoRef;
		__checkVCOM(geometry->CreateGeometry(EGdtfObjectType::eGdtfGeometryReference, "GeoRef", nullptr, STransformMatrix(), &geoRef));
		__checkVCOM(geoRef->SetGeometryReference(geoToRef));


		IGdtfBreakPtr break3;
		__checkVCOM(geoRef->CreateBreak(3,5, &break3));

		IGdtfBreakPtr refBreak;
		__checkVCOM(geoRef->CreateBreak(3, 1, &refBreak));

		IGdtfGeometryPtr childGeoOfRef;
		__checkVCOM(geoToRef->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "Child of refed Geo", model, STransformMatrix(), &childGeoOfRef));

		IGdtfDmxModePtr mode;
		__checkVCOM(gdtfWrite->CreateDmxMode("Mode", &mode));
		__checkVCOM(mode->SetDescription("Mode Description"));
		__checkVCOM(mode->SetGeometry(geometry));

		//----------------------------------------------------------------
		// Write 8 bit Channel
		IGdtfDmxChannelPtr bit8channel;
		__checkVCOM(mode->CreateDmxChannel(geometry, &bit8channel));
		__checkVCOM(bit8channel->SetGeometry(geometry));
		bit8channel->SetCoarse(1);
		//bit8channel->SetDmxBreak(1); This is the default

		//bit8channel->SetHighlight();
		// The default values is none, so we check of this comes in

		// First Logical Channel
		IGdtfDmxLogicalChannelPtr bit8LogicalChannel1;
		bit8channel->CreateLogicalChannel(attribute1, &bit8LogicalChannel1);
		bit8LogicalChannel1->SetAttribute(attribute1);

		IGdtfDmxChannelFunctionPtr bit8Function1;
		bit8LogicalChannel1->CreateDmxFunction("Function1", &bit8Function1);
		bit8Function1->SetStartAddress(0);
		bit8Function1->SetAttribute(attribute1);

		IGdtfDmxChannelSetPtr bit8ChannelSet1;
		bit8Function1->CreateDmxChannelSet("My Name1", 15, 60, &bit8ChannelSet1);

		IGdtfDmxChannelSetPtr bit8ChannelSet2;
		bit8Function1->CreateDmxChannelSet("My Name2", 61, 90, &bit8ChannelSet2);

		IGdtfDmxChannelSetPtr bit8ChannelSet3;
		bit8Function1->CreateDmxChannelSet("My Name3", 91, 92, &bit8ChannelSet3);

			//SubChannelSets
		IGdtfSubPhysicalUnitPtr subPhysicalUnit1;
		__checkVCOM(attribute1->CreateSubPhysicalUnit(EGdtfSubPhysicalUnitType::Duration, &subPhysicalUnit1));
		IGdtfSubPhysicalUnitPtr subPhysicalUnit2;
		__checkVCOM(attribute1->CreateSubPhysicalUnit(EGdtfSubPhysicalUnitType::Amplitude, &subPhysicalUnit2));

		IGdtfDMXProfilePtr gdtfDMXProfile1;
		__checkVCOM(gdtfWrite->CreateDMXProfile(&gdtfDMXProfile1));
		__checkVCOM(gdtfDMXProfile1->SetName("DMXProfile 1"));

		IGdtfDmxSubChannelSetPtr subChannelSet1;
		bit8Function1->CreateDmxSubChannelSet("My SubChannelSet Name 1", subPhysicalUnit1, &subChannelSet1);
		__checkVCOM(subChannelSet1->SetPhysicalFrom(1.1));
		__checkVCOM(subChannelSet1->SetPhysicalTo(1.2));
		__checkVCOM(subChannelSet1->SetDMXProfile(gdtfDMXProfile1));
		IGdtfDmxSubChannelSetPtr subChannelSet2;
		bit8Function1->CreateDmxSubChannelSet("My SubChannelSet Name 2", subPhysicalUnit1, &subChannelSet2);
		__checkVCOM(subChannelSet2->SetPhysicalFrom(2.1));
		__checkVCOM(subChannelSet2->SetPhysicalTo(2.2));
		__checkVCOM(subChannelSet2->SetSubPhysicalUnit(subPhysicalUnit2));

		// Second Channel Function
		IGdtfDmxChannelFunctionPtr bit8Function2;
		bit8LogicalChannel1->CreateDmxFunction("Function2", &bit8Function2);
		bit8Function2->SetStartAddress(100);
		bit8Function2->SetAttribute(attribute1);

		IGdtfDmxChannelSetPtr bit8ChannelSet4;
		bit8Function2->CreateDmxChannelSet("My Name4", 100, 120, &bit8ChannelSet4);

		IGdtfDmxChannelSetPtr bit8ChannelSet5;
		bit8Function2->CreateDmxChannelSet("My Name5", 121, 130, &bit8ChannelSet5);

		IGdtfDmxChannelSetPtr bit8ChannelSet6;
		bit8Function2->CreateDmxChannelSet("My Name6", 160, 165, &bit8ChannelSet6);

		// Second Logical Channel
		IGdtfDmxLogicalChannelPtr bit8LogicalChannel2;
		bit8channel->CreateLogicalChannel(attribute6, &bit8LogicalChannel2);
		bit8LogicalChannel2->SetAttribute(attribute6);

		IGdtfDmxChannelFunctionPtr bit8Function3;
		bit8LogicalChannel2->CreateDmxFunction("Function3", &bit8Function3);
		bit8Function3->SetStartAddress(0);
		bit8Function3->SetAttribute(attribute1);

		IGdtfDmxChannelSetPtr bit8ChannelSet7;
		bit8Function3->CreateDmxChannelSet("My Name7", 170, 170, &bit8ChannelSet7);

		IGdtfDmxChannelSetPtr bit8ChannelSet8;
		bit8Function3->CreateDmxChannelSet("My Name8", 180, 180, &bit8ChannelSet8);

		IGdtfDmxChannelSetPtr bit8ChannelSet9;
		bit8Function3->CreateDmxChannelSet("My Name9", 181, 198, &bit8ChannelSet9);

		// Second Channel Function
		IGdtfDmxChannelFunctionPtr bit8Function4;
		bit8LogicalChannel2->CreateDmxFunction("Function4", &bit8Function4);
		bit8Function4->SetStartAddress(200);
		bit8Function4->SetAttribute(attribute1);

		IGdtfDmxChannelSetPtr bit8ChannelSet10;
		bit8Function4->CreateDmxChannelSet("My Name10", 210, 210, &bit8ChannelSet10);

		IGdtfDmxChannelSetPtr bit8ChannelSet11;
		bit8Function4->CreateDmxChannelSet("My Name11", 220, 225, &bit8ChannelSet11);

		IGdtfDmxChannelSetPtr bit8ChannelSet12;
		bit8Function4->CreateDmxChannelSet("My Name12", 230, 255, &bit8ChannelSet12);

		//----------------------------------------------------------------
		// Write 16 bit Channel
		IGdtfDmxChannelPtr bit16channel;
		__checkVCOM(mode->CreateDmxChannel(geoToRef, &bit16channel));
		__checkVCOM(bit16channel->SetGeometry(geoToRef));
		bit16channel->SetCoarse(1);
		bit16channel->SetFine(2);
		bit16channel->SetDmxBreak(0);
		bit16channel->SetHighlight(256);

		IGdtfDmxLogicalChannelPtr bit16LogicalChannel;
		bit16channel->CreateLogicalChannel(attribute2, &bit16LogicalChannel);
		bit16LogicalChannel->SetAttribute(attribute2);

		IGdtfDmxChannelFunctionPtr bit16Function;
		bit16LogicalChannel->CreateDmxFunction("Function", &bit16Function);
		bit16Function->SetAttribute(attribute1);

		IGdtfDmxChannelSetPtr bit16ChannelSet1;
		bit16Function->CreateDmxChannelSet("My Name1", 15, 60, &bit16ChannelSet1);

		IGdtfDmxChannelSetPtr bit16ChannelSet;
		bit16Function->CreateDmxChannelSet("My Name2", 61, 90, &bit16ChannelSet);

		IGdtfDmxChannelSetPtr bit16ChannelSet3;
		bit16Function->CreateDmxChannelSet("My Name3", 128, 4501, &bit16ChannelSet3);


		__checkVCOM(bit16Function->SetModeMasterFunction(bit8Function4, 15, 78));

		//----------------------------------------------------------------
		// Write 24 bit Channel - With Mode Relation
		IGdtfDmxChannelPtr bit24channel;
		__checkVCOM(mode->CreateDmxChannel(geometry, &bit24channel));
		__checkVCOM(bit24channel->SetDmxBreak(3));
		__checkVCOM(bit24channel->SetGeometry(childGeoOfRef));
		bit24channel->SetCoarse(3);
		bit24channel->SetFine(4);
		bit24channel->SetUltra(5);

		IGdtfDmxLogicalChannelPtr logicalChannel24bit;
		__checkVCOM(bit24channel->CreateLogicalChannel(attribute3, &logicalChannel24bit));
		__checkVCOM(logicalChannel24bit->SetAttribute(attribute3));

		IGdtfDmxChannelFunctionPtr function24bit_1;
		__checkVCOM(logicalChannel24bit->CreateDmxFunction("Log 1", & function24bit_1));
		__checkVCOM(function24bit_1->SetStartAddress(0));
		__checkVCOM(function24bit_1->SetAttribute(attribute1));

		IGdtfDmxChannelFunctionPtr function24bit_2;
		__checkVCOM(logicalChannel24bit->CreateDmxFunction("Log 2", & function24bit_2));
		__checkVCOM(function24bit_2->SetStartAddress(0));
		__checkVCOM(function24bit_2->SetAttribute(attribute1));

		IGdtfDmxChannelFunctionPtr function24bit_3;
		__checkVCOM(logicalChannel24bit->CreateDmxFunction("Log 3", & function24bit_3));
		__checkVCOM(function24bit_3->SetStartAddress(0));
		__checkVCOM(function24bit_3->SetAttribute(attribute1));


		__checkVCOM(function24bit_1->SetModeMasterChannel(bit16channel, 0, 39));
		__checkVCOM(function24bit_2->SetModeMasterChannel(bit16channel, 40, 79));
		__checkVCOM(function24bit_3->SetModeMasterChannel(bit16channel, 80, 179));


		//----------------------------------------------------------------
		// Write 8 bit Channel with no Channel Sets
		IGdtfDmxChannelPtr bit8channel2;
		__checkVCOM(mode->CreateDmxChannel(geometry, &bit8channel2));
		bit8channel2->SetCoarse(19);
		bit8channel2->SetDmxBreak(3);
		IGdtfDmxLogicalChannelPtr bit8_1LogicalChannel1;
		bit8channel2->CreateLogicalChannel(attribute4, &bit8_1LogicalChannel1);

		IGdtfDmxChannelFunctionPtr bit8_1Function1;
		bit8_1LogicalChannel1->CreateDmxFunction("Function1", &bit8_1Function1);
		bit8_1Function1->SetStartAddress(0);
		bit8_1Function1->SetAttribute(attribute1);

		//----------------------------------------------------------------
		// Write virtual Channel
		IGdtfDmxChannelPtr virtualChannel;
		__checkVCOM(mode->CreateDmxChannel(geometry, &virtualChannel));
		__checkVCOM(virtualChannel->SetGeometry(geometry));
		IGdtfDmxLogicalChannelPtr virtualLogicalChannel;
		virtualChannel->CreateLogicalChannel(attribute5, &virtualLogicalChannel);


		IGdtfDmxChannelFunctionPtr virtualFunction;
		virtualLogicalChannel->CreateDmxFunction("Function", &virtualFunction);
		virtualFunction->SetAttribute(attribute5);
		__checkVCOM(virtualFunction->SetDefaultValue(50000));

		IGdtfDmxChannelSetPtr virtualChannelSet1;
		virtualFunction->CreateDmxChannelSet("My Name1", 0, 0, &virtualChannelSet1);

		IGdtfDmxChannelSetPtr virtualChannelSet3;
		virtualFunction->CreateDmxChannelSet("My Name3", 4294967295, 4294967295, &virtualChannelSet3);


        __checkVCOM(gdtfWrite->Close());
    }
}

void GdtfDmxUnittest::ReadFile()
{
	//------------------------------------------------------------------------------------------------
	// Create Pointer to GDTF Interface
    IGdtfFixturePtr gdtfRead (IID_IGdtfFixture);
    if(__checkVCOM(gdtfRead->ReadFromFile(fPath.c_str())))
    {
		size_t bufferLength = 0;
		__checkVCOM(gdtfRead->GetBufferLength(bufferLength));

		char* buffer = new char[bufferLength + 1];
		__checkVCOM(gdtfRead->ToBuffer(buffer));
		delete[] buffer;

		//------------------------------------------------------------------------------
		// Read the linked GUID
		MvrUUID guid 		(0,0,0,0);
		MvrUUID emptyguid 	(0,0,0,0);

		__checkVCOM_NotSet(gdtfRead->GetLinkedFixtureGUID(guid));
		this->checkifEqual("Linked GDTF", guid, emptyguid);

		//------------------------------------------------------------------------------ 
		// Read the Attributes
		size_t countAttributes = 0;
		__checkVCOM(gdtfRead->GetAttributeCount(countAttributes));
		this->checkifEqual("Check Count Attributes ", countAttributes, size_t(6));

		// Check Attribute
		IGdtfAttributePtr	gdtfAttribute1;
		__checkVCOM(gdtfRead->GetAttributeAt(0, &gdtfAttribute1));
		this->checkifEqual("gdtfAttribute GetName() ", gdtfAttribute1->GetName(), "Attribute1");
		this->checkifEqual("gdtfAttribute GetName() ", gdtfAttribute1->GetPrettyName(), "Pretty");

		IGdtfAttributePtr	gdtfAttribute2;
		__checkVCOM(gdtfRead->GetAttributeAt(1, &gdtfAttribute2));
		this->checkifEqual("gdtfAttribute GetName() ", gdtfAttribute2->GetName(), "Attribute2");
		this->checkifEqual("gdtfAttribute GetName() ", gdtfAttribute2->GetPrettyName(), "Pretty");

		IGdtfAttributePtr	gdtfAttribute3;
		__checkVCOM(gdtfRead->GetAttributeAt(2, &gdtfAttribute3));
		this->checkifEqual("gdtfAttribute GetName() ", gdtfAttribute3->GetName(), "Attribute3");
		this->checkifEqual("gdtfAttribute GetName() ", gdtfAttribute3->GetPrettyName(), "Pretty");

		IGdtfAttributePtr	gdtfAttribute4;
		__checkVCOM(gdtfRead->GetAttributeAt(3, &gdtfAttribute4));
		this->checkifEqual("gdtfAttribute GetName() ", gdtfAttribute4->GetName(), "Attribute4");
		this->checkifEqual("gdtfAttribute GetName() ", gdtfAttribute4->GetPrettyName(), "Pretty");

		IGdtfAttributePtr	gdtfAttribute5;
		__checkVCOM(gdtfRead->GetAttributeAt(4, &gdtfAttribute5));
		this->checkifEqual("gdtfAttribute GetName() ", gdtfAttribute5->GetName(), "Attribute5");
		this->checkifEqual("gdtfAttribute GetName() ", gdtfAttribute5->GetPrettyName(), "Pretty");

		IGdtfAttributePtr	gdtfAttribute6;
		__checkVCOM(gdtfRead->GetAttributeAt(5, &gdtfAttribute6));
		this->checkifEqual("gdtfAttribute GetName() ", gdtfAttribute6->GetName(), "Attribute6");
		this->checkifEqual("gdtfAttribute GetName() ", gdtfAttribute6->GetPrettyName(), "Pretty");

		//------------------------------------------------------------------------------    
		// Extract Geometry & Models
		size_t countModels = 0;
		__checkVCOM(gdtfRead->GetModelCount(countModels));
		for (size_t i = 0; i < countModels; i++)
		{
			IGdtfModelPtr gdtfModel;
			if (__checkVCOM(gdtfRead->GetModelAt(i, &gdtfModel)))
			{
				MvrString  modelName = gdtfModel->GetName();
				MvrString geometryFile = gdtfModel->GetGeometryFileName();
				this->checkifEqual("gdtfModelGetName ", modelName, "Model");

				// Height
				double heightVal = 0.0;
				__checkVCOM(gdtfModel->GetHeight(heightVal));
				this->checkifEqual("gdtfModelGetHeight ", heightVal, double(0));

				// Width
				double widthVal = 0.0;
				__checkVCOM(gdtfModel->GetWidth(widthVal));
				this->checkifEqual("gdtfModelGetWidth ", widthVal, double(0));

				// Length
				double lengthVal = 0.0;
				__checkVCOM(gdtfModel->GetLength(lengthVal));
				this->checkifEqual("gdtfModelGetLength ", lengthVal, double(0));

				// PrimitiveType
				EGdtfModel_PrimitiveType primitiveType = EGdtfModel_PrimitiveType::eGdtfModel_PrimitiveType_Undefined;
				__checkVCOM(gdtfModel->GetPrimitiveType(primitiveType));
				this->checkifEqual("gdtfModelGetPrimitiveType ", primitiveType, EGdtfModel_PrimitiveType::eGdtfModel_PrimitiveType_Undefined);
			}
		} // Models loop


		//--------------------------------------------------------------------------------
		// Geometry Section
		size_t countGeo = 0;
		__checkVCOM(gdtfRead->GetGeometryCount(countGeo));
		this->checkifEqual("Geometry Count ", countGeo, size_t(2));

		IGdtfGeometryPtr gdtfGeometry;
		__checkVCOM(gdtfRead->GetGeometryAt(0, &gdtfGeometry));
		this->checkifEqual("GetGeometryAtGetName() ", gdtfGeometry->GetName(), "Geometry");

		IGdtfGeometryPtr possibleParentGeometry;
		__checkVCOM_NotSet(gdtfGeometry->GetParent( & possibleParentGeometry));
		
		IGdtfGeometryPtr childGeometry;
		__checkVCOM(gdtfGeometry->GetInternalGeometryAt(0, &childGeometry));
		__checkVCOM(childGeometry->GetParent( & possibleParentGeometry));

		this->checkifEqual("GeometryParent", gdtfGeometry->GetName(),possibleParentGeometry->GetName());


		//------------------------------------------------------------------
		// Get DMX Mode
		size_t countDmxModes;
		__checkVCOM(gdtfRead->GetDmxModeCount(countDmxModes));
		this->checkifEqual("Check Count DMX Modes", countDmxModes, size_t(1));

		IGdtfDmxModePtr mode;
		__checkVCOM(gdtfRead->GetDmxModeAt(0, &mode));
		
		this->checkifEqual("Check DMX Mode Description", mode->GetDescription(), "Mode Description");

		size_t countChannels = 0;
		__checkVCOM(mode->GetDmxChannelCount(countChannels));
		this->checkifEqual("Check Count DMX Channels", countChannels, size_t(5));

		size_t countBreaks = 0;
		__checkVCOM(mode->GetBreakCount(countBreaks));
		this->checkifEqual("Check Count DMX Breaks", countBreaks, size_t(2));

		size_t break2 = 0;
		__checkVCOM(mode->GetBreakAt(size_t(1), break2));
		this->checkifEqual("Check the second Break", break2, size_t(3));

		size_t footprint = 0;
		__checkVCOM(mode->GetFootprintForBreak(break2, footprint));
		this->checkifEqual("Check the footprint", footprint, size_t(19));
		

		//----------------------------------------------------------------
		// Check 8 bit Channel
		IGdtfDmxChannelPtr bit8channel;
		__checkVCOM(mode->GetDmxChannelAt(0, &bit8channel));
		Check8bitChannel(bit8channel);

		//----------------------------------------------------------------
		// Read 16 bit Channel
		IGdtfDmxChannelPtr bit16channel;
		__checkVCOM(mode->GetDmxChannelAt(1, &bit16channel));

		Sint32 dmxBreakChannel2 = 0;
		__checkVCOM(bit16channel->GetDmxBreak(dmxBreakChannel2));
		this->checkifEqual("Check DMX Break Channel 2 - Overwrite", dmxBreakChannel2, 0);

		DmxValue highlight16bit = 0;
		__checkVCOM(bit16channel->GetHighlight(highlight16bit));
		this->checkifEqual("Check DMX Break Channel 2 - Highlight", (DmxValue)256, highlight16bit);

		bool hasHighlight16bit = false;
		__checkVCOM(bit16channel->HasHighlight(hasHighlight16bit));
		this->checkifEqual("Check DMX Break Channel 2 - Highlight", true, hasHighlight16bit);

		IGdtfDmxLogicalChannelPtr bit16LogicalChannel;
		__checkVCOM(bit16channel->GetLogicalChannelAt(0, &bit16LogicalChannel));

		IGdtfDmxChannelFunctionPtr bit16Function;
		__checkVCOM(bit16LogicalChannel->GetDmxFunctionAt(0, &bit16Function));

		// Check DMX Channel Sets
		size_t countChannelSets = 0;
		__checkVCOM(bit16Function->GetDmxChannelSetCount(countChannelSets));
		this->checkifEqual("Check Count DMX Channels", countChannelSets, size_t(6));

		IGdtfDmxChannelSetPtr bit16ChannelSet1;
		__checkVCOM(bit16Function->GetDmxChannelSetAt(0, &bit16ChannelSet1)); 
		this->CheckChannelSet(bit16ChannelSet1, "",0,14);

		IGdtfDmxChannelSetPtr bit16ChannelSet2;
		__checkVCOM(bit16Function->GetDmxChannelSetAt(1, &bit16ChannelSet2));
		this->CheckChannelSet(bit16ChannelSet2, "My Name1",15,60);

		IGdtfDmxChannelSetPtr bit16ChannelSet3;
		__checkVCOM(bit16Function->GetDmxChannelSetAt(2, &bit16ChannelSet3));
		this->CheckChannelSet(bit16ChannelSet3, "My Name2",61,90);

		IGdtfDmxChannelSetPtr bit16ChannelSet4;
		__checkVCOM(bit16Function->GetDmxChannelSetAt(3, &bit16ChannelSet4));
		this->CheckChannelSet(bit16ChannelSet4, "",91,127);

		IGdtfDmxChannelSetPtr bit16ChannelSet5;
		__checkVCOM(bit16Function->GetDmxChannelSetAt(4, &bit16ChannelSet5));
		this->CheckChannelSet(bit16ChannelSet5, "My Name3",128,4501);

		IGdtfDmxChannelSetPtr bit16ChannelSet6;
		__checkVCOM(bit16Function->GetDmxChannelSetAt(5, &bit16ChannelSet6));
		this->CheckChannelSet(bit16ChannelSet6, "",4502,65535);


		// Check Mode Master Function here
		IGdtfDmxChannelPtr 			gdtfChannel;
		IGdtfDmxChannelFunctionPtr 	gdtfFunction;
		DmxValue					start;
		DmxValue					end;
		__checkVCOM(bit16Function->GetModeMasterFunction(&gdtfFunction, start, end));

		this->checkifEqual("Check ModeMaster Function Start ",start, (DmxValue)15);
		this->checkifEqual("Check ModeMaster Function End ",  end,   (DmxValue)78);

		__checkVCOM_NotSet(bit16Function->GetModeMasterChannel(&gdtfChannel, start, end));


		//----------------------------------------------------------------
		// Check 24 bit Channel
		IGdtfDmxChannelPtr bit24channel;
		__checkVCOM(mode->GetDmxChannelAt(2, &bit24channel));
		Check24bitChannel(bit24channel);

		//----------------------------------------------------------------
		// Read 8 bit Channel2
		IGdtfDmxChannelPtr bit8channel2;
		__checkVCOM(mode->GetDmxChannelAt(3, &bit8channel2));


		size_t countLogChannel = 0;
		__checkVCOM(bit8channel2->GetLogicalChannelCount(countLogChannel));
		this->checkifEqual("Count Logical Channels", countLogChannel, size_t(1));

		IGdtfDmxLogicalChannelPtr bit8_1LogicalChannel1;
		__checkVCOM(bit8channel2->GetLogicalChannelAt(0, &bit8_1LogicalChannel1));

		IGdtfDmxChannelFunctionPtr bit8_1Function;
		__checkVCOM(bit8_1LogicalChannel1->GetDmxFunctionAt(0, &bit8_1Function));

		// Check DMX Channel Sets
		__checkVCOM(bit8_1Function->GetDmxChannelSetCount(countChannelSets));
		this->checkifEqual("Check Count DMX Channels", countChannelSets, size_t(0));

		//----------------------------------------------------------------
		// Check Virtual Channel
		IGdtfDmxChannelPtr virtualChannel;
		__checkVCOM(mode->GetDmxChannelAt(4, &virtualChannel));

		IGdtfDmxLogicalChannelPtr virtualLogChannel;
		__checkVCOM(virtualChannel->GetLogicalChannelAt(0, &virtualLogChannel));

		IGdtfDmxChannelFunctionPtr virtualFunction;
		__checkVCOM(virtualLogChannel->GetDmxFunctionAt(0, &virtualFunction));

		DmxValue defaultValue = 0;
		__checkVCOM(virtualFunction->GetDefaultValue(defaultValue));
		this->checkifEqual("Default Virtual Channel Function", defaultValue, (DmxValue)50000);

		size_t countVirtualChannelSets = 0;
		__checkVCOM(virtualFunction->GetDmxChannelSetCount(countVirtualChannelSets));

		this->checkifEqual("countVirtualChannelSets ", size_t(3), countVirtualChannelSets);

		// Channel Sets
		IGdtfDmxChannelSetPtr virtualChannelSet1;
		__checkVCOM(virtualFunction->GetDmxChannelSetAt(0, &virtualChannelSet1));
		this->CheckChannelSet(virtualChannelSet1, "My Name1", 0, 0);


		IGdtfDmxChannelSetPtr virtualChannelSet2;
		__checkVCOM(virtualFunction->GetDmxChannelSetAt(1, &virtualChannelSet2));
		this->CheckChannelSet(virtualChannelSet2, "", 1, 4294967294);

		IGdtfDmxChannelSetPtr virtualChannelSet3;
		__checkVCOM(virtualFunction->GetDmxChannelSetAt(2, &virtualChannelSet3));
		this->CheckChannelSet(virtualChannelSet3, "My Name3", 4294967295, 4294967295);
	}

	PrintParsingErrorList(gdtfRead);
}



void GdtfDmxUnittest::Check8bitChannel(VectorworksMVR::IGdtfDmxChannelPtr& dmxChannel)
{
	// ---------------------------------------------------------------------------
	// Check DMXChannel attributes
	CheckDmxChannel(dmxChannel, 1, 1, 0, 0, 0, false, (double)0, (double)0, eGdtfChannelBitResolution_8);

	// ---------------------------------------------------------------------------
	// Get Logical Channels
	size_t count = 0;
	__checkVCOM(dmxChannel->GetLogicalChannelCount(count));
	this->checkifEqual("Count Logical Channels", count, size_t(2));

	IGdtfDmxLogicalChannelPtr bit8LogicalChannel1;
	__checkVCOM(dmxChannel->GetLogicalChannelAt(0, &bit8LogicalChannel1));

	IGdtfDmxLogicalChannelPtr bit8LogicalChannel2;
	__checkVCOM(dmxChannel->GetLogicalChannelAt(1, &bit8LogicalChannel2));

	// ---------------------------------------------------------------------------
	// Get Functions
	__checkVCOM(bit8LogicalChannel1->GetDmxFunctionCount(count));
	this->checkifEqual("Count Function Count", count, size_t(2));

	__checkVCOM(bit8LogicalChannel2->GetDmxFunctionCount(count));
	this->checkifEqual("Count Function Count", count, size_t(2));

	IGdtfDmxChannelFunctionPtr bit8Function1;
	__checkVCOM(bit8LogicalChannel1->GetDmxFunctionAt(0, &bit8Function1));
	CheckFunction(bit8Function1, "Function1", "Attribute1", (DmxValue)0, 0, 99, eGdtfChannelBitResolution_8);

	IGdtfDmxChannelFunctionPtr bit8Function2;
	__checkVCOM(bit8LogicalChannel1->GetDmxFunctionAt(1, &bit8Function2));
	CheckFunction(bit8Function2, "Function2", "Attribute1", (DmxValue)0, 100, 255, eGdtfChannelBitResolution_8);

	IGdtfDmxChannelFunctionPtr bit8Function3;
	__checkVCOM(bit8LogicalChannel2->GetDmxFunctionAt(0, &bit8Function3));
	CheckFunction(bit8Function3, "Function3", "Attribute1", (DmxValue)0, 0, 199, eGdtfChannelBitResolution_8);

	IGdtfDmxChannelFunctionPtr bit8Function4;
	__checkVCOM(bit8LogicalChannel2->GetDmxFunctionAt(1, &bit8Function4));
	CheckFunction(bit8Function4, "Function4", "Attribute1", (DmxValue)0, 200, 255, eGdtfChannelBitResolution_8);

	// ---------------------------------------------------------------------------
	// Check Channel Set Count bit8Function1
	__checkVCOM(bit8Function1->GetDmxChannelSetCount(count));
	this->checkifEqual("bit8Function1 Count Channel Set", count, size_t(5));

	IGdtfDmxChannelSetPtr bit8ChannelSet1;
	__checkVCOM(bit8Function1->GetDmxChannelSetAt(0, &bit8ChannelSet1));
	this->CheckChannelSet(bit8ChannelSet1, "",0,14);

	IGdtfDmxChannelSetPtr bit8ChannelSet2;
	__checkVCOM(bit8Function1->GetDmxChannelSetAt(1, &bit8ChannelSet2));
	this->CheckChannelSet(bit8ChannelSet2, "My Name1",15,60);

	IGdtfDmxChannelSetPtr bit8ChannelSet3;
	__checkVCOM(bit8Function1->GetDmxChannelSetAt(2, &bit8ChannelSet3));
	this->CheckChannelSet(bit8ChannelSet3, "My Name2",61,90);

	IGdtfDmxChannelSetPtr bit8ChannelSet4;
	__checkVCOM(bit8Function1->GetDmxChannelSetAt(3, &bit8ChannelSet4));
	this->CheckChannelSet(bit8ChannelSet4, "My Name3",91,92);

	IGdtfDmxChannelSetPtr bit8ChannelSet5;
	__checkVCOM(bit8Function1->GetDmxChannelSetAt(4, &bit8ChannelSet5));
	this->CheckChannelSet(bit8ChannelSet5, "",93,99);

	// ---------------------------------------------------------------------------
	// Check Sub Channel Set Count bit8Function1
	__checkVCOM(bit8Function1->GetDmxSubChannelSetCount(count));
	this->checkifEqual("bit8Function1 Count Sub Channel Set", count, size_t(2));

	IGdtfDmxSubChannelSetPtr subChannelSet1;
	__checkVCOM(bit8Function1->GetDmxSubChannelSetAt(0, &subChannelSet1));

	double physicalFrom = 0.0;
	__checkVCOM(subChannelSet1->GetPhysicalFrom(physicalFrom));
	this->checkifEqual("subChannelSet1 physicalFrom", physicalFrom, double(1.1));

	double physicalTo = 0.0;
	__checkVCOM(subChannelSet1->GetPhysicalTo(physicalTo));
	this->checkifEqual("subChannelSet1 physicalTo", physicalTo, double(1.2));

	IGdtfSubPhysicalUnitPtr subPhysicalUnit1;
	__checkVCOM(subChannelSet1->GetSubPhysicalUnit(&subPhysicalUnit1));

	EGdtfSubPhysicalUnitType subPhysicalUnit1unitType = EGdtfSubPhysicalUnitType::PlacementOffset;
	__checkVCOM(subPhysicalUnit1->GetType(subPhysicalUnit1unitType));
	this->checkifEqual("subChannelSet1 subPhysicalUnit1 Type", (size_t)subPhysicalUnit1unitType, size_t(EGdtfSubPhysicalUnitType::Duration));

	IGdtfDMXProfilePtr dmxProfile;
	__checkVCOM(subChannelSet1->GetDMXProfile(&dmxProfile));
	this->checkifEqual("subChannelSet1 dmxProfile", dmxProfile->GetName(), "DMXProfile 1");

	IGdtfDmxSubChannelSetPtr subChannelSet2;
	__checkVCOM(bit8Function1->GetDmxSubChannelSetAt(1, &subChannelSet2));

	__checkVCOM(subChannelSet2->GetPhysicalFrom(physicalFrom));
	this->checkifEqual("subChannelSet2 physicalFrom", physicalFrom, double(2.1));

	__checkVCOM(subChannelSet2->GetPhysicalTo(physicalTo));
	this->checkifEqual("subChannelSet2 physicalTo", physicalTo, double(2.2));

	IGdtfSubPhysicalUnitPtr subPhysicalUnit2;
	__checkVCOM(subChannelSet2->GetSubPhysicalUnit(&subPhysicalUnit2));

	EGdtfSubPhysicalUnitType subPhysicalUnit2unitType = EGdtfSubPhysicalUnitType::PlacementOffset;
	__checkVCOM(subPhysicalUnit2->GetType(subPhysicalUnit2unitType));
	this->checkifEqual("subChannelSet2 subPhysicalUnit2 Type", (size_t)subPhysicalUnit2unitType, size_t(EGdtfSubPhysicalUnitType::Amplitude));


	// ---------------------------------------------------------------------------
	// Check Channel Set Count bit8Function2
	__checkVCOM(bit8Function2->GetDmxChannelSetCount(count));
	this->checkifEqual("bit8Function2 Count Channel Set", count, size_t(5));

	IGdtfDmxChannelSetPtr bit8ChannelSet6;
	__checkVCOM(bit8Function2->GetDmxChannelSetAt(0, &bit8ChannelSet1));
	this->CheckChannelSet(bit8ChannelSet1, "My Name4",100,120);

	IGdtfDmxChannelSetPtr bit8ChannelSet7;
	__checkVCOM(bit8Function2->GetDmxChannelSetAt(1, &bit8ChannelSet2));
	this->CheckChannelSet(bit8ChannelSet2, "My Name5",121,130);

	IGdtfDmxChannelSetPtr bit8ChannelSet8;
	__checkVCOM(bit8Function2->GetDmxChannelSetAt(2, &bit8ChannelSet3));
	this->CheckChannelSet(bit8ChannelSet3, "",131,159);

	IGdtfDmxChannelSetPtr bit8ChannelSet9;
	__checkVCOM(bit8Function2->GetDmxChannelSetAt(3, &bit8ChannelSet4));
	this->CheckChannelSet(bit8ChannelSet4, "My Name6",160,165);

	IGdtfDmxChannelSetPtr bit8ChannelSet10;
	__checkVCOM(bit8Function2->GetDmxChannelSetAt(4, &bit8ChannelSet5));
	this->CheckChannelSet(bit8ChannelSet5, "",166,255);
	// ---------------------------------------------------------------------------
	// Check Channel Set Count bit8Function3
	__checkVCOM(bit8Function3->GetDmxChannelSetCount(count));
	this->checkifEqual("bit8Function3 Count Channel Set", count, size_t(6));

	IGdtfDmxChannelSetPtr bit8ChannelSet11;
	__checkVCOM(bit8Function3->GetDmxChannelSetAt(1, &bit8ChannelSet11));
	this->CheckChannelSet(bit8ChannelSet11, "My Name7",170,170);

	IGdtfDmxChannelSetPtr bit8ChannelSet12;
	__checkVCOM(bit8Function3->GetDmxChannelSetAt(2, &bit8ChannelSet12));
	this->CheckChannelSet(bit8ChannelSet12, "",171,179);

	IGdtfDmxChannelSetPtr bit8ChannelSet13;
	__checkVCOM(bit8Function3->GetDmxChannelSetAt(3, &bit8ChannelSet13));
	this->CheckChannelSet(bit8ChannelSet13, "My Name8",180,180);

	IGdtfDmxChannelSetPtr bit8ChannelSet14;
	__checkVCOM(bit8Function3->GetDmxChannelSetAt(4, &bit8ChannelSet14));
	this->CheckChannelSet(bit8ChannelSet14, "My Name9",181,198);

	IGdtfDmxChannelSetPtr bit8ChannelSet15;
	__checkVCOM(bit8Function3->GetDmxChannelSetAt(5, &bit8ChannelSet15));
	this->CheckChannelSet(bit8ChannelSet15, "",199,199);

	// ---------------------------------------------------------------------------
	// Check Channel Set Count bit8Function4
	__checkVCOM(bit8Function4->GetDmxChannelSetCount(count));
	this->checkifEqual("bit8Function4 Count Channel Set", count, size_t(6));

	IGdtfDmxChannelSetPtr bit8ChannelSet16;
	__checkVCOM(bit8Function4->GetDmxChannelSetAt(0, &bit8ChannelSet16));
	this->CheckChannelSet(bit8ChannelSet16, "",200,209);

	IGdtfDmxChannelSetPtr bit8ChannelSet17;
	__checkVCOM(bit8Function4->GetDmxChannelSetAt(1, &bit8ChannelSet17));
	this->CheckChannelSet(bit8ChannelSet17, "My Name10",210,210);

	IGdtfDmxChannelSetPtr bit8ChannelSet18;
	__checkVCOM(bit8Function4->GetDmxChannelSetAt(2, &bit8ChannelSet18));
	this->CheckChannelSet(bit8ChannelSet18, "",211,219);

	IGdtfDmxChannelSetPtr bit8ChannelSet19;
	__checkVCOM(bit8Function4->GetDmxChannelSetAt(3, &bit8ChannelSet19));
	this->CheckChannelSet(bit8ChannelSet19, "My Name11",220,225);

	IGdtfDmxChannelSetPtr bit8ChannelSet20;
	__checkVCOM(bit8Function4->GetDmxChannelSetAt(4, &bit8ChannelSet20));
	this->CheckChannelSet(bit8ChannelSet20, "",226,229);

	IGdtfDmxChannelSetPtr bit8ChannelSet21;
	__checkVCOM(bit8Function4->GetDmxChannelSetAt(5, &bit8ChannelSet21));
	this->CheckChannelSet(bit8ChannelSet21, "My Name12",230,255);

    //-----------------------------------------------------------------------------
    double thisDmxMibFade = 0;
	__checkVCOM(bit8LogicalChannel1->GetMoveInBlackFrames(thisDmxMibFade));
	this->checkifEqual("Check DmxChannel MibFade - Default: 0 ", (double)0, thisDmxMibFade);

	double thisDmxChangeTimeLimit = 0;
	__checkVCOM(bit8LogicalChannel1->GetDmxChangeTimeLimit(thisDmxChangeTimeLimit));
	this->checkifEqual("Check DmxChannel DMXChangeTimeLimit  - Default: 0 ", (double)0, thisDmxChangeTimeLimit);

}

void GdtfDmxUnittest::Check24bitChannel(VectorworksMVR::IGdtfDmxChannelPtr& dmxChannel)
{
	// ---------------------------------------------------------------------------
	// Get Logical Channels
	size_t count = 0;
	__checkVCOM(dmxChannel->GetLogicalChannelCount(count));
	this->checkifEqual("Count Logical Channels", count, size_t(1));

	IGdtfDmxLogicalChannelPtr logicalChannel;
	__checkVCOM(dmxChannel->GetLogicalChannelAt(0, &logicalChannel));

	// ---------------------------------------------------------------------------
	// Get Functions
	__checkVCOM(logicalChannel->GetDmxFunctionCount(count));
	this->checkifEqual("Count Function Count", count, size_t(3));

	GdtfDefines::DmxValue max24bit = (256*256*256) - 1;

	IGdtfDmxChannelFunctionPtr bit8Function1;
	__checkVCOM(logicalChannel->GetDmxFunctionAt(0, &bit8Function1));
	CheckFunction(bit8Function1, "Log 1", "Attribute1", (DmxValue)0, 0, max24bit, eGdtfChannelBitResolution_24);

	IGdtfDmxChannelFunctionPtr bit8Function2;
	__checkVCOM(logicalChannel->GetDmxFunctionAt(1, &bit8Function2));
	CheckFunction(bit8Function2, "Log 2", "Attribute1", (DmxValue)0, 0, max24bit, eGdtfChannelBitResolution_24);

	IGdtfDmxChannelFunctionPtr bit8Function3;
	__checkVCOM(logicalChannel->GetDmxFunctionAt(2, &bit8Function3));
	CheckFunction(bit8Function3, "Log 3", "Attribute1", (DmxValue)0, 0, max24bit, eGdtfChannelBitResolution_24);

	double thisDmxMibFade = 0;
	__checkVCOM(logicalChannel->GetMoveInBlackFrames(thisDmxMibFade));
	this->checkifEqual("Check DmxChannel MibFade - Default: 0 ", (double)0, thisDmxMibFade);

	double thisDmxChangeTimeLimit = 0;
	__checkVCOM(logicalChannel->GetDmxChangeTimeLimit(thisDmxChangeTimeLimit));
	this->checkifEqual("Check DmxChannel DMXChangeTimeLimit  - Default: 0 ", (double)0, thisDmxChangeTimeLimit);


	// Check ModeMaster
	IGdtfDmxChannelPtr 			gdtfChannel;
	IGdtfDmxChannelFunctionPtr 	gdtfFunction;
	DmxValue					start;
	DmxValue					end;

	__checkVCOM(bit8Function3->GetModeMasterChannel(&gdtfChannel, start, end));

	this->checkifEqual("Check ModeMaster Channel Start ",start, (DmxValue)80);
	this->checkifEqual("Check ModeMaster Channel End ",  end,   (DmxValue)179);

	__checkVCOM_NotSet(bit8Function3->GetModeMasterFunction(&gdtfFunction, start, end));

}

void GdtfDmxUnittest::CheckDmxChannel(VectorworksMVR::IGdtfDmxChannelPtr& dmxChannel, Sint32 dmxBreak, Sint32 coarse,
									  Sint32 fine, Sint32 ultra, Sint32 uber, DmxValue highlight,
									  double MibFade, double dmxChangeLimit, EGdtfChannelBitResolution resolution)
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

	Sint32 thisDmxUltra = 0;
	__checkVCOM(dmxChannel->GetUltra(thisDmxUltra));
	this->checkifEqual("Check DmxChannel Ultra - Default: \"None\" ", ultra, thisDmxUltra);

	Sint32 thisDmxUber = 0;
	__checkVCOM(dmxChannel->GetUber(thisDmxUber));
	this->checkifEqual("Check DmxChannel Uber - Default: \"None\"  ", uber, thisDmxUber);

	bool thisHasHighlight = 0;
	__checkVCOM(dmxChannel->HasHighlight(thisHasHighlight));
	if (thisHasHighlight)
	{
		DmxValue thisHighlight = 0;
		__checkVCOM(dmxChannel->GetHighlight(thisHighlight));
		this->checkifEqual("Check DmxChannel HighlightValue  - Default: \"None\"  ", highlight, thisHighlight);
	}

	EGdtfChannelBitResolution thisResolution;
	__checkVCOM(dmxChannel->GetResolution(thisResolution));
	this->checkifEqual("CheckResolution ",  (size_t)resolution, (size_t)thisResolution);

}

void GdtfDmxUnittest::CheckChannelSet(IGdtfDmxChannelSetPtr& channelSet, std::string name, DmxValue start, DmxValue end)
{
	if( ! channelSet) { this->checkifTrue("CheckChannelSet ok", channelSet != nullptr); return;}
	this->checkifEqual("CheckChannelSet Check Name ", name, channelSet->GetName());

	DmxValue thisStart = 0;
	__checkVCOM(channelSet->GetDmxStartAddress(thisStart));
	this->checkifEqual("CheckChannelSet Check Start " + name, start, thisStart);

	DmxValue thisEnd = 0;
	__checkVCOM(channelSet->GetDmxEndAddress(thisEnd));
	this->checkifEqual("CheckChannelSet Check End " + name,  end, thisEnd);
}

void GdtfDmxUnittest::CheckFunction(VectorworksMVR::IGdtfDmxChannelFunctionPtr& function, std::string name, std::string attributeName, DmxValue defaultValue, DmxValue start, DmxValue end, EGdtfChannelBitResolution resolution)
{
	this->checkifEqual("CheckFunction Check Name ", name, function->GetName());
	IGdtfAttributePtr gdtfAttribute;
	if (__checkVCOM(function->GetAttribute(&gdtfAttribute))) { this->checkifEqual("gdtfAttributeGetName ", attributeName, gdtfAttribute->GetName()); }

	DmxValue thisDmxDefaultValue = 0;
	__checkVCOM(function->GetDefaultValue(thisDmxDefaultValue));
	this->checkifEqual("CheckFunction DefaultValue - Default: 0/1 ", defaultValue, thisDmxDefaultValue);

	DmxValue thisStart = 0;
	__checkVCOM(function->GetStartAddress(thisStart));
	this->checkifEqual("CheckFunction Check Start " + name, start, thisStart);

	DmxValue thisEnd = 0;
	__checkVCOM(function->GetEndAddress(thisEnd));
	this->checkifEqual("CheckFunction Check End " + name,  end, thisEnd);


	EGdtfChannelBitResolution thisResolution;
	__checkVCOM(function->GetResolution(thisResolution));
	this->checkifEqual("CheckFunction CheckResolution ",  (size_t)resolution, (size_t)thisResolution);

}
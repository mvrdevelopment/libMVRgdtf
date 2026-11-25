//-----------------------------------------------------------------------------
//----- Copyright MVR Group
//-----------------------------------------------------------------------------
#include "Include/VectorworksMVR.h"
#include "WheelSlotIndexTest.h"
#include "Utility.h"

#include "Prefix/StdAfx.h"
#include "XmlFileHelper.h"


using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;


#define __checkVCOM(x) this->checkVCOM(x, #x)
#define __checkVCOM_NotSet(x) this->checkVCOM_NotSet(x, #x)

WheelSlotIndexTest::WheelSlotIndexTest(const std::string& currentDir) : GdtfUnitTest(currentDir)
{
    // Same path that GdtfUnitTest::ExecuteTest writes to
    fFilePath = currentDir + kSeparator + GetUnitTestName() + ".gdtf";
}

WheelSlotIndexTest::~WheelSlotIndexTest()
{
}

std::string WheelSlotIndexTest::GetUnitTestName()
{
    return std::string("WheelSlotIndexTest");
}

void WheelSlotIndexTest::WriteFile(IGdtfFixturePtr& fixture)
{
    IGdtfFeatureGroupPtr featureGroup;
    __checkVCOM(fixture->CreateFeatureGroup("Color", "Color", &featureGroup));

    IGdtfFeaturePtr feature;
    __checkVCOM(featureGroup->CreateFeature("Color", &feature));

    IGdtfAttributePtr attribute;
    __checkVCOM(fixture->CreateAttribute("Color1", "Color1", &attribute));
    __checkVCOM(attribute->SetFeature(feature));

    IGdtfWheelPtr wheel;
    __checkVCOM(fixture->CreateWheel("Wheel", &wheel));

    IGdtfWheelSlotPtr wheelSlot;
    __checkVCOM(wheel->CreateWheelSlot("Red", &wheelSlot));

    IGdtfModelPtr model;
    __checkVCOM(fixture->CreateModel("Model", &model));

    IGdtfGeometryPtr geometry;
    __checkVCOM(fixture->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "Geometry", model, STransformMatrix(), &geometry));

    IGdtfDmxModePtr mode;
    __checkVCOM(fixture->CreateDmxMode("Mode", &mode));
    __checkVCOM(mode->SetGeometry(geometry));

    IGdtfDmxChannelPtr channel;
    __checkVCOM(mode->CreateDmxChannel(geometry, &channel));
    __checkVCOM(channel->SetCoarse(1));

    IGdtfDmxLogicalChannelPtr logicalChannel;
    __checkVCOM(channel->CreateLogicalChannel(attribute, &logicalChannel));

    IGdtfDmxChannelFunctionPtr function;
    __checkVCOM(logicalChannel->CreateDmxFunction("Color1", &function));
    __checkVCOM(function->SetStartAddress(0));
    __checkVCOM(function->SetAttribute(attribute));
    __checkVCOM(function->SetOnWheel(wheel));

    // A channel set without a link to a wheel slot keeps the default index 0
    IGdtfDmxChannelSetPtr openSet;
    __checkVCOM(function->CreateDmxChannelSet("Open", 0, 9, &openSet));

    IGdtfDmxChannelSetPtr redSet;
    __checkVCOM(function->CreateDmxChannelSet("Red", 10, 255, &redSet));
    __checkVCOM(redSet->SetWheelSlot(1));
}

void WheelSlotIndexTest::ReadFile(IGdtfFixturePtr& fixture)
{
    IGdtfDmxModePtr mode;
    __checkVCOM(fixture->GetDmxModeAt(0, &mode));

    IGdtfDmxChannelPtr channel;
    __checkVCOM(mode->GetDmxChannelAt(0, &channel));

    IGdtfDmxLogicalChannelPtr logicalChannel;
    __checkVCOM(channel->GetLogicalChannelAt(0, &logicalChannel));

    IGdtfDmxChannelFunctionPtr function;
    __checkVCOM(logicalChannel->GetDmxFunctionAt(0, &function));

    size_t count = 0;
    __checkVCOM(function->GetDmxChannelSetCount(count));
    this->checkifEqual("Channel Set Count", count, size_t(2));

    CheckWheelSlot(function, 0, "Open", 0);
    CheckWheelSlot(function, 1, "Red",  1);

    CheckDescriptionXml();
}

void WheelSlotIndexTest::CheckWheelSlot(IGdtfDmxChannelFunctionPtr& function, size_t at, const std::string& name, Sint32 wheelSlot)
{
    IGdtfDmxChannelSetPtr channelSet;
    if( ! __checkVCOM(function->GetDmxChannelSetAt(at, &channelSet))) { return; }

    this->checkifEqual("Channel Set Name", name, channelSet->GetName());

    Sint32 thisWheelSlot = -1;
    __checkVCOM(channelSet->GetWheelSlot(thisWheelSlot));
    this->checkifEqual("Channel Set WheelSlot", thisWheelSlot, wheelSlot);
}

void WheelSlotIndexTest::CheckDescriptionXml()
{
    // WheelSlotIndex is optional in the GDTF spec, so it must only be written for the channel set that links to a wheel slot
    IFileIdentifierPtr file (IID_FileIdentifier);
    file->Set(TXString(fFilePath));

    IZIPFilePtr zipFile (IID_ZIPFile);
    if( ! __checkVCOM(zipFile->OpenRead(file))) { return; }

    SceneData::ISceneDataZipBuffer buffer;
    __checkVCOM(zipFile->GetFile("description.xml", &buffer));
    zipFile->Close();

    size_t size = 0;
    buffer.GetDataSize(size);

    std::string xml(size, '\0');
    if(size > 0) { buffer.CopyDataInto(&xml[0], size); }

    size_t occurrences = 0;
    for(size_t pos = xml.find("WheelSlotIndex"); pos != std::string::npos; pos = xml.find("WheelSlotIndex", pos + 1))
    {
        occurrences++;
    }

    this->checkifEqual("WheelSlotIndex count in description.xml", occurrences, size_t(1));
}

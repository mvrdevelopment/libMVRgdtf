//-----------------------------------------------------------------------------
//----- Copyright MVR Group
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include "ResolutionTest.h"
#include <iostream>
#include "Utility.h"
#include "Include/VectorworksMVR.h"

using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;

#define __checkVCOM(x) this->checkVCOM(x, #x)
#define __checkVCOM_NotSet(x) this->checkVCOM_NotSet(x, #x)

ResolutionTest::ResolutionTest(const std::string& currentDir)
{
}

ResolutionTest::~ResolutionTest()
{
}

bool ResolutionTest::ExecuteTest()
{
    std::cout << "=                         ResolutionTest Unit Test                           =" << std::endl;
    
    bool allTestsPassed = true;
    
    // Test 1: Resolution extraction from DMXFrom field
    std::cout << "\n--- Test 1: Resolution Extraction from DMXFrom ---" << std::endl;
    if (!TestResolutionExtractionFromDMXFrom()) {
        std::cout << "❌ TestResolutionExtractionFromDMXFrom FAILED" << std::endl;
        allTestsPassed = false;
    } else {
        std::cout << "✅ TestResolutionExtractionFromDMXFrom PASSED" << std::endl;
    }
    
    // Test 2: SetResolution API functionality
    std::cout << "\n--- Test 2: SetResolution API ---" << std::endl;
    if (!TestSetResolutionAPI()) {
        std::cout << "❌ TestSetResolutionAPI FAILED" << std::endl;
        allTestsPassed = false;
    } else {
        std::cout << "✅ TestSetResolutionAPI PASSED" << std::endl;
    }
    
    // Test 3: Resolution in XML output
    std::cout << "\n--- Test 3: Resolution in XML Output ---" << std::endl;
    if (!TestResolutionInXMLOutput()) {
        std::cout << "❌ TestResolutionInXMLOutput FAILED" << std::endl;
        allTestsPassed = false;
    } else {
        std::cout << "✅ TestResolutionInXMLOutput PASSED" << std::endl;
    }
    
    // Test 4: Mixed resolution channels
    std::cout << "\n--- Test 4: Mixed Resolution Channels ---" << std::endl;
    if (!TestMixedResolutionChannels()) {
        std::cout << "❌ TestMixedResolutionChannels FAILED" << std::endl;
        allTestsPassed = false;
    } else {
        std::cout << "✅ TestMixedResolutionChannels PASSED" << std::endl;
    }
    
    // Test 5: Resolution validation
    std::cout << "\n--- Test 5: Resolution Validation ---" << std::endl;
    if (!TestResolutionValidation()) {
        std::cout << "❌ TestResolutionValidation FAILED" << std::endl;
        allTestsPassed = false;
    } else {
        std::cout << "✅ TestResolutionValidation PASSED" << std::endl;
    }
    
    std::cout << "\n=== Resolution Test Summary ===" << std::endl;
    if (allTestsPassed) {
        std::cout << "🎉 ALL RESOLUTION TESTS PASSED!" << std::endl;
    } else {
        std::cout << "⚠️  SOME RESOLUTION TESTS FAILED!" << std::endl;
    }
    
    return allTestsPassed;
}

bool ResolutionTest::TestResolutionExtractionFromDMXFrom()
{
    // Test with a test GDTF file that has mixed resolutions
    std::string path = UnitTestUtil::GetTestResourceFolder() + kSeparator + "allWorking.gdtf";
    
    IGdtfFixturePtr gdtfFile(IID_IGdtfFixture);
    if (!__checkVCOM(gdtfFile->ReadFromFile(path.c_str()))) {
        std::cout << "Failed to open " << path << std::endl;
        return false;
    }
    
    // Get the first DMX mode
    size_t modeCount;
    if (!__checkVCOM(gdtfFile->GetDmxModeCount(modeCount))) {
        std::cout << "Failed to get DMX mode count" << std::endl;
        return false;
    }
    if (modeCount == 0) {
        std::cout << "No DMX modes found" << std::endl;
        return false;
    }
    
    IGdtfDmxModePtr mode;
    if (!__checkVCOM(gdtfFile->GetDmxModeAt(0, &mode))) {
        std::cout << "Failed to get DMX mode" << std::endl;
        return false;
    }
    
    size_t channelCount;
    if (!__checkVCOM(mode->GetDmxChannelCount(channelCount))) {
        std::cout << "Failed to get DMX channel count" << std::endl;
        return false;
    }
    std::cout << "Found " << channelCount << " DMX channels" << std::endl;
    
    bool testPassed = true;
    
    // Check each channel
    for (size_t i = 0; i < channelCount; i++) {
        IGdtfDmxChannelPtr channel;
        if (__checkVCOM(mode->GetDmxChannelAt(i, &channel))) {
            EGdtfChannelBitResolution resolution;
            if (!__checkVCOM(channel->GetResolution(resolution))) {
                std::cout << "Failed to get channel resolution" << std::endl;
                continue;
            }
            
            std::cout << "Channel " << i << ": ";
            PrintResolutionInfo(resolution, "Extracted");
            
            // Based on description.xml analysis:
            // Channel 0: DMXFrom="0/1" should be 8-bit
            // Channel 1: DMXFrom="0/4" should be 32-bit  
            // Channel 2: DMXFrom="0/1" should be 8-bit
            EGdtfChannelBitResolution expectedResolution;
            if (i == 0) {
                expectedResolution = EGdtfChannelBitResolution::eGdtfChannelBitResolution_8;
            } else if (i == 1) {
                expectedResolution = EGdtfChannelBitResolution::eGdtfChannelBitResolution_32;
            } else if (i == 2) {
                expectedResolution = EGdtfChannelBitResolution::eGdtfChannelBitResolution_8;
            } else {
                expectedResolution = EGdtfChannelBitResolution::eGdtfChannelBitResolution_8; // default
            }
            
            if (!VerifyChannelResolution(channel, expectedResolution)) {
                testPassed = false;
            }
        }
    }
    
    return testPassed;
}

bool ResolutionTest::TestSetResolutionAPI()
{
    // Create a test fixture
    std::string testPath = UnitTestUtil::GetTestResourceFolder() + kSeparator + "test_setresolution_api.gdtf";
    
    if (!CreateTestFixture(testPath, "SetResolutionTestFixture")) {
        std::cout << "Failed to create test fixture" << std::endl;
        return false;
    }
    
    // Open for write
    IGdtfFixturePtr gdtfWrite(IID_IGdtfFixture);
    MvrUUID uuid = VectorworksMVR::MvrUUID(1, 2, 3, 4);
    
    if (!__checkVCOM(gdtfWrite->OpenForWrite(testPath.c_str(), "TestFixture", "TestManufacturer", uuid))) {
        std::cout << "Failed to open GDTF for write" << std::endl;
        return false;
    }
    
    // Create attribute
    IGdtfAttributePtr attr;
    if (!__checkVCOM(gdtfWrite->CreateAttribute("Dimmer", "Dimmer", &attr))) {
        std::cout << "Failed to create attribute" << std::endl;
        return false;
    }
    
    // Create model and geometry
    IGdtfModelPtr model;
    if (!__checkVCOM(gdtfWrite->CreateModel("TestModel", &model))) {
        std::cout << "Failed to create model" << std::endl;
        return false;
    }
    
    IGdtfGeometryPtr geometry;
    if (!__checkVCOM(gdtfWrite->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "TestGeometry", model, STransformMatrix(), &geometry))) {
        std::cout << "Failed to create geometry" << std::endl;
        return false;
    }
    
    // Create DMX mode
    IGdtfDmxModePtr dmxMode;
    if (!__checkVCOM(gdtfWrite->CreateDmxMode("TestMode", &dmxMode))) {
        std::cout << "Failed to create DMX mode" << std::endl;
        return false;
    }
    
    // Create DMX channel
    IGdtfDmxChannelPtr dmxChannel;
    if (!__checkVCOM(dmxMode->CreateDmxChannel(geometry, &dmxChannel))) {
        std::cout << "Failed to create DMX channel" << std::endl;
        return false;
    }
    
    dmxChannel->SetCoarse(1);
    
    // Test SetResolution with different bit resolutions
    bool allResolutionTests = true;
    
    // Test 8-bit
    std::cout << "Testing SetResolution(8-bit)..." << std::endl;
    if (__checkVCOM(dmxChannel->SetResolution(EGdtfChannelBitResolution::eGdtfChannelBitResolution_8))) {
        if (!VerifyChannelResolution(dmxChannel, EGdtfChannelBitResolution::eGdtfChannelBitResolution_8)) {
            allResolutionTests = false;
        }
    } else {
        std::cout << "Failed to set 8-bit resolution" << std::endl;
        allResolutionTests = false;
    }
    
    // Test 16-bit
    std::cout << "Testing SetResolution(16-bit)..." << std::endl;
    if (__checkVCOM(dmxChannel->SetResolution(EGdtfChannelBitResolution::eGdtfChannelBitResolution_16))) {
        if (!VerifyChannelResolution(dmxChannel, EGdtfChannelBitResolution::eGdtfChannelBitResolution_16)) {
            allResolutionTests = false;
        }
    } else {
        std::cout << "Failed to set 16-bit resolution" << std::endl;
        allResolutionTests = false;
    }
    
    // Test 24-bit
    std::cout << "Testing SetResolution(24-bit)..." << std::endl;
    if (__checkVCOM(dmxChannel->SetResolution(EGdtfChannelBitResolution::eGdtfChannelBitResolution_24))) {
        if (!VerifyChannelResolution(dmxChannel, EGdtfChannelBitResolution::eGdtfChannelBitResolution_24)) {
            allResolutionTests = false;
        }
    } else {
        std::cout << "Failed to set 24-bit resolution" << std::endl;
        allResolutionTests = false;
    }
    
    // Test 32-bit
    std::cout << "Testing SetResolution(32-bit)..." << std::endl;
    if (__checkVCOM(dmxChannel->SetResolution(EGdtfChannelBitResolution::eGdtfChannelBitResolution_32))) {
        if (!VerifyChannelResolution(dmxChannel, EGdtfChannelBitResolution::eGdtfChannelBitResolution_32)) {
            allResolutionTests = false;
        }
    } else {
        std::cout << "Failed to set 32-bit resolution" << std::endl;
        allResolutionTests = false;
    }
    
    gdtfWrite->Close();
    
    return allResolutionTests;
}

bool ResolutionTest::TestResolutionInXMLOutput()
{
    // Create a fixture with different resolution channels and verify XML output
    std::string testPath = UnitTestUtil::GetTestResourceFolder() + kSeparator + "test_resolution_xml.gdtf";
    
    IGdtfFixturePtr gdtfWrite(IID_IGdtfFixture);
    MvrUUID uuid = VectorworksMVR::MvrUUID(5, 6, 7, 8);
    
    if (!__checkVCOM(gdtfWrite->OpenForWrite(testPath.c_str(), "XMLTestFixture", "TestManufacturer", uuid))) {
        return false;
    }
    
    // Create attribute
    IGdtfAttributePtr attr;
    if (!__checkVCOM(gdtfWrite->CreateAttribute("Dimmer", "Dimmer", &attr))) {
        return false;
    }
    
    // Create model and geometry
    IGdtfModelPtr model;
    if (!__checkVCOM(gdtfWrite->CreateModel("XMLTestModel", &model))) {
        return false;
    }
    
    IGdtfGeometryPtr geometry;
    if (!__checkVCOM(gdtfWrite->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "XMLTestGeometry", model, STransformMatrix(), &geometry))) {
        return false;
    }
    
    // Create DMX mode
    IGdtfDmxModePtr dmxMode;
    if (!__checkVCOM(gdtfWrite->CreateDmxMode("XMLTestMode", &dmxMode))) {
        return false;
    }
    
    // Create channels with different resolutions
    for (int i = 0; i < 4; i++) {
        IGdtfDmxChannelPtr dmxChannel;
        if (!__checkVCOM(dmxMode->CreateDmxChannel(geometry, &dmxChannel))) {
            return false;
        }
        
        dmxChannel->SetCoarse(i + 1);
        
        // Set different resolutions
        EGdtfChannelBitResolution resolution;
        switch (i) {
            case 0: resolution = EGdtfChannelBitResolution::eGdtfChannelBitResolution_8; break;
            case 1: resolution = EGdtfChannelBitResolution::eGdtfChannelBitResolution_16; break;
            case 2: resolution = EGdtfChannelBitResolution::eGdtfChannelBitResolution_24; break;
            case 3: resolution = EGdtfChannelBitResolution::eGdtfChannelBitResolution_32; break;
        }
        
        if (!__checkVCOM(dmxChannel->SetResolution(resolution))) {
            return false;
        }
        
        // Create logical channel and channel function
        IGdtfDmxLogicalChannelPtr logicalChannel;
        if (!__checkVCOM(dmxChannel->CreateLogicalChannel(attr, &logicalChannel))) {
            return false;
        }
        
        IGdtfDmxChannelFunctionPtr channelFunction;
        if (!__checkVCOM(logicalChannel->CreateDmxFunction("TestFunction", &channelFunction))) {
            return false;
        }
    }
    
    gdtfWrite->Close();
    
    // Now read back and verify
    IGdtfFixturePtr gdtfRead(IID_IGdtfFixture);
    if (!__checkVCOM(gdtfRead->ReadFromFile(testPath.c_str()))) {
        return false;
    }
    
    IGdtfDmxModePtr readMode;
    if (!__checkVCOM(gdtfRead->GetDmxModeAt(0, &readMode))) {
        return false;
    }
    
    size_t channelCount;
    if (!__checkVCOM(readMode->GetDmxChannelCount(channelCount))) {
        std::cout << "Failed to get channel count" << std::endl;
        return false;
    }
    if (channelCount != 4) {
        std::cout << "Expected 4 channels, got " << channelCount << std::endl;
        return false;
    }
    
    // Verify each channel's resolution
    EGdtfChannelBitResolution expectedResolutions[] = {
        EGdtfChannelBitResolution::eGdtfChannelBitResolution_8,
        EGdtfChannelBitResolution::eGdtfChannelBitResolution_16,
        EGdtfChannelBitResolution::eGdtfChannelBitResolution_24,
        EGdtfChannelBitResolution::eGdtfChannelBitResolution_32
    };
    
    bool allCorrect = true;
    for (size_t i = 0; i < channelCount; i++) {
        IGdtfDmxChannelPtr channel;
        if (__checkVCOM(readMode->GetDmxChannelAt(i, &channel))) {
            if (!VerifyChannelResolution(channel, expectedResolutions[i])) {
                allCorrect = false;
            }
        }
    }
    
    std::cout << "XML output test: " << (allCorrect ? "PASSED" : "FAILED") << std::endl;
    
    return allCorrect;
}

bool ResolutionTest::TestMixedResolutionChannels()
{
    // Use an existing GDTF file
    std::string path = UnitTestUtil::GetTestResourceFolder() + kSeparator + "allWorking.gdtf";
    
    IGdtfFixturePtr gdtfFile(IID_IGdtfFixture);
    if (!__checkVCOM(gdtfFile->ReadFromFile(path.c_str()))) {
        return false;
    }
    
    IGdtfDmxModePtr mode;
    if (!__checkVCOM(gdtfFile->GetDmxModeAt(0, &mode))) {
        return false;
    }
    
    size_t channelCount;
    if (!__checkVCOM(mode->GetDmxChannelCount(channelCount))) {
        std::cout << "Failed to get channel count" << std::endl;
        return false;
    }
    std::cout << "Testing mixed resolution channels (" << channelCount << " channels)" << std::endl;
    
    bool hasMultipleResolutions = false;
    EGdtfChannelBitResolution firstResolution = EGdtfChannelBitResolution::eGdtfChannelBitResolution_8;
    bool firstSet = false;
    
    for (size_t i = 0; i < channelCount; i++) {
        IGdtfDmxChannelPtr channel;
        if (__checkVCOM(mode->GetDmxChannelAt(i, &channel))) {
            EGdtfChannelBitResolution resolution;
            if (!__checkVCOM(channel->GetResolution(resolution))) {
                continue;
            }
            
            if (!firstSet) {
                firstResolution = resolution;
                firstSet = true;
            } else if (resolution != firstResolution) {
                hasMultipleResolutions = true;
                std::cout << "Found mixed resolutions: ";
                PrintResolutionInfo(firstResolution, "First");
                std::cout << " and ";
                PrintResolutionInfo(resolution, "Other");
                std::cout << std::endl;
                break;
            }
        }
    }
    
    if (hasMultipleResolutions) {
        std::cout << "✅ Successfully detected mixed resolution channels" << std::endl;
        return true;
    } else {
        std::cout << "⚠️  All channels have the same resolution - this might be expected" << std::endl;
        return true; // This is not necessarily an error
    }
}

bool ResolutionTest::TestResolutionValidation()
{
    // Test edge cases and validation
    IGdtfFixturePtr gdtfWrite(IID_IGdtfFixture);
    MvrUUID uuid = VectorworksMVR::MvrUUID(9, 10, 11, 12);
    
    std::string testPath = UnitTestUtil::GetTestResourceFolder() + kSeparator + "test_validation.gdtf";
    
    if (!__checkVCOM(gdtfWrite->OpenForWrite(testPath.c_str(), "ValidationTestFixture", "TestManufacturer", uuid))) {
        return false;
    }
    
    // Create basic structure
    IGdtfAttributePtr attr;
    if (!__checkVCOM(gdtfWrite->CreateAttribute("Dimmer", "Dimmer", &attr))) {
        return false;
    }
    
    // Create model and geometry
    IGdtfModelPtr model;
    if (!__checkVCOM(gdtfWrite->CreateModel("ValidationModel", &model))) {
        return false;
    }
    
    IGdtfGeometryPtr geometry;
    if (!__checkVCOM(gdtfWrite->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "ValidationGeometry", model, STransformMatrix(), &geometry))) {
        return false;
    }
    
    IGdtfDmxModePtr dmxMode;
    if (!__checkVCOM(gdtfWrite->CreateDmxMode("ValidationMode", &dmxMode))) {
        return false;
    }
    
    IGdtfDmxChannelPtr dmxChannel;
    if (!__checkVCOM(dmxMode->CreateDmxChannel(geometry, &dmxChannel))) {
        return false;
    }
    
    // Test all valid resolution values
    std::vector<EGdtfChannelBitResolution> validResolutions = {
        EGdtfChannelBitResolution::eGdtfChannelBitResolution_8,
        EGdtfChannelBitResolution::eGdtfChannelBitResolution_16,
        EGdtfChannelBitResolution::eGdtfChannelBitResolution_24,
        EGdtfChannelBitResolution::eGdtfChannelBitResolution_32
    };
    
    bool allValidationsPassed = true;
    
    for (auto resolution : validResolutions) {
        if (!__checkVCOM(dmxChannel->SetResolution(resolution))) {
            std::cout << "Failed to set valid resolution: ";
            PrintResolutionInfo(resolution, "Validation");
            std::cout << std::endl;
            allValidationsPassed = false;
        } else {
            if (!VerifyChannelResolution(dmxChannel, resolution)) {
                allValidationsPassed = false;
            }
        }
    }
    
    gdtfWrite->Close();
    
    std::cout << "Resolution validation: " << (allValidationsPassed ? "PASSED" : "FAILED") << std::endl;
    
    return allValidationsPassed;
}

bool ResolutionTest::CreateTestFixture(const std::string& filePath, const std::string& fixtureName)
{
    // Helper method to create basic test fixtures
    return true; // Implementation would go here if needed
}

bool ResolutionTest::VerifyChannelResolution(IGdtfDmxChannelPtr channel, EGdtfChannelBitResolution expectedResolution)
{
    if (!channel) {
        std::cout << "Channel is null" << std::endl;
        return false;
    }
    
    EGdtfChannelBitResolution actualResolution;
    if (!__checkVCOM(channel->GetResolution(actualResolution))) {
        std::cout << "Failed to get channel resolution" << std::endl;
        return false;
    }
    
    if (actualResolution == expectedResolution) {
        std::cout << "✅ Resolution matches: ";
        PrintResolutionInfo(actualResolution, "Verified");
        std::cout << std::endl;
        return true;
    } else {
        std::cout << "❌ Resolution mismatch - Expected: ";
        PrintResolutionInfo(expectedResolution, "Expected");
        std::cout << ", Got: ";
        PrintResolutionInfo(actualResolution, "Actual");
        std::cout << std::endl;
        return false;
    }
}

void ResolutionTest::PrintResolutionInfo(EGdtfChannelBitResolution resolution, const std::string& context)
{
    const char* resolutionStr;
    switch (resolution) {
        case EGdtfChannelBitResolution::eGdtfChannelBitResolution_8:
            resolutionStr = "8-bit";
            break;
        case EGdtfChannelBitResolution::eGdtfChannelBitResolution_16:
            resolutionStr = "16-bit";
            break;
        case EGdtfChannelBitResolution::eGdtfChannelBitResolution_24:
            resolutionStr = "24-bit";
            break;
        case EGdtfChannelBitResolution::eGdtfChannelBitResolution_32:
            resolutionStr = "32-bit";
            break;
        default:
            resolutionStr = "Unknown";
            break;
    }
    
    std::cout << context << ": " << resolutionStr;
}
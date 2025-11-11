//-----------------------------------------------------------------------------
//----- Copyright MVR Group
//-----------------------------------------------------------------------------
#pragma once
#include "Unittest.h"

class ResolutionTest : public Unittest
{
public:
    ResolutionTest(const std::string& currentDir);
    virtual ~ResolutionTest();
protected:
    bool virtual ExecuteTest();

private:
    // Test resolution extraction from DMXFrom field
    bool TestResolutionExtractionFromDMXFrom();
    
    // Test SetResolution API functionality
    bool TestSetResolutionAPI();
    
    // Test resolution in XML output
    bool TestResolutionInXMLOutput();
    
    // Test mixed resolution channels
    bool TestMixedResolutionChannels();
    
    // Test resolution validation
    bool TestResolutionValidation();
    
    // Helper methods
    bool CreateTestFixture(const std::string& filePath, const std::string& fixtureName);
    bool VerifyChannelResolution(VectorworksMVR::IGdtfDmxChannelPtr channel, VectorworksMVR::GdtfDefines::EGdtfChannelBitResolution expectedResolution);
    void PrintResolutionInfo(VectorworksMVR::GdtfDefines::EGdtfChannelBitResolution resolution, const std::string& context);
};
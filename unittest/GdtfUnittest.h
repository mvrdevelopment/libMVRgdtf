//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "Unittest.h"

class GdtfUnittest : public Unittest
{
public:
    GdtfUnittest(const std::string& currentDir);
    virtual ~GdtfUnittest();
protected:
    bool virtual ExecuteTest();

private:
    std::string fAppDataFolder;
    std::string fTestGdtf_Path;
    std::string fTestResourcesFolder;    

    void        WriteFile();
    void        ReadFile();
    
    // Test Resources
    std::string GetTestPNG_ThumbNail(bool readLocation = false);
    std::string GetTestSVG_ThumbNail(bool readLocation = false);
    std::string GetTestSVG_Model(bool readLocation = false);
    std::string GetTestSVGSide_Model(bool readLocation = false);
    std::string GetTestSVGFront_Model(bool readLocation = false);
    std::string GetTest3DS_Model(bool readLocation = false);
    std::string GetTest3DSLow_Model(bool readLocation = false);
    std::string GetTest3DSHigh_Model(bool readLocation = false);
    std::string GetTestGLTF_Model_glb(bool readLocation = false);
    std::string GetTestGLTFLow_Model_glb(bool readLocation = false);
    std::string GetTestGLTFHigh_Model_glb(bool readLocation = false);
    std::string GetTestGLTF_Model(bool readLocation = false);
    std::string GetTestWheel_PNG(bool readLocation = false);

    void CheckAttibute(VectorworksMVR::IGdtfAttributePtr attribute, bool hasColor);
    void CheckAttachedFiles(VectorworksMVR::IGdtfFixturePtr fixture, size_t at, std::string inFile);
};
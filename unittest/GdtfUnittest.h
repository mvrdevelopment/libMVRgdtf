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
    std::string GetTestPNG_ThumbNail();
    std::string GetTestSVG_ThumbNail();
    std::string GetTestSVG_Model();
    std::string GetTest3DS_Model();
    std::string GetTestWheel_PNG();
};
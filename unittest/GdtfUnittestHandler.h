
//-----------------------------------------------------------------------------
//----- Copyright MVR Group
//-----------------------------------------------------------------------------
#pragma once
#include "Unittest.h"

class GdtfUnitTest : public Unittest
{
public:
    GdtfUnitTest(const std::string& currentDir);
    virtual ~GdtfUnitTest();
protected:
    bool                ExecuteTest();
    std::string virtual GetUnitTestName() = 0;

private:
    void virtual WriteFile(VectorworksMVR::IGdtfFixturePtr& fixtureDuringRead) = 0;
    void virtual ReadFile(VectorworksMVR::IGdtfFixturePtr& fixtureDuringWrite) = 0;


    std::string  fPath;

};
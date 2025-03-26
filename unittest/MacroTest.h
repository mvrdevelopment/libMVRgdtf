
//-----------------------------------------------------------------------------
//----- Copyright MVR Group
//-----------------------------------------------------------------------------
#pragma once
#include "Unittest.h"
#include "GdtfUnittestHandler.h"


class GdtfMacroTest : public GdtfUnitTest
{
public:
    GdtfMacroTest(const std::string& currentDir);
    virtual ~GdtfMacroTest();
protected:
    std::string virtual GetUnitTestName() override;

private:
    void virtual WriteFile(VectorworksMVR::IGdtfFixturePtr& fixtureDuringRead) override;
    void virtual ReadFile(VectorworksMVR::IGdtfFixturePtr& fixtureDuringWrite) override;
};
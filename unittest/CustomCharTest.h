
//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "Unittest.h"
#include "GdtfUnittestHandler.h"


class GdtfCustomCharTest : public GdtfUnitTest
{
public:
    GdtfCustomCharTest(const std::string& currentDir);
    virtual ~GdtfCustomCharTest();
protected:
    std::string virtual GetUnitTestName() override;

private:
    void virtual WriteFile(VectorworksMVR::IGdtfFixturePtr& fixtureDuringRead) override;
    void virtual ReadFile(VectorworksMVR::IGdtfFixturePtr& fixtureDuringWrite) override;

};
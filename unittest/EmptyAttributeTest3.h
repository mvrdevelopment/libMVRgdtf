
//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "Unittest.h"
#include "GdtfUnittestHandler.h"


class EmptyAttributeTest3 : public GdtfUnitTest
{
public:
    EmptyAttributeTest3(const std::string& currentDir);
    virtual ~EmptyAttributeTest3();
protected:
    std::string virtual GetUnitTestName() override;

private:
    void virtual WriteFile(VectorworksMVR::IGdtfFixturePtr& fixtureDuringRead) override;
    void virtual ReadFile(VectorworksMVR::IGdtfFixturePtr& fixtureDuringWrite) override;

    void TestFunction(VectorworksMVR::IGdtfDmxChannelFunctionPtr& function);


};
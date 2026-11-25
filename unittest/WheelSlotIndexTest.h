//-----------------------------------------------------------------------------
//----- Copyright MVR Group
//-----------------------------------------------------------------------------
#pragma once
#include "Unittest.h"
#include "GdtfUnittestHandler.h"


class WheelSlotIndexTest : public GdtfUnitTest
{
public:
    WheelSlotIndexTest(const std::string& currentDir);
    virtual ~WheelSlotIndexTest();
protected:
    std::string virtual GetUnitTestName() override;

private:
    void virtual WriteFile(VectorworksMVR::IGdtfFixturePtr& fixture) override;
    void virtual ReadFile(VectorworksMVR::IGdtfFixturePtr& fixture) override;

    void CheckWheelSlot(VectorworksMVR::IGdtfDmxChannelFunctionPtr& function, size_t at, const std::string& name, Sint32 wheelSlot);
    void CheckDescriptionXml();

    std::string fFilePath;
};

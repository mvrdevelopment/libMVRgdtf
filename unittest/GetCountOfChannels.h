
//-----------------------------------------------------------------------------
//----- Copyright MVR Group
//-----------------------------------------------------------------------------
#pragma once
#include "Unittest.h"
#include "GdtfUnittestHandler.h"


class GdtfGetCountOfLinkedChannelsForGeometry : public GdtfUnitTest
{
public:
    GdtfGetCountOfLinkedChannelsForGeometry(const std::string& currentDir);
    virtual ~GdtfGetCountOfLinkedChannelsForGeometry();
protected:
    std::string virtual GetUnitTestName() override;

private:
    void virtual WriteFile(VectorworksMVR::IGdtfFixturePtr& fixtureDuringRead) override;
    void virtual ReadFile(VectorworksMVR::IGdtfFixturePtr& fixtureDuringWrite) override;

};
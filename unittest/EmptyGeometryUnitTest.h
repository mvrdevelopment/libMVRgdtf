
//-----------------------------------------------------------------------------
//----- Copyright MVR Group
//-----------------------------------------------------------------------------
#pragma once
#include "Unittest.h"
#include "GdtfUnittestHandler.h"


class GdtfEmptyModelTest : public Unittest
{
public:
    GdtfEmptyModelTest(const std::string& currentDir);
    virtual ~GdtfEmptyModelTest();
protected:
    bool virtual ExecuteTest();

private:
    void WriteFile(VectorworksMVR::IGdtfFixturePtr& fixtureDuringRead);
    void ReadFile(VectorworksMVR::IGdtfFixturePtr& fixtureDuringWrite);

};
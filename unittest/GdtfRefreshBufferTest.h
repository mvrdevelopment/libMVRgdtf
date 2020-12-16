//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "Unittest.h"

class GdtfRefreshBufferTest : public Unittest
{
public:
    GdtfRefreshBufferTest(const std::string& currentDir);
    virtual ~GdtfRefreshBufferTest();
protected:
    bool virtual ExecuteTest();

private:
    void WriteFile();
    void ReadFile();

    std::string fPath;
    std::string fExistingPath;
    std::string fMvrPath;

    void CheckDmxChannel(VectorworksMVR::IGdtfDmxChannelPtr& dmxChannel, Sint32 dmxBreak, Sint32 coarse, Sint32 fine);
    void AddMode(VectorworksMVR::IGdtfFixturePtr gdtfWrite);
};
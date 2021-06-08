//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "Unittest.h"

class GdtfVirtualChannelTest : public Unittest
{
public:
    GdtfVirtualChannelTest(const std::string& currentDir);
    virtual ~GdtfVirtualChannelTest();
protected:
    bool virtual ExecuteTest();

private:
    void ReadFile();

    std::string fPath;


};
//-----------------------------------------------------------------------------
//----- Copyright MVR Group
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
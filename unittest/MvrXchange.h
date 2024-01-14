//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "Unittest.h"

class MvrXChangeUnitTest : public Unittest
{
public:
    MvrXChangeUnitTest(const std::string& currentDir);
    virtual ~MvrXChangeUnitTest();
protected:
    bool virtual ExecuteTest();

private:
};
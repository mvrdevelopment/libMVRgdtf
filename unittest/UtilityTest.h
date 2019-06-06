//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "Unittest.h"

class UtilityTest : public Unittest
{
public:
    UtilityTest(const std::string& currentDir);
    virtual ~UtilityTest();
protected:
    bool virtual ExecuteTest();
};
//-----------------------------------------------------------------------------
//----- Copyright MVR Group
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
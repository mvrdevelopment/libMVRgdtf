//-----------------------------------------------------------------------------
//----- Copyright MVR Group
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
//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "Unittest.h"

class MvrUnittest : public Unittest
{
public:
    MvrUnittest();
    virtual ~MvrUnittest();
protected:
    bool virtual ExecuteTest();

private:
    void WriteFile();
    void ReadFile();
};
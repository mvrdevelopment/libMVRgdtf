//-----------------------------------------------------------------------------
//----- Copyright MVR Group
//-----------------------------------------------------------------------------
#pragma once
#include "Unittest.h"

class GdtfBufferTest : public Unittest
{
public:
    GdtfBufferTest(const std::string& currentDir);
    virtual ~GdtfBufferTest();
protected:
    bool virtual ExecuteTest();

};
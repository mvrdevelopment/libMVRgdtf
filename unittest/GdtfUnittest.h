//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "Unittest.h"

class GdtfUnittest : public Unittest
{
public:
    GdtfUnittest(const std::string& currentDir);
    virtual ~GdtfUnittest();
protected:
    bool virtual ExecuteTest();

private:
    void WriteFile();
    void ReadFile();

    std::string fPath;
};
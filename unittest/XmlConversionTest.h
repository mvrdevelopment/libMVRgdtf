//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "Unittest.h"


class XmlConversionTest : public Unittest
{
public:
    XmlConversionTest(const std::string& currentDir);
    virtual ~XmlConversionTest();
protected:
    bool virtual ExecuteTest();

private:
    void RunTests();
};
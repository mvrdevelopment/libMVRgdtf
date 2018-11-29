//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "Unittest.h"

class MvrUnittest : public Unittest
{
public:
    MvrUnittest(const std::string& currentDir);
    virtual ~MvrUnittest();
protected:
    bool virtual ExecuteTest();

private:
    void WriteFile();
    void ReadFile();

    std::string fPath;
	std::string gdtfPath;
};
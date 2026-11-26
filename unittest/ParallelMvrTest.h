//-----------------------------------------------------------------------------
//----- Copyright MVR Group
//-----------------------------------------------------------------------------
#pragma once
#include "Unittest.h"

#include <string>
#include <vector>

// Covers the parallel MVR write/read paths and the opt-in GDTF preload cache.
class ParallelMvrTest : public Unittest
{
public:
    ParallelMvrTest(const std::string& currentDir);
    virtual ~ParallelMvrTest();
protected:
    bool virtual ExecuteTest();

private:
    void WriteFile();
    void ReadFile(bool preload, std::vector<std::string>& outFixtureSummary);

    std::string fMvrPath;
};

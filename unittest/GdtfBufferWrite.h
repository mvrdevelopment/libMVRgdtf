//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "Unittest.h"

class GdtfBufferWrite : public Unittest
{
public:
    GdtfBufferWrite(const std::string& currentDir);
    virtual ~GdtfBufferWrite();
protected:
    bool virtual ExecuteTest();

    private:
    void Write();
    void Read();


    char*   fBuffer;
    char*   fFileBuffer;
    size_t  fBufferLength;


};
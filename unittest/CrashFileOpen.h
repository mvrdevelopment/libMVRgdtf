//-----------------------------------------------------------------------------
//----- Copyright MVR Group
//-----------------------------------------------------------------------------
#pragma once
#include "Unittest.h"

class GdtfCrashFileOpen : public Unittest
{
public:
    GdtfCrashFileOpen(const std::string& currentDir);
    virtual ~GdtfCrashFileOpen();
protected:
    bool virtual ExecuteTest();

    private:
    void ReadError(VectorworksMVR::IGdtfXmlParsingErrorPtr& error, size_t lineNumber, size_t colNumber, VectorworksMVR::GdtfDefines::EGdtfParsingError errorType);



};
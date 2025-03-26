//-----------------------------------------------------------------------------
//----- Copyright MVR Group
//-----------------------------------------------------------------------------
#pragma once
#include "Unittest.h"

class ChannelFunctionStartTest : public Unittest
{
public:
    ChannelFunctionStartTest(const std::string& currentDir);
    virtual ~ChannelFunctionStartTest();
protected:
    bool virtual ExecuteTest();

    private:
    void ReadError(VectorworksMVR::IGdtfXmlParsingErrorPtr& error, size_t lineNumber, size_t colNumber, VectorworksMVR::GdtfDefines::EGdtfParsingError errorType);



};
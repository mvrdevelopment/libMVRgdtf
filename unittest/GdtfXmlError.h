//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "Unittest.h"


class GdtfXmlErrorTest : public Unittest
{
public:
    GdtfXmlErrorTest(const std::string& currentDir);
    virtual ~GdtfXmlErrorTest();
protected:
    bool virtual ExecuteTest();

private:
    void ReadDamagedFile();
    void ReadNonExistingFile();
    void ReadError(VectorworksMVR::IGdtfXmlParsingErrorPtr& error, size_t lineNumber, size_t colNumber, VectorworksMVR::GdtfDefines::EGdtfParsingError errorType, const std::string& nodeName, const std::string& objectName);

    std::string fErrorGdtf_Path;
};
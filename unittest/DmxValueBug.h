//-----------------------------------------------------------------------------
//----- Copyright MVR Group
//-----------------------------------------------------------------------------
#pragma once
#include "Unittest.h"

class GdtfValueBug : public Unittest
{
public:
    GdtfValueBug(const std::string& currentDir);
    virtual ~GdtfValueBug();
protected:
    bool virtual ExecuteTest();

    private:
    void ReadError(VectorworksMVR::IGdtfXmlParsingErrorPtr& error, size_t lineNumber, size_t colNumber, VectorworksMVR::GdtfDefines::EGdtfParsingError errorType);
    void CheckChannelSet(VectorworksMVR::IGdtfDmxChannelSetPtr& channelSet, std::string name, VectorworksMVR::GdtfDefines::DmxValue start, VectorworksMVR::GdtfDefines::DmxValue end);



};
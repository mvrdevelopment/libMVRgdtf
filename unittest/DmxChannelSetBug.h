//-----------------------------------------------------------------------------
//----- Copyright MVR Group
//-----------------------------------------------------------------------------
#pragma once
#include "Unittest.h"

class GdtfDmxChannelSetBug : public Unittest
{
public:
    GdtfDmxChannelSetBug(const std::string& currentDir);
    virtual ~GdtfDmxChannelSetBug();
protected:
    bool virtual ExecuteTest();

    private:
    void ReadError(VectorworksMVR::IGdtfXmlParsingErrorPtr& error, size_t lineNumber, size_t colNumber, VectorworksMVR::GdtfDefines::EGdtfParsingError errorType);
    void CheckChannelSet(VectorworksMVR::IGdtfDmxChannelSetPtr& channelSet, std::string name, VectorworksMVR::GdtfDefines::DmxValue start, VectorworksMVR::GdtfDefines::DmxValue end);



};
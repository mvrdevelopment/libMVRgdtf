//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "Unittest.h"

class GdtfDmxUnittest : public Unittest
{
public:
    GdtfDmxUnittest(const std::string& currentDir);
    virtual ~GdtfDmxUnittest();
protected:
    bool virtual ExecuteTest();

private:
    void WriteFile();
    void ReadFile();

    std::string fPath;
    
    void CheckChannelSet(VectorworksMVR::IGdtfDmxChannelSetPtr& channelSet, std::string name, VectorworksMVR::GdtfDefines::DmxValue start, VectorworksMVR::GdtfDefines::DmxValue end);
    void Check8bitChannel(VectorworksMVR::IGdtfDmxChannelPtr& dmxChannel);

};
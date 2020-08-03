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

    void CheckDmxChannel(VectorworksMVR::IGdtfDmxChannelPtr& dmxChannel, Sint32 dmxBreak, Sint32 coarse, Sint32 fine, Sint32 ultra, Sint32 uber, VectorworksMVR::GdtfDefines::DmxValue highlight, double MibFade, double dmxChangeLimit, VectorworksMVR::GdtfDefines::EGdtfChannelBitResolution resolution);
    void CheckChannelSet(VectorworksMVR::IGdtfDmxChannelSetPtr& channelSet, std::string name, VectorworksMVR::GdtfDefines::DmxValue start, VectorworksMVR::GdtfDefines::DmxValue end);
    void CheckFunction(VectorworksMVR::IGdtfDmxChannelFunctionPtr& function, std::string name, std::string attributeName, VectorworksMVR::GdtfDefines::DmxValue defaultValue, VectorworksMVR::GdtfDefines::DmxValue start, VectorworksMVR::GdtfDefines::DmxValue end, VectorworksMVR::GdtfDefines::EGdtfChannelBitResolution resolution);

    void Check8bitChannel(VectorworksMVR::IGdtfDmxChannelPtr& dmxChannel);
    void Check24bitChannel(VectorworksMVR::IGdtfDmxChannelPtr& dmxChannel);


};
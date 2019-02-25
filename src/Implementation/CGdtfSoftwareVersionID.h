//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    class CGdtfSoftwareVersionIDImpl : public VCOMImpl<IGdtfSoftwareVersionID>
    {
    public:
        CGdtfSoftwareVersionIDImpl();
        ~CGdtfSoftwareVersionIDImpl();
    
    public:
        virtual VCOMError VCOM_CALLTYPE     GetValue (size_t& outVal);
        virtual VCOMError VCOM_CALLTYPE     SetValue (size_t  value);

        virtual VCOMError VCOM_CALLTYPE     GetDMXPersonalityCount(size_t& outCount);
        virtual VCOMError VCOM_CALLTYPE     GetDMXPersonalityAt(size_t at, IGdtfDMXPersonality**  outValue);
        virtual VCOMError VCOM_CALLTYPE     CreateDMXPersonality(size_t dmxPersonalityValue, IGdtfDmxMode* dmxMode, IGdtfDMXPersonality **outVal);		

        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
        virtual void*	  VCOM_CALLTYPE     GetBoundObject();

    private:
        SceneData::GdtfSoftwareVersionID* fSoftwareVersionID;

    public:
        void					            SetPointer(SceneData::GdtfSoftwareVersionID* softwareVersionID);
        SceneData::GdtfSoftwareVersionID*	GetPointer();
    };

    const VWIID IID_GdtfSoftwareVersionID = { 0xf06292b8, 0x4d57, 0x4c8c, {0xbc, 0xd1, 0xfc, 0x57, 0x31, 0xc5, 0x31, 0xe3}};
}


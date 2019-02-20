//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "GDTFManager.h"


namespace VectorworksMVR
{
    class CGdtfDMXPersonalityImpl : public VCOMImpl<IGdtfDMXPersonality>
    {
    public:
        CGdtfDMXPersonalityImpl();
        virtual ~CGdtfDMXPersonalityImpl();

        // DMXPersonality_Optional virtual VCOMError VCOM_CALLTYPE     GetDMXPersonalityCount(size_t& outCount);
        // DMXPersonality_Optional virtual VCOMError VCOM_CALLTYPE     GetDMXPersonalityAt(size_t at, IGdtfDMXPersonality**  outDMXPersonality);
        // DMXPersonality_Optional virtual VCOMError VCOM_CALLTYPE     CreateDMXPersonality (IGdtfDMXPersonality** outDMXPersonality);		

        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
        virtual void*	  VCOM_CALLTYPE     GetBoundObject();
    private:
        SceneData::GdtfDMXPersonality* fDMXPersonality;

    public:
        void					        SetPointer(SceneData::GdtfDMXPersonality* dmxPersonality);
        SceneData::GdtfDMXPersonality*	GetPointer();

    };
    
    const VWIID IID_GdtfDMXPersonality = { 0xe24395d7, 0xfda9, 0x4fae, {0xb8, 0x3b, 0xac, 0xe8, 0x38, 0x24, 0x25, 0x83}};
}


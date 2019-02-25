//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "GDTFManager.h"
#include "CGdtfDmxMode.h"

namespace VectorworksMVR
{
    class CGdtfDMXPersonalityImpl : public VCOMImpl<IGdtfDMXPersonality>
    {
    public:
        CGdtfDMXPersonalityImpl();
        virtual ~CGdtfDMXPersonalityImpl();

        // Getter        
        virtual VCOMError VCOM_CALLTYPE		GetValue(size_t& outValue) const;        
        virtual VCOMError VCOM_CALLTYPE     GetDmxMode(IGdtfDmxMode **outDmxMode);
        // Setter       
        virtual VCOMError VCOM_CALLTYPE     SetValue(size_t val);
        virtual VCOMError VCOM_CALLTYPE     SetDmxMode (IGdtfDmxMode * newDmxMode);
        //    
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






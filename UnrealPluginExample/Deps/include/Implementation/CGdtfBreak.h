//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "GDTFManager.h"
#include "Include/IMediaRessourceVectorInterface.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfBreakImpl : public VCOMImpl<IGdtfBreak>
    {
    public:
        CGdtfBreakImpl();
        virtual ~CGdtfBreakImpl();
        
        virtual VCOMError VCOM_CALLTYPE     GetDmxBreak(Sint32& dmxBreak);
        virtual VCOMError VCOM_CALLTYPE     GetDmxAddress(DMXAddress& dmxAdress);

        virtual VCOMError VCOM_CALLTYPE     SetDmxBreak(Sint32 dmxBreak);
        virtual VCOMError VCOM_CALLTYPE     SetDmxAddress(DMXAddress dmxAdress);

		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
		virtual void*	  VCOM_CALLTYPE     GetBoundObject();
		
    private:
        SceneData::GdtfBreak* fBreak;
    public:
        void setPointer(SceneData::GdtfBreak* breakp);
    };
    const VWIID IID_GdtfBreak = { 0x67f3107f, 0xebfb, 0x48b9, {0x96, 0xac, 0x51, 0xa4, 0xee, 0x93, 0xf6, 0xd8}};
}

//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "GDTFManager.h"
#include "Include/IMediaRessourceVectorInterface.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfMapImpl : public VCOMImpl<IGdtfMap>
    {
    public:
        CGdtfMapImpl();
        virtual ~CGdtfMapImpl();
        
		virtual VCOMError VCOM_CALLTYPE     GetKey(Uint32& key);
		virtual VCOMError VCOM_CALLTYPE     GetValue(Uint32& value);

        virtual VCOMError VCOM_CALLTYPE     SetKey(Uint32 key);
        virtual VCOMError VCOM_CALLTYPE     SetValue(Uint32 value);

		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
		virtual void*	  VCOM_CALLTYPE     GetBoundObject();
		
    private:
        SceneData::GdtfMap* fMap;
    public:
        void SetPointer(SceneData::GdtfMap* map);
    };
    const VWIID IID_GdtfMap = { 0x4cb99d7d, 0x854c, 0x4f18, {0x83, 0xf2, 0x53, 0x3f, 0x6a, 0x53, 0xfc, 0xc2}};
}

//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "GDTFManager.h"

namespace VectorworksMVR
{
    class CGdtfArtNetImpl : public VCOMImpl<IGdtfArtNet>
    {
    public:
        CGdtfArtNetImpl();
        virtual ~CGdtfArtNetImpl();
        
        virtual VCOMError VCOM_CALLTYPE  	GetMapCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE  	GetMapAt(size_t at, IGdtfMap** map);
        virtual VCOMError VCOM_CALLTYPE  	CreateMap(Uint32 key, Uint32 value, IGdtfMap** map);

        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
        virtual void*	  VCOM_CALLTYPE     GetBoundObject();
    private:
        SceneData::GdtfArtNet* fArtNet;

    public:
        void			        SetPointer(SceneData::GdtfArtNet* value);
        SceneData::GdtfArtNet*	GetPointer();
    };

    const VWIID IID_GdtfArtNet = { 0xdf2ba7be, 0x7650, 0x4ee1, {0xba, 0x73, 0x6c, 0xac, 0x1a, 0xa1, 0x17, 0xcb}};
}
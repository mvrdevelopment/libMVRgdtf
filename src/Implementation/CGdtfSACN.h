//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "GDTFManager.h"

namespace VectorworksMVR
{
    class CGdtfSACNImpl : public VCOMImpl<IGdtfSACN>
    {
    public:
        CGdtfSACNImpl();
        virtual ~CGdtfSACNImpl();
        
        virtual VCOMError VCOM_CALLTYPE  	GetMapCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE  	GetMapAt(size_t at, IGdtfMap** map);
        virtual VCOMError VCOM_CALLTYPE  	CreateMap(Uint32 key, Uint32 value, IGdtfMap** map);

        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
        virtual void*	  VCOM_CALLTYPE     GetBoundObject();
    private:
        SceneData::GdtfsAcn* fSACN;

    public:
        void			        SetPointer(SceneData::GdtfsAcn* value);
        SceneData::GdtfsAcn*	GetPointer();
    };

    const VWIID IID_GdtfSACN = { 0x3c9b0bc4, 0xb04b, 0x42c7, {0xb9, 0x39, 0xe4, 0x42, 0xed, 0xdc, 0x4e, 0x52}};
}
//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "GDTFManager.h"
#include "Include/IMediaRessourceVectorInterface.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfGamutImpl : public VCOMImpl<IGdtfGamut>
    {
    public:
        CGdtfGamutImpl();
        virtual ~CGdtfGamutImpl();
        
        virtual MvrString VCOM_CALLTYPE     GetName();
		virtual VCOMError VCOM_CALLTYPE     SetName(MvrString name);

		virtual VCOMError VCOM_CALLTYPE 	GetPointCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE 	GetPointAt(size_t at, CieColor& outColor);
        virtual VCOMError VCOM_CALLTYPE 	CreatePoint(CieColor& outColor);

		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
		virtual void*	  VCOM_CALLTYPE     GetBoundObject();
		
    private:
        SceneData::GdtfGamut* fGamut;
    public:
        void                    SetPointer(SceneData::GdtfGamut* gamut);
        SceneData::GdtfGamut*   GetPointer();
    };
    const VWIID IID_GdtfGamut = { 0x13481bd5, 0x04cd, 0x4845, {0xab, 0xf4, 0x5c, 0xb8, 0xc2, 0x0d, 0xdb, 0xa7}};
}

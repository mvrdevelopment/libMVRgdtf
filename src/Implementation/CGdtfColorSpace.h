//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "GDTFManager.h"

namespace VectorworksMVR
{
    class CGdtfColorSpaceImpl : public VCOMImpl<IGdtfColorSpace>
    {
    public:
        CGdtfColorSpaceImpl();
        virtual ~CGdtfColorSpaceImpl();

        // Getter
        virtual MvrString VCOM_CALLTYPE GetName();
        virtual VCOMError VCOM_CALLTYPE GetColorSpace(EGdtfColorSpace& outVal);
        virtual VCOMError VCOM_CALLTYPE	GetRed (CieColor& outVal);
        virtual VCOMError VCOM_CALLTYPE GetGreen(CieColor& outVal);
        virtual VCOMError VCOM_CALLTYPE	GetBlue(CieColor& outVal);
        virtual VCOMError VCOM_CALLTYPE	GetWhite(CieColor& outVal);
        // Setter
        virtual VCOMError VCOM_CALLTYPE SetName(MvrString name);
        virtual VCOMError VCOM_CALLTYPE SetColorSpace(EGdtfColorSpace val);
        virtual VCOMError VCOM_CALLTYPE SetRed(CieColor val);
        virtual VCOMError VCOM_CALLTYPE SetGreen(CieColor val);
        virtual VCOMError VCOM_CALLTYPE SetBlue(CieColor val);
        virtual VCOMError VCOM_CALLTYPE SetWhite(CieColor val);
        //
        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
        virtual void*	  VCOM_CALLTYPE     GetBoundObject();

    private:
        SceneData::GdtfColorSpace* fColorSpace;

    public:
        void					    SetPointer(SceneData::GdtfColorSpace* ColorSpace);
        SceneData::GdtfColorSpace*	GetPointer();

    };

    const VWIID IID_GdtfColorSpace = { 0x70988cb4, 0x1e9e, 0x4aa6, {0x8f, 0x35, 0x74, 0xd2, 0x0a, 0xef, 0xfe, 0x6c}};
}


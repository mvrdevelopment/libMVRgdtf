//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "GDTFManager.h"

namespace VectorworksMVR
{
    class CGdtfCRIImpl : public VCOMImpl<IGdtfCRI>
    {
    public:
        CGdtfCRIImpl();
        virtual ~CGdtfCRIImpl();
        
        // Getter
        virtual VCOMError VCOM_CALLTYPE     GetColorSample(EGdtfColorSample outVal);
        virtual VCOMError VCOM_CALLTYPE     GetColorRenderingIndex(Uint8& outVal);
        // Setter
        virtual VCOMError VCOM_CALLTYPE     SetColorSample(EGdtfColorSample val);
        virtual VCOMError VCOM_CALLTYPE     SetColorRenderingIndex(Uint8 val);
        //
        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
        virtual void*	  VCOM_CALLTYPE     GetBoundObject();

    private:
        SceneData::GdtfCRI* fCRI;

    public:
        void				SetPointer(SceneData::GdtfCRI* CRI);
        SceneData::GdtfCRI*	GetPointer();

    };

    const VWIID IID_GdtfCRI = {0x4bf0778b, 0x10a3, 0x48dd, {0xbb, 0x52, 0x59, 0x9a, 0x05, 0xc1, 0xe8, 0x28}};
}


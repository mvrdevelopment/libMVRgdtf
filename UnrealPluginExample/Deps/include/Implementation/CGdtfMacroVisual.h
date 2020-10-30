//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfMacroVisualImpl : public VCOMImpl<IGdtfMacroVisual>
    {
    public:
        CGdtfMacroVisualImpl();
        virtual ~CGdtfMacroVisualImpl();

        virtual VCOMError VCOM_CALLTYPE     GetVisualStepCount(size_t& outCount);
        virtual VCOMError VCOM_CALLTYPE     GetVisualStepAt(size_t at, IGdtfMacroVisualStep**  outVal);
        virtual VCOMError VCOM_CALLTYPE     CreateVisualStep(IGdtfMacroVisualStep** outVal);

        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
        virtual void*	  VCOM_CALLTYPE     GetBoundObject();
    private:
        SceneData::GdtfMacroVisual* fMacroVisual;
    public:
        void					SetPointer(SceneData::GdtfMacroVisual* macroVisual);
        SceneData::GdtfMacroVisual*	GetPointer();
    };

    const VWIID IID_GdtfMacroVisual = { 0x043c01ba, 0x18a6, 0x4ca9,{ 0x97, 0xb6, 0x59, 0x14, 0x7d, 0xc8, 0x96, 0x31 } };
}

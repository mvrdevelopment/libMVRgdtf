//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfMacroVisualValueImpl : public VCOMImpl<IGdtfMacroVisualValue>
    {
    public:
        CGdtfMacroVisualValueImpl();
        virtual ~CGdtfMacroVisualValueImpl();

        virtual VCOMError VCOM_CALLTYPE   GetDmxValue(DmxValue& outValue);
        virtual VCOMError VCOM_CALLTYPE   GetDmxChannel(IGdtfDmxChannelFunction** outValue);

        virtual VCOMError VCOM_CALLTYPE   SetDmxValue(DmxValue newValue);
        virtual VCOMError VCOM_CALLTYPE   SetDmxChannel(IGdtfDmxChannelFunction* newValue);

        virtual VCOMError VCOM_CALLTYPE   BindToObject(void* objAddr);
        virtual void*	  VCOM_CALLTYPE   GetBoundObject();

    private:
        SceneData::GdtfMacroVisualValue* fMacroVisualValue;

    public:
        void					            SetPointer(SceneData::GdtfMacroVisualValue* macroVisualValue);
        SceneData::GdtfMacroVisualValue*	GetPointer();

    };

    const VWIID IID_GdtfMacroVisualValue = { 0x0feadc0f, 0x9da4, 0x4f6a,{ 0xbc, 0x7a, 0xce, 0xeb, 0x7d, 0x8d, 0x5a, 0xd4 } };
}

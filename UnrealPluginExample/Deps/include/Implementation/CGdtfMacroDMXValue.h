//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfMacroDMXValueImpl : public VCOMImpl<IGdtfMacroDMXValue>
    {
    public:
        CGdtfMacroDMXValueImpl();
        virtual ~CGdtfMacroDMXValueImpl();

        virtual VCOMError VCOM_CALLTYPE   GetDmxValue(DmxValue& outValue);
        virtual VCOMError VCOM_CALLTYPE   GetDmxChannel(IGdtfDmxChannel** outValue);
        
        virtual VCOMError VCOM_CALLTYPE   BindToObject(void* objAddr);
        virtual void*	  VCOM_CALLTYPE   GetBoundObject();
    private:
        SceneData::GdtfMacroDMXValue* fMacroDMXValue;

    public:
        void					        SetPointer(SceneData::GdtfMacroDMXValue* MacroDMXValue);
        SceneData::GdtfMacroDMXValue*	GetPointer();

    };

    const VWIID IID_GdtfMacroDMXValue = { 0x43d21f05, 0x1129, 0x42b3,{ 0x9d, 0x7d, 0x87, 0x3e, 0xad, 0xe3, 0x79, 0x14 } };
}

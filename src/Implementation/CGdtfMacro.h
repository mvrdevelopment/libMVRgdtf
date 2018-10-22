//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "../Include/IMediaRessourceVectorInterface.h"
#include "../GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfMacroImpl : public VCOMImpl<IGdtfMacro>
    {
    public:
        CGdtfMacroImpl();
        virtual ~CGdtfMacroImpl();

        virtual MvrString VCOM_CALLTYPE     GetName();
        virtual VCOMError VCOM_CALLTYPE     SetName(MvrString name);

    private:
        SceneData::GdtfMacro* fMacro;
        
    public:
        void setPointer(SceneData::GdtfMacro* macro);
    };
    const VWIID IID_GdtfMacro = { 0xba3ddafc, 0x2ce0, 0x43d9, {0xab, 0x0b, 0xdc, 0xff, 0x30, 0xab, 0x49, 0xb1}};

}

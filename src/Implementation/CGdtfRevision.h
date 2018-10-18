//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "CGeometryProviderWrapper.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfRevisionImpl : public VectorworksMVR::VCOMImpl<IGdtfRevision>
    {
    public:
        CGdtfRevisionImpl();
        virtual ~CGdtfRevisionImpl();
        
        virtual MvrString VCOM_CALLTYPE     GetText();
        virtual MvrString VCOM_CALLTYPE     GetDate();

        virtual VCOMError VCOM_CALLTYPE     SetText(MvrString txt);       

    private:
        SceneData::GdtfRevision* fRevision;
    
    public:
        void setPointer(SceneData::GdtfRevision* revision);
        
    };
    const VWIID IID_GdtfRevision = { 0x40f3de7e, 0x7990, 0x4eca, {0xaf, 0x53, 0x16, 0x3a, 0x28, 0x9f, 0xcb, 0x52}};

}

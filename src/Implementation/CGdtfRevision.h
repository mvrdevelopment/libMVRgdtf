//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfRevisionImpl : public VCOMImpl<IGdtfRevision>
    {
    public:
        CGdtfRevisionImpl();
        virtual ~CGdtfRevisionImpl();
        
        virtual MvrString VCOM_CALLTYPE     GetText();
        virtual VCOMError VCOM_CALLTYPE     GetDate(STime& date);
        virtual VCOMError VCOM_CALLTYPE     GetUserId(size_t& userId);
        virtual MvrString VCOM_CALLTYPE     GetModifiedBy();

        virtual VCOMError VCOM_CALLTYPE     SetText(MvrString txt);
        virtual VCOMError VCOM_CALLTYPE     SetDate(STime date);    
		virtual VCOMError VCOM_CALLTYPE     SetUserId(size_t userId);
        virtual VCOMError VCOM_CALLTYPE     SetModifiedBy(MvrString modifiedBy);


    private:
        SceneData::GdtfRevision* fRevision;
    
    public:
        void setPointer(SceneData::GdtfRevision* revision);
        
    };
    const VWIID IID_GdtfRevision = { 0x40f3de7e, 0x7990, 0x4eca, {0xaf, 0x53, 0x16, 0x3a, 0x28, 0x9f, 0xcb, 0x52}};

}

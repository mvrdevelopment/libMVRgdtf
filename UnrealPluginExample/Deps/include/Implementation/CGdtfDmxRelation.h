//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfDmxRelationImpl : public VCOMImpl<IGdtfDmxRelation>
    {
    public:
        CGdtfDmxRelationImpl();
        virtual ~CGdtfDmxRelationImpl();
        
        virtual MvrString VCOM_CALLTYPE     GetName();
        virtual VCOMError VCOM_CALLTYPE     GetMasterChannel(IGdtfDmxChannel** master);
        virtual VCOMError VCOM_CALLTYPE     GetSlaveChannel(IGdtfDmxChannelFunction** slave);
        virtual VCOMError VCOM_CALLTYPE     GetRelationType(EGdtfDmxRelationType& relation);
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
		virtual void*	  VCOM_CALLTYPE     GetBoundObject();
		
    private:
        SceneData::GdtfDmxRelation* fRelation;
        
    public:
        void setPointer(SceneData::GdtfDmxRelation* relation);
        
    };
    const VWIID IID_GdtfDmxRelation = { 0x171f2cc2, 0xf458, 0x4314, {0xb0, 0x10, 0xb9, 0x5b, 0xe1, 0x41, 0x12, 0xaf}};

}

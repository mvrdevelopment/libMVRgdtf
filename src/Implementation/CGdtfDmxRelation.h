//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "CGeometryProviderWrapper.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfDmxRelationImpl : public VectorworksMVR::VCOMImpl<IGdtfDmxRelation>
    {
    public:
        CGdtfDmxRelationImpl();
        virtual ~CGdtfDmxRelationImpl();
        
        virtual MvrString VCOM_CALLTYPE     GetName();
        virtual VCOMError VCOM_CALLTYPE     GetMasterChannel(IGdtfDmxChannel** master);
        virtual VCOMError VCOM_CALLTYPE     GetSlaveChannel(IGdtfDmxChannelFunction** slave);
        virtual VCOMError VCOM_CALLTYPE     GetRelationType(EGdtfDmxRelationType& relation);
        virtual VCOMError VCOM_CALLTYPE     GetDmxStart(Sint32& start);
        virtual VCOMError VCOM_CALLTYPE     GetDmxEnd(Sint32& end);

		virtual VCOMError VCOM_CALLTYPE     SetName(MvrString name);
		virtual VCOMError VCOM_CALLTYPE     SetMasterChannel(IGdtfDmxChannel* newMaster);
		virtual VCOMError VCOM_CALLTYPE     SetSlaveChannel(IGdtfDmxChannelFunction* newSlave);
		virtual VCOMError VCOM_CALLTYPE     SetRelationType(GdtfDefines::EGdtfDmxRelationType type);
		virtual VCOMError VCOM_CALLTYPE     SetDmxStart(DmxValue start);
		virtual VCOMError VCOM_CALLTYPE     SetDmxEnd(DmxValue end);
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
		virtual void*	  VCOM_CALLTYPE     GetBoundObject();
		
    private:
        SceneData::GdtfDmxRelation* fRelation;
        
    public:
        void setPointer(SceneData::GdtfDmxRelation* relation);
        
    };
    const VWIID IID_GdtfDmxRelation = { 0x171f2cc2, 0xf458, 0x4314, {0xb0, 0x10, 0xb9, 0x5b, 0xe1, 0x41, 0x12, 0xaf}};

}

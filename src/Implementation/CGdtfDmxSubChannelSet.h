//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfDmxSubChannelSetImpl : public VCOMImpl<IGdtfDmxSubChannelSet>
    {
    public:
        CGdtfDmxSubChannelSetImpl();
        virtual ~CGdtfDmxSubChannelSetImpl();
        
        virtual MvrString VCOM_CALLTYPE     GetName();		
        virtual VCOMError VCOM_CALLTYPE     GetPhysicalFrom(double& from);        
        virtual VCOMError VCOM_CALLTYPE     GetPhysicalTo(double& to);
        virtual VCOMError VCOM_CALLTYPE     GetSubPhysicalUnit(IGdtfSubPhysicalUnit** subPhysicalUnit);
		virtual VCOMError VCOM_CALLTYPE		GetDMXProfile(IGdtfDMXProfile** dmxProfile);
		
		virtual VCOMError VCOM_CALLTYPE     SetName(MvrString name);		
        virtual VCOMError VCOM_CALLTYPE     SetPhysicalFrom(double from);        
        virtual VCOMError VCOM_CALLTYPE     SetPhysicalTo(double to);
        virtual VCOMError VCOM_CALLTYPE     SetSubPhysicalUnit(IGdtfSubPhysicalUnit* subPhysicalUnit);
		virtual VCOMError VCOM_CALLTYPE		SetDMXProfile(IGdtfDMXProfile* dmxProfile);
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
		virtual void*	  VCOM_CALLTYPE     GetBoundObject();

	private:
        SceneData::GdtfDmxSubChannelSet* fSubChannelSet;
        
    public:
        void SetPointer(SceneData::GdtfDmxSubChannelSet* subChannelSet);
    };
    const VWIID IID_GdtfDmxSubChannelSet = { 0x1d5603d3, 0x28fd, 0x47db, {0x96, 0x84, 0xe8, 0x65, 0x92, 0x8e, 0xb2, 0x63}};

}

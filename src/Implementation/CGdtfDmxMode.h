//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfDmxModeImpl : public VCOMImpl<IGdtfDmxMode>
    {
    public:
        CGdtfDmxModeImpl();
        virtual ~CGdtfDmxModeImpl();
        
        virtual MvrString VCOM_CALLTYPE     GetName();

        virtual MvrString VCOM_CALLTYPE     GetDescription();
        virtual VCOMError VCOM_CALLTYPE     SetDescription(MvrString description);
		
		virtual VCOMError VCOM_CALLTYPE     GetGeometry(VectorworksMVR::IGdtfGeometry **geo);
		virtual VCOMError VCOM_CALLTYPE     SetGeometry(IGdtfGeometry* model);
		
        virtual VCOMError VCOM_CALLTYPE     GetDmxChannelCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE     GetDmxChannelAt(size_t at, IGdtfDmxChannel** channel);
		virtual VCOMError VCOM_CALLTYPE     CreateDmxChannel(IGdtfGeometry* geometry, IGdtfDmxChannel** channel);
		
        
        virtual VCOMError VCOM_CALLTYPE     GetDmxRelationCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE     GetDmxRelationAt(size_t at, IGdtfDmxRelation** relation);
		virtual VCOMError VCOM_CALLTYPE     CreateDmxRelation(MvrString name, GdtfDefines::EGdtfDmxRelationType type, IGdtfDmxChannel* master, IGdtfDmxChannelFunction* slave, IGdtfDmxRelation** relation);

		virtual VCOMError VCOM_CALLTYPE     GetDmxMacroCount(size_t& count);
		virtual VCOMError VCOM_CALLTYPE     GetDmxMacroAt(size_t at, IGdtfMacro** macro);
		virtual VCOMError VCOM_CALLTYPE     CreateDmxMacro(MvrString name, IGdtfMacro** macro);

        virtual VCOMError VCOM_CALLTYPE     GetBreakCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE     GetBreakAt(size_t at, size_t &breakId);
        virtual VCOMError VCOM_CALLTYPE     GetFootprintForBreak(size_t inBreak, size_t& footprint);

		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
		virtual void*	  VCOM_CALLTYPE     GetBoundObject();
		
    private:
        SceneData::GdtfDmxMode* fDmxMode;
        
    public:
        SceneData::GdtfDmxMode* getPointer();
        void setPointer(SceneData::GdtfDmxMode* dmxMode);
        
    };
    const VWIID IID_GdtfDmxMode = { 0x5433d14d, 0xe4c6, 0x4a39, {0xb0, 0x2a, 0xf0, 0xa6, 0x09, 0xe6, 0x3d, 0x56}};

}

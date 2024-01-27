//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfDmxChannelImpl : public VCOMImpl<IGdtfDmxChannel>
    {
    public:
        CGdtfDmxChannelImpl();
        virtual ~CGdtfDmxChannelImpl();
        
        virtual MvrString VCOM_CALLTYPE     GetName();
        virtual VCOMError VCOM_CALLTYPE     GetDmxBreak(Sint32& dmxBreak);
        virtual VCOMError VCOM_CALLTYPE     GetCoarse(Sint32& coarse);
        virtual VCOMError VCOM_CALLTYPE     GetFine(Sint32& fine);
        virtual VCOMError VCOM_CALLTYPE     GetUltra(Sint32& ultra);
		virtual VCOMError VCOM_CALLTYPE	    GetUber(Sint32& uber);        
        virtual VCOMError VCOM_CALLTYPE     GetHighlight(DmxValue& highlight);
		virtual VCOMError VCOM_CALLTYPE     HasHighlight(bool& highlight);
		virtual VCOMError VCOM_CALLTYPE     GetGeometry(VectorworksMVR::IGdtfGeometry **geo);
        virtual VCOMError VCOM_CALLTYPE     GetResolution(GdtfDefines::EGdtfChannelBitResolution& resolution);
		
		virtual VCOMError VCOM_CALLTYPE     SetDmxBreak(Sint32 dmxBreak);
		virtual VCOMError VCOM_CALLTYPE     SetCoarse(Sint32 coarse);
		virtual VCOMError VCOM_CALLTYPE     SetFine(Sint32 fine);
		virtual VCOMError VCOM_CALLTYPE     SetUltra(Sint32 ultra);
		virtual VCOMError VCOM_CALLTYPE     SetUber(Sint32 uber);		
		virtual VCOMError VCOM_CALLTYPE     SetHighlight(DmxValue highlight);
		virtual VCOMError VCOM_CALLTYPE     SetGeometry(IGdtfGeometry* model);
		
        virtual VCOMError VCOM_CALLTYPE     GetLogicalChannelCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE     GetLogicalChannelAt(size_t at, IGdtfDmxLogicalChannel** channel);
		virtual VCOMError VCOM_CALLTYPE     CreateLogicalChannel(IGdtfAttribute* attribute, IGdtfDmxLogicalChannel** channel);
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
		virtual void*	  VCOM_CALLTYPE     GetBoundObject();

        // GDTF 1.1
		virtual VCOMError VCOM_CALLTYPE     GetInitialFunction(IGdtfDmxChannelFunction** function);
		virtual VCOMError VCOM_CALLTYPE     SetInitialFunction(IGdtfDmxChannelFunction* function);
        
    private:
        SceneData::GdtfDmxChannel* fChannel;
        
    public:
        void setPointer(SceneData::GdtfDmxChannel* channel);
        SceneData::GdtfDmxChannel* getPointer();
        
    };
    const VWIID IID_GdtfDmxChannel = { 0x05dd4507, 0x5471, 0x49a8, {0x81, 0xd7, 0x2e, 0xec, 0xc1, 0x3d, 0xdd, 0xbe}};

}

//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "GDTFManager.h"
#include "Include/IMediaRessourceVectorInterface.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfLaserProtocolImpl : public VCOMImpl<IGdtfLaserProtocol>
    {
    public:
        CGdtfLaserProtocolImpl();
        virtual ~CGdtfLaserProtocolImpl();
        
        virtual MvrString VCOM_CALLTYPE     GetName();
		virtual VCOMError VCOM_CALLTYPE     SetName(MvrString name);

		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
		virtual void*	  VCOM_CALLTYPE     GetBoundObject();
		
    private:
        SceneData::GdtfLaserProtocol* fLaserProtocol;
    public:
        void SetPointer(SceneData::GdtfLaserProtocol* laserProtocol);
    };
    const VWIID IID_GdtfLaserProtocol = { 0x740ee43c, 0xce2d, 0x49b4, {0xba, 0xe9, 0x50, 0x28, 0xaf, 0x50, 0x54, 0x78}}; 
}

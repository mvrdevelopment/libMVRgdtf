//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfDmxLogicalChannelImpl : public VCOMImpl<IGdtfDmxLogicalChannel>
    {
    public:
        CGdtfDmxLogicalChannelImpl();
        virtual ~CGdtfDmxLogicalChannelImpl();
        
        virtual MvrString VCOM_CALLTYPE     GetName();
		
        virtual VCOMError VCOM_CALLTYPE     GetAttribute(IGdtfAttribute** attribute);
        virtual VCOMError VCOM_CALLTYPE     GetDmxSnap(EGdtfDmxSnap& snap);
		virtual VCOMError VCOM_CALLTYPE     GetDmxMaster(EGdtfDmxMaster& master);
        virtual VCOMError VCOM_CALLTYPE     GetMoveInBlackFrames(double& frames);
        virtual VCOMError VCOM_CALLTYPE     GetDmxChangeTimeLimit(double& changeTimeLimit);

		virtual VCOMError VCOM_CALLTYPE     SetAttribute(IGdtfAttribute* attribute);
		virtual VCOMError VCOM_CALLTYPE     SetDmxSnap(EGdtfDmxSnap snap);
		virtual VCOMError VCOM_CALLTYPE     SetDmxMaster(EGdtfDmxMaster master);
        virtual VCOMError VCOM_CALLTYPE     SetMoveInBlackFrames(double frames);
        virtual VCOMError VCOM_CALLTYPE     SetDmxChangeTimeLimit(double changeTimeLimit);
		
        virtual VCOMError VCOM_CALLTYPE     GetDmxFunctionCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE     GetDmxFunctionAt(size_t at, IGdtfDmxChannelFunction** function);
		virtual VCOMError VCOM_CALLTYPE     CreateDmxFunction(MvrString name, IGdtfDmxChannelFunction** function);

        virtual VCOMError VCOM_CALLTYPE     GetParentDmxChannel(IGdtfDmxChannel** parent);
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
		virtual void*	  VCOM_CALLTYPE     GetBoundObject();
		
    private:
        SceneData::GdtfDmxLogicalChannel* fLogicalChannel;
    public:
        void setPointer(SceneData::GdtfDmxLogicalChannel* logicalChannel);
        
    };
    const VWIID IID_GdtfDmxLogicalChannel = { 0xc6c6fc05, 0x74e8, 0x4cc1, {0xac, 0xda, 0x9c, 0xae, 0x04, 0xd0, 0xf2, 0xaf}};

}

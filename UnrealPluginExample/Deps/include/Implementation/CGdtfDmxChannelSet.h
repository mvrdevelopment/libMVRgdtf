//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfDmxChannelSetImpl : public VCOMImpl<IGdtfDmxChannelSet>
    {
    public:
        CGdtfDmxChannelSetImpl();
        virtual ~CGdtfDmxChannelSetImpl();
        
        virtual MvrString VCOM_CALLTYPE     GetName();
        virtual VCOMError VCOM_CALLTYPE     GetDmxStartAddress(DmxValue& address);
        virtual VCOMError VCOM_CALLTYPE     GetDmxEndAddress(DmxValue& address);
		
        virtual VCOMError VCOM_CALLTYPE     GetPhysicalStart(double& start);
        virtual VCOMError VCOM_CALLTYPE     GetPhysicalEnd(double& end);        
        virtual VCOMError VCOM_CALLTYPE     GetWheelSlot(Sint32& WheelSlotIdx);
		virtual VCOMError VCOM_CALLTYPE		GetUsePhysicalFromParent(bool& outUse);
		
		
		virtual VCOMError VCOM_CALLTYPE     SetPhysicalStart(double start);
		virtual VCOMError VCOM_CALLTYPE     SetPhysicalEnd(double end);		
		virtual VCOMError VCOM_CALLTYPE     SetWheelSlot(Sint32 wheelSlotIdx);
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
		virtual void*	  VCOM_CALLTYPE     GetBoundObject();

	private:
        SceneData::GdtfDmxChannelSet* fChannelSet;
        
    public:
        void setPointer(SceneData::GdtfDmxChannelSet* channelSet);
    };
    const VWIID IID_GdtfDmxChannelSet = { 0x408771ce, 0x035a, 0x4ba2, {0x84, 0x00, 0x8e, 0xbb, 0xb9, 0x21, 0x94, 0x64}};

}

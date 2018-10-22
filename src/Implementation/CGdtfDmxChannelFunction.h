//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "../Include/IMediaRessourceVectorInterface.h"
#include "../GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfDmxChannelFunctionImpl : public VCOMImpl<IGdtfDmxChannelFunction>
    {
    public:
        CGdtfDmxChannelFunctionImpl();
        virtual ~CGdtfDmxChannelFunctionImpl();
        
        virtual MvrString VCOM_CALLTYPE     GetName();		
        virtual VCOMError VCOM_CALLTYPE     GetAttribute(IGdtfAttribute** attribute);
        virtual MvrString VCOM_CALLTYPE     GetOriginalAttribute();
        virtual VCOMError VCOM_CALLTYPE     GetStartAddress(DMXAddress& address);
        virtual VCOMError VCOM_CALLTYPE     GetPhysicalStart(double& start);
        virtual VCOMError VCOM_CALLTYPE     GetPhysicalEnd(double& end);
        virtual VCOMError VCOM_CALLTYPE     GetRealFade(double& fade);        
        virtual VCOMError VCOM_CALLTYPE     GetOnWheel(IGdtfWheel** wheel);
        virtual VCOMError VCOM_CALLTYPE     GetEmitter(IGdtfPhysicalEmitter** emitter);
        virtual VCOMError VCOM_CALLTYPE     GetDMXInvert(EGDTFDmxInvert& dmxInvert);
        virtual VCOMError VCOM_CALLTYPE     GetEncoderInvert(EGDTFEncoderInvert& encoderInvert);

		virtual VCOMError VCOM_CALLTYPE     SetAttribute(IGdtfAttribute* attribute);
		virtual VCOMError VCOM_CALLTYPE     SetOriginalAttribute(MvrString attr);
		virtual VCOMError VCOM_CALLTYPE     SetStartAddress(DMXAddress address);
		virtual VCOMError VCOM_CALLTYPE     SetPhysicalStart(double start);
		virtual VCOMError VCOM_CALLTYPE     SetPhysicalEnd(double end);
		virtual VCOMError VCOM_CALLTYPE     SetRealFade(double fade);
		virtual VCOMError VCOM_CALLTYPE     SetOnWheel(IGdtfWheel* wheel);
        virtual VCOMError VCOM_CALLTYPE     SetEmitter(IGdtfPhysicalEmitter* emitter);
        virtual VCOMError VCOM_CALLTYPE     SetDMXInvert(EGDTFDmxInvert dmxInvert);
        virtual VCOMError VCOM_CALLTYPE     SetEncoderInvert(EGDTFEncoderInvert encoderInvert);

		
        virtual VCOMError VCOM_CALLTYPE     GetDmxChannelSetCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE     GetDmxChannelSetAt(size_t at, IGdtfDmxChannelSet** set);
		virtual VCOMError VCOM_CALLTYPE     CreateDmxChannelSet(MvrString name, DMXAddress start, DMXAddress end, IGdtfDmxChannelSet** set);
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
		virtual void*	  VCOM_CALLTYPE     GetBoundObject();

	private:
        SceneData::GdtfDmxChannelFunction* fFunction;
        
    public:
        void setPointer(SceneData::GdtfDmxChannelFunction* function);
        SceneData::GdtfDmxChannelFunction* getPointer();        
    };
    const VWIID IID_GdtfDmxChannelFunction = { 0x36450821, 0x795d, 0x48be, {0x8b, 0xb0, 0xa1, 0x9d, 0xcd, 0xb7, 0x96, 0x37}};

}

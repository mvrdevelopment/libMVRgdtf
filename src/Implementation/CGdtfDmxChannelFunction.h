//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"

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
        virtual VCOMError VCOM_CALLTYPE     GetDefaultValue(DmxValue& defaultValue);
        virtual VCOMError VCOM_CALLTYPE     GetStartAddress(DmxValue& address);
        virtual VCOMError VCOM_CALLTYPE     GetEndAddress(DmxValue& address);
        virtual VCOMError VCOM_CALLTYPE     GetPhysicalStart(double& start);
        virtual VCOMError VCOM_CALLTYPE     GetPhysicalEnd(double& end);
        virtual VCOMError VCOM_CALLTYPE     GetRealFade(double& fade);
        virtual VCOMError VCOM_CALLTYPE     GetRealAcceleration(double& value);
        virtual VCOMError VCOM_CALLTYPE     GetOnWheel(IGdtfWheel** wheel);
        virtual VCOMError VCOM_CALLTYPE     GetEmitter(IGdtfPhysicalEmitter** emitter);
        virtual VCOMError VCOM_CALLTYPE     GetFilter(IGdtfFilter** outVal);
        virtual VCOMError VCOM_CALLTYPE     GetResolution(GdtfDefines::EGdtfChannelBitResolution& resolution);
        virtual VCOMError VCOM_CALLTYPE     GetColorSpace(IGdtfColorSpace** colorSpace);
		virtual VCOMError VCOM_CALLTYPE     GetGamut(IGdtfGamut** gamut);
		virtual VCOMError VCOM_CALLTYPE     GetDMXProfile(IGdtfDMXProfile** dmxProfile);
		virtual VCOMError VCOM_CALLTYPE     GetMin(double& value);
		virtual VCOMError VCOM_CALLTYPE     GetMax(double& value);
		virtual MvrString VCOM_CALLTYPE     GetCustomName();

		virtual VCOMError VCOM_CALLTYPE     SetAttribute(IGdtfAttribute* attribute);
		virtual VCOMError VCOM_CALLTYPE     SetOriginalAttribute(MvrString attr);
        virtual VCOMError VCOM_CALLTYPE     SetDefaultValue(DmxValue defaultValue);
		virtual VCOMError VCOM_CALLTYPE     SetStartAddress(DmxValue address);
		virtual VCOMError VCOM_CALLTYPE     SetPhysicalStart(double start);
		virtual VCOMError VCOM_CALLTYPE     SetPhysicalEnd(double end);
		virtual VCOMError VCOM_CALLTYPE     SetRealFade(double fade);
        virtual VCOMError VCOM_CALLTYPE     SetRealAcceleration(double value);
		virtual VCOMError VCOM_CALLTYPE     SetOnWheel(IGdtfWheel* wheel);
        virtual VCOMError VCOM_CALLTYPE     SetEmitter(IGdtfPhysicalEmitter* emitter);
        virtual VCOMError VCOM_CALLTYPE     SetFilter(IGdtfFilter* val);
        virtual VCOMError VCOM_CALLTYPE     SetColorSpace(IGdtfColorSpace* colorSpace);
		virtual VCOMError VCOM_CALLTYPE     SetGamut(IGdtfGamut* gamut);
		virtual VCOMError VCOM_CALLTYPE     SetDMXProfile(IGdtfDMXProfile* dmxProfile);
		virtual VCOMError VCOM_CALLTYPE     SetMin(double value);
		virtual VCOMError VCOM_CALLTYPE     SetMax(double value);
		virtual VCOMError VCOM_CALLTYPE     SetCustomName(MvrString customName);
		
        virtual VCOMError VCOM_CALLTYPE     GetDmxChannelSetCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE     GetDmxChannelSetAt(size_t at, IGdtfDmxChannelSet** set);
		virtual VCOMError VCOM_CALLTYPE     CreateDmxChannelSet(MvrString name, DmxValue start, DmxValue end, IGdtfDmxChannelSet** set);

        virtual VCOMError VCOM_CALLTYPE     GetDmxSubChannelSetCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE     GetDmxSubChannelSetAt(size_t at, IGdtfDmxSubChannelSet** subChannelSet);
		virtual VCOMError VCOM_CALLTYPE     CreateDmxSubChannelSet(MvrString name, IGdtfSubPhysicalUnit* subPhysicalUnit, IGdtfDmxSubChannelSet** subChannelSet);

        // Mode Master from GDTF 0.88
		virtual VCOMError VCOM_CALLTYPE     GetModeMasterChannel(IGdtfDmxChannel** outChannel, DmxValue& start, DmxValue& end);
		virtual VCOMError VCOM_CALLTYPE     GetModeMasterFunction(IGdtfDmxChannelFunction** outFunction, DmxValue& start, DmxValue& end);
		virtual VCOMError VCOM_CALLTYPE     SetModeMasterChannel(IGdtfDmxChannel* channel, DmxValue start, DmxValue end);
		virtual VCOMError VCOM_CALLTYPE     SetModeMasterFunction(IGdtfDmxChannelFunction* function, DmxValue start, DmxValue end);
        
        virtual VCOMError VCOM_CALLTYPE     GetParentLogicalChannel(IGdtfDmxLogicalChannel** parent);
		
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

//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfPowerConsumptionImpl : public VCOMImpl<IGdtfPowerConsumption>
    {
    public:
        CGdtfPowerConsumptionImpl();
        virtual ~CGdtfPowerConsumptionImpl();
        
        virtual VCOMError VCOM_CALLTYPE     GetValue(double& outValue);
        virtual VCOMError VCOM_CALLTYPE     GetPowerFactor(double& outPowerFactor);
        virtual VCOMError VCOM_CALLTYPE     GetConnector(IGdtfConnector** outConnector);
        virtual VCOMError VCOM_CALLTYPE     GetVoltageLow(double& outVoltageLow);
        virtual VCOMError VCOM_CALLTYPE     GetVoltageHigh(double& outVoltageHigh);
        virtual VCOMError VCOM_CALLTYPE     GetFrequencyLow(double& outFrequencyLow);
        virtual VCOMError VCOM_CALLTYPE     GetFrequencyHigh(double& outFrequencyHigh);
        
        virtual VCOMError VCOM_CALLTYPE     SetValue(double value);
        virtual VCOMError VCOM_CALLTYPE     SetPowerFactor(double powerFactor);
        virtual VCOMError VCOM_CALLTYPE     SetConnector(IGdtfConnector* connector);
        virtual VCOMError VCOM_CALLTYPE     SetVoltageLow(double voltageLow);
        virtual VCOMError VCOM_CALLTYPE     SetVoltageHigh(double voltageHigh);
        virtual VCOMError VCOM_CALLTYPE     SetFrequencyLow(double frequencyLow);
        virtual VCOMError VCOM_CALLTYPE     SetFrequencyHigh(double frequencyHigh);

		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
		virtual void*	  VCOM_CALLTYPE     GetBoundObject();
    private:
        SceneData::GdtfPowerConsumption* fPowerConsumption;
    public:
        void SetPointer(SceneData::GdtfPowerConsumption* powerConsumption);
        SceneData::GdtfPowerConsumption* GetPointer();
        
    };
    const VWIID IID_GdtfPowerConsumption = { 0xd5044cc5, 0x9399, 0x4c38, {0x94, 0xed, 0x89, 0x8d, 0x13, 0xff, 0x69, 0x75}};
    
}


//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfMacroVisualStepImpl : public VCOMImpl<IGdtfMacroVisualStep>
    {
    public:
        CGdtfMacroVisualStepImpl();
        virtual ~CGdtfMacroVisualStepImpl();
        // 
        virtual VCOMError VCOM_CALLTYPE GetDuration(double& duration);
        virtual VCOMError VCOM_CALLTYPE GetFade(double& fade);
        virtual VCOMError VCOM_CALLTYPE GetDelay(double& delay);
        //        
        virtual VCOMError VCOM_CALLTYPE SetDuration(double d);
        virtual VCOMError VCOM_CALLTYPE SetFade(double f);
        virtual VCOMError VCOM_CALLTYPE SetDelay(double d);

        virtual VCOMError VCOM_CALLTYPE     GetVisualValueCount(size_t& outCount);
        virtual VCOMError VCOM_CALLTYPE     GetVisualValueAt(size_t at, IGdtfMacroVisualValue**  outVal);
        virtual VCOMError VCOM_CALLTYPE     CreateVisualValue(DmxValue dmxVal, IGdtfDmxChannelFunction* channelFunction, IGdtfMacroVisualValue ** outVal);

        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
        virtual void*	  VCOM_CALLTYPE     GetBoundObject();

    private:
        SceneData::GdtfMacroVisualStep* fMacroVisualStep;

    public:
        void					        SetPointer(SceneData::GdtfMacroVisualStep* macroVisualStep);
        SceneData::GdtfMacroVisualStep*	GetPointer();

    };

    const VWIID IID_GdtfMacroVisualStep = { 0x2a3d0a50, 0x9b48, 0x4c6d,{ 0x81, 0x03, 0xaa, 0xfd, 0x0b, 0x29, 0xc1, 0x57 } };
}
//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfMacroDMXStepImpl : public VCOMImpl<IGdtfMacroDMXStep>
    {
    public:
        CGdtfMacroDMXStepImpl();
        virtual ~CGdtfMacroDMXStepImpl();

        virtual VCOMError VCOM_CALLTYPE     GetDuration(double & outDur);

        virtual VCOMError VCOM_CALLTYPE GetDMXValueCount(size_t & count);
        virtual VCOMError VCOM_CALLTYPE GetDMXValueAt(size_t at, IGdtfMacroDMXValue**  outVal);
        virtual VCOMError VCOM_CALLTYPE CreateDMXValue(DmxValue dmxVal, IGdtfDmxChannel* dmxChannel, IGdtfMacroDMXValue** outVal);

        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
        virtual void*	  VCOM_CALLTYPE     GetBoundObject();
    private:
        SceneData::GdtfMacroDMXStep* fMacroDMXStep;

    public:
        void					        SetPointer(SceneData::GdtfMacroDMXStep* MacroDMXStep);
        SceneData::GdtfMacroDMXStep*	GetPointer();        
    };

    const VWIID IID_GdtfMacroDMXStep = { 0x89d397b7, 0x0b93, 0x4670,{ 0x93, 0xfb, 0x62, 0x9a, 0xc7, 0x90, 0x19, 0xe1 } };
}

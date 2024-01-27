//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "GDTFManager.h"

namespace VectorworksMVR
{
    class CGdtfCRIGroupImpl : public VCOMImpl<IGdtfCRIGroup>
    {
    public:
        CGdtfCRIGroupImpl();
        virtual ~CGdtfCRIGroupImpl();
        
        virtual VCOMError VCOM_CALLTYPE GetColorTemperature(double& outVal);
        virtual VCOMError VCOM_CALLTYPE SetColorTemperature(double value);
        
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetCRICount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE CreateCRI(EGdtfColorSample ces, Sint32 colorTemp, VectorworksMVR::IGdtfCRI **outVal);
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetCRIAt(size_t at, VectorworksMVR::IGdtfCRI** value);

        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
        virtual void*	  VCOM_CALLTYPE     GetBoundObject();

    private:
        SceneData::GdtfCRIGroup* fCRIGroup;

    public:
        void					    SetPointer(SceneData::GdtfCRIGroup* CRIGroup);
        SceneData::GdtfCRIGroup*	GetPointer();

    };

    const VWIID IID_GdtfCRIGroup = { 0x98bbf990, 0xa7e1, 0x4881,{ 0xb2, 0x7c, 0xdd, 0xce, 0x0e, 0x71, 0xf5, 0xb6 } };
}


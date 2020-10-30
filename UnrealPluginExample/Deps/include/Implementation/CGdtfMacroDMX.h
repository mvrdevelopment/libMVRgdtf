//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "GDTFManager.h"

namespace VectorworksMVR
{    
    class CGdtfMacroDMXImpl : public VCOMImpl<IGdtfMacroDMX>
    {
    public:
        CGdtfMacroDMXImpl();
        virtual ~CGdtfMacroDMXImpl();
        
        virtual VCOMError VCOM_CALLTYPE    GetStepCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE    GetStepAt(size_t at, IGdtfMacroDMXStep** outStep);                                           
        virtual VCOMError VCOM_CALLTYPE    CreateStep(double& macroDuration, IGdtfMacroDMXStep** outStep);
        
        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
        virtual void*	  VCOM_CALLTYPE     GetBoundObject();

    private:
        SceneData::GdtfMacroDMX* fMacroDMX;        

    public:
        void					    SetPointer(SceneData::GdtfMacroDMX* macroDMX);
        SceneData::GdtfMacroDMX*	GetPointer();
    };

    const VWIID IID_GdtfMacroDMX = { 0x0e38a244, 0x935b, 0x41f1, {0xad, 0x1a, 0xce, 0xfc, 0x70, 0x55, 0xa3, 0xcf}};
}
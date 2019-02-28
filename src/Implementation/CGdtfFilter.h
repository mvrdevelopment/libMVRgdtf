//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    class CGdtfFilterImpl : public VCOMImpl<IGdtfFilter>
    {
    public:
        CGdtfFilterImpl();
        virtual ~CGdtfFilterImpl();

        // Getter
        virtual MvrString VCOM_CALLTYPE     GetName();
        virtual VCOMError VCOM_CALLTYPE     GetColor(CieColor& outVal);
        // Setter
        virtual VCOMError VCOM_CALLTYPE     SetName(MvrString name);
        virtual VCOMError VCOM_CALLTYPE     SetColor(CieColor val);
        //
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetMeasurementCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE CreateMeasurement(VectorworksMVR::IGdtfMeasurement** outVal);
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetMeasurementAt(size_t at, VectorworksMVR::IGdtfMeasurement** value);
        //

        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
        virtual void*	  VCOM_CALLTYPE     GetBoundObject();

    private:
        SceneData::GdtfFilter*  fFilter;

    public:
        void					SetPointer(SceneData::GdtfFilter* val);
        SceneData::GdtfFilter*	GetPointer();

    };

    const VWIID IID_GdtfFilter  = { 0x66f1d4b2, 0xf040, 0x4d4e, {0xb1, 0x54, 0x4c, 0xcb, 0x2b, 0x68, 0xc2, 0xc0}};
}

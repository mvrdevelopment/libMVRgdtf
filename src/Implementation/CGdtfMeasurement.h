//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    class CGdtfMeasurementImpl : public VCOMImpl<IGdtfMeasurement>
    {
    public:
        CGdtfMeasurementImpl();
        virtual ~CGdtfMeasurementImpl();
        
        // Getter
        virtual VCOMError VCOM_CALLTYPE    GetPhysical(double& outVal);
        virtual VCOMError VCOM_CALLTYPE    GetLuminousIntensity(double& outVal);
        virtual VCOMError VCOM_CALLTYPE    GetTransmission(double& outVal);
        virtual VCOMError VCOM_CALLTYPE    GetInterpolationTo(EGdtfInterpolationTo& outVal);
        // Setter               
        virtual VCOMError VCOM_CALLTYPE    SetPhysical(double val);
        virtual VCOMError VCOM_CALLTYPE    SetLuminousIntensity(double val);
        virtual VCOMError VCOM_CALLTYPE    SetTransmission(double val);
        virtual VCOMError VCOM_CALLTYPE    SetInterpolationTo(EGdtfInterpolationTo val);        
        //
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetMeasurementPointCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE CreateMeasurementPoint(VectorworksMVR::IGdtfMeasurementPoint** outVal);
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetMeasurementPointAt(size_t at, VectorworksMVR::IGdtfMeasurementPoint** value);
        //
        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
        virtual void*	  VCOM_CALLTYPE     GetBoundObject();

    private:
        SceneData::GdtfMeasurement* fMeasurement;

    public:
        void					    SetPointer(SceneData::GdtfMeasurement* measurement);
        SceneData::GdtfMeasurement*	GetPointer();

    };

    const VWIID IID_GdtfMeasurement = { 0x02d62b0e, 0x4ef3, 0x4eb8, {0x84, 0x70, 0x35, 0x2f, 0x23, 0x28, 0xc2, 0x19}};
}


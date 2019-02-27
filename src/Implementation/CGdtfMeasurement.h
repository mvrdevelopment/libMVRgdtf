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

        // Measurement_Optional virtual VCOMError VCOM_CALLTYPE     GetMeasurementCount(size_t& outCount);
        // Measurement_Optional virtual VCOMError VCOM_CALLTYPE     GetMeasurementAt(size_t at, IGdtfMeasurement**  outMeasurement);
        // Measurement_Optional virtual VCOMError VCOM_CALLTYPE     CreateMeasurement (IGdtfMeasurement** outMeasurement);		

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


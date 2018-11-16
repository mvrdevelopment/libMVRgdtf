//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "GDTFManager.h"

namespace VectorworksMVR
{
    class CGdtfRDMSensorNotificationImpl : public VCOMImpl<IGdtfRDMSensorNotification>
    {
    public:
        CGdtfRDMSensorNotificationImpl();
        virtual ~CGdtfRDMSensorNotificationImpl();
                
        virtual VCOMError VCOM_CALLTYPE GetSensorOffset(Sint32& outVal);
        virtual VCOMError VCOM_CALLTYPE SetSensorOffset(Sint32 value);

        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetValueSensorCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE CreateValueSensor(Sint32 value,
                                                                        Sint32 lowest,
                                                                        Sint32 highest,
                                                                        Sint32 recorded,
                                                                        EGdtf_RDMValue_ThresholdOperator thresholdOperator,
                                                                        IGdtfRDMValueSensor** outVal);

        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetValueSensorAt(size_t at, IGdtfRDMValueSensor** value); 

        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
        virtual void*	  VCOM_CALLTYPE     GetBoundObject();        
    private:
        SceneData::GdtfRDMSensorNotification* fSensorNotification;

    public:
        void			                        SetPointer(SceneData::GdtfRDMSensorNotification* value);
        SceneData::GdtfRDMSensorNotification*	GetPointer();
    };

    const VWIID IID_GdtfRDMSensorNotification = { 0x4feb6a24, 0x356d, 0x48c6, {0xb9, 0x26, 0x2b, 0x27, 0x9c, 0x61, 0x99, 0xd8}};
}

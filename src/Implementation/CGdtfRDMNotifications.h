//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "GDTFManager.h"

namespace VectorworksMVR
{
    class CGdtfRDMNotificationsImpl : public VCOMImpl<IGdtfRDMNotifications>
    {
    public:
        CGdtfRDMNotificationsImpl();
        virtual ~CGdtfRDMNotificationsImpl();
        
        virtual VCOMError GetRDMAbsentNotification(VectorworksMVR::IGdtfRDMAbsentNotification ** outRDMAbsentNotification);
        virtual VCOMError SetRDMAbsentNotification(IGdtfRDMAbsentNotification * newRDMAbsentNotification);

        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetRDMParameterNotificationCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE CreateRDMParameterNotification(Sint32 PID, VectorworksMVR::IGdtfRDMParameterNotification** outVal);
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetRDMParameterNotificationAt(size_t at, VectorworksMVR::IGdtfRDMParameterNotification** value);        
        
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetSensorNotificationCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE CreateSensorNotification(Sint32 sensorOffset, VectorworksMVR::IGdtfRDMSensorNotification**outVal);
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetSensorNotificationAt(size_t at, VectorworksMVR::IGdtfRDMSensorNotification **SensorNotification);        

        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
        virtual void*	  VCOM_CALLTYPE     GetBoundObject();

    private:
        SceneData::GdtfRDMNotifications* fNotifications;

    public:
        void			    SetPointer(SceneData::GdtfRDMNotifications* value);
        SceneData::GdtfRDMNotifications*	GetPointer();
    };

    const VWIID IID_GdtfRDMNotifications = { 0x4799a20f, 0x16e1, 0x45c2, {0xae, 0x7e, 0x3f, 0xac, 0x61, 0xe0, 0xae, 0x06}};
}



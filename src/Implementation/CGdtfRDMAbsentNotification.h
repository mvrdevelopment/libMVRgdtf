//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "CGeometryProviderWrapper.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    class CGdtfRDMAbsentNotificationImpl : public VectorworksMVR::VCOMImpl<IGdtfRDMAbsentNotification>
    {
    public:
        CGdtfRDMAbsentNotificationImpl();
        virtual ~CGdtfRDMAbsentNotificationImpl();

        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
        virtual void*	  VCOM_CALLTYPE     GetBoundObject();

    private:
        SceneData::GdtfRDMAbsentNotification* fAbsentNotification;

    public:
        void  SetPointer(SceneData::GdtfRDMAbsentNotification* value);
        SceneData::GdtfRDMAbsentNotification*	GetPointer();
    };
    
    const VWIID IID_GdtfRDMAbsentNotification = { 0xc5dd5ec0, 0x8d32, 0x414d, {0xb7, 0xcd, 0x7b, 0x89, 0x4c, 0xe3, 0xc2, 0xd9}};
}




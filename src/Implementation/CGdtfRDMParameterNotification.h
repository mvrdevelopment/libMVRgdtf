//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "CGeometryProviderWrapper.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    class CGdtfRDMParameterNotificationImpl : public VectorworksMVR::VCOMImpl<IGdtfRDMParameterNotification>
    {
    public:
        CGdtfRDMParameterNotificationImpl();
        virtual ~CGdtfRDMParameterNotificationImpl();

        virtual VCOMError VCOM_CALLTYPE GetPID(Sint32& outVal);
        virtual VCOMError VCOM_CALLTYPE SetPID(Sint32 value);        
        // Arrays
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetRDMParameterValueCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE CreateRDMParameterValue(EGdtfObjectType type, VectorworksMVR::IGdtfRDMParameterValue** outVal);
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetRDMParameterValueAt(size_t at, VectorworksMVR::IGdtfRDMParameterValue** value);
        //
        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
        virtual void*	  VCOM_CALLTYPE     GetBoundObject();

    private:
        SceneData::GdtfRDMParameterNotification* fParamNotification;

    public:
        void			                            SetPointer(SceneData::GdtfRDMParameterNotification* value);
        SceneData::GdtfRDMParameterNotification*	GetPointer();
    };

    const VWIID IID_GdtfRDMParameterNotification =  { 0x2f26097e, 0x1318, 0x4e1e, {0xac, 0x33, 0x3a, 0x04, 0x8a, 0xfb, 0xe1, 0x38}};
}



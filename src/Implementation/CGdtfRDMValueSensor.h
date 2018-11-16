//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "GDTFManager.h"

namespace VectorworksMVR
{
    class CGdtfRDMValueSensorImpl : public VCOMImpl<IGdtfRDMValueSensor>
    {
    public:
        CGdtfRDMValueSensorImpl();
        virtual ~CGdtfRDMValueSensorImpl();
        
        // Getter        
        virtual VCOMError VCOM_CALLTYPE  GetValue(Sint32& outVal);
        virtual VCOMError VCOM_CALLTYPE  GetLowest(Sint32& outVal);
        virtual VCOMError VCOM_CALLTYPE  GetHighest(Sint32& outVal);
        virtual VCOMError VCOM_CALLTYPE  GetRecorded(Sint32& outVal);
        virtual VCOMError VCOM_CALLTYPE  GetThresholdOperator(EGdtf_RDMValue_ThresholdOperator& outVal);
        // Setter       
        virtual VCOMError VCOM_CALLTYPE  SetValue(Sint32 val);
        virtual VCOMError VCOM_CALLTYPE  SetLowest(Sint32 val);
        virtual VCOMError VCOM_CALLTYPE  SetHighest(Sint32 val);
        virtual VCOMError VCOM_CALLTYPE  SetRecorded(Sint32 val);
        virtual VCOMError VCOM_CALLTYPE  SetThresholdOperator(EGdtf_RDMValue_ThresholdOperator val);
        //
        virtual VCOMError VCOM_CALLTYPE   BindToObject(void* objAddr);
        virtual void*	  VCOM_CALLTYPE   GetBoundObject();

    private:
        SceneData::GdtfRDMValueSensor* fRDMValueSensor;

    public:
        void			                SetPointer(SceneData::GdtfRDMValueSensor* RDMValueSensor);
        SceneData::GdtfRDMValueSensor*	GetPointer();
    };

    const VWIID IID_GdtfRDMValueSensor = { 0xed2ad1af, 0x532d, 0x4698,{ 0x89, 0x24, 0x4d, 0x33, 0xa0, 0xd1, 0xa6, 0x59 } };
}



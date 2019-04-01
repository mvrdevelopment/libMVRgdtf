//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "GDTFManager.h"

namespace VectorworksMVR
{
    class CGdtf_FTRDMImpl : public VCOMImpl<IGdtf_FTRDM>
    {
    public:
        CGdtf_FTRDMImpl();
        virtual ~CGdtf_FTRDMImpl();
        
        virtual VCOMError VCOM_CALLTYPE GetManufacturerID(size_t& outVal);        
        virtual VCOMError VCOM_CALLTYPE GetDeviceModelID(size_t& outVal);
		
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetSoftwareVersionIDCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE CreateSoftwareVersionID(size_t value, VectorworksMVR::IGdtfSoftwareVersionID** outVal);
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetSoftwareVersionIDAt(size_t at, VectorworksMVR::IGdtfSoftwareVersionID** value);

        virtual VCOMError VCOM_CALLTYPE SetManufacturerID(size_t value);
        virtual VCOMError VCOM_CALLTYPE SetDeviceModelID(size_t value);


        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
        virtual void*	  VCOM_CALLTYPE     GetBoundObject();
    private:
        SceneData::GdtfFTRDM* f_FtRDM;

    public:
        void			        SetPointer(SceneData::GdtfFTRDM* value);
        SceneData::GdtfFTRDM*	GetPointer();
    };

    const VWIID IID_GdtfTRDM = { 0xfe83bd9c, 0xea72, 0x4ed5, {0x90, 0xce, 0x2d, 0x93, 0x4f, 0xc1, 0x0e, 0xb7}};
}
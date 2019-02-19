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
        
        virtual VCOMError VCOM_CALLTYPE GetManufacturerID(Sint32& outVal);        
        virtual VCOMError VCOM_CALLTYPE GetDeviceModelID(Sint32& outVal);
		
		virtual VCOMError VCOM_CALLTYPE GetSoftwareIDAt(size_t at, Sint32& outVal);
		virtual VCOMError VCOM_CALLTYPE GetSoftwareIDCount(size_t& count);

        virtual VCOMError VCOM_CALLTYPE SetManufacturerID(Sint32 value);
        virtual VCOMError VCOM_CALLTYPE SetDeviceModelID(Sint32 value);
        virtual VCOMError VCOM_CALLTYPE AddSoftwareID(Sint32 softID);        

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
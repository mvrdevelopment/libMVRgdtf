//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"


namespace VectorworksMVR
{
    class CGdtfSoftwareVersionIDImpl : public VCOMImpl<IGdtfSoftwareVersionID>
    {
    public:
        CGdtfSoftwareVersionIDImpl();
        virtual ~CGdtfSoftwareVersionIDImpl();

        // SoftwareVersionID_Optional virtual VCOMError VCOM_CALLTYPE     GetSoftwareVersionIDCount(size_t& outCount); // XXX
        // SoftwareVersionID_Optional virtual VCOMError VCOM_CALLTYPE     GetSoftwareVersionIDAt(size_t at, IGdtfSoftwareVersionID**  outSoftwareVersionID);
        // SoftwareVersionID_Optional virtual VCOMError VCOM_CALLTYPE     CreateSoftwareVersionID (IGdtfSoftwareVersionID** outSoftwareVersionID);		

        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
        virtual void*	  VCOM_CALLTYPE     GetBoundObject();

    private:
        SceneData::GdtfSoftwareVersionID* fSoftwareVersionID;

    public:
        void					            SetPointer(SceneData::GdtfSoftwareVersionID* SoftwareVersionID);
        SceneData::GdtfSoftwareVersionID*	GetPointer();

    };

    const VWIID IID_GdtfSoftwareVersionID = { 0xf06292b8, 0x4d57, 0x4c8c, {0xbc, 0xd1, 0xfc, 0x57, 0x31, 0xc5, 0x31, 0xe3}};
}


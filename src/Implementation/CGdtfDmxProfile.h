//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    class CGdtfDMXProfileImpl : public VCOMImpl<IGdtfDMXProfile>
    {
    public:
        CGdtfDMXProfileImpl();
        virtual ~CGdtfDMXProfileImpl();

        virtual MvrString VCOM_CALLTYPE		GetName();
        virtual VCOMError VCOM_CALLTYPE		SetName(MvrString name);

        virtual VCOMError VCOM_CALLTYPE		GetPointCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE		GetPointAt(size_t at, IGdtfPoint** point);
        virtual VCOMError VCOM_CALLTYPE		CreatePoint(double DMXPercentage, double CFC3, double CFC2, double CFC1, double CFC0, IGdtfPoint** point);

        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
        virtual void*	  VCOM_CALLTYPE     GetBoundObject();

    private:
        SceneData::GdtfDMXProfile* fDMXProfile;

    public:
        void				        SetPointer(SceneData::GdtfDMXProfile* dmxProfile);
        SceneData::GdtfDMXProfile*	GetPointer();
    };

    const VWIID IID_GdtfDMXProfile = { 0x69cd3df3, 0x8244, 0x4888, {0xa5, 0x5a, 0x09, 0x07, 0x59, 0x6b, 0x03, 0xc8}};
}


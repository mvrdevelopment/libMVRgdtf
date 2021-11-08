//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    class CGdtfPointImpl : public VCOMImpl<IGdtfPoint>
    {
    public:
        CGdtfPointImpl();
        virtual ~CGdtfPointImpl();

        virtual VCOMError VCOM_CALLTYPE		GetDMXPercentage(double& dmxPercentage);
        virtual VCOMError VCOM_CALLTYPE		GetCFC3(double& cfc3);
        virtual VCOMError VCOM_CALLTYPE		GetCFC2(double& cfc2);
        virtual VCOMError VCOM_CALLTYPE		GetCFC1(double& cfc1);
        virtual VCOMError VCOM_CALLTYPE		GetCFC0(double& cfc0);


        virtual VCOMError VCOM_CALLTYPE		SetDMXPercentage(double dmxPercentage);
        virtual VCOMError VCOM_CALLTYPE		SetCFC3(double cfc3);
        virtual VCOMError VCOM_CALLTYPE		SetCFC2(double cfc2);
        virtual VCOMError VCOM_CALLTYPE		SetCFC1(double cfc1);
        virtual VCOMError VCOM_CALLTYPE		SetCFC0(double cfc0);

        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
        virtual void*	  VCOM_CALLTYPE     GetBoundObject();

    private:
        SceneData::GdtfPoint* fPoint;

    public:
        void				    SetPointer(SceneData::GdtfPoint* point);
        SceneData::GdtfPoint*	GetPointer();
    };

    const VWIID IID_GdtfPoint = { 0x95c73846, 0x21dc, 0x4330, {0xa3, 0x11, 0x34, 0x28, 0xf0, 0xe5, 0xcf, 0xb4}};
    
}


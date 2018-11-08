//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfPhysicalEmitterImpl : public VCOMImpl<IGdtfPhysicalEmitter>
    {
    public:
        CGdtfPhysicalEmitterImpl();
        virtual ~CGdtfPhysicalEmitterImpl();
        
        virtual MvrString VCOM_CALLTYPE     GetName();
        virtual VCOMError VCOM_CALLTYPE     GetColor(CieColor& color);
        
        virtual VCOMError VCOM_CALLTYPE     GetMeasurementPointCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE     GetMeasurementPointAt(size_t at, IGdtfMeasurementPoint** measurementPoint);
		virtual VCOMError VCOM_CALLTYPE     CreateMeasurementPoint(double wavelength, double energy, IGdtfMeasurementPoint** measurementPoint);
		
        virtual VCOMError VCOM_CALLTYPE     SetName(MvrString name);
        virtual VCOMError VCOM_CALLTYPE     SetColor(CieColor & color);

		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
		virtual void*	  VCOM_CALLTYPE     GetBoundObject();
    private:
        SceneData::GdtfPhysicalEmitter* fEmitter;
    public:
        void setPointer(SceneData::GdtfPhysicalEmitter* emitter);
        SceneData::GdtfPhysicalEmitter* GetPointer();
        
    };
    const VWIID IID_GdtfPhysicalEmitter = { 0xa0d95810, 0x28c7, 0x40fb, {0xbe, 0x9b, 0xa6, 0x8f, 0xc4, 0x78, 0xf3, 0x55}};

    
    
}


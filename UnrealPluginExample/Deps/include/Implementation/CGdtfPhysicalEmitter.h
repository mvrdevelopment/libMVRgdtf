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
        
        virtual VCOMError VCOM_CALLTYPE     GetMeasurementCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE     GetMeasurementAt(size_t at, IGdtfMeasurement** outVal);
		virtual VCOMError VCOM_CALLTYPE     CreateMeasurement(IGdtfMeasurement** outVal);
		virtual MvrString VCOM_CALLTYPE     GetDiodePart();
        virtual VCOMError VCOM_CALLTYPE     GetDominantWaveLength(double& outVal);
        

        virtual VCOMError VCOM_CALLTYPE     SetName(MvrString name);
        virtual VCOMError VCOM_CALLTYPE     SetColor(CieColor & color);
		virtual VCOMError VCOM_CALLTYPE     SetDiodePart(MvrString val);
        virtual VCOMError VCOM_CALLTYPE     SetDominantWaveLength(double val);

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


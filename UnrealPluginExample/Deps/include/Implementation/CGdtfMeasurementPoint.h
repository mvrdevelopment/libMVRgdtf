//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfMeasurementPointImpl : public VCOMImpl<IGdtfMeasurementPoint>
    {
    public:
        CGdtfMeasurementPointImpl();
        virtual ~CGdtfMeasurementPointImpl();
        
        virtual VCOMError VCOM_CALLTYPE     GetWaveLength(double& wavelength);  
        virtual VCOMError VCOM_CALLTYPE     GetEnergy(double& energy);

		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
		virtual void*	  VCOM_CALLTYPE     GetBoundObject();

        virtual VCOMError VCOM_CALLTYPE     SetWaveLength(double wavelength);  
        virtual VCOMError VCOM_CALLTYPE     SetEnergy(double energy);

	private:
        SceneData::GdtfMeasurementPoint* fMeasurementPoint;
    public:
        void setPointer(SceneData::GdtfMeasurementPoint* measurementPoint);
        
    };
    const VWIID IID_GdtfMeasurementPoint = { 0xf8f07a48, 0xc2fe, 0x4ec9, {0x94, 0xec, 0x4e, 0x7b, 0x36, 0x2c, 0x5e, 0x62}};

    
    
}

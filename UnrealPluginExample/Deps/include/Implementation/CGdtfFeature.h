//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfFeatureImpl : public VCOMImpl<IGdtfFeature>
    {
    public:
        CGdtfFeatureImpl();
        virtual ~CGdtfFeatureImpl();
        
        virtual MvrString VCOM_CALLTYPE     GetName();
		
		virtual VCOMError VCOM_CALLTYPE		GetAttributeCount(size_t& count);
		virtual VCOMError VCOM_CALLTYPE		GetAttributeAt(size_t at, IGdtfAttribute** attribute);
        virtual VCOMError VCOM_CALLTYPE     GetFeatureGroup(IGdtfFeatureGroup** group);


        virtual VCOMError VCOM_CALLTYPE     SetName(MvrString name);        
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
		virtual void*	  VCOM_CALLTYPE     GetBoundObject();
		
    private:
        SceneData::GdtfFeature* fFeature;
	public:
		void						SetPointer(SceneData::GdtfFeature* feature);
		SceneData::GdtfFeature*		GetPointer();
    };
    const VWIID IID_GdtfFeature = { 0x2b2d2092, 0xfbfb, 0x4e7d, {0xa7, 0x24, 0x70, 0xaf, 0x3c, 0x96, 0x45, 0x6a}};

}

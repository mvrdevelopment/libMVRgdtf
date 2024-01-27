//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfFeatureGroupImpl : public VCOMImpl<IGdtfFeatureGroup>
    {
    public:
        CGdtfFeatureGroupImpl();
        virtual ~CGdtfFeatureGroupImpl();

		virtual VCOMError VCOM_CALLTYPE     CreateFeature(MvrString name, IGdtfFeature** feature);
        
        virtual MvrString VCOM_CALLTYPE     GetName();
        virtual MvrString VCOM_CALLTYPE     GetPrettyName();
        
        virtual VCOMError VCOM_CALLTYPE     GetFeatureCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE     GetFeatureAt(size_t at, IGdtfFeature** feature);

		virtual VCOMError VCOM_CALLTYPE		SetPrettyName(MvrString name);				
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
		virtual void*	  VCOM_CALLTYPE     GetBoundObject();
		
    private:
        SceneData::GdtfFeatureGroup* fFeatureGroup;
        
    public:
        void setPointer(SceneData::GdtfFeatureGroup* featureGroup);
        
    };
    const VWIID IID_GdtfFeatureGroup = { 0xb5a67ae5, 0x504d, 0x4cce, {0x84, 0xf8, 0x32, 0x84, 0x0c, 0xfe, 0x03, 0xee}};

}

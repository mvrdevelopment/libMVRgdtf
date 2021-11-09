//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfAttributeImpl : public VCOMImpl<IGdtfAttribute>
    {
    public:
        CGdtfAttributeImpl();
        virtual ~CGdtfAttributeImpl();
        
        virtual MvrString VCOM_CALLTYPE     GetName();
        virtual MvrString VCOM_CALLTYPE     GetPrettyName();
        virtual VCOMError VCOM_CALLTYPE     GetActivationGroup(IGdtfActivationGroup** activationGroup);
        virtual VCOMError VCOM_CALLTYPE     GetFeature(IGdtfFeature** feature);
        virtual VCOMError VCOM_CALLTYPE     GetMainAttribute(IGdtfAttribute** mainAttrib);
        virtual VCOMError VCOM_CALLTYPE     GetPhysicalUnit(GdtfDefines::EGdtfPhysicalUnit& unit);
        virtual VCOMError VCOM_CALLTYPE     GetColor(CieColor & col);
		
		virtual VCOMError VCOM_CALLTYPE     SetActivationGroup(IGdtfActivationGroup* activationGroup);
		virtual VCOMError VCOM_CALLTYPE     SetFeature(IGdtfFeature* feature);
        virtual VCOMError VCOM_CALLTYPE     SetMainAttribute(IGdtfAttribute* mainAttrib);
        virtual VCOMError VCOM_CALLTYPE     SetPhysicalUnit(GdtfDefines::EGdtfPhysicalUnit unit);
        virtual VCOMError VCOM_CALLTYPE     SetColor(const CieColor & col);

        virtual VCOMError VCOM_CALLTYPE 	GetSubPhysicalUnitCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE 	GetSubPhysicalUnitAt(size_t at, VectorworksMVR::IGdtfSubPhysicalUnit** outSubPhysicalUnit);
        virtual VCOMError VCOM_CALLTYPE 	CreateSubPhysicalUnit(GdtfDefines::EGdtfSubPhysicalUnitType type, VectorworksMVR::IGdtfSubPhysicalUnit** outSubPhysicalUnit);
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
		virtual void*	  VCOM_CALLTYPE     GetBoundObject();
		
    private:
        SceneData::GdtfAttribute* fAttribute;
    public:
        void						SetPointer(SceneData::GdtfAttribute* attribute);
		SceneData::GdtfAttribute*	GetPointer();
        
    };
    const VWIID IID_GdtfAttribute = { 0x25f5680d, 0x6f19, 0x4bd8, {0xa0, 0x79, 0xcf, 0x9d, 0x18, 0x67, 0x91, 0xf6}};

}

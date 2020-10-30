//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfWheelSlotImpl : public VCOMImpl<IGdtfWheelSlot>
    {
    public:
        CGdtfWheelSlotImpl();
        virtual ~CGdtfWheelSlotImpl();
        
        virtual MvrString VCOM_CALLTYPE     GetName();
        virtual VCOMError VCOM_CALLTYPE     GetColor(CieColor& color);
        virtual MvrString VCOM_CALLTYPE     GetGobo();
		virtual MvrString VCOM_CALLTYPE     GetGoboFileFullPath();
        virtual VCOMError VCOM_CALLTYPE     GetFilter(IGdtfFilter** outVal);
		
        virtual VCOMError VCOM_CALLTYPE		SetName(MvrString name);				
		virtual VCOMError VCOM_CALLTYPE     SetColor(const CieColor& color);
		virtual VCOMError VCOM_CALLTYPE     SetGobo(MvrString path);
        virtual VCOMError VCOM_CALLTYPE     SetFilter(IGdtfFilter* val);
		
        virtual VCOMError VCOM_CALLTYPE     GetPrismFacetCount(size_t& outCount);
        virtual VCOMError VCOM_CALLTYPE     GetPrismFacetAt(size_t& at, IGdtfWheelSlotPrismFacet** outPosition);
		virtual VCOMError VCOM_CALLTYPE     CreatePrismFacet(const STransformMatrix& transformMatrix, IGdtfWheelSlotPrismFacet** outFacet);

        virtual VCOMError VCOM_CALLTYPE     GetAnimationSystem(IGdtfWheelSlotAnimationSystem** outAnimationSystem);
		virtual VCOMError VCOM_CALLTYPE     CreateAnimationSystem(double p1_X, double p1_Y, double p2_X, double p2_Y, double p3_X, double p3_Y, double radius, IGdtfWheelSlotAnimationSystem**   outAnimationSystem);
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
		virtual void*	  VCOM_CALLTYPE     GetBoundObject();

	private:
        SceneData::GdtfWheelSlot* fWheelSlot;
        
    public:
        void    setPointer(SceneData::GdtfWheelSlot* wheelSlot);
    };
    const VWIID IID_GdtfWheelSlot = { 0xc093e485, 0x87e7, 0x4412, {0xbe, 0x20, 0x63, 0x4b, 0x6a, 0xe2, 0xdf, 0xf6}};

}

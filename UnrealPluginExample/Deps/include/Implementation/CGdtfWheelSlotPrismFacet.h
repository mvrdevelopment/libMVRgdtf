//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfWheelSlotPrismFacetImpl : public VCOMImpl<IGdtfWheelSlotPrismFacet>
    {
    public:
        CGdtfWheelSlotPrismFacetImpl();
        virtual ~CGdtfWheelSlotPrismFacetImpl();
        
        virtual VCOMError VCOM_CALLTYPE     GetColor(CieColor& color);
        virtual VCOMError VCOM_CALLTYPE     GetTransformMatrix(STransformMatrix& transformMatrix);
		
		virtual VCOMError VCOM_CALLTYPE     SetColor(const CieColor& color);
        virtual VCOMError VCOM_CALLTYPE     SetTransformMatrix(const STransformMatrix& transformMatrix);
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
		virtual void*	  VCOM_CALLTYPE     GetBoundObject();
		
    private:
        SceneData::GdtfWheelSlotPrismFacet* fPrismFacet;
    public:
        void setPointer(SceneData::GdtfWheelSlotPrismFacet* prismFacet);
    };
    const VWIID IID_GdtfWheelSlotPrismFacet = { 0x7c1744b3, 0x8b29, 0x4d44, {0xa8, 0xac, 0x36, 0x85, 0xf4, 0xc2, 0xb9, 0xb1}};

}

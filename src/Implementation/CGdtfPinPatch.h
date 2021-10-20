//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "GDTFManager.h"
#include "Include/IMediaRessourceVectorInterface.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfPinPatchImpl : public VCOMImpl<IGdtfPinPatch>
    {
    public:
        CGdtfPinPatchImpl();
        virtual ~CGdtfPinPatchImpl();
        
        virtual VCOMError VCOM_CALLTYPE     GetLinkedWiringObject(IGdtfGeometry** toWiringObject);
		virtual VCOMError VCOM_CALLTYPE     GetFromPin(size_t& fromPin);
		virtual VCOMError VCOM_CALLTYPE     GetToPin(size_t& toPin);

		virtual VCOMError VCOM_CALLTYPE     SetLinkedWiringObject(IGdtfGeometry* toWiringObject);
        virtual VCOMError VCOM_CALLTYPE     SetFromPin(size_t fromPin);
        virtual VCOMError VCOM_CALLTYPE     SetToPin(size_t toPin);

		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
		virtual void*	  VCOM_CALLTYPE     GetBoundObject();
		
    private:
        SceneData::GdtfPinPatch* fPinPatch;
    public:
        void SetPointer(SceneData::GdtfPinPatch* pinPatch);
    };
    const VWIID IID_GdtfPinPatch = { 0x9dff4944, 0x9f91, 0x4b4e, {0xbf, 0x7d, 0x3c, 0xe3, 0x24, 0x88, 0xdc, 0xed}};
}

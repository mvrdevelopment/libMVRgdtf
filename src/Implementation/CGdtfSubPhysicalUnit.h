//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "GDTFManager.h"
#include "Include/IMediaRessourceVectorInterface.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfSubPhysicalUnitImpl : public VCOMImpl<IGdtfSubPhysicalUnit>
    {
    public:
        CGdtfSubPhysicalUnitImpl();
        virtual ~CGdtfSubPhysicalUnitImpl();
        
        virtual VCOMError VCOM_CALLTYPE     GetType(GdtfDefines::EGdtfSubPhysicalUnitType& type);
		virtual VCOMError VCOM_CALLTYPE     GetPhysicalFrom(double& physicalFrom);
		virtual VCOMError VCOM_CALLTYPE     GetPhysicalTo(double& physicalTo);
        virtual VCOMError VCOM_CALLTYPE     GetPhysicalUnit(GdtfDefines::EGdtfPhysicalUnit& unit);

		virtual VCOMError VCOM_CALLTYPE     SetType(GdtfDefines::EGdtfSubPhysicalUnitType type);
        virtual VCOMError VCOM_CALLTYPE     SetPhysicalFrom(double physicalFrom);
        virtual VCOMError VCOM_CALLTYPE     SetPhysicalTo(double physicalTo);
        virtual VCOMError VCOM_CALLTYPE     SetPhysicalUnit(GdtfDefines::EGdtfPhysicalUnit& unit);

		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
		virtual void*	  VCOM_CALLTYPE     GetBoundObject();
		
    private:
        SceneData::GdtfSubPhysicalUnit* fSubPhysicalUnit;
    public:
        void                            SetPointer(SceneData::GdtfSubPhysicalUnit* subPhysicalUnit);
        SceneData::GdtfSubPhysicalUnit* GetPointer();  
    };
    const VWIID IID_GdtfSubPhysicalUnit = { 0x1705fb6d, 0xe589, 0x40c0, {0xa9, 0xee, 0x8d, 0x7b, 0xf5, 0x3a, 0x54, 0xc8}};
}

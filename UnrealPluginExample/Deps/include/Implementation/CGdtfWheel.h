//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfWheelImpl : public VCOMImpl<IGdtfWheel>
    {
    public:
        CGdtfWheelImpl();
        virtual ~CGdtfWheelImpl();
        
        virtual MvrString VCOM_CALLTYPE     GetName();        
        
        virtual VCOMError VCOM_CALLTYPE     GetWheelSlotCount(size_t& outCount);
        virtual VCOMError VCOM_CALLTYPE     GetWheelSlotAt(size_t at, IGdtfWheelSlot** outSlot);
		virtual VCOMError VCOM_CALLTYPE     CreateWheelSlot(MvrString name, IGdtfWheelSlot** outSlot);
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
		virtual void*	  VCOM_CALLTYPE     GetBoundObject();
		
    private:
        SceneData::GdtfWheel* fWheel;
        
    public:
        void					SetPointer(SceneData::GdtfWheel* wheel);
		SceneData::GdtfWheel*	GetPointer();
        
    };
    
    const VWIID IID_GdtfWheel = { 0x09787bcb, 0x4526, 0x4e09, {0xb7, 0xca, 0x0b, 0xd2, 0x70, 0x6c, 0xb5, 0xfd}};
    
}

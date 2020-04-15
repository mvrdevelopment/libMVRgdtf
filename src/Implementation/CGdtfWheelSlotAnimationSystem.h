//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfWheelSlotAnimationSystemImpl : public VCOMImpl<IGdtfWheelSlotAnimationSystem>
    {
    public:
        CGdtfWheelSlotAnimationSystemImpl();
        virtual ~CGdtfWheelSlotAnimationSystemImpl();
        
        virtual VCOMError VCOM_CALLTYPE     GetP1_X(double& p1_X);
        virtual VCOMError VCOM_CALLTYPE     GetP1_Y(double& p1_Y);
        virtual VCOMError VCOM_CALLTYPE     GetP2_X(double& p2_X);
        virtual VCOMError VCOM_CALLTYPE     GetP2_Y(double& p2_Y);
        virtual VCOMError VCOM_CALLTYPE     GetP3_X(double& p3_X);
        virtual VCOMError VCOM_CALLTYPE     GetP3_Y(double& p3_Y);
        virtual VCOMError VCOM_CALLTYPE     GetRadius(double& radius);

        virtual VCOMError VCOM_CALLTYPE     SetP1_X(double p1_X);
        virtual VCOMError VCOM_CALLTYPE     SetP1_Y(double p1_Y);
        virtual VCOMError VCOM_CALLTYPE     SetP2_X(double p2_X);
        virtual VCOMError VCOM_CALLTYPE     SetP2_Y(double p2_Y);
        virtual VCOMError VCOM_CALLTYPE     SetP3_X(double p3_X);
        virtual VCOMError VCOM_CALLTYPE     SetP3_Y(double p3_Y);
        virtual VCOMError VCOM_CALLTYPE     SetRadius(double radius);
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
		virtual void*	  VCOM_CALLTYPE     GetBoundObject();
		
    private:
        SceneData::GdtfWheelSlotAnimationSystem* fAnimationSystem;
    public:
        void setPointer(SceneData::GdtfWheelSlotAnimationSystem* animationSystem);
    };
    const VWIID IID_GdtfWheelSlotAnimationSystem = { 0xaa1c3739, 0xa08a, 0x4541, {0x97, 0x97, 0xd5, 0xed, 0x51, 0xdb, 0xf9, 0xb4}};

}

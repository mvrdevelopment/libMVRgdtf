//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfActivationGroupImpl : public VCOMImpl<IGdtfActivationGroup>
    {
    public:
        CGdtfActivationGroupImpl();
        virtual ~CGdtfActivationGroupImpl();
        
        virtual MvrString VCOM_CALLTYPE     GetName();
		
		virtual VCOMError VCOM_CALLTYPE		GetAttributeCount(size_t& count);
		virtual VCOMError VCOM_CALLTYPE		GetAttributeAt(size_t at, IGdtfAttribute** attribute);
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
		virtual void*	  VCOM_CALLTYPE     GetBoundObject();
		
    private:
        SceneData::GdtfActivationGroup* fActivationGroup;
    public:
        void							SetPointer(SceneData::GdtfActivationGroup* activationGroup);
		SceneData::GdtfActivationGroup* GetPointer();
        
    };
    const VWIID IID_GdtfActivationGroup = { 0x56806f27, 0xc391, 0x4553, {0xbc, 0x42, 0x0c, 0xb4, 0xd2, 0x96, 0x02, 0xfc}};
}

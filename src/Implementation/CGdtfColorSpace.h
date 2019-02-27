//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    class CGdtfColorSpaceImpl : public VectorworksMVR::VCOMImpl<IGdtfColorSpace>
    {
    public:
        CGdtfColorSpaceImpl();
        virtual ~CGdtfColorSpaceImpl();


        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
        virtual void*	  VCOM_CALLTYPE     GetBoundObject();

    private:
        SceneData::GdtfColorSpace* fColorSpace;

    public:
        void					SetPointer(SceneData::GdtfColorSpace* ColorSpace);
        SceneData::GdtfColorSpace*	GetPointer();

    };

    // const VWIID IID_GdtfColorSpace = { 0x09787bcb, 0x4526, 0x4e09,{ 0xb7, 0xca, 0x0b, 0xd2, 0x70, 0x6c, 0xb5, 0xfd } }; 
}


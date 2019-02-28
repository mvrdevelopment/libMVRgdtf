//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    class CGdtfPhysicalDescriptionsImpl : public VCOMImpl<IGdtfPhysicalDescriptions>
    {
    public:
        CGdtfPhysicalDescriptionsImpl();
        virtual ~CGdtfPhysicalDescriptionsImpl();

        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
        virtual void*	  VCOM_CALLTYPE     GetBoundObject();

    private:
        SceneData::GdtfPhysicalDescriptions*   fPhysicalDescriptions;

    public:
        void					                SetPointer(SceneData::GdtfPhysicalDescriptions* val);
        SceneData::GdtfPhysicalDescriptions*	GetPointer();
    };

    const VWIID IID_GdtfPhysicalDescriptions = { 0x80683668, 0x1f68, 0x4a91, {0xb8, 0x9e, 0xb9, 0x8d, 0x36, 0x74, 0x08, 0x96}};
}

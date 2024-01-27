//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfUserPresetImpl : public VCOMImpl<IGdtfUserPreset>
    {
    public:
        CGdtfUserPresetImpl();
        virtual ~CGdtfUserPresetImpl();
        
    private:
        SceneData::GdtfUserPreset* fUserPreset;
        
    public:
        void setPointer(SceneData::GdtfUserPreset* userPreset);
        
    };
    const VWIID IID_GdtfUserPreset = { 0x4fe829da, 0x5d65, 0x4c72, {0xb2, 0x76, 0xcc, 0x86, 0x4f, 0x4f, 0x24, 0xf5}};

}

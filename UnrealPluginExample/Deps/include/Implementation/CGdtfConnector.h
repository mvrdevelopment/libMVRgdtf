//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfConnectorImpl : public VCOMImpl<IGdtfConnector>
    {
    public:
        CGdtfConnectorImpl();
        virtual ~CGdtfConnectorImpl();
        
        virtual MvrString VCOM_CALLTYPE     GetName();
        virtual MvrString VCOM_CALLTYPE     GetType();
        virtual VCOMError VCOM_CALLTYPE     GetDmxBreak(Uint32& outDmxBreak);
        virtual VCOMError VCOM_CALLTYPE     GetGender(Sint32& outGender);
        virtual VCOMError VCOM_CALLTYPE     GetLength(double& outLength);
        
        

        virtual VCOMError VCOM_CALLTYPE     SetName(MvrString name);
        virtual VCOMError VCOM_CALLTYPE     SetType(MvrString type);
        virtual VCOMError VCOM_CALLTYPE     SetDmxBreak(Uint32 dmxBreak);
        virtual VCOMError VCOM_CALLTYPE     SetGender(Sint32 gender);
        virtual VCOMError VCOM_CALLTYPE     SetLength(double length);

		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
		virtual void*	  VCOM_CALLTYPE     GetBoundObject();
    private:
        SceneData::GdtfConnector* fConnector;
    public:
        void SetPointer(SceneData::GdtfConnector* connector);
        SceneData::GdtfConnector* GetPointer();
        
    };
    const VWIID IID_GdtfConnector = { 0x35eb4c82, 0x4381, 0x43bd, {0x8e, 0x8a, 0xb8, 0xb0, 0x09, 0xac, 0xf9, 0xa9}};
    

    
    
}


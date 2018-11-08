//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfGeometryImpl : public VCOMImpl<IGdtfGeometry>
    {
    public:
        CGdtfGeometryImpl();
        virtual ~CGdtfGeometryImpl();
		
		virtual VCOMError VCOM_CALLTYPE     GetGeometryType(EGdtfObjectType& type);
        virtual MvrString VCOM_CALLTYPE     GetName();
        virtual VCOMError VCOM_CALLTYPE     GetModel(IGdtfModel** model);
        virtual VCOMError VCOM_CALLTYPE     GetTransformMatrix(STransformMatrix& transformMatrix);
		
        virtual VCOMError VCOM_CALLTYPE     GetInternalGeometryCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE     GetInternalGeometryAt(size_t at, IGdtfGeometry** geometry);
		virtual VCOMError VCOM_CALLTYPE		CreateGeometry(EGdtfObjectType type, MvrString name, IGdtfModel* model, const STransformMatrix& mat, IGdtfGeometry** geometry);
		
		// Lamp
		virtual VCOMError VCOM_CALLTYPE     GetLampType(EGdtfLampType& lampType);
		virtual VCOMError VCOM_CALLTYPE     GetPowerConsumption(double& powerConsumption);
		virtual VCOMError VCOM_CALLTYPE     GetLuminousIntensity(double& luminousIntensity);
		virtual VCOMError VCOM_CALLTYPE     GetColorTemperature(double& colorTemperature);
		virtual VCOMError VCOM_CALLTYPE     GetBeamAngle(double& beamAngle);
        virtual VCOMError VCOM_CALLTYPE     GetFieldAngle(double& fldAngle);
        virtual VCOMError VCOM_CALLTYPE     GetBeamRadius(double& radius);
        virtual VCOMError VCOM_CALLTYPE     GetBeamType(EGdtfBeamType & type);
        virtual VCOMError VCOM_CALLTYPE     GetColorIndex(Sint32& idx);

        virtual VCOMError VCOM_CALLTYPE     SetName(MvrString name);
        virtual VCOMError VCOM_CALLTYPE     SetModel(IGdtfModel** model);
        virtual VCOMError VCOM_CALLTYPE     SetTransformMatrix(STransformMatrix& transformMatrix);
		virtual VCOMError VCOM_CALLTYPE     SetLampType(EGdtfLampType lampType);
		virtual VCOMError VCOM_CALLTYPE     SetPowerConsumption(double powerConsumption);
		virtual VCOMError VCOM_CALLTYPE     SetLuminousIntensity(double luminousIntensity);
		virtual VCOMError VCOM_CALLTYPE     SetColorTemperature(double colorTemperature);
		virtual VCOMError VCOM_CALLTYPE     SetBeamAngle(double beamAngle);
        virtual VCOMError VCOM_CALLTYPE     SetFieldAngle(double fldAngle);
        virtual VCOMError VCOM_CALLTYPE     SetBeamRadius(double radius);
        virtual VCOMError VCOM_CALLTYPE     SetBeamType(EGdtfBeamType type);
        virtual VCOMError VCOM_CALLTYPE     SetColorIndex(Sint32 idx);
		
		// Axis
		virtual VCOMError VCOM_CALLTYPE     GetStartAngle(double& angle);   //in Degrees
		virtual VCOMError VCOM_CALLTYPE     GetEndAngle(double& angle);     //in Degrees
		virtual VCOMError VCOM_CALLTYPE     GetSpeed(double& speed);        //in mm/s
		
		virtual VCOMError VCOM_CALLTYPE     SetStartAngle(double angle);   //in Degrees
		virtual VCOMError VCOM_CALLTYPE     SetEndAngle(double angle);     //in Degrees
		virtual VCOMError VCOM_CALLTYPE     SetSpeed(double speed);        //in mm/s
		
		// Reference
		virtual VCOMError VCOM_CALLTYPE     GetBreakCount(size_t& count);
		virtual VCOMError VCOM_CALLTYPE     GetBreakAt(size_t at, IGdtfBreak** gdtfBreak);
		virtual VCOMError VCOM_CALLTYPE     CreateBreak(Sint32 dmxBreak, DMXAddress address, IGdtfBreak** gdtfBreak);
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
		virtual void*	  VCOM_CALLTYPE     GetBoundObject();
		
    private:
        SceneData::GdtfGeometry*	fGeometry;
		EGdtfObjectType				fGeometryType;
        
    public:
        void						SetPointer(SceneData::GdtfGeometry* geometry);
		SceneData::GdtfGeometry*	GetPointer();
        
    };
    const VWIID IID_GdtfGeometry = { 0xa1e55fe9, 0x0312, 0x4348, {0x8e, 0x35, 0xd2, 0x1c, 0x6e, 0x0b, 0x2e, 0x83}};

}

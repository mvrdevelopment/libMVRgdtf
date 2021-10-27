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
        virtual VCOMError VCOM_CALLTYPE     GetParent(IGdtfGeometry** model);

		
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
        virtual VCOMError VCOM_CALLTYPE     GetThrowRatio(double& ratio);
        virtual VCOMError VCOM_CALLTYPE     GetRectangleRatio(double& ratio);
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
        virtual VCOMError VCOM_CALLTYPE     SetThrowRatio(double ratio);
        virtual VCOMError VCOM_CALLTYPE     SetRectangleRatio(double ratio);
        virtual VCOMError VCOM_CALLTYPE     SetBeamType(EGdtfBeamType type);
        virtual VCOMError VCOM_CALLTYPE     SetColorIndex(Sint32 idx);
		
		// Reference
		virtual VCOMError VCOM_CALLTYPE     GetBreakCount(size_t& count);
		virtual VCOMError VCOM_CALLTYPE     GetBreakAt(size_t at, IGdtfBreak** gdtfBreak);
		virtual VCOMError VCOM_CALLTYPE     CreateBreak(Sint32 dmxBreak, DMXAddress address, IGdtfBreak** gdtfBreak);
		virtual VCOMError VCOM_CALLTYPE     GetGeometryReference(IGdtfGeometry** geometry);
		virtual VCOMError VCOM_CALLTYPE     SetGeometryReference(IGdtfGeometry*  geometry);

        // Display
		virtual MvrString VCOM_CALLTYPE		GetTexture();
		virtual VCOMError VCOM_CALLTYPE		SetTexture(MvrString texture);

        // Helpers
        virtual VCOMError VCOM_CALLTYPE     GetCountLinkedDmxChannel(size_t& count, IGdtfDmxMode * forMode);
        virtual VCOMError VCOM_CALLTYPE     GetLinkedDmxChannelAt(size_t at, IGdtfDmxChannel** outChannel, IGdtfDmxMode * forMode);

        // GDTF 1.2
        // Laser
        virtual VCOMError VCOM_CALLTYPE		GetColorType(GdtfDefines::EGdtfLaserColorType& colorType);
        virtual VCOMError VCOM_CALLTYPE		GetLaserColor(double& waveLength);
        virtual VCOMError VCOM_CALLTYPE		GetOutputStrength(double& outputStrength);
        virtual VCOMError VCOM_CALLTYPE		GetEmitter(IGdtfPhysicalEmitter** emitter);
        virtual VCOMError VCOM_CALLTYPE		GetBeamDiameter(double& beamDiameter);
        virtual VCOMError VCOM_CALLTYPE		GetBeamDivergenceMin(double& beamDivergenceMin);
        virtual VCOMError VCOM_CALLTYPE		GetBeamDivergenceMax(double& beamDivergenceMax);
        virtual VCOMError VCOM_CALLTYPE		GetScanAnglePan(double& scanAnglePan);
        virtual VCOMError VCOM_CALLTYPE		GetScanAngleTilt(double& scanAngleTilt);
        virtual VCOMError VCOM_CALLTYPE		GetScanSpeed(double& scanSpeed);

        virtual VCOMError VCOM_CALLTYPE		SetColorType(GdtfDefines::EGdtfLaserColorType colorType);
		virtual VCOMError VCOM_CALLTYPE		SetLaserColor(double waveLength);
        virtual VCOMError VCOM_CALLTYPE		SetOutputStrength(double outputStrength);
        virtual VCOMError VCOM_CALLTYPE		SetEmitter(IGdtfPhysicalEmitter* emitter);
        virtual VCOMError VCOM_CALLTYPE		SetBeamDiameter(double beamDiameter);
        virtual VCOMError VCOM_CALLTYPE		SetBeamDivergenceMin(double beamDivergenceMin);
        virtual VCOMError VCOM_CALLTYPE		SetBeamDivergenceMax(double beamDivergenceMax);
        virtual VCOMError VCOM_CALLTYPE		SetScanAnglePan(double scanAnglePan);
        virtual VCOMError VCOM_CALLTYPE		SetScanAngleTilt(double scanAngleTilt);
        virtual VCOMError VCOM_CALLTYPE		SetScanSpeed(double scanSpeed);

        virtual VCOMError VCOM_CALLTYPE 	GetLaserProtocolCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE 	GetLaserProtocolAt(size_t at, VectorworksMVR::IGdtfLaserProtocol** outLaserProtocol);
        virtual VCOMError VCOM_CALLTYPE 	CreateLaserProtocol(MvrString name, VectorworksMVR::IGdtfLaserProtocol** outLaserProtocol);

        // WiringObject
        virtual MvrString VCOM_CALLTYPE     GetConnectorType();
        virtual VCOMError VCOM_CALLTYPE		GetComponentType(GdtfDefines::EGdtfComponentType& componentType);
        virtual MvrString VCOM_CALLTYPE     GetSignalType();
        virtual VCOMError VCOM_CALLTYPE     GetPinCount(size_t& pinCount);
        virtual VCOMError VCOM_CALLTYPE     GetSignalLayer(size_t& signalLayer);
        virtual VCOMError VCOM_CALLTYPE		GetOrientation(GdtfDefines::EGdtfOrientation& orientation);
        virtual MvrString VCOM_CALLTYPE     GetWireGroup();
        virtual VCOMError VCOM_CALLTYPE		GetElectricalPayload(double& electricalPayload);
        virtual VCOMError VCOM_CALLTYPE		GetVoltageRangeMin(double& voltageRangeMin);
        virtual VCOMError VCOM_CALLTYPE		GetVoltageRangeMax(double& voltageRangeMax);
        virtual VCOMError VCOM_CALLTYPE		GetFrequencyRangeMin(double& frequencyRangeMin);
        virtual VCOMError VCOM_CALLTYPE		GetFrequencyRangeMax(double& frequencyRangeMax);
        virtual VCOMError VCOM_CALLTYPE		GetCosPhi(double& cosPhi);
        virtual VCOMError VCOM_CALLTYPE		GetMaxPayLoad(double& maxPayload);
        virtual VCOMError VCOM_CALLTYPE		GetVoltage(double& voltage);
        virtual VCOMError VCOM_CALLTYPE		GetFuseCurrent(double& fuseCurrent);
        virtual VCOMError VCOM_CALLTYPE		GetFuseRating(GdtfDefines::EGdtfFuseRating& fuseRating);

        virtual VCOMError VCOM_CALLTYPE     SetConnectorType(MvrString connectorType);
        virtual VCOMError VCOM_CALLTYPE		SetComponentType(GdtfDefines::EGdtfComponentType componentType);
        virtual VCOMError VCOM_CALLTYPE     SetSignalType(MvrString signalType);
        virtual VCOMError VCOM_CALLTYPE     SetPinCount(size_t pinCount);
        virtual VCOMError VCOM_CALLTYPE     SetSignalLayer(size_t signalLayer);
        virtual VCOMError VCOM_CALLTYPE		SetOrientation(GdtfDefines::EGdtfOrientation orientation);
        virtual VCOMError VCOM_CALLTYPE     SetWireGroup(MvrString wireGroup);
        virtual VCOMError VCOM_CALLTYPE		SetElectricalPayload(double electricalPayload);
        virtual VCOMError VCOM_CALLTYPE		SetVoltageRangeMin(double voltageRangeMin);
        virtual VCOMError VCOM_CALLTYPE		SetVoltageRangeMax(double voltageRangeMax);
        virtual VCOMError VCOM_CALLTYPE		SetFrequencyRangeMin(double frequencyRangeMin);
        virtual VCOMError VCOM_CALLTYPE		SetFrequencyRangeMax(double frequencyRangeMax);
        virtual VCOMError VCOM_CALLTYPE		SetCosPhi(double cosPhi);
        virtual VCOMError VCOM_CALLTYPE		SetMaxPayLoad(double maxPayload);
        virtual VCOMError VCOM_CALLTYPE		SetVoltage(double voltage);
        virtual VCOMError VCOM_CALLTYPE		SetFuseCurrent(double fuseCurrent);
        virtual VCOMError VCOM_CALLTYPE		SetFuseRating(GdtfDefines::EGdtfFuseRating fuseRating);

        virtual VCOMError VCOM_CALLTYPE     GetPinPatchCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE     GetPinPatchAt(size_t at, VectorworksMVR::IGdtfPinPatch** pinPatch);
        virtual VCOMError VCOM_CALLTYPE     CreatePinPatch(VectorworksMVR::IGdtfGeometry* toWiringObject, size_t fromPin, size_t toPin, VectorworksMVR::IGdtfPinPatch** pinPatch);

        // Inventory
		virtual VCOMError VCOM_CALLTYPE     GetInventoryCount(size_t& count);
		virtual VCOMError VCOM_CALLTYPE     SetInventoryCount(size_t count);

        // Structure
        virtual VCOMError VCOM_CALLTYPE		GetStructureLinkedGeometry(IGdtfGeometry** linkedGeometry);
        virtual VCOMError VCOM_CALLTYPE		GetStructureType(GdtfDefines::EGdtfStructureType& structureType);
        virtual VCOMError VCOM_CALLTYPE		GetCrossSectionType(GdtfDefines::EGdtfCrossSectionType& crossSectionType);
        virtual VCOMError VCOM_CALLTYPE		GetCrossSectionHeight(double& crossSectionHeight);
        virtual VCOMError VCOM_CALLTYPE		GetCrossSectionWallThickness(double& crossSectionWallThickness);
        virtual MvrString VCOM_CALLTYPE		GetTrussCrossSection();

        virtual VCOMError VCOM_CALLTYPE	    SetStructureLinkedGeometry(IGdtfGeometry* linkedGeometry);
		virtual VCOMError VCOM_CALLTYPE	    SetStructureType(GdtfDefines::EGdtfStructureType structureType);
		virtual VCOMError VCOM_CALLTYPE	    SetCrossSectionType(GdtfDefines::EGdtfCrossSectionType crossSectionType);
		virtual VCOMError VCOM_CALLTYPE	    SetCrossSectionHeight(double crossSectionHeight);
		virtual VCOMError VCOM_CALLTYPE	    SetCrossSectionWallThickness(double crossSectionWallThickness);
		virtual VCOMError VCOM_CALLTYPE	    SetTrussCrossSection(MvrString trussCrossSection);

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

//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"

namespace VectorworksMVR
{
	//----------------------------------------------------------------------------------------
	class CSceneObjImpl : public VCOMImpl<ISceneObj>
	{
	public:
		CSceneObjImpl();
		virtual ~CSceneObjImpl();
		
		//Interface
	public:
		virtual VCOMError VCOM_CALLTYPE		GetType(ESceneObjType& outType);
		
		virtual MvrString VCOM_CALLTYPE		GetName();
		virtual VCOMError VCOM_CALLTYPE		GetGuid(MvrUUID& outGuid);
		
		virtual VCOMError VCOM_CALLTYPE		GetTransfromMatrix(STransformMatrix& outName);
		virtual VCOMError VCOM_CALLTYPE		GetGeometryCount(size_t& outCount);
		virtual VCOMError VCOM_CALLTYPE		GetGeometryAt(size_t at, IGeometryReference** outGeometryRef);
		
		
		virtual VCOMError VCOM_CALLTYPE		AddGeometry(const STransformMatrix& geometry, MvrString fileName);
		virtual VCOMError VCOM_CALLTYPE		AddSymbol(const MvrUUID& guid, const STransformMatrix& geometry, ISymDef* symDef);
		
		virtual VCOMError VCOM_CALLTYPE		GetClass(IClass** outClass) ;
		virtual VCOMError VCOM_CALLTYPE		SetClass(IClass* clas);

		virtual MvrString VCOM_CALLTYPE		GetGdtfName();
		virtual VCOMError VCOM_CALLTYPE		GetGdtfFixture(IGdtfFixture** outFixture);
		virtual VCOMError VCOM_CALLTYPE		SetGdtfName(MvrString gdtfName);

		virtual MvrString VCOM_CALLTYPE		GetGdtfMode();
		virtual VCOMError VCOM_CALLTYPE		SetGdtfMode(MvrString gdtfMode);

		virtual VCOMError VCOM_CALLTYPE		GetCustomCommandCount(size_t& outCount);
		virtual VCOMError VCOM_CALLTYPE		GetCustomCommandAt(size_t at, ICustomCommand** outCustomCommand);
		virtual VCOMError VCOM_CALLTYPE		CreateCustomCommand(MvrString channelFunction, bool isPercentage, double physicalValue, ICustomCommand** outCustomCommand);

		virtual VCOMError VCOM_CALLTYPE		GetAlignmentCount(size_t& outCount);
		virtual VCOMError VCOM_CALLTYPE		GetAlignmentAt(size_t at, IAlignment** outAlignment);
		virtual VCOMError VCOM_CALLTYPE		CreateAlignment(MvrString beamGeometry, const SVector3& upVector, const SVector3& direction, IAlignment** outAlignment);

		virtual VCOMError VCOM_CALLTYPE		GetOverwriteCount(size_t& outCount);
		virtual VCOMError VCOM_CALLTYPE		GetOverwriteAt(size_t at, IOverwrite** outOverwrite);
		virtual VCOMError VCOM_CALLTYPE		CreateOverwrite(MvrString universal, MvrString target, IOverwrite** outOverwrite);
		
		
		// Fixture
		virtual MvrString VCOM_CALLTYPE		GetFunction();
		virtual VCOMError VCOM_CALLTYPE		SetFunction(MvrString function);


		virtual VCOMError VCOM_CALLTYPE		GetFocusPoint(ISceneObj** outFocusPoint);
		virtual VCOMError VCOM_CALLTYPE		GetPosition(IPosition** outPosition);
		virtual VCOMError VCOM_CALLTYPE		GetAdressCount(size_t& outAdresses);
		virtual VCOMError VCOM_CALLTYPE		GetAdressAt(size_t at, SDmxAdress& adress);
		virtual VCOMError VCOM_CALLTYPE		GetUnitNumber(Sint32& outUnitNumber);
		virtual MvrString VCOM_CALLTYPE		GetFixtureId();
		virtual VCOMError VCOM_CALLTYPE		GetColor(CieColor& outColor);
		virtual VCOMError VCOM_CALLTYPE		GetFixtureTypeId(Sint8& outType);
		virtual VCOMError VCOM_CALLTYPE		GetCustomId(size_t& outId);
		virtual MvrString VCOM_CALLTYPE		GetGobo();
		virtual VCOMError VCOM_CALLTYPE		GetGoboRotation(double& value);
		virtual MvrString VCOM_CALLTYPE		GetGoboFullPath();
		virtual VCOMError VCOM_CALLTYPE		GetCastShadow(bool& value);
		virtual VCOMError VCOM_CALLTYPE		GetMappingCount(size_t& outMappings);
		virtual VCOMError VCOM_CALLTYPE		GetMappingAt(size_t at, IMapping** outMapping);


		virtual VCOMError VCOM_CALLTYPE		SetFocusPoint(ISceneObj* focusPoint);
		virtual VCOMError VCOM_CALLTYPE		SetPosition(IPosition* position);
		virtual VCOMError VCOM_CALLTYPE		AddAdress(const size_t& adresses, const size_t& breakId);
		virtual VCOMError VCOM_CALLTYPE		SetUnitNumber(const Sint32& unitNumber);
		virtual VCOMError VCOM_CALLTYPE		SetFixtureId(MvrString fixtureId);
		virtual VCOMError VCOM_CALLTYPE		SetColor(const CieColor& color);
		virtual VCOMError VCOM_CALLTYPE		SetFixtureTypeId(const Sint8& outType);
		virtual VCOMError VCOM_CALLTYPE		SetCustomId(const size_t& outId);
		virtual VCOMError VCOM_CALLTYPE		SetGobo(MvrString gobo);
		virtual VCOMError VCOM_CALLTYPE		SetGoboRotation(double rotation);
		virtual VCOMError VCOM_CALLTYPE		SetCastShadow(bool castShadow);
		virtual VCOMError VCOM_CALLTYPE		AddMapping(MvrUUID mapDefUuid);

		// Video Screen
		virtual VCOMError VCOM_CALLTYPE		SetVideoScreenSource(MvrString value, MvrString linkedGeometry, GdtfDefines::ESourceType);
		virtual VCOMError VCOM_CALLTYPE		GetVideoScreenSource(ISource** outSource);

		// Projector
		virtual VCOMError VCOM_CALLTYPE		SetProjectorSource(MvrString value, MvrString linkedGeometry, GdtfDefines::ESourceType);
		virtual VCOMError VCOM_CALLTYPE		GetProjectorSource(ISource** outSource);
		virtual VCOMError VCOM_CALLTYPE		SetScaleHandling(GdtfDefines::EScaleHandlingType scaleHandling);
		virtual VCOMError VCOM_CALLTYPE		GetScaleHandling(GdtfDefines::EScaleHandlingType& outScaleHandling);
		
		virtual VCOMError VCOM_CALLTYPE		GetConnectionCount(size_t& outConnections);
		virtual VCOMError VCOM_CALLTYPE		GetConnectionAt(size_t at, IConnection** outConnection);
		virtual VCOMError VCOM_CALLTYPE		CreateConnection(MvrString own, MvrString other, MvrUUID ToObject, IConnection** addedObj);


		// Implementation
	public:
		void SetPointer(SceneData::SceneDataObjWithMatrixPtr pointer, SceneData::SceneDataExchange* context);
		void GetPointer(SceneData::SceneDataObjWithMatrixPtr& pointer, ESceneObjType& type);
		
	private:
		SceneData::SceneDataObjWithMatrix*	fPtr;
		SceneData::SceneDataExchange*		fContext;
		ESceneObjType						fType;
	};
	
	const VWIID IID_SceneObject = { 0xc7186c7e, 0x606b, 0x412d, {0xbe, 0xe0, 0xb9, 0x7e, 0xd8, 0xf6, 0x03, 0xa3}};


}

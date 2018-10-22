//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "../Include/IMediaRessourceVectorInterface.h"

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
		virtual VCOMError VCOM_CALLTYPE		GetGuid(UUID& outGuid);
		
		virtual VCOMError VCOM_CALLTYPE		GetTransfromMatrix(STransformMatrix& outName);
		virtual VCOMError VCOM_CALLTYPE		GetGeometryCount(size_t& outCount);
		virtual VCOMError VCOM_CALLTYPE		GetGeometryAt(size_t at, IGeometryReference** outGeometryRef);
		
		
		virtual VCOMError VCOM_CALLTYPE		AddGeometry(const STransformMatrix& geometry);
		virtual VCOMError VCOM_CALLTYPE		AddSymbol(const STransformMatrix& geometry, ISymDef* symDef);
		
		virtual VCOMError VCOM_CALLTYPE		GetClass(IClass** outClass) ;
		virtual VCOMError VCOM_CALLTYPE		SetClass(IClass* clas);
		
		
		// Fixture
		virtual MvrString VCOM_CALLTYPE		GetGdtfName();
		virtual VCOMError VCOM_CALLTYPE		GetGdtfFixture(IGdtfFixture** outFixture);
		virtual MvrString VCOM_CALLTYPE		GetGdtfMode();
		virtual VCOMError VCOM_CALLTYPE		GetFocusPoint(ISceneObj** outFocusPoint);
		virtual VCOMError VCOM_CALLTYPE		GetPosition(IPosition** outPosition);
		virtual VCOMError VCOM_CALLTYPE		GetAdressCount(size_t& outAdresses);
		virtual VCOMError VCOM_CALLTYPE		GetAdressAt(size_t at, SDmxAdress& adress);
		virtual VCOMError VCOM_CALLTYPE		GetUnitNumber(Sint32& outUnitNumber);
		virtual MvrString VCOM_CALLTYPE		GetFixtureId();
		virtual VCOMError VCOM_CALLTYPE		GetColor(CieColor& outColor);
		virtual VCOMError VCOM_CALLTYPE		GetFixtureTypeId(Sint8& outType);
		virtual VCOMError VCOM_CALLTYPE		GetCustomId(size_t& outId);
		
		virtual VCOMError VCOM_CALLTYPE		SetGdtfName(MvrString gdtfName);
		virtual VCOMError VCOM_CALLTYPE		SetGdtfMode(MvrString gdtfMode);
		virtual VCOMError VCOM_CALLTYPE		SetFocusPoint(ISceneObj* focusPoint);
		virtual VCOMError VCOM_CALLTYPE		SetPosition(IPosition* position);
		virtual VCOMError VCOM_CALLTYPE		AddAdress(const size_t& adresses, const size_t& breakId);
		virtual VCOMError VCOM_CALLTYPE		SetUnitNumber(const Sint32& unitNumber);
		virtual VCOMError VCOM_CALLTYPE		SetFixtureId(MvrString fixtureId);
		virtual VCOMError VCOM_CALLTYPE		SetColor(const CieColor& color);
		virtual VCOMError VCOM_CALLTYPE		SetFixtureTypeId(const Sint8& outType);
		virtual VCOMError VCOM_CALLTYPE		SetCustomId(const size_t& outId);
		
		
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

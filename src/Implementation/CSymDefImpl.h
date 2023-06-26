//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"

namespace VectorworksMVR
{	
	//----------------------------------------------------------------------------------------
	class CSymDefImpl : public VCOMImpl<ISymDef>
	{
	public:
		CSymDefImpl();
		virtual ~CSymDefImpl();
		
	public:
        virtual VCOMError VCOM_CALLTYPE		GetGuid(MvrUUID& outGuid);
		virtual MvrString VCOM_CALLTYPE		GetName();
		virtual VCOMError VCOM_CALLTYPE		GetGeometryCount(size_t& outCount) ;
		virtual VCOMError VCOM_CALLTYPE		GetGeometryAt(size_t at, IGeometryReference** outGeometryRef) ;
		
		virtual VCOMError VCOM_CALLTYPE		AddGeometry(const STransformMatrix& geometry, MvrString fileName);
		virtual VCOMError VCOM_CALLTYPE		AddSymbol(const MvrUUID& guid, const STransformMatrix& geometry, ISymDef* symDef);
		
		// Implementation
	public:
		void SetPointer(SceneData::SceneDataSymDefObjPtr pointer, SceneData::SceneDataExchange* context);
		void GetPointer(SceneData::SceneDataSymDefObjPtr& pointer);
		
	private:
		SceneData::SceneDataSymDefObj*	fPtr;
		SceneData::SceneDataExchange*	fContext;
	};
	
	const VWIID IID_ISymDef = { 0x7d668c6d, 0x6fdf, 0x4f84, {0x90, 0x0d, 0x89, 0xc3, 0xdd, 0xb5, 0x05, 0xac}};

}

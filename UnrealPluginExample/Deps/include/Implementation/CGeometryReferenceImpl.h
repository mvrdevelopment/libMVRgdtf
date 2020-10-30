//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"

namespace VectorworksMVR
{	
	//----------------------------------------------------------------------------------------
	class CGeometryReferenceImpl : public VCOMImpl<IGeometryReference>
	{
	public:
		CGeometryReferenceImpl();
		virtual ~CGeometryReferenceImpl();
		
	public:
		virtual VCOMError VCOM_CALLTYPE		GetIsSymbol(bool& isSymbol);
		virtual MvrString VCOM_CALLTYPE		GetFileForGeometry();
		virtual VCOMError VCOM_CALLTYPE		GetSymDef(ISymDef** outSymDef);
		virtual VCOMError VCOM_CALLTYPE		GetTransfromMatrix(STransformMatrix& outName);
		
		// Implementation
	public:
		void SetPointer(SceneData::SceneDataGeoInstanceObjPtr pointer, bool isSymbol, SceneData::SceneDataExchange* context);
		void GetPointer(SceneData::SceneDataGeoInstanceObjPtr& pointer, bool& isSymbol);
		
	private:
		SceneData::SceneDataExchange*		fContext;
		SceneData::SceneDataGeoInstanceObj*	fPtr;
		bool								fIsSymbol;
	};
	
	const VWIID IID_GeometryReference = { 0xe67ad9b6, 0xae54, 0x4472, {0x99, 0xbd, 0x8f, 0x64, 0xd1, 0x58, 0xf1, 0x98}};

}

//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "../SceneDataExchange.h"
#include "CGeometryReferenceImpl.h"
#include "CPositionImpl.h"
#include "CSceneDataProviderImpl.h"
#include "CSceneObjImpl.h"
#include "CSymDefImpl.h"
#include "CClassImpl.h"

namespace VectorworksMVR
{
	class CMediaRessourceVectorImpl : public VectorworksMVR::VCOMImpl<IMediaRessourceVectorInterface>
	{
	public:
				CMediaRessourceVectorImpl();
		virtual ~CMediaRessourceVectorImpl();

	private:
		SceneData::SceneDataExchange*	GetExchangeObj();

	private:
		IFileIdentifierPtr				fPath;
		SceneData::SceneDataExchange	fExchangeObj;
		bool							fWriteMode;
		bool							fReadMode;

		//----------------------------------------------------------------------------------------
		// methods to write a file
	public:
		// Call this at the start of generating a MVR file
		virtual VCOMError VCOM_CALLTYPE	OpenForWrite(MvrString fullPath);
		virtual VCOMError VCOM_CALLTYPE	AddGdtfFolderLocation(MvrString fullPathToFolder);
		
		// After this you can generate Aux Objects
		virtual VCOMError VCOM_CALLTYPE		CreateDataProviderObject(MvrString provider,	MvrString version, ISceneDataProvider** outSceneDataProvider);
		virtual VCOMError VCOM_CALLTYPE		CreatePositionObject(	 const UUID& guid,		MvrString name,	IPosition** outPositionObj);
		virtual VCOMError VCOM_CALLTYPE		CreateSymDefObject(		 const UUID& guid,		MvrString name,	ISymDef** outSymDef);
		virtual VCOMError VCOM_CALLTYPE		CreateClassObject(		 const UUID& guid,		MvrString name,	IClass** outclass);
		
		
		// Then you can generate all other objects
		virtual VCOMError VCOM_CALLTYPE		CreateLayerObject(	const UUID& guid,								 MvrString name,								ISceneObj**	outLayerObj);
		virtual VCOMError VCOM_CALLTYPE		CreateGroupObject(	const UUID& guid, const STransformMatrix& offset,							ISceneObj* addToContainer,	ISceneObj**	outGroupObj);
		virtual VCOMError VCOM_CALLTYPE		CreateFixture(		const UUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj**	outFixture);
		virtual VCOMError VCOM_CALLTYPE		CreateSceneObject(	const UUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj**	outSceneObj);
		virtual VCOMError VCOM_CALLTYPE		CreateFocusPoint(	const UUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj** outFocusPoint);
		virtual VCOMError VCOM_CALLTYPE		CreateTruss(		const UUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj**	outTruss);
		virtual VCOMError VCOM_CALLTYPE		CreateVideoScreen(	const UUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj** outVideoScreen);
		
		// Add the end call to write the file to disk
		virtual VCOMError VCOM_CALLTYPE		Close();
		
		
		//----------------------------------------------------------------------------------------
		// methods to read a file
	public:
		// Call this at the start of generating a MVR file
		virtual VCOMError VCOM_CALLTYPE		OpenForRead(MvrString fullPath);
		
		// Get data provider objs
		virtual VCOMError VCOM_CALLTYPE		GetDataProviderObjectCount(size_t& outCount);
		virtual VCOMError VCOM_CALLTYPE		GetDataProviderObjectAt(size_t at, ISceneDataProvider** outSceneDataProvider );
		
		// Get data position objs
		virtual VCOMError VCOM_CALLTYPE		GetPositionObjectCount(size_t& outCount);
		virtual VCOMError VCOM_CALLTYPE		GetPositionObjectAt(size_t at, IPosition** outPosition );
		
		// Get SymDef objs
		virtual VCOMError VCOM_CALLTYPE		GetSymDefCount(size_t& outCount);
		virtual VCOMError VCOM_CALLTYPE		GetSymDefAt(size_t at, ISymDef** outSymDef );
		
		
		// Get Class objs
		virtual VCOMError VCOM_CALLTYPE		GetClassCount(size_t& outCount);
		virtual VCOMError VCOM_CALLTYPE		GetClassAt(size_t at, IClass** outClass );
		
		// Traversel call for object tree
		virtual VCOMError VCOM_CALLTYPE		GetFirstLayer(ISceneObj** firstLayer );
		virtual VCOMError VCOM_CALLTYPE		GetFirstChild(ISceneObj* container, ISceneObj** outChild);
		virtual VCOMError VCOM_CALLTYPE		GetNextObject(ISceneObj* object, ISceneObj** outNextObj);	
	};
}

//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "SceneDataExchange.h"
#include "Include/IMediaRessourceVectorInterface.h"
#include "CPositionImpl.h"
#include "CMappingDefinitionImpl.h"
#include "CSceneDataProviderImpl.h"
#include "CSceneObjImpl.h"
#include "CSymDefImpl.h"
#include "CClassImpl.h"

#include "CSourceImpl.h"
#include "CMappingImpl.h"
namespace VectorworksMVR
{
	class CMediaRessourceVectorImpl : public VCOMImpl<IMediaRessourceVectorInterface>
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

		// This array is just to store the additional file path
		TXStringArray 					fullPathStorage;


		//----------------------------------------------------------------------------------------
		// methods to write a file
	public:
		// Call this at the start of generating a MVR file
		virtual VCOMError VCOM_CALLTYPE	OpenForWrite(MvrString fullPath);
		virtual VCOMError VCOM_CALLTYPE	AddGdtfFolderLocation(MvrString fullPathToFolder);
        virtual VCOMError VCOM_CALLTYPE	AddFileToMvrFile(MvrString fullPath);
		virtual VCOMError VCOM_CALLTYPE AddBufferToMvrFile(MvrString filename, char* buffer, size_t length);
		virtual VCOMError VCOM_CALLTYPE	AddProviderAndProviderVersion( MvrString provider, MvrString providerVersion );

		// After this you can generate Aux Objects
		virtual VCOMError VCOM_CALLTYPE		CreateDataProviderObject(		MvrString provider,		MvrString version, 	ISceneDataProvider** outSceneDataProvider);
		virtual VCOMError VCOM_CALLTYPE		CreatePositionObject(	 		const MvrUUID& guid,	MvrString name,		IPosition** outPositionObj);
		virtual VCOMError VCOM_CALLTYPE		CreateSymDefObject(		 		const MvrUUID& guid,	MvrString name,		ISymDef** outSymDef);
		virtual VCOMError VCOM_CALLTYPE		CreateClassObject(		 		const MvrUUID& guid,	MvrString name,		IClass** outclass);
		virtual VCOMError VCOM_CALLTYPE		CreateMappingDefinitionObject(	const MvrUUID& guid,	MvrString name,		IMappingDefinition** outMapDef);
		
		
		// Then you can generate all other objects
		virtual VCOMError VCOM_CALLTYPE		CreateLayerObject(	const MvrUUID& guid,								 MvrString name,								ISceneObj**	outLayerObj);
		virtual VCOMError VCOM_CALLTYPE		CreateGroupObject(	const MvrUUID& guid, const STransformMatrix& offset,					ISceneObj* addToContainer,	ISceneObj**	outGroupObj);
		virtual VCOMError VCOM_CALLTYPE		CreateGroupObject(	const MvrUUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj**	outGroupObj);
		virtual VCOMError VCOM_CALLTYPE		CreateFixture(		const MvrUUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj**	outFixture);
		virtual VCOMError VCOM_CALLTYPE		CreateSceneObject(	const MvrUUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj**	outSceneObj);
		virtual VCOMError VCOM_CALLTYPE		CreateFocusPoint(	const MvrUUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj** outFocusPoint);
		virtual VCOMError VCOM_CALLTYPE		CreateTruss(		const MvrUUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj**	outTruss);
		virtual VCOMError VCOM_CALLTYPE		CreateSupport(		const MvrUUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj**	outSupport);
		virtual VCOMError VCOM_CALLTYPE		CreateVideoScreen(	const MvrUUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj** outVideoScreen);
		virtual VCOMError VCOM_CALLTYPE		CreateProjector(	const MvrUUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj**	outProjector);
		
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
		virtual VCOMError VCOM_CALLTYPE		GetPositionObjectAt(size_t at, IPosition** outPosition);
		
		// Get SymDef objs
		virtual VCOMError VCOM_CALLTYPE		GetSymDefCount(size_t& outCount);
		virtual VCOMError VCOM_CALLTYPE		GetSymDefAt(size_t at, ISymDef** outSymDef);
		
		// Get Class objs
		virtual VCOMError VCOM_CALLTYPE		GetClassCount(size_t& outCount);
		virtual VCOMError VCOM_CALLTYPE		GetClassAt(size_t at, IClass** outClass);

		// Get MappingDefinition objs
		virtual VCOMError VCOM_CALLTYPE		GetMappingDefinitionCount(size_t& outCount);
		virtual VCOMError VCOM_CALLTYPE		GetMappingDefinitionAt(size_t at, IMappingDefinition** outMapDef);

		// Get File Traversel
		virtual VCOMError VCOM_CALLTYPE		GetAttachedFileCount(size_t& outCount);
		virtual MvrString VCOM_CALLTYPE		GetAttachedFileCountAt(size_t at);

		
		// Traversel call for object tree
		virtual VCOMError VCOM_CALLTYPE		GetFirstLayer(ISceneObj** firstLayer );
		virtual VCOMError VCOM_CALLTYPE		GetFirstChild(ISceneObj* container, ISceneObj** outChild);
		virtual VCOMError VCOM_CALLTYPE		GetNextObject(ISceneObj* object, ISceneObj** outNextObj);	

		virtual VCOMError VCOM_CALLTYPE		GetSceneObjectCount(size_t& countObjects );

		// Check for duplicated uuids
		virtual VCOMError VCOM_CALLTYPE		GetDuplicatedUuids(bool& outDuplicated);

	};
}

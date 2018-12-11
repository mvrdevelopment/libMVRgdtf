//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CMediaRessourceVectorImpl.h"
#include "Utility.h"

using namespace VectorWorks::Filing;

VectorworksMVR::CMediaRessourceVectorImpl::CMediaRessourceVectorImpl()
{
	fWriteMode	= false;
	fReadMode	= false;;

}

VectorworksMVR::CMediaRessourceVectorImpl::~CMediaRessourceVectorImpl()
{
}

SceneData::SceneDataExchange* VectorworksMVR::CMediaRessourceVectorImpl::GetExchangeObj()
{
	return & fExchangeObj;
}


VectorworksMVR::VCOMError VectorworksMVR::CMediaRessourceVectorImpl::AddFileToMvrFile(MvrString fullPath)
{
    TXString strFullPath(fullPath);

    // Create the file pointer on the full path
    IFileIdentifierPtr file(IID_FileIdentifier);
    file->Set(strFullPath);

    bool fileExisis = false;
    file->ExistsOnDisk(fileExisis);

    // Check if the file exists
    if (!fileExisis) { return kVCOMError_Failed; }

    fExchangeObj.AddFileToZip(file);

    // 
    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CMediaRessourceVectorImpl::AddGdtfFolderLocation(MvrString fullPathToFolder)
{
	TXString path (fullPathToFolder);
	
	IFolderIdentifierPtr folder (IID_FolderIdentifier);
	folder->Set(path);
	
	fExchangeObj.AddLocationForGdtfFiles(folder);
	
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMediaRessourceVectorImpl::OpenForWrite(MvrString fullPath)
{
	//---------------------------------------------------------------------------
	// Set Path
	fPath = IFileIdentifierPtr(IID_FileIdentifier);
	if ( VCOM_FAILED(fPath->Set(fullPath)) )	{return kVCOMError_Failed;}
	
	
	//---------------------------------------------------------------------------
	// Initialize Reading
	fExchangeObj.InitializeForExport();
	fWriteMode = true;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMediaRessourceVectorImpl::CreateDataProviderObject(MvrString provider,	MvrString version, ISceneDataProvider** outSceneDataProvider)
{
	//---------------------------------------------------------------------------
	// Create the obj
	SceneData::SceneDataProviderObjPtr ptr = fExchangeObj.CreateDataProviderObject(provider, version);
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CSceneDataProviderImpl* pProviderObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_SceneDataProvider, (IVWUnknown**) & pProviderObj)))
	{
		// Check Casting
		CSceneDataProviderImpl* pResultInterface = dynamic_cast<CSceneDataProviderImpl* >(pProviderObj);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(ptr);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*outSceneDataProvider)
	{
		(*outSceneDataProvider)->Release();
		*outSceneDataProvider		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outSceneDataProvider		= pProviderObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMediaRessourceVectorImpl::CreatePositionObject(const MvrUUID& guid,		MvrString name,	IPosition** outPositionObj)
{
	//---------------------------------------------------------------------------
	// Create the obj
	VWFC::Tools::VWUUID uuid (guid.a,guid.b,guid.c,guid.d);
	
	TXString nameStr ( name );
	SceneData::SceneDataPositionObjPtr scPostion = fExchangeObj.CreatePositionObject(uuid, nameStr);
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CPositionImpl* pPosition = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_PositionObj, (IVWUnknown**) & pPosition)))
	{
		// Check Casting
		CPositionImpl* pResultInterface = dynamic_cast<CPositionImpl* >(pPosition);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(scPostion);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*outPositionObj)
	{
		(*outPositionObj)->Release();
		*outPositionObj		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outPositionObj		= pPosition;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMediaRessourceVectorImpl::CreateSymDefObject( const MvrUUID& guid,		MvrString name,	ISymDef** outSymDef)
{
	//---------------------------------------------------------------------------
	// Create the obj
	VWFC::Tools::VWUUID	uuid	(guid.a,guid.b,guid.c,guid.d);
	TXString	nameStr ( name );
	
	SceneData::SceneDataSymDefObjPtr scSymDef = fExchangeObj.CreateSymDefObject(uuid, nameStr);
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CSymDefImpl* pSymDef = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_ISymDef, (IVWUnknown**) & pSymDef)))
	{
		// Check Casting
		CSymDefImpl* pResultInterface = dynamic_cast<CSymDefImpl* >(pSymDef);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(scSymDef, GetExchangeObj());
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*outSymDef)
	{
		(*outSymDef)->Release();
		*outSymDef		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outSymDef		= pSymDef;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMediaRessourceVectorImpl::CreateClassObject(		 const MvrUUID& guid,		MvrString name,	IClass** outclass)
{
	//---------------------------------------------------------------------------
	// Create the obj
	VWFC::Tools::VWUUID	uuid	(guid.a,guid.b,guid.c,guid.d);
	TXString	nameStr ( name );
	
	SceneData::SceneDataClassObjPtr scClass = fExchangeObj.CreateClassObject(uuid, nameStr);
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CClassImpl* pClass = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_IClass, (IVWUnknown**) & pClass)))
	{
		// Check Casting
		CClassImpl* pResultInterface = dynamic_cast<CClassImpl* >(pClass);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(scClass);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*outclass)
	{
		(*outclass)->Release();
		*outclass		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outclass		= pClass;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMediaRessourceVectorImpl::CreateLayerObject(	const MvrUUID& guid, MvrString name,								ISceneObj**		outLayerObj)
{
	//---------------------------------------------------------------------------
	// Create the obj
	VWFC::Tools::VWUUID	uuid	(guid.a,guid.b,guid.c,guid.d);
	TXString	nameStr ( name );
	
	SceneData::SceneDataLayerObjPtr ptr = fExchangeObj.CreateLayerObject(uuid, nameStr);
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CSceneObjImpl* pProviderObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_SceneObject, (IVWUnknown**) & pProviderObj)))
	{
		// Check Casting
		CSceneObjImpl* pResultInterface = dynamic_cast<CSceneObjImpl* >(pProviderObj);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(ptr, GetExchangeObj());
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*outLayerObj)
	{
		(*outLayerObj)->Release();
		*outLayerObj		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outLayerObj		= pProviderObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMediaRessourceVectorImpl::CreateGroupObject(	const MvrUUID& guid, const STransformMatrix& offset, ISceneObj* addToContainer,	ISceneObj**	outGroupObj)
{
	//---------------------------------------------------------------------------
	// Read Container
	CSceneObjImpl* pContainer = dynamic_cast<CSceneObjImpl* >(addToContainer);
	
	ASSERTN(kEveryone, pContainer != nullptr);
	if ( ! pContainer) { return kVCOMError_NoValidContainerObj; }
	
	
	SceneData::SceneDataObjWithMatrixPtr	obj		= nullptr;
	ESceneObjType							type	= ESceneObjType::Layer;
	pContainer->GetPointer(obj, type);
	
	
	ASSERTN(kEveryone, type == ESceneObjType::Layer || type ==  ESceneObjType::Group);
	if ( ! (type == ESceneObjType::Layer || type ==  ESceneObjType::Group) ) { return kVCOMError_NoValidContainerObj; }
	
	SceneData::SceneDataGroupObjPtr group = dynamic_cast<SceneData::SceneDataGroupObjPtr>(obj);
	
	ASSERTN(kEveryone, group != nullptr);
	if ( ! group) { return kVCOMError_NoValidContainerObj; }
	
	//---------------------------------------------------------------------------
	// Create the obj
	VWFC::Tools::VWUUID	uuid	(guid.a,guid.b,guid.c,guid.d);
	
	VWTransformMatrix ma;
	Utility::ConvertMatrix(offset, ma);
	
	SceneData::SceneDataGroupObjPtr ptr = fExchangeObj.CreateGroupObject(uuid, ma, group);
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CSceneObjImpl* pGroupObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_SceneObject, (IVWUnknown**) & pGroupObj)))
	{
		// Check Casting
		CSceneObjImpl* pResultInterface = dynamic_cast<CSceneObjImpl* >(pGroupObj);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(ptr, GetExchangeObj());
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*outGroupObj)
	{
		(*outGroupObj)->Release();
		*outGroupObj		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outGroupObj		= pGroupObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMediaRessourceVectorImpl::CreateFixture(const MvrUUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj**	outFixture)
{
	
	//---------------------------------------------------------------------------
	// Read Container
	CSceneObjImpl* pContainer = dynamic_cast<CSceneObjImpl* >(addToContainer);
	
	ASSERTN(kEveryone, pContainer != nullptr);
	if ( ! pContainer) { return kVCOMError_NoValidContainerObj; }
	
	
	SceneData::SceneDataObjWithMatrixPtr	obj		= nullptr;
	ESceneObjType							type	= ESceneObjType::Layer;
	pContainer->GetPointer(obj, type);
	
	
	ASSERTN(kEveryone, type == ESceneObjType::Layer || type ==  ESceneObjType::Group);
	if ( ! (type == ESceneObjType::Layer || type ==  ESceneObjType::Group) ) { return kVCOMError_NoValidContainerObj; }
	
	SceneData::SceneDataGroupObjPtr group = dynamic_cast<SceneData::SceneDataGroupObjPtr>(obj);
	
	ASSERTN(kEveryone, group != nullptr);
	if ( ! group) { return kVCOMError_NoValidContainerObj; }
	
	//---------------------------------------------------------------------------
	// Create the obj
	VWFC::Tools::VWUUID	uuid	(guid.a,guid.b,guid.c,guid.d);
	TXString	nameStr ( name );
	
	VWTransformMatrix ma;
	Utility::ConvertMatrix(offset, ma);
	
	SceneData::SceneDataFixtureObjPtr ptr = fExchangeObj.CreateFixture(uuid, ma, nameStr, group);
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CSceneObjImpl* pProviderObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_SceneObject, (IVWUnknown**) & pProviderObj)))
	{
		// Check Casting
		CSceneObjImpl* pResultInterface = dynamic_cast<CSceneObjImpl* >(pProviderObj);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(ptr, GetExchangeObj());
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*outFixture)
	{
		(*outFixture)->Release();
		*outFixture		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outFixture		= pProviderObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMediaRessourceVectorImpl::CreateSceneObject(	const MvrUUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj**		outSceneObj)
{
	//---------------------------------------------------------------------------
	// Read Container
	CSceneObjImpl* pContainer = dynamic_cast<CSceneObjImpl* >(addToContainer);
	
	ASSERTN(kEveryone, pContainer != nullptr);
	if ( ! pContainer) { return kVCOMError_NoValidContainerObj; }
	
	
	SceneData::SceneDataObjWithMatrixPtr	obj		= nullptr;
	ESceneObjType							type	= ESceneObjType::Layer;
	pContainer->GetPointer(obj, type);
	
	
	ASSERTN(kEveryone, type == ESceneObjType::Layer || type ==  ESceneObjType::Group);
	if ( ! (type == ESceneObjType::Layer || type ==  ESceneObjType::Group) ) { return kVCOMError_NoValidContainerObj; }
	
	SceneData::SceneDataGroupObjPtr group = dynamic_cast<SceneData::SceneDataGroupObjPtr>(obj);
	
	ASSERTN(kEveryone, group != nullptr);
	if ( ! group) { return kVCOMError_NoValidContainerObj; }
	
	//---------------------------------------------------------------------------
	// Create the obj
	VWFC::Tools::VWUUID	uuid	(guid.a,guid.b,guid.c,guid.d);
	TXString	nameStr ( name );
	
	VWTransformMatrix ma;
	Utility::ConvertMatrix(offset, ma);
	
	SceneData::SceneDataSceneryObjPtr ptr = fExchangeObj.CreateSceneryObject(uuid, ma, nameStr, group);
	//---------------------------------------------------------------------------
	// Initialize Object
	CSceneObjImpl* pSceneObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_SceneObject, (IVWUnknown**) & pSceneObj)))
	{
		// Check Casting
		CSceneObjImpl* pResultInterface = dynamic_cast<CSceneObjImpl* >(pSceneObj);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(ptr, GetExchangeObj());
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*outSceneObj)
	{
		(*outSceneObj)->Release();
		*outSceneObj		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outSceneObj		= pSceneObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMediaRessourceVectorImpl::CreateFocusPoint(	const MvrUUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj** outFocusPoint)
{
	//---------------------------------------------------------------------------
	// Read Container
	CSceneObjImpl* pContainer = dynamic_cast<CSceneObjImpl* >(addToContainer);
	
	ASSERTN(kEveryone, pContainer != nullptr);
	if ( ! pContainer) { return kVCOMError_NoValidContainerObj; }
	
	
	SceneData::SceneDataObjWithMatrixPtr	obj		= nullptr;
	ESceneObjType							type	= ESceneObjType::Layer;
	pContainer->GetPointer(obj, type);
	
	
	ASSERTN(kEveryone, type == ESceneObjType::Layer || type ==  ESceneObjType::Group);
	if ( ! (type == ESceneObjType::Layer || type ==  ESceneObjType::Group) ) { return kVCOMError_NoValidContainerObj; }
	
	SceneData::SceneDataGroupObjPtr group = dynamic_cast<SceneData::SceneDataGroupObjPtr>(obj);
	
	ASSERTN(kEveryone, group != nullptr);
	if ( ! group) { return kVCOMError_NoValidContainerObj; }
	
	//---------------------------------------------------------------------------
	// Create the obj
	VWFC::Tools::VWUUID	uuid	(guid.a,guid.b,guid.c,guid.d);
	TXString	nameStr ( name );
	
	VWTransformMatrix ma;
	Utility::ConvertMatrix(offset, ma);
	
	SceneData::SceneDataFocusPointObjPtr ptr = fExchangeObj.CreateFocusPoint(uuid, ma, nameStr, group);
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CSceneObjImpl* pProviderObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_SceneObject, (IVWUnknown**) & pProviderObj)))
	{
		// Check Casting
		CSceneObjImpl* pResultInterface = dynamic_cast<CSceneObjImpl* >(pProviderObj);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(ptr, GetExchangeObj());
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*outFocusPoint)
	{
		(*outFocusPoint)->Release();
		*outFocusPoint		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outFocusPoint		= pProviderObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMediaRessourceVectorImpl::CreateTruss(		const MvrUUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj**		outTruss)
{
	//---------------------------------------------------------------------------
	// Read Container
	CSceneObjImpl* pContainer = dynamic_cast<CSceneObjImpl* >(addToContainer);
	
	ASSERTN(kEveryone, pContainer != nullptr);
	if ( ! pContainer) { return kVCOMError_NoValidContainerObj; }
	
	
	SceneData::SceneDataObjWithMatrixPtr	obj		= nullptr;
	ESceneObjType							type	= ESceneObjType::Layer;
	pContainer->GetPointer(obj, type);
	
	
	ASSERTN(kEveryone, type == ESceneObjType::Layer || type ==  ESceneObjType::Group);
	if ( ! (type == ESceneObjType::Layer || type ==  ESceneObjType::Group) ) { return kVCOMError_NoValidContainerObj; }
	
	SceneData::SceneDataGroupObjPtr group = dynamic_cast<SceneData::SceneDataGroupObjPtr>(obj);
	
	ASSERTN(kEveryone, group != nullptr);
	if ( ! group) { return kVCOMError_NoValidContainerObj; }
	
	//---------------------------------------------------------------------------
	// Create the obj
	VWFC::Tools::VWUUID	uuid	(guid.a,guid.b,guid.c,guid.d);
	TXString	nameStr	( name );
	
	VWTransformMatrix ma;
	Utility::ConvertMatrix(offset, ma);
	
	SceneData::SceneDataTrussObjPtr ptr = fExchangeObj.CreateTruss(uuid, ma, nameStr, group);
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CSceneObjImpl* pTrussObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_SceneObject, (IVWUnknown**) & pTrussObj)))
	{
		// Check Casting
		CSceneObjImpl* pResultInterface = dynamic_cast<CSceneObjImpl* >(pTrussObj);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(ptr, GetExchangeObj());
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*outTruss)
	{
		(*outTruss)->Release();
		*outTruss		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outTruss		= pTrussObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMediaRessourceVectorImpl::CreateVideoScreen(	const MvrUUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj** outVideoScreen)
{
	//---------------------------------------------------------------------------
	// Read Container
	CSceneObjImpl* pContainer = dynamic_cast<CSceneObjImpl* >(addToContainer);
	
	ASSERTN(kEveryone, pContainer != nullptr);
	if ( ! pContainer) { return kVCOMError_NoValidContainerObj; }
	
	
	SceneData::SceneDataObjWithMatrixPtr	obj		= nullptr;
	ESceneObjType							type	= ESceneObjType::Layer;
	pContainer->GetPointer(obj, type);
	
	
	ASSERTN(kEveryone, type == ESceneObjType::Layer || type ==  ESceneObjType::Group);
	if ( ! (type == ESceneObjType::Layer || type ==  ESceneObjType::Group) ) { return kVCOMError_NoValidContainerObj; }
	
	SceneData::SceneDataGroupObjPtr group = dynamic_cast<SceneData::SceneDataGroupObjPtr>(obj);
	
	ASSERTN(kEveryone, group != nullptr);
	if ( ! group) { return kVCOMError_NoValidContainerObj; }
	
	//---------------------------------------------------------------------------
	// Create the obj
	VWFC::Tools::VWUUID	uuid	(guid.a,guid.b,guid.c,guid.d);
	TXString	nameStr ( name );
	
	VWTransformMatrix ma;
	Utility::ConvertMatrix(offset, ma);
	
	SceneData::SceneDataVideoScreenObjPtr ptr = fExchangeObj.CreateVideoScreen(uuid, ma, nameStr, group);
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CSceneObjImpl* pVideoScreen = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_SceneObject, (IVWUnknown**) & pVideoScreen)))
	{
		// Check Casting
		CSceneObjImpl* pResultInterface = dynamic_cast<CSceneObjImpl* >(pVideoScreen);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(ptr, GetExchangeObj());
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*outVideoScreen)
	{
		(*outVideoScreen)->Release();
		*outVideoScreen		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outVideoScreen		= pVideoScreen;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMediaRessourceVectorImpl::Close()
{
	//------------------------------------------------------------------
	// Write Mode
	if(fWriteMode)
	{
		fExchangeObj.WriteToFile(fPath);
		return kVCOMError_NoError;
	}
	
	//------------------------------------------------------------------
	// Read Mode
	if(fReadMode)
	{
		return kVCOMError_NoError;
	}
	
	return kVCOMError_Failed;
}

VectorworksMVR::VCOMError VectorworksMVR::CMediaRessourceVectorImpl::OpenForRead(MvrString fullPath)
{
	//---------------------------------------------------------------------------
	// Set Path
	fPath = IFileIdentifierPtr(IID_FileIdentifier);
	if ( VCOM_FAILED(fPath->Set(fullPath)) )	{return kVCOMError_Failed;}
	
	//---------------------------------------------------------------------------
	// Initialize & Read
	fExchangeObj.InitializeForImport();
	
	if (fExchangeObj.ReadFromFile(fPath))	{ return kVCOMError_NoError; }
	
	// If the file could not be read, we return a no file error
	return kVCOMError_FileNotFound;
	
}

VectorworksMVR::VCOMError VectorworksMVR::CMediaRessourceVectorImpl::GetDataProviderObjectCount(size_t& outCount)
{
	outCount = fExchangeObj.GetProviderObjects().size();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMediaRessourceVectorImpl::GetDataProviderObjectAt(size_t at, ISceneDataProvider** outSceneDataProvider)
{
	//---------------------------------------------------------------------------
	// Check incomming count
	size_t count = fExchangeObj.GetProviderObjects().size();
	
	ASSERTN(kEveryone, at < count);
	if (at >= count) { return kVCOMError_InvalidArg; }
	
	
	//---------------------------------------------------------------------------
	// Get Symdef
	SceneData::SceneDataProviderObjPtr provider = fExchangeObj.GetProviderObjects().at(at);
	
	//---------------------------------------------------------------------------
	// Create Symdef
	CSceneDataProviderImpl* pSymDef = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_SceneDataProvider, (IVWUnknown**) & pSymDef)))
	{
		// Check Casting
		CSceneDataProviderImpl* pResultInterface = dynamic_cast<CSceneDataProviderImpl* >(pSymDef);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(provider);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*outSceneDataProvider)
	{
		(*outSceneDataProvider)->Release();
		*outSceneDataProvider		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outSceneDataProvider		= pSymDef;
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMediaRessourceVectorImpl::GetPositionObjectCount(size_t& outCount)
{
	outCount = 0;
	for (SceneData::SceneDataAuxObjPtr auxObj : fExchangeObj.GetAuxDataObjects())
	{
		if (auxObj->GetObjectType() == SceneData::ESceneDataObjectType::ePosition) { outCount++; }
	}
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMediaRessourceVectorImpl::GetPositionObjectAt(size_t at, IPosition** outPosition)
{
	// Prepare a var for local counting
	size_t positionCount = 0;
	
	// Now cycle thru aux data
	for (SceneData::SceneDataAuxObjPtr auxObj : fExchangeObj.GetAuxDataObjects())
	{
		if (auxObj->GetObjectType() == SceneData::ESceneDataObjectType::ePosition)
		{
			if (at == positionCount)
			{
				// Do the cast
				SceneData::SceneDataPositionObjPtr scPosition = dynamic_cast<SceneData::SceneDataPositionObjPtr>(auxObj);
				ASSERTN(kEveryone, scPosition != nullptr);
				if (!scPosition) { return kVCOMError_Failed; }
				
				
				//---------------------------------------------------------------------------
				// Initialize Object
				CPositionImpl* pPosition = nullptr;
				
				// Query Interface
				if (VCOM_SUCCEEDED(VWQueryInterface(IID_PositionObj, (IVWUnknown**) & pPosition)))
				{
					// Check Casting
					CPositionImpl* pResultInterface = dynamic_cast<CPositionImpl* >(pPosition);
					if (pResultInterface)
					{
						pResultInterface->SetPointer(scPosition);
					}
					else
					{
						pResultInterface->Release();
						pResultInterface = nullptr;
						return kVCOMError_NoInterface;
					}
				}
				
				//---------------------------------------------------------------------------
				// Check Incomming Object
				if (*outPosition)
				{
					(*outPosition)->Release();
					*outPosition		= NULL;
				}
				
				//---------------------------------------------------------------------------
				// Set Out Value
				*outPosition		= pPosition;
				return kVCOMError_NoError;
			}
			
			// Increase position count
			positionCount++;
		}
	}
	
	DSTOP((kEveryone,"Get Position is out of bounds!"));
	return kVCOMError_Failed;
}
																				  
VectorworksMVR::VCOMError VectorworksMVR::CMediaRessourceVectorImpl::GetSymDefCount(size_t& outCount)
{
	outCount = 0;
	for (SceneData::SceneDataAuxObjPtr auxObj : fExchangeObj.GetAuxDataObjects())
	{
		if (auxObj->GetObjectType() == SceneData::ESceneDataObjectType::eSymDef) { outCount++; }
	}
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMediaRessourceVectorImpl::GetSymDefAt(size_t at, ISymDef** outSymDef)
{
	// Prepare a var for local counting
	size_t symDefCount = 0;
	
	// Now cycle thru aux data
	for (SceneData::SceneDataAuxObjPtr auxObj : fExchangeObj.GetAuxDataObjects())
	{
		if (auxObj->GetObjectType() == SceneData::ESceneDataObjectType::eSymDef)
		{
			if (at == symDefCount)
			{
				// Do the cast
				SceneData::SceneDataSymDefObjPtr scSymDef = dynamic_cast<SceneData::SceneDataSymDefObjPtr>(auxObj);
				ASSERTN(kEveryone, scSymDef != nullptr);
				if (!scSymDef) { return kVCOMError_Failed; }
				
				
				//---------------------------------------------------------------------------
				// Initialize Object
				CSymDefImpl* pSymDef = nullptr;
				
				// Query Interface
				if (VCOM_SUCCEEDED(VWQueryInterface(IID_ISymDef, (IVWUnknown**) & pSymDef)))
				{
					// Check Casting
					CSymDefImpl* pResultInterface = dynamic_cast<CSymDefImpl* >(pSymDef);
					if (pResultInterface)
					{
						pResultInterface->SetPointer(scSymDef, GetExchangeObj());
					}
					else
					{
						pResultInterface->Release();
						pResultInterface = nullptr;
						return kVCOMError_NoInterface;
					}
				}
				
				//---------------------------------------------------------------------------
				// Check Incomming Object
				if (*outSymDef)
				{
					(*outSymDef)->Release();
					*outSymDef		= NULL;
				}
				
				//---------------------------------------------------------------------------
				// Set Out Value
				*outSymDef		= pSymDef;
				return kVCOMError_NoError;
			}
			
			// Increase position count
			symDefCount++;
		}
	}
	
	DSTOP((kEveryone,"Get Position is out of bounds!"));
	return kVCOMError_Failed;
}

VectorworksMVR::VCOMError VectorworksMVR::CMediaRessourceVectorImpl::GetClassCount(size_t& outCount)
{
	outCount = 0;
	for (SceneData::SceneDataAuxObjPtr auxObj : fExchangeObj.GetAuxDataObjects())
	{
		if (auxObj->GetObjectType() == SceneData::ESceneDataObjectType::eClassObject) { outCount++; }
	}
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMediaRessourceVectorImpl::GetClassAt(size_t at, IClass** outClass)
{
	// Prepare a var for local counting
	size_t classCount = 0;
	
	// Now cycle thru aux data
	for (SceneData::SceneDataAuxObjPtr auxObj : fExchangeObj.GetAuxDataObjects())
	{
		if (auxObj->GetObjectType() == SceneData::ESceneDataObjectType::eClassObject)
		{
			if (at == classCount)
			{
				// Do the cast
				SceneData::SceneDataClassObjPtr scClass = dynamic_cast<SceneData::SceneDataClassObjPtr>(auxObj);
				ASSERTN(kEveryone, scClass != nullptr);
				if (!scClass) { return kVCOMError_Failed; }
				
				
				//---------------------------------------------------------------------------
				// Initialize Object
				CClassImpl* pClass = nullptr;
				
				// Query Interface
				if (VCOM_SUCCEEDED(VWQueryInterface(IID_IClass, (IVWUnknown**) & pClass)))
				{
					// Check Casting
					CClassImpl* pResultInterface = dynamic_cast<CClassImpl* >(pClass);
					if (pResultInterface)
					{
						pResultInterface->SetPointer(scClass);
					}
					else
					{
						pResultInterface->Release();
						pResultInterface = nullptr;
						return kVCOMError_NoInterface;
					}
				}
				
				//---------------------------------------------------------------------------
				// Check Incomming Object
				if (*outClass)
				{
					(*outClass)->Release();
					*outClass		= NULL;
				}
				
				//---------------------------------------------------------------------------
				// Set Out Value
				*outClass		= pClass;
				return kVCOMError_NoError;
			}
			
			// Increase position count
			classCount++;
		}
	}
	
	DSTOP((kEveryone,"Get Position is out of bounds!"));
	return kVCOMError_Failed;
}

VectorworksMVR::VCOMError VectorworksMVR::CMediaRessourceVectorImpl::GetFirstLayer(ISceneObj** firstLayer)
{
	// ------------------------------------------------------------------------------------------
	// Check if there is a layer
	if (fExchangeObj.GetChildObjects().size() == 0) { return kVCOMError_NoLayerObj; }
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*firstLayer)
	{
		(*firstLayer)->Release();
		*firstLayer		= NULL;
	}
	
	SceneData::SceneDataObjWithMatrixPtr layer = fExchangeObj.GetChildObjects().at(0);
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CSceneObjImpl* pLayerObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_SceneObject, (IVWUnknown**) & pLayerObj)))
	{
		// Check Casting
		CSceneObjImpl* pResultInterface = dynamic_cast<CSceneObjImpl* >(pLayerObj);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(layer, GetExchangeObj());
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*firstLayer		= pLayerObj;
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMediaRessourceVectorImpl::GetFirstChild(ISceneObj* container, ISceneObj** outChild)
{
	// ------------------------------------------------------------------------------------------
	// Check the container object
	if ( ! container) { return kVCOMError_NoValidContainerObj; }
	
	
	// ------------------------------------------------------------------------------------------
	// Cast to object
	CSceneObjImpl* pContainer = dynamic_cast<CSceneObjImpl* >(container);
	
	//
	SceneData::SceneDataObjWithMatrixPtr	layer	= nullptr;
	ESceneObjType							objType;
	
	pContainer->GetPointer(layer, objType);
	
	// Check Pointer
	if ( ! layer)							{ return kVCOMError_NoValidContainerObj; }
	
	// Just to be sure
	ASSERTN(kEveryone,	layer->GetObjectType() == SceneData::ESceneDataObjectType::eLayer ||
						layer->GetObjectType() == SceneData::ESceneDataObjectType::eGroup);
	
	// Check Object
	bool isLayer = objType == ESceneObjType::Layer;
	bool isGroup = objType == ESceneObjType::Group;
	if ( (isLayer || isGroup) == false)	{ return kVCOMError_NoValidContainerObj; }
	
	
	// Do the last casting
	SceneData::SceneDataGroupObjPtr scGroupObj = dynamic_cast<SceneData::SceneDataGroupObjPtr >(layer);
	if(!scGroupObj) { return kVCOMError_NoValidContainerObj; }
	
	//---------------------------------------------------------------------------
	// Check of there are childs and get first object
	if (scGroupObj->GetChildArray().size() == 0){ return kVCOMError_NoError; }
	
	SceneData::SceneDataObjWithMatrixPtr	child	= scGroupObj->GetChildArray().at(0);
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CSceneObjImpl* pSceneObject = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_SceneObject, (IVWUnknown**) & pSceneObject)))
	{
		// Check Casting
		CSceneObjImpl* pResultInterface = dynamic_cast<CSceneObjImpl* >(pSceneObject);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(child, GetExchangeObj());
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*outChild)
	{
		(*outChild)->Release();
		*outChild		= NULL;
	}
	
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outChild		= pSceneObject;
	return kVCOMError_NoError;
	
	
}
																				  
VectorworksMVR::VCOMError VectorworksMVR::CMediaRessourceVectorImpl::GetNextObject(ISceneObj* object, ISceneObj** outNextObj)
{
	// ------------------------------------------------------------------------------------------
	// Check the container object
	if ( ! object) { return kVCOMError_NoValidContainerObj; }
	
	
	// ------------------------------------------------------------------------------------------
	// Cast to object
	CSceneObjImpl* pContainer = dynamic_cast<CSceneObjImpl* >(object);
	
	//
	SceneData::SceneDataObjWithMatrixPtr	scObject	= nullptr;
	ESceneObjType							objType;
	
	pContainer->GetPointer(scObject, objType);
	
	
	//---------------------------------------------------------------------------
	// Check of there are childs and get first object
	SceneData::SceneDataObjWithMatrixPtr scNextObj = scObject->GetNextObject();
	
	
	//---------------------------------------------------------------------------
	// Check Incomming Object - This need to be done before the possible return
	// of empty next object call
	if (*outNextObj)
	{
		(*outNextObj)->Release();
		*outNextObj		= NULL;
	}
	
	
	// If no next object is there, just return ok
	if (scNextObj == nullptr)	{ return kVCOMError_NotSet; }
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CSceneObjImpl* pSceneObject = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_SceneObject, (IVWUnknown**) & pSceneObject)))
	{
		// Check Casting
		CSceneObjImpl* pResultInterface = dynamic_cast<CSceneObjImpl* >(pSceneObject);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(scNextObj, GetExchangeObj());
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	

	
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outNextObj		= pSceneObject;
	return kVCOMError_NoError;
}

//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CMediaRessourceVectorImpl.h"
#include "CGeometryReferenceImpl.h"

#include "CGdtfFixture.h"
#include "Utility.h"

using namespace VectorworksMVR::Filing;


VectorworksMVR::CSceneObjImpl::CSceneObjImpl()
{
	fPtr	= nullptr;
	fContext= nullptr;
	fType	= ESceneObjType::Group;
}

VectorworksMVR::CSceneObjImpl::~CSceneObjImpl()
{
	fPtr	= nullptr;
	fContext= nullptr;
	fType	= ESceneObjType::Group;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::GetType(ESceneObjType& outType)
{
	outType = fType;
	return kVCOMError_NoError;
}

MvrString VectorworksMVR::CSceneObjImpl::GetName()
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return "";
	
	// Otherise return data
	return fPtr->getName().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::GetGuid(MvrUUID& outGuid)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherise return data
	fPtr->getGuid().GetUuidObj().GetUUID(outGuid.a, outGuid.b, outGuid.c, outGuid.d);
	
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::GetTransfromMatrix(STransformMatrix& outMatrix)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Get Matrix
	VWTransformMatrix ma;
	fPtr->GetTransformMatric(ma);
	
	// Dump Matrix in memory
	GdtfUtil::ConvertMatrix(ma, outMatrix);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::GetGeometryCount(size_t& outCount)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherise return data
	outCount = fPtr->GetGeometryArr().size();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::GetGeometryAt(size_t at, IGeometryReference** outGeometryRef)
{
	//------------------------------------------------------------------------------------------
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	ASSERTN(kEveryone,fContext);
	if( ! fContext) return kVCOMError_NotInitialized;
	
	
	//------------------------------------------------------------------------------------------
	// Check the position in the array
	size_t count = fPtr->GetGeometryArr().size();
	
	
	ASSERTN(kEveryone, at < count);
	if (count < at) { return kVCOMError_InvalidArg; }
	
	SceneData::SceneDataGeoInstanceObjPtr pScGeoObjInst = fPtr->GetGeometryArr().at(at);
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGeometryReferenceImpl* pGeometryRef = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GeometryReference, (IVWUnknown**) & pGeometryRef)))
	{
		// Check Casting
		CGeometryReferenceImpl* pResultInterface = static_cast<CGeometryReferenceImpl* >(pGeometryRef);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(pScGeoObjInst, pScGeoObjInst->IsSymDef(), fContext);
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
	if (*outGeometryRef)
	{
		(*outGeometryRef)->Release();
		*outGeometryRef		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outGeometryRef		= pGeometryRef;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::AddGeometry(const STransformMatrix& scMatrix, MvrString fileName)
{
	//---------------------------------------------------------------------------
	// Create the new object, and set the file name
	SceneData::SceneDataGeometryObjPtr geometryObject = new SceneData::SceneDataGeometryObj();
	
	//---------------------------------------------------------------------------
	// Set Transfrom Matrix
	VWTransformMatrix ma;
	GdtfUtil::ConvertMatrix(scMatrix, ma);
	geometryObject->SetTransformMatrix(ma);
    geometryObject->SetFileName(fileName);
	
	//---------------------------------------------------------------------------
	// Simply add it to the the array, deletion will be handeld by the container
	fPtr->AddGeometryObj(geometryObject);
	
	// If export fails, just return false
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::AddSymbol(const STransformMatrix& geometry, ISymDef* symDef)
{
	//------------------------------------------------------------------------------------------
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	//------------------------------------------------------------------------------------------
	// Cast incomming symDef
	CSymDefImpl* pSymDef = static_cast<CSymDefImpl*>(symDef);
	
	// Check Casting
	ASSERTN(kEveryone, pSymDef != nullptr);
	if ( ! pSymDef) { return kVCOMError_InvalidArg; }
	
	//------------------------------------------------------------------------------------------
	// Get linked Symdef
	SceneData::SceneDataSymDefObjPtr pScSymDef = nullptr;
	pSymDef->GetPointer(pScSymDef);
	
	ASSERTN(kEveryone, pScSymDef != nullptr);
	if ( ! pScSymDef) { return kVCOMError_NotInitialized; }
	
	
	//------------------------------------------------------------------------------------------
	// Create new geometry obj
	SceneData::SceneDataSymbolObjPtr newSymbolObj = new SceneData::SceneDataSymbolObj(SceneData::SceneDataGUID(VWFC::Tools::VWUUID()));
	
	// Set Transfrom Matrix
	VWTransformMatrix ma;
	GdtfUtil::ConvertMatrix(geometry,  ma);
	newSymbolObj->SetTransformMatrix(ma);
	
	// Set SymbolDef
	newSymbolObj->SetSymDef(pScSymDef);
	
	//-------------------------------------------------------------------------------------------
	// Add Object
	fPtr->AddGeometryObj(newSymbolObj);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::GetClass(IClass** outClass)
{
	//---------------------------------------------------------------------------
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	ASSERTN(kEveryone,fContext);
	if( ! fContext) return kVCOMError_NotInitialized;
	
	//---------------------------------------------------------------------------
	// Check if this is fixture
	ASSERTN(kEveryone, fType != ESceneObjType::Layer && fType != ESceneObjType::Group);
	if (fType == ESceneObjType::Layer || fType == ESceneObjType::Group) { return kVCOMError_NoValidContainerObj; }
	
	//---------------------------------------------------------------------------
	// Check if you can cast this
	SceneData::SceneDataObjWithMatrixPtr scObj = static_cast<SceneData::SceneDataObjWithMatrixPtr>(fPtr);
	
	ASSERTN(kEveryone, scObj);
	if	( scObj == nullptr) { return kVCOMError_Failed; }
	
	SceneData::SceneDataClassObjPtr scClass = scObj->GetClass();
	if(! scClass) { return kVCOMError_NotSet; }
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CClassImpl* pClass = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_IClass, (IVWUnknown**) & pClass)))
	{
		// Check Casting
		CClassImpl* pResultInterface = static_cast<CClassImpl* >(pClass);
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

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::SetClass(IClass* clas)
{
	// ------------------------------------------------------------------------------------------
	// Check the type is right
	ASSERTN(kEveryone,fType != ESceneObjType::Layer && fType != ESceneObjType::Group);
	if( fType == ESceneObjType::Layer || fType == ESceneObjType::Group) return kVCOMError_NoValidContainerObj;
	
	// ------------------------------------------------------------------------------------------
	// Check the incomming object
	if ( ! clas) { return kVCOMError_InvalidArg; }
	
	// ------------------------------------------------------------------------------------------
	// Cast to object
	CClassImpl* pClass = static_cast<CClassImpl* >(clas);
	
	ASSERTN(kEveryone, pClass != nullptr);
	if ( ! pClass) { return kVCOMError_Failed;	}
	
	//
	SceneData::SceneDataClassObjPtr scClass = nullptr;
	pClass->GetPointer(scClass);
	
	ASSERTN(kEveryone, scClass != nullptr);
	if ( ! scClass) { return kVCOMError_InvalidArg; }
	
	// ------------------------------------------------------------------------------------------
	// Cast to this object
	SceneData::SceneDataObjWithMatrixPtr scObj = static_cast<SceneData::SceneDataObjWithMatrixPtr>(fPtr);
	
	ASSERTN(kEveryone, scObj != nullptr);
	if ( ! scObj) { return kVCOMError_Failed; }
	
	
	// ------------------------------------------------------------------------------------------
	// Set the Position
	scObj->SetClass(scClass);
	
	return kVCOMError_NoError;
}


//------------------------------------------------------------------------------------------------------------------------------------------
// Fixture
MvrString VectorworksMVR::CSceneObjImpl::GetGdtfName()
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return "";
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) return "";
	
	// Try to cast
	SceneData::SceneDataFixtureObjPtr fixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	if( ! fixture) return "";
	
	return fixture->GetGdtfFile().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::GetGdtfFixture(IGdtfFixture** outFixture)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_Failed;
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) return kVCOMError_NoFixtureObj;
	
	// Try to cast
	SceneData::SceneDataFixtureObjPtr fixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	if( ! fixture) return kVCOMError_NoFixtureObj;
	
	
	//---------------------------------------------------------------------------------------------------
	// Now get the GDTF File
	TXString gdtfName = fixture->GetGdtfFile();
	
	if (gdtfName.Find(".gdtf") == ptrdiff_t(-1)) { gdtfName += ".gdtf";}
	
	IFolderIdentifierPtr workingFolder = fContext->GetWorkingFolder();
	
	IFileIdentifierPtr gdtfFile (IID_FileIdentifier);
	gdtfFile->Set(workingFolder, gdtfName);
	
	// Check if the file exists
	bool fileExists = false;
	if (VCOM_SUCCEEDED(gdtfFile->ExistsOnDisk(fileExists)) && !fileExists)
	{
		return kVCOMError_FileNotFound;
	}

	// Get working Folder
	TXString workingFolderName;
	gdtfFile->GetFileNameWithoutExtension(workingFolderName);
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfFixtureImpl*	pGdtfFixture	= nullptr;
	bool				read			= false;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_IGdtfFixture, (IVWUnknown**) & pGdtfFixture)))
	{
		// Check Casting
		CGdtfFixtureImpl* pResultInterface = static_cast<CGdtfFixtureImpl* >(pGdtfFixture);
		if (pResultInterface)
		{
			read = VCOM_SUCCEEDED( pResultInterface->ReadFromFile(gdtfFile, workingFolderName) );
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
	*outFixture		= pGdtfFixture;
	
	// If reading failed
	if(!read) {return kVCOMError_Failed;}
	
	return kVCOMError_NoError;
	
}

MvrString VectorworksMVR::CSceneObjImpl::GetGdtfMode()
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return "";
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) return "";
	
	// Try to cast
	SceneData::SceneDataFixtureObjPtr fixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	if( ! fixture) return "";
	
	
	return fixture->GetGdtfDmxMode().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::GetFocusPoint(ISceneObj** outFocusPoint)
{
	//---------------------------------------------------------------------------
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	ASSERTN(kEveryone,fContext);
	if( ! fContext) return kVCOMError_NotInitialized;
	
	//---------------------------------------------------------------------------
	// Check if this is fixture
	ASSERTN(kEveryone, fType == ESceneObjType::Fixture);
	if (fType != ESceneObjType::Fixture) { return kVCOMError_NoFixtureObj; }
	
	//---------------------------------------------------------------------------
	// Check if you can cast this
	SceneData::SceneDataFixtureObjPtr scFixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);

	ASSERTN(kEveryone, scFixture);
	if	( scFixture == nullptr) { return kVCOMError_Failed; }
	    
    SceneData::SceneDataFocusPointObjPtr focus = scFixture->GetFocusPoint();
    
    if ( ! focus) 
    {
        return kVCOMError_NotSet;
    }
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CSceneObjImpl* pFocusPoint = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_SceneObject, (IVWUnknown**) & pFocusPoint)))
	{
		// Check Casting
		CSceneObjImpl* pResultInterface = static_cast<CSceneObjImpl* >(pFocusPoint);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(focus, fContext);
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
	*outFocusPoint		= pFocusPoint;
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::GetPosition(IPosition** outPosition)
{
	//---------------------------------------------------------------------------
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	//---------------------------------------------------------------------------
	// Check if this is fixture
	ASSERTN(kEveryone, fType == ESceneObjType::Fixture);
	if (fType != ESceneObjType::Fixture) { return kVCOMError_NoFixtureObj; }
	
	//---------------------------------------------------------------------------
	// Check if you can cast this
	SceneData::SceneDataFixtureObjPtr scFixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	
	ASSERTN(kEveryone, scFixture);
	if	( scFixture == nullptr) { return kVCOMError_Failed; }
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CPositionImpl* pPosition = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_PositionObj, (IVWUnknown**) & pPosition)))
	{
		// Check Casting
		CPositionImpl* pResultInterface = static_cast<CPositionImpl* >(pPosition);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(scFixture->GetPosition());
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

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::GetAdressCount(size_t& outAdresses)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) return kVCOMError_NoFixtureObj;
	
	// Try to cast
	SceneData::SceneDataFixtureObjPtr fixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	if( ! fixture) return kVCOMError_NoFixtureObj;
	
	outAdresses = fixture->GetAdressesArray().size();
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::GetAdressAt(size_t at, SDmxAdress& adress)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) return kVCOMError_NoFixtureObj;
	
	// Try to cast
	SceneData::SceneDataFixtureObjPtr fixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	if( ! fixture) return kVCOMError_NoFixtureObj;
	
	// Check the psotion of the array
	if (at > fixture->GetAdressesArray().size())
	{
		DSTOP((kEveryone, "Array overflow"));
		return kVCOMError_Failed;
	}
	
	SceneData::SceneDataDmxAdress dmxAdress = fixture->GetAdressesArray().at(at);
	
	adress.fAbsuluteAdress	= dmxAdress.fAbsuluteAdress;
	adress.fBreakId			= dmxAdress.fBreak;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::GetUnitNumber(Sint32& outUnitNumber)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) return kVCOMError_NoFixtureObj;
	
	// Try to cast
	SceneData::SceneDataFixtureObjPtr fixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	if( ! fixture) return kVCOMError_NoFixtureObj;
	
	outUnitNumber = fixture->GetUnitNumber();
	
	return kVCOMError_NoError;
}

MvrString VectorworksMVR::CSceneObjImpl::GetFixtureId()
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return "";
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) return "";
	
	// Try to cast
	SceneData::SceneDataFixtureObjPtr fixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	if( ! fixture) return "";
	
	return fixture->GetFixtureId().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::GetColor(CieColor& outColor)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) return kVCOMError_NoFixtureObj;
	
	// Try to cast
	SceneData::SceneDataFixtureObjPtr fixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	if( ! fixture) return kVCOMError_NoFixtureObj;
	
	// Get the color
	CCieColor color = fixture->GetColor();
	
	outColor.fy	 = color.Get_y();
	outColor.fx	 = color.Get_x();
	outColor.f_Y = color.Get_Y_luminance();
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::GetFixtureTypeId(Sint8& outType)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) return kVCOMError_NoFixtureObj;
	
	// Try to cast
	SceneData::SceneDataFixtureObjPtr fixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	if( ! fixture) return kVCOMError_NoFixtureObj;
	
	outType = fixture->GetFixtureTypeId();
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::GetCustomId(size_t& outId)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) return kVCOMError_NoFixtureObj;
	
	// Try to cast
	SceneData::SceneDataFixtureObjPtr fixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	if( ! fixture) return kVCOMError_NoFixtureObj;
	
	outId = fixture->GetCustomId();
	
	return kVCOMError_NoError;
}

MvrString VectorworksMVR::CSceneObjImpl::GetGobo()
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return "";
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) return "";
	
	// Try to cast
	SceneData::SceneDataFixtureObjPtr fixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	if( ! fixture) return "";
	
	return fixture->GetGobo().GetCharPtr();
}

MvrString VectorworksMVR::CSceneObjImpl::GetGoboFullPath()
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return "";
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) return "";
	
	// Try to cast
	SceneData::SceneDataFixtureObjPtr fixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	if( ! fixture) return "";
	

	return fixture->GetGoboFullPath(fContext).GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::GetGoboRotation(double& value)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) return kVCOMError_NoFixtureObj;
	
	// Try to cast
	SceneData::SceneDataFixtureObjPtr fixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	if( ! fixture) return kVCOMError_NoFixtureObj;
		
	value = fixture->GetGoboRotation();

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::GetCastShadow(bool& value)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) return kVCOMError_NoFixtureObj;
	
	// Try to cast
	SceneData::SceneDataFixtureObjPtr fixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	if( ! fixture) return kVCOMError_NoFixtureObj;
		
	value = fixture->GetCastShadow();

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::GetMappingCount(size_t& outMappings)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) return kVCOMError_NoFixtureObj;
	
	// Try to cast
	SceneData::SceneDataFixtureObjPtr fixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	if( ! fixture) return kVCOMError_NoFixtureObj;
	
	outMappings = fixture->GetMappingsArray().size();
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::GetMappingAt(size_t at, IMapping** outMapping)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) return kVCOMError_NoFixtureObj;

	// Try to cast
	SceneData::SceneDataFixtureObjPtr fixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	if( ! fixture) return kVCOMError_NoFixtureObj;
	
	//------------------------------------------------------------------------------------------
	// Check the position in the array
	size_t count = fixture->GetMappingsArray().size();
	
	
	ASSERTN(kEveryone, at < count);
	if (count < at) { return kVCOMError_InvalidArg; }
	
	SceneData::SceneDataMappingObjPtr pScMapping = fixture->GetMappingsArray().at(at);
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CMappingImpl* pMapping = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_MappingObj, (IVWUnknown**) & pMapping)))
	{
		// Check Casting
		CMappingImpl* pResultInterface = static_cast<CMappingImpl* >(pMapping);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(pScMapping);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incoming Object
	if (*outMapping)
	{
		(*outMapping)->Release();
		*outMapping		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outMapping	= pMapping;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::SetGdtfName(MvrString gdtfName)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) return kVCOMError_NoFixtureObj;
	
	// Try to cast
	SceneData::SceneDataFixtureObjPtr fixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	if( ! fixture) return kVCOMError_NoFixtureObj;
	
	//
	TXString name (gdtfName);
	fixture->SetGDTFFile(gdtfName);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::SetGdtfMode(MvrString gdtfMode)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) return kVCOMError_NoFixtureObj;
	
	// Try to cast
	SceneData::SceneDataFixtureObjPtr fixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	if( ! fixture) return kVCOMError_NoFixtureObj;
	
	//
	TXString name (gdtfMode);
	fixture->SetGdtfDmxMode(name);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::SetFocusPoint(ISceneObj* focusPoint)
{
	// ------------------------------------------------------------------------------------------
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) return kVCOMError_NoFixtureObj;
	
	// ------------------------------------------------------------------------------------------
	// Check the container object
	if ( ! focusPoint) { return kVCOMError_InvalidArg; }
	
	// ------------------------------------------------------------------------------------------
	// Cast to object
	CSceneObjImpl* pFocusPoint = static_cast<CSceneObjImpl* >(focusPoint);
	
	ASSERTN(kEveryone, pFocusPoint != nullptr);
	if ( ! pFocusPoint) { return kVCOMError_Failed;	}
	
	//
	ESceneObjType type;
	SceneData::SceneDataObjWithMatrixPtr	scFpParent	= nullptr;
	pFocusPoint->GetPointer(scFpParent, type);
	
	SceneData::SceneDataFocusPointObjPtr scFocusPoint = static_cast<SceneData::SceneDataFocusPointObjPtr>(scFpParent);
	
	ASSERTN(kEveryone, scFocusPoint != nullptr);
	if ( ! scFocusPoint) { return kVCOMError_InvalidArg; }
	
	// ------------------------------------------------------------------------------------------
	// Cast to this object
	SceneData::SceneDataFixtureObjPtr scThisFixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	
	ASSERTN(kEveryone, scThisFixture != nullptr);
	if ( ! scThisFixture) { return kVCOMError_Failed; }
	
	
	// ------------------------------------------------------------------------------------------
	// Set the focus point
	scThisFixture->SetFocusPoint(scFocusPoint);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::SetPosition(IPosition* position)
{
	// ------------------------------------------------------------------------------------------
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) return kVCOMError_NoFixtureObj;
	
	// ------------------------------------------------------------------------------------------
	// Check the incomming object
	if ( ! position) { return kVCOMError_InvalidArg; }
	
	// ------------------------------------------------------------------------------------------
	// Cast to object
	CPositionImpl* pPosition = static_cast<CPositionImpl* >(position);
	
	ASSERTN(kEveryone, pPosition != nullptr);
	if ( ! pPosition) { return kVCOMError_Failed;	}
	
	//
	SceneData::SceneDataPositionObjPtr scPosition = nullptr;
	pPosition->GetPointer(scPosition);
	
	ASSERTN(kEveryone, scPosition != nullptr);
	if ( ! scPosition) { return kVCOMError_InvalidArg; }
	
	// ------------------------------------------------------------------------------------------
	// Cast to this object
	SceneData::SceneDataFixtureObjPtr scThisFixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	
	ASSERTN(kEveryone, scThisFixture != nullptr);
	if ( ! scThisFixture) { return kVCOMError_Failed; }
	
	
	// ------------------------------------------------------------------------------------------
	// Set the Position
	scThisFixture->SetPosition(scPosition);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::AddAdress(const size_t& adresses, const size_t& breakId)
{
	// ------------------------------------------------------------------------------------------
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) return kVCOMError_NoFixtureObj;

	
	// ------------------------------------------------------------------------------------------
	// Cast to this object
	SceneData::SceneDataFixtureObjPtr scThisFixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	
	ASSERTN(kEveryone, scThisFixture != nullptr);
	if ( ! scThisFixture) { return kVCOMError_Failed; }
	
	
	// ------------------------------------------------------------------------------------------
	// Add the Adress
	scThisFixture->AddAdress(SceneData::SceneDataDmxAdress(adresses, breakId));
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::SetUnitNumber(const Sint32& unitNumber)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) return kVCOMError_NoFixtureObj;
	
	// Try to cast
	SceneData::SceneDataFixtureObjPtr fixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	if( ! fixture) return kVCOMError_NoFixtureObj;
	
	//
	fixture->SetUnitNumber(unitNumber);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::SetFixtureId(MvrString fixtureId)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) return kVCOMError_NoFixtureObj;
	
	// Try to cast
	SceneData::SceneDataFixtureObjPtr fixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	if( ! fixture) return kVCOMError_NoFixtureObj;
	
	//
	TXString name (fixtureId);
	fixture->SetFixtureId(name);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::SetColor(const CieColor& color)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) return kVCOMError_NoFixtureObj;
	
	// Try to cast
	SceneData::SceneDataFixtureObjPtr fixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	if( ! fixture) return kVCOMError_NoFixtureObj;
	
	//
	fixture->SetColor(CCieColor(color.fx, color.fy, color.f_Y) );
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::SetFixtureTypeId(const Sint8& outType)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) return kVCOMError_NoFixtureObj;
	
	// Try to cast
	SceneData::SceneDataFixtureObjPtr fixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	if( ! fixture) return kVCOMError_NoFixtureObj;
	
	//
	fixture->SetFixtureTypeId(outType);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::SetCustomId(const size_t& outId)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) return kVCOMError_NoFixtureObj;
	
	// Try to cast
	SceneData::SceneDataFixtureObjPtr fixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	if( ! fixture) return kVCOMError_NoFixtureObj;
	
	//
	fixture->SetCustomId(outId);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::SetGobo(MvrString gobo)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) {return kVCOMError_NotInitialized;}
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) {return kVCOMError_NoFixtureObj;}
	
	// Try to cast
	SceneData::SceneDataFixtureObjPtr fixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	if( ! fixture) {return kVCOMError_NoFixtureObj;}
	
	//
	TXString goboString (gobo);
	fixture->SetGobo(goboString);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::SetGoboRotation(double rotation)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) {return kVCOMError_NotInitialized;}
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) {return kVCOMError_NoFixtureObj;}
	
	// Try to cast
	SceneData::SceneDataFixtureObjPtr fixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	if( ! fixture) {return kVCOMError_NoFixtureObj;}
	
	//
	fixture->SetGoboRotation(rotation);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::SetCastShadow(bool castShadow)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) {return kVCOMError_NotInitialized;}
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) {return kVCOMError_NoFixtureObj;}
	
	// Try to cast
	SceneData::SceneDataFixtureObjPtr fixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	if( ! fixture) {return kVCOMError_NoFixtureObj;}
	
	//
	fixture->SetCastShadow(castShadow);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::AddMapping(MvrUUID mapDefUuid)
{
	// ------------------------------------------------------------------------------------------
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) return kVCOMError_NoFixtureObj;

	// ------------------------------------------------------------------------------------------
	// Cast to this object
	SceneData::SceneDataFixtureObjPtr fixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	
	ASSERTN(kEveryone, fixture != nullptr);
	if ( ! fixture) { return kVCOMError_Failed; }
	
	// ------------------------------------------------------------------------------------------
	// Add mapping

	SceneData::SceneDataGUID newMappingUuid = SceneData::SceneDataGUID(VWUUID(mapDefUuid.a, mapDefUuid.b, mapDefUuid.c, mapDefUuid.d));

	// A fixture can't have 2 mappings with the same linked mappingDef
	for(SceneData::SceneDataMappingObjPtr mapping : fixture->GetMappingsArray())
	{
		if(mapping->GetLinkedDefUuid() == newMappingUuid) { return kVCOMError_InvalidArg; }
	}

	fixture->AddMapping(newMappingUuid);
	return kVCOMError_NoError;
}

//------------------------------------------------------------------------------------------------------------------------------------------
// Videos Screen
VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::SetVideoScreenSource(MvrString value, MvrString linkedGeometry, GdtfDefines::ESourceType type)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::VideoScreen);
	if( fType != ESceneObjType::VideoScreen) return kVCOMError_NoVideoScreenObj;
	
	// Try to cast
	SceneData::SceneDataVideoScreenObjPtr videoScreen = static_cast<SceneData::SceneDataVideoScreenObjPtr>(fPtr);
	if( ! videoScreen) return kVCOMError_NoVideoScreenObj;

	videoScreen->SetVideoSource(value, linkedGeometry, type);

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::GetVideoScreenSource(ISource** outSource)
{
	//------------------------------------------------------------------------------------------
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;

	//------------------------------------------------------------------------------------------
	// Check the type is right
	ASSERTN(kEveryone, fType == ESceneObjType::VideoScreen);
	if( fType != ESceneObjType::VideoScreen) return kVCOMError_NoVideoScreenObj;
	
	// Try to cast
	SceneData::SceneDataVideoScreenObjPtr videoScreen = static_cast<SceneData::SceneDataVideoScreenObjPtr>(fPtr);
	if( ! videoScreen) return kVCOMError_NoVideoScreenObj;

	
	SceneData::SceneDataSourceObjPtr source = videoScreen->GetVideoSource();
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CSourceImpl* pSource = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_SourceObj, (IVWUnknown**) &pSource)))
	{
		// Check Casting
		CSourceImpl* pResultInterface = static_cast<CSourceImpl*>(pSource);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(source);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	else
	{
		return kVCOMError_Failed;
	}
	
	
	//---------------------------------------------------------------------------
	// Check Incoming Object
	if (*outSource)
	{
		(*outSource)->Release();
		*outSource		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outSource = pSource;
	
	return kVCOMError_NoError;
}

//------------------------------------------------------------------------------------------------------------------------------------------
// Projector
VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::SetProjectorSource(MvrString value, MvrString linkedGeometry, GdtfDefines::ESourceType type)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Projector);
	if( fType != ESceneObjType::Projector) return kVCOMError_NoProjectorObj;
	
	// Try to cast
	SceneData::SceneDataProjectorObjPtr projector = static_cast<SceneData::SceneDataProjectorObjPtr>(fPtr);
	if( ! projector) return kVCOMError_NoProjectorObj;

	projector->SetVideoSource(value, linkedGeometry, type);

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::GetProjectorSource(ISource** outSource)
{
	//------------------------------------------------------------------------------------------
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;

	//------------------------------------------------------------------------------------------
	// Check the type is right
	ASSERTN(kEveryone, fType == ESceneObjType::Projector);
	if( fType != ESceneObjType::Projector) return kVCOMError_NoProjectorObj;
	
	// Try to cast
	SceneData::SceneDataProjectorObjPtr projector = static_cast<SceneData::SceneDataProjectorObjPtr>(fPtr);
	if( ! projector) return kVCOMError_NoProjectorObj;

	
	SceneData::SceneDataSourceObjPtr source = projector->GetVideoSource();
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CSourceImpl* pSource = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_SourceObj, (IVWUnknown**) &pSource)))
	{
		// Check Casting
		CSourceImpl* pResultInterface = static_cast<CSourceImpl*>(pSource);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(source);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	else
	{
		return kVCOMError_Failed;
	}
	
	
	//---------------------------------------------------------------------------
	// Check Incoming Object
	if (*outSource)
	{
		(*outSource)->Release();
		*outSource		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outSource = pSource;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::SetScaleHandling(GdtfDefines::EScaleHandlingType scaleHandling)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Projector);
	if( fType != ESceneObjType::Projector) return kVCOMError_NoProjectorObj;
	
	// Try to cast
	SceneData::SceneDataProjectorObjPtr projector = static_cast<SceneData::SceneDataProjectorObjPtr>(fPtr);
	if( ! projector) return kVCOMError_NoProjectorObj;

	projector->SetScaleHandling(scaleHandling);

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::GetScaleHandling(GdtfDefines::EScaleHandlingType& outScaleHandling)
{
	//------------------------------------------------------------------------------------------
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;

	//------------------------------------------------------------------------------------------
	// Check the type is right
	ASSERTN(kEveryone, fType == ESceneObjType::Projector);
	if( fType != ESceneObjType::Projector) return kVCOMError_NoProjectorObj;
	
	// Try to cast
	SceneData::SceneDataProjectorObjPtr projector = static_cast<SceneData::SceneDataProjectorObjPtr>(fPtr);
	if( ! projector) return kVCOMError_NoProjectorObj;

	//---------------------------------------------------------------------------
	// Set Out Value
	outScaleHandling = projector->GetScaleHandling();
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSceneObjImpl::SetFunction(MvrString function){
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) {return kVCOMError_NotInitialized;}
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) {return kVCOMError_NoFixtureObj;}
	
	// Try to cast
	SceneData::SceneDataFixtureObjPtr fixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	if( ! fixture) {return kVCOMError_NoFixtureObj;}
	
	TXString funStr (function);
	fixture->SetFunction(funStr);
	
	return kVCOMError_NoError;
}

MvrString VectorworksMVR::CSceneObjImpl::GetFunction(){
		// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return "";
	
	// Check the type is right
	ASSERTN(kEveryone,fType == ESceneObjType::Fixture);
	if( fType != ESceneObjType::Fixture) return "";
	
	// Try to cast
	SceneData::SceneDataFixtureObjPtr fixture = static_cast<SceneData::SceneDataFixtureObjPtr>(fPtr);
	if( ! fixture) return "";
	
	return fixture->GetFunction().GetCharPtr();
}
	

//------------------------------------------------------------------------------------------------------------------------------------------
// Implementation
void VectorworksMVR::CSceneObjImpl::SetPointer(SceneData::SceneDataObjWithMatrixPtr pointer, SceneData::SceneDataExchange* context)
{
	ASSERTN(kEveryone, pointer != nullptr);
	fPtr = pointer;
	
	switch (pointer->GetObjectType())
	{
		case SceneData::eLayer:			fType = ESceneObjType::Layer;		break;
		case SceneData::eGroup:			fType = ESceneObjType::Group;		break;
		case SceneData::eTruss:			fType = ESceneObjType::Truss;		break;
		case SceneData::eFixture:		fType = ESceneObjType::Fixture;		break;
		case SceneData::eFocusPoint:	fType = ESceneObjType::FocusPoint;	break;
		case SceneData::eSceneObject:	fType = ESceneObjType::SceneObj;	break;
		case SceneData::eVideoScreen:	fType = ESceneObjType::VideoScreen; break;
		case SceneData::eProjector:		fType = ESceneObjType::Projector; 	break;
			
		default:
			DSTOP((kEveryone, "Unexpected input!"));
			break;
	}
	
	ASSERTN(kEveryone, context!= nullptr);
	fContext = context;
	
}

void VectorworksMVR::CSceneObjImpl::GetPointer(SceneData::SceneDataObjWithMatrixPtr& pointer, ESceneObjType& type)
{
	pointer	= fPtr;
	type	= fType;
}




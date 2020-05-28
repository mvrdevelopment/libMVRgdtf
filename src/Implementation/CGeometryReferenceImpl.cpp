//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CMediaRessourceVectorImpl.h"
#include "CGeometryReferenceImpl.h"

using namespace VectorworksMVR::Filing;

//----------------------------------------------------------------------------------------
VectorworksMVR::CGeometryReferenceImpl::CGeometryReferenceImpl()
{
	fPtr		= nullptr;
	fContext	= nullptr;
	fIsSymbol	= false;
}

VectorworksMVR::CGeometryReferenceImpl::~CGeometryReferenceImpl()
{
	fPtr		= nullptr;
	fContext	= nullptr;
	fIsSymbol	= false;
}

VectorworksMVR::VCOMError VectorworksMVR::CGeometryReferenceImpl::GetIsSymbol(bool& isSymbol)
{
	isSymbol = fIsSymbol;
	return kVCOMError_NoError;
}

MvrString VectorworksMVR::CGeometryReferenceImpl::GetFileForGeometry()
{
	//----------------------------------------------------------------------------------------------------
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr ) return nullptr;
	
	// Do the actual cast
	SceneData::SceneDataGeometryObjPtr geoObj = static_cast<SceneData::SceneDataGeometryObjPtr>(fPtr);
	
	ASSERTN(kEveryone, geoObj != nullptr );
	if (!geoObj) { return ""; }
	
	//----------------------------------------------------------------------------------------------------
	// Get the geometry full file path
	return geoObj->GetFileFullPath(fContext).GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGeometryReferenceImpl::GetSymDef(ISymDef** outSymDef)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;

	// Check if this is symdef
	ASSERTN(kEveryone,fIsSymbol);
	if( ! fIsSymbol) return kVCOMError_Failed;
	
	// Cast to Symdef
	SceneData::SceneDataSymbolObjPtr scSymObj = static_cast<SceneData::SceneDataSymbolObjPtr>(fPtr);
	if(!scSymObj)	{ return kVCOMError_Failed; }
	
	SceneData::SceneDataSymDefObjPtr scSymDef = scSymObj->GetSymDef();
	if(!scSymDef)	{ return kVCOMError_NotInitialized; }

	//---------------------------------------------------------------------------
	// Initialize Object
	CSymDefImpl* pSymDef = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_ISymDef, (IVWUnknown**) & pSymDef)))
	{
		// Check Casting
		CSymDefImpl* pResultInterface = static_cast<CSymDefImpl* >(pSymDef);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(scSymDef, fContext);
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

VectorworksMVR::VCOMError VectorworksMVR::CGeometryReferenceImpl::GetTransfromMatrix(STransformMatrix& outMatrix)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Get Matrix
	VWTransformMatrix ma;
	fPtr->GetTransformMatric(ma);
	
	// Dump Matrix in memory
	outMatrix.ux = ma.fMatrix.mat[0][0];	outMatrix.uy = ma.fMatrix.mat[0][1];	outMatrix.uz = ma.fMatrix.mat[0][2];
	outMatrix.vx = ma.fMatrix.mat[1][0];	outMatrix.vy = ma.fMatrix.mat[1][1];	outMatrix.vz = ma.fMatrix.mat[1][2];
	outMatrix.wx = ma.fMatrix.mat[2][0];	outMatrix.wy = ma.fMatrix.mat[2][1];	outMatrix.wz = ma.fMatrix.mat[2][2];
	outMatrix.ox = ma.fMatrix.mat[3][0];	outMatrix.oy = ma.fMatrix.mat[3][1];	outMatrix.oz = ma.fMatrix.mat[3][2];
	
	
	
	return kVCOMError_NoError;
}

void VectorworksMVR::CGeometryReferenceImpl::SetPointer(SceneData::SceneDataGeoInstanceObjPtr pointer, bool isSymbol, SceneData::SceneDataExchange* context)
{
	ASSERTN(kEveryone, pointer != nullptr);
	ASSERTN(kEveryone, context != nullptr);
	
	fPtr		= pointer;
	fContext	= context;
	fIsSymbol	= isSymbol;
}

void VectorworksMVR::CGeometryReferenceImpl::GetPointer(SceneData::SceneDataGeoInstanceObjPtr& pointer, bool& isSymbol)
{
	pointer		= fPtr;
	isSymbol	= fIsSymbol;
}







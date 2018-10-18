//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "VectorworksMVR.h"


#include "CMediaRessourceVectorImpl.h"

using namespace VectorWorks::Filing;
using namespace VectorworksMVR;

//----------------------------------------------------------------------------------------
class CReceiverMaterialWrapper : public IGeometryReceiver::Material
{
public:
	CReceiverMaterialWrapper(const IGeometryReceiver3DS::Material* material) : fMaterial(material)
	{
		fMaterialName = fMaterial->GetMaterialName();
		this->Translate( fMaterial->GetAmbientColor(), fAmbientColor );
		this->Translate( fMaterial->GetDiffuseColor(), fDiffuseColor );
		this->Translate( fMaterial->GetSpecularColor(), fSpecularColor );
	}

	virtual ~CReceiverMaterialWrapper() {}

	virtual const std::string&		GetMaterialName() const { return fMaterialName; }

	virtual float					GetTransparencyPercentage() const { return fMaterial->GetTransparencyPercentage(); }

	virtual const VectorworksMVR::RGBColor&		GetAmbientColor() const { return fAmbientColor; }
	virtual const VectorworksMVR::RGBColor&		GetDiffuseColor() const { return fDiffuseColor; }
	virtual const VectorworksMVR::RGBColor&		GetSpecularColor() const { return fSpecularColor; }

	virtual bool					HasTexture() const { return fMaterial->HasTexture(); }
	virtual void					GetTexture(VectorworksMVR::GeometryTexture& outTexture) const
	{
		VectorWorks::Filing::GeometryTexture theTexture;
		fMaterial->GetTexture( theTexture );
		this->Translate( theTexture, outTexture );
	}

	virtual void					GetTextureMask(VectorworksMVR::GeometryTexture& outTexture) const
	{
		VectorWorks::Filing::GeometryTexture theTexture;
		fMaterial->GetTextureMask( theTexture );
		this->Translate( theTexture, outTexture );
	}

protected:
	void Translate(const ::RGBColor& from, VectorworksMVR::RGBColor& to) const
	{
		to.r = (Uint8)(from.red & 0xFF);
		to.g = (Uint8)(from.green & 0xFF);
		to.b = (Uint8)(from.blue & 0xFF);
	}

	void Translate(const VectorWorks::Filing::GeometryTexture& from, VectorworksMVR::GeometryTexture& to) const
	{
		to.fFileCallback_Import		= (VectorworksMVR::TImportBufferCallback) from.fFileCallback_Import; // force cast as we assume the callbacks are identical
		to.fFileCallbackID			= from.fFileCallbackID;
		to.fFileCallbackUserData	= from.fFileCallbackUserData;
		to.fName					= from.fName;
		to.fTilingFlags				= from.fTilingFlags;
		to.fBlurring				= from.fBlurring;
		to.fUOffset					= from.fUOffset;
		to.fUTiling					= from.fUTiling;
		to.fVOffset					= from.fVOffset;
		to.fVTiling					= from.fVTiling;
		to.fRotation				= from.fRotation;
	}

private:
	const IGeometryReceiver3DS::Material*	fMaterial;

	std::string					fMaterialName;
	VectorworksMVR::RGBColor	fAmbientColor;
	VectorworksMVR::RGBColor	fDiffuseColor;
	VectorworksMVR::RGBColor	fSpecularColor;
};

//----------------------------------------------------------------------------------------
class CGeometryReceiverWrapper : public IGeometryReceiver3DS
{
public:
			CGeometryReceiverWrapper(IGeometryReceiver* receiver) : fReceiver( receiver ) {}
	virtual	~CGeometryReceiverWrapper() {}

	virtual void BeginObject(Sint16 objectID, Sint16 parentObjectID)								{ fReceiver->BeginObject( objectID, parentObjectID ); }
	virtual void SetVerticesCount(size_t cnt)														{ fReceiver->SetVerticesCount( cnt ); }
	virtual void SetVertex(size_t vertexIndex, double x, double y, double z, double u, double v)	{ fReceiver->SetVertex( vertexIndex, x, y, z, u, v ); }
	virtual void SetFacesCount(size_t cnt)															{ fReceiver->SetFacesCount( cnt ); }
	virtual void SetFace(size_t faceIndex, size_t vertexAIndex, size_t vertexBIndex, size_t vertexCIndex, VectorWorks::Filing::EGeometryFaceInfo info)
	{
		VectorworksMVR::EGeometryFaceInfo	theInfo;
		switch ( info )
		{
			case VectorWorks::Filing::EGeometryFaceInfo::LineABVisible:
				theInfo = VectorworksMVR::EGeometryFaceInfo::LineABVisible;
				break;
			case VectorWorks::Filing::EGeometryFaceInfo::LineBCVisible:
				theInfo = VectorworksMVR::EGeometryFaceInfo::LineBCVisible;
				break;
			case VectorWorks::Filing::EGeometryFaceInfo::LineCAVisible:
				theInfo = VectorworksMVR::EGeometryFaceInfo::LineCAVisible;
				break;
			case VectorWorks::Filing::EGeometryFaceInfo::LineAllVisible:
				theInfo = VectorworksMVR::EGeometryFaceInfo::LineAllVisible;
				break;
		}
		fReceiver->SetFace( faceIndex, vertexAIndex, vertexBIndex, vertexCIndex, theInfo );
	}

	virtual void SetFaceMaterial(size_t faceIndex, const IGeometryReceiver3DS::Material* material)
	{
		CReceiverMaterialWrapper	theMaterial( material );
		fReceiver->SetFaceMaterial( faceIndex, & theMaterial );
	}

	virtual void EndObject() { fReceiver->EndObject(); }

private:
	IGeometryReceiver* fReceiver;
};

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

VectorworksMVR::VCOMError VectorworksMVR::CGeometryReferenceImpl::GetGeometry(IGeometryReceiver* receiver)
{
	//----------------------------------------------------------------------------------------------------
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr && receiver);
	if( ! fPtr ) return kVCOMError_NotInitialized;
	if( ! receiver ) return kVCOMError_InvalidArg;
	
	//----------------------------------------------------------------------------------------------------
	// Check if this is a real geometry obj and not a symdef
	ASSERTN(kEveryone, fIsSymbol == false);
	if (fIsSymbol) { return kVCOMError_Failed; }
	
	//----------------------------------------------------------------------------------------------------
	// Do the actual cast
	SceneData::SceneDataGeometryObjPtr geoObj = dynamic_cast<SceneData::SceneDataGeometryObjPtr>(fPtr);
	
	ASSERTN(kEveryone, geoObj != nullptr );
	if (!geoObj) { return kVCOMError_Failed; }
	
	//----------------------------------------------------------------------------------------------------
	// Get the geometry
	CGeometryReceiverWrapper	receiverWrapper( receiver );
	geoObj->GetGeometryReceiver3DS( &receiverWrapper, fContext);
	
	return kVCOMError_NoError;
}

MvrString VectorworksMVR::CGeometryReferenceImpl::GetFileForGeometry()
{
	//----------------------------------------------------------------------------------------------------
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr ) return nullptr;
	
	// Do the actual cast
	SceneData::SceneDataGeometryObjPtr geoObj = dynamic_cast<SceneData::SceneDataGeometryObjPtr>(fPtr);
	
	ASSERTN(kEveryone, geoObj != nullptr );
	if (!geoObj) { return nullptr; }
	
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
	SceneData::SceneDataSymDefObjPtr scSymDef = dynamic_cast<SceneData::SceneDataSymDefObjPtr>(fPtr);
	if(!scSymDef)	{ return kVCOMError_Failed; }
	
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CSymDefImpl* pSymDef = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GeometryReference, (IVWUnknown**) & pSymDef)))
	{
		// Check Casting
		CSymDefImpl* pResultInterface = dynamic_cast<CSymDefImpl* >(pSymDef);
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
	isSymbol	= isSymbol;
}







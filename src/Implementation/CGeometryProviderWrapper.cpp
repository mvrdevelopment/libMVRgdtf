//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "VectorworksMVR.h"

#include "CGeometryProviderWrapper.h"

using namespace VectorworksMVR;

CGeometryProviderWrapper::CGeometryProviderWrapper()
	: fProvider( nullptr )
{
}

CGeometryProviderWrapper::CGeometryProviderWrapper(VectorworksMVR::IGeometryProvider* provider)
	: fProvider( provider )
{
}

CGeometryProviderWrapper::CGeometryProviderWrapper(const CGeometryProviderWrapper& src)
	: fProvider( src.fProvider )
{
}

CGeometryProviderWrapper::~CGeometryProviderWrapper()
{
	fProvider = nullptr;
}

CGeometryProviderWrapper& CGeometryProviderWrapper::operator=(const CGeometryProviderWrapper& src)
{
	fProvider = src.fProvider;
	return *this;
}

void CGeometryProviderWrapper::GetObjects(std::vector<Sint16>& outObjectIDs, Sint16 parentObjectID)
{
	fProvider->GetObjects( outObjectIDs, parentObjectID );
}

void CGeometryProviderWrapper::BeginObject(Sint16 id)
{
	fProvider->BeginObject( id );
}

void CGeometryProviderWrapper::GetVerticesCount(size_t& outCnt)
{
	fProvider->GetVerticesCount( outCnt );
}

void CGeometryProviderWrapper::GetVertex(size_t vertexIndex, double& outX, double& outY, double& outZ, double& outU, double& outV)
{
	fProvider->GetVertex( vertexIndex, outX, outY, outZ, outU, outV );
}

void CGeometryProviderWrapper::GetFacesCount(size_t& outCnt)
{
	fProvider->GetFacesCount( outCnt );
}

void CGeometryProviderWrapper::GetFace(size_t faceIndex, size_t& outVertexAIndex, size_t& outVertexBIndex, size_t& outVertexCIndex, VectorWorks::Filing::EGeometryFaceInfo& outInfo)
{
	VectorworksMVR::EGeometryFaceInfo	theInfo;
	fProvider->GetFace( faceIndex, outVertexAIndex, outVertexBIndex, outVertexCIndex, theInfo );
	switch ( theInfo )
	{
		case VectorworksMVR::EGeometryFaceInfo::LineABVisible:
			outInfo = VectorWorks::Filing::EGeometryFaceInfo::LineABVisible;
			break;
		case VectorworksMVR::EGeometryFaceInfo::LineBCVisible:
			outInfo = VectorWorks::Filing::EGeometryFaceInfo::LineBCVisible;
			break;
		case VectorworksMVR::EGeometryFaceInfo::LineCAVisible:
			outInfo = VectorWorks::Filing::EGeometryFaceInfo::LineCAVisible;
			break;
		case VectorworksMVR::EGeometryFaceInfo::LineAllVisible:
			outInfo = VectorWorks::Filing::EGeometryFaceInfo::LineAllVisible;
			break;
	}
}

class CProviderMaterialWrapper : public VectorworksMVR::IGeometryProvider::Material
{
public:
	CProviderMaterialWrapper(IGeometryProvider3DS::Material* material) : fMaterial( material ) {}

	virtual void	SetMaterialName(const std::string& name)						{ fMaterial->SetMaterialName( name.c_str() ); }
	virtual void	SetTransparencyPercentage(float value)							{ fMaterial->SetTransparencyPercentage( value ); }
	virtual void	SetAmbientColor(const VectorworksMVR::RGBColor& clr)			{ ::RGBColor theClr; theClr.red = clr.r; theClr.green = clr.g; theClr.blue = clr.b; fMaterial->SetAmbientColor( theClr ); }
	virtual void	SetDiffuseColor(const VectorworksMVR::RGBColor& clr)			{ ::RGBColor theClr; theClr.red = clr.r; theClr.green = clr.g; theClr.blue = clr.b; fMaterial->SetDiffuseColor( theClr ); }
	virtual void	SetSpecularColor(const VectorworksMVR::RGBColor& clr)			{ ::RGBColor theClr; theClr.red = clr.r; theClr.green = clr.g; theClr.blue = clr.b; fMaterial->SetSpecularColor( theClr ); }
	virtual void	SetTexture(const VectorworksMVR::GeometryTexture& texture)
	{
		VectorWorks::Filing::GeometryTexture theTexture;
		this->Translate( texture, theTexture );
		fMaterial->SetTexture( theTexture );
	}
	
	virtual void	SetTextureMask(const VectorworksMVR::GeometryTexture& texture)
	{
		VectorWorks::Filing::GeometryTexture theTexture;
		this->Translate( texture, theTexture );
		fMaterial->SetTextureMask( theTexture );
	}

protected:
	void Translate(const VectorworksMVR::GeometryTexture& from, VectorWorks::Filing::GeometryTexture& to)
	{
		to.fFileCallback_Export		= (VectorWorks::Filing::TExportBufferCallback) from.fFileCallback_Export; // force cast as we assume the callbacks are identical
		to.fFileCallbackID			= from.fFileCallbackID;
		to.fFileCallbackUserData	= from.fFileCallbackUserData;
		to.fName					= from.fName.c_str();
		to.fTilingFlags				= from.fTilingFlags;
		to.fBlurring				= from.fBlurring;
		to.fUOffset					= from.fUOffset;
		to.fUTiling					= from.fUTiling;
		to.fVOffset					= from.fVOffset;
		to.fVTiling					= from.fVTiling;
		to.fRotation				= from.fRotation;
	}

private:
	IGeometryProvider3DS::Material* fMaterial;
};

void CGeometryProviderWrapper::GetFaceMaterial(size_t faceIndex, IGeometryProvider3DS::Material* material)
{
	CProviderMaterialWrapper	theMaterial( material );
	fProvider->GetFaceMaterial( faceIndex, & theMaterial );
}

void CGeometryProviderWrapper::EndObject()
{
	fProvider->EndObject();
}


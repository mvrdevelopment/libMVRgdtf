#pragma once
//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

namespace VectorworksMVR
{	
	//----------------------------------------------------------------------------------------
	class CGeometryProviderWrapper : public VectorWorks::Filing::IGeometryProvider3DS
	{
	public:
				CGeometryProviderWrapper();
				CGeometryProviderWrapper(VectorworksMVR::IGeometryProvider* provider);
				CGeometryProviderWrapper(const CGeometryProviderWrapper& src);
		virtual	~CGeometryProviderWrapper();

		CGeometryProviderWrapper& operator=(const CGeometryProviderWrapper& src);

		virtual void GetObjects(std::vector<Sint16>& outObjectIDs, Sint16 parentObjectID=-1);

		virtual void BeginObject(Sint16 id);
		virtual void GetVerticesCount(size_t& outCnt);
		virtual void GetVertex(size_t vertexIndex, double& outX, double& outY, double& outZ, double& outU, double& outV);
		virtual void GetFacesCount(size_t& outCnt);
		virtual void GetFace(size_t faceIndex, size_t& outVertexAIndex, size_t& outVertexBIndex, size_t& outVertexCIndex, VectorWorks::Filing::EGeometryFaceInfo& outInfo);
		virtual void GetFaceMaterial(size_t faceIndex, IGeometryProvider3DS::Material* material);
		virtual void EndObject();

	private:
		VectorworksMVR::IGeometryProvider*	fProvider;
	};

}

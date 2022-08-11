//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "SceneDataExchange.h"
#include "Include/IMediaRessourceVectorInterface.h"

namespace VectorworksMVR
{
	//----------------------------------------------------------------------------------------
	class CAlignmentImpl : public VCOMImpl<IAlignment>
	{
	public:
		CAlignmentImpl();
		virtual ~CAlignmentImpl();
		
		//Interface
	public:
		virtual MvrString VCOM_CALLTYPE		GetBeamGeometry();
		virtual VCOMError VCOM_CALLTYPE		GetUpVector(SVector3& upVector);
		virtual VCOMError VCOM_CALLTYPE	    GetDirection(SVector3& direction);

		virtual VCOMError VCOM_CALLTYPE		SetBeamGeometry(const MvrString& beamGeometry);
		virtual VCOMError VCOM_CALLTYPE		SetUpVector(double x, double y, double z);
		virtual VCOMError VCOM_CALLTYPE		SetDirection(double x, double y, double z);
		
		// Implementation
	public:
		void SetPointer(SceneData::SceneDataAlignmentPtr pointer);
		void GetPointer(SceneData::SceneDataAlignmentPtr& pointer);
		
	private:
		SceneData::SceneDataAlignment*	fPtr;
	};
	
	const VWIID IID_Alignment = {0xa95897b2, 0x744c, 0x445d, {0x80, 0xf3, 0x0f, 0xa8, 0xe6, 0x1e, 0x0b, 0x5f}};


}

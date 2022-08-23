//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "SceneDataExchange.h"
#include "Include/IMediaRessourceVectorInterface.h"

namespace VectorworksMVR
{
	//----------------------------------------------------------------------------------------
	class COverwriteImpl : public VCOMImpl<IOverwrite>
	{
	public:
		COverwriteImpl();
		virtual ~COverwriteImpl();
		
		//Interface
	public:
		virtual MvrString VCOM_CALLTYPE		GetUniversal();
		virtual MvrString VCOM_CALLTYPE		GetTarget();

		virtual VCOMError VCOM_CALLTYPE		SetUniversal(const MvrString& universal);
		virtual VCOMError VCOM_CALLTYPE		SetTarget(const MvrString& target);
		
		// Implementation
	public:
		void SetPointer(SceneData::SceneDataOverwritePtr pointer);
		void GetPointer(SceneData::SceneDataOverwritePtr& pointer);
		
	private:
		SceneData::SceneDataOverwrite*	fPtr;
	};
	
	const VWIID IID_Overwrite = {0x9fb62410, 0xf0ff, 0x4f21, {0xbb, 0xca, 0xda, 0x91, 0x18, 0xa6, 0x07, 0xcf}};
	


}

//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"

namespace VectorworksMVR
{	
	//----------------------------------------------------------------------------------------
	class CPositionImpl : public VCOMImpl<IPosition>
	{
	public:
		CPositionImpl();
		virtual ~CPositionImpl();
		
	public:
		virtual MvrString VCOM_CALLTYPE		GetName();
		virtual VCOMError VCOM_CALLTYPE		GetGuid(MvrUUID& guid);
		
		
		// Implementation
	public:
		void SetPointer(SceneData::SceneDataPositionObjPtr pointer);
		void GetPointer(SceneData::SceneDataPositionObjPtr& pointer);
		
	private:
		SceneData::SceneDataPositionObj*	fPtr;
	};
	
	const VWIID IID_PositionObj = { 0xe7c5e208, 0x984e, 0x4524, {0xba, 0xba, 0xb9, 0xfb, 0xd7, 0x1b, 0x8e, 0x62}};

}

//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"

namespace VectorworksMVR
{	
	//----------------------------------------------------------------------------------------
	class CClassImpl : public VCOMImpl<IClass>
	{
	public:
		CClassImpl();
		virtual ~CClassImpl();
		
	public:
		virtual MvrString VCOM_CALLTYPE		GetName();
		virtual VCOMError VCOM_CALLTYPE		GetGuid(MvrUUID& guid);
		
		
		// Implementation
	public:
		void SetPointer(SceneData::SceneDataClassObjPtr pointer);
		void GetPointer(SceneData::SceneDataClassObjPtr& pointer);
		
	private:
		SceneData::SceneDataClassObj*	fPtr;

	};
	
	const VWIID IID_IClass = { 0x0694e844, 0x1c51, 0x4aea, {0xb0, 0x78, 0x4a, 0xd1, 0x4b, 0x08, 0xb2, 0x8e}};

}

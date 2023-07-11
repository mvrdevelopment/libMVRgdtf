//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "SceneDataExchange.h"
#include "Include/IMediaRessourceVectorInterface.h"

namespace VectorworksMVR
{	
	//----------------------------------------------------------------------------------------
	class CConnectionImpl : public VCOMImpl<IConnection>
	{
	public:
		CConnectionImpl();
		virtual ~CConnectionImpl();
		
	public:
		virtual VCOMError VCOM_CALLTYPE		GetToObject(MvrUUID& linkedDefUuid);
		virtual MvrString VCOM_CALLTYPE		GetOwn();
		virtual MvrString VCOM_CALLTYPE		GetOther();

		virtual VCOMError VCOM_CALLTYPE		SetToObject(MvrUUID linkedDefUuid);
		virtual VCOMError VCOM_CALLTYPE		SetOwn(MvrString value);
		virtual VCOMError VCOM_CALLTYPE		SetOther(MvrString value);
		
		
		// Implementation
	public:
		void SetPointer(SceneData::SceneDataConnectionObjPtr pointer);
		void GetPointer(SceneData::SceneDataConnectionObjPtr& pointer);
		
	private:
		SceneData::SceneDataConnectionObjPtr	fPtr;
	};
	
	const VWIID IID_ConnectionObj = {0x611648db, 0x09c7, 0x472c, {0x9d, 0x32, 0x16, 0x06, 0x93, 0x7a, 0xb1, 0xd4}};
	

}

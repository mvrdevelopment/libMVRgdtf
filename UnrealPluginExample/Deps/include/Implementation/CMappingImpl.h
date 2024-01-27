//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"

namespace VectorworksMVR
{	
	//----------------------------------------------------------------------------------------
	class CMappingImpl : public VCOMImpl<IMapping>
	{
	public:
		CMappingImpl();
		virtual ~CMappingImpl();
		
	public:
		virtual VCOMError VCOM_CALLTYPE		GetLinkedDefUuid(MvrUUID& linkedDefUuid);
		virtual VCOMError VCOM_CALLTYPE		GetUx(Uint32& outValue);
		virtual VCOMError VCOM_CALLTYPE		GetUy(Uint32& outValue);
		virtual VCOMError VCOM_CALLTYPE		GetOx(Uint32& outValue);
		virtual VCOMError VCOM_CALLTYPE		GetOy(Uint32& outValue);
		virtual VCOMError VCOM_CALLTYPE		GetRz(double& outValue);

		virtual VCOMError VCOM_CALLTYPE		SetLinkedDefUuid(MvrUUID linkedDefUuid);
		virtual VCOMError VCOM_CALLTYPE		SetUx(Uint32 value);
		virtual VCOMError VCOM_CALLTYPE		SetUy(Uint32 value);
		virtual VCOMError VCOM_CALLTYPE		SetOx(Uint32 value);
		virtual VCOMError VCOM_CALLTYPE		SetOy(Uint32 value);
		virtual VCOMError VCOM_CALLTYPE		SetRz(double value);
		
		
		// Implementation
	public:
		void SetPointer(SceneData::SceneDataMappingObjPtr pointer);
		void GetPointer(SceneData::SceneDataMappingObjPtr& pointer);
		
	private:
		SceneData::SceneDataMappingObj*	fPtr;
	};
	
	const VWIID IID_MappingObj = {0x98bafa4f, 0x1e7a, 0x4b33, {0xb7, 0x11, 0x7b, 0xc7, 0x61, 0xda, 0x5a, 0x41}};

}

//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"

namespace VectorworksMVR
{	
	//----------------------------------------------------------------------------------------
	class CSceneDataProviderImpl : public VCOMImpl<ISceneDataProvider>
	{
	public:
		CSceneDataProviderImpl();
		virtual ~CSceneDataProviderImpl();
		
		// Interface
	public:
		virtual VCOMError VCOM_CALLTYPE		AddKeyValue(MvrString key, MvrString value);
		virtual VCOMError VCOM_CALLTYPE		GetKeyValueCount(size_t& outVal);
		virtual MvrString VCOM_CALLTYPE		GetKeyAt(size_t at);
		virtual MvrString VCOM_CALLTYPE		GetValueAt(size_t at);
		virtual MvrString VCOM_CALLTYPE		GetProviderName();
		virtual MvrString VCOM_CALLTYPE		GetVersion();

		
	public:
		void SetPointer(SceneData::SceneDataProviderObjPtr pointer);
		
	private:
		SceneData::SceneDataProviderObjPtr fPtr;
	};
	const VWIID IID_SceneDataProvider = { 0xe03678a4, 0xfc58, 0x42e6, {0xb2, 0x13, 0x75, 0xcf, 0x52, 0xdc, 0x5c, 0x67}};
}

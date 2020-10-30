//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"

namespace VectorworksMVR
{	
	//----------------------------------------------------------------------------------------
	class CSourceImpl : public VCOMImpl<ISource>
	{
	public:
		CSourceImpl();
		virtual ~CSourceImpl();
		
	public:
		virtual MvrString VCOM_CALLTYPE		GetValue();
		virtual MvrString VCOM_CALLTYPE		GetLinkedGeometry();
		virtual VCOMError VCOM_CALLTYPE		GetType(GdtfDefines::ESourceType& sourceType);

		virtual VCOMError VCOM_CALLTYPE		SetValue(MvrString value);
		virtual VCOMError VCOM_CALLTYPE		SetLinkedGeometry(MvrString linkedGeometry);
		virtual VCOMError VCOM_CALLTYPE		SetType(GdtfDefines::ESourceType type);
		
		
		// Implementation
	public:
		void SetPointer(SceneData::SceneDataSourceObjPtr pointer);
		void GetPointer(SceneData::SceneDataSourceObjPtr& pointer);
		
	private:
		SceneData::SceneDataSourceObj*	fPtr;
	};
	
	const VWIID IID_SourceObj = { 0x13676a17, 0xc2e8, 0x4fd4, {0xa8, 0x5c, 0x8c, 0xaa, 0x3a, 0xab, 0x16, 0xee}};

}

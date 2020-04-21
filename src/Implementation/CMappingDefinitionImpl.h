//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"

namespace VectorworksMVR
{	
	//----------------------------------------------------------------------------------------
	class CMappingDefinitionImpl : public VCOMImpl<IMappingDefinition>
	{
	public:
		CMappingDefinitionImpl();
		virtual ~CMappingDefinitionImpl();
		
	public:
		virtual MvrString VCOM_CALLTYPE		GetName();
		virtual VCOMError VCOM_CALLTYPE		GetGuid(MvrUUID& guid);

		virtual VCOMError VCOM_CALLTYPE		GetSizeX(const Uint32& sizeX);
		virtual VCOMError VCOM_CALLTYPE		GetSizeY(const Uint32& sizeY);
		
		
		// Implementation
	public:
		void SetPointer(SceneData::SceneDataMappingDefinitionObjPtr pointer);
		void GetPointer(SceneData::SceneDataMappingDefinitionObjPtr& pointer);
		
	private:
		SceneData::SceneDataMappingDefinitionObj*	fPtr;
	};
	
	const VWIID IID_MappingDefinitionObj = { 0x977e20ed, 0xad01, 0x4809, {0x86, 0xaa, 0x4f, 0xd7, 0x4d, 0xd5, 0x40, 0x77}};

}

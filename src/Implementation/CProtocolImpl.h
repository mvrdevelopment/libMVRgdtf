//-----------------------------------------------------------------------------
//----- Copyright Nemetschek Vectorworks
//-----------------------------------------------------------------------------
#pragma once
#include "Include/IMediaRessourceVectorInterface.h"

namespace VectorworksMVR
{	
	//----------------------------------------------------------------------------------------
	class CProtocolImpl : public VCOMImpl<IProtocol>
	{
	public:
		CProtocolImpl();
		virtual ~CProtocolImpl();
		
	public:


	};
	
	const VWIID IID_ProtocolObj = {0x98bafa4f, 0x1e7a, 0x4b33, {0xb7, 0x11, 0x7b, 0xc7, 0x61, 0xda, 0x5a, 0x41}};

}

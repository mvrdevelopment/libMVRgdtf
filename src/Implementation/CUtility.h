//-----------------------------------------------------------------------------
//----- Copyright MVR Group
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"

namespace VectorworksMVR
{	
	//----------------------------------------------------------------------------------------
	class CUtilityImpl : public VCOMImpl<IUtility>
	{
	public:
		CUtilityImpl();
		virtual ~CUtilityImpl();
		
	public:
        virtual VCOMError VCOM_CALLTYPE     CieToRgb(const CieColor& color, RGBColor& out);
        virtual VCOMError VCOM_CALLTYPE     RgBToCie(const RGBColor& color, CieColor& out);
		
		

	};
}

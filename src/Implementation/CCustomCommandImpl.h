//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "SceneDataExchange.h"
#include "Include/IMediaRessourceVectorInterface.h"

namespace VectorworksMVR
{
	//----------------------------------------------------------------------------------------
	class CCustomCommandImpl : public VCOMImpl<ICustomCommand>
	{
	public:
		CCustomCommandImpl();
		virtual ~CCustomCommandImpl();
		
		//Interface
	public:
		virtual MvrString VCOM_CALLTYPE		GetChannelFunction();
		virtual VCOMError VCOM_CALLTYPE		IsPercentage(bool& isPercentage);
		virtual VCOMError VCOM_CALLTYPE		GetValue(double& outValue);

		virtual VCOMError VCOM_CALLTYPE		SetChannelFunction(const MvrString& channelFunction);
		virtual VCOMError VCOM_CALLTYPE		SetIsPercentage(bool isPercentage);
		virtual VCOMError VCOM_CALLTYPE		SetValue(double value);
		
		// Implementation
	public:
		void SetPointer(SceneData::SceneDataCustomCommandPtr pointer);
		void GetPointer(SceneData::SceneDataCustomCommandPtr& pointer);
		
	private:
		SceneData::SceneDataCustomCommand*	fPtr;
	};
	
	const VWIID IID_CustomCommand = {0x14f386cf, 0x2152, 0x44bd, {0x8d, 0x8c, 0xdc, 0x5c, 0x14, 0xac, 0x6c, 0x92}};


}

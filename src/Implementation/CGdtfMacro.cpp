//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfMacro.h"
#include "CGdtfDmxChannelFunction.h"
#include "CGdtfMacroDMX.h"
#include "CGdtfMacroVisual.h"


using namespace VectorworksMVR::Filing;

VectorworksMVR::CGdtfMacroImpl::CGdtfMacroImpl()
{
	fMacro = nullptr;
};

VectorworksMVR::CGdtfMacroImpl::~CGdtfMacroImpl()
{
    
}
MvrString VectorworksMVR::CGdtfMacroImpl::GetName()
{
   	if( ! fMacro) return "";

    return fMacro->GetName();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMacroImpl::SetName(MvrString name)
{
  	// Check if valid
	if( ! fMacro) return kVCOMError_NotInitialized;

    fMacro->SetName(name);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMacroImpl::GetChannelFunction(IGdtfDmxChannelFunction** outChannelFunction)
{
	// Check if Set
	if (!fMacro) { return kVCOMError_NotInitialized; }
	

	SceneData::GdtfDmxChannelFunction* gdtfChannelFunction = fMacro->GetChannelFunction();
	if( !gdtfChannelFunction ) { return kVCOMError_NotSet; }

	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfDmxChannelFunctionImpl* pChannelFunction = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDmxChannelFunction, (IVWUnknown**)& pChannelFunction)))
	{
		// Check Casting
		CGdtfDmxChannelFunctionImpl* pResultInterface = static_cast<CGdtfDmxChannelFunctionImpl*>(pChannelFunction);
		if (pResultInterface)
		{
			pResultInterface->setPointer(gdtfChannelFunction);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if ( *outChannelFunction)
	{
		(*outChannelFunction)->Release();
		outChannelFunction = NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out outMacroDmx
	 *outChannelFunction = pChannelFunction;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMacroImpl::SetChannelFunction(IGdtfDmxChannelFunction* newChannelFunction)
{
	// Check if Set
	if (!fMacro) { return kVCOMError_NotInitialized; }	
		
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfDmxChannelFunctionImpl* pChannelFunctionObj = static_cast<CGdtfDmxChannelFunctionImpl*> (newChannelFunction);
	if(!pChannelFunctionObj) { return kVCOMError_InvalidArg; }
	
	SceneData::GdtfDmxChannelFunction* gdtfChannelFunction = pChannelFunctionObj->getPointer();
	fMacro->SetChannelFunction(gdtfChannelFunction);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMacroImpl::CreateMacroDMX(VectorworksMVR::IGdtfMacroDMX** outMacroDmx)
{
	// Check if Set
	if (!fMacro) { return kVCOMError_NotInitialized; }
	
	SceneData::GdtfMacroDMX* gdtfMacroDmx = new SceneData::GdtfMacroDMX();
    fMacro->SetMacroDMX(gdtfMacroDmx);
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfMacroDMXImpl* pMacroDmx = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfMacroDMX, (IVWUnknown**)& pMacroDmx)))
	{
		// Check Casting
		CGdtfMacroDMXImpl* pResultInterface = static_cast<CGdtfMacroDMXImpl* >(pMacroDmx);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(gdtfMacroDmx);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*outMacroDmx)
	{
		(*outMacroDmx)->Release();
		*outMacroDmx = NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outMacroDmx = pMacroDmx;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMacroImpl::CreateMacroVisual(VectorworksMVR::IGdtfMacroVisual** outMacroVisual)
{
	// Check if Set
	if (!fMacro) { return kVCOMError_NotInitialized; }
	
	
	SceneData::GdtfMacroVisual* gdtfMacroVisual = new SceneData::GdtfMacroVisual();
    fMacro->SetMacroVisual(gdtfMacroVisual);
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfMacroVisualImpl* pMacroVisual = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfMacroVisual, (IVWUnknown**)& pMacroVisual)))
	{
		// Check Casting
		CGdtfMacroVisualImpl* pResultInterface = static_cast<CGdtfMacroVisualImpl* >(pMacroVisual);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(gdtfMacroVisual);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*outMacroVisual)
	{
		(*outMacroVisual)->Release();
		*outMacroVisual = NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outMacroVisual = pMacroVisual;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMacroImpl::GetMacroDMX(IGdtfMacroDMX ** outMacroDmx)
{
	// Check if Set
	if (!fMacro) { return kVCOMError_NotInitialized; }
	

	SceneData::GdtfMacroDMX* gdtfMacroDmx = fMacro->GetMacroDMX();
	if( !gdtfMacroDmx ) { return kVCOMError_NotSet; }

	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfMacroDMXImpl* pMacroDmx = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfMacroDMX, (IVWUnknown**)& pMacroDmx)))
	{
		// Check Casting
		CGdtfMacroDMXImpl* pResultInterface = static_cast<CGdtfMacroDMXImpl*>(pMacroDmx);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(gdtfMacroDmx);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if ( *outMacroDmx)
	{
		(*outMacroDmx)->Release();
		 *outMacroDmx = NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out outMacroDmx
	 *outMacroDmx = pMacroDmx;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMacroImpl::GetMacroVisual(IGdtfMacroVisual ** outMacroVisual)
{
	// Check if Set
	if (!fMacro) { return kVCOMError_NotInitialized; }
	

	SceneData::GdtfMacroVisual* gdtfMacroVisual = fMacro->GetMacroVisual();
	if ( !gdtfMacroVisual ) {
		return kVCOMError_NotSet;
	}

	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfMacroVisualImpl* pMacroVisual = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfMacroVisual, (IVWUnknown**)& pMacroVisual)))
	{
		// Check Casting
		CGdtfMacroVisualImpl* pResultInterface = static_cast<CGdtfMacroVisualImpl*>(pMacroVisual);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(gdtfMacroVisual);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if ( *outMacroVisual)
	{
		(*outMacroVisual)->Release();
		 outMacroVisual = NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out outMacroDmx
	 *outMacroVisual = pMacroVisual;
	
	return kVCOMError_NoError;
}

void VectorworksMVR::CGdtfMacroImpl::setPointer(SceneData::GdtfMacro *macro)
{
    fMacro = macro;
}

SceneData::GdtfMacro* VectorworksMVR::CGdtfMacroImpl::getPointer()
{
    return fMacro;
}
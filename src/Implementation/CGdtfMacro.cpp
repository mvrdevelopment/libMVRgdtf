//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfMacro.h"
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

void VectorworksMVR::CGdtfMacroImpl::setPointer(SceneData::GdtfMacro *macro)
{
    fMacro = macro;
}

SceneData::GdtfMacro* VectorworksMVR::CGdtfMacroImpl::getPointer()
{
    return fMacro;
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
		CGdtfMacroDMXImpl* pResultInterface = dynamic_cast<CGdtfMacroDMXImpl* >(pMacroDmx);
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
		CGdtfMacroVisualImpl* pResultInterface = dynamic_cast<CGdtfMacroVisualImpl* >(pMacroVisual);
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
	if( !gdtfMacroDmx ) {
		return kVCOMError_NotSet;
	}

	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfMacroDMXImpl* pMacroDmx = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfMacroDMX, (IVWUnknown**)& pMacroDmx)))
	{
		// Check Casting
		CGdtfMacroDMXImpl* pResultInterface = dynamic_cast<CGdtfMacroDMXImpl*>(pMacroDmx);
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
		 outMacroDmx = NULL;
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
		CGdtfMacroVisualImpl* pResultInterface = dynamic_cast<CGdtfMacroVisualImpl*>(pMacroVisual);
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
//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfWheel.h"
#include "CGdtfWheelSlot.h"


using namespace VectorworksMVR::Filing;

VectorworksMVR::CGdtfWheelImpl::CGdtfWheelImpl()
{
    fWheel = nullptr;
};

VectorworksMVR::CGdtfWheelImpl::~CGdtfWheelImpl()
{
	
};

MvrString VectorworksMVR::CGdtfWheelImpl::GetName()
{
	// Check Data
	if( ! fWheel) return "";
	
    return fWheel->GetName().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelImpl::GetWheelSlotCount(size_t &outCount)
{
	// Check Data
	if( ! fWheel) return kVCOMError_NotInitialized;
	
    outCount = fWheel->GetWheelSlotArray().size();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelImpl::GetWheelSlotAt(size_t at, VectorworksMVR::IGdtfWheelSlot **outPosition)
{
	// Check Data
	if( ! fWheel) return kVCOMError_NotInitialized;
	
    // Check if no Overflow
    if (at >=  fWheel->GetWheelSlotArray().size()) { return kVCOMError_OutOfBounds;  }
    
    
    SceneData::GdtfWheelSlot* gdtfWheelSlot = fWheel->GetWheelSlotArray()[at];
    
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfWheelSlotImpl* pWheelSlotObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfWheelSlot, (IVWUnknown**) & pWheelSlotObj)))
    {
        // Check Casting
        CGdtfWheelSlotImpl* pResultInterface = static_cast<CGdtfWheelSlotImpl* >(pWheelSlotObj);
        if (pResultInterface)
        {
            pResultInterface->setPointer(gdtfWheelSlot);
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
    if (*outPosition)
    {
        (*outPosition)->Release();
        *outPosition		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *outPosition		= pWheelSlotObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelImpl::CreateWheelSlot(MvrString name, IGdtfWheelSlot** outSlot)
{
	// Check Data
	if( ! fWheel) return kVCOMError_NotInitialized;
	
	TXString vwName (name);
	
	SceneData::GdtfWheelSlot* gdtfWheelSlot = fWheel->AddWheelSlot(vwName);
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfWheelSlotImpl* pWheelSlotObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfWheelSlot, (IVWUnknown**) & pWheelSlotObj)))
	{
		// Check Casting
		CGdtfWheelSlotImpl* pResultInterface = static_cast<CGdtfWheelSlotImpl* >(pWheelSlotObj);
		if (pResultInterface)
		{
			pResultInterface->setPointer(gdtfWheelSlot);
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
	if (*outSlot)
	{
		(*outSlot)->Release();
		*outSlot		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outSlot		= pWheelSlotObj;
	
	return kVCOMError_NoError;
}

void VectorworksMVR::CGdtfWheelImpl::SetPointer(SceneData::GdtfWheel *wheel)
{
    fWheel = wheel;
}

SceneData::GdtfWheel* VectorworksMVR::CGdtfWheelImpl::GetPointer()
{
	return fWheel;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelImpl::BindToObject(void* objAddr)
{
	// Check if valid
	if(!fWheel) return kVCOMError_NotInitialized;
	
	fWheel->SetBind(objAddr);
	
	return kVCOMError_NoError;
}

void* VectorworksMVR::CGdtfWheelImpl::GetBoundObject()
{
	// Check if valid
	if(!fWheel) return nullptr;
	
	return fWheel->GetBind();
}

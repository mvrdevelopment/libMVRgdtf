//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfPhysicalEmitter.h"
#include "CGdtfMeasurement.h"


using namespace VectorworksMVR::Filing;

VectorworksMVR::CGdtfPhysicalEmitterImpl::CGdtfPhysicalEmitterImpl()
{
	fEmitter = nullptr;
};

VectorworksMVR::CGdtfPhysicalEmitterImpl::~CGdtfPhysicalEmitterImpl()
{
    
};

MvrString VectorworksMVR::CGdtfPhysicalEmitterImpl::GetName()
{
	// Check if valid
	if(!fEmitter) return "";
	
	// Return the name
    return fEmitter->GetName().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfPhysicalEmitterImpl::GetColor(VectorworksMVR::CieColor &color)
{
	// Check if valid
	if(!fEmitter) return kVCOMError_NotInitialized;
	
    CCieColor col = fEmitter->GetColor();
    color.fx   = col.Get_x();
    color.fy   = col.Get_y();
    color.f_Y  = col.Get_Y_luminance();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfPhysicalEmitterImpl::GetMeasurementCount(size_t &count)
{
	// Check if valid
	if(!fEmitter) return kVCOMError_NotInitialized;
	
    count = fEmitter->GetMeasurements().size();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfPhysicalEmitterImpl::GetMeasurementAt(size_t at, VectorworksMVR::IGdtfMeasurement **outVal)
{
	// Check if valid
	if(!fEmitter) return kVCOMError_NotInitialized;
	
    // Check if no Overflow
    if (at >=  fEmitter->GetMeasurements().size()) { return kVCOMError_OutOfBounds;  }
    
    SceneData::GdtfMeasurement* gdtfMeasurement = fEmitter->GetMeasurements()[at];
    
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfMeasurementImpl* pMeasurementObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfMeasurement, (IVWUnknown**) & pMeasurementObj)))
    {
        // Check Casting
        CGdtfMeasurementImpl* pResultInterface = static_cast<CGdtfMeasurementImpl* >(pMeasurementObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfMeasurement);
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
    if (*outVal)
    {
        (*outVal)->Release();
        *outVal		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *outVal		= pMeasurementObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfPhysicalEmitterImpl::CreateMeasurement(IGdtfMeasurement** outVal)
{
	// Check if valid
	if(!fEmitter) return kVCOMError_NotInitialized;
	
	SceneData::GdtfMeasurement* gdtfMeasurement = fEmitter->AddMeasurement();
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfMeasurementImpl* pMeasurementObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfMeasurement, (IVWUnknown**) & pMeasurementObj)))
	{
		// Check Casting
		CGdtfMeasurementImpl* pResultInterface = static_cast<CGdtfMeasurementImpl* >(pMeasurementObj);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(gdtfMeasurement);
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
	if (*outVal)
	{
		(*outVal)->Release();
		*outVal		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outVal		= pMeasurementObj;
	
	return kVCOMError_NoError;
}

MvrString VCOM_CALLTYPE VectorworksMVR::CGdtfPhysicalEmitterImpl::GetDiodePart()
{
	// Check if valid
	if(!fEmitter) return "";
	
	// Return the name
    return fEmitter->GetDiodePart().GetCharPtr();
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfPhysicalEmitterImpl::GetDominantWaveLength(double & outVal)
{
	// Check if valid
	if(!fEmitter) return kVCOMError_NotInitialized;

    outVal = fEmitter->GetDominantWaveLength();

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfPhysicalEmitterImpl::SetName(MvrString name)
{
	// Check if valid
	if(!fEmitter) return kVCOMError_NotInitialized;

    fEmitter->SetName(name);

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfPhysicalEmitterImpl::SetColor(CieColor & color)
{
	// Check if valid
	if(!fEmitter) return kVCOMError_NotInitialized;
		
	fEmitter->SetColor(CCieColor(color.fx, color.fy, color.f_Y) );

    return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfPhysicalEmitterImpl::SetDiodePart(MvrString val)
{
	// Check if valid
	if(!fEmitter) return kVCOMError_NotInitialized;

    fEmitter->SetDiodePart(val);

	return kVCOMError_NoError;    
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfPhysicalEmitterImpl::SetDominantWaveLength(double val)
{
	// Check if valid
	if(!fEmitter) return kVCOMError_NotInitialized;

    fEmitter->SetDominantWaveLength(val);

	return kVCOMError_NoError;
}

void VectorworksMVR::CGdtfPhysicalEmitterImpl::setPointer(SceneData::GdtfPhysicalEmitter *emitter)
{
    fEmitter = emitter;
}

SceneData::GdtfPhysicalEmitter * VectorworksMVR::CGdtfPhysicalEmitterImpl::GetPointer()
{
    return fEmitter;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfPhysicalEmitterImpl::BindToObject(void* objAddr)
{
	// Check if valid
	if(!fEmitter) return kVCOMError_NotInitialized;
	
	fEmitter->SetBind(objAddr);
	
	return kVCOMError_NoError;
}

void* VectorworksMVR::CGdtfPhysicalEmitterImpl::GetBoundObject()
{
	// Check if valid
	if(!fEmitter) return nullptr;
		
	return fEmitter->GetBind();
}



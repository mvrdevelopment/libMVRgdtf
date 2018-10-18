//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "VectorworksMVR.h"
#include "CGdtfPhysicalEmitter.h"
#include "CGdtfMeasurementPoint.h"


using namespace VectorWorks::Filing;

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

VectorworksMVR::VCOMError VectorworksMVR::CGdtfPhysicalEmitterImpl::GetMeasurementPointCount(size_t &count)
{
	// Check if valid
	if(!fEmitter) return kVCOMError_NotInitialized;
	
    count = fEmitter->GetMeasurementPoints().size();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfPhysicalEmitterImpl::GetMeasurementPointAt(size_t at, VectorworksMVR::IGdtfMeasurementPoint **measurementPoint)
{
	// Check if valid
	if(!fEmitter) return kVCOMError_NotInitialized;
	
    // Check if no Overflow
    if (at >=  fEmitter->GetMeasurementPoints().size()) { return kVCOMError_OutOfBounds;  }
    
    SceneData::GdtfMeasurementPoint* gdtfMeasurementPoint = fEmitter->GetMeasurementPoints()[at];
    
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfMeasurementPointImpl* pMeasurementPointObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfMeasurementPoint, (IVWUnknown**) & pMeasurementPointObj)))
    {
        // Check Casting
        CGdtfMeasurementPointImpl* pResultInterface = dynamic_cast<CGdtfMeasurementPointImpl* >(pMeasurementPointObj);
        if (pResultInterface)
        {
            pResultInterface->setPointer(gdtfMeasurementPoint);
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
    if (*measurementPoint)
    {
        (*measurementPoint)->Release();
        *measurementPoint		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *measurementPoint		= pMeasurementPointObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfPhysicalEmitterImpl::CreateMeasurementPoint(double wavelength, double energy, IGdtfMeasurementPoint** measurementPoint)
{
	// Check if valid
	if(!fEmitter) return kVCOMError_NotInitialized;
	
	SceneData::GdtfMeasurementPoint* gdtfMeasurementPoint = fEmitter->AddMeasurementPoint();
	gdtfMeasurementPoint->SetEnergy(energy);
	gdtfMeasurementPoint->SetWavelength(wavelength);
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfMeasurementPointImpl* pMeasurementPointObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfMeasurementPoint, (IVWUnknown**) & pMeasurementPointObj)))
	{
		// Check Casting
		CGdtfMeasurementPointImpl* pResultInterface = dynamic_cast<CGdtfMeasurementPointImpl* >(pMeasurementPointObj);
		if (pResultInterface)
		{
			pResultInterface->setPointer(gdtfMeasurementPoint);
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
	if (*measurementPoint)
	{
		(*measurementPoint)->Release();
		*measurementPoint		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*measurementPoint		= pMeasurementPointObj;
	
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



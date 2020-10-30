//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfMeasurementPoint.h"


using namespace VectorworksMVR::Filing;

VectorworksMVR::CGdtfMeasurementPointImpl::CGdtfMeasurementPointImpl()
{
	fMeasurementPoint = nullptr;
};

VectorworksMVR::CGdtfMeasurementPointImpl::~CGdtfMeasurementPointImpl()
{
    
};

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMeasurementPointImpl::GetWaveLength(double &wavelength)
{
	// Check if valid
	if(!fMeasurementPoint) return kVCOMError_NotInitialized;
	
    wavelength = fMeasurementPoint->GetWavelength();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMeasurementPointImpl::GetEnergy(double &energy)
{
	// Check if valid
	if(!fMeasurementPoint) return kVCOMError_NotInitialized;
	
    energy = fMeasurementPoint->GetEnergy();
    return kVCOMError_NoError;
}

void VectorworksMVR::CGdtfMeasurementPointImpl::setPointer(SceneData::GdtfMeasurementPoint *measurementPoint)
{
    fMeasurementPoint = measurementPoint;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMeasurementPointImpl::BindToObject(void* objAddr)
{
	// Check if valid
	if(!fMeasurementPoint) return kVCOMError_NotInitialized;
	
	fMeasurementPoint->SetBind(objAddr);
	
	return kVCOMError_NoError;
}

void* VectorworksMVR::CGdtfMeasurementPointImpl::GetBoundObject()
{
	// Check if valid
	if(!fMeasurementPoint) return nullptr;
	
	return fMeasurementPoint->GetBind();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMeasurementPointImpl::SetWaveLength(double wavelength)
{
	if(!fMeasurementPoint) return kVCOMError_NotInitialized;

    fMeasurementPoint->SetWavelength(wavelength);

  	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMeasurementPointImpl::SetEnergy(double energy)
{
	if(!fMeasurementPoint) return kVCOMError_NotInitialized;

    fMeasurementPoint->SetEnergy(energy);

   	return kVCOMError_NoError;
}

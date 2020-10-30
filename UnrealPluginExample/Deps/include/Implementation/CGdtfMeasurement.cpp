//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfMeasurement.h"
#include "CGdtfMeasurementPoint.h"


VectorworksMVR::CGdtfMeasurementImpl::CGdtfMeasurementImpl()
{
    fMeasurement = nullptr;
}

VectorworksMVR::CGdtfMeasurementImpl::~CGdtfMeasurementImpl()
{
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfMeasurementImpl::GetPhysical(double& outVal)
{
    // Check if valid
    if(!fMeasurement) return kVCOMError_NotInitialized;
	
    outVal = fMeasurement->GetPhysical();

    return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfMeasurementImpl::GetLuminousIntensity(double& outVal)
{
    // Check if valid
    if(!fMeasurement) return kVCOMError_NotInitialized;
	
    outVal = fMeasurement->GetLuminousIntensity();

    return kVCOMError_NoError;    
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfMeasurementImpl::GetTransmission(double& outVal)
{
    // Check if valid
    if(!fMeasurement) return kVCOMError_NotInitialized;
	
    outVal = fMeasurement->GetTransmission();

    return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfMeasurementImpl::GetInterpolationTo(EGdtfInterpolationTo& outVal)
{
    // Check if valid
    if(!fMeasurement) return kVCOMError_NotInitialized;
	
    outVal = fMeasurement->GetInterpolationTo();

    return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfMeasurementImpl::SetPhysical(double val)
{
    // Check if valid
    if(!fMeasurement) return kVCOMError_NotInitialized;
	
    fMeasurement->SetPhysical(val);

    return kVCOMError_NoError;    
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfMeasurementImpl::SetLuminousIntensity(double val)
{
    // Check if valid
    if(!fMeasurement) return kVCOMError_NotInitialized;
	
    fMeasurement->SetLuminousIntensity(val);

    return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfMeasurementImpl::SetTransmission(double val)
{
    // Check if valid
    if(!fMeasurement) return kVCOMError_NotInitialized;
	
    fMeasurement->SetTransmission(val);

    return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfMeasurementImpl::SetInterpolationTo(EGdtfInterpolationTo val)
{
    // Check if valid
    if(!fMeasurement) return kVCOMError_NotInitialized;
	
    fMeasurement->SetInterpolationTo(val);

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfMeasurementImpl::GetMeasurementPointCount(size_t &count)
{
    if (!fMeasurement) { return kVCOMError_NotInitialized; }

    count = fMeasurement->GetMeasurementPointsArray().size();

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfMeasurementImpl::GetMeasurementPointAt(size_t at, VectorworksMVR::IGdtfMeasurementPoint** value)
{
    // Check if Set
    if (!fMeasurement) { return kVCOMError_NotInitialized; }

    // Check if no Overflow
    if (at >= fMeasurement->GetMeasurementPointsArray().size()) { return kVCOMError_OutOfBounds; }


    SceneData::GdtfMeasurementPoint* gdtfMeasurementPoint = fMeasurement->GetMeasurementPointsArray()[at];


    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfMeasurementPointImpl* pMeasurementPointObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfMeasurementPoint, (IVWUnknown**)& pMeasurementPointObj)))
    {
        // Check Casting
        CGdtfMeasurementPointImpl* pResultInterface = static_cast<CGdtfMeasurementPointImpl*>(pMeasurementPointObj);
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
    if (*value)
    {
        (*value)->Release();
        *value = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *value = pMeasurementPointObj;

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfMeasurementImpl::CreateMeasurementPoint(VectorworksMVR::IGdtfMeasurementPoint **outVal)
{
    // Check if Set
    if (!fMeasurement) { return kVCOMError_NotInitialized; }


    SceneData::GdtfMeasurementPoint* gdtfMeasurementPoint = fMeasurement->CreateMeasurementPoint();

    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfMeasurementPointImpl* pMeasurementPointObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfMeasurementPoint, (IVWUnknown**)& pMeasurementPointObj)))
    {
        // Check Casting
        CGdtfMeasurementPointImpl* pResultInterface = static_cast<CGdtfMeasurementPointImpl*>(pMeasurementPointObj);
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
    if (*outVal)
    {
        (*outVal)->Release();
        *outVal = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *outVal = pMeasurementPointObj;

    return kVCOMError_NoError;
}


VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfMeasurementImpl::BindToObject(void * objAddr)
{
    // Check if valid
    if (!fMeasurement) return kVCOMError_NotInitialized;

    fMeasurement->SetBind(objAddr);

    return kVCOMError_NoError;
}

void *VCOM_CALLTYPE VectorworksMVR::CGdtfMeasurementImpl::GetBoundObject()
{
    // Check if valid
    if (!fMeasurement) return nullptr;

    return fMeasurement->GetBind();
}

void VectorworksMVR::CGdtfMeasurementImpl::SetPointer(SceneData::GdtfMeasurement * measurement)
{
    fMeasurement = measurement;
}

SceneData::GdtfMeasurement * VectorworksMVR::CGdtfMeasurementImpl::GetPointer()
{
    return fMeasurement;
}

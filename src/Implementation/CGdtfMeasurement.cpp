//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfMeasurement.h"

VectorworksMVR::CGdtfMeasurementImpl::CGdtfMeasurementImpl()
{
    fMeasurement = nullptr;
}

VectorworksMVR::CGdtfMeasurementImpl::~CGdtfMeasurementImpl()
{
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

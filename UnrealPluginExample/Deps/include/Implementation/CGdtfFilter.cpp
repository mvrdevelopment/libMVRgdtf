//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"

#include "CGdtfFilter.h"
#include "CGdtfMeasurement.h"
#include "XmlFileHelper.h"

using namespace VectorworksMVR;


CGdtfFilterImpl::CGdtfFilterImpl()
{
    fFilter = nullptr;
}

VectorworksMVR::CGdtfFilterImpl::~CGdtfFilterImpl()
{
}

MvrString VCOM_CALLTYPE VectorworksMVR::CGdtfFilterImpl::GetName()
{
	if( ! fFilter) return "";
	
	return fFilter->GetName().GetCharPtr();    
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfFilterImpl::GetColor(CieColor& outVal)
{
    // Check if valid
    if(!fFilter) return kVCOMError_NotInitialized;
	
    outVal = SceneData::GdtfConverter::ConvertCColor( fFilter->GetColor() );

    return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfFilterImpl::SetName(MvrString name)
{
    // Check if valid
    if(!fFilter) return kVCOMError_NotInitialized;
	
    fFilter->SetName(name);

    return kVCOMError_NoError;   
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfFilterImpl::SetColor(CieColor val)
{
    // Check if valid
    if(!fFilter) return kVCOMError_NotInitialized;
	
    fFilter->SetColor( SceneData::GdtfConverter::ConvertCColor( val ) );

    return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfFilterImpl::BindToObject(void * objAddr)
{
    // Check if valid
    if (!fFilter) return kVCOMError_NotInitialized;

    fFilter->SetBind(objAddr);

    return kVCOMError_NoError;
}

void *VCOM_CALLTYPE VectorworksMVR::CGdtfFilterImpl::GetBoundObject()
{
    // Check if valid
    if (!fFilter) return nullptr;

    return fFilter->GetBind();
}

void VectorworksMVR::CGdtfFilterImpl::SetPointer(SceneData::GdtfFilter * val)
{
    fFilter = val;
}

SceneData::GdtfFilter * VectorworksMVR::CGdtfFilterImpl::GetPointer()
{
    return fFilter;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfFilterImpl::GetMeasurementCount(size_t &count)
{
    if (!fFilter) { return kVCOMError_NotInitialized; }

    count = fFilter->GetMeasurementsArray().size();

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfFilterImpl::GetMeasurementAt(size_t at, VectorworksMVR::IGdtfMeasurement** value)
{
    // Check if Set
    if (!fFilter) { return kVCOMError_NotInitialized; }

    // Check if no Overflow
    if (at >= fFilter->GetMeasurementsArray().size()) { return kVCOMError_OutOfBounds; }


    SceneData::GdtfMeasurement* gdtfMeasurement = fFilter->GetMeasurementsArray()[at];


    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfMeasurementImpl* pMeasurementObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfMeasurement, (IVWUnknown**)& pMeasurementObj)))
    {
        // Check Casting
        CGdtfMeasurementImpl* pResultInterface = static_cast<CGdtfMeasurementImpl*>(pMeasurementObj);
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
    if (*value)
    {
        (*value)->Release();
        *value = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *value = pMeasurementObj;

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfFilterImpl::CreateMeasurement(VectorworksMVR::IGdtfMeasurement **outVal)
{
    // Check if Set
    if (!fFilter) { return kVCOMError_NotInitialized; }
    
    SceneData::GdtfMeasurement* gdtfMeasurement = fFilter->CreateMeasurement();

    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfMeasurementImpl* pMeasurementObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfMeasurement, (IVWUnknown**)& pMeasurementObj)))
    {
        // Check Casting
        CGdtfMeasurementImpl* pResultInterface = static_cast<CGdtfMeasurementImpl*>(pMeasurementObj);
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
        *outVal = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *outVal = pMeasurementObj;

    return kVCOMError_NoError;
}





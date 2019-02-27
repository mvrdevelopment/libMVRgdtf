//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"

#include "CGdtfFilter.h"
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

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfFilterImpl::GetColor(CieColor outVal)
{
    // Check if valid
    if(!fFilter) return kVCOMError_NotInitialized;
	
    outVal = SceneData::GdtfConverter::ConvertCColor( fFilter->GetColor() );

    return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfFilterImpl::SetName(const TXString & name)
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



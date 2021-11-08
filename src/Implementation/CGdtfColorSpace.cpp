//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------

#include "Prefix/StdAfx.h"
#include "CGdtfColorSpace.h"
#include "XmlFileHelper.h"



using namespace VectorworksMVR;

VectorworksMVR::CGdtfColorSpaceImpl::CGdtfColorSpaceImpl()
{
    fColorSpace = nullptr;
}

VectorworksMVR::CGdtfColorSpaceImpl::~CGdtfColorSpaceImpl()
{   
}

MvrString VectorworksMVR::CGdtfColorSpaceImpl::GetName()
{
	// Check Pointer
	if ( ! fColorSpace) return "";
	
    return fColorSpace->GetName();
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfColorSpaceImpl::GetColorSpace(EGdtfColorSpace& outVal)
{
	//Check Pointer
	if( ! fColorSpace)		return kVCOMError_NotInitialized;    

    outVal = fColorSpace->GetColorSpace();

	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfColorSpaceImpl::GetRed(CieColor& outVal)
{
	//Check Pointer
	if( ! fColorSpace)		return kVCOMError_NotInitialized;    

    outVal = SceneData::GdtfConverter::ConvertCColor (fColorSpace->GetRed() );

	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfColorSpaceImpl::GetGreen(CieColor& outVal)
{
	//Check Pointer
	if( ! fColorSpace)		return kVCOMError_NotInitialized;    

    outVal = SceneData::GdtfConverter::ConvertCColor (fColorSpace->GetGreen() );

    return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfColorSpaceImpl::GetBlue(CieColor& outVal)
{
	//Check Pointer
	if( ! fColorSpace)		return kVCOMError_NotInitialized;    

    outVal = SceneData::GdtfConverter::ConvertCColor( fColorSpace->GetBlue() );

    return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfColorSpaceImpl::GetWhite(CieColor& outVal)
{
	//Check Pointer
	if( ! fColorSpace)		return kVCOMError_NotInitialized;    

    outVal = SceneData::GdtfConverter::ConvertCColor( fColorSpace->GetWhite() );

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfColorSpaceImpl::SetName(MvrString name)
{
	if(!fColorSpace) return kVCOMError_NotInitialized;	
	
    fColorSpace->SetName(name);

   	return kVCOMError_NoError;   
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfColorSpaceImpl::SetColorSpace(EGdtfColorSpace val)
{
	//Check Pointer
	if( ! fColorSpace)		return kVCOMError_NotInitialized;    

	fColorSpace->SetColorSpace(val);
	
    return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfColorSpaceImpl::SetRed(CieColor val)
{
	//Check Pointer
	if( ! fColorSpace)		return kVCOMError_NotInitialized;    

    fColorSpace->SetRed( SceneData::GdtfConverter::ConvertCColor (val) );

	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfColorSpaceImpl::SetGreen(CieColor val)
{
	//Check Pointer
	if( ! fColorSpace)		return kVCOMError_NotInitialized;    

    fColorSpace->SetGreen( SceneData::GdtfConverter::ConvertCColor(val) );

	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfColorSpaceImpl::SetBlue(CieColor val)
{
	//Check Pointer
	if( ! fColorSpace)		return kVCOMError_NotInitialized;    

    fColorSpace->SetBlue( SceneData::GdtfConverter::ConvertCColor(val) );

	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfColorSpaceImpl::SetWhite(CieColor val)
{
	//Check Pointer
	if( ! fColorSpace)		return kVCOMError_NotInitialized;    

    fColorSpace->SetWhite( SceneData::GdtfConverter::ConvertCColor(val) );

	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfColorSpaceImpl::BindToObject(void * objAddr)
{
    // Check if valid
    if (!fColorSpace) return kVCOMError_NotInitialized;

    fColorSpace->SetBind(objAddr);

    return kVCOMError_NoError;
}

void *VCOM_CALLTYPE VectorworksMVR::CGdtfColorSpaceImpl::GetBoundObject()
{
    // Check if valid
    if (!fColorSpace) return nullptr;

    return fColorSpace->GetBind();
}

void VectorworksMVR::CGdtfColorSpaceImpl::SetPointer(SceneData::GdtfColorSpace * ColorSpace)
{
    fColorSpace = ColorSpace;
}

SceneData::GdtfColorSpace * VectorworksMVR::CGdtfColorSpaceImpl::GetPointer()
{
    return fColorSpace;
}

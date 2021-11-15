//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfGamut.h"
#include "XmlFileHelper.h"


using namespace VectorworksMVR::Filing;

VectorworksMVR::CGdtfGamutImpl::CGdtfGamutImpl()
{
	fGamut = nullptr;
};

VectorworksMVR::CGdtfGamutImpl::~CGdtfGamutImpl()
{
    
};

MvrString VectorworksMVR::CGdtfGamutImpl::GetName()
{
	// Check Pointer
	if ( ! fGamut) { return ""; }
	
    return fGamut->GetName().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGamutImpl::SetName(MvrString name)
{
	if( ! fGamut) return kVCOMError_NotInitialized;	
	
    fGamut->SetName(name);

   	return kVCOMError_NoError;    
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGamutImpl::GetPointCount(size_t& count)
{
	// Check Pointer
	if ( ! fGamut) { return kVCOMError_NotInitialized; }
	
	count = fGamut->GetGamutPoints().size();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGamutImpl::GetPointAt(size_t at, CieColor& outColor)
{
	// Check Pointer
	if ( ! fGamut) { return kVCOMError_NotInitialized; }
	
	// check overflow
	if (fGamut->GetGamutPoints().size() < at) { return kVCOMError_OutOfBounds; }

	CCieColorPtr colorPtr = fGamut->GetGamutPoints()[at];

	outColor = SceneData::GdtfConverter::ConvertCColor(*colorPtr);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGamutImpl::CreatePoint(CieColor& color)
{
	// Check Pointer
	if ( ! fGamut) { return kVCOMError_NotInitialized; }

	CCieColorPtr cieColor = new CCieColor(color.fx, color.fy, color.f_Y);

	fGamut->AddGamutPoint(cieColor);

	return kVCOMError_NoError;
}

void VectorworksMVR::CGdtfGamutImpl::SetPointer(SceneData::GdtfGamut* gamut)
{
    fGamut = gamut;
}

SceneData::GdtfGamut* VectorworksMVR::CGdtfGamutImpl::GetPointer()
{
    return fGamut;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGamutImpl::BindToObject(void* objAddr)
{
	// Check if valid
	if(!fGamut) return kVCOMError_NotInitialized;
	
	fGamut->SetBind(objAddr);
	
	return kVCOMError_NoError;
}

void* VectorworksMVR::CGdtfGamutImpl::GetBoundObject()
{
	// Check if valid
	if(!fGamut) return nullptr;
	
	return fGamut->GetBind();
}

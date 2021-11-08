//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfPoint.h"

VectorworksMVR::CGdtfPointImpl::CGdtfPointImpl()
{
}

VectorworksMVR::CGdtfPointImpl::~CGdtfPointImpl()
{
    fPoint = nullptr;
}

// Getters
VCOMError VCOM_CALLTYPE	CGdtfPointImpl::GetDMXPercentage(double& dmxPercentage)
{
    if(!fPoint) {return kVCOMError_NotInitialized;}
	
	dmxPercentage = fPoint->GetDMXPercentage();
	
	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE	CGdtfPointImpl::GetCFC3(double& cfc3)
{
    if(!fPoint) {return kVCOMError_NotInitialized;}
	
	cfc3 = fPoint->GetCFC3();
	
	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE	CGdtfPointImpl::GetCFC2(double& cfc2)
{
    if(!fPoint) {return kVCOMError_NotInitialized;}
	
	cfc2 = fPoint->GetCFC2();
	
	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE	CGdtfPointImpl::GetCFC1(double& cfc1)
{
    if(!fPoint) {return kVCOMError_NotInitialized;}
	
	cfc1 = fPoint->GetCFC1();
	
	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE	CGdtfPointImpl::GetCFC0(double& cfc0)
{
    if(!fPoint) {return kVCOMError_NotInitialized;}
	
	cfc0 = fPoint->GetCFC0();
	
	return kVCOMError_NoError;
}

// Setters
VCOMError VCOM_CALLTYPE	CGdtfPointImpl::SetDMXPercentage(double dmxPercentage)
{
    if(!fPoint) {return kVCOMError_NotInitialized;}
	
	fPoint->SetDMXPercentage(dmxPercentage);
	
	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE	CGdtfPointImpl::SetCFC3(double cfc3)
{
    if(!fPoint) {return kVCOMError_NotInitialized;}
	
	fPoint->SetCFC3(cfc3);
	
	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE	CGdtfPointImpl::SetCFC2(double cfc2)
{
    if(!fPoint) {return kVCOMError_NotInitialized;}
	
	fPoint->SetCFC2(cfc2);
	
	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE	CGdtfPointImpl::SetCFC1(double cfc1)
{
    if(!fPoint) {return kVCOMError_NotInitialized;}
	
	fPoint->SetCFC1(cfc1);
	
	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE	CGdtfPointImpl::SetCFC0(double cfc0)
{
    if(!fPoint) {return kVCOMError_NotInitialized;}
	
	fPoint->SetCFC0(cfc0);
	
	return kVCOMError_NoError;
}

// Bind
VectorworksMVR::VCOMError VectorworksMVR::CGdtfPointImpl::BindToObject(void * objAddr)
{
    // Check if valid
    if (!fPoint) return kVCOMError_NotInitialized;

    fPoint->SetBind(objAddr);

    return kVCOMError_NoError;
}

void* VectorworksMVR::CGdtfPointImpl::GetBoundObject()
{
    // Check if valid
    if (!fPoint) return nullptr;

    return fPoint->GetBind();
}

void VectorworksMVR::CGdtfPointImpl::SetPointer(SceneData::GdtfPoint* point)
{
    fPoint = point;
}

SceneData::GdtfPoint* VectorworksMVR::CGdtfPointImpl::GetPointer()
{ 
    return fPoint;
}

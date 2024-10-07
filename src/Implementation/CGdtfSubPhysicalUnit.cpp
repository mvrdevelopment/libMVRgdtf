//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfSubPhysicalUnit.h"


using namespace VectorworksMVR::Filing;

VectorworksMVR::CGdtfSubPhysicalUnitImpl::CGdtfSubPhysicalUnitImpl()
{
	fSubPhysicalUnit = nullptr;
};

VectorworksMVR::CGdtfSubPhysicalUnitImpl::~CGdtfSubPhysicalUnitImpl()
{
    
};

VectorworksMVR::VCOMError VectorworksMVR::CGdtfSubPhysicalUnitImpl::GetType(GdtfDefines::EGdtfSubPhysicalUnitType& type)
{
	// Check Pointer
	if ( ! fSubPhysicalUnit) return kVCOMError_NotInitialized;
	
    type = fSubPhysicalUnit->GetType();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfSubPhysicalUnitImpl::GetPhysicalFrom(double& physicalFrom)
{
	// Check Pointer
	if ( ! fSubPhysicalUnit) return kVCOMError_NotInitialized;
	
    physicalFrom = fSubPhysicalUnit->GetPhysicalFrom();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfSubPhysicalUnitImpl::GetPhysicalTo(double& physicalTo)
{
	// Check Pointer
	if ( ! fSubPhysicalUnit) return kVCOMError_NotInitialized;
	
    physicalTo = fSubPhysicalUnit->GetPhysicalTo();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfSubPhysicalUnitImpl::GetPhysicalUnit(GdtfDefines::EGdtfPhysicalUnit& unit)
{
	// Check Pointer
	if ( ! fSubPhysicalUnit) return kVCOMError_NotInitialized;

	unit = fSubPhysicalUnit->GetPhysicalUnit();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfSubPhysicalUnitImpl::SetType(GdtfDefines::EGdtfSubPhysicalUnitType type)
{
	// Check Pointer
	if( ! fSubPhysicalUnit) return kVCOMError_NotInitialized;

    fSubPhysicalUnit->SetType(type);

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfSubPhysicalUnitImpl::SetPhysicalFrom(double physicalFrom)
{
	// Check Pointer
	if( ! fSubPhysicalUnit) return kVCOMError_NotInitialized;

    fSubPhysicalUnit->SetPhysicalFrom(physicalFrom);

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfSubPhysicalUnitImpl::SetPhysicalUnit(GdtfDefines::EGdtfPhysicalUnit& unit)
{
	// Check Pointer
	if( ! fSubPhysicalUnit) return kVCOMError_NotInitialized;

	fSubPhysicalUnit->SetPhysicalUnit(unit);

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfSubPhysicalUnitImpl::SetPhysicalTo(double physicalTo)
{
	// Check Pointer
	if( ! fSubPhysicalUnit) return kVCOMError_NotInitialized;

    fSubPhysicalUnit->SetPhysicalTo(physicalTo);

	return kVCOMError_NoError;
}

void VectorworksMVR::CGdtfSubPhysicalUnitImpl::SetPointer(SceneData::GdtfSubPhysicalUnit* subPhysicalUnit)
{
    fSubPhysicalUnit = subPhysicalUnit;
}

SceneData::GdtfSubPhysicalUnit* VectorworksMVR::CGdtfSubPhysicalUnitImpl::GetPointer()
{
    return fSubPhysicalUnit;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfSubPhysicalUnitImpl::BindToObject(void* objAddr)
{
	// Check if valid
	if(!fSubPhysicalUnit) return kVCOMError_NotInitialized;
	
	fSubPhysicalUnit->SetBind(objAddr);
	
	return kVCOMError_NoError;
}

void* VectorworksMVR::CGdtfSubPhysicalUnitImpl::GetBoundObject()
{
	// Check if valid
	if(!fSubPhysicalUnit) return nullptr;
	
	return fSubPhysicalUnit->GetBind();
}

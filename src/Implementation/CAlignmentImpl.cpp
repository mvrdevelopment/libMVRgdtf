//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CAlignmentImpl.h"
#include "Utility.h"


VectorworksMVR::CAlignmentImpl::CAlignmentImpl()
{
	fPtr = nullptr;
}

VectorworksMVR::CAlignmentImpl::~CAlignmentImpl()
{
	fPtr = nullptr;
}

MvrString VectorworksMVR::CAlignmentImpl::GetBeamGeometry()
{
	// Check if this is initialized
	ASSERTN(kEveryone, fPtr);
	if( ! fPtr) return "";
	
	// Otherwise return data
	return fPtr->GetBeamGeometry().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CAlignmentImpl::GetUpVector(SVector3& upVector)
{
	// Check if this is initialized
	ASSERTN(kEveryone, fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	GdtfUtil::ConvertVector3(fPtr->GetUpVector(), upVector);

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CAlignmentImpl::GetDirection(SVector3& direction)
{
	// Check if this is initialized
	ASSERTN(kEveryone, fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	GdtfUtil::ConvertVector3(fPtr->GetDirection(), direction);

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CAlignmentImpl::SetBeamGeometry(const MvrString& beamGeometry)
{
	// Check if this is initialized
	ASSERTN(kEveryone, fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	fPtr->SetBeamGeometry(beamGeometry);

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CAlignmentImpl::SetUpVector(double x, double y, double z)
{
	// Check if this is initialized
	ASSERTN(kEveryone, fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	fPtr->SetUpVector(x, y, z);

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CAlignmentImpl::SetDirection(double x, double y, double z)
{
	// Check if this is initialized
	ASSERTN(kEveryone, fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	fPtr->SetDirection(x, y, z);

	return kVCOMError_NoError;
}


void VectorworksMVR::CAlignmentImpl::SetPointer(SceneData::SceneDataAlignmentPtr pointer)
{
	fPtr = pointer;
}

void VectorworksMVR::CAlignmentImpl::GetPointer(SceneData::SceneDataAlignmentPtr& pointer)
{
	pointer = fPtr;
}

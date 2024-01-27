//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfWheelSlotAnimationSystem.h"

using namespace VectorworksMVR::Filing;

VectorworksMVR::CGdtfWheelSlotAnimationSystemImpl::CGdtfWheelSlotAnimationSystemImpl()
{
	fAnimationSystem = nullptr;
};

VectorworksMVR::CGdtfWheelSlotAnimationSystemImpl::~CGdtfWheelSlotAnimationSystemImpl()
{
    
};

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotAnimationSystemImpl::GetP1_X(double& p1_X)
{
	// Check Data
	if( ! fAnimationSystem) return kVCOMError_NotInitialized;
	
    p1_X = fAnimationSystem->GetP1_X();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotAnimationSystemImpl::GetP1_Y(double& p1_Y)
{
	// Check Data
	if( ! fAnimationSystem) return kVCOMError_NotInitialized;
	
    p1_Y = fAnimationSystem->GetP1_Y();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotAnimationSystemImpl::GetP2_X(double& p2_X)
{
	// Check Data
	if( ! fAnimationSystem) return kVCOMError_NotInitialized;
	
    p2_X = fAnimationSystem->GetP2_X();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotAnimationSystemImpl::GetP2_Y(double& p2_Y)
{
	// Check Data
	if( ! fAnimationSystem) return kVCOMError_NotInitialized;
	
    p2_Y = fAnimationSystem->GetP2_Y();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotAnimationSystemImpl::GetP3_X(double& p3_X)
{
	// Check Data
	if( ! fAnimationSystem) return kVCOMError_NotInitialized;
	
    p3_X = fAnimationSystem->GetP3_X();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotAnimationSystemImpl::GetP3_Y(double& p3_Y)
{
	// Check Data
	if( ! fAnimationSystem) return kVCOMError_NotInitialized;
	
    p3_Y = fAnimationSystem->GetP3_Y();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotAnimationSystemImpl::GetRadius(double& radius)
{
	// Check Data
	if( ! fAnimationSystem) return kVCOMError_NotInitialized;
	
    radius = fAnimationSystem->GetRadius();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotAnimationSystemImpl::SetP1_X(double p1_X)
{
	// Check Data
	if( ! fAnimationSystem) return kVCOMError_NotInitialized;
	
	fAnimationSystem->SetP1_X(p1_X);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotAnimationSystemImpl::SetP1_Y(double p1_Y)
{
	// Check Data
	if( ! fAnimationSystem) return kVCOMError_NotInitialized;
	
	fAnimationSystem->SetP1_Y(p1_Y);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotAnimationSystemImpl::SetP2_X(double p2_X)
{
	// Check Data
	if( ! fAnimationSystem) return kVCOMError_NotInitialized;
	
	fAnimationSystem->SetP2_X(p2_X);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotAnimationSystemImpl::SetP2_Y(double p2_Y)
{
	// Check Data
	if( ! fAnimationSystem) return kVCOMError_NotInitialized;
	
	fAnimationSystem->SetP2_Y(p2_Y);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotAnimationSystemImpl::SetP3_X(double p3_X)
{
	// Check Data
	if( ! fAnimationSystem) return kVCOMError_NotInitialized;
	
	fAnimationSystem->SetP3_X(p3_X);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotAnimationSystemImpl::SetP3_Y(double p3_Y)
{
	// Check Data
	if( ! fAnimationSystem) return kVCOMError_NotInitialized;
	
	fAnimationSystem->SetP3_Y(p3_Y);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotAnimationSystemImpl::SetRadius(double radius)
{
	// Check Data
	if( ! fAnimationSystem) return kVCOMError_NotInitialized;
	
	fAnimationSystem->SetRadius(radius);
	
	return kVCOMError_NoError;
}

void VectorworksMVR::CGdtfWheelSlotAnimationSystemImpl::setPointer(SceneData::GdtfWheelSlotAnimationSystem* animationSystem)
{
    fAnimationSystem = animationSystem;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfWheelSlotAnimationSystemImpl::BindToObject(void* objAddr)
{
	// Check if valid
	if(!fAnimationSystem) return kVCOMError_NotInitialized;
	
	fAnimationSystem->SetBind(objAddr);
	
	return kVCOMError_NoError;
}

void* VectorworksMVR::CGdtfWheelSlotAnimationSystemImpl::GetBoundObject()
{
	// Check if valid
	if(!fAnimationSystem) return nullptr;
	
	return fAnimationSystem->GetBind();
}

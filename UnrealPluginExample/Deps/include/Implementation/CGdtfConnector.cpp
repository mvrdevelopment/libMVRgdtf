//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfConnector.h"


VectorworksMVR::CGdtfConnectorImpl::CGdtfConnectorImpl()
{
	fConnector = nullptr;
};

VectorworksMVR::CGdtfConnectorImpl::~CGdtfConnectorImpl()
{
    
};

MvrString VectorworksMVR::CGdtfConnectorImpl::GetName()
{
	// Check if valid
	if(!fConnector) return "";
	
	// Return the name
    return fConnector->GetName().GetCharPtr();
}

MvrString VectorworksMVR::CGdtfConnectorImpl::GetType()
{
	// Check if valid
	if(!fConnector) return "";
	
	// Return the name
    return fConnector->GetType().GetCharPtr();
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfConnectorImpl::GetDmxBreak(Uint32& outDmxBreak)
{
	// Check if valid
	if(!fConnector) return kVCOMError_NotInitialized;

    outDmxBreak = fConnector->GetDmxBreak();

	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfConnectorImpl::GetGender(Sint32& outGender)
{
	// Check if valid
	if(!fConnector) return kVCOMError_NotInitialized;

    outGender = fConnector->GetGender();

	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfConnectorImpl::GetLength(double& outLength)
{
	// Check if valid
	if(!fConnector) return kVCOMError_NotInitialized;

    outLength = fConnector->GetLength();

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfConnectorImpl::SetName(MvrString name)
{
	// Check if valid
	if(!fConnector) return kVCOMError_NotInitialized;

    fConnector->SetName(name);

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfConnectorImpl::SetType(MvrString type)
{
	// Check if valid
	if(!fConnector) return kVCOMError_NotInitialized;

    fConnector->SetName(type);

	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfConnectorImpl::SetDmxBreak(Uint32 dmxBreak)
{
	// Check if valid
	if(!fConnector) return kVCOMError_NotInitialized;

    fConnector->SetDmxBreak(dmxBreak);

	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfConnectorImpl::SetGender(Sint32 gender)
{
	// Check if valid
	if(!fConnector) return kVCOMError_NotInitialized;

    fConnector->SetGender(gender);

	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfConnectorImpl::SetLength(double length)
{
	// Check if valid
	if(!fConnector) return kVCOMError_NotInitialized;

    fConnector->SetLength(length);

	return kVCOMError_NoError;
}

void VectorworksMVR::CGdtfConnectorImpl::SetPointer(SceneData::GdtfConnector* connector)
{
    fConnector = connector;
}

SceneData::GdtfConnector * VectorworksMVR::CGdtfConnectorImpl::GetPointer()
{
    return fConnector;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfConnectorImpl::BindToObject(void* objAddr)
{
	// Check if valid
	if(!fConnector) return kVCOMError_NotInitialized;
	
	fConnector->SetBind(objAddr);
	
	return kVCOMError_NoError;
}

void* VectorworksMVR::CGdtfConnectorImpl::GetBoundObject()
{
	// Check if valid
	if(!fConnector) return nullptr;
		
	return fConnector->GetBind();
}



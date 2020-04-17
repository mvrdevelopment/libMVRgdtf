//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfPowerConsumption.h"
#include "CGdtfConnector.h"


VectorworksMVR::CGdtfPowerConsumptionImpl::CGdtfPowerConsumptionImpl()
{
	fPowerConsumption = nullptr;
};

VectorworksMVR::CGdtfPowerConsumptionImpl::~CGdtfPowerConsumptionImpl()
{
    
};

//-----------------------------------------------------------------------------------------------------------------------
//Getters
VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfPowerConsumptionImpl::GetValue(double& outValue)
{
	// Check if valid
	if(!fPowerConsumption) return kVCOMError_NotInitialized;

    outValue = fPowerConsumption->GetValue();

	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfPowerConsumptionImpl::GetPowerFactor(double& outPowerFactor)
{
	// Check if valid
	if(!fPowerConsumption) return kVCOMError_NotInitialized;

    outPowerFactor = fPowerConsumption->GetPowerFactor();

	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfPowerConsumptionImpl::GetConnector(IGdtfConnector** outConnector)
{
    // Check Pointer
    if (!fPowerConsumption) { return kVCOMError_NotInitialized; }

    //---------------------------------------------------------------------------
    // Initialize Object
    SceneData::GdtfConnector*	gdtfConnector = fPowerConsumption->GetConnector();
    if (!gdtfConnector) { return kVCOMError_NotSet; }

    CGdtfConnectorImpl*		pConnectorObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfConnector, (IVWUnknown**)& pConnectorObj)))
    {
        // Check Casting
        CGdtfConnectorImpl* pResultInterface = dynamic_cast<CGdtfConnectorImpl*>(pConnectorObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfConnector);
        }
        else
        {
            pResultInterface->Release();
            pResultInterface = nullptr;
            return kVCOMError_NoInterface;
        }
    }

    //---------------------------------------------------------------------------
    // Check Incoming Object
    if (*outConnector)
    {
        (*outConnector)->Release();
        *outConnector = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *outConnector = pConnectorObj;

    return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfPowerConsumptionImpl::GetVoltageLow(double& outVoltageLow)
{
	// Check if valid
	if(!fPowerConsumption) return kVCOMError_NotInitialized;

    outVoltageLow = fPowerConsumption->GetVoltageLow();

	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfPowerConsumptionImpl::GetVoltageHigh(double& outVoltageHigh)
{
	// Check if valid
	if(!fPowerConsumption) return kVCOMError_NotInitialized;

    outVoltageHigh = fPowerConsumption->GetVoltageHigh();

	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfPowerConsumptionImpl::GetFrequencyLow(double& outFrequencyLow)
{
	// Check if valid
	if(!fPowerConsumption) return kVCOMError_NotInitialized;

    outFrequencyLow = fPowerConsumption->GetFrequencyLow();

	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfPowerConsumptionImpl::GetFrequencyHigh(double& outFrequencyHigh)
{
	// Check if valid
	if(!fPowerConsumption) return kVCOMError_NotInitialized;

    outFrequencyHigh = fPowerConsumption->GetFrequencyHigh();

	return kVCOMError_NoError;
}

//-----------------------------------------------------------------------------------------------------------------------
//Setters
VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfPowerConsumptionImpl::SetValue(double value)
{
	// Check if valid
	if(!fPowerConsumption) return kVCOMError_NotInitialized;

    fPowerConsumption->SetValue(value);

	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfPowerConsumptionImpl::SetPowerFactor(double powerFactor)
{
	// Check if valid
	if(!fPowerConsumption) return kVCOMError_NotInitialized;

    fPowerConsumption->SetPowerFactor(powerFactor);

	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfPowerConsumptionImpl::SetConnector(IGdtfConnector* connector)
{
    if (!fPowerConsumption) { return kVCOMError_NotInitialized; }
    if (!connector) { return kVCOMError_InvalidArg; }

    // Cast
    CGdtfConnectorImpl* connectorImpl = dynamic_cast<CGdtfConnectorImpl*>(connector);
    if (!connectorImpl) { return kVCOMError_Failed; }

    // Set Object
    SceneData::GdtfConnector* gdtfConnector = connectorImpl->GetPointer();
    if (!gdtfConnector) { return kVCOMError_Failed; }

    fPowerConsumption->SetConnector(gdtfConnector);

    return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfPowerConsumptionImpl::SetVoltageLow(double voltageLow)
{
	// Check if valid
	if(!fPowerConsumption) return kVCOMError_NotInitialized;

    fPowerConsumption->SetVoltageLow(voltageLow);

	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfPowerConsumptionImpl::SetVoltageHigh(double voltageHigh)
{
	// Check if valid
	if(!fPowerConsumption) return kVCOMError_NotInitialized;

    fPowerConsumption->SetVoltageHigh(voltageHigh);

	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfPowerConsumptionImpl::SetFrequencyLow(double frequencyLow)
{
	// Check if valid
	if(!fPowerConsumption) return kVCOMError_NotInitialized;

    fPowerConsumption->SetFrequencyLow(frequencyLow);

	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfPowerConsumptionImpl::SetFrequencyHigh(double frequencyHigh)
{
	// Check if valid
	if(!fPowerConsumption) return kVCOMError_NotInitialized;

    fPowerConsumption->SetFrequencyHigh(frequencyHigh);

	return kVCOMError_NoError;
}

void VectorworksMVR::CGdtfPowerConsumptionImpl::SetPointer(SceneData::GdtfPowerConsumption* powerConsumption)
{
    fPowerConsumption = powerConsumption;
}

SceneData::GdtfPowerConsumption * VectorworksMVR::CGdtfPowerConsumptionImpl::GetPointer()
{
    return fPowerConsumption;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfPowerConsumptionImpl::BindToObject(void* objAddr)
{
	// Check if valid
	if(!fPowerConsumption) return kVCOMError_NotInitialized;
	
	fPowerConsumption->SetBind(objAddr);
	
	return kVCOMError_NoError;
}

void* VectorworksMVR::CGdtfPowerConsumptionImpl::GetBoundObject()
{
	// Check if valid
	if(!fPowerConsumption) return nullptr;
		
	return fPowerConsumption->GetBind();
}



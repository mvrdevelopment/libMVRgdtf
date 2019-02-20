//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfFTRDM.h"
#include "CGdtfSoftwareVersionID.h"

VectorworksMVR::CGdtf_FTRDMImpl::CGdtf_FTRDMImpl()
{
	f_FtRDM = nullptr;
};

VectorworksMVR::CGdtf_FTRDMImpl::~CGdtf_FTRDMImpl()
{
    
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtf_FTRDMImpl::GetManufacturerID(Sint32& outVal)
{
    // Check Data
    if (!f_FtRDM) return kVCOMError_NotInitialized;

    outVal = f_FtRDM->GetManufacturerID();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtf_FTRDMImpl::SetManufacturerID(Sint32 value)
{
    // Check Pointer
    if (!f_FtRDM) return kVCOMError_NotInitialized;

    f_FtRDM->SetManufacturerID (value);

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtf_FTRDMImpl::BindToObject(void * objAddr)
{
    // Check if valid
    if (!f_FtRDM) return kVCOMError_NotInitialized;

    f_FtRDM->SetBind(objAddr);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtf_FTRDMImpl::GetDeviceModelID(Sint32& outVal)
{

    // Check Data
    if (!f_FtRDM) return kVCOMError_NotInitialized;

    outVal = f_FtRDM->GetDeviceModelID();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtf_FTRDMImpl::GetSoftwareVersionIDCount(size_t &count)
{
    if (!f_FtRDM) { return kVCOMError_NotInitialized; }

    count = f_FtRDM->GetSoftwareVersIDs().size();

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtf_FTRDMImpl::GetSoftwareVersionIDAt(size_t at, VectorworksMVR::IGdtfSoftwareVersionID** value)
{
    // Check if Set
    if (!f_FtRDM) { return kVCOMError_NotInitialized; }

    // Check if no Overflow
    if (at >= f_FtRDM->GetSoftwareVersIDs().size()) { return kVCOMError_OutOfBounds; }


    SceneData::GdtfSoftwareVersionID* gdtfSoftwareVersionID = f_FtRDM->GetSoftwareVersIDs()[at];


    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfSoftwareVersionIDImpl* pSoftwareVersionIDObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfSoftwareVersionID, (IVWUnknown**)& pSoftwareVersionIDObj)))
    {
        // Check Casting
        CGdtfSoftwareVersionIDImpl* pResultInterface = dynamic_cast<CGdtfSoftwareVersionIDImpl*>(pSoftwareVersionIDObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfSoftwareVersionID);
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
    *value = pSoftwareVersionIDObj;

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtf_FTRDMImpl::CreateSoftwareVersionID(VectorworksMVR::IGdtfSoftwareVersionID **outVal)
{
    // Check if Set
    if (!f_FtRDM) { return kVCOMError_NotInitialized; }


    SceneData::GdtfSoftwareVersionID* gdtfSoftwareVersionID = f_FtRDM->AddSoftwareVersionID();

    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfSoftwareVersionIDImpl* pSoftwareVersionIDObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfSoftwareVersionID, (IVWUnknown**)& pSoftwareVersionIDObj)))
    {
        // Check Casting
        CGdtfSoftwareVersionIDImpl* pResultInterface = dynamic_cast<CGdtfSoftwareVersionIDImpl*>(pSoftwareVersionIDObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfSoftwareVersionID);
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
    *outVal = pSoftwareVersionIDObj;

    return kVCOMError_NoError;
}



VectorworksMVR::VCOMError VectorworksMVR::CGdtf_FTRDMImpl::SetDeviceModelID(Sint32 value)
{
    // Check Pointer
    if (!f_FtRDM) return kVCOMError_NotInitialized;

    f_FtRDM->SetDeviceModelID (value);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtf_FTRDMImpl::GetSoftwareIDCount(size_t& count)
{
    // Check Data
    if (!f_FtRDM) return kVCOMError_NotInitialized;

    count = f_FtRDM->GetSoftwareVersIDs().size();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtf_FTRDMImpl::GetSoftwareIDAt(size_t at, Sint32& outVal)
{
	// Check Data
	if (!f_FtRDM) return kVCOMError_NotInitialized;
	
	if(f_FtRDM->GetSoftwareVersIDs().size() <= (at + 1)) { return  kVCOMError_OutOfBounds; }
	
	outVal = f_FtRDM->GetSoftwareVersIDs().at(at);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtf_FTRDMImpl::AddSoftwareID(Sint32 softID)
{
    // Check Pointer
    if (!f_FtRDM) return kVCOMError_NotInitialized;

    f_FtRDM->AddSoftwareVersID(softID);

    return kVCOMError_NoError;
}

void *VCOM_CALLTYPE VectorworksMVR::CGdtf_FTRDMImpl::GetBoundObject()
{
    // Check if valid
    if (!f_FtRDM) return nullptr;

    return f_FtRDM->GetBind();
}

void VectorworksMVR::CGdtf_FTRDMImpl::SetPointer(SceneData::GdtfFTRDM * value)
{
    f_FtRDM = value;
}

SceneData::GdtfFTRDM * VectorworksMVR::CGdtf_FTRDMImpl::GetPointer()
{
    return f_FtRDM;
}

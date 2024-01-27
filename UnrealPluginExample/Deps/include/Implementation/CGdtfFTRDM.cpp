//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfFTRDM.h"
#include "CGdtfSoftwareVersionID.h"

using namespace VectorworksMVR;

CGdtf_FTRDMImpl::CGdtf_FTRDMImpl()
{
	f_FtRDM = nullptr;
};

CGdtf_FTRDMImpl::~CGdtf_FTRDMImpl()
{
    
}

VCOMError CGdtf_FTRDMImpl::GetManufacturerID(size_t& outVal)
{
    // Check Data
    if (!f_FtRDM) return kVCOMError_NotInitialized;

    outVal = f_FtRDM->GetManufacturerID();

    return kVCOMError_NoError;
}

VCOMError CGdtf_FTRDMImpl::SetManufacturerID(size_t value)
{
    // Check Pointer
    if (!f_FtRDM) return kVCOMError_NotInitialized;

    f_FtRDM->SetManufacturerID (value);

    return kVCOMError_NoError;
}


VCOMError VCOM_CALLTYPE CGdtf_FTRDMImpl::BindToObject(void * objAddr)
{
    // Check if valid
    if (!f_FtRDM) return kVCOMError_NotInitialized;

    f_FtRDM->SetBind(objAddr);

    return kVCOMError_NoError;
}

VCOMError CGdtf_FTRDMImpl::GetDeviceModelID(size_t& outVal)
{

    // Check Data
    if (!f_FtRDM) return kVCOMError_NotInitialized;

    outVal = f_FtRDM->GetDeviceModelID();

    return kVCOMError_NoError;
}

VCOMError CGdtf_FTRDMImpl::GetSoftwareVersionIDCount(size_t &count)
{
    if (!f_FtRDM) { return kVCOMError_NotInitialized; }

    count = f_FtRDM->GetSoftwareVersIDs().size();

    return kVCOMError_NoError;
}


VCOMError CGdtf_FTRDMImpl::GetSoftwareVersionIDAt(size_t at, IGdtfSoftwareVersionID** value)
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
        CGdtfSoftwareVersionIDImpl* pResultInterface = static_cast<CGdtfSoftwareVersionIDImpl*>(pSoftwareVersionIDObj);
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


VCOMError CGdtf_FTRDMImpl::CreateSoftwareVersionID(size_t value, IGdtfSoftwareVersionID **outVal)
{
    // Check if Set
    if (!f_FtRDM) { return kVCOMError_NotInitialized; }


    SceneData::GdtfSoftwareVersionID* gdtfSoftwareVersionID = f_FtRDM->AddSoftwareVersID(value);

    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfSoftwareVersionIDImpl* pSoftwareVersionIDObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfSoftwareVersionID, (IVWUnknown**)& pSoftwareVersionIDObj)))
    {
        // Check Casting
        CGdtfSoftwareVersionIDImpl* pResultInterface = static_cast<CGdtfSoftwareVersionIDImpl*>(pSoftwareVersionIDObj);
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


VCOMError CGdtf_FTRDMImpl::SetDeviceModelID(size_t value)
{
    // Check Pointer
    if (!f_FtRDM) return kVCOMError_NotInitialized;

    f_FtRDM->SetDeviceModelID (value);

    return kVCOMError_NoError;
}

void *VCOM_CALLTYPE CGdtf_FTRDMImpl::GetBoundObject()
{
    // Check if valid
    if (!f_FtRDM) return nullptr;

    return f_FtRDM->GetBind();
}

void CGdtf_FTRDMImpl::SetPointer(SceneData::GdtfFTRDM * value)
{
    f_FtRDM = value;
}

SceneData::GdtfFTRDM * CGdtf_FTRDMImpl::GetPointer()
{
    return f_FtRDM;
}

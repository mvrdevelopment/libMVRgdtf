//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfArtNet.h"
#include "CGdtfMap.h"

using namespace VectorworksMVR;

CGdtfArtNetImpl::CGdtfArtNetImpl()
{
	fArtNet = nullptr;
};

CGdtfArtNetImpl::~CGdtfArtNetImpl()
{
    
}

VCOMError CGdtfArtNetImpl::GetMapCount(size_t& count)
{
    if (!fArtNet) { return kVCOMError_NotInitialized; }

    count = fArtNet->GetMapArray().size();

    return kVCOMError_NoError;
}


VCOMError CGdtfArtNetImpl::GetMapAt(size_t at, IGdtfMap** map)
{
    // Check if Set
    if (!fArtNet) { return kVCOMError_NotInitialized; }

    // Check if no Overflow
    if (at >= fArtNet->GetMapArray().size()) { return kVCOMError_OutOfBounds; }

    SceneData::GdtfMap* gdtfMap = fArtNet->GetMapArray()[at];

    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfMapImpl* pMapObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfMap, (IVWUnknown**)& pMapObj)))
    {
        // Check Casting
        CGdtfMapImpl* pResultInterface = static_cast<CGdtfMapImpl*>(pMapObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfMap);
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
    if (*map)
    {
        (*map)->Release();
        *map = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *map = pMapObj;

    return kVCOMError_NoError;
}


VCOMError CGdtfArtNetImpl::CreateMap(Uint32 key, Uint32 value, IGdtfMap** map)
{
    // Check if Set
    if (!fArtNet) { return kVCOMError_NotInitialized; }


    SceneData::GdtfMap* gdtfMap = fArtNet->CreateMap(key, value);

    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfMapImpl* pMapObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfMap, (IVWUnknown**)& pMapObj)))
    {
        // Check Casting
        CGdtfMapImpl* pResultInterface = static_cast<CGdtfMapImpl*>(pMapObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfMap);
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
    if (*map)
    {
        (*map)->Release();
        *map = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *map = pMapObj;

    return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE CGdtfArtNetImpl::BindToObject(void * objAddr)
{
    // Check if valid
    if (!fArtNet) return kVCOMError_NotInitialized;

    fArtNet->SetBind(objAddr);

    return kVCOMError_NoError;
}

void *VCOM_CALLTYPE CGdtfArtNetImpl::GetBoundObject()
{
    // Check if valid
    if (!fArtNet) return nullptr;

    return fArtNet->GetBind();
}

void CGdtfArtNetImpl::SetPointer(SceneData::GdtfArtNet* value)
{
    fArtNet = value;
}

SceneData::GdtfArtNet* CGdtfArtNetImpl::GetPointer()
{
    return fArtNet;
}

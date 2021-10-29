//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfSACN.h"
#include "CGdtfMap.h"

using namespace VectorworksMVR;

CGdtfSACNImpl::CGdtfSACNImpl()
{
	fSACN = nullptr;
};

CGdtfSACNImpl::~CGdtfSACNImpl()
{
    
}

VCOMError CGdtfSACNImpl::GetMapCount(size_t& count)
{
    if (!fSACN) { return kVCOMError_NotInitialized; }

    count = fSACN->GetMapArray().size();

    return kVCOMError_NoError;
}


VCOMError CGdtfSACNImpl::GetMapAt(size_t at, IGdtfMap** map)
{
    // Check if Set
    if (!fSACN) { return kVCOMError_NotInitialized; }

    // Check if no Overflow
    if (at >= fSACN->GetMapArray().size()) { return kVCOMError_OutOfBounds; }

    SceneData::GdtfMap* gdtfMap = fSACN->GetMapArray()[at];

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


VCOMError CGdtfSACNImpl::CreateMap(Uint32 key, Uint32 value, IGdtfMap** map)
{
    // Check if Set
    if (!fSACN) { return kVCOMError_NotInitialized; }


    SceneData::GdtfMap* gdtfMap = fSACN->CreateMap(key, value);

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

VCOMError VCOM_CALLTYPE CGdtfSACNImpl::BindToObject(void * objAddr)
{
    // Check if valid
    if (!fSACN) return kVCOMError_NotInitialized;

    fSACN->SetBind(objAddr);

    return kVCOMError_NoError;
}

void *VCOM_CALLTYPE CGdtfSACNImpl::GetBoundObject()
{
    // Check if valid
    if (!fSACN) return nullptr;

    return fSACN->GetBind();
}

void CGdtfSACNImpl::SetPointer(SceneData::GdtfsAcn* value)
{
    fSACN = value;
}

SceneData::GdtfsAcn* CGdtfSACNImpl::GetPointer()
{
    return fSACN;
}

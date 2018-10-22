#include "StdAfx.h"

#include "SDKImpl.h"

CSDKImpl::CSDKImpl()
{
}

CSDKImpl::~CSDKImpl()
{
}

bool CSDKImpl::SelectItemFromPluginCatalog( MCObjectHandle hObj, TXString catName)
{
	return false;
}

class CTesselator
{
public:
	CTesselator() {}
	virtual ~CTesselator() {}
};

TTesselator CSDKImpl::CreateTessellator(short convertRes3D)
{
	return (TTesselator) new CTesselator();
}

void CSDKImpl::DeleteTessellator(TTesselator pTess)
{
	delete (CTesselator*) pTess;
}

bool CSDKImpl::TesselateObject(TTesselator pTess, MCObjectHandle h, GS_TessellateIteratorProcPtr proc, void* pEnv)
{
	return true;
}


#include "MockUp/MockSDK.h"

class CSDKImpl : public MockUp::MockSDK
{
public:
				CSDKImpl();
	virtual		~CSDKImpl();

public:
	virtual bool VCOM_CALLTYPE SelectItemFromPluginCatalog( MCObjectHandle hObj, TXString catName = "" );

	virtual TTesselator VCOM_CALLTYPE CreateTessellator(short convertRes3D);
	virtual void VCOM_CALLTYPE DeleteTessellator(TTesselator pTess);
	virtual bool VCOM_CALLTYPE TesselateObject(TTesselator pTess, MCObjectHandle h, GS_TessellateIteratorProcPtr proc, void* pEnv);
};

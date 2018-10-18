//
//	ModuleMain.cpp
//
//	Main entry point for Vectorworks module code.
//


#include "StdAfx.h"
#include "VectorworksMVR.h"
#include "IMediaRessourceVectorInterface.h"
#include "Implementation/CMediaRessourceVectorImpl.h"
#include "../../../../Core/Source/Interfaces/VectorWorks/Filing/FileIdentifier.h"
#include "../../../../Core/Source/Interfaces/VectorWorks/Filing/FolderIdentifier.h"
#include "../../../../Core/Source/Interfaces/VectorWorks/Filing/ZIPFileImpl.h"
#include "../../../Shipping/3DS ImportExport/3DS Library/Source/ImportExportObject3DSImpl.h"
#include "../../../Shipping/Support/Source/XMLLib/XMLFileImpl.h"
#include "../../../Shipping/Support/Source/XMLLib/XMLFileNodeImpl.h"
#include "Wrapper/RawOSFileimpl.h"
#include "Wrapper/SDKImpl.h"

// GDTF stuff
#include "Implementation/CGdtfFixture.h"
#include "Implementation/CGdtfWheel.h"
#include "Implementation/CGdtfActivationGroup.h"
#include "Implementation/CGdtfFeatureGroup.h"
#include "Implementation/CGdtfAttribute.h"
#include "Implementation/CGdtfModel.h"
#include "Implementation/CGdtfGeometry.h"
#include "Implementation/CGdtfDmxMode.h"
#include "Implementation/CGdtfRevision.h"
#include "Implementation/CGdtfUserPreset.h"
#include "Implementation/CGdtfMacro.h"
#include "Implementation/CGdtfFeature.h"
#include "Implementation/CGdtfWheelSlot.h"
#include "Implementation/CGdtfDmxChannel.h"
#include "Implementation/CGdtfDmxRelation.h"
#include "Implementation/CGdtfPhysicalEmitter.h"
#include "Implementation/CGdtfMeasurementPoint.h"
#include "Implementation/CGdtfDmxLogicalChannel.h"
#include "Implementation/CGdtfDmxChannelFunction.h"
#include "Implementation/CGdtfDmxChannelSet.h"
#include "Implementation/CGdtfBreak.h"
#include "Implementation/CGdtfWheelSlotPrismFacet.h"

//------------------------------------------------------------------
// These are not relevant as it is not a Vectorworks plugin. But, it's needed to link agains VWSDK
const char * DefaultPluginVWRIdentifier() { return "VectorworksMVR"; } 
extern "C" Sint32 GS_EXTERNAL_ENTRY plugin_module_ver() { return SDK_VERSION; }

//------------------------------------------------------------------
extern "C" VectorworksMVR::VCOMError VW_EXPORT VWQueryInterface(const VectorworksMVR::VWIID& iid, VectorworksMVR::IVWUnknown** outInterface)
{
	if ( gSDK == nullptr )
	{
		using namespace VectorWorks;
		VCOMPtr<ISDK>	localSDK( IID_SDK );
		gSDK	= localSDK;
	}

	VectorworksMVR::IVWUnknown* resultInterface = nullptr;

	// match interface iid
	if ( iid == VectorworksMVR::IID_MediaRessourceVectorInterface )
		resultInterface = new VectorworksMVR::CMediaRessourceVectorImpl();
	else if (iid == VectorworksMVR::IID_SceneDataProvider)
		resultInterface = new VectorworksMVR::CSceneDataProviderImpl();
	else if (iid == VectorworksMVR::IID_SceneObject)
		resultInterface = new VectorworksMVR::CSceneObjImpl();
	else if (iid == VectorworksMVR::IID_ISymDef)
		resultInterface = new VectorworksMVR::CSymDefImpl();
	else if (iid == VectorworksMVR::IID_IClass)
		resultInterface = new VectorworksMVR::CClassImpl();
	else if (iid == VectorworksMVR::IID_PositionObj)
		resultInterface = new VectorworksMVR::CPositionImpl();
	else if (iid == VectorworksMVR::IID_GeometryReference)
		resultInterface = new VectorworksMVR::CGeometryReferenceImpl();
    else if (iid == VectorworksMVR::IID_IGdtfFixture)
        resultInterface = new VectorworksMVR::CGdtfFixtureImpl();
    else if (iid == VectorworksMVR::IID_GdtfWheel)
        resultInterface = new VectorworksMVR::CGdtfWheelImpl();
    else if (iid == VectorworksMVR::IID_GdtfActivationGroup)
        resultInterface = new VectorworksMVR::CGdtfActivationGroupImpl();
    else if (iid == VectorworksMVR::IID_GdtfFeatureGroup)
        resultInterface = new VectorworksMVR::CGdtfFeatureGroupImpl();
    else if (iid == VectorworksMVR::IID_GdtfAttribute)
        resultInterface = new VectorworksMVR::CGdtfAttributeImpl();
    else if (iid == VectorworksMVR::IID_GdtfModel)
        resultInterface = new VectorworksMVR::CGdtfModelImpl();
    else if (iid == VectorworksMVR::IID_GdtfGeometry)
        resultInterface = new VectorworksMVR::CGdtfGeometryImpl();
    else if (iid == VectorworksMVR::IID_GdtfDmxMode)
        resultInterface = new VectorworksMVR::CGdtfDmxModeImpl();
    else if (iid == VectorworksMVR::IID_GdtfRevision)
        resultInterface = new VectorworksMVR::CGdtfRevisionImpl();
    else if (iid == VectorworksMVR::IID_GdtfUserPreset)
        resultInterface = new VectorworksMVR::CGdtfUserPresetImpl();
    else if (iid == VectorworksMVR::IID_GdtfMacro)
        resultInterface = new VectorworksMVR::CGdtfMacroImpl();
    else if (iid == VectorworksMVR::IID_GdtfFeature)
        resultInterface = new VectorworksMVR::CGdtfFeatureImpl();
    else if (iid == VectorworksMVR::IID_GdtfWheelSlot)
        resultInterface = new VectorworksMVR::CGdtfWheelSlotImpl();
    else if (iid == VectorworksMVR::IID_GdtfDmxChannel)
        resultInterface = new VectorworksMVR::CGdtfDmxChannelImpl();
    else if (iid == VectorworksMVR::IID_GdtfDmxRelation)
        resultInterface = new VectorworksMVR::CGdtfDmxRelationImpl();
    else if (iid == VectorworksMVR::IID_GdtfPhysicalEmitter)
        resultInterface = new VectorworksMVR::CGdtfPhysicalEmitterImpl();
    else if (iid == VectorworksMVR::IID_GdtfMeasurementPoint)
        resultInterface = new VectorworksMVR::CGdtfMeasurementPointImpl();
    else if (iid == VectorworksMVR::IID_GdtfDmxLogicalChannel)
        resultInterface = new VectorworksMVR::CGdtfDmxLogicalChannelImpl();
    else if (iid == VectorworksMVR::IID_GdtfDmxChannelFunction)
        resultInterface = new VectorworksMVR::CGdtfDmxChannelFunctionImpl();
    else if (iid == VectorworksMVR::IID_GdtfDmxChannelSet)
        resultInterface = new VectorworksMVR::CGdtfDmxChannelSetImpl();
    else if (iid == VectorworksMVR::IID_GdtfBreak)
        resultInterface = new VectorworksMVR::CGdtfBreakImpl();
    else if (iid == VectorworksMVR::IID_GdtfWheelSlotPrismFacet)
        resultInterface = new VectorworksMVR::CGdtfWheelSlotPrismFacetImpl();
	
	// determine the result values
	VCOMError result = kVCOMError_Failed;
	if ( outInterface == nullptr )
		result = kVCOMError_NotInitialized;
	else if ( resultInterface == nullptr )
		result = kVCOMError_NoInstance;
	else
	{
		resultInterface->AddRef();
		result = kVCOMError_NoError;
		*outInterface = resultInterface;
	}

	return result;
}

//------------------------------------------------------------------
class CInterfaceManager
{
public:
			CInterfaceManager();
	virtual	~CInterfaceManager();

protected:
	static void*		_GetFunction(size_t id);

protected:
	static Sint32		_RegisterInterface(void* pInLibFile, void* pInIID, bool cacheIt);
	static Sint32		_RegisterInterfaceInContainer(void* pInLibFile, void* pInIID, void* pInIIDContainer, bool cacheIt);
	static Sint32		_QueryInterface(void* pInIID, void** pInInterface);
	static Sint32		_QueryInterfaceRTTI(void* pInIID, void** ppInterfaceRTTI);
	static void			_DeleteInterface(void* ppInInterface);
	static size_t		_GetContainerInterfacesCount(void* pInIIDContainer);
	static void			_GetContainerInterface(void* pInIIDContainer, size_t index, void* pOutIID);
	static void			_ReleaseInterface(bool takeYourTime);
	static size_t		_GetInterfaceModulePath(void* pInIID, char* buffer, size_t bufferSize);
	static Sint32		_RegisterInterfaceCallbacks(void* pInIID, TRegisterAllocateCallback allocateCallback, TRegisterFreeCallback freeCallback);

public:
	void*						fCallbackTable[15];
	std::map<IVWUnknown*, bool>	fmapQueriedInterfaces;

	VectorWorks::ISDK*		fSingleton_SDK;
} gVCOMRegistry;

//------------------------------------------------------------------
CInterfaceManager::CInterfaceManager()
	: fSingleton_SDK( nullptr )
{
	fCallbackTable[0]	= (void*) CInterfaceManager::_RegisterInterface;
	fCallbackTable[1]	= (void*) CInterfaceManager::_QueryInterface;
	fCallbackTable[2]	= (void*) CInterfaceManager::_DeleteInterface;
	fCallbackTable[3]	= (void*) CInterfaceManager::_RegisterInterfaceInContainer;
	fCallbackTable[4]	= (void*) CInterfaceManager::_GetContainerInterfacesCount;
	fCallbackTable[5]	= (void*) CInterfaceManager::_GetContainerInterface;
	fCallbackTable[6]	= (void*) NULL;	// _LoadInterfaceResource;
	fCallbackTable[7]	= (void*) NULL;	// _UnloadInterfaceResource;
	fCallbackTable[8]	= (void*) CInterfaceManager::_QueryInterfaceRTTI;
	fCallbackTable[9]	= (void*) CInterfaceManager::_ReleaseInterface;
	fCallbackTable[10]	= (void*) CInterfaceManager::_GetInterfaceModulePath;
	fCallbackTable[11]	= (void*) CInterfaceManager::_RegisterInterfaceCallbacks;
	fCallbackTable[12]	= NULL;
	fCallbackTable[13]	= NULL;
	fCallbackTable[14]	= NULL;

	static void* cbp = (void*)CInterfaceManager::_GetFunction;
	gCBP = (CallBackPtr) &cbp;
	GS_InitializeVCOM( gCBP );
};

CInterfaceManager::~CInterfaceManager()
{
	if ( fSingleton_SDK )
	{
		delete fSingleton_SDK;
		fSingleton_SDK = nullptr;
	}
}

static CBBoolean CB_Kludge(CBSignedShort selector, void* in, void* out, bool bUseLegacyZ)
{
	CBBoolean result = false;
	switch ( selector )
	{
	case 499:
		{
			void**	pVCOMCallBack	= (void**) out;
			*pVCOMCallBack			= gVCOMRegistry.fCallbackTable;
		}
		break;

	default:
		break;
	}

	return result;
}

static CBBoolean CB_StringToDouble(TNumStyleClass inNumStyle, const TXString& inString, double& outDouble)
{
	outDouble = atof( inString );
	return true;
}

/*static*/ void* CInterfaceManager::_GetFunction(size_t id)
{
	void* result = nullptr;
	switch ( id )
	{
		case kcbKludge:			result = (void*)CB_Kludge;			break;
		case kcbStringToDouble:	result = (void*)CB_StringToDouble;	break;
		default: break;
	}

	return result;
}

/*static*/ Sint32 CInterfaceManager::_RegisterInterface(void* pInLibFile, void* pInIID, bool cacheIt)
{
	return 0;
}

/*static*/ Sint32 CInterfaceManager::_RegisterInterfaceInContainer(void* pInLibFile, void* pInIID, void* pInIIDContainer, bool cacheIt)
{
	return 0;
}

/*static*/ Sint32 CInterfaceManager::_QueryInterface(void* pInIID, void** pInInterface)
{
	VCOMError result = kVCOMError_Failed;
	if ( pInIID )
	{
		const VWIID& iid = *(VWIID*) pInIID;

		IVWUnknown* resultInterface = nullptr;

		// match interface iid
		if ( iid == VectorWorks::Filing::IID_FileIdentifier )
			resultInterface = new CFileIdentifier();
		else if ( iid == VectorWorks::Filing::IID_FolderIdentifier )
			resultInterface = new CFolderIdentifier();
		else if ( iid == VectorWorks::Filing::IID_ZIPFile )
			resultInterface = new CZIPFileImpl();
		else if ( iid == VectorWorks::Filing::IID_RawOSFile )
			resultInterface = new CRawOSFileImpl();
		else if ( iid == VectorWorks::Filing::IID_IImportExportObject3DS )
			resultInterface = new CImportExportObject3DSImpl( gCBP );
		else if ( iid == VectorWorks::Filing::IID_XMLFile )
			resultInterface = new XML::CXMLFileImpl( gCBP );
		else if ( iid == XML::IID_XMLFileNode )
			resultInterface = new XML::CXMLFileNodeImpl( gCBP );
		else if ( iid == VectorWorks::IID_SDK )
		{
			if ( gVCOMRegistry.fSingleton_SDK == nullptr )
			{
				gVCOMRegistry.fSingleton_SDK = new CSDKImpl();
				gVCOMRegistry.fSingleton_SDK->AddRef();
			}
			resultInterface = gVCOMRegistry.fSingleton_SDK;
		}

		// determine the result values
		if ( pInInterface == nullptr )
			result = kVCOMError_NotInitialized;
		else if ( resultInterface == nullptr )
			result = kVCOMError_NoInstance;
		else
		{
			resultInterface->AddRef();
			result = kVCOMError_NoError;
			*pInInterface = resultInterface;

			// this is a fail safe if we use interfaces that are not immediate delete
			// we dont expect to take up a lot of time, but if it does then we'll add timing constraints
			auto it = gVCOMRegistry.fmapQueriedInterfaces.cbegin();
			while ( it != gVCOMRegistry.fmapQueriedInterfaces.cend() )
			{
				IVWUnknown* ptr = it->first;
				ptr->AddRef();
				if ( ptr->Release() == 0 )
				{
					delete ptr;
					it = gVCOMRegistry.fmapQueriedInterfaces.erase(it);
				}
				else
				{
					++it;
				}
			}
			gVCOMRegistry.fmapQueriedInterfaces[resultInterface] = true;
		}
	}

	return result;
}

/*static*/ Sint32 CInterfaceManager::_QueryInterfaceRTTI(void* pInIID, void** ppInterfaceRTTI)
{
	return 0;
}

/*static*/ void CInterfaceManager::_DeleteInterface(void* ppInInterface)
{
	IVWUnknown* ptr = (IVWUnknown*) ppInInterface;
	if ( ptr )
	{
		auto it = gVCOMRegistry.fmapQueriedInterfaces.find( ptr );
		if ( it != gVCOMRegistry.fmapQueriedInterfaces.end() )
		{
			gVCOMRegistry.fmapQueriedInterfaces.erase( it );
			delete ptr;
		}
	}
}

/*static*/ size_t CInterfaceManager::_GetContainerInterfacesCount(void* pInIIDContainer)
{
	return 0;
}

/*static*/ void CInterfaceManager::_GetContainerInterface(void* pInIIDContainer, size_t index, void* pOutIID)
{
}

/*static*/ void CInterfaceManager::_ReleaseInterface(bool takeYourTime)
{
}

/*static*/ size_t CInterfaceManager::_GetInterfaceModulePath(void* pInIID, char* buffer, size_t bufferSize)
{
	return 0;
}

/*static*/ Sint32 CInterfaceManager::_RegisterInterfaceCallbacks(void* pInIID, TRegisterAllocateCallback allocateCallback, TRegisterFreeCallback freeCallback)
{
	return 0;
}


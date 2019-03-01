//
//	ModuleMain.cpp
//
//	Main entry point for Vectorworks module code.
//


#include "Prefix/StdAfx.h"
#include "Include/VectorworksMVR.h"
#include "Include/IMediaRessourceVectorInterface.h"
#include "Implementation/CMediaRessourceVectorImpl.h"

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
#include "Implementation/CGeometryReferenceImpl.h"
#include "Implementation/CGdtfXmlParsingError.h"
#include "Implementation/CGdtfDMXPersonality.h"
#include "Implementation/CGdtfSoftwareVersionID.h"
#include "Implementation/CGdtfFTRDM.h"
#include "Implementation/CGdtfMeasurement.h"
#include "Implementation/CGdtfFilter.h"
#include "Implementation/CGdtfColorSpace.h"

// XML
#include "XMLLib/XMLFileNodeImpl.h"
#include "XMLLib/XMLFileImpl.h"

// Wrapper
#include "Wrapper/FileIdentifier.h"
#include "Wrapper/FilingWrapper.h"
#include "Wrapper/FolderIdentifier.h"
#include "Wrapper/PluginResource.h"
#include "Wrapper/RawOSFileimpl.h"
#include "Wrapper/TDQuickDraw.h"
#include "Wrapper/UTranslateFiles.h"
#include "Wrapper/ZIPFileImpl.h"

//------------------------------------------------------------------
extern "C" VectorworksMVR::VCOMError VW_EXPORT VWQueryInterface(const VectorworksMVR::VWIID& iid, VectorworksMVR::IVWUnknown** outInterface)
{
	VectorworksMVR::IVWUnknown* resultInterface = nullptr;

	// match interface iid
    if (iid == VectorworksMVR::IID_MediaRessourceVectorInterface)
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
        resultInterface = new CGdtfWheelSlotPrismFacetImpl();
    else if (iid == VectorworksMVR::IID_GdtfXmlParsingError)
        resultInterface = new CGdtfXmlParsingErrorImpl();
    else if (iid == VectorworksMVR::IID_GdtfTRDM)
        resultInterface = new CGdtf_FTRDMImpl();
    else if (iid == VectorworksMVR::IID_GdtfDMXPersonality)
        resultInterface = new CGdtfDMXPersonalityImpl();
    else if (iid == VectorworksMVR::IID_GdtfSoftwareVersionID)
        resultInterface = new CGdtfSoftwareVersionIDImpl();
    else if (iid == VectorworksMVR::IID_GdtfMeasurement)
        resultInterface = new CGdtfMeasurementImpl();
    else if (iid == VectorworksMVR::IID_GdtfFilter)
        resultInterface = new CGdtfFilterImpl();
    else if (iid == VectorworksMVR::IID_GdtfColorSpace)
        resultInterface = new CGdtfColorSpaceImpl();
	else if (iid == VectorWorks::Filing::IID_FileIdentifier)
		resultInterface = new CFileIdentifier();
	else if (iid == VectorWorks::Filing::IID_FolderIdentifier )
		resultInterface = new CFolderIdentifier();
	else if (iid == VectorWorks::Filing::IID_ZIPFile)
		resultInterface = new CZIPFileImpl();
	else if (iid == VectorWorks::Filing::IID_RawOSFile)
		resultInterface = new CRawOSFileImpl();
	else if (iid == XML::IID_XMLFile)
		resultInterface = new XML::CXMLFileImpl();
	else if (iid == XML::IID_XMLFileNode)
		resultInterface = new XML::CXMLFileNodeImpl();
	
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

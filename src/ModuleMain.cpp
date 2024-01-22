//
//	ModuleMain.cpp
//
//	Main entry point for Vectorworks module code.
//


#include "Prefix/StdAfx.h"
#include "Include/VectorworksMVR.h"
#include "Include/IMediaRessourceVectorInterface.h"
#include "Implementation/CMediaRessourceVectorImpl.h"
#include "Implementation/CConnectionImpl.h"

#include "Implementation/CCustomCommandImpl.h"
#include "Implementation/CAlignmentImpl.h"
#include "Implementation/COverwriteImpl.h"

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
#include "Implementation/CGdtfMacroDMX.h"
#include "Implementation/CGdtfMacroDMXStep.h"
#include "Implementation/CGdtfMacroDMXValue.h"
#include "Implementation/CGdtfMacroVisual.h"
#include "Implementation/CGdtfMacroVisualStep.h"
#include "Implementation/CGdtfMacroVisualValue.h"
#include "Implementation/CGdtfFeature.h"
#include "Implementation/CGdtfWheelSlot.h"
#include "Implementation/CGdtfDmxChannel.h"
#include "Implementation/CGdtfDmxRelation.h"
#include "Implementation/CGdtfPhysicalEmitter.h"
#include "Implementation/CGdtfMeasurementPoint.h"
#include "Implementation/CGdtfDmxLogicalChannel.h"
#include "Implementation/CGdtfDmxChannelFunction.h"
#include "Implementation/CGdtfDmxChannelSet.h"
#include "Implementation/CGdtfDmxSubChannelSet.h"
#include "Implementation/CGdtfBreak.h"
#include "Implementation/CGdtfWheelSlotPrismFacet.h"
#include "Implementation/CGdtfWheelSlotAnimationSystem.h"
#include "Implementation/CGeometryReferenceImpl.h"
#include "Implementation/CGdtfXmlParsingError.h"
#include "Implementation/CGdtfDMXPersonality.h"
#include "Implementation/CGdtfSoftwareVersionID.h"
#include "Implementation/CGdtfFTRDM.h"
#include "Implementation/CGdtfMap.h"
#include "Implementation/CGdtfArtNet.h"
#include "Implementation/CGdtfSACN.h"
#include "Implementation/CGdtfMeasurement.h"
#include "Implementation/CGdtfFilter.h"
#include "Implementation/CGdtfDmxProfile.h"
#include "Implementation/CGdtfPoint.h"
#include "Implementation/CGdtfColorSpace.h"
#include "Implementation/CGdtfConnector.h"
#include "Implementation/CUtility.h"
#include "Implementation/CGdtfLaserProtocol.h"
#include "Implementation/CGdtfPinPatch.h"
#include "Implementation/CGdtfSubPhysicalUnit.h"
#include "Implementation/CGdtfGamut.h"

#ifdef BUILD_MVR_XCHANGE
// not in Implementation folder, so it can be switched off easily
#include "mvrxchange/CMVRxchangeService.h"
#endif

// XML
#include "XMLLib/XMLFileNodeImpl.h"
#include "XMLLib/XMLFileImpl.h"

#ifdef DONT_USE_XERCES_AS_XMLLIB
#include "rapidxmlsupport/mvr_xml_impl.h"
#endif

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
extern "C" VectorworksMVR::VCOMError VWQueryInterface(const VectorworksMVR::VWIID& iid, VectorworksMVR::IVWUnknown** outInterface)
{
	VectorworksMVR::IVWUnknown* resultInterface = nullptr;

	// match interface iid
    if (iid == VectorworksMVR::IID_MediaRessourceVectorInterface)
        resultInterface = new VectorworksMVR::CMediaRessourceVectorImpl();
    else if (iid == VectorworksMVR::IID_SceneDataProvider)
        resultInterface = new VectorworksMVR::CSceneDataProviderImpl();
    else if (iid == VectorworksMVR::IID_SceneObject)
        resultInterface = new VectorworksMVR::CSceneObjImpl();
    else if (iid == VectorworksMVR::IID_SourceObj)
        resultInterface = new VectorworksMVR::CSourceImpl();
    else if (iid == VectorworksMVR::IID_ISymDef)
        resultInterface = new VectorworksMVR::CSymDefImpl();
    else if (iid == VectorworksMVR::IID_IClass)
        resultInterface = new VectorworksMVR::CClassImpl();
    else if (iid == VectorworksMVR::IID_PositionObj)
        resultInterface = new VectorworksMVR::CPositionImpl();
    else if (iid == VectorworksMVR::IID_MappingDefinitionObj)
        resultInterface = new VectorworksMVR::CMappingDefinitionImpl();
    else if (iid == VectorworksMVR::IID_MappingObj)
        resultInterface = new VectorworksMVR::CMappingImpl();
    else if (iid == VectorworksMVR::IID_ConnectionObj)
        resultInterface = new VectorworksMVR::CConnectionImpl();
    else if (iid == VectorworksMVR::IID_CustomCommand)
        resultInterface = new VectorworksMVR::CCustomCommandImpl();
    else if (iid == VectorworksMVR::IID_Alignment)
        resultInterface = new VectorworksMVR::CAlignmentImpl();
    else if (iid == VectorworksMVR::IID_Overwrite)
        resultInterface = new VectorworksMVR::COverwriteImpl();
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
    else if (iid == VectorworksMVR::IID_GdtfMacroDMX)
        resultInterface = new VectorworksMVR::CGdtfMacroDMXImpl();
    else if (iid == VectorworksMVR::IID_GdtfMacroDMXStep)
        resultInterface = new VectorworksMVR::CGdtfMacroDMXStepImpl();
    else if (iid == VectorworksMVR::IID_GdtfMacroDMXValue)
        resultInterface = new VectorworksMVR::CGdtfMacroDMXValueImpl();
    else if (iid == VectorworksMVR::IID_GdtfMacroVisual)
        resultInterface = new VectorworksMVR::CGdtfMacroVisualImpl();
    else if (iid == VectorworksMVR::IID_GdtfMacroVisualStep)
        resultInterface = new VectorworksMVR::CGdtfMacroVisualStepImpl();
    else if (iid == VectorworksMVR::IID_GdtfMacroVisualValue)
        resultInterface = new VectorworksMVR::CGdtfMacroVisualValueImpl();
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
    else if (iid == VectorworksMVR::IID_GdtfDmxSubChannelSet)
        resultInterface = new VectorworksMVR::CGdtfDmxSubChannelSetImpl();
    else if (iid == VectorworksMVR::IID_GdtfBreak)
        resultInterface = new VectorworksMVR::CGdtfBreakImpl();
    else if (iid == VectorworksMVR::IID_GdtfWheelSlotPrismFacet)
        resultInterface = new CGdtfWheelSlotPrismFacetImpl();
    else if (iid == VectorworksMVR::IID_GdtfWheelSlotAnimationSystem)
        resultInterface = new CGdtfWheelSlotAnimationSystemImpl();
    else if (iid == VectorworksMVR::IID_GdtfXmlParsingError)
        resultInterface = new CGdtfXmlParsingErrorImpl();
    else if (iid == VectorworksMVR::IID_GdtfTRDM)
        resultInterface = new CGdtf_FTRDMImpl();
    else if (iid == VectorworksMVR::IID_GdtfMap)
        resultInterface = new CGdtfMapImpl();
    else if (iid == VectorworksMVR::IID_GdtfArtNet)
        resultInterface = new CGdtfArtNetImpl();
    else if (iid == VectorworksMVR::IID_GdtfSACN)
        resultInterface = new CGdtfSACNImpl();
    else if (iid == VectorworksMVR::IID_GdtfDMXPersonality)
        resultInterface = new CGdtfDMXPersonalityImpl();
    else if (iid == VectorworksMVR::IID_GdtfSoftwareVersionID)
        resultInterface = new CGdtfSoftwareVersionIDImpl();
    else if (iid == VectorworksMVR::IID_GdtfMeasurement)
        resultInterface = new CGdtfMeasurementImpl();
    else if (iid == VectorworksMVR::IID_GdtfFilter)
        resultInterface = new CGdtfFilterImpl();
    else if (iid == VectorworksMVR::IID_GdtfDMXProfile)
        resultInterface = new CGdtfDMXProfileImpl();
    else if (iid == VectorworksMVR::IID_GdtfPoint)
        resultInterface = new CGdtfPointImpl();
    else if (iid == VectorworksMVR::IID_GdtfColorSpace)
        resultInterface = new CGdtfColorSpaceImpl();
    else if (iid == VectorworksMVR::IID_GdtfGamut)
		resultInterface = new CGdtfGamutImpl();
    else if (iid == VectorworksMVR::IID_GdtfConnector)
        resultInterface = new CGdtfConnectorImpl();
	else if (iid == VectorworksMVR::Filing::IID_FileIdentifier)
		resultInterface = new CFileIdentifier();
	else if (iid == VectorworksMVR::Filing::IID_FolderIdentifier )
		resultInterface = new CFolderIdentifier();
	else if (iid == VectorworksMVR::Filing::IID_ZIPFile)
		resultInterface = new CZIPFileImpl();
	else if (iid == VectorworksMVR::Filing::IID_RawOSFile)
		resultInterface = new CRawOSFileImpl();
	else if (iid == XML::IID_XMLFile)
		resultInterface = new XML::CXMLFileImpl();
	else if (iid == XML::IID_XMLFileNode)
		resultInterface = new XML::CXMLFileNodeImpl();
    else if (iid == VectorworksMVR::IID_IUtility)
		resultInterface = new CUtilityImpl();
    else if (iid == VectorworksMVR::IID_GdtfLaserProtocol)
		resultInterface = new CGdtfLaserProtocolImpl();
    else if (iid == VectorworksMVR::IID_GdtfPinPatch)
		resultInterface = new CGdtfPinPatchImpl();
    else if (iid == VectorworksMVR::IID_GdtfSubPhysicalUnit)
		resultInterface = new CGdtfSubPhysicalUnitImpl();
    #ifdef BUILD_MVR_XCHANGE
    else if (iid == VectorworksMVR::IID_IMVRxchangeService)
		resultInterface = new CMVRxchangeServiceImpl();
	#endif
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

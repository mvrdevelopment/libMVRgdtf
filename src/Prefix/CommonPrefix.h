//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"

////////////////////////////////////////////////////////////////
// Plug-in specific
#define VWParaLightingDevice_CLASSNAME			"Lighting Device"
#define VWParaLightingDevice_P_Symbol			"Symbol Name"
#define VWParaLightingDevice_P_NAME				"Inst Type"
#define VWParaLightingDevice_P_Position			"Position"
#define VWParaLightingDevice_P_Focus			"Focus"
#define VWParaLightingDevice_P_Symbol			"Symbol Name"
#define VWParaLightingDevice_P_GoboData			"Gobo Data"
#define VWParaLightingDevice_P_ColorData		"Color Data"
#define VWParaLightingDevice_P_AniWheel			"Color Flag Data"
#define VWParaLightingDevice_P_LitFileName		"Fixture Mode"
#define VWParaLightingDevice_P_CountDmxChannels "Num Channels"
#define VWParaLightingDevice_P_Color			"RGBColor"

#define VWParaLightingDevice_P_AdditionalRotX	"xRot"
#define VWParaLightingDevice_P_AdditionalRotY	"yRot"
#define VWParaLightingDevice_P_AdditionalRotZ	"zRot"
#define VWParaLightingDevice_P_UseAdditionalRot "Rotate3DPosition"
#define VWParaLightingDevice_P_EnableZRot		"EnableZRot"


// Fields developed for GDTF
#define VWParaLightingDevice_P_CieColor			"GDTF CIE Color"
#define VWParaLightingDevice_P_GdtfName			"GDTF Fixture Name"
#define VWParaLightingDevice_P_GdtfMode			"GDTF Fixture Mode"
#define VWParaLightingDevice_P_CustomId			"GDTF Fixture Custom ID"
#define VWParaLightingDevice_P_FixtureTypeId	"GDTF Fixture Type ID"

// Fields that need to be matched
#define VWParaLightingDevice_P_FixtureId		"FixtureId"
#define VWParaLightingDevice_P_UnitNumber		"Unit Number"
#define VWParaLightingDevice_P_Address			"Dimmer"
#define VWParaLightingDevice_P_Universe			"Universe"

#define VWParaLightingPosition_CLASSNAME		"Light Position Obj"
#define VWParaLightingPosition_P_Name			"Position Name"



#define VWParaFocusPointObject_CLASSNAME		"Focus Point Object"
#define VWParaFocusPointObject_P_Name			"Name"

#define VWParaCurvedTruss_CLASSNAME				"Curved Truss"
#define VWParaCurvedTruss_P_Name				"Name"

#define VWParaTrussObj_CLASSNAME				"Straight Truss"
#define VWParaTrussObj_P_Name					"Name"

#define TrussItem_CLASSNAME						"TrussItem"
#define TrussItem_P_NAME						"Name"

#define VideoScreen_CLASSNAME					"Video Screen"

//----------------------------------------------------------------------------------------------------------------------------------
// SceneDataExchange XML Values
#define XML_Val_RootNodeName			"GeneralSceneDescription"
#define XML_Val_RootAttrMainVersion		"verMajor"
#define XML_Val_RootAttrMinorVersion	"verMinor"
#define XML_Val_RootAttrProvider		"provider"
#define XML_Val_RootAttrProviderVersion	"providerVersion"

#define XML_Val_UserDataNodeName		"UserData"
#define XML_Val_UserDataVWEntry			"VWEntry"
#define XML_Val_UserDataVWKeyAttr		"key"

#define XML_Val_DataNodeName			"Data"
#define XML_Val_DataNodeAttrVersion		"ver"
#define XML_Val_DataNodeAttrProvider	"provider"

#define XML_Val_SceneNodeName		"Scene"
#define XML_Val_AuxDataNodeName		"AUXData"
#define XML_Val_LayersNodeName		"Layers"

#define XML_Val_SymDefNodeName		"Symdef"

#define XML_Val_PositionNodeName	"Position"

#define XML_Val_ClassNodeName	    "Class"


#define XML_Val_SourceNodeName	        "Source"
#define XML_Val_SourceLinkedGeometry	"linkedGeometry"
#define XML_Val_SourceType	            "type"
#define XML_Val_SourceTypeNDI	        "NDI"
#define XML_Val_SourceTypeFile	        "File"
#define XML_Val_SourceTypeCITP	        "CITP"
#define XML_Val_SourceTypeCaptureDevice	"CaptureDevice"

#define XML_Val_MappingDefinitionNodeName           "MappingDefinition"
#define XML_Val_MappingDefinitionSizeX              "SizeX"
#define XML_Val_MappingDefinitionSizeY              "SizeY"
#define XML_Val_MappingDefinitionScaleHandling      "ScaleHandling"
#define XML_Val_ScaleHandlingTypeScaleKeepRatio	    "ScaleKeepRatio"
#define XML_Val_ScaleHandlingTypeScaleIgnoreRatio   "ScaleIgnoreRatio"
#define XML_Val_ScaleHandlingTypeKeepSizeCenter	    "KeepSizeCenter"

#define XML_Val_LaserColorTypeRGB                   "RGB"
#define XML_Val_LaserColorTypeSingleWaveLength      "SingleWaveLength"

#define XML_Val_ComponentTypeInput              "Input"
#define XML_Val_ComponentTypeOutput             "Output"
#define XML_Val_ComponentTypePowerSource        "PowerSource"
#define XML_Val_ComponentTypeConsumer           "Consumer"
#define XML_Val_ComponentTypeFuse               "Fuse"
#define XML_Val_ComponentTypeNetworkProvider    "NetworkProvider"
#define XML_Val_ComponentTypeNetworkInput       "NetworkInput"
#define XML_Val_ComponentTypeNetworkOutput      "NetworkOutput"
#define XML_Val_ComponentTypeNetworkInOut       "NetworkInOut"

#define XML_Val_OrientationLeft         "Left"
#define XML_Val_OrientationRight        "Right"
#define XML_Val_OrientationTop          "Top"
#define XML_Val_OrientationBottom       "Bottom"

#define XML_Val_FuseRatingB       "B"
#define XML_Val_FuseRatingC       "C"
#define XML_Val_FuseRatingD       "D"
#define XML_Val_FuseRatingK       "K"
#define XML_Val_FuseRatingZ       "Z"

#define XML_Val_StructureTypeCenterLineBased    "CenterLineBased"
#define XML_Val_StructureTypeDetail             "Detail"

#define XML_Val_CrossSectionTypeTrussFramework  "TrussFramework"
#define XML_Val_CrossSectionTypeTube            "Tube"

#define XML_Val_SupportTypeRope                 "Rope"
#define XML_Val_SupportTypeGroundSupport        "GroundSupport"

#define XML_Val_SubPhysicalUnitTypePlacementOffset  "PlacementOffset"
#define XML_Val_SubPhysicalUnitTypeAmplitude        "Amplitude"
#define XML_Val_SubPhysicalUnitTypeAmplitudeMin     "AmplitudeMin"
#define XML_Val_SubPhysicalUnitTypeAmplitudeMax     "AmplitudeMax"
#define XML_Val_SubPhysicalUnitTypeDuration         "Duration"
#define XML_Val_SubPhysicalUnitTypeDutyCycle        "DutyCycle"
#define XML_Val_SubPhysicalUnitTypeTimeOffset       "TimeOffset"
#define XML_Val_SubPhysicalUnitTypeMinimumOpening   "MinimumOpening"
#define XML_Val_SubPhysicalUnitTypeValue            "Value"
#define XML_Val_SubPhysicalUnitTypeRatioHorizontal  "RatioHorizontal"
#define XML_Val_SubPhysicalUnitTypeRatioVertical    "RatioVertical"

#define XML_Val_MappingNodeName	        "Mapping"
#define XML_Val_MappingLinkedDefUuid	"linkedDef"
#define XML_Val_MappingUx	            "ux"
#define XML_Val_MappingUy	            "uy"
#define XML_Val_MappingOx	            "ox"
#define XML_Val_MappingOy	            "oy"
#define XML_Val_MappingRz	            "rz"

#define XML_Val_ConnectionNodeName      "Connection"
#define XML_Val_ConnectionsNodeName     "Connections"
#define XML_Val_ConnectionOwn           "own"
#define XML_Val_ConnectionOther         "other"
#define XML_Val_ConnectionToObject      "toObject"

#define XML_Val_CustomCommandsNodeName	"CustomCommands"
#define XML_Val_CustomCommandNodeName	"CustomCommand"

#define XML_Val_AlignmentsNodeName	    "Alignments"
#define XML_Val_AlignmentNodeName	    "Alignment"
#define XML_Val_AlignmentBeamGeometry   "geometry"
#define XML_Val_AlignmentUpVector       "up"
#define XML_Val_AlignmentDirection      "direction"

#define XML_Val_OverwritesNodeName	    "Overwrites"
#define XML_Val_OverwriteNodeName	    "Overwrite"
#define XML_Val_OverwriteUniversal      "universal"
#define XML_Val_OverwriteTarget         "target"

#define XML_Val_LayerObjectNodeName	"Layer"
#define XML_Val_FixtureNodeName		"Fixture"
#define XML_Val_GroupNodeName		"GroupObject"
#define XML_Val_ChildObsNodeName	"ChildList"

#define XML_Val_MatrixNodeName		"Matrix"
#define XML_Val_Matrix_U_NodeName	"U"
#define XML_Val_Matrix_V_NodeName	"V"
#define XML_Val_Matrix_W_NodeName	"W"
#define XML_Val_Matrix_O_NodeName	"O"

#define XML_Val_GeometriesNodeName		"Geometries"

#define XML_Val_NameAttrName		"name"
#define XML_Val_GuidAttrName		"uuid"
#define XML_Val_ClassingNodeName	"Classing"

#define XML_Val_FixtureGDTFSpec		"GDTFSpec"
#define XML_Val_FixtureDMXMode		"GDTFMode"
#define XML_Val_FixtureFocus		"Focus"
#define XML_Val_FixturePosition		"Position"
#define XML_Val_FixtureAddress		"Address"

#define XML_Val_FixtureAddresses	"Addresses"
#define XML_Val_FixtureFixtureID	"FixtureID"
#define XML_Val_FixtureUnitNumber	"UnitNumber"
#define XML_Val_FixtureColor		"Color"
#define XML_Val_FixtureAttrBreak	"break"
#define XML_Val_FixtureTypeId		"FixtureTypeId"
#define XML_Val_FixtureCustomid		"CustomId"
#define XML_Val_FixtureGobo		    "Gobo"
#define XML_Val_FixtureFunction	    "Function"
#define XML_Val_FixtureGoboRotation "rotation"
#define XML_Val_FixtureCastShadow   "CastShadow"
#define XML_Val_FixtureMappings     "Mappings"

#define XML_Val_SceneObjectNodeName			"SceneObject"

#define XML_Val_FocusPointObjectNodeName	"FocusPoint"

#define XML_Val_TrussObjectNodeName			"Truss"

#define XML_Val_SupportObjectNodeName		"Support"

#define XML_Val_VideoScreenObjectNodeName	"VideoScreen"
#define XML_Val_VideoScreenObjectSources    "Sources"

#define XML_Val_ProjectorObjectNodeName	        "Projector"
#define XML_Val_ProjectorObjectProjections      "Projections"
#define XML_Val_ProjectorObjectProjection       "Projection"
#define XML_Val_ProjectorObjectScaleHandling    "ScaleHandling"

#define XML_Val_SymbolObjectNodeName		"Symbol"
#define XML_Val_GuidSymdefAttrName			"symdef"

#define XML_Val_GeometryObjectNodeName		"Geometry3D"
#define XML_Val_GeometryObjectAttrFile		"fileName"

const Sint32 kMVR_MajorVersion = 1;
const Sint32 kMVR_MinorVersion = 5;

// ----------------------------------------------------------------------------------------------------------------------------------
// GDTF XML Values

#define XML_GDTF_GDTFFILENAME			    "description.xml"

#define XML_GDTF_ROOTNODENAME			    "GDTF"
#define XML_GDTF_ROOTNODEATTRVERSION	    "DataVersion"
#define XML_GDTF_CurrentVersion			    "1.2"

#define XML_GDTF_FixtureNodeName		    "FixtureType"
#define XML_GDTF_FixtureName			    "Name"
#define XML_GDTF_FixtureShortName		    "ShortName"
#define XML_GDTF_FixtureLongName		    "LongName"
#define XML_GDTF_FixtureManufacturer	    "Manufacturer"
#define XML_GDTF_FixtureDescription		    "Description"
#define XML_GDTF_FixtureTypeID			    "FixtureTypeID"
#define XML_GDTF_FixtureThumbnail		    "Thumbnail"
#define XML_GDTF_FixtureThumbnailOffsetX	"ThumbnailOffsetX"
#define XML_GDTF_FixtureThumbnailOffsetY    "ThumbnailOffsetY"
#define XML_GDTF_FixtureCanHaveChildren     "CanHaveChildren"
#define XML_GDTF_LinkedUuid				    "RefFT"

#define XML_GDTF_FixtureChildNodeAttributeDef		"AttributeDefinitions"
#define XML_GDTF_FixtureChildNodeActivationGroupDef	"ActivationGroups"
#define XML_GDTF_FixtureChildNodeFeatureGroupDef	"FeatureGroups"
#define XML_GDTF_FixtureChildNodeAttributesDef		"Attributes"

#define XML_GDTF_SubPhysicalUnitNodeName		    "SubPhysicalUnit"
#define XML_GDTF_SubPhysicalUnitType		        "Type"
#define XML_GDTF_SubPhysicalUnitPhysicalUnit		"PhysicalUnit"
#define XML_GDTF_SubPhysicalUnitPhysicalFrom		"PhysicalFrom"
#define XML_GDTF_SubPhysicalUnitPhysicalTo		    "PhysicalTo"

#define XML_GDTF_AttributeNode					"Attribute"
#define XML_GDTF_AttributeName					"Name"
#define XML_GDTF_AttributePrettyName			"Pretty"
#define XML_GDTF_AttributeActGroup				"ActivationGroup"
#define XML_GDTF_AttributeFeature				"Feature"
#define XML_GDTF_AttributefMainAttribute        "MainAttribute"
#define XML_GDTF_AttributePhysicalUnit          "PhysicalUnit"
#define XML_GDTF_AttributeColor                 "Color"

#define XML_GDTF_AttributeNoFeature_nullptr		    "NoFeature"

#define XML_GDTFPhysicalUnitEnum_None				"None"
#define XML_GDTFPhysicalUnitEnum_Percent			"Percent"
#define XML_GDTFPhysicalUnitEnum_Length				"Length"
#define XML_GDTFPhysicalUnitEnum_Mass				"Mass"
#define XML_GDTFPhysicalUnitEnum_Time				"Time"
#define XML_GDTFPhysicalUnitEnum_Temperatur			"Temperature"
#define XML_GDTFPhysicalUnitEnum_LuminousItensity	"LuminousIntensity"
#define XML_GDTFPhysicalUnitEnum_Angle				"Angle"
#define XML_GDTFPhysicalUnitEnum_Force				"Force"
#define XML_GDTFPhysicalUnitEnum_Frequeny			"Frequency"
#define XML_GDTFPhysicalUnitEnum_Current			"Current"
#define XML_GDTFPhysicalUnitEnum_Voltage			"Voltage"
#define XML_GDTFPhysicalUnitEnum_Power				"Power"
#define XML_GDTFPhysicalUnitEnum_Energy				"Energy"
#define XML_GDTFPhysicalUnitEnum_Area				"Area"
#define XML_GDTFPhysicalUnitEnum_Volume				"Volume"
#define XML_GDTFPhysicalUnitEnum_Speed				"Speed"
#define XML_GDTFPhysicalUnitEnum_Acceleration		"Acceleration"
#define XML_GDTFPhysicalUnitEnum_AngularSpeed		"AngularSpeed"
#define XML_GDTFPhysicalUnitEnum_AngularAccc		"AngularAccc"
#define XML_GDTFPhysicalUnitEnum_WaveLength			"WaveLength"
#define XML_GDTFPhysicalUnitEnum_ColorComponent		"ColorComponent"

#define XML_EGdtfSpecialEnum_None			"Node"
#define XML_EGdtfSpecialEnum_Dimmer			"Dimmer"
#define XML_EGdtfSpecialEnum_Pan			"Pan"
#define XML_EGdtfSpecialEnum_Tilt			"Tilt"
#define XML_EGdtfSpecialEnum_X				"X"
#define XML_EGdtfSpecialEnum_Y				"Y"
#define XML_EGdtfSpecialEnum_Z				"Z"
#define XML_EGdtfSpecialEnum_RGB			"RGB"
#define XML_EGdtfSpecialEnum_Hue			"Hue"
#define XML_EGdtfSpecialEnum_Saturation		"Saturation"
#define XML_EGdtfSpecialEnum_Brightness		"Brightness"
#define XML_EGdtfSpecialEnum_ColorWheel		"ColorWheel"
#define XML_EGdtfSpecialEnum_Focus			"Focus"
#define XML_EGdtfSpecialEnum_Zoom			"Zoom"
#define XML_EGdtfSpecialEnum_Dummy			"Dummy"

#define XML_GDTF_ActivationGroupNode				"ActivationGroup"
#define XML_GDTF_ActivationGroupName				"Name"

#define XML_GDTF_FeatureGroupNode					"FeatureGroup"
#define XML_GDTF_FeatureGroupName					"Name"
#define XML_GDTF_FeatureGroupPrettyName				"Pretty"

#define XML_GDTF_FeatureNode					"Feature"
#define XML_GDTF_FeatureName					"Name"

#define XML_GDTF_FixtureChildNodeWheels				"Wheels"
#define XML_GDTF_FixtureChildNodeModels				"Models"
#define XML_GDTF_FixtureChildNodeGeomertries		"Geometries"
#define XML_GDTF_FixtureChildNodeDMX				"DMXModes"
#define XML_GDTF_FixtureChildNodeRevisions			"Revisions"
#define XML_GDTF_FixtureChildNodePresets			"FTPresets"
#define XML_GDTF_FixtureChildNodeMacros				"FTMacros"
#define XML_GDTF_FixtureChildNodeRDM				"FTRDM"

#define XML_GDTF_FixtureChildNodePhysicalDesrip		 "PhysicalDescriptions"
#define XML_GDTF_PhysicalDescriptionsAttrColorSpace  "ColorSpace"

//-----------------------------------------------------------------------------
// ColorSpace
#define XML_GDTF_ColorSpaceNode         "ColorSpace"

// ColorSpace Attributes
#define XML_GDTF_ColorSpace_Mode        "Mode"
#define XML_GDTF_ColorSpace_Name        "Name"
#define XML_GDTF_ColorSpace_Red         "Red"
#define XML_GDTF_ColorSpace_Green       "Green"
#define XML_GDTF_ColorSpace_Blue	    "Blue"
#define XML_GDTF_ColorSpace_WhitePoint  "WhitePoint"
//-----------------------------------------------------------------------------
// Filter
#define XML_GDTF_FiltersCollect         "Filters"
#define XML_GDTF_FilterNode             "Filter"
// Filter Attribs
#define XML_GDTF_Filter_Name            "Name"
#define XML_GDTF_FilterColor            "Color"
//-----------------------------------------------------------------------------

#define XML_GDTF_WheelNodeName			"Wheel"
#define XML_GDTF_WheelName				"Name"

#define XML_GDTF_WheelSlotNodeName		"Slot"
#define XML_GDTF_WheelSlotName			"Name"
#define XML_GDTF_WheelSlotColor			"Color"
#define XML_GDTF_WheelSlotPicture		"MediaFileName"
#define XML_GDTF_WheelSlotFilter		"Filter"

#define XML_GDTF_PrismFacetNodeName		"Facet"
#define XML_GDTF_PrismFacetColor		"Color"
#define XML_GDTF_PrismFacetRotation		"Rotation"

#define XML_GDTF_AnimationSystemNodeName    "AnimationSystem"
#define XML_GDTF_AnimationSystemP1          "P1"
#define XML_GDTF_AnimationSystemP2          "P2"
#define XML_GDTF_AnimationSystemP3          "P3"
#define XML_GDTF_AnimationSystemRadius      "Radius"

#define XML_GDTF_ModelNodeName			"Model"
#define XML_GDTF_ModelName				"Name"
#define XML_GDTF_ModelLength			"Length"
#define XML_GDTF_ModelWidth				"Width"
#define XML_GDTF_ModelHeight			"Height"
#define XML_GDTF_ModelPrimitiveType		"PrimitiveType"
#define XML_GDTF_ModelFile				"File"
#define XML_GDTF_ModelSVGOffsetX		"SVGOffsetX"
#define XML_GDTF_ModelSVGOffsetY		"SVGOffsetY"
#define XML_GDTF_ModelSVGSideOffsetX	"SVGSideOffsetX"
#define XML_GDTF_ModelSVGSideOffsetY	"SVGSideOffsetY"
#define XML_GDTF_ModelSVGFrontOffsetX	"SVGFrontOffsetX"
#define XML_GDTF_ModelSVGFrontOffsetY	"SVGFrontOffsetY"

#define XML_GDTF_PrimitiveTypeEnum_Undefined	    "Undefined"
#define XML_GDTF_PrimitiveTypeEnum_Cube			    "Cube"
#define XML_GDTF_PrimitiveTypeEnum_Cylinder		    "Cylinder"
#define XML_GDTF_PrimitiveTypeEnum_Sphere		    "Sphere"
#define XML_GDTF_PrimitiveTypeEnum_Base			    "Base"
#define XML_GDTF_PrimitiveTypeEnum_Yoke			    "Yoke"
#define XML_GDTF_PrimitiveTypeEnum_Head			    "Head"
#define XML_GDTF_PrimitiveTypeEnum_Scanner		    "Scanner"
#define XML_GDTF_PrimitiveTypeEnum_Conventional	    "Conventional"
#define XML_GDTF_PrimitiveTypeEnum_Pigtail	        "Pigtail"
#define XML_GDTF_PrimitiveTypeEnum_Base1_1          "Base1_1"
#define XML_GDTF_PrimitiveTypeEnum_Scanner1_1       "Scanner1_1"
#define XML_GDTF_PrimitiveTypeEnum_Conventional1_1  "Conventional1_1"

#define XML_GDTF_GeometryNodeName				"Geometry"
#define XML_GDTF_GeometryName					"Name"
#define XML_GDTF_GeometryModelRef				"Model"
#define XML_GDTF_GeometryMatrix					"Position"

#define XML_GDTF_GeometryAxisNodeName			"Axis"

#define XML_GDTF_FilterBeamNodeName				"FilterBeam"

#define XML_GDTF_FilterColorNodeName			"FilterColor"

#define XML_GDTF_FilterGoboNodeName				"FilterGobo"

#define XML_GDTF_FilterShaperNodeName			"FilterShaper"

#define XML_GDTF_MediaServerCameraNodeName		"MediaServerCamera"

#define XML_GDTF_MediaServerLayerNodeName		"MediaServerLayer"

#define XML_GDTF_MediaServerMasterNodeName		"MediaServerMaster"

#define XML_GDTF_DisplayNodeName                "Display"
#define XML_GDTF_DisplayTexture                 "Texture"

#define XML_GDTF_LaserProtocolNodeName          "Protocol"
#define XML_GDTF_LaserProtocolName              "Name"

#define XML_GDTF_LaserNodeName                  "Laser"
#define XML_GDTF_LaserColorType                 "ColorType"
#define XML_GDTF_LaserColor                     "Color"
#define XML_GDTF_LaserOutputStrength            "OutputStrength"
#define XML_GDTF_LaserEmitter                   "Emitter"
#define XML_GDTF_LaserBeamDiameter              "BeamDiameter"
#define XML_GDTF_LaserBeamDivergenceMin         "BeamDivergenceMin"
#define XML_GDTF_LaserBeamDivergenceMax         "BeamDivergenceMax"
#define XML_GDTF_LaserScanAnglePan              "ScanAnglePan"
#define XML_GDTF_LaserScanAngleTilt             "ScanAngleTilt"
#define XML_GDTF_LaserScanSpeed                 "ScanSpeed"

#define XML_GDTF_PinPatchNodeName               "PinPatch"
#define XML_GDTF_PinPatchToWiringObject         "ToWiringObject"
#define XML_GDTF_PinPatchFromPin                "FromPin"
#define XML_GDTF_PinPatchToPin                  "ToPin"

#define XML_GDTF_WiringObjectNodeName           "WiringObject"
#define XML_GDTF_WiringObjectConnectorType      "ConnectorType"
#define XML_GDTF_WiringObjectComponentType      "ComponentType"
#define XML_GDTF_WiringObjectSignalType         "SignalType"
#define XML_GDTF_WiringObjectPinCount           "PinCount"
#define XML_GDTF_WiringObjectSignalLayer        "SignalLayer"
#define XML_GDTF_WiringObjectOrientation        "Orientation"
#define XML_GDTF_WiringObjectWireGroup          "WireGroup"
#define XML_GDTF_WiringObjectElectricalPayLoad  "ElectricalPayLoad"
#define XML_GDTF_WiringObjectVoltageRangeMin    "VoltageRangeMin"
#define XML_GDTF_WiringObjectVoltageRangeMax    "VoltageRangeMax"
#define XML_GDTF_WiringObjectFrequencyRangeMin  "FrequencyRangeMin"
#define XML_GDTF_WiringObjectFrequencyRangeMax  "FrequencyRangeMax"
#define XML_GDTF_WiringObjectCosPhi             "CosPhi"
#define XML_GDTF_WiringObjectMaxPayLoad         "MaxPayLoad"
#define XML_GDTF_WiringObjectVoltage            "Voltage"
#define XML_GDTF_WiringObjectFuseCurrent        "FuseCurrent"
#define XML_GDTF_WiringObjectFuseRating         "FuseRating"

#define XML_GDTF_InventoryNodeName              "Inventory"
#define XML_GDTF_InventoryCount                 "Count"

#define XML_GDTF_StructureNodeName                  "Structure"
#define XML_GDTF_StructureLinkedGeometry            "LinkedGeometry"
#define XML_GDTF_StructureStructureType             "StructureType"
#define XML_GDTF_StructureCrossSectionType          "CrossSectionType"
#define XML_GDTF_StructureCrossSectionHeight        "CrossSectionHeight"
#define XML_GDTF_StructureCrossSectionWallThickness "CrossSectionWallThickness"
#define XML_GDTF_StructureTrussCrossSection         "TrussCrossSection"

#define XML_GDTF_SupportNodeName                    "Support"
#define XML_GDTF_SupportSupportType                 "SupportType"
#define XML_GDTF_SupportCapacityX                   "CapacityX"
#define XML_GDTF_SupportCapacityY                   "CapacityY"
#define XML_GDTF_SupportCapacityZ                   "CapacityZ"
#define XML_GDTF_SupportCapacityXX                  "CapacityXX"
#define XML_GDTF_SupportCapacityYY                  "CapacityYY"
#define XML_GDTF_SupportCapacityZZ                  "CapacityZZ"
#define XML_GDTF_SupportRopeCrossSection            "RopeCrossSection"
#define XML_GDTF_SupportRopeOffset                  "RopeOffset"
#define XML_GDTF_SupportResistanceX                 "ResistanceX"
#define XML_GDTF_SupportResistanceY                 "ResistanceY"
#define XML_GDTF_SupportResistanceZ                 "ResistanceZ"
#define XML_GDTF_SupportResistanceXX                "ResistanceXX"
#define XML_GDTF_SupportResistanceYY                "ResistanceYY"
#define XML_GDTF_SupportResistanceZZ                "ResistanceZZ"

#define XML_GDTF_MagnetNodeName                 "Magnet"

#define XML_GDTF_LampNodeName					"Beam"
#define XML_GDTF_LampLampType					"LampType"
#define XML_GDTF_LampPowerConsumption			"PowerConsumption"
#define XML_GDTF_LampLuminousFlux			    "LuminousFlux"
#define XML_GDTF_ColorTemperature				"ColorTemperature"
#define XML_GDTF_BeamAngle						"BeamAngle"
#define XML_GDTF_BeamRadius						"BeamRadius"
#define XML_GDTF_FieldAngle						"FieldAngle"
#define XML_GDTF_ThrowRatio						"ThrowRatio"
#define XML_GDTF_RectangleRatio					"RectangleRatio"
#define XML_GDTF_BeamType						"BeamType"
#define XML_GDTF_BeamColorRenderingIndex        "ColorRenderingIndex"				
#define XML_GDTF_BeamEmitterSpectrum            "EmitterSpectrum"				

#define XML_GDTF_BeamTypeEnum_Wash				"Wash"
#define XML_GDTF_BeamTypeEnum_Spot				"Spot"
#define XML_GDTF_BeamTypeEnum_None				"None"
#define XML_GDTF_BeamTypeEnum_Rectangle			"Rectangle"
#define XML_GDTF_BeamTypeEnum_PC			    "PC"
#define XML_GDTF_BeamTypeEnum_Fresnel			"Fresnel"
#define XML_GDTF_BeamTypeEnum_Glow			    "Glow"



#define XML_GDTF_LampTypeEnum_Discharge			"Discharge"
#define XML_GDTF_LampTypeEnum_Tungsten			"Tungsten"
#define XML_GDTF_LampTypeEnum_Halogen			"Halogen"
#define XML_GDTF_LampTypeEnum_LED				"LED"

#define XML_GDTF_BreakNodeName					"Break"
#define XML_GDTF_BreakDMXBreak					"DMXBreak"
#define XML_GDTF_BreakOffset					"DMXOffset"

#define XML_GDTF_GeometryReferenceNodeName		"GeometryReference"
#define XML_GDTF_GeometryReferenceLinkedGeo     "Geometry"


#define XML_GDTF_DMXModeNodeName				"DMXMode"
#define XML_GDTF_DMXModeName					"Name"
#define XML_GDTF_DMXModeDescription				"Description"
#define XML_GDTF_DMXModeGeometryRef				"Geometry"
#define XML_GDTF_DMXModeDMXChannels				"DMXChannels"
#define XML_GDTF_DMXModeRelations				"Relations"
#define XML_GDTF_DMXModeMacros					"FTMacros"


#define XML_GDTF_DMXChannelNodeName				"DMXChannel"
#define XML_GDTF_DMXChannelDMXBreak				"DMXBreak"
#define XML_GDTF_DMXChannelOffset				"Offset"

#define XML_GDTF_DMXChannelHighlight			"Highlight"
#define XML_GDTF_DMXChannelGeometry				"Geometry"
#define XML_GDTF_DMXChannelInitialFunction  	"InitialFunction"

#define XML_GDTF_DMXFChannel_NONEVALUE			    "None"
#define XML_GDTF_DMXChannelDMXBreak_OverwriteValue	"Overwrite"

#define XML_GDTF_DMXFrequencyEnum_60			"60"
#define XML_GDTF_DMXFrequencyEnum_30			"30"
#define XML_GDTF_DMXFrequencyEnum_15			"15"
#define XML_GDTF_DMXFrequencyEnum_Slow1			"Slow1"
#define XML_GDTF_DMXFrequencyEnum_Slow2			"Slow2"
#define XML_GDTF_DMXFrequencyEnum_Slow3			"Slow3"

#define XML_GDTF_DMXLogicalChannelNodeName		"LogicalChannel"
#define XML_GDTF_DMXLogicalChannelAttribute		"Attribute"
#define XML_GDTF_DMXLogicalChannelSnap			"Snap"
#define XML_GDTF_DMXLogicalChannelMaster		"Master"
#define XML_GDTF_DMXLogicalChannelMibFadeFrames		    "MibFade"
#define XML_GDTF_DMXLogicalChannelDMXChangeTimeLimit    "DMXChangeTimeLimit"


#define XML_GDTF_DMXSnapEnum_Yes				"Yes"
#define XML_GDTF_DMXSnapEnum_No					"No"
#define XML_GDTF_DMXSnapEnum_On					"On"
#define XML_GDTF_DMXSnapEnum_Off				"Off"

#define XML_GDTF_DMXChannelFuntionNodeName				"ChannelFunction"
#define XML_GDTF_DMXChannelFuntionName					"Name"
#define XML_GDTF_DMXChannelFuntionAttribute             "Attribute"
#define XML_GDTF_DMXChannelFuntionOriginalAttribute		"OriginalAttribute"
#define XML_GDTF_DMXChannelFuntionDefault				"Default"
#define XML_GDTF_DMXChannelFuntionDMXFrom				"DMXFrom"
#define XML_GDTF_DMXChannelFuntionPhysicalFrom			"PhysicalFrom"
#define XML_GDTF_DMXChannelFuntionPhysicalTo			"PhysicalTo"
#define XML_GDTF_DMXChannelFuntionRealFade				"RealFade"
#define XML_GDTF_DMXChannelFuntionRealAcceleration		"RealAcceleration"
#define XML_GDTF_DMXChannelFuntionWheelRef				"Wheel"
#define XML_GDTF_DMXChannelEmitter						"Emitter"
#define XML_GDTF_DMXChannelFuntionModeMaster			"ModeMaster"
#define XML_GDTF_DMXChannelFuntionModeFrom				"ModeFrom"
#define XML_GDTF_DMXChannelFuntionModeTo				"ModeTo"
#define XML_GDTF_DMXChannelFuntionFilter                "Filter"
#define XML_GDTF_DMXChannelFunctionColorSpace           "ColorSpace"
#define XML_GDTF_DMXChannelFunctionGamut                "Gamut"
#define XML_GDTF_DMXChannelFunctionDMXProfile           "DMXProfile"
#define XML_GDTF_DMXChannelFunctionMin                  "Min"
#define XML_GDTF_DMXChannelFunctionMax                  "Max"
#define XML_GDTF_DMXChannelFunctionCustomName           "CustomName"

#define XML_GDTF_DMXChannelDmxnvertEnum_Yes				"Yes"
#define XML_GDTF_DMXChannelDmxInvertEnum_No				"No"

#define XML_GDTF_DMXMasterEnum_None						"None"
#define XML_GDTF_DMXMasterEnum_Grand					"Grand"
#define XML_GDTF_DMXMasterEnum_Group					"Group"


#define XML_GDTF_DMXChannelSetNodeName					"ChannelSet"
#define XML_GDTF_DMXChannelSetName						"Name"
#define XML_GDTF_DMXChannelSetDMXFrom					"DMXFrom"
#define XML_GDTF_DMXChannelSetDMXTo						"DMXTo"
#define XML_GDTF_DMXChannelSetPhysicalFrom				"PhysicalFrom"
#define XML_GDTF_DMXChannelSetPhysicalTo				"PhysicalTo"
#define XML_GDTF_DMXChannelSetWheelSlotIndexRef			"WheelSlotIndex"

#define XML_GDTF_DMXSubChannelSetNodeName				"SubChannelSet"
#define XML_GDTF_DMXSubChannelSetName					"Name"
#define XML_GDTF_DMXSubChannelSetPhysicalFrom			"PhysicalFrom"
#define XML_GDTF_DMXSubChannelSetPhysicalTo				"PhysicalTo"
#define XML_GDTF_DMXSubChannelSetSubPhysicalUnit		"SubPhysicalUnit"
#define XML_GDTF_DMXSubChannelSetDMXProfile		        "DMXProfile"
// Macros
#define XML_GDTF_MacroNodeName							"FTMacro"
#define XML_GDTF_MacroName                              "Name"
#define XML_GDTF_MacroChannelFunction                   "ChannelFunction"
#define XML_GDTF_MacroDMX                               "MacroDMX"  
#define XML_GDTF_MacroDMXStep                           "MacroDMXStep"
#define XML_GDTF_MacroDMXStepDuration                   "Duration"
#define XML_GDTF_MacroDMXValue                          "MacroDMXValue"
#define XML_GDTF_MacroDMXValue_AttrValue                "Value"
#define XML_GDTF_MacroDMXValue_AttrChannel              "DMXChannel"
#define XML_GDTF_MacroVisual                            "MacroVisual"
#define XML_GDTF_MacroVisualStep                        "MacroVisualStep"
#define XML_GDTF_MacroVisualStep_AttrDuration           "Duration"
#define XML_GDTF_MacroVisualStep_AttrFade               "Fade"
#define XML_GDTF_MacroVisualStep_AttrDelay              "Delay"
#define XML_GDTF_MacroVisualValue                       "MacroVisualValue"
#define XML_GDTF_MacroVisualValue_AttrValue             "Value"
#define XML_GDTF_MacroVisualValue_AttrChanFunc          "ChannelFunction"
//
#define XML_GDTF_DMXRelationNodeName					"Relation"
#define XML_GDTF_DMXRelationName						"Name"
#define XML_GDTF_DMXRelationMaster						"Master"
#define XML_GDTF_DMXRelationSlave						"Follower"
#define XML_GDTF_DMXRelationType						"Type"
#define XML_GDTF_DMXRelationDMXFrom						"DMXFrom"
#define XML_GDTF_DMXRelationDMXTo						"DMXTo"

#define XML_GDTF_DMXMasterEnum_Multiply					"Multiply"
#define XML_GDTF_DMXMasterEnum_Override					"Override"

#define XML_GDTF_RevisionNodeName						"Revision"
#define XML_GDTF_RevisionText							"Text"
#define XML_GDTF_RevisionDate							"Date"
#define XML_GDTF_RevisionUserId							"UserID"
#define XML_GDTF_RevisionModifiedBy						"ModifiedBy"
// -------------------------------------------------------------------------------
// Protocolls
#define XML_GDTF_Protocols                              "Protocols"

#define XML_GDTF_FTRDM                                  "FTRDM"
#define XML_GDTF_FTRDM_AttrManufacturerID               "ManufacturerID"
#define XML_GDTF_FTRDM_AttrDeviceModelID                "DeviceModelID"
#define XML_GDTF_FTRDM_AttrSoftwareVersionIDs           "SoftwareVersionIDs"
//
#define XML_GDTF_DMXPersonalityNodeNam                  "DMXPersonality"
#define XML_GDTF_DMXPersonalityValue                    "Value"   
#define XML_GDTF_DMXPersonalityDMXMode                  "DMXMode"
//
#define XML_GDTF_SoftwareVersionID_NodeNam              "SoftwareVersionID"
#define XML_GDTF_SoftwareVersionID_Value                "Value"
//
#define XML_GDTF_MapNodeName                            "Map"
#define XML_GDTF_MapKey                                 "Key"
#define XML_GDTF_MapValue                               "Value"

#define XML_GDTF_ArtNet                                 "Art-Net"
#define XML_GDTF_sACN                                   "sACN"
#define XML_GDTF_KiNET                                  "KiNET"
#define XML_GDTF_PosiStageNet                           "PosiStageNet"
#define XML_GDTF_OpenSoundControl                       "OpenSoundControl"
#define XML_GDTF_CITP                                   "CITP"

#define XML_GDTF_ThresholdOperator_Is                   "Is"
#define XML_GDTF_ThresholdOperator_IsNot                "IsNot"
#define XML_GDTF_ThresholdOperator_Greater              "Greater"
#define XML_GDTF_ThresholdOperator_Less                 "Less"
// -------------------------------------------------------------------------------
#define XML_GDTF_UserPresetNodeName						"FTPreset"

#define XML_GDTF_PhysicalDescriptionsColorSpaceCollect	"AdditionalColorSpaces"
#define XML_GDTF_PhysicalDescriptionsGamutCollect	    "Gamuts"
#define XML_GDTF_PhysicalDescriptionsEmitterCollect	    "Emitters"
#define XML_GDTF_EmitterNodeName						"Emitter"
#define XML_GDTF_EmitterName							"Name"
#define XML_GDTF_EmitterColor							"Color"
#define XML_GDTF_EmitterDominantWaveLength              "DominantWaveLength"
#define XML_GDTF_EmitterDiodePart                       "DiodePart"

#define XML_GDTF_DMX_ProfileCollect                     "DMXProfiles"
#define XML_GDTF_DMX_Profile                            "DMXProfile"
#define XML_GDTF_DMX_ProfileName                        "Name"

#define XML_GDTF_GamutNodeName                          "Gamut"
#define XML_GDTF_GamutName                              "Name"
#define XML_GDTF_GamutPoints                            "Points"

#define XML_GDTF_Point                                  "Point"
#define XML_GDTF_PointDMXPercentage                     "DMXPercentage"
#define XML_GDTF_PointCFC3                              "CFC3"
#define XML_GDTF_PointCFC2                              "CFC2"
#define XML_GDTF_PointCFC1                              "CFC1"
#define XML_GDTF_PointCFC0                              "CFC0"

#define XML_GDTF_ConnectorCollect	                    "Connectors"
#define XML_GDTF_ConnectorNodeName                      "Connector"
#define XML_GDTF_ConnectorName                          "Name"
#define XML_GDTF_ConnectorType                          "Type"
#define XML_GDTF_ConnectorDmxBreak                      "DMXBreak"
#define XML_GDTF_ConnectorGender                        "Gender"
#define XML_GDTF_ConnectorLength                        "Length"

//-----------------------------------------------------------------------------
// Properties Collect

#define XML_GDTF_PropertiesCollect	                    "Properties"

#define XML_GDTF_OperatingTemperatureNodeName           "OperatingTemperature"
#define XML_GDTF_OperatingTemperatureLow                "Low"
#define XML_GDTF_OperatingTemperatureHigh               "High"

#define XML_GDTF_WeightNodeName                         "Weight"
#define XML_GDTF_WeightValue                            "Value"

#define XML_GDTF_LegHeightNodeName                      "LegHeight"
#define XML_GDTF_LegHeightValue                         "Value"

//-----------------------------------------------------------------------------
// Measurement
#define XML_GDTF_MeasurementNodeName					"Measurement"
// Measurement Attribs
#define XML_GDTF_MeasurementPhysical                   "Physical"
#define XML_GDTF_MeasurementLuminousIntensity          "LuminousIntensity"
#define XML_GDTF_MeasurementTransmission               "Transmission"
#define XML_GDTF_MeasurementInterpolationTo            "InterpolationTo"
//-----------------------------------------------------------------------------
// MeasurementPoint
#define XML_GDTF_MeasurementPointNode                   "MeasurementPoint"
// MeasurementPoint Attribs.
#define XML_GDTF_MeasurementWaveLegth					"WaveLength"
#define XML_GDTF_MeasurementEnergy						"Energy"    
//-----------------------------------------------------------------------------
// InterpolationTo Enum
#define XML_GDTF_InterpolationTo_Linear  "Linear" 
#define XML_GDTF_InterpolationTo_Step    "Step"
#define XML_GDTF_InterpolationTo_Log     "Log"

//-----------------------------------------------------------------------------
// CanHaveChildren Enum
#define XML_GDTF_CanHaveChildren_Yes    "Yes" 
#define XML_GDTF_CanHaveChildren_No     "No"

//-----------------------------------------------------------------------------
#define XML_GDTF_ColorRenderingIndexCollect             "CRIs"
#define XML_GDTF_ColorRenderingIndexGroup               "CRIGroup"
#define XML_GDTF_ColorRenderingIndexGroup_ColorTemp     "ColorTemperature"
#define XML_GDTF_ColorRenderingIndex                    "CRI"			
#define XML_GDTF_ColorRenderingIndex_CES                "CES"
#define XML_GDTF_ColorRenderingIndex_CRI                "ColorRenderingIndex"


// ColorSample Array
#define XML_GDTF_ColorSample_1  "CES01"
#define XML_GDTF_ColorSample_2  "CES02"
#define XML_GDTF_ColorSample_3  "CES03"
#define XML_GDTF_ColorSample_4  "CES04"
#define XML_GDTF_ColorSample_5  "CES05"
#define XML_GDTF_ColorSample_6  "CES06"
#define XML_GDTF_ColorSample_7  "CES07"
#define XML_GDTF_ColorSample_8  "CES08"
#define XML_GDTF_ColorSample_9  "CES09"
#define XML_GDTF_ColorSample_10 "CES10"
#define XML_GDTF_ColorSample_11 "CES11"
#define XML_GDTF_ColorSample_12 "CES12"
#define XML_GDTF_ColorSample_13 "CES13"
#define XML_GDTF_ColorSample_14 "CES14"
#define XML_GDTF_ColorSample_15 "CES15"
#define XML_GDTF_ColorSample_16 "CES16"
#define XML_GDTF_ColorSample_17 "CES17"
#define XML_GDTF_ColorSample_18 "CES18"
#define XML_GDTF_ColorSample_19 "CES19"
#define XML_GDTF_ColorSample_20 "CES20"
#define XML_GDTF_ColorSample_21 "CES21"
#define XML_GDTF_ColorSample_22 "CES22"
#define XML_GDTF_ColorSample_23 "CES23"
#define XML_GDTF_ColorSample_24 "CES24"
#define XML_GDTF_ColorSample_25 "CES25"
#define XML_GDTF_ColorSample_26 "CES26"
#define XML_GDTF_ColorSample_27 "CES27"
#define XML_GDTF_ColorSample_28 "CES28"
#define XML_GDTF_ColorSample_29 "CES29"
#define XML_GDTF_ColorSample_30 "CES30"
#define XML_GDTF_ColorSample_31 "CES31"
#define XML_GDTF_ColorSample_32 "CES32"
#define XML_GDTF_ColorSample_33 "CES33"
#define XML_GDTF_ColorSample_34 "CES34"
#define XML_GDTF_ColorSample_35 "CES35"
#define XML_GDTF_ColorSample_36 "CES36"
#define XML_GDTF_ColorSample_37 "CES37"
#define XML_GDTF_ColorSample_38 "CES38"
#define XML_GDTF_ColorSample_39 "CES39"
#define XML_GDTF_ColorSample_40 "CES40"
#define XML_GDTF_ColorSample_41 "CES41"
#define XML_GDTF_ColorSample_42 "CES42"
#define XML_GDTF_ColorSample_43 "CES43"
#define XML_GDTF_ColorSample_44 "CES44"
#define XML_GDTF_ColorSample_45 "CES45"
#define XML_GDTF_ColorSample_46 "CES46"
#define XML_GDTF_ColorSample_47 "CES47"
#define XML_GDTF_ColorSample_48 "CES48"
#define XML_GDTF_ColorSample_49 "CES49"
#define XML_GDTF_ColorSample_50 "CES50"
#define XML_GDTF_ColorSample_51 "CES51"
#define XML_GDTF_ColorSample_52 "CES52"
#define XML_GDTF_ColorSample_53 "CES53"
#define XML_GDTF_ColorSample_54 "CES54"
#define XML_GDTF_ColorSample_55 "CES55"
#define XML_GDTF_ColorSample_56 "CES56"
#define XML_GDTF_ColorSample_57 "CES57"
#define XML_GDTF_ColorSample_58 "CES58"
#define XML_GDTF_ColorSample_59 "CES59"
#define XML_GDTF_ColorSample_60 "CES60"
#define XML_GDTF_ColorSample_61 "CES61"
#define XML_GDTF_ColorSample_62 "CES62"
#define XML_GDTF_ColorSample_63 "CES63"
#define XML_GDTF_ColorSample_64 "CES64"
#define XML_GDTF_ColorSample_65 "CES65"
#define XML_GDTF_ColorSample_66 "CES66"
#define XML_GDTF_ColorSample_67 "CES67"
#define XML_GDTF_ColorSample_68 "CES68"
#define XML_GDTF_ColorSample_69 "CES69"
#define XML_GDTF_ColorSample_70 "CES70"
#define XML_GDTF_ColorSample_71 "CES71"
#define XML_GDTF_ColorSample_72 "CES72"
#define XML_GDTF_ColorSample_73 "CES73"
#define XML_GDTF_ColorSample_74 "CES74"
#define XML_GDTF_ColorSample_75 "CES75"
#define XML_GDTF_ColorSample_76 "CES76"
#define XML_GDTF_ColorSample_77 "CES77"
#define XML_GDTF_ColorSample_78 "CES78"
#define XML_GDTF_ColorSample_79 "CES79"
#define XML_GDTF_ColorSample_80 "CES80"
#define XML_GDTF_ColorSample_81 "CES81"
#define XML_GDTF_ColorSample_82 "CES82"
#define XML_GDTF_ColorSample_83 "CES83"
#define XML_GDTF_ColorSample_84 "CES84"
#define XML_GDTF_ColorSample_85 "CES85"
#define XML_GDTF_ColorSample_86 "CES86"
#define XML_GDTF_ColorSample_87 "CES87"
#define XML_GDTF_ColorSample_88 "CES88"
#define XML_GDTF_ColorSample_89 "CES89"
#define XML_GDTF_ColorSample_90 "CES90"
#define XML_GDTF_ColorSample_91 "CES91"
#define XML_GDTF_ColorSample_92 "CES92"
#define XML_GDTF_ColorSample_93 "CES93"
#define XML_GDTF_ColorSample_94 "CES94"
#define XML_GDTF_ColorSample_95 "CES95"
#define XML_GDTF_ColorSample_96 "CES96"
#define XML_GDTF_ColorSample_97 "CES97"
#define XML_GDTF_ColorSample_98 "CES98"
#define XML_GDTF_ColorSample_99 "CES99"

//-----------------------------------------------------------------------------
// ColorSpace Enum Vals
#define XML_GDTF_ColorSpaceEnum "ColorSpace"

#define XML_GDTF_ColorSpaceEnum_sRGB      "sRGB" 
#define XML_GDTF_ColorSpaceEnum_Custom    "Custom"
#define XML_GDTF_ColorSpaceEnum_ProPhoto  "ProPhoto"     
#define XML_GDTF_ColorSpaceEnumr_ANSI     "ANSI"   
//-----------------------------------------------------------------------------
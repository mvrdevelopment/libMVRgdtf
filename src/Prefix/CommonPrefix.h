//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------


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

// ----------------------------------------------------------------------------------------------------------------------------------
// SceneDataExchange XML Values
#define XML_Val_RootNodeName			"GeneralScenceDescription"
#define XML_Val_RootAttrMainVersion		"verMajor"
#define XML_Val_RootAttrMinorVersion	"verMinor"

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

#define XML_Val_ClassNodeName	"Class"

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
#define XML_Val_ClassingNodeName		"Classing"

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

#define XML_Val_SceneObjectNodeName			"SceneObject"

#define XML_Val_FocusPointObjectNodeName	"FocusPoint"

#define XML_Val_TrussObjectNodeName			"Truss"

#define XML_Val_VideoScreenObjectNodeName	"VideoScreen"

#define XML_Val_SymbolObjectNodeName		"Symbol"
#define XML_Val_GuidSymdefAttrName			"symdef"

#define XML_Val_GeometryObjectNodeName		"Geometry3D"
#define XML_Val_GeometryObjectAttrFile		"fileName"

const Sint32 kMVR_MajorVersion = 1;
const Sint32 kMVR_MinorVersion = 1;


// Export
enum EExportQuality : short
{
	eLowConvertRes		= 16,
	eMedConvertRes		= 64,
	eHighConvertRes		= 128,
	eVeryHighConvertRes = 512,
};


// ----------------------------------------------------------------------------------------------------------------------------------
// GDTF XML Values

#define XML_GDTF_GDTFFILENAME			"description.xml"

#define XML_GDTF_ROOTNODENAME			"GDTF"
#define XML_GDTF_ROOTNODEATTRVERSION	"DataVersion"
#define XML_GDTF_CurrentVersion			"0.87"

#define XML_GDTF_FixtureNodeName		"FixtureType"
#define XML_GDTF_FixtureName			"Name"
#define XML_GDTF_FixtureShortName		"ShortName"
#define XML_GDTF_FixtureManufacturer	"Manufacturer"
#define XML_GDTF_FixtureDescription		"Description"
#define XML_GDTF_FixtureTypeID			"FixtureTypeID"
#define XML_GDTF_FixtureThumbnail		"Thumbnail"

#define XML_GDTF_FixtureChildNodeAttributeDef		"AttributeDefinitions"
#define XML_GDTF_FixtureChildNodeActivationGroupDef	"ActivationGroups"
#define XML_GDTF_FixtureChildNodeFeatureGroupDef	"FeatureGroups"
#define XML_GDTF_FixtureChildNodeAttributesDef		"Attributes"

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
#define XML_GDTFPhysicalUnitEnum_Temperatur			"Temperatur"
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
#define XML_GDTF_FixtureChildNodePhysicalDesrip		"PhysicalDescriptions"
#define XML_GDTF_FixtureChildNodeRDM				"FTRDM"

#define XML_GDTF_WheelNodeName			"Wheel"
#define XML_GDTF_WheelName				"Name"
#define XML_GDTF_WhhelSubAttribute		"SubAttribute"

#define XML_GDTF_WheelSlotNodeName		"Slot"
#define XML_GDTF_WheelSlotName			"Name"
#define XML_GDTF_WhhelSlotColor			"Color"
#define XML_GDTF_WhhelSlotPicture		"MediaFileName"

#define XML_GDTF_PrismFacetNodeName		"Facet"
#define XML_GDTF_PrismFacetColor		"Color"
#define XML_GDTF_PrismFacetRotation		"Rotation"


#define XML_GDTF_ModelNodeName			"Model"
#define XML_GDTF_ModelName				"Name"
#define XML_GDTF_ModelLength			"Length"
#define XML_GDTF_ModelWidth				"Width"
#define XML_GDTF_ModelHeight			"Height"
#define XML_GDTF_ModelPrimitiveType		"PrimitiveType"
#define XML_GDTF_ModelFile				"File"

#define XML_GDTF_PrimitiveTypeEnum_Undefined	"Undefined"
#define XML_GDTF_PrimitiveTypeEnum_Cube			"Cube"
#define XML_GDTF_PrimitiveTypeEnum_Cylinder		"Cylinder"
#define XML_GDTF_PrimitiveTypeEnum_Sphere		"Sphere"
#define XML_GDTF_PrimitiveTypeEnum_Base			"Base"
#define XML_GDTF_PrimitiveTypeEnum_Yoke			"Yoke"
#define XML_GDTF_PrimitiveTypeEnum_Head			"Head"
#define XML_GDTF_PrimitiveTypeEnum_Scanner		"Scanner"
#define XML_GDTF_PrimitiveTypeEnum_Conventional	"Conventional"
#define XML_GDTF_PrimitiveTypeEnum_Pigtail	    "Pigtail"

#define XML_GDTF_GeometryNodeName				"Geometry"
#define XML_GDTF_GeometryName					"Name"
#define XML_GDTF_GeometryModelRef				"Model"
#define XML_GDTF_GeometryMatrix					"Position"

#define XML_GDTF_GeometryAxisNodeName			"Axis"
#define XML_GDTF_GeometryAxisFrom				"From"
#define XML_GDTF_GeometryAxisTo					"To"
#define XML_GDTF_GeometryAxisSpeed				"Speed"

#define XML_GDTF_FilterBeamNodeName				"FilterBeam"

#define XML_GDTF_FilterColorNodeName			"FilterColor"

#define XML_GDTF_FilterGoboNodeName				"FilterGobo"

#define XML_GDTF_FilterShaperNodeName			"FilterShaper"

#define XML_GDTF_LampNodeName					"Beam"
#define XML_GDTF_LampLampType					"LampType"
#define XML_GDTF_LampPowerConsumption			"PowerConsumption"
#define XML_GDTF_LampLuminousIntensity			"LuminousIntensity"
#define XML_GDTF_ColorTemperature				"ColorTemperature"
#define XML_GDTF_BeamAngle						"BeamAngle"
#define XML_GDTF_BeamRadius						"BeamRadius"
#define XML_GDTF_BeamType						"BeamType"
#define XML_GDTF_ColorRenderingIndex			"ColorRenderingIndex"

#define XML_GDTF_BeamTypeEnum_Wash				"Wash"
#define XML_GDTF_BeamTypeEnum_Spot				"Spot"
#define XML_GDTF_BeamTypeEnum_None				"None"



#define XML_GDTF_LampTypeEnum_Discharge			"Discharge"
#define XML_GDTF_LampTypeEnum_Tungsten			"Tungsten"
#define XML_GDTF_LampTypeEnum_Halogen			"Halogen"
#define XML_GDTF_LampTypeEnum_LED				"LED"

#define XML_GDTF_BreakNodeName					"Break"
#define XML_GDTF_BreakDMXBreak					"DMXBreak"
#define XML_GDTF_BreakOffset					"DMXOffset"

#define XML_GDTF_GeometryReferenceNodeName		"GeometryReference"


#define XML_GDTF_DMXModeNodeName				"DMXMode"
#define XML_GDTF_DMXModeName					"Name"
#define XML_GDTF_DMXModeGeometryRef				"Geometry"
#define XML_GDTF_DMXModeDMXChannels				"DMXChannels"
#define XML_GDTF_DMXModeRelations				"Relations"

#define XML_GDTF_DMXChannelNodeName				"DMXChannel"
#define XML_GDTF_DMXChannelDMXBreak				"DMXBreak"
#define XML_GDTF_DMXChannelCoarse				"Coarse"
#define XML_GDTF_DMXChannelFine					"Fine"
#define XML_GDTF_DMXChannelUltra				"Ultra"
#define XML_GDTF_DMXChannelUber                 "Uber"
#define XML_GDTF_DMXChannelFrequency			"Frequency"
#define XML_GDTF_DMXChannelDefault				"Default"
#define XML_GDTF_DMXChannelHighlight			"Highlight"
#define XML_GDTF_DMXChannelMibFadeFrames		"MibFadeFrames"
#define XML_GDTF_DMXChannelDMXChangeTimeLimit	"DMXChangeTimeLimit"
#define XML_GDTF_DMXChannelGeometry				"Geometry"

#define XML_GDTF_DMXFChannel_NONEVALUE			"None"

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

#define XML_GDTF_DMXSnapEnum_Yes				"Yes"
#define XML_GDTF_DMXSnapEnum_No					"No"
#define XML_GDTF_DMXSnapEnum_On					"On"
#define XML_GDTF_DMXSnapEnum_Off				"Off"

#define XML_GDTF_DMXChannelFuntionNodeName				"ChannelFunction"
#define XML_GDTF_DMXChannelFuntionName					"Name"
#define XML_GDTF_DMXChannelFuntionAttribute             "Attribute"
#define XML_GDTF_DMXChannelFuntionOriginalAttribute		"OriginalAttribute"
#define XML_GDTF_DMXChannelFuntionDMXFrom				"DMXFrom"
#define XML_GDTF_DMXChannelFuntionPhysicalFrom			"PhysicalFrom"
#define XML_GDTF_DMXChannelFuntionPhysicalTo			"PhysicalTo"
#define XML_GDTF_DMXChannelFuntionRealFade				"RealFade"
#define XML_GDTF_DMXChannelFuntionWheelRef				"Wheel"
#define XML_GDTF_DMXChannelEmitter						"Emitter"
#define XML_GDTF_DMXChannelDMXInvert					"DMXInvert"
#define XML_GDTF_DMXChannelEncoderInvert				"EncoderInvert"

#define XML_GDTF_DMXChannelEncoderInvertEnum_Yes		"Yes"
#define XML_GDTF_DMXChannelEncoderInvertEnum_No			"No"

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

#define XML_GDTF_DMXRelationNodeName					"Relation"
#define XML_GDTF_DMXRelationName						"Name"
#define XML_GDTF_DMXRelationMaster						"Master"
#define XML_GDTF_DMXRelationSlave						"Slave"
#define XML_GDTF_DMXRelationType						"Type"
#define XML_GDTF_DMXRelationDMXFrom						"DMXFrom"
#define XML_GDTF_DMXRelationDMXTo						"DMXTo"

#define XML_GDTF_DMXMasterEnum_Mode						"Mode"
#define XML_GDTF_DMXMasterEnum_Multiply					"Multiply"
#define XML_GDTF_DMXMasterEnum_Override					"Override"

#define XML_GDTF_RevisionNodeName						"Revision"
#define XML_GDTF_RevisionText							"Text"
#define XML_GDTF_RevisionDate							"Date"

#define XML_GDTF_MacroNodeName							"FTMacro"
#define XML_GDTF_UserPresetNodeName						"FTPreset"

#define XML_GDTF_PhysicalDescriptionsEmitterCollect		"Emitters"

#define XML_GDTF_EmitterNodeName						"Emitter"
#define XML_GDTF_EmitterName							"Name"
#define XML_GDTF_EmitterColor							"Color"

#define XML_GDTF_MeasurementNodeName					"Measurement"
#define XML_GDTF_MeasurementWaveLegth					"WaveLength"
#define XML_GDTF_MeasurementEnergy						"Energy"


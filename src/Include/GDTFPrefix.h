//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------

#ifndef __GDTFPREFIX
#define __GDTFPREFIX

namespace VectorworksMVR
{
	namespace GdtfDefines
	{
		typedef Sint32		DMXAddress;		
		typedef Sint32		DmxValue;
		
		enum EGdtfObjectType
		{
			eGdtfActivationGroup		= 0,
			eGdtfFeatureGroup			= 1,
			eGdtfFeature				= 2,
			eGdtfSubAttribute			= 3,
			eGdtfAttribute				= 4,
			eGdtfWheelSlot				= 5,
			eGdtfPrismFacet				= 6,
			eGdtfWheel					= 7,
			eGdtfModel					= 8,
			eGdtfGeometry				= 9,
			eGdtfGeometryAxis			= 10,
			eGdtfGeometryBeamFilter		= 11,
			eGdtfGeometryColorFilter	= 12,
			eGdtfGeometryGoboFilter		= 13,
			eGdtfGeometryShaperFilter	= 14,
			eGdtfGeometryLamp			= 15,
			eGdtfBreak					= 16,
			eGdtfGeometryReference		= 17,
			eGdtfDmxChannelSet			= 18,
			eGdtfDmxChannelFuntion		= 19,
			eGdtfDmxLogicalChannel		= 20,
			eGdtfDmxChannel				= 21,
			eGdtfDmxRelation			= 22,
			eGdtfDmxMode				= 23,
			eGdtfRevision				= 24,
			eGdtfUserPreset				= 25,
			eGdtfMacro					= 26,
			eGdtfMeasurementPoint		= 27,
			eGdtfPhysicalEmitter		= 28,
			eGdtfPhysicalDescription	= 29,
			eGdtfFixture				= 30,
		};
		
		enum class EGdtfPhysicalUnit
		{
			None			= 0,	// Default
			Percent			= 1,
			Length			= 2,	// Meter
			Mass			= 3,	// kg
			Time			= 4,	// s
			Temperatur		= 5,	// K
			LuminousItensity= 6,	//cd
			Angle			= 7,	//degree
			Force			= 8,	// Newton
			Frequeny		= 9,	// 1/s
			Current			= 10,	// A
			Voltage			= 12,	// V
			Power			= 13,	// W
			Energy			= 14,	// J
			Area			= 15,	//m^2
			Volume			= 16,	// m^3
			Speed			= 17,	// m/s
			Acceleration	= 18,	//m/s^2
			AngularSpeed	= 19,	// degree/s
			AngularAccc		= 20,	//degree/s^2
			WaveLength		= 21,	//nm
			ColorComponent	= 22
		};
		
		enum class EGdtfSpecial
		{
			None		= 0,			//Default
			Dimmer		= 1,
			Pan			= 2,
			Tilt		= 3,
			X			= 4,
			Y			= 5,
			Z			= 6,
			RGB			= 7,
			Hue			= 8,
			Saturation	= 9,
			Brightness	= 10,
			ColorWheel	= 11,
			Focus		= 12,
			Zoom		= 13,
			Dummy		= 14,
		};
		
		enum EGdtfModel_PrimitiveType
		{
			eGdtfModel_PrimitiveType_Undefined		= 0,
			eGdtfModel_PrimitiveType_Cube			= 1,
			eGdtfModel_PrimitiveType_Cylinder		= 2,
			eGdtfModel_PrimitiveType_Sphere			= 3,
			eGdtfModel_PrimitiveType_Base			= 4,
			eGdtfModel_PrimitiveType_Yoke			= 5,
			eGdtfModel_PrimitiveType_Head			= 6,
			eGdtfModel_PrimitiveType_Scanner		= 7,
			eGdtfModel_PrimitiveType_Conventional	= 8,
            eGdtfModel_PrimitiveType_Pigtail        = 9,
		};
		
		enum EGdtfLampType
		{
			eGdtfLampType_Dischange = 0,
			eGdtfLampType_Tungsten = 1,
			eGdtfLampType_Halogen = 2,
			eGdtfLampType_LED = 3,
		};
		
		enum EGdtfBeamType
		{
			eGdtfBeamType_Wash	= 0, // Default
			eGdtfBeamType_Spot  = 1,
			eGdtfBeamType_None  = 2,
		};
		
		enum EGdtfDmxFrequency
		{
			eGdtfDmxFrequency_30	= 0,
			eGdtfDmxFrequency_15	= 1,
			eGdtfDmxFrequency_60	= 2,
			eGdtfDmxFrequency_Slow1 = 3,
			eGdtfDmxFrequency_Slow2 = 4,
			eGdtfDmxFrequency_Slow3 = 5,
		};
		
		enum EGdtfDmxMaster
		{
			eGdtfDmxMaster_None		= 0,
			eGdtfDmxMaster_Grand	= 1,
			eGdtfDmxMaster_Group	= 2,
			
		};
		
		enum EGdtfDmxSnap
		{
			eGdtfDmxMaster_Yes,
			eGdtfDmxMaster_No,
			eGdtfDmxMaster_On,
			eGdtfDmxMaster_Off,
		};
		
		enum EGDTFEncoderInvert
		{
			eGDTFEncoderInvert_No, //Default
			eGDTFEncoderInvert_Yes,
			
		};
		
		enum EGDTFDmxInvert
		{
			eGDTFDmxInvert_No, //Default
			eGDTFDmxInvert_Yes,
			
		};
		
		enum EGdtfDmxRelationType // Default is missing
		{
			eGdtfDmxRelationType_Mode,
			eGdtfDmxRelationType_Multiply,
			eGdtfDmxRelationType_Override,
		};

		enum  EGdtfChannelBitResolution
		{
			// Do not change the values!
			eGdtfChannelBitResolution_8 =  1, 
			eGdtfChannelBitResolution_16 = 2,
			eGdtfChannelBitResolution_24 = 3,
            eGdtfChannelBitResolution_32 = 4,
		};
	}
}

#endif // !1

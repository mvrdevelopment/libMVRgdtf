//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "GDTFManager.h"
#include "XmlFileHelper.h"
#include "CieColor.h"

namespace SceneData
{
    class DYNAMIC_ATTRIBUTE ISceneDataZipBuffer : public IZIPFileIOBuffer
    {
        
    private:
        Uint8*						fpZIPDataBuffer;
        size_t						fZIPDataBufferSize;
        
    public:
        ISceneDataZipBuffer();
        virtual					~ISceneDataZipBuffer();
        
        virtual	VCOMError VCOM_CALLTYPE	GetDataSize(size_t& outSize);
        virtual VCOMError VCOM_CALLTYPE	CopyDataInto(void* pBuffer, size_t bufferSize);
        virtual VCOMError VCOM_CALLTYPE	SetData(void* pBuffer, size_t bufferSize);
        
        VCOMError                       WriteToFile(IFileIdentifierPtr file);
        VCOMError                       GetData(void*& dataPointer);
        
        bool							IsSet();
    };
    
    class DYNAMIC_ATTRIBUTE IXMLFileIOBufferImpl : public IXMLFileIOBuffer
    {
        
    private:
        Uint8*						fXMLBuffer;
        size_t						fXMLBufferSize;
        
    public:
        IXMLFileIOBufferImpl();
        virtual					~IXMLFileIOBufferImpl();
        
        virtual	VCOMError VCOM_CALLTYPE	GetDataSize(size_t& outSize);
        virtual VCOMError VCOM_CALLTYPE	CopyDataInto(void* pBuffer, size_t bufferSize);
        virtual VCOMError VCOM_CALLTYPE	SetData(void* pBuffer, size_t bufferSize);
        VCOMError                       GetData(void*& dataPointer);
        
    };
    
    //------------------------------------------------------------------------------------
	// GdtfFixture Definition
	class GdtfConverter
	{
	public:
        //-----------------------------------------------------------------------------
        // Convert to String functions:
		static TXString	ConvertUUID(const VWFC::Tools::VWUUID& uuid);
		static TXString	ConvertColor(const CCieColor& color);
		static TXString	ConvertDouble(double value);
		static TXString	ConvertInteger(Sint32 value);
        static TXString	ConvertDmxBreak(Sint32 value);
		static TXString	ConvertInteger(size_t value);
		static TXString	ConvertInteger(Sint32 value, bool noneValue);
        static TXString	ConvertIntegerArray (TSint32Array& values);
		static TXString	ConvertDMXAdress(DMXAddress value);
		static TXString	ConvertDMXValue(DmxValue value, EGdtfChannelBitResolution chanlReso, bool noneValue=false);		
		static TXString	ConvertPrimitiveType(EGdtfModel_PrimitiveType value);
		static TXString ConvertMatrix(const VWTransformMatrix& ma, bool fourLines);
		static TXString ConvertRotation(const VWTransformMatrix& ma);
		static TXString	ConvertLampeType(EGdtfLampType value);
		static TXString	ConvertFrequenz(EGdtfDmxFrequency value);
		static TXString	ConvertSnapEnum(EGdtfDmxSnap value);
		static TXString	ConvertMasterEnum(EGdtfDmxMaster value);
		static TXString	ConvertRelationEnum(EGdtfDmxRelationType value);
		static TXString	ConvertPhysicalUnitEnum(EGdtfPhysicalUnit value);
		static TXString	ConvertSpecialAttrEnum(EGdtfSpecial value);
		static TXString ConvertBeamType(EGdtfBeamType value);
		static TXString ConvertDMXInvertEnum(EGDTFDmxInvert value);
		static TXString ConvertEncoderInvertEnum(EGDTFEncoderInvert value);
        static TXString ConvertRDMParamTypeEnum(EGdtf_RDMParam_Type value);
        static TXString Convert_RDMParamDataTypeEnum(EGdtf_RDMParam_DataType value);		
        static TXString Convert_RDMParam_CommandEnum(EGdtf_RDMParam_Command value);
        static TXString Convert_RDMParam_SensorUnitEnum(EGdtf_RDMParam_SensorUnit value);        
        static TXString Convert_RDMParam_SensorUnitPrefixEnum(EGdtf_RDMParam_SensorUnitPrefix value);
        static TXString ConvertEGdtf_RDMValueBool_ValueEnum(EGdtf_RDMValueBool_Value value);
        static TXString ConvertEGdtf_RDMValue_ThresholdOperatorEnum(EGdtf_RDMValue_ThresholdOperator value);		
        static TXString ConvertRDMValue_SENSOR_DEFINITION_TypeEnum(EGdtf_RDMValue_SENSOR_DEFINITION_TYPE value);
        static TXString Convert_RDMValue_LowesHighestDetectionSupportedEnum(EGdtf_RDMValue_LowesHighestDetectionSupported value);
        static TXString Convert_RDMValue_RecordValueSupportedEnum(EGdtf_RDMValue_RecordValueSupported value);
        static TXString ConvertRDMValue_SLOT_INFO_TypeEnum(EGdtf_RDMValue_SLOT_INFO_Type value);
        static TXString ConvertRDMValue_SLOT_INFO_SlotLabelIDEnum(EGdtf_RDMValue_SLOT_INFO_SlotLabelID value);
        //-----------------------------------------------------------------------------
        // Convert from String functions:
        static bool		ConvertUUID(										const TXString& value,			VWFC::Tools::VWUUID& uuid);
        static TXString ConvertEGdtfColorSampleEnum(							  EGdtfColorSample value);
		static bool		ConvertColor(										const TXString& value,			CCieColor& color);
		static bool		ConvertDouble(										const TXString& value,			double& doubleValue);
		static bool		ConvertMatrix(										const TXString& value,			VWTransformMatrix& ma);
		static bool		ConvertRotation(									const TXString& value,			VWTransformMatrix& ma);
		static bool		ConvertPrimitiveType(								const TXString& value,			EGdtfModel_PrimitiveType& type);
		static bool		ConvertLampeType(									const TXString& value,			EGdtfLampType& lampType);
		static bool		ConvertInteger(										const TXString& value,			Sint32&	intValue);
        static bool		ConvertDmxBreak(									const TXString& value,			Sint32&	intValue);
		static bool		ConvertInteger(										const TXString& value,			Sint8& intValue);
		static bool		ConvertInteger(										const TXString& value,			size_t& intValue);
		static bool		ConvertInteger(										const TXString& value,			Sint32&	intValue,						bool& noneValue);
        static bool     ConvertIntegerArray(									  TXString  values,			TSint32Array& intArray);
		static bool		ConvertDMXAdress(									const TXString& value,			DMXAddress& intValue);
		static bool  	ConvertDMXValue(									const TXString& strValue,		EGdtfChannelBitResolution chanlReso,	DmxValue& intValue);
		static bool  	ConvertDMXValue(									const TXString& strValue,		EGdtfChannelBitResolution chanlReso,	DmxValue& intValue, bool& noneValue);
		static bool		ConvertFrequenz(									const TXString& value,			EGdtfDmxFrequency& freq);
		static bool		ConvertRelationEnum(								const TXString& value,			EGdtfDmxRelationType& relation);
		static bool		ConvertSnapEnum(									const TXString& value,			EGdtfDmxSnap& snap);
		static bool		ConvertMasterEnum(									const TXString& value,			EGdtfDmxMaster& master);
		static bool		ConvertPhysicalUnitEnum(							const TXString& value,			EGdtfPhysicalUnit& unit);
		static bool		ConvertSpecialAttrEnum(								const TXString& value,			EGdtfSpecial& special);
		static bool		ConvertBeamType(									const TXString& value,			EGdtfBeamType& type);
		static bool		ConvertDMXInvertEnum(								const TXString& value,			EGDTFDmxInvert&	dmx);
		static bool		ConvertEncoderInvertEnum(							const TXString& value,			EGDTFEncoderInvert&	enc);
        static bool     ConvertRDMParamTypeEnum(							const TXString& value,			EGdtf_RDMParam_Type& val);
        static bool     Convert_RDMParamDataTypeEnum(						const TXString& value,			EGdtf_RDMParam_DataType& val);
        static bool     Convert_RDMParam_CommandEnum(						const TXString& value,			EGdtf_RDMParam_Command&	val);
        static bool     Convert_RDMParam_SensorUnitEnum(					const TXString& value,			EGdtf_RDMParam_SensorUnit& val);
        static bool     Convert_RDMParam_SensorUnitPrefixEnum(				const TXString& value,			EGdtf_RDMParam_SensorUnitPrefix& val);
        static bool     ConvertEGdtf_RDMValueBool_ValueEnum(				const TXString& value,			EGdtf_RDMValueBool_Value& val);
        static bool     ConvertEGdtf_RDMValue_ThresholdOperatorEnum(		const TXString& value,			EGdtf_RDMValue_ThresholdOperator& val);
        static bool     ConvertRDMValue_SENSOR_DEFINITION_TypeEnum(			const TXString& value,			EGdtf_RDMValue_SENSOR_DEFINITION_TYPE& val);
        static bool     Convert_RDMValue_LowesHighestDetectionSupportedEnum(const TXString& value,			EGdtf_RDMValue_LowesHighestDetectionSupported& val);
        static bool     Convert_RDMValue_RecordValueSupportedEnum(			const TXString& value,			EGdtf_RDMValue_RecordValueSupported& val);
        static bool     ConvertRDMValue_SLOT_INFO_TypeEnum(					const TXString& value,			EGdtf_RDMValue_SLOT_INFO_Type& val);
        static bool     ConvertRDMValue_SLOT_INFO_SlotLabelIDEnum(			const TXString& value,			EGdtf_RDMValue_SLOT_INFO_SlotLabelID& val);        
        static bool     ConvertEGdtfColorSampleEnum(						const TXString& inVal,			EGdtfColorSample& outVal);

        static DmxValue GetChannelMaxDmx(const EGdtfChannelBitResolution chanlReso);

		typedef		std::function<void(IXMLFileNodePtr objNode)>	TProcessNodeCall;
		static void		TraverseNodes(IXMLFileNodePtr root, const TXString& childContainerNodeName,const TXString& childNodeName, TProcessNodeCall processNodeFunction);
		
		typedef		std::function<void(IXMLFileNodePtr objNode,const TXString& childNodeName)>	TProcessMultiNodeCall;
		static void		TraverseMultiNodes(IXMLFileNodePtr root, const TXString& childContainerNodeName, TProcessMultiNodeCall processNodeFunction);
		
	private:
		static bool		Deserialize(const TXString& value, std::vector<double>& doubleArr);
		static bool		Deserialize(const TXString& value, TSint32Array& doubleArr);
       

	};
	
	class SceneDataZip
	{
	public:
		static bool AddFileToZip(IZIPFilePtr& zipFile, const IFileIdentifierPtr& file, bool createChecksum, bool deleteFile, bool mustExist = true);
        static void AddFileToZip(IZIPFilePtr& zipFile, ISceneDataZipBuffer& buffer,const TXString &name , bool createChecksum);
		static bool GetFile(const TXString& fileName,const IFolderIdentifierPtr& workingFolder, IFileIdentifierPtr& outFile, bool& hasCheckSum, bool& checksumIsFine, bool checkSumCheck );
	};
}

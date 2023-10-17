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
		static TXString	ConvertDate(const STime& date);
		static TXString	ConvertColor(const CCieColor& color);
		static TXString	ConvertColorArray(TCCieColorArray& colors);
		static TXString	ConvertDouble(double value);
		static TXString	ConvertDoubleArray(TDoubleArray& values, bool includeBrackets);
		static TXString	ConvertInteger(Sint32 value);
#ifdef IS64BIT
		static TXString	ConvertInteger(Uint32 value);
#endif
        static TXString	ConvertDmxBreak(Sint32 value);
		static TXString	ConvertInteger(size_t value);
		static TXString	ConvertInteger(Sint32 value, bool noneValue);
        static TXString	ConvertIntegerArray (TSint32Array& values, bool includeBrackets);
		static TXString	ConvertDMXAdress(DMXAddress value);
		static TXString	ConvertDMXValue(DmxValue value, EGdtfChannelBitResolution chanlReso, bool noneValue=false);		
		static TXString	ConvertPrimitiveType(EGdtfModel_PrimitiveType value);
		static TXString ConvertVector3(const VWPoint3D& value);
		static TXString ConvertMatrix(const VWTransformMatrix& ma, bool fourLines);
		static TXString ConvertRotation(const VWTransformMatrix& ma);
		static TXString	ConvertLampeType(EGdtfLampType value);		
		static TXString	ConvertSnapEnum(EGdtfDmxSnap value);
		static TXString	ConvertMasterEnum(EGdtfDmxMaster value);
		static TXString	ConvertRelationEnum(EGdtfDmxRelationType value);
		static TXString	ConvertPhysicalUnitEnum(EGdtfPhysicalUnit value);
		static TXString	ConvertSpecialAttrEnum(EGdtfSpecial value);
		static TXString ConvertBeamType(EGdtfBeamType value);
        static TXString ConvertEGdtfColorSampleEnum(EGdtfColorSample value);
		static TXString ConvertDmxOffset(DMXAddress coarse, DMXAddress fine, DMXAddress ultra, DMXAddress uber);
        static TXString ConvertEGdtfColorSpace(EGdtfColorSpace value);
        static TXString ConvertEGdtfInterpolationTo(EGdtfInterpolationTo value);
		static TXString	ConvertHexValue(size_t value);
		static TXString	ConvertEGdtfCanHaveChildren(bool value);
		static TXString	Convert2DPoint(double p_X, double p_Y);
		static TXString	ConvertBool(bool value);
		static TXString	ConvertESourceType(GdtfDefines::ESourceType);
		static TXString	ConvertEScaleHandlingType(GdtfDefines::EScaleHandlingType value);
		static TXString	ConvertLaserColorTypeEnum(GdtfDefines::EGdtfLaserColorType value);
		static TXString	ConvertComponentTypeEnum(GdtfDefines::EGdtfComponentType value);
		static TXString	ConvertOrientationEnum(GdtfDefines::EGdtfOrientation value);
		static TXString	ConvertFuseRatingEnum(GdtfDefines::EGdtfFuseRating value);
		static TXString	ConvertStructureTypeEnum(GdtfDefines::EGdtfStructureType value);
		static TXString	ConvertCrossSectionTypeEnum(GdtfDefines::EGdtfCrossSectionType value);
		static TXString	ConvertSupportTypeEnum(GdtfDefines::EGdtfSupportType value);
		static TXString	ConvertSubPhysicalUnitTypeEnum(GdtfDefines::EGdtfSubPhysicalUnitType value);
		

        //-----------------------------------------------------------------------------
        // Convert from String functions:
        static bool		ConvertUUID(					const TXString& value,	MvrUUID& uuid);        
        static bool		ConvertUUID(					const TXString& value, const IXMLFileNodePtr& node,	VWFC::Tools::VWUUID& uuid);        
		static bool		ConvertDate(					const TXString& value, const IXMLFileNodePtr& node,	STime& date);
		static bool		ConvertColor(					const TXString& value, const IXMLFileNodePtr& node,	CCieColor& color);
		static bool		ConvertColorArray(				 	  TXString  values,const IXMLFileNodePtr& node,	TCCieColorArray& colorArray);
		static bool		ConvertDouble(					const TXString& value, const IXMLFileNodePtr& node,	double& doubleValue);
		static bool     ConvertDoubleArray(				  	  TXString  values,const IXMLFileNodePtr& node,	TDoubleArray& doubleArray);
		static bool		ConvertVector3(					const TXString& value, const IXMLFileNodePtr& node,	VWPoint3D& vector);
		static bool		ConvertMatrix(					const TXString& value, const IXMLFileNodePtr& node,	VWTransformMatrix& ma);
		static bool		ConvertRotation(				const TXString& value, const IXMLFileNodePtr& node,	VWTransformMatrix& ma);
		static bool		ConvertPrimitiveType(			const TXString& value, const IXMLFileNodePtr& node,	EGdtfModel_PrimitiveType& type);
		static bool		ConvertLampeType(				const TXString& value, const IXMLFileNodePtr& node,	EGdtfLampType& lampType);
		static bool		ConvertInteger(					const TXString& value, const IXMLFileNodePtr& node,	Sint32&	intValue);
#ifdef IS64BIT
		static bool		ConvertInteger(					const TXString& value, const IXMLFileNodePtr& node,	Uint32&	intValue);
#endif
        static bool		ConvertDmxBreak(				const TXString& value, const IXMLFileNodePtr& node,	Sint32&	intValue);
		static bool		ConvertInteger(					const TXString& value, const IXMLFileNodePtr& node,	Sint8& intValue);
		static bool		ConvertInteger(					const TXString& value, const IXMLFileNodePtr& node,	Uint8& intValue);
		static bool		ConvertInteger(					const TXString& value, const IXMLFileNodePtr& node,	size_t& intValue);
		static bool		ConvertInteger(					const TXString& value, const IXMLFileNodePtr& node,	Sint32&	intValue,						bool& noneValue);
        static bool     ConvertIntegerArray(				  TXString  values,const IXMLFileNodePtr& node,	TSint32Array& intArray);
		static bool		ConvertDMXAdress(				const TXString& value, const IXMLFileNodePtr& node,	DMXAddress& intValue);
		static bool  	ConvertDMXValue(				const TXString& value, const IXMLFileNodePtr& node,	EGdtfChannelBitResolution chanlReso,	DmxValue& intValue);
		static bool  	ConvertDMXValue(				const TXString& value, const IXMLFileNodePtr& node,	EGdtfChannelBitResolution chanlReso,	DmxValue& intValue, bool& noneValue);		
		static bool		ConvertRelationEnum(			const TXString& value, const IXMLFileNodePtr& node,	EGdtfDmxRelationType& relation);
		static bool		ConvertSnapEnum(				const TXString& value, const IXMLFileNodePtr& node,	EGdtfDmxSnap& snap);
		static bool		ConvertMasterEnum(				const TXString& value, const IXMLFileNodePtr& node,	EGdtfDmxMaster& master);
		static bool		ConvertPhysicalUnitEnum(		const TXString& value, const IXMLFileNodePtr& node,	EGdtfPhysicalUnit& unit);
		static bool		ConvertSpecialAttrEnum(			const TXString& value, const IXMLFileNodePtr& node,	EGdtfSpecial& special);
		static bool		ConvertBeamType(				const TXString& value, const IXMLFileNodePtr& node,	EGdtfBeamType& type);
        static bool     ConvertEGdtfColorSampleEnum(	const TXString& inVal, const IXMLFileNodePtr& node,	EGdtfColorSample& outVal);        
        static bool     ConvertEGdtfColorSpace(			const TXString& inVal, const IXMLFileNodePtr& node, EGdtfColorSpace& outVal);
        static bool     ConvertEGdtfInterpolationTo(	const TXString& inVal, const IXMLFileNodePtr& node, EGdtfInterpolationTo& outVal);
		static bool		ConvertHexValue(				const TXString& inVal, const IXMLFileNodePtr& node, size_t& outValue);
		static bool     ConvertEGdtfCanHaveChildren(	const TXString& inVal, const IXMLFileNodePtr& node, bool& outVal);
		static bool     Convert2DPoint(					const TXString& inVal, const IXMLFileNodePtr& node, double& p_X, 							double& p_Y);
		static bool     ConvertBool(					const TXString& inVal, const IXMLFileNodePtr& node, bool& outVal);
		static bool     ConvertESourceType(				const TXString& inVal, const IXMLFileNodePtr& node, GdtfDefines::ESourceType& outVal);
		static bool     ConvertEScaleHandlingType(		const TXString& inVal, const IXMLFileNodePtr& node, GdtfDefines::EScaleHandlingType& outVal);
		static bool     ConvertLaserColorTypeEnum(		const TXString& inVal, const IXMLFileNodePtr& node, GdtfDefines::EGdtfLaserColorType& outVal);
		static bool     ConvertComponentTypeEnum(		const TXString& inVal, const IXMLFileNodePtr& node, GdtfDefines::EGdtfComponentType& outVal);
		static bool     ConvertOrientationEnum(			const TXString& inVal, const IXMLFileNodePtr& node, GdtfDefines::EGdtfOrientation& outVal);
		static bool     ConvertFuseRatingEnum(			const TXString& inVal, const IXMLFileNodePtr& node, GdtfDefines::EGdtfFuseRating& outVal);
		static bool     ConvertStructureTypeEnum(		const TXString& inVal, const IXMLFileNodePtr& node, GdtfDefines::EGdtfStructureType& outVal);
		static bool     ConvertCrossSectionTypeEnum(	const TXString& inVal, const IXMLFileNodePtr& node, GdtfDefines::EGdtfCrossSectionType& outVal);
		static bool     ConvertSupportTypeEnum(			const TXString& inVal, const IXMLFileNodePtr& node, GdtfDefines::EGdtfSupportType& outVal);
		static bool     ConvertSubPhysicalUnitTypeEnum(	const TXString& inVal, const IXMLFileNodePtr& node, GdtfDefines::EGdtfSubPhysicalUnitType& outVal);
		

        static bool 	ConvertDmxOffset(const TXString& inVal, const IXMLFileNodePtr& node, DMXAddress& coarse, DMXAddress& fine, DMXAddress& ultra, DMXAddress& uber);
        //-----------------------------------------------------------------------------
        static CCieColor ConvertCColor (const CieColor& color);
        static CieColor  ConvertCColor (const CCieColor& color);

        static DmxValue GetChannelMaxDmx(const EGdtfChannelBitResolution chanlReso);

		typedef		std::function<void(IXMLFileNodePtr objNode)>	TProcessNodeCall;
		static void		TraverseNodes(IXMLFileNodePtr root, const TXString& childContainerNodeName,const TXString& childNodeName, TProcessNodeCall processNodeFunction);
		
		typedef		std::function<void(IXMLFileNodePtr objNode,const TXString& childNodeName)>	TProcessMultiNodeCall;
		static void		TraverseMultiNodes(IXMLFileNodePtr root, const TXString& childContainerNodeName, TProcessMultiNodeCall processNodeFunction);

		static GdtfDefines::EGdtfPhysicalUnit GetUnitFromSubPhysical(GdtfDefines::EGdtfSubPhysicalUnitType type);
		
	private:
		static bool		Deserialize(const TXString& value, const IXMLFileNodePtr& node, std::vector<double>& doubleArr);
		static bool		Deserialize(const TXString& value, const IXMLFileNodePtr& node, TSint32Array& intArray, TXChar seperator = ',');
		static bool		DeserializeUTC_Date(const TXString& value, const IXMLFileNodePtr& node, TSint32Array& intArray);

        static TXString IntToString2Digits(Sint64 value);


	public:
		// UNIT TEST HELPER
		static bool  	ConvertDMXValue_UnitTest(const char* value, EGdtfChannelBitResolution chanlReso,	DmxValue& intValue);


	};
	
	class SceneDataZip
	{
	public:
		static bool AddFileToZip(IZIPFilePtr& zipFile, const IFileIdentifierPtr& file, ERessourceType resType, bool deleteFile, bool mustExist = true);
        static void AddFileToZip(IZIPFilePtr& zipFile, ISceneDataZipBuffer& buffer,const TXString &name);		

        static TXString GetResourceSubFolder(ERessourceType resType);
	};
}

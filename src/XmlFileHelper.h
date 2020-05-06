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
		static TXString	ConvertDouble(double value);
		static TXString	ConvertDoubleArray(TDoubleArray& values, bool includeBrackets);
		static TXString	ConvertInteger(Sint32 value);
		static TXString	ConvertInteger(Uint32 value);
        static TXString	ConvertDmxBreak(Sint32 value);
		static TXString	ConvertInteger(size_t value);
		static TXString	ConvertInteger(Sint32 value, bool noneValue);
        static TXString	ConvertIntegerArray (TSint32Array& values, bool includeBrackets);
		static TXString	ConvertDMXAdress(DMXAddress value);
		static TXString	ConvertDMXValue(DmxValue value, EGdtfChannelBitResolution chanlReso, bool noneValue=false);		
		static TXString	ConvertPrimitiveType(EGdtfModel_PrimitiveType value);
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
		static TXString	ConvertEGdtfCanHaveChildren(EGdtfCanHaveChildren value);
		static TXString	Convert2DPoint(double p_X, double p_Y);
		static TXString	ConvertBool(bool value);
		static TXString	ConvertESourceType(ESourceType value);
		static TXString	ConvertEScaleHandlingType(EScaleHandlingType value);
		

        //-----------------------------------------------------------------------------
        // Convert from String functions:
        static bool		ConvertUUID(					const TXString& value, const IXMLFileNodePtr& node,	VWFC::Tools::VWUUID& uuid);        
		static bool		ConvertDate(					const TXString& value, const IXMLFileNodePtr& node,	STime& date);
		static bool		ConvertColor(					const TXString& value, const IXMLFileNodePtr& node,	CCieColor& color);
		static bool		ConvertDouble(					const TXString& value, const IXMLFileNodePtr& node,	double& doubleValue);
		static bool     ConvertDoubleArray(				  	  TXString  values,const IXMLFileNodePtr& node,	TDoubleArray& doubleArray);
		static bool		ConvertMatrix(					const TXString& value, const IXMLFileNodePtr& node,	VWTransformMatrix& ma);
		static bool		ConvertRotation(				const TXString& value, const IXMLFileNodePtr& node,	VWTransformMatrix& ma);
		static bool		ConvertPrimitiveType(			const TXString& value, const IXMLFileNodePtr& node,	EGdtfModel_PrimitiveType& type);
		static bool		ConvertLampeType(				const TXString& value, const IXMLFileNodePtr& node,	EGdtfLampType& lampType);
		static bool		ConvertInteger(					const TXString& value, const IXMLFileNodePtr& node,	Sint32&	intValue);
		static bool		ConvertInteger(					const TXString& value, const IXMLFileNodePtr& node,	Uint32&	intValue);
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
		static bool     ConvertEGdtfCanHaveChildren(	const TXString& inVal, const IXMLFileNodePtr& node, EGdtfCanHaveChildren& outVal);
		static bool     Convert2DPoint(					const TXString& inVal, const IXMLFileNodePtr& node, double& p_X, 							double& p_Y);
		static bool     ConvertBool(					const TXString& inVal, const IXMLFileNodePtr& node, bool& outVal);
		static bool     ConvertESourceType(				const TXString& inVal, const IXMLFileNodePtr& node, ESourceType& outVal);
		static bool     ConvertEScaleHandlingType(		const TXString& inVal, const IXMLFileNodePtr& node, EScaleHandlingType& outVal);
		

        static bool 	ConvertDmxOffset(const TXString& inVal, const IXMLFileNodePtr& node, DMXAddress& coarse, DMXAddress& fine, DMXAddress& ultra, DMXAddress& uber);
        //-----------------------------------------------------------------------------
        static CCieColor ConvertCColor (const CieColor& color);
        static CieColor  ConvertCColor (const CCieColor& color);

        static DmxValue GetChannelMaxDmx(const EGdtfChannelBitResolution chanlReso);

		typedef		std::function<void(IXMLFileNodePtr objNode)>	TProcessNodeCall;
		static void		TraverseNodes(IXMLFileNodePtr root, const TXString& childContainerNodeName,const TXString& childNodeName, TProcessNodeCall processNodeFunction);
		
		typedef		std::function<void(IXMLFileNodePtr objNode,const TXString& childNodeName)>	TProcessMultiNodeCall;
		static void		TraverseMultiNodes(IXMLFileNodePtr root, const TXString& childContainerNodeName, TProcessMultiNodeCall processNodeFunction);
		
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

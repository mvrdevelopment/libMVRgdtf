//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------


#include "Prefix/StdAfx.h"

using namespace VWFC;

#include "Prefix/CommonPrefix.h"
#include "SceneDataExchange.h"
#include "GDTFManager.h"
#include "XmlFileHelper.h"
#include "HashManager.h"

using namespace SceneData;

/*static*/ TXString GdtfConverter::ConvertUUID(const UUID& uuid)
{
	// Currenty this is working on strings, but if the see performance issues we could switch to
	// the actual integer operation for this
	
	//------------------------------------------------------
	// This is how Vectorworks prints to string
	// "09E95D97-364C-43d5-8ADF-FF4CE0EC41A7"
	TXString vwUuid = uuid.ToString(false);
	
	// First check if the length is as aspected
	ASSERTN(kEveryone, vwUuid.GetLength() == 36);
	
	//------------------------------------------------------
	// This is how GDTF need the UUID values
	//70 8B CD 59 9E 14 00 00 C1 52 36 54 9A 84 55 B0
	
	TXString outVal;
	
	// Do the mapping
	outVal += vwUuid.GetAt(0);
	outVal += vwUuid.GetAt(1);
	outVal += " ";
	outVal += vwUuid.GetAt(2);
	outVal += vwUuid.GetAt(3);
	outVal += " ";
	outVal += vwUuid.GetAt(4);
	outVal += vwUuid.GetAt(5);
	outVal += " ";
	outVal += vwUuid.GetAt(6);
	outVal += vwUuid.GetAt(7);
	outVal += " ";
	outVal += vwUuid.GetAt(9);	// 8 = "-"
	outVal += vwUuid.GetAt(10);
	outVal += " ";
	outVal += vwUuid.GetAt(11);
	outVal += vwUuid.GetAt(12);
	outVal += " ";
	outVal += vwUuid.GetAt(14);// 13 = "-"
	outVal += vwUuid.GetAt(15);
	outVal += " ";
	outVal += vwUuid.GetAt(16);
	outVal += vwUuid.GetAt(17);
	outVal += " ";
	outVal += vwUuid.GetAt(19);// 18 = "-"
	outVal += vwUuid.GetAt(20);
	outVal += " ";
	outVal += vwUuid.GetAt(21);
	outVal += vwUuid.GetAt(22);
	outVal += " ";
	outVal += vwUuid.GetAt(24);// 23 = "-"
	outVal += vwUuid.GetAt(25);
	outVal += " ";
	outVal += vwUuid.GetAt(26);
	outVal += vwUuid.GetAt(27);
	outVal += " ";
	outVal += vwUuid.GetAt(28);
	outVal += vwUuid.GetAt(29);
	outVal += " ";
	outVal += vwUuid.GetAt(30);
	outVal += vwUuid.GetAt(31);
	outVal +=  " ";
	outVal += vwUuid.GetAt(32);
	outVal += vwUuid.GetAt(33);
	outVal += " ";
	outVal += vwUuid.GetAt(34);
	outVal += vwUuid.GetAt(35);
	
	// Just check if this was aspected
	ASSERTN(kEveryone, outVal.GetLength() == 47);
	
	return outVal;
	
}

/*static*/ bool GdtfConverter::ConvertUUID(const TXString& inValue, UUID& uuid)
{
	// First check if theinValuelength is as aspected
	ASSERTN(kEveryone, inValue.GetLength() == 47);
	if (inValue.GetLength() != 47)	{ return false; }
	
	// Remove white space
	TXString value = inValue;
	value.Replace(" ", "");
	
	TXString uuidForRead (38);
	
	uuidForRead[0] = '{';
	uuidForRead[1] = value[0];
	uuidForRead[2] = value[1];
	uuidForRead[3] = value[2];
	uuidForRead[4] = value[3];
	uuidForRead[5] = value[4];
	uuidForRead[6] = value[5];
	uuidForRead[7] = value[6];
	uuidForRead[8] = value[7];
	uuidForRead[9] = '-';
	uuidForRead[10] = value[8];
	uuidForRead[11] = value[9];
	uuidForRead[12] = value[10];
	uuidForRead[13] = value[11];
	uuidForRead[14] = '-';
	uuidForRead[15] = value[12];
	uuidForRead[16] = value[13];
	uuidForRead[17] = value[14];
	uuidForRead[18] = value[15];
	uuidForRead[19] = '-';
	uuidForRead[20] = value[16];
	uuidForRead[21] = value[17];
	uuidForRead[22] = value[18];
	uuidForRead[23] = value[19];
	uuidForRead[24] = '-';
	uuidForRead[25] = value[20];
	uuidForRead[26] = value[21];
	uuidForRead[27] = value[22];
	uuidForRead[28] = value[23];
	uuidForRead[29] = value[24];
	uuidForRead[30] = value[25];
	uuidForRead[31] = value[26];
	uuidForRead[32] = value[27];
	uuidForRead[33] = value[28];
	uuidForRead[34] = value[29];
	uuidForRead[35] = value[30];
	uuidForRead[36] = value[31];
	uuidForRead[37] = '}';
	
	uuid = UUID(uuidForRead);
	
	return true;
	
}

/*static*/ TXString GdtfConverter::ConvertColor(const CCieColor& color)
{
	return (TXString() << color.Get_x() << "," << color.Get_y() << "," << color.Get_Y_luminance() );
}

/*static*/ bool GdtfConverter::ConvertColor(const TXString& value, CCieColor& color)
{
	// ------------------------------------------------------------
	// Check if the string is empty, use the default color
	if (value.IsEmpty()) { color = CCieColor(); return true; }
	
	// ------------------------------------------------------------
	// Split string
	TXString strVal = value;
	
	// Prepare Array
	std::vector<double> d_arr;
	
	Deserialize(strVal, d_arr);
	
	
	// ------------------------------------------------------------
	// Check if you have three valies
	ASSERTN(kEveryone, d_arr.size() == 3);
	if (d_arr.size() != 3) { color = CCieColor(); return false; }
	
	
	// Set Out Color and return true
	color = CCieColor(d_arr[0],d_arr[1],d_arr[2]);
	
	return true;
}

/*static*/ TXString GdtfConverter::ConvertDouble(double value)
{
	TXString valueStr;
	valueStr << value;
	return valueStr;
}

/*static*/ bool GdtfConverter::ConvertDouble(const TXString& value, double& doubleValue)
{
	// Try to convert
	doubleValue = value.atof();
	
	// Return ig the casting was good
	return true;
}

/*static*/ TXString GdtfConverter::ConvertInteger(Sint32 value)
{
	TXString valueStr;
	valueStr << value;
	return valueStr;
}



/*static*/ bool GdtfConverter::ConvertInteger(const TXString& value, Sint8& intValue)
{
	intValue = value.atoi();
	
	return true;
}

/*static*/ bool GdtfConverter::ConvertInteger(const TXString& value, size_t& intValue)
{
	intValue = value.atoi();
	
	return true;
}

/*static*/ bool GdtfConverter::ConvertInteger(const TXString& value, Sint32& intValue)
{
	intValue = value.atoi();
	
	return true;
}

TXString SceneData::GdtfConverter::ConvertDMXValue(DmxValue value, EGdtfChannelBitResolution chanlReso, bool noneValue)
/* Convert DmxValue to String */
{
	// Return None if it is the none value
	if (noneValue) { return XML_GDTF_DMXFChannel_NONEVALUE; }
	
	// Otherwise convert and return the value
	TXString dmxValueStr;
	
	dmxValueStr << TXString().itoa(value) << "/" << TXString().itoa( (Sint64)chanlReso);

	return dmxValueStr; 
}

/*static*/ TXString GdtfConverter::ConvertInteger(Sint32 value, bool noneValue)
{
	// Return None if it is the none value
	if (noneValue)		{ return XML_GDTF_DMXFChannel_NONEVALUE; }
	
	// Otherwise return the value
	TXString valueStr;
	valueStr << value;
	return valueStr;
}

/*static*/ TXString GdtfConverter::ConvertInteger(size_t value)
{	
	// Otherwise return the value
	TXString valueStr;
	valueStr << value;
	return valueStr;
}

TXString SceneData::GdtfConverter::ConvertDMXAdress(DMXAddress value)
/* Convert DMXAdress to String */
{
	/* Absolute DMX address (size 4 bytes); 
	  Alternative format: Universe � integer universe number, starting with 1;  XXX check this
	  Address: address within universe from 1 to 512. Format: integer */
	
	return ConvertInteger(value);
}

/*static*/ bool GdtfConverter::ConvertInteger(const TXString& value, Sint32& intValue, bool& noneValue)
{
	noneValue = false;
	
	if (value == XML_GDTF_DMXFChannel_NONEVALUE)		{ noneValue = true; intValue = 0; return true; ; }
	
	return ConvertInteger(value, intValue);;
}

bool SceneData::GdtfConverter::ConvertDMXAdress(const TXString& value, DMXAddress & intValue)
/* Convert String to DMXAdress*/
{
	/* Absolute DMX address (size 4 bytes); 
	  Alternative format: Universe � integer universe number, starting with 1;  XXX check this
	  Address: address within universe from 1 to 512. Format: integer */
	
	return ConvertInteger(value, intValue);
}

bool SplitStr(const TXString& str, TXString& part1, TXString& part2, size_t splitPos, bool includeSplitPos=false)
/*
	Split the provided string into 2 seperate string at splitPos.
	If includeSplitPos is true the part1 will include the char at splitPos.

	Returns the succes of the operation.
*/
{
	size_t strLen = str.GetLength();

	if (strLen <= splitPos)  { return false; }

	part1 = "";
	part2 = "";

	// First Part
	for (size_t i = 0; i < splitPos; i++)
	{
		part1 << str.GetAt(i);
	}

	// 2nd Part: Start at Split pos + 1 to exclude the spilt char from the result.
	size_t start2ndPart = 0;

	if (includeSplitPos) { start2ndPart = splitPos; }
	else				 { start2ndPart = splitPos + 1; }

	for (size_t i = start2ndPart; i < strLen; i++)	{ part2 << str.GetAt(i); }
	
	return true;
}

bool SceneData::GdtfConverter::ConvertDMXValue(const TXString& strValue, EGdtfChannelBitResolution chanlReso, DmxValue & intValue)
/* Converts a string to a DmxValue. returns succes of the opeation as bool (XXX this is always true at the moment.)*/
{
	// Split the String ("ValRaw/bytetSpecifier")
	TXString firstPart;
	TXString secndPart;

	// Find first entry
	ptrdiff_t splitPos = strValue.Find("/");
	
	SplitStr(strValue, firstPart, secndPart, (size_t)splitPos);
	//-----------------------------------------------------------------------------------
	
	Sint32 dmxValueRaw    = firstPart.atoi();
	Sint32 bytetSpecifier = secndPart.atoi();

	// Check if the ByteSpecifier is different to the ChannelResolution.
	if (bytetSpecifier != chanlReso) 
	{
        switch (chanlReso) 
        {
		    // The Value needs to be scaled depending on the ChannelResolution.
            case eGdtfChannelBitResolution_8:
		    {
                switch (bytetSpecifier)
                {                
			        // (No need to check eGdtfChannelBitResolution_8 here.)
                    case eGdtfChannelBitResolution_16:
			        {			
				        intValue = dmxValueRaw * 256; break;
			        }
                    case eGdtfChannelBitResolution_24:
			        {
				        intValue = dmxValueRaw * 256 * 256; break;
			        }	
                    case eGdtfChannelBitResolution_32:
			        {			
				        intValue = dmxValueRaw * 256 * 256 * 256; break;
			        }                    
                }
                break;
		    }
            case eGdtfChannelBitResolution_16:
		    {
                switch (bytetSpecifier)
                {

                    case eGdtfChannelBitResolution_8:
                    {
                        intValue = dmxValueRaw / 256; break;
                    }
                    // /No need to check eGdtfChannelBitResolution_16 here.)
                    case eGdtfChannelBitResolution_24:
                    {
                        intValue = dmxValueRaw * 256; break;
                    }
                    case eGdtfChannelBitResolution_32:
                    {
                        intValue = dmxValueRaw * 256 * 256; break;
                    }
                }
                break;
		    }	
            case eGdtfChannelBitResolution_24:
		    {
                switch (bytetSpecifier)
                {
                    case eGdtfChannelBitResolution_8:
                    {
                        intValue = dmxValueRaw / 256 / 256; break;
                    }
                    case eGdtfChannelBitResolution_16:
                    {
                        intValue = dmxValueRaw / 256; break;
                    }
                    // (No need to check eGdtfChannelBitResolution_24 here.)
                    case eGdtfChannelBitResolution_32:
                    {
                        intValue = dmxValueRaw * 256; break;
                    }                
                }
                break;
		    }
            case eGdtfChannelBitResolution_32:
            {
                switch (bytetSpecifier)
                {
                    case eGdtfChannelBitResolution_8:
                    {
                        intValue = dmxValueRaw / 256 / 256 / 256; break;
                    }
                    case eGdtfChannelBitResolution_16:
                    {
                        intValue = dmxValueRaw / 256 / 256; break;
                    }
                    case eGdtfChannelBitResolution_24:
                    {
                        intValue = dmxValueRaw / 256; break;
                    }
                    // (No need to check eGdtfChannelBitResolution_32 here.)                    
                }
                break;
            }
        }
	}	
	else
	{
	    // We can take the value as it is defined in the document without scaling it to another BitResolution.
		intValue = dmxValueRaw; 
	}

	return true;
}

bool SceneData::GdtfConverter::ConvertDMXValue(const TXString & strValue, EGdtfChannelBitResolution chanlReso, DmxValue & intValue, bool & noneValue)
/* Converts a string to a DmxValue */
{	
	noneValue = false; 

	if (strValue == XML_GDTF_DMXFChannel_NONEVALUE) 
	{
		noneValue = true; 
		return true;
	}

	ConvertDMXValue(strValue, chanlReso, intValue);

	return true;
}

/*static*/ TXString GdtfConverter::ConvertPrimitiveType(EGdtfModel_PrimitiveType value)
{
	switch (value)
	{
		case eGdtfModel_PrimitiveType_Cube:			return XML_GDTF_PrimitiveTypeEnum_Cube;
		case eGdtfModel_PrimitiveType_Sphere:		return XML_GDTF_PrimitiveTypeEnum_Sphere;
		case eGdtfModel_PrimitiveType_Cylinder:		return XML_GDTF_PrimitiveTypeEnum_Cylinder;
		case eGdtfModel_PrimitiveType_Undefined:	return XML_GDTF_PrimitiveTypeEnum_Undefined;
		case eGdtfModel_PrimitiveType_Base:			return XML_GDTF_PrimitiveTypeEnum_Base;
		case eGdtfModel_PrimitiveType_Head:			return XML_GDTF_PrimitiveTypeEnum_Head;
		case eGdtfModel_PrimitiveType_Yoke:			return XML_GDTF_PrimitiveTypeEnum_Yoke;
		case eGdtfModel_PrimitiveType_Scanner:		return XML_GDTF_PrimitiveTypeEnum_Scanner;
		case eGdtfModel_PrimitiveType_Conventional:	return XML_GDTF_PrimitiveTypeEnum_Conventional;
        case eGdtfModel_PrimitiveType_Pigtail:      return XML_GDTF_PrimitiveTypeEnum_Pigtail;			
	}
	
	// Make Assert
	ASSERTN(kEveryone,	value == eGdtfModel_PrimitiveType_Cube ||
						value == eGdtfModel_PrimitiveType_Sphere ||
						value == eGdtfModel_PrimitiveType_Undefined ||
						value == eGdtfModel_PrimitiveType_Base ||
						value == eGdtfModel_PrimitiveType_Head ||
						value == eGdtfModel_PrimitiveType_Yoke ||
						value == eGdtfModel_PrimitiveType_Scanner ||
						value == eGdtfModel_PrimitiveType_Conventional ||
                        value == eGdtfModel_PrimitiveType_Pigtail);
	
	// Return default value
	return XML_GDTF_PrimitiveTypeEnum_Undefined;
}


/*static*/ bool GdtfConverter::ConvertPrimitiveType(const TXString& value, EGdtfModel_PrimitiveType& type)
{
	if		(value == XML_GDTF_PrimitiveTypeEnum_Cube)			{ type = eGdtfModel_PrimitiveType_Cube;		}
	else if (value == XML_GDTF_PrimitiveTypeEnum_Sphere)		{ type = eGdtfModel_PrimitiveType_Sphere;	}
	else if (value == XML_GDTF_PrimitiveTypeEnum_Cylinder)		{ type = eGdtfModel_PrimitiveType_Cylinder;	}
	else if (value == XML_GDTF_PrimitiveTypeEnum_Base)			{ type = eGdtfModel_PrimitiveType_Base;	}
	else if (value == XML_GDTF_PrimitiveTypeEnum_Head)			{ type = eGdtfModel_PrimitiveType_Head;	}
	else if (value == XML_GDTF_PrimitiveTypeEnum_Yoke)			{ type = eGdtfModel_PrimitiveType_Yoke;	}
	else if (value == XML_GDTF_PrimitiveTypeEnum_Scanner)		{ type = eGdtfModel_PrimitiveType_Scanner;	}
	else if (value == XML_GDTF_PrimitiveTypeEnum_Conventional)	{ type = eGdtfModel_PrimitiveType_Conventional;	}
	else if (value == XML_GDTF_PrimitiveTypeEnum_Undefined)		{ type = eGdtfModel_PrimitiveType_Undefined; }
    else if (value == XML_GDTF_PrimitiveTypeEnum_Pigtail)		{ type = eGdtfModel_PrimitiveType_Pigtail; }
	else if (value == "")										{ type = eGdtfModel_PrimitiveType_Undefined; }
	else														{ type = eGdtfModel_PrimitiveType_Undefined; DSTOP((kEveryone, "Unaspected Input for Primitive Type Enum"));}
	
	// Return true
	return true;
}

/*static*/ TXString GdtfConverter::ConvertSpecialAttrEnum(EGdtfSpecial value)
{
	switch (value)
	{
		case EGdtfSpecial::None:		return XML_GDTFPhysicalUnitEnum_None;
		case EGdtfSpecial::Dimmer:		return XML_EGdtfSpecialEnum_Dimmer;
		case EGdtfSpecial::Pan:			return XML_EGdtfSpecialEnum_Pan;
		case EGdtfSpecial::Tilt:		return XML_EGdtfSpecialEnum_Tilt;
		case EGdtfSpecial::X:			return XML_EGdtfSpecialEnum_X;
		case EGdtfSpecial::Y:			return XML_EGdtfSpecialEnum_Y;
		case EGdtfSpecial::Z:			return XML_EGdtfSpecialEnum_Z;
		case EGdtfSpecial::RGB:			return XML_EGdtfSpecialEnum_RGB;
		case EGdtfSpecial::Hue:			return XML_EGdtfSpecialEnum_Hue;
		case EGdtfSpecial::Saturation:	return XML_EGdtfSpecialEnum_Saturation;
		case EGdtfSpecial::Brightness:	return XML_EGdtfSpecialEnum_Brightness;
		case EGdtfSpecial::ColorWheel:	return XML_EGdtfSpecialEnum_ColorWheel;
		case EGdtfSpecial::Focus:		return XML_EGdtfSpecialEnum_Focus;
		case EGdtfSpecial::Zoom:		return XML_EGdtfSpecialEnum_Zoom;
		case EGdtfSpecial::Dummy:		return XML_EGdtfSpecialEnum_Dummy;
			
		default: DSTOP((kEveryone,"EGdtfSpecial enum is not implemented!"));
			
			
	}
	
	// Return default value
	return XML_GDTFPhysicalUnitEnum_None;
}

/*static*/ bool GdtfConverter::ConvertSpecialAttrEnum(const TXString& value, EGdtfSpecial& special)
{
	if		(value == XML_GDTFPhysicalUnitEnum_None)	{ special = EGdtfSpecial::None;			}
	else if (value == XML_EGdtfSpecialEnum_Dimmer)		{ special = EGdtfSpecial::Dimmer;		}
	else if (value == XML_EGdtfSpecialEnum_Pan)			{ special = EGdtfSpecial::Pan;			}
	else if (value == XML_EGdtfSpecialEnum_Tilt)		{ special = EGdtfSpecial::Tilt;			}
	else if (value == XML_EGdtfSpecialEnum_X)			{ special = EGdtfSpecial::X;			}
	else if (value == XML_EGdtfSpecialEnum_Y)			{ special = EGdtfSpecial::Y;			}
	else if (value == XML_EGdtfSpecialEnum_Z)			{ special = EGdtfSpecial::Z;			}
	else if (value == XML_EGdtfSpecialEnum_RGB)			{ special = EGdtfSpecial::RGB;			}
	else if (value == XML_EGdtfSpecialEnum_Hue)			{ special = EGdtfSpecial::Hue;			}
	else if (value == XML_EGdtfSpecialEnum_Saturation)	{ special = EGdtfSpecial::Saturation;	}
	else if (value == XML_EGdtfSpecialEnum_Brightness)	{ special = EGdtfSpecial::Brightness;	}
	else if (value == XML_EGdtfSpecialEnum_ColorWheel)	{ special = EGdtfSpecial::ColorWheel;	}
	else if (value == XML_EGdtfSpecialEnum_Focus)		{ special = EGdtfSpecial::Focus;		}
	else if (value == XML_EGdtfSpecialEnum_Zoom)		{ special = EGdtfSpecial::Zoom;			}
	else if (value == XML_EGdtfSpecialEnum_Dummy)		{ special = EGdtfSpecial::Dummy;		}
	else if (value == "")								{ special = EGdtfSpecial::None; }
	else												{ special = EGdtfSpecial::None; DSTOP((kEveryone, "Unaspected Input for EGdtfSpecial Enum"));}
	
	// Return true
	return true;
}

/*static*/ TXString GdtfConverter::ConvertPhysicalUnitEnum(EGdtfPhysicalUnit value)
{
	switch (value)
	{
		case EGdtfPhysicalUnit::None:					return XML_GDTFPhysicalUnitEnum_None;
		case EGdtfPhysicalUnit::Percent:				return XML_GDTFPhysicalUnitEnum_Percent;
		case EGdtfPhysicalUnit::Length:					return XML_GDTFPhysicalUnitEnum_Length;
		case EGdtfPhysicalUnit::Mass:					return XML_GDTFPhysicalUnitEnum_Mass;
		case EGdtfPhysicalUnit::Time:					return XML_GDTFPhysicalUnitEnum_Time;
		case EGdtfPhysicalUnit::Temperatur:				return XML_GDTFPhysicalUnitEnum_Temperatur;
		case EGdtfPhysicalUnit::LuminousItensity:		return XML_GDTFPhysicalUnitEnum_LuminousItensity;
		case EGdtfPhysicalUnit::Angle:					return XML_GDTFPhysicalUnitEnum_Angle;
		case EGdtfPhysicalUnit::Force:					return XML_GDTFPhysicalUnitEnum_Force;
		case EGdtfPhysicalUnit::Frequeny:				return XML_GDTFPhysicalUnitEnum_Frequeny;
		case EGdtfPhysicalUnit::Current:				return XML_GDTFPhysicalUnitEnum_Current;
		case EGdtfPhysicalUnit::Voltage:				return XML_GDTFPhysicalUnitEnum_Voltage;
		case EGdtfPhysicalUnit::Power:					return XML_GDTFPhysicalUnitEnum_Power;
		case EGdtfPhysicalUnit::Energy:					return XML_GDTFPhysicalUnitEnum_Energy;
		case EGdtfPhysicalUnit::Area:					return XML_GDTFPhysicalUnitEnum_Area;
		case EGdtfPhysicalUnit::Volume:					return XML_GDTFPhysicalUnitEnum_Volume;
		case EGdtfPhysicalUnit::Speed:					return XML_GDTFPhysicalUnitEnum_Speed;
		case EGdtfPhysicalUnit::Acceleration:			return XML_GDTFPhysicalUnitEnum_Acceleration;
		case EGdtfPhysicalUnit::AngularSpeed:			return XML_GDTFPhysicalUnitEnum_AngularSpeed;
		case EGdtfPhysicalUnit::AngularAccc:			return XML_GDTFPhysicalUnitEnum_AngularAccc;
		case EGdtfPhysicalUnit::WaveLength:				return XML_GDTFPhysicalUnitEnum_WaveLength;
		case EGdtfPhysicalUnit::ColorComponent:			return XML_GDTFPhysicalUnitEnum_ColorComponent;

		default: DSTOP((kEveryone,"This enum for EGdtfPhysicalUnit was not implemented!"));
	}
	
	// Return default value
	return XML_GDTFPhysicalUnitEnum_None;
}

/*static*/ bool GdtfConverter::ConvertPhysicalUnitEnum(const TXString& value, EGdtfPhysicalUnit& unit)
{
	if		(value == XML_GDTFPhysicalUnitEnum_None)			{ unit = EGdtfPhysicalUnit::None;			 }
	else if (value == XML_GDTFPhysicalUnitEnum_Percent)			{ unit = EGdtfPhysicalUnit::Percent;		 }
	else if (value == XML_GDTFPhysicalUnitEnum_Length)			{ unit = EGdtfPhysicalUnit::Length;		 	 }
	else if (value == XML_GDTFPhysicalUnitEnum_Mass)			{ unit = EGdtfPhysicalUnit::Mass;			 }
	else if (value == XML_GDTFPhysicalUnitEnum_Time)			{ unit = EGdtfPhysicalUnit::Time;			 }
	else if (value == XML_GDTFPhysicalUnitEnum_Temperatur)		{ unit = EGdtfPhysicalUnit::Temperatur;		 }
	else if (value == XML_GDTFPhysicalUnitEnum_LuminousItensity){ unit = EGdtfPhysicalUnit::LuminousItensity;}
	else if (value == XML_GDTFPhysicalUnitEnum_Angle)			{ unit = EGdtfPhysicalUnit::Angle;			 }
	else if (value == XML_GDTFPhysicalUnitEnum_Force)			{ unit = EGdtfPhysicalUnit::Force;			 }
	else if (value == XML_GDTFPhysicalUnitEnum_Frequeny)		{ unit = EGdtfPhysicalUnit::Frequeny;		 }
	else if (value == XML_GDTFPhysicalUnitEnum_Current)			{ unit = EGdtfPhysicalUnit::Current;		 }
	else if (value == XML_GDTFPhysicalUnitEnum_Voltage)			{ unit = EGdtfPhysicalUnit::Voltage;		 }
	else if (value == XML_GDTFPhysicalUnitEnum_Power)			{ unit = EGdtfPhysicalUnit::Power;			 }
	else if (value == XML_GDTFPhysicalUnitEnum_Energy)			{ unit = EGdtfPhysicalUnit::Energy;			 }
	else if (value == XML_GDTFPhysicalUnitEnum_Area)			{ unit = EGdtfPhysicalUnit::Area;			 }
	else if (value == XML_GDTFPhysicalUnitEnum_Volume)			{ unit = EGdtfPhysicalUnit::Volume;			 }
	else if (value == XML_GDTFPhysicalUnitEnum_Speed)			{ unit = EGdtfPhysicalUnit::Speed;			 }
	else if (value == XML_GDTFPhysicalUnitEnum_Acceleration)	{ unit = EGdtfPhysicalUnit::Acceleration;	 }
	else if (value == XML_GDTFPhysicalUnitEnum_AngularSpeed)	{ unit = EGdtfPhysicalUnit::AngularSpeed;	 }
	else if (value == XML_GDTFPhysicalUnitEnum_AngularAccc)		{ unit = EGdtfPhysicalUnit::AngularAccc;	 }
	else if (value == XML_GDTFPhysicalUnitEnum_WaveLength)		{ unit = EGdtfPhysicalUnit::WaveLength;		 }
	else if (value == XML_GDTFPhysicalUnitEnum_ColorComponent)	{ unit = EGdtfPhysicalUnit::ColorComponent;	 }
	else if (value == "")										{ unit = EGdtfPhysicalUnit::None;			 }
	else														{ unit = EGdtfPhysicalUnit::None; DSTOP((kEveryone, "Unaspected Input for EGdtfPhysicalUnit Enum"));}
	
	// Return true
	return true;
}
/*static*/ bool GdtfConverter::ConvertBeamType(const TXString& value, EGdtfBeamType& unit)
{
	if		(value == XML_GDTF_BeamTypeEnum_Wash)			{ unit = EGdtfBeamType::eGdtfBeamType_Wash;		 }
	else if (value == XML_GDTF_BeamTypeEnum_Spot)			{ unit = EGdtfBeamType::eGdtfBeamType_Spot;		 }
	else if (value == XML_GDTF_BeamTypeEnum_None)			{ unit = EGdtfBeamType::eGdtfBeamType_None;		 }
	else if (value == "")									{ unit = EGdtfBeamType::eGdtfBeamType_Wash;		 }
	else													{ unit = EGdtfBeamType::eGdtfBeamType_Wash; DSTOP((kEveryone, "Unaspected Input for EGdtfBeamType Enum"));}
	
	// Return true
	return true;
}

/*static*/ TXString GdtfConverter::ConvertBeamType(EGdtfBeamType value)
{
	switch (value)
	{
		case eGdtfBeamType_None: return XML_GDTF_BeamTypeEnum_None;
		case eGdtfBeamType_Spot: return XML_GDTF_BeamTypeEnum_Spot;
		case eGdtfBeamType_Wash: return XML_GDTF_BeamTypeEnum_Wash;
			
		default: DSTOP((kEveryone,"This enum for EGdtfBeamType was not implemented!")); break;
	}
	
	// Return true
	return XML_GDTF_BeamTypeEnum_Wash;
}


/*static*/ TXString GdtfConverter::ConvertMatrix(const VWTransformMatrix& ma)
{
	TXString value;
	value << "{" << ma.GetUVector().x  << "," << ma.GetUVector().y << "," << ma.GetUVector().z << "}";
	value << "{" << ma.GetVVector().x  << "," << ma.GetVVector().y << "," << ma.GetVVector().z << "}";
	value << "{" << ma.GetWVector().x  << "," << ma.GetWVector().y << "," << ma.GetWVector().z << "}";
	value << "{" << ma.GetOffset().x   << "," << ma.GetOffset().y  << "," << ma.GetOffset().z  << "}";
	
	
	return value;
}

/*static*/ bool GdtfConverter::ConvertMatrix(const TXString& value, VWTransformMatrix& matrix)
{
	// ----------------------------------------------------------------
	// If the String is empty, use the DefaultMaterix
	if (value.IsEmpty()) { matrix = VWTransformMatrix(); return true; }
	
	
	// ----------------------------------------------------------------
	// Split string
	TXString strVal = value;
	
	
	// ----------------------------------------------------------------
	// Delete first element
	ASSERTN(kEveryone, strVal.GetAt(0) == '{');
	if (strVal.GetAt(0) == '{')		{ strVal.Delete(0,1); }
	
	// Delete last element
	ASSERTN(kEveryone, strVal.GetLast() == '}');
	if (strVal.GetLast() == '}')	{ strVal.DeleteLast(); }
	
	// ----------------------------------------------------------------
	// Split into parts
	std::vector<TXString> lines;
	ptrdiff_t pos = strVal.Find("}{");
	while (pos > 0 )
	{
		// Copy string
		TXString strValInner;
		for (ptrdiff_t i = 0; i < pos; i++)	{ strValInner += strVal.GetAt(i); }
		
		// Try to cast
		lines.push_back(strValInner);
		
		// Delete and find next
		strVal.Delete(0, pos + 2);
		pos = strVal.Find("}{");
	}
	
	// Apped the rest
	lines.push_back(strVal);

	if (lines.size() != 4)
	{
		DSTOP((kEveryone,"Failed to split the Matrix into vertices"));
		return false;
	}
	
	// ----------------------------------------------------------------
	// Do the conversion
	for (size_t i = 0; i < lines.size(); i++)
	{
		std::vector<double> arr;
		Deserialize(lines.at(i), arr);
		
		// Use this for 4x4 matrix and 4x3 matrix
		if (arr.size() < 3 || arr.size() > 4)
		{
			DSTOP((kEveryone, "Failed to seserialize string"));
			continue;
		}
		
		// ----------------------------------------------------------------
		// Set the matrix
		matrix.fMatrix.mat[i][0] = arr [0];
		matrix.fMatrix.mat[i][1] = arr [1];
		matrix.fMatrix.mat[i][2] = arr [2];

	}

	
	return true;
}

/*static*/ TXString GdtfConverter::ConvertRotation(const VWTransformMatrix& ma)
{
	TXString value;
	value << "{" << ma.GetUVector().x  << "," << ma.GetUVector().y << "," << ma.GetUVector().z << "}";
	value << "{" << ma.GetVVector().x  << "," << ma.GetVVector().y << "," << ma.GetVVector().z << "}";
	value << "{" << ma.GetWVector().x  << "," << ma.GetWVector().y << "," << ma.GetWVector().z << "}";
	
	return value;
}

/*static*/ bool GdtfConverter::ConvertRotation(const TXString& value, VWTransformMatrix& matrix)
{
	// ----------------------------------------------------------------
	// Split string
	TXString strVal = value;
	
	
	// ----------------------------------------------------------------
	// Delete first element
	ASSERTN(kEveryone, strVal.GetAt(0) == '{');
	if (strVal.GetAt(0) == '{')		{ strVal.Delete(0,1); }
	
	
	// Delete second last element
	ASSERTN(kEveryone, strVal.GetLast() == '}');
	if (strVal.GetLast() == '}')	{ strVal.DeleteLast(); }
	
	// ----------------------------------------------------------------
	// Split into parts
	TXStringArray lines;
	ptrdiff_t pos = strVal.Find("}{");
	while (pos > 0 )
	{
		// Copy string
		TXString strValInner;
		for (ptrdiff_t i = 0; i < pos; i++)	{ strValInner << strVal.GetAt(i); }
		
		// Try to cast
		lines.Append(strValInner);
		
		// Delete and find next
		strVal.Delete(0, pos + 2);
		pos = strVal.Find("}{");
	}
	
	// Apped the rest
	lines.Append(strVal);
	
	if (lines.GetSize() != 3)
	{
		DSTOP((kEveryone,"Failed to split the Matrix into vertices"));
		return false;
	}
	
	// ----------------------------------------------------------------
	// Do the conversion
	for (size_t i = 0; i < lines.GetSize(); i++)
	{
		std::vector<double> arr;
		Deserialize(lines.GetAt(i), arr);
		
		if (arr.size() != 3)
		{
			DSTOP((kEveryone, "Failed to seserialize string"));
			continue;
		}
		
		// ----------------------------------------------------------------
		// Set the matrix
		matrix.fMatrix.mat[i][0] = arr [0];
		matrix.fMatrix.mat[i][1] = arr [1];
		matrix.fMatrix.mat[i][2] = arr [2];
		
	}
	
	
	return true;
}

/*static*/ TXString GdtfConverter::ConvertLampeType(EGdtfLampType value)
{
	switch (value)
	{
		case eGdtfLampType_LED:			return XML_GDTF_LampTypeEnum_Discharge;
		case eGdtfLampType_Halogen:		return XML_GDTF_LampTypeEnum_Halogen;
		case eGdtfLampType_Tungsten:	return XML_GDTF_LampTypeEnum_Tungsten;
		case eGdtfLampType_Dischange:	return XML_GDTF_LampTypeEnum_LED;
			
			
	}
	
	// Make Assert
	ASSERTN(kEveryone,	value == eGdtfLampType_LED ||
			value == eGdtfLampType_Halogen ||
			value == eGdtfLampType_Tungsten ||
			value == eGdtfLampType_Dischange);
	
	// Return default value
	return XML_GDTF_LampTypeEnum_Discharge;
}

/*static*/ bool GdtfConverter::ConvertLampeType(const TXString& value, EGdtfLampType& lampType)
{
	if		(value == XML_GDTF_LampTypeEnum_Discharge)	{ lampType = eGdtfLampType_Dischange;	}
	else if (value == XML_GDTF_LampTypeEnum_Halogen)	{ lampType = eGdtfLampType_Halogen;		}
	else if (value == XML_GDTF_LampTypeEnum_Tungsten)	{ lampType = eGdtfLampType_Tungsten;	}
	else if (value == XML_GDTF_LampTypeEnum_LED)		{ lampType = eGdtfLampType_LED;			}
	else if (value == "")								{ lampType = eGdtfLampType_Dischange;	}
	else												{ lampType = eGdtfLampType_Dischange; DSTOP((kEveryone, "Unaspected Input for Lamp Type Enum"));}
	
	// Return true
	return true;
}

/*static*/ TXString GdtfConverter::ConvertFrequenz(EGdtfDmxFrequency value)
{
	switch (value)
	{
		case eGdtfDmxFrequency_60:		return XML_GDTF_DMXFrequencyEnum_60;
		case eGdtfDmxFrequency_15:		return XML_GDTF_DMXFrequencyEnum_15;
		case eGdtfDmxFrequency_30:		return XML_GDTF_DMXFrequencyEnum_30;
		case eGdtfDmxFrequency_Slow1:	return XML_GDTF_DMXFrequencyEnum_Slow1;
		case eGdtfDmxFrequency_Slow2:	return XML_GDTF_DMXFrequencyEnum_Slow2;
		case eGdtfDmxFrequency_Slow3:	return XML_GDTF_DMXFrequencyEnum_Slow3;
			
	}
	
	// Make Assert
	ASSERTN(kEveryone,	value == eGdtfDmxFrequency_60 ||
			value == eGdtfDmxFrequency_15 ||
			value == eGdtfDmxFrequency_30 ||
			value == eGdtfDmxFrequency_Slow1 ||
			value == eGdtfDmxFrequency_Slow2 ||
			value == eGdtfDmxFrequency_Slow3);
	
	// Return default value
	return XML_GDTF_DMXFrequencyEnum_30;
}

/*static*/ bool GdtfConverter::ConvertFrequenz(const TXString& value, EGdtfDmxFrequency& freq)
{
	
	if		(value == XML_GDTF_DMXFrequencyEnum_60)		{ freq = eGdtfDmxFrequency_60;		}
	else if (value == XML_GDTF_DMXFrequencyEnum_15)		{ freq = eGdtfDmxFrequency_15;		}
	else if (value == XML_GDTF_DMXFrequencyEnum_30)		{ freq = eGdtfDmxFrequency_30;		}
	else if (value == XML_GDTF_DMXFrequencyEnum_Slow1)	{ freq = eGdtfDmxFrequency_Slow1;	}
	else if (value == XML_GDTF_DMXFrequencyEnum_Slow2)	{ freq = eGdtfDmxFrequency_Slow2;	}
	else if (value == XML_GDTF_DMXFrequencyEnum_Slow3)	{ freq = eGdtfDmxFrequency_Slow3;	}
	else if (value == "")								{ freq = eGdtfDmxFrequency_30;		}
	else												{ freq = eGdtfDmxFrequency_30; DSTOP((kEveryone, "Unaspected Input for Lamp Type Enum"));}
	
	// Return true
	return true;
	
}

/*static*/ TXString GdtfConverter::ConvertSnapEnum(EGdtfDmxSnap value)
{
	switch (value)
	{
		case eGdtfDmxMaster_No:		return XML_GDTF_DMXSnapEnum_No;
		case eGdtfDmxMaster_On:		return XML_GDTF_DMXSnapEnum_On;
		case eGdtfDmxMaster_Off:	return XML_GDTF_DMXSnapEnum_Off;
		case eGdtfDmxMaster_Yes:	return XML_GDTF_DMXSnapEnum_Yes;
	}
	
	// Make Assert
	ASSERTN(kEveryone,	value == eGdtfDmxMaster_On ||
			value == eGdtfDmxMaster_No ||
			value == eGdtfDmxMaster_Off ||
			value == eGdtfDmxMaster_Yes);
	
	// Return default value
	return XML_GDTF_DMXSnapEnum_No;
}

/*static*/ bool GdtfConverter::ConvertSnapEnum(const TXString& value, EGdtfDmxSnap& snap)
{
	if		(value == XML_GDTF_DMXSnapEnum_No)	{ snap = eGdtfDmxMaster_No;		}
	else if (value == XML_GDTF_DMXSnapEnum_On)	{ snap = eGdtfDmxMaster_On;		}
	else if (value == XML_GDTF_DMXSnapEnum_Off)	{ snap = eGdtfDmxMaster_Off;	}
	else if (value == XML_GDTF_DMXSnapEnum_Yes)	{ snap = eGdtfDmxMaster_Off;	}
	else if (value == "")						{ snap = eGdtfDmxMaster_No;		}
	else										{ snap = eGdtfDmxMaster_No; DSTOP((kEveryone, "Unaspected Input for EGdtfDmxSnap Enum"));}
	
	// Return true
	return true;
	
}

/*static*/ TXString GdtfConverter::ConvertMasterEnum(EGdtfDmxMaster value)
{
	switch (value)
	{
		case eGdtfDmxMaster_None:	return XML_GDTF_DMXMasterEnum_None;
		case eGdtfDmxMaster_Grand:	return XML_GDTF_DMXMasterEnum_Grand;
		case eGdtfDmxMaster_Group:	return XML_GDTF_DMXMasterEnum_Group;
	}
	
	// Make Assert
	ASSERTN(kEveryone,	value == eGdtfDmxMaster_None ||
			value == eGdtfDmxMaster_Grand ||
			value == eGdtfDmxMaster_Group);
	
	// Return default value
	return XML_GDTF_DMXMasterEnum_None;
}

/*static*/ bool GdtfConverter::ConvertMasterEnum(const TXString& value, EGdtfDmxMaster& master)
{
	if		(value == XML_GDTF_DMXMasterEnum_None)	{ master = eGdtfDmxMaster_None;	}
	else if (value == XML_GDTF_DMXMasterEnum_Grand)	{ master = eGdtfDmxMaster_Grand;}
	else if (value == XML_GDTF_DMXMasterEnum_Group)	{ master = eGdtfDmxMaster_Group;}
	else if (value == "")							{ master = eGdtfDmxMaster_None;	}
	else											{ master = eGdtfDmxMaster_None; DSTOP((kEveryone, "Unaspected Input for EGdtfDmxMaster Enum"));}
	
	// Return true
	return true;
	
}

/*static*/ TXString GdtfConverter::ConvertRelationEnum(EGdtfDmxRelationType value)
{
	switch (value)
	{
		case eGdtfDmxRelationType_Mode:		return XML_GDTF_DMXMasterEnum_Mode;
		case eGdtfDmxRelationType_Multiply:	return XML_GDTF_DMXMasterEnum_Multiply;
		case eGdtfDmxRelationType_Override:	return XML_GDTF_DMXMasterEnum_Override;
	}
	
	// Make Assert
	ASSERTN(kEveryone,	value == eGdtfDmxRelationType_Mode ||
			value == eGdtfDmxRelationType_Multiply ||
			value == eGdtfDmxRelationType_Override);
	
	// Return default value
	return XML_GDTF_DMXMasterEnum_Mode;
}

/*static*/ bool GdtfConverter::ConvertRelationEnum(const TXString& value, EGdtfDmxRelationType& relation)
{
	if		(value == XML_GDTF_DMXMasterEnum_Mode)		{ relation = eGdtfDmxRelationType_Mode;			}
	else if (value == XML_GDTF_DMXMasterEnum_Multiply)	{ relation = eGdtfDmxRelationType_Multiply;		}
	else if (value == XML_GDTF_DMXMasterEnum_Override)	{ relation = eGdtfDmxRelationType_Override;		}
	else if (value == "")								{ relation = eGdtfDmxRelationType_Mode;			}
	else												{ relation = eGdtfDmxRelationType_Mode; DSTOP((kEveryone, "Unaspected Input for EGdtfDmxRelationType Enum"));}
	
	// Return true
	return true;
	
	
}

/*static*/ TXString GdtfConverter::ConvertDMXInvertEnum(EGDTFDmxInvert value)
{
	switch (value)
	{
		case eGDTFDmxInvert_No:			return XML_GDTF_DMXChannelDmxInvertEnum_No;
		case eGDTFDmxInvert_Yes:		return XML_GDTF_DMXChannelDmxnvertEnum_Yes;
	}
	
	// Make Assert
	ASSERTN(kEveryone,	value == eGDTFDmxInvert_No ||
						value == eGDTFDmxInvert_Yes );
	
	// Return default value
	return XML_GDTF_DMXChannelDmxInvertEnum_No;
}

/*static*/ bool GdtfConverter::ConvertDMXInvertEnum(const TXString& value, EGDTFDmxInvert& dmx)
{
	if		(value == XML_GDTF_DMXChannelDmxInvertEnum_No)	{ dmx = eGDTFDmxInvert_No;		}
	else if (value == XML_GDTF_DMXChannelDmxnvertEnum_Yes)	{ dmx = eGDTFDmxInvert_Yes;		}
	else if (value == "")									{ dmx = eGDTFDmxInvert_No;		}
	else													{ dmx = eGDTFDmxInvert_No; DSTOP((kEveryone, "Unaspected Input for EGDTFDmxInvert Enum"));}
	
	// Return true
	return true;
	
}

/*static*/ TXString GdtfConverter::ConvertEncoderInvertEnum(EGDTFEncoderInvert value)
{
	switch (value)
	{
		case eGDTFEncoderInvert_No:			return XML_GDTF_DMXChannelEncoderInvertEnum_No;
		case eGDTFEncoderInvert_Yes:		return XML_GDTF_DMXChannelEncoderInvertEnum_Yes;
	}
	
	// Make Assert
	ASSERTN(kEveryone,	value == eGDTFEncoderInvert_No ||
						value == eGDTFEncoderInvert_Yes );
	
	// Return default value
	return XML_GDTF_DMXChannelEncoderInvertEnum_No;
}

/*static*/ bool GdtfConverter::ConvertEncoderInvertEnum(const TXString& value,EGDTFEncoderInvert&			enc)
{
	if		(value == XML_GDTF_DMXChannelEncoderInvertEnum_No)	{ enc = eGDTFEncoderInvert_No;		}
	else if (value == XML_GDTF_DMXChannelEncoderInvertEnum_Yes)	{ enc = eGDTFEncoderInvert_Yes;		}
	else if (value == "")										{ enc = eGDTFEncoderInvert_No;		}
	else														{ enc = eGDTFEncoderInvert_No; DSTOP((kEveryone, "Unaspected Input for EGDTFEncoderInvert Enum"));}
	
	// Return true
	return true;
	
}

bool SceneDataZip::GetFile(const TXString &fileName, const IFolderIdentifierPtr &workingFolder, IFileIdentifierPtr& outFile, bool& hasCheckSum, bool& checksumIsFine, bool checkSumCheck )
{
	// Preset out values
	hasCheckSum		= false;
	checksumIsFine	= false;
	
	// Make a pointer to that file
	IFileIdentifierPtr file (IID_FileIdentifier);
	file->Set(workingFolder, fileName);
	
	// Check if the files exists
	bool fileExists = false;
	file->ExistsOnDisk(fileExists);
	
	// If the file is there to something usefull with it
	if (fileExists)
	{
        if(checkSumCheck)
        {
			// Prepare a pointer to the file
			IFileIdentifierPtr checksumFile (IID_FileIdentifier);
			
			// Create the Filename for the checksum
			TXString filenameWithoutExtension;
			file->GetFileNameWithoutExtension(filenameWithoutExtension);
			
			// Check if the file is there
			bool placeholderBool1 = false;
			bool placeholderBool2 = false;
			hasCheckSum = GetFile(TXString() << filenameWithoutExtension << ".checksum.txt", workingFolder, checksumFile, placeholderBool1, placeholderBool2, false);
			

			if (hasCheckSum)
			{
				checksumIsFine = HashManager::HashManager::CheckHashForFile(file, checksumFile);
			}
		}

		// Set Out File Ptrb
		outFile = file;
		
		return true;
	}
	
	return false;
}


bool SceneDataZip::AddFileToZip(IZIPFilePtr& zipFile, const IFileIdentifierPtr& file, bool createChecksum, bool deleteFile, bool mustExist)
{
	//-------------------------------------------------------------------------------------------------
	// Check if there is a pointer
	ASSERTN(kEveryone, file != nullptr);
	if (file == nullptr) { return false; }
	
	//-------------------------------------------------------------------------------------------------
	// Check if there a file
	bool existsOnDisk = false;
	file->ExistsOnDisk(existsOnDisk);
	if(mustExist) {ASSERTN(kEveryone, existsOnDisk);} 
	if (existsOnDisk == false) { return false; }
	
	//-------------------------------------------------------------------------------------------------
	// Add the files that will be stored
	TXString nameFile;
	file->GetFileName(nameFile);
	
	//-------------------------------------------------------------------------------------------------
	// Write the  file
	zipFile->AddFile(nameFile, file);
	
	if (createChecksum)
	{
		SceneData::ISceneDataZipBuffer hashBuffer;
		HashManager::HashManager::CreateHashForFile(file, hashBuffer);
		
		// Create file name for checksum
		TXString fileNameCheckSum;
		file->GetFileNameWithoutExtension(fileNameCheckSum);
		
		fileNameCheckSum += ".checksum.txt";
		
		
		// Just call this again for this, but do not create a checksum for the checksum...
		AddFileToZip(zipFile, hashBuffer,fileNameCheckSum, false);
		
	}
	
	//-------------------------------------------------------------------------------------------------
	// HouseKeeping
	if (deleteFile) {
		file->DeleteOnDisk();
	}
	
	return true;
	
}

void SceneDataZip::AddFileToZip(IZIPFilePtr& zipFile, ISceneDataZipBuffer& buffer,const TXString &name , bool createChecksum)
{
    //-------------------------------------------------------------------------------------------------
    // Write the  file
    zipFile->AddFile(name, &buffer);
    
    if (createChecksum)
    {
        // Extract the filename
        ptrdiff_t	pos							= name.ReverseFind(".");
        TXString	fileNamewithoutExtension	= name.Mid(0,pos);

        TXString checksumFileName;
        checksumFileName += fileNamewithoutExtension;
        checksumFileName += ".checksum.txt";

        // Create the hash
        ISceneDataZipBuffer hashBuffer;
        HashManager::HashManager::CreateHashForBuffer(buffer, hashBuffer);
        

        // Just call this again for this, but do not create a checksum for the checksum...
        AddFileToZip(zipFile, hashBuffer, checksumFileName , false);
    }
}



/*static*/ bool GdtfConverter::Deserialize(const TXString& value, std::vector<double>& doubleArr)
{
	// Split string
	TXString strVal = value;
	
	// Find first entry
	ptrdiff_t pos = strVal.Find(",");
	while (pos > 0 )
	{
		// Copy string
		TXString strValInner;
		for (ptrdiff_t i = 0; i < pos; i++)	{ strValInner << strVal.GetAt(i); }
		
		// Try to cast
		VWStringConv con(strValInner);
		doubleArr.push_back(con.GetVWDocumentDouble(nsGeneral));
		
		// Delete and find next
		strVal.Delete(0, pos + 1);
		pos = strVal.Find(",");
	}
	
	// Delete and find next
	VWStringConv con(strVal);
	doubleArr.push_back(con.GetVWDocumentDouble(nsGeneral));
	

	
	return true;
}

void GdtfConverter::TraverseNodes(IXMLFileNodePtr root, const TXString& childContainerNodeName,const TXString& childNodeName, TProcessNodeCall processNodeFunction )
{
	// ------------------------------------------------------------------------------------
	// Print models
	IXMLFileNodePtr containerNode = nullptr;
	if (childContainerNodeName == "")	{ containerNode = root; }
	else								{ root->GetChildNode(childContainerNodeName, & containerNode); }
	
	if (containerNode)
	{
		IXMLFileNodePtr objNode = nullptr;
		if (VCOM_SUCCEEDED(containerNode->GetFirstChildNode(& objNode)))
		{
			while (objNode)
			{
				TXString nodeName;
				objNode->GetNodeName(nodeName);
				ASSERTN(kEveryone, nodeName == childNodeName);
				if (nodeName == childNodeName)
				{
					processNodeFunction(objNode);
				}
				
				// Step to the next node
				IXMLFileNodePtr next = nullptr;
				objNode->GetNextSiblingNode( & next);
				objNode = next;
			}
		}
		
		
		
	}
}

void GdtfConverter::TraverseMultiNodes(IXMLFileNodePtr root, const TXString& childContainerNodeName, TProcessMultiNodeCall processNodeFunction )
{
	// ------------------------------------------------------------------------------------
	// Print models
	IXMLFileNodePtr containerNode = nullptr;
	if (childContainerNodeName == "")	{ containerNode = root; }
	else								{ root->GetChildNode(childContainerNodeName, & containerNode); }
	
	if (containerNode)
	{
		IXMLFileNodePtr objNode = nullptr;
		if (VCOM_SUCCEEDED(containerNode->GetFirstChildNode(& objNode)))
		{
			while (objNode)
			{
				TXString nodeName;
				objNode->GetNodeName(nodeName);
				
				// Process Node
				processNodeFunction(objNode, nodeName);
				
				// Step to the next node
				IXMLFileNodePtr next = nullptr;
				objNode->GetNextSiblingNode( & next);
				objNode = next;
			}
		}
		
		
		
	}
}

ISceneDataZipBuffer::ISceneDataZipBuffer()
{
    fpZIPDataBuffer = NULL;
    fZIPDataBufferSize = 0;
}

ISceneDataZipBuffer::~ISceneDataZipBuffer()
{
    if ( fpZIPDataBuffer )
        delete [] fpZIPDataBuffer;
    fpZIPDataBuffer = NULL;
}


VCOMError ISceneDataZipBuffer::GetDataSize(size_t& outSize)
{
    outSize = fZIPDataBufferSize;
    return kVCOMError_NoError;
}

VCOMError ISceneDataZipBuffer::CopyDataInto(void* pDestinationBuffer, size_t bufferSize)
{
    if ( !fpZIPDataBuffer )
        return kVCOMError_NotInitialized;
    
    memcpy( pDestinationBuffer, fpZIPDataBuffer, (bufferSize >= fZIPDataBufferSize)? fZIPDataBufferSize : bufferSize );
    
    return kVCOMError_NoError;
}

VCOMError ISceneDataZipBuffer::SetData(void* pBuffer, size_t bufferSize)
{
    
    if ( fpZIPDataBuffer )
        delete [] fpZIPDataBuffer;
    
    fZIPDataBufferSize	= bufferSize;
    fpZIPDataBuffer		= new Uint8[ fZIPDataBufferSize + 1 ];
    memcpy( fpZIPDataBuffer, pBuffer, fZIPDataBufferSize );
    
    return kVCOMError_NoError;
}



VCOMError ISceneDataZipBuffer::WriteToFile(IFileIdentifierPtr file) {
    bool bOk = false;
    if ( file )
    {
        IRawOSFilePtr pFile( IID_RawOSFile );
        if ( pFile && VCOM_SUCCEEDED( pFile->Open( file, true, true, true, true ) ) )
        {
            size_t dataSize;
            this->GetDataSize( dataSize );
            char* writeData = new char[dataSize];
            this->CopyDataInto( writeData, dataSize );
            pFile->Write( 0, (Uint64)dataSize, (void*)writeData );
            pFile->Close();
            
            bOk = true;
            
            if ( writeData )
                delete [] writeData;
        }
    }
    return kVCOMError_NoError;
}

VCOMError ISceneDataZipBuffer::GetData(void*& dataPointer)
{
    dataPointer = fpZIPDataBuffer;
    return kVCOMError_NoError;
}

bool ISceneDataZipBuffer::IsSet()
{
	return (fpZIPDataBuffer != nullptr);
}

IXMLFileIOBufferImpl::IXMLFileIOBufferImpl()
{
    fXMLBuffer = NULL;
    fXMLBufferSize = 0;
}

IXMLFileIOBufferImpl::~IXMLFileIOBufferImpl()
{
    if ( fXMLBuffer )
        delete [] fXMLBuffer;
    fXMLBuffer = NULL;
}


VCOMError IXMLFileIOBufferImpl::GetDataSize(size_t& outSize)
{
    outSize = fXMLBufferSize;
    return kVCOMError_NoError;
}

VCOMError IXMLFileIOBufferImpl::CopyDataInto(void* pDestinationBuffer, size_t bufferSize)
{
    if ( !fXMLBuffer )
        return kVCOMError_NotInitialized;
    
    memcpy( pDestinationBuffer, fXMLBuffer, (bufferSize >= fXMLBufferSize)? fXMLBufferSize : bufferSize );
    
    return kVCOMError_NoError;
}

VCOMError IXMLFileIOBufferImpl::SetData(void* pBuffer, size_t bufferSize)
{
    
    if ( fXMLBuffer )
        delete [] fXMLBuffer;
    
    fXMLBufferSize	= bufferSize;
    fXMLBuffer		= new Uint8[ fXMLBufferSize + 1 ];
    memcpy( fXMLBuffer, pBuffer, fXMLBufferSize );
    
    return kVCOMError_NoError;
}

VCOMError IXMLFileIOBufferImpl::GetData(void*& dataPointer)
{
    dataPointer = fXMLBuffer;
    return kVCOMError_NoError;
}

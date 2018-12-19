//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------


#include "Prefix/StdAfx.h"
using namespace VWFC;

#include "SceneDataExchange.h"
#include "GDTFManager.h"
#include "XmlFileHelper.h"
#include "HashManager.h"
#include "GdtfError.h"

using namespace SceneData;

/*static*/ TXString GdtfConverter::ConvertUUID(const VWFC::Tools::VWUUID& uuid)
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

/*static*/ bool GdtfConverter::ConvertUUID(const TXString& inValue, VWFC::Tools::VWUUID& uuid)
{
	// First check if theinValuelength is as aspected
	ASSERTN(kEveryone, inValue.GetLength() == 47 || inValue.GetLength() == 0);
	if (inValue.GetLength() != 47)	
    {
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_UuidHasWrongFormat);
        SceneData::GdtfFixture::AddError(error); 
        return false; 
    }
	
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
	
	uuid = VWUUID(uuidForRead);
	
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
	if (d_arr.size() != 3)
    {
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_ColorHasWrongFormat);
        SceneData::GdtfFixture::AddError(error);
        color = CCieColor();
        return false;
    }
	
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
	if(value.IsEmpty()) { return false; }
	
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

/*static*/ bool GdtfConverter::ConvertDmxBreak(const TXString& value, Sint32& intValue)
{
    if(value.IsEmpty()) return false;
    if(value == XML_GDTF_DMXChannelDMXBreak_OverwriteValue) { intValue = 0; return true; }

	intValue = value.atoi();
	return true;
}

/*static*/ bool GdtfConverter::ConvertInteger(const TXString& value, Sint8& intValue)
{
    if(value.IsEmpty()) return false;

	intValue = value.atoi();
	return true;
}

/*static*/ bool GdtfConverter::ConvertInteger(const TXString& value, size_t& intValue)
{
    if(value.IsEmpty()) return false;
	
    intValue = value.atoi();
	return true;
}

/*static*/ bool GdtfConverter::ConvertInteger(const TXString& value, Sint32& intValue)
{
    if(value.IsEmpty()) return false;
	
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

TXString SceneData::GdtfConverter::ConvertIntegerArray(TSint32Array & values)
/* Takes an Int-Array and returns it as string in the format: "{Int, Int, ... Int}" */
{   
    TXString arrayStr;
    
    // Begin the array Str
    arrayStr = "{";

    // Add the Values
    for (int idx = 0; idx < values.size(); idx++)
    {        
        arrayStr += TXString().ToStringInt(values.at(idx));
        
        // The last index is size-1. We want that no "," is appended at the last item 
        // so only append "," for idx < last_idx.
        if (idx < values.size() - 1) 
        {
            arrayStr += ",";
        }        
    }    

    // CLose the Array Str
    arrayStr += "}";

    return arrayStr;
}

bool SceneData::GdtfConverter::ConvertIntegerArray(TXString values, TSint32Array & intArray)
/* Takes string in the format: "{Int, Int, ... Int}" and fills the values into the IntArray. */
{
    TXString intArrayString = values;
    if (values.IsEmpty()) { return false; }

    // Remove the barcets "{" and "}"
    values.Replace("{", "");
    values.Replace("}", "");

    // Seperate the string by ","
    GdtfConverter::Deserialize(values, intArray);
    return true;
}

/*static*/ TXString GdtfConverter::ConvertInteger(size_t value)
{	
	// Otherwise return the value
	TXString valueStr;
	valueStr << value;
	return valueStr;
}

/*static*/ TXString GdtfConverter::ConvertDmxBreak(Sint32 value)
{	
	// If it is not set then it is Overwrite value
    if(value == 0){ return TXString( XML_GDTF_DMXChannelDMXBreak_OverwriteValue );}
    
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
    if(value.IsEmpty()) {intValue = 1; return false;}

	intValue = value.atoi();

    ASSERTN(kEveryone, intValue > 0);
    ASSERTN(kEveryone, intValue < 513);
	if (intValue > 0)	
    {
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_DmxAdressHasWrongValue);
        SceneData::GdtfFixture::AddError(error); 
        return false; 
    }
	if (intValue < 513)	
    {
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_DmxAdressHasWrongValue);
        SceneData::GdtfFixture::AddError(error); 
        return false; 
    }

    return true;
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
		part1 += str.GetAt(i);
	}

	// 2nd Part: Start at Split pos + 1 to exclude the spilt char from the result.
	size_t start2ndPart = 0;

	if (includeSplitPos) { start2ndPart = splitPos; }
	else				 { start2ndPart = splitPos + 1; }

	for (size_t i = start2ndPart; i < strLen; i++)	{ part2 += str.GetAt(i); }
	
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
	if (splitPos == -1)
    {
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_DmxValueHasWrongValue);
        SceneData::GdtfFixture::AddError(error);
        return false;
    }


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
				        intValue = dmxValueRaw / 256; break;
			        }
                    case eGdtfChannelBitResolution_24:
			        {
				        intValue = dmxValueRaw / 256 / 256; break;
			        }	
                    case eGdtfChannelBitResolution_32:
			        {			
				        intValue = dmxValueRaw / 256 / 256 / 256; break;
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
                        intValue = dmxValueRaw * 256; break;
                    }
                    // /No need to check eGdtfChannelBitResolution_16 here.)
                    case eGdtfChannelBitResolution_24:
                    {
                        intValue = dmxValueRaw / 256; break;
                    }
                    case eGdtfChannelBitResolution_32:
                    {
                        intValue = dmxValueRaw / 256 / 256; break;
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
                        intValue = dmxValueRaw * 256 * 256; break;
                    }
                    case eGdtfChannelBitResolution_16:
                    {
                        intValue = dmxValueRaw * 256; break;
                    }
                    // (No need to check eGdtfChannelBitResolution_24 here.)
                    case eGdtfChannelBitResolution_32:
                    {
                        intValue = dmxValueRaw / 256; break;
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
                        intValue = dmxValueRaw * 256 * 256 * 256; break;
                    }
                    case eGdtfChannelBitResolution_16:
                    {
                        intValue = dmxValueRaw * 256 * 256; break;
                    }
                    case eGdtfChannelBitResolution_24:
                    {
                        intValue = dmxValueRaw * 256; break;
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

    if ( GetChannelMaxDmx(chanlReso) < intValue)
    {
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_DmxValueHasWrongValue);
        SceneData::GdtfFixture::AddError(error);
        return false;
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
	else
    {
        type = eGdtfModel_PrimitiveType_Undefined; DSTOP((kEveryone, "Unaspected Input for Primitive Type Enum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_EnumNoMatchingEntry);
        SceneData::GdtfFixture::AddError(error);
    }
	
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
			
		default:                        DSTOP((kEveryone,"EGdtfSpecial enum is not implemented!"));

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
	else												
    {
        special = EGdtfSpecial::None; DSTOP((kEveryone, "Unaspected Input for EGdtfSpecial Enum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_EnumNoMatchingEntry);
        SceneData::GdtfFixture::AddError(error);
    }
	
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
	else
    {
        unit = EGdtfPhysicalUnit::None; DSTOP((kEveryone, "Unaspected Input for EGdtfPhysicalUnit Enum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_EnumNoMatchingEntry);
        SceneData::GdtfFixture::AddError(error); 
    }
	
	// Return true
	return true;
}
/*static*/ bool GdtfConverter::ConvertBeamType(const TXString& value, EGdtfBeamType& unit)
{
	if		(value == XML_GDTF_BeamTypeEnum_Wash)			{ unit = EGdtfBeamType::eGdtfBeamType_Wash;		 }
	else if (value == XML_GDTF_BeamTypeEnum_Spot)			{ unit = EGdtfBeamType::eGdtfBeamType_Spot;		 }
	else if (value == XML_GDTF_BeamTypeEnum_None)			{ unit = EGdtfBeamType::eGdtfBeamType_None;		 }
	else if (value == "")									{ unit = EGdtfBeamType::eGdtfBeamType_Wash;		 }
	else													
    {
        unit = EGdtfBeamType::eGdtfBeamType_Wash; DSTOP((kEveryone, "Unaspected Input for EGdtfBeamType Enum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_EnumNoMatchingEntry);
        SceneData::GdtfFixture::AddError(error); 
    }
	
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


/*static*/ TXString GdtfConverter::ConvertMatrix(const VWTransformMatrix& ma, bool fourLines)
{
	TXString value;
	if(fourLines)
	{
		// For GDTF
		value << "{" << ma.GetUVector().x  << "," << ma.GetUVector().y << "," << ma.GetUVector().z << "," << ma.GetOffset().x << "}";
		value << "{" << ma.GetVVector().x  << "," << ma.GetVVector().y << "," << ma.GetVVector().z << "," << ma.GetOffset().y << "}";
		value << "{" << ma.GetWVector().x  << "," << ma.GetWVector().y << "," << ma.GetWVector().z << "," << ma.GetOffset().z << "}";
		value << "{" << "0"                << "," << "0"               << "," << "0"               << "," << "1"              << "}";

	}
	else
	{
		// For MVR
		value << "{" << ma.GetUVector().x  << "," << ma.GetUVector().y << "," << ma.GetUVector().z << "}";
		value << "{" << ma.GetVVector().x  << "," << ma.GetVVector().y << "," << ma.GetVVector().z << "}";
		value << "{" << ma.GetWVector().x  << "," << ma.GetWVector().y << "," << ma.GetWVector().z << "}";
		value << "{" << ma.GetOffset().x   << "," << ma.GetOffset().y  << "," << ma.GetOffset().z  << "}";
	}
	

	
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
	if (strVal.GetAt(0) == '{') { strVal.Delete(0,1); }
    else
    {
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_MatrixFormatError);
        SceneData::GdtfFixture::AddError(error); 
    }
	
	// Delete last element
	ASSERTN(kEveryone, strVal.GetLast() == '}');
	if (strVal.GetLast() == '}') { strVal.DeleteLast(); }
    else
    {
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_MatrixFormatError);
        SceneData::GdtfFixture::AddError(error);
    }
	
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
	if (strVal.Find("}{") == -1)
    {
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_MatrixFormatError);
        SceneData::GdtfFixture::AddError(error);
    }

	// Apped the rest
	lines.push_back(strVal);

	if (lines.size() != 4)
	{
		DSTOP((kEveryone,"Failed to split the Matrix into vertices"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_MatrixFormatError);
        SceneData::GdtfFixture::AddError(error);
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
			DSTOP((kEveryone, "Unaspected Format of Matrix"));
			continue;
		}
		
		// ----------------------------------------------------------------
		// Set the matrix for a 4x3 matrix
		if(arr.size() == 3)
		{
			matrix.fMatrix.mat[i][0] = arr [0];
			matrix.fMatrix.mat[i][1] = arr [1];
			matrix.fMatrix.mat[i][2] = arr [2];

		}
		// ----------------------------------------------------------------
		// Set the matrix for a 4x4 matrix
		else
		{
			if(i<3)
			{
				// This is the rotation part
				matrix.fMatrix.mat[i][0] = arr [0];
				matrix.fMatrix.mat[i][1] = arr [1];
				matrix.fMatrix.mat[i][2] = arr [2];

				// This is the offset part
				matrix.fMatrix.mat[3][i] = arr [3];
			}


		}


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
	else
    {
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_MatrixFormatError);
        SceneData::GdtfFixture::AddError(error); 
    }
	
	// Delete second last element
	ASSERTN(kEveryone, strVal.GetLast() == '}');
	if (strVal.GetLast() == '}')	{ strVal.DeleteLast(); }
	else
    {
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_MatrixFormatError);
        SceneData::GdtfFixture::AddError(error); 
    }

	// ----------------------------------------------------------------
	// Split into parts
	TXStringArray lines;
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
    if (strVal.Find("}{") == -1)
    {
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_MatrixFormatError);
        SceneData::GdtfFixture::AddError(error); 
    }
	
	// Apped the rest
	lines.push_back(strVal);
	
	if (lines.size() != 3)
	{
		DSTOP((kEveryone,"Failed to split the Matrix into vertices"));
		GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_MatrixFormatError);
        SceneData::GdtfFixture::AddError(error);
        return false;
	}
	
	// ----------------------------------------------------------------
	// Do the conversion
	for (size_t i = 0; i < lines.size(); i++)
	{
		std::vector<double> arr;
		Deserialize(lines.at(i), arr);
		
		if (arr.size() != 3)
		{
			DSTOP((kEveryone, "Unaspected amount of entries in Matrix"));
            GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_MatrixFormatError);
            SceneData::GdtfFixture::AddError(error);
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
	else
    {
        lampType = eGdtfLampType_Dischange; DSTOP((kEveryone, "Unaspected Input for Lamp Type Enum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_EnumNoMatchingEntry);
        SceneData::GdtfFixture::AddError(error);
    }
	
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
	else
    {
        freq = eGdtfDmxFrequency_30; DSTOP((kEveryone, "Unaspected Input for Lamp Type Enum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_EnumNoMatchingEntry);
        SceneData::GdtfFixture::AddError(error);
    }
	
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

        default: DSTOP((kEveryone, "ConvertSnapEnum: Invalid Input-Value"));
	}	
	
	// Return default value
	return XML_GDTF_DMXSnapEnum_No;
}

/*static*/ bool GdtfConverter::ConvertSnapEnum(const TXString& value, EGdtfDmxSnap& snap)
{
	if		(value == XML_GDTF_DMXSnapEnum_No)	{ snap = eGdtfDmxMaster_No;		}
	else if (value == XML_GDTF_DMXSnapEnum_On)	{ snap = eGdtfDmxMaster_On;		}
	else if (value == XML_GDTF_DMXSnapEnum_Off)	{ snap = eGdtfDmxMaster_Off;	}
	else if (value == XML_GDTF_DMXSnapEnum_Yes)	{ snap = eGdtfDmxMaster_Yes;	}
	else if (value == "")						{ snap = eGdtfDmxMaster_No;		}
	else
    {
        snap = eGdtfDmxMaster_No; DSTOP((kEveryone, "Unaspected Input for EGdtfDmxSnap Enum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_EnumNoMatchingEntry);
        SceneData::GdtfFixture::AddError(error);
    }
	
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
        default: DSTOP((kEveryone, "ConvertMasterEnum: Invalid Input-Value"));
	}	
	
	// Return default value
	return XML_GDTF_DMXMasterEnum_None;
}

/*static*/ bool GdtfConverter::ConvertMasterEnum(const TXString& value, EGdtfDmxMaster& master)
{
	if		(value == XML_GDTF_DMXMasterEnum_None)	{ master = eGdtfDmxMaster_None;	}
	else if (value == XML_GDTF_DMXMasterEnum_Grand)	{ master = eGdtfDmxMaster_Grand;}
	else if (value == XML_GDTF_DMXMasterEnum_Group)	{ master = eGdtfDmxMaster_Group;}
	else if (value == "")							{ master = eGdtfDmxMaster_None;	}
	else
    {
        master = eGdtfDmxMaster_None; DSTOP((kEveryone, "Unaspected Input for EGdtfDmxMaster Enum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_EnumNoMatchingEntry);
        SceneData::GdtfFixture::AddError(error);
    }
	
	// Return true
	return true;
	
}

/*static*/ TXString GdtfConverter::ConvertRelationEnum(EGdtfDmxRelationType value)
{
	switch (value)
	{
		case eGdtfDmxRelationType_Multiply:	return XML_GDTF_DMXMasterEnum_Multiply;
		case eGdtfDmxRelationType_Override:	return XML_GDTF_DMXMasterEnum_Override;
        default: DSTOP((kEveryone, "ConvertRelationEnum: Invalid Input-Value"));
	}	
	
	// Return default value
	return XML_GDTF_DMXMasterEnum_Override;
}

/*static*/ bool GdtfConverter::ConvertRelationEnum(const TXString& value, EGdtfDmxRelationType& relation)
{
	if      (value == XML_GDTF_DMXMasterEnum_Multiply)	{ relation = eGdtfDmxRelationType_Multiply;		}
	else if (value == XML_GDTF_DMXMasterEnum_Override)	{ relation = eGdtfDmxRelationType_Override;		}
	else if (value == "")								{ relation = eGdtfDmxRelationType_Override;			}
	else
    {
        relation = eGdtfDmxRelationType_Override; DSTOP((kEveryone, "Unaspected Input for EGdtfDmxRelationType Enum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_EnumNoMatchingEntry);
        SceneData::GdtfFixture::AddError(error);
    }
	
	// Return true
	return true;
	
	
}

/*static*/ TXString GdtfConverter::ConvertDMXInvertEnum(EGDTFDmxInvert value)
{
	switch (value)
	{
		case eGDTFDmxInvert_No:			return XML_GDTF_DMXChannelDmxInvertEnum_No;
		case eGDTFDmxInvert_Yes:		return XML_GDTF_DMXChannelDmxnvertEnum_Yes;
        default: DSTOP((kEveryone, "ConvertDMXInvertEnum: Invalid Input-Value"));
	}	
	
	// Return default value
	return XML_GDTF_DMXChannelDmxInvertEnum_No;
}

/*static*/ bool GdtfConverter::ConvertDMXInvertEnum(const TXString& value, EGDTFDmxInvert& dmx)
{
	if		(value == XML_GDTF_DMXChannelDmxInvertEnum_No)	{ dmx = eGDTFDmxInvert_No;		}
	else if (value == XML_GDTF_DMXChannelDmxnvertEnum_Yes)	{ dmx = eGDTFDmxInvert_Yes;		}
	else if (value == "")									{ dmx = eGDTFDmxInvert_No;		}
	else
    {
        dmx = eGDTFDmxInvert_No; DSTOP((kEveryone, "Unaspected Input for EGDTFDmxInvert Enum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_EnumNoMatchingEntry);
        SceneData::GdtfFixture::AddError(error);
    }
	
	// Return true
	return true;
}

/*static*/ TXString GdtfConverter::ConvertEncoderInvertEnum(EGDTFEncoderInvert value)
{
	switch (value)
	{
		case eGDTFEncoderInvert_No:			return XML_GDTF_DMXChannelEncoderInvertEnum_No;
		case eGDTFEncoderInvert_Yes:		return XML_GDTF_DMXChannelEncoderInvertEnum_Yes;
        default: DSTOP((kEveryone, "ConvertEncoderInvertEnum: Invalid Input-Value"));
	}	
	
	// Return default value
	return XML_GDTF_DMXChannelEncoderInvertEnum_No;
}

/*static*/ bool GdtfConverter::ConvertEncoderInvertEnum(const TXString& value, EGDTFEncoderInvert&			enc)
{
	if		(value == XML_GDTF_DMXChannelEncoderInvertEnum_No)	{ enc = eGDTFEncoderInvert_No;		}
	else if (value == XML_GDTF_DMXChannelEncoderInvertEnum_Yes)	{ enc = eGDTFEncoderInvert_Yes;		}
	else if (value == "")										{ enc = eGDTFEncoderInvert_No;		}
	else
    {
        enc = eGDTFEncoderInvert_No; DSTOP((kEveryone, "Unaspected Input for EGDTFEncoderInvert Enum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_EnumNoMatchingEntry);
        SceneData::GdtfFixture::AddError(error);
    }
	
	// Return true
	return true;	
}

/*static*/ TXString GdtfConverter::ConvertRDMParamTypeEnum(EGdtf_RDMParam_Type value)
{           
    switch (value)
    {
        case EGdtf_RDMParam_Type::RDM:			  return XML_GDTF_RDMParamTypeEnum_RDM;
        case EGdtf_RDMParam_Type::FixtureType:	  return XML_GDTF_RDMParamTypeEnum_FixtureType;
        case EGdtf_RDMParam_Type::Fixture:		  return XML_GDTF_RDMParamTypeEnum_Fixture;        
        default: DSTOP((kEveryone, "ConvertRDMParamTypeEnum: Invalid Input-Value"));
    }

    // Default
    return XML_GDTF_RDMParamTypeEnum_RDM; // TODO: Theres no default value at the moment check this later again. (19.10)
}

/*static*/ bool GdtfConverter::ConvertRDMParamTypeEnum(const TXString& value, EGdtf_RDMParam_Type&			val)
{
    if (value == XML_GDTF_RDMParamTypeEnum_RDM)              { val = EGdtf_RDMParam_Type::RDM;}
    else if (value == XML_GDTF_RDMParamTypeEnum_FixtureType) { val = EGdtf_RDMParam_Type::FixtureType;}
    else if (value == XML_GDTF_RDMParamTypeEnum_Fixture)     { val = EGdtf_RDMParam_Type::Fixture;}
    else 
    { 
        val = EGdtf_RDMParam_Type::RDM; 
        DSTOP((kEveryone, "Unaspected Input for ConvertRDMParamTypeEnum Enum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_EnumNoMatchingEntry);
        SceneData::GdtfFixture::AddError(error);
    } // TODO: Theres no default value at the moment check this later again. (19.10)

    return true;
}

/*static*/ TXString GdtfConverter::Convert_RDMParamDataTypeEnum(EGdtf_RDMParam_DataType value)
{
    switch (value)
    {
        case EGdtf_RDMParam_DataType::DS_NOT_DEFINED :   	return XML_GDTF_RDMParam_DataTypeEnum_DS_NOT_DEFINED;
        case EGdtf_RDMParam_DataType::DS_BIT_FIELD:			return XML_GDTF_RDMParam_DataTypeEnum_DS_BIT_FIELD;
        case EGdtf_RDMParam_DataType::DS_ASCII: 			return XML_GDTF_RDMParam_DataTypeEnum_DS_ASCII;
        case EGdtf_RDMParam_DataType::DS_UNSIGNED_BYTE:		return XML_GDTF_RDMParam_DataTypeEnum_DS_UNSIGNED_BYTE;
        case EGdtf_RDMParam_DataType::DS_SIGNED_BYTE:		return XML_GDTF_RDMParam_DataTypeEnum_DS_SIGNED_BYTE;
        case EGdtf_RDMParam_DataType::DS_UNSIGNED_WORD:		return XML_GDTF_RDMParam_DataTypeEnum_DS_UNSIGNED_WORD;
        case EGdtf_RDMParam_DataType::DS_SIGNED_WORD:   	return XML_GDTF_RDMParam_DataTypeEnum_DS_SIGNED_WORD;
        case EGdtf_RDMParam_DataType::DS_UNSIGNED_DWORD:	return XML_GDTF_RDMParam_DataTypeEnum_DS_UNSIGNED_DWORD;
        case EGdtf_RDMParam_DataType::DS_SIGNED_DWORD:		return XML_GDTF_RDMParam_DataTypeEnum_DS_SIGNED_DWORD;
        case EGdtf_RDMParam_DataType::DS_MS:        		return XML_GDTF_RDMParam_DataTypeEnum_DS_MS;
        default: DSTOP((kEveryone, "Convert_RDMParamDataTypeEnum: Invalid Input-Value"));
    }

    // Default
    return XML_GDTF_RDMParam_DataTypeEnum_DS_NOT_DEFINED; // TODO: Theres no default value at the moment check this later again. (19.10)
}

/*static*/ bool GdtfConverter::Convert_RDMParamDataTypeEnum(const TXString& value, EGdtf_RDMParam_DataType& val)
{
    if      (value == XML_GDTF_RDMParam_DataTypeEnum_DS_NOT_DEFINED)    { val = EGdtf_RDMParam_DataType::DS_NOT_DEFINED; }
    else if (value == XML_GDTF_RDMParam_DataTypeEnum_DS_BIT_FIELD)      { val = EGdtf_RDMParam_DataType::DS_BIT_FIELD ; }
    else if (value == XML_GDTF_RDMParam_DataTypeEnum_DS_ASCII)          { val = EGdtf_RDMParam_DataType::DS_ASCII; }
    else if (value == XML_GDTF_RDMParam_DataTypeEnum_DS_UNSIGNED_BYTE)  { val = EGdtf_RDMParam_DataType::DS_UNSIGNED_BYTE; }
    else if (value == XML_GDTF_RDMParam_DataTypeEnum_DS_SIGNED_BYTE)    { val = EGdtf_RDMParam_DataType::DS_SIGNED_BYTE; }
    else if (value == XML_GDTF_RDMParam_DataTypeEnum_DS_UNSIGNED_WORD)  { val = EGdtf_RDMParam_DataType::DS_UNSIGNED_WORD; }
    else if (value == XML_GDTF_RDMParam_DataTypeEnum_DS_SIGNED_WORD)    { val = EGdtf_RDMParam_DataType::DS_SIGNED_WORD; }
    else if (value == XML_GDTF_RDMParam_DataTypeEnum_DS_UNSIGNED_DWORD) { val = EGdtf_RDMParam_DataType::DS_UNSIGNED_DWORD; }
    else if (value == XML_GDTF_RDMParam_DataTypeEnum_DS_SIGNED_DWORD)   { val = EGdtf_RDMParam_DataType::DS_SIGNED_DWORD; }
    else if (value == XML_GDTF_RDMParam_DataTypeEnum_DS_MS)             { val = EGdtf_RDMParam_DataType::DS_MS;}
    else 
    { 
        val = EGdtf_RDMParam_DataType::DS_NOT_DEFINED; // TODO: Theres no default value at the moment check this later again. (19.10)
        DSTOP((kEveryone, "Unaspected Input for EGDTFvaloderInvert Enum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_EnumNoMatchingEntry);
        SceneData::GdtfFixture::AddError(error);
    }

    return true;
}

/*static*/ TXString GdtfConverter::Convert_RDMParam_CommandEnum(EGdtf_RDMParam_Command value)
{
    switch (value)
    {
        case EGdtf_RDMParam_Command::None:	    		return XML_GDTF_RDMParam_Command_None;
        case EGdtf_RDMParam_Command::CC_GET:			return XML_GDTF_RDMParam_Command_CC_GET;
        case EGdtf_RDMParam_Command::CC_SET:			return XML_GDTF_RDMParam_Command_CC_SET;
        case EGdtf_RDMParam_Command::CC_GET_SET:		return XML_GDTF_RDMParam_Command_CC_GET_SET;
        default: DSTOP( (kEveryone, "Convert_RDMParam_CommandEnum: Invalid Input-Value") );
    }
    
    // Default
    return XML_GDTF_RDMParam_Command_None; // TODO: Theres no default value at the moment check this later again. (19.10)
}

/*static*/ bool GdtfConverter::Convert_RDMParam_CommandEnum(const TXString& value, EGdtf_RDMParam_Command&			val)
{
    if      (value == XML_GDTF_RDMParam_Command_None)       { val = EGdtf_RDMParam_Command::None; }
    else if (value == XML_GDTF_RDMParam_Command_CC_GET)     { val = EGdtf_RDMParam_Command::CC_GET; }
    else if (value == XML_GDTF_RDMParam_Command_CC_SET)     { val = EGdtf_RDMParam_Command::CC_SET; }
    else if (value == XML_GDTF_RDMParam_Command_CC_GET_SET) { val = EGdtf_RDMParam_Command::CC_GET_SET; }
    else
    {
        val = EGdtf_RDMParam_Command::None;; // TODO: Theres no default value at the moment check this later again. (19.10)
        DSTOP((kEveryone, "Unaspected Input for Convert_RDMParam_CommandEnum Enum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_RDMParamNoMatchingEntry);
        SceneData::GdtfFixture::AddError(error);
    }

    return true;
}


/*static*/ TXString GdtfConverter::Convert_RDMParam_SensorUnitEnum(EGdtf_RDMParam_SensorUnit value)
{
    switch (value)
    {
    case EGdtf_RDMParam_SensorUnit::UNITS_NONE:		                    return XML_GDTF_RDMParam_SensorUnit_UNITS_NONE;
    case EGdtf_RDMParam_SensorUnit::UNITS_CENTIGRADE:	                return XML_GDTF_RDMParam_SensorUnit_UNITS_CENTIGRADE;
    case EGdtf_RDMParam_SensorUnit::UNITS_VOLTS_DC:			            return XML_GDTF_RDMParam_SensorUnit_UNITS_VOLTS_DC;
    case EGdtf_RDMParam_SensorUnit::UNITS_VOLTS_AC_PEAK:		    	return XML_GDTF_RDMParam_SensorUnit_UNITS_VOLTS_AC_PEAK;
    case EGdtf_RDMParam_SensorUnit::UNITS_VOLTS_AC_RMS:			        return XML_GDTF_RDMParam_SensorUnit_UNITS_VOLTS_AC_RMS;
    case EGdtf_RDMParam_SensorUnit::UNITS_AMPERE_DC:			        return XML_GDTF_RDMParam_SensorUnit_UNITS_AMPERE_DC;
    case EGdtf_RDMParam_SensorUnit::UNITS_AMPERE_AC_PEAK:			    return XML_GDTF_RDMParam_SensorUnit_UNITS_AMPERE_AC_PEAK;
    case EGdtf_RDMParam_SensorUnit::UNITS_AMPERE_AC_RMS:		      	return XML_GDTF_RDMParam_SensorUnit_UNITS_AMPERE_AC_RMS;
    case EGdtf_RDMParam_SensorUnit::UNITS_HERTZ:		            	return XML_GDTF_RDMParam_SensorUnit_UNITS_HERTZ;
    case EGdtf_RDMParam_SensorUnit::UNITS_OHM:			                return XML_GDTF_RDMParam_SensorUnit_UNITS_OHM;
    case EGdtf_RDMParam_SensorUnit::UNITS_WATT:			                return XML_GDTF_RDMParam_SensorUnit_UNITS_WATT;
    case EGdtf_RDMParam_SensorUnit::UNITS_KILOGRAM:		            	return XML_GDTF_RDMParam_SensorUnit_UNITS_KILOGRAM;
    case EGdtf_RDMParam_SensorUnit::UNITS_METERS:			            return XML_GDTF_RDMParam_SensorUnit_UNITS_METERS;
    case EGdtf_RDMParam_SensorUnit::UNITS_METERS_SQUARED:		    	return XML_GDTF_RDMParam_SensorUnit_UNITS_METERS_SQUARED;
    case EGdtf_RDMParam_SensorUnit::UNITS_METERS_CUBED:			        return XML_GDTF_RDMParam_SensorUnit_UNITS_METERS_CUBED;
    case EGdtf_RDMParam_SensorUnit::UNITS_KILOGRAMMES_PER_METER_CUBED:	return XML_GDTF_RDMParam_SensorUnit_UNITS_KILOGRAMMES_PER_METER_CUBED;
    case EGdtf_RDMParam_SensorUnit::UNITS_METERS_PER_SECOND:			return XML_GDTF_RDMParam_SensorUnit_UNITS_METERS_PER_SECOND;
    case EGdtf_RDMParam_SensorUnit::UNITS_METERS_PER_SECOND_SQUARED:	return XML_GDTF_RDMParam_SensorUnit_UNITS_METERS_PER_SECOND_SQUARED;
    case EGdtf_RDMParam_SensorUnit::UNITS_NEWTON:			            return XML_GDTF_RDMParam_SensorUnit_UNITS_NEWTON;
    case EGdtf_RDMParam_SensorUnit::UNITS_JOULE:			            return XML_GDTF_RDMParam_SensorUnit_UNITS_JOULE;
    case EGdtf_RDMParam_SensorUnit::UNITS_PASCAL:			            return XML_GDTF_RDMParam_SensorUnit_UNITS_PASCAL;
    case EGdtf_RDMParam_SensorUnit::UNITS_SECOND:			            return XML_GDTF_RDMParam_SensorUnit_UNITS_SECOND;
    case EGdtf_RDMParam_SensorUnit::UNITS_DEGREE:			            return XML_GDTF_RDMParam_SensorUnit_UNITS_DEGREE;
    case EGdtf_RDMParam_SensorUnit::UNITS_STERADIAN:		        	return XML_GDTF_RDMParam_SensorUnit_UNITS_STERADIAN;
    case EGdtf_RDMParam_SensorUnit::UNITS_CANDELA:		            	return XML_GDTF_RDMParam_SensorUnit_UNITS_CANDELA;
    case EGdtf_RDMParam_SensorUnit::UNITS_LUMEN:			            return XML_GDTF_RDMParam_SensorUnit_UNITS_LUMEN;
    case EGdtf_RDMParam_SensorUnit::UNITS_LUX:			                return XML_GDTF_RDMParam_SensorUnit_UNITS_LUX;
    case EGdtf_RDMParam_SensorUnit::UNITS_IRE:		                	return XML_GDTF_RDMParam_SensorUnit_UNITS_IRE;
    case EGdtf_RDMParam_SensorUnit::UNITS_BYTE:		                	return XML_GDTF_RDMParam_SensorUnit_UNITS_BYTE;
    case EGdtf_RDMParam_SensorUnit::UNITS_MS:		                	return XML_GDTF_RDMParam_SensorUnit_UNITS_MS;    
    default: DSTOP( (kEveryone, "Convert_RDMParam_SensorUnitEnum: Invalid Input-Value") );
    }
        
    return XML_GDTF_RDMParam_SensorUnit_UNITS_NONE;  // TODO: Theres no default value at the moment check this later again. (19.10)
}

/*static*/ bool GdtfConverter::Convert_RDMParam_SensorUnitEnum(const TXString& value, EGdtf_RDMParam_SensorUnit&	val)
{
    if      (value == XML_GDTF_RDMParam_SensorUnit_UNITS_NONE)                        { val = EGdtf_RDMParam_SensorUnit::UNITS_NONE;}
    else if (value == XML_GDTF_RDMParam_SensorUnit_UNITS_CENTIGRADE)                  { val = EGdtf_RDMParam_SensorUnit::UNITS_CENTIGRADE;}
    else if (value == XML_GDTF_RDMParam_SensorUnit_UNITS_VOLTS_DC)                    { val = EGdtf_RDMParam_SensorUnit::UNITS_VOLTS_DC;}
    else if (value == XML_GDTF_RDMParam_SensorUnit_UNITS_VOLTS_AC_PEAK)               { val = EGdtf_RDMParam_SensorUnit::UNITS_VOLTS_AC_PEAK;}
    else if (value == XML_GDTF_RDMParam_SensorUnit_UNITS_VOLTS_AC_RMS)                { val = EGdtf_RDMParam_SensorUnit::UNITS_VOLTS_AC_RMS;}
    else if (value == XML_GDTF_RDMParam_SensorUnit_UNITS_AMPERE_DC)                   { val = EGdtf_RDMParam_SensorUnit::UNITS_AMPERE_DC;}
    else if (value == XML_GDTF_RDMParam_SensorUnit_UNITS_AMPERE_AC_PEAK)              { val = EGdtf_RDMParam_SensorUnit::UNITS_AMPERE_AC_PEAK;}
    else if (value == XML_GDTF_RDMParam_SensorUnit_UNITS_AMPERE_AC_RMS)               { val = EGdtf_RDMParam_SensorUnit::UNITS_AMPERE_AC_RMS;}
    else if (value == XML_GDTF_RDMParam_SensorUnit_UNITS_HERTZ)                       { val = EGdtf_RDMParam_SensorUnit::UNITS_HERTZ;}
    else if (value == XML_GDTF_RDMParam_SensorUnit_UNITS_OHM)                         { val = EGdtf_RDMParam_SensorUnit::UNITS_OHM;}
    else if (value == XML_GDTF_RDMParam_SensorUnit_UNITS_WATT)                        { val = EGdtf_RDMParam_SensorUnit::UNITS_WATT;}
    else if (value == XML_GDTF_RDMParam_SensorUnit_UNITS_KILOGRAM)                    { val = EGdtf_RDMParam_SensorUnit::UNITS_KILOGRAM;}
    else if (value == XML_GDTF_RDMParam_SensorUnit_UNITS_METERS)                      { val = EGdtf_RDMParam_SensorUnit::UNITS_METERS;}
    else if (value == XML_GDTF_RDMParam_SensorUnit_UNITS_METERS_SQUARED)              { val = EGdtf_RDMParam_SensorUnit::UNITS_METERS_SQUARED;}
    else if (value == XML_GDTF_RDMParam_SensorUnit_UNITS_METERS_CUBED)                { val = EGdtf_RDMParam_SensorUnit::UNITS_METERS_CUBED;}
    else if (value == XML_GDTF_RDMParam_SensorUnit_UNITS_KILOGRAMMES_PER_METER_CUBED) { val = EGdtf_RDMParam_SensorUnit::UNITS_KILOGRAMMES_PER_METER_CUBED;}
    else if (value == XML_GDTF_RDMParam_SensorUnit_UNITS_METERS_PER_SECOND)           { val = EGdtf_RDMParam_SensorUnit::UNITS_METERS_PER_SECOND;}
    else if (value == XML_GDTF_RDMParam_SensorUnit_UNITS_METERS_PER_SECOND_SQUARED)   { val = EGdtf_RDMParam_SensorUnit::UNITS_METERS_PER_SECOND_SQUARED;}
    else if (value == XML_GDTF_RDMParam_SensorUnit_UNITS_NEWTON)                      { val = EGdtf_RDMParam_SensorUnit::UNITS_NEWTON;}
    else if (value == XML_GDTF_RDMParam_SensorUnit_UNITS_JOULE)                       { val = EGdtf_RDMParam_SensorUnit::UNITS_JOULE;}
    else if (value == XML_GDTF_RDMParam_SensorUnit_UNITS_PASCAL)                      { val = EGdtf_RDMParam_SensorUnit::UNITS_PASCAL;}
    else if (value == XML_GDTF_RDMParam_SensorUnit_UNITS_SECOND)                      { val = EGdtf_RDMParam_SensorUnit::UNITS_SECOND;}
    else if (value == XML_GDTF_RDMParam_SensorUnit_UNITS_DEGREE)                      { val = EGdtf_RDMParam_SensorUnit::UNITS_DEGREE;}
    else if (value == XML_GDTF_RDMParam_SensorUnit_UNITS_STERADIAN)                   { val = EGdtf_RDMParam_SensorUnit::UNITS_STERADIAN;}
    else if (value == XML_GDTF_RDMParam_SensorUnit_UNITS_CANDELA)                     { val = EGdtf_RDMParam_SensorUnit::UNITS_CANDELA;}
    else if (value == XML_GDTF_RDMParam_SensorUnit_UNITS_LUMEN)                       { val = EGdtf_RDMParam_SensorUnit::UNITS_LUMEN;}
    else if (value == XML_GDTF_RDMParam_SensorUnit_UNITS_LUX)                         { val = EGdtf_RDMParam_SensorUnit::UNITS_LUX;}
    else if (value == XML_GDTF_RDMParam_SensorUnit_UNITS_IRE)                         { val = EGdtf_RDMParam_SensorUnit::UNITS_IRE;}
    else if (value == XML_GDTF_RDMParam_SensorUnit_UNITS_BYTE)                        { val = EGdtf_RDMParam_SensorUnit::UNITS_BYTE;}
    else if (value == XML_GDTF_RDMParam_SensorUnit_UNITS_MS)                          { val = EGdtf_RDMParam_SensorUnit::UNITS_MS;}
    else
    {
        val = EGdtf_RDMParam_SensorUnit::UNITS_NONE;   // TODO: Theres no default value at the moment check this later again. (19.10)
        DSTOP((kEveryone, "Unaspected Input for Convert_RDMParam_SensorUnitEnum Enum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_RDMParamNoMatchingEntry);
        SceneData::GdtfFixture::AddError(error);
    }

    // Return true
    return true;
}

/*static*/ TXString GdtfConverter::Convert_RDMParam_SensorUnitPrefixEnum(EGdtf_RDMParam_SensorUnitPrefix value)
{
    switch (value)
    {
    case EGdtf_RDMParam_SensorUnitPrefix::PREFIX_NONE:			return XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_NONE;
    case EGdtf_RDMParam_SensorUnitPrefix::PREFIX_DECI:			return XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_DECI;
    case EGdtf_RDMParam_SensorUnitPrefix::PREFIX_CENTI:			return XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_CENTI;
    case EGdtf_RDMParam_SensorUnitPrefix::PREFIX_MILLI:			return XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_MILLI;
    case EGdtf_RDMParam_SensorUnitPrefix::PREFIX_MICRO:			return XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_MICRO;
    case EGdtf_RDMParam_SensorUnitPrefix::PREFIX_NANO:			return XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_NANO;
    case EGdtf_RDMParam_SensorUnitPrefix::PREFIX_PICO:			return XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_PICO;
    case EGdtf_RDMParam_SensorUnitPrefix::PREFIX_FEMPTO:		return XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_FEMPTO;
    case EGdtf_RDMParam_SensorUnitPrefix::PREFIX_ATTO:			return XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_ATTO;
    case EGdtf_RDMParam_SensorUnitPrefix::PREFIX_ZEPTO:			return XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_ZEPTO;
    case EGdtf_RDMParam_SensorUnitPrefix::PREFIX_YOCTO:			return XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_YOCTO;
    case EGdtf_RDMParam_SensorUnitPrefix::PREFIX_DECA:			return XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_DECA;
    case EGdtf_RDMParam_SensorUnitPrefix::PREFIX_HECTO:			return XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_HECTO;
    case EGdtf_RDMParam_SensorUnitPrefix::PREFIX_KILO:			return XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_KILO;
    case EGdtf_RDMParam_SensorUnitPrefix::PREFIX_MEGA:			return XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_MEGA;
    case EGdtf_RDMParam_SensorUnitPrefix::PREFIX_GIGA:			return XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_GIGA;
    case EGdtf_RDMParam_SensorUnitPrefix::PREFIX_TERRA:			return XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_TERRA;
    case EGdtf_RDMParam_SensorUnitPrefix::PREFIX_PETA:			return XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_PETA;
    case EGdtf_RDMParam_SensorUnitPrefix::PREFIX_EXA:			return XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_EXA;
    case EGdtf_RDMParam_SensorUnitPrefix::PREFIX_ZETTA:			return XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_ZETTA;
    case EGdtf_RDMParam_SensorUnitPrefix::PREFIX_YOTTA:			return XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_YOTTA;    
    default: DSTOP((kEveryone, "Convert_RDMParam_SensorUnitPrefixEnum: Invalid Input-Value"));
    }
    
    // Default
    return XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_NONE; // TODO: Theres no default value at the moment check this later again. (19.10)
}

/*static*/ bool GdtfConverter::Convert_RDMParam_SensorUnitPrefixEnum(const TXString& value, EGdtf_RDMParam_SensorUnitPrefix& val)
{    
    if      (value == XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_NONE)   { val =  EGdtf_RDMParam_SensorUnitPrefix::PREFIX_NONE;}
    else if (value == XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_DECI)   { val =  EGdtf_RDMParam_SensorUnitPrefix::PREFIX_DECI;}
    else if (value == XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_CENTI)  { val =  EGdtf_RDMParam_SensorUnitPrefix::PREFIX_CENTI;}
    else if (value == XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_MILLI)  { val =  EGdtf_RDMParam_SensorUnitPrefix::PREFIX_MILLI;}
    else if (value == XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_MICRO)  { val =  EGdtf_RDMParam_SensorUnitPrefix::PREFIX_MICRO;}
    else if (value == XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_NANO)   { val =  EGdtf_RDMParam_SensorUnitPrefix::PREFIX_NANO;}
    else if (value == XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_PICO)   { val =  EGdtf_RDMParam_SensorUnitPrefix::PREFIX_PICO;}
    else if (value == XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_FEMPTO) { val =  EGdtf_RDMParam_SensorUnitPrefix::PREFIX_FEMPTO;}
    else if (value == XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_ATTO)   { val =  EGdtf_RDMParam_SensorUnitPrefix::PREFIX_ATTO;}
    else if (value == XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_ZEPTO)  { val =  EGdtf_RDMParam_SensorUnitPrefix::PREFIX_ZEPTO;}
    else if (value == XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_YOCTO)  { val =  EGdtf_RDMParam_SensorUnitPrefix::PREFIX_YOCTO;}
    else if (value == XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_DECA)   { val =  EGdtf_RDMParam_SensorUnitPrefix::PREFIX_DECA;}
    else if (value == XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_HECTO)  { val =  EGdtf_RDMParam_SensorUnitPrefix::PREFIX_HECTO;}
    else if (value == XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_KILO)   { val =  EGdtf_RDMParam_SensorUnitPrefix::PREFIX_KILO;}
    else if (value == XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_MEGA)   { val =  EGdtf_RDMParam_SensorUnitPrefix::PREFIX_MEGA;}
    else if (value == XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_GIGA)   { val =  EGdtf_RDMParam_SensorUnitPrefix::PREFIX_GIGA;}
    else if (value == XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_TERRA)  { val =  EGdtf_RDMParam_SensorUnitPrefix::PREFIX_TERRA;}
    else if (value == XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_PETA)   { val =  EGdtf_RDMParam_SensorUnitPrefix::PREFIX_PETA;}
    else if (value == XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_EXA)    { val =  EGdtf_RDMParam_SensorUnitPrefix::PREFIX_EXA;}
    else if (value == XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_ZETTA)  { val =  EGdtf_RDMParam_SensorUnitPrefix::PREFIX_ZETTA;}
    else if (value == XML_GDTF_RDMParam_SensorUnitPrefix_PREFIX_YOTTA)  { val =  EGdtf_RDMParam_SensorUnitPrefix::PREFIX_YOTTA;}
    else
    {
        val = EGdtf_RDMParam_SensorUnitPrefix::PREFIX_NONE;   // TODO: Theres no default value at the moment check this later again. (19.10)
        DSTOP((kEveryone, "Unaspected Input for Convert_RDMParam_SensorUnitPrefixEnum Enum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_RDMParamNoMatchingEntry);
        SceneData::GdtfFixture::AddError(error);
    }

    return true;
}


/*static*/ TXString GdtfConverter::ConvertEGdtf_RDMValueBool_ValueEnum(EGdtf_RDMValueBool_Value value)
{
    switch (value)
    {
    case EGdtf_RDMValueBool_Value::eYes:			return XML_GDTF_RDMValueBool_Value_YES;
    case EGdtf_RDMValueBool_Value::eNo:			return XML_GDTF_RDMValueBool_Value_NO;
    default: DSTOP((kEveryone, "ConvertEGdtf_RDMValueBool_ValueEnum: Invalid Input-Value"));
    }

    // Default
    return XML_GDTF_RDMValueBool_Value_YES; // TODO: Theres no default value at the moment check this later again. (19.10)
}

/*static*/ bool GdtfConverter::ConvertEGdtf_RDMValueBool_ValueEnum(const TXString& value, EGdtf_RDMValueBool_Value&	val)
{
    if      (value == XML_GDTF_RDMValueBool_Value_YES) { val = EGdtf_RDMValueBool_Value::eYes; }
    else if (value == XML_GDTF_RDMValueBool_Value_NO)  { val = EGdtf_RDMValueBool_Value::eNo; }
    else
    {
        val = EGdtf_RDMValueBool_Value::eYes;   // TODO: Theres no default value at the moment check this later again. (19.10)
        DSTOP((kEveryone, "Unaspected Input for ConvertEGdtf_RDMValueBool_ValueEnum Enum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_RDMParamNoMatchingEntry);
        SceneData::GdtfFixture::AddError(error);
    }
        
    return true;
}

/*static*/ TXString GdtfConverter::ConvertEGdtf_RDMValue_ThresholdOperatorEnum(EGdtf_RDMValue_ThresholdOperator value)
{
    switch (value)
    {
    case EGdtf_RDMValue_ThresholdOperator::Is:		    	return XML_GDTF_ThresholdOperator_Is;
    case EGdtf_RDMValue_ThresholdOperator::IsNot:			return XML_GDTF_ThresholdOperator_IsNot;
    case EGdtf_RDMValue_ThresholdOperator::Greater:			return XML_GDTF_ThresholdOperator_Greater;
    case EGdtf_RDMValue_ThresholdOperator::Less:			return XML_GDTF_ThresholdOperator_Less;
    default: DSTOP((kEveryone, "ConvertEGdtf_RDMValue_ThresholdOperatorEnum: Invalid Input-Value"));
    }

    // Default
    return XML_GDTF_ThresholdOperator_Is; // TODO: Theres no default value at the moment check this later again. (19.10)
}

/*static*/ bool GdtfConverter::ConvertEGdtf_RDMValue_ThresholdOperatorEnum(const TXString& value, EGdtf_RDMValue_ThresholdOperator& val)
{
    if      (value == XML_GDTF_ThresholdOperator_Is)      { val = EGdtf_RDMValue_ThresholdOperator::Is; }
    else if (value == XML_GDTF_ThresholdOperator_IsNot)   { val = EGdtf_RDMValue_ThresholdOperator::IsNot; }
    else if (value == XML_GDTF_ThresholdOperator_Greater) { val = EGdtf_RDMValue_ThresholdOperator::Greater; }
    else if (value == XML_GDTF_ThresholdOperator_Less)    { val = EGdtf_RDMValue_ThresholdOperator::Less; }
    else
    {
        val = EGdtf_RDMValue_ThresholdOperator::Is;   // TODO: Theres no default value at the moment check this later again. (19.10)
        DSTOP((kEveryone, "Unaspected Input for ConvertEGdtf_RDMValue_ThresholdOperatorEnum Enum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_RDMParamNoMatchingEntry);
        SceneData::GdtfFixture::AddError(error);
    }

    // Return true
    return true;
}

/*static*/ TXString GdtfConverter::ConvertRDMValue_SENSOR_DEFINITION_TypeEnum(EGdtf_RDMValue_SENSOR_DEFINITION_TYPE value)
{
    switch (value)
    {
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_TEMPERATURE: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_TEMPERATURE;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_VOLTAGE: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_VOLTAGE;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_CURRENT: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_CURRENT;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_FREQUENCY: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_FREQUENCY;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_RESISTANCE: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_RESISTANCE;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_POWER: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_POWER;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_MASS: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_MASS;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_LENGTH: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_LENGTH;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_AREA: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_AREA;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_VOLUME: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_VOLUME;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_DENSITY: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_DENSITY;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_VELOCITY: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_VELOCITY;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_ACCELERATION: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_ACCELERATION;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_FORCE: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_FORCE;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_ENERGY: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_ENERGY;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_PRESSURE: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_PRESSURE;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_TIME: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_TIME;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_ANGLE: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_ANGLE;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_POSITION_X: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_POSITION_X;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_POSITION_Y: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_POSITION_Y;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_POSITION_Z: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_POSITION_Z;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_ANGULAR_VELOCITY: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_ANGULAR_VELOCITY;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_LUMINOUS_INTENSITY: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_LUMINOUS_INTENSITY;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_LUMINOUS_FLUX: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_LUMINOUS_FLUX;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_ILLUMINANCE: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_ILLUMINANCE;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_CHROMINANCE_RED: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_CHROMINANCE_RED;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_CHROMINANCE_GREEN: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_CHROMINANCE_GREEN;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_CHROMINANCE_BLUE: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_CHROMINANCE_BLUE;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_CONTACTS: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_CONTACTS;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_MEMORY: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_MEMORY;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_ITEMS: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_ITEMS;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_HUMIDITY: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_HUMIDITY;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_COUNTER_16BIT: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_COUNTER_16BIT;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_OTHER: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_OTHER;
    case EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_MS: return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_MS;
    default: DSTOP((kEveryone, "ConvertRDMValue_SENSOR_DEFINITION_TypeEnum: Invalid Input-Value"));
    }        

    // Default
    return XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_TEMPERATURE; // TODO: Theres no default value at the moment check this later again. (19.10)
}

/*static*/ bool GdtfConverter::ConvertRDMValue_SENSOR_DEFINITION_TypeEnum(const TXString& value, EGdtf_RDMValue_SENSOR_DEFINITION_TYPE&			val)
{    
    if      (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_TEMPERATURE)           { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_TEMPERATURE; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_VOLTAGE)               { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_VOLTAGE; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_CURRENT)               { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_CURRENT; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_FREQUENCY)             { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_FREQUENCY; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_RESISTANCE)            { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_RESISTANCE; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_POWER)                 { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_POWER; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_MASS)                  { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_MASS; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_LENGTH)                { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_LENGTH; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_AREA)                  { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_AREA; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_VOLUME)                { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_VOLUME; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_DENSITY)               { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_DENSITY; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_VELOCITY)              { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_VELOCITY; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_ACCELERATION)          { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_ACCELERATION; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_FORCE)                 { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_FORCE; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_ENERGY)                { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_ENERGY; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_PRESSURE)              { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_PRESSURE; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_TIME)                  { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_TIME; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_ANGLE)                 { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_ANGLE; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_POSITION_X)            { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_POSITION_X; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_POSITION_Y)            { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_POSITION_Y; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_POSITION_Z)            { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_POSITION_Z; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_ANGULAR_VELOCITY)      { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_ANGULAR_VELOCITY; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_LUMINOUS_INTENSITY)    { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_LUMINOUS_INTENSITY; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_LUMINOUS_FLUX)         { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_LUMINOUS_FLUX; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_ILLUMINANCE)           { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_ILLUMINANCE; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_CHROMINANCE_RED)       { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_CHROMINANCE_RED; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_CHROMINANCE_GREEN)     { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_CHROMINANCE_GREEN; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_CHROMINANCE_BLUE)      { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_CHROMINANCE_BLUE; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_CONTACTS)              { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_CONTACTS; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_MEMORY)                { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_MEMORY; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_ITEMS)                 { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_ITEMS; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_HUMIDITY)              { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_HUMIDITY; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_COUNTER_16BIT)         { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_COUNTER_16BIT; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_OTHER)                 { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_OTHER; }
    else if (value == XML_GDTF_RDMValue_SENSOR_DEFINITION_TYPE_ENUM_SEND_MS)                    { val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_MS; }
    else
    {
        val = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_TEMPERATURE;   // TODO: Theres no default value at the moment check this later again. (19.10)
        DSTOP((kEveryone, "Unaspected Input for ConvertRDMValue_SENSOR_DEFINITION_TypeEnum Enum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_RDMParamNoMatchingEntry);
        SceneData::GdtfFixture::AddError(error);
    }
       
    return true;
}

/*static*/ TXString GdtfConverter::Convert_RDMValue_LowesHighestDetectionSupportedEnum(EGdtf_RDMValue_LowesHighestDetectionSupported value)
{
    switch (value)
    {
    case EGdtf_RDMValue_LowesHighestDetectionSupported::eYES:	return XML_GDTF_RDMValue_LowesHighestDetectionSupported_ENUM_YES;
    case EGdtf_RDMValue_LowesHighestDetectionSupported::eNO:     return XML_GDTF_RDMValue_LowesHighestDetectionSupported_ENUM_NO;
    default: DSTOP((kEveryone, "Convert_RDMValue_LowesHighestDetectionSupportedEnum: Invalid Input-Value"));
    }   
    
    return XML_GDTF_RDMValue_LowesHighestDetectionSupported_ENUM_YES; // TODO: Theres no default value at the moment check this later again. (19.10)
}

/*static*/ bool GdtfConverter::Convert_RDMValue_LowesHighestDetectionSupportedEnum(const TXString& value, EGdtf_RDMValue_LowesHighestDetectionSupported&			val)
{
    if      (value == XML_GDTF_RDMValue_LowesHighestDetectionSupported_ENUM_YES) { val = EGdtf_RDMValue_LowesHighestDetectionSupported::eYES; }
    else if (value == XML_GDTF_RDMValue_LowesHighestDetectionSupported_ENUM_NO)  { val = EGdtf_RDMValue_LowesHighestDetectionSupported::eNO; }
    else
    {
        val = val = EGdtf_RDMValue_LowesHighestDetectionSupported::eYES;   // TODO: Theres no default value at the moment check this later again. (19.10)
        DSTOP((kEveryone, "Unaspected Input for Convert_RDMValue_LowesHighestDetectionSupportedEnum."));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_RDMParamNoMatchingEntry);
        SceneData::GdtfFixture::AddError(error);
    }

    return true;
}

/*static*/ TXString GdtfConverter::Convert_RDMValue_RecordValueSupportedEnum(EGdtf_RDMValue_RecordValueSupported value)
{
    switch (value)
    {
    case EGdtf_RDMValue_RecordValueSupported::eYES:			return XML_GDTF_RDMValue_RecordValueSupported_ENUM_YES;
    case EGdtf_RDMValue_RecordValueSupported::eNO:			return XML_GDTF_RDMValue_RecordValueSupported_ENUM_NO;
    default: DSTOP((kEveryone, "Convert_RDMValue_RecordValueSupportedEnum: Invalid Input-Value"));
    }
    
    // Default
    return XML_GDTF_RDMValue_RecordValueSupported_ENUM_YES; // TODO: Theres no default value at the moment check this later again. (19.10)
}

/*static*/ bool GdtfConverter::Convert_RDMValue_RecordValueSupportedEnum(const TXString& value, EGdtf_RDMValue_RecordValueSupported& val)
{
    if      (value == XML_GDTF_RDMValue_RecordValueSupported_ENUM_YES) { val = EGdtf_RDMValue_RecordValueSupported::eYES; }
    else if (value == XML_GDTF_RDMValue_RecordValueSupported_ENUM_NO)  { val = EGdtf_RDMValue_RecordValueSupported::eNO; }
    else
    {
        val = EGdtf_RDMValue_RecordValueSupported::eYES;   // TODO: Theres no default value at the moment check this later again. (19.10)
        DSTOP((kEveryone, "Unaspected Input for Convert_RDMValue_RecordValueSupportedEnum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_RDMParamNoMatchingEntry);
        SceneData::GdtfFixture::AddError(error);
    }

    return true;
}

/*static*/ TXString GdtfConverter::ConvertRDMValue_SLOT_INFO_TypeEnum(EGdtf_RDMValue_SLOT_INFO_Type value)
{
    switch (value)
    {    
    case EGdtf_RDMValue_SLOT_INFO_Type::ST_PRIMARY:           return XML_GDTF_SLOT_INFO_Type_ENUM_ST_PRIMARY;
    case EGdtf_RDMValue_SLOT_INFO_Type::ST_SEC_FINE:          return XML_GDTF_SLOT_INFO_Type_ENUM_ST_SEC_FINE;
    case EGdtf_RDMValue_SLOT_INFO_Type::ST_SEC_TIMING:        return XML_GDTF_SLOT_INFO_Type_ENUM_ST_SEC_TIMING;
    case EGdtf_RDMValue_SLOT_INFO_Type::ST_SEC_SPEED:         return XML_GDTF_SLOT_INFO_Type_ENUM_ST_SEC_SPEED;
    case EGdtf_RDMValue_SLOT_INFO_Type::ST_SEC_CONTROL:       return XML_GDTF_SLOT_INFO_Type_ENUM_ST_SEC_CONTROL;
    case EGdtf_RDMValue_SLOT_INFO_Type::ST_SEC_INDEX:         return XML_GDTF_SLOT_INFO_Type_ENUM_ST_SEC_INDEX;
    case EGdtf_RDMValue_SLOT_INFO_Type::ST_SEC_ROTATION:      return XML_GDTF_SLOT_INFO_Type_ENUM_ST_SEC_ROTATION;
    case EGdtf_RDMValue_SLOT_INFO_Type::ST_SEC_INDEX_ROTATE:  return XML_GDTF_SLOT_INFO_Type_ENUM_ST_SEC_INDEX_ROTATE;
    case EGdtf_RDMValue_SLOT_INFO_Type::ST_SEC_UNDEFINED:     return XML_GDTF_SLOT_INFO_Type_ENUM_ST_SEC_UNDEFINED;
    default: DSTOP((kEveryone, "ConvertRDMValue_SLOT_INFO_TypeEnum: Invalid Input-Value"));
    }

    // Default
    return XML_GDTF_SLOT_INFO_Type_ENUM_ST_PRIMARY; // TODO: Theres no default value at the moment check this later again. (19.10)
}

/*static*/ bool GdtfConverter::ConvertRDMValue_SLOT_INFO_TypeEnum(const TXString& value, EGdtf_RDMValue_SLOT_INFO_Type&	val)
{
    if      (value == XML_GDTF_SLOT_INFO_Type_ENUM_ST_PRIMARY) { val = EGdtf_RDMValue_SLOT_INFO_Type::ST_PRIMARY; }
    else if (value == XML_GDTF_SLOT_INFO_Type_ENUM_ST_SEC_FINE) { val = EGdtf_RDMValue_SLOT_INFO_Type::ST_SEC_FINE; }
    else if (value == XML_GDTF_SLOT_INFO_Type_ENUM_ST_SEC_TIMING) { val = EGdtf_RDMValue_SLOT_INFO_Type::ST_SEC_TIMING; }
    else if (value == XML_GDTF_SLOT_INFO_Type_ENUM_ST_SEC_SPEED) { val = EGdtf_RDMValue_SLOT_INFO_Type::ST_SEC_SPEED; }
    else if (value == XML_GDTF_SLOT_INFO_Type_ENUM_ST_SEC_CONTROL) { val = EGdtf_RDMValue_SLOT_INFO_Type::ST_SEC_CONTROL; }
    else if (value == XML_GDTF_SLOT_INFO_Type_ENUM_ST_SEC_INDEX) { val = EGdtf_RDMValue_SLOT_INFO_Type::ST_SEC_INDEX; }
    else if (value == XML_GDTF_SLOT_INFO_Type_ENUM_ST_SEC_ROTATION) { val = EGdtf_RDMValue_SLOT_INFO_Type::ST_SEC_ROTATION; }
    else if (value == XML_GDTF_SLOT_INFO_Type_ENUM_ST_SEC_INDEX_ROTATE) { val = EGdtf_RDMValue_SLOT_INFO_Type::ST_SEC_INDEX_ROTATE; }
    else if (value == XML_GDTF_SLOT_INFO_Type_ENUM_ST_SEC_UNDEFINED) { val = EGdtf_RDMValue_SLOT_INFO_Type::ST_SEC_UNDEFINED; }
    else
    {
        val = EGdtf_RDMValue_SLOT_INFO_Type::ST_PRIMARY;   // TODO: Theres no default value at the moment check this later again. (19.10)
        DSTOP((kEveryone, "Unaspected Input for ConvertRDMValue_SLOT_INFO_TypeEnum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_RDMParamNoMatchingEntry);
        SceneData::GdtfFixture::AddError(error);
    }

    return true;
}

/*static*/ TXString GdtfConverter::ConvertRDMValue_SLOT_INFO_SlotLabelIDEnum(EGdtf_RDMValue_SLOT_INFO_SlotLabelID value)
{
    switch (value)
    {    
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_INTENSITY:                return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_INTENSITY;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_INTENSITY_MASTER:         return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_INTENSITY_MASTER;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_PAN:                      return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_PAN;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_TILT:                     return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_TILT;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_WHEEL:              return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_WHEEL;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_SUB_CYAN:           return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_SUB_CYAN;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_SUB_YELLOW:         return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_SUB_YELLOW;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_SUB_MAGENTA:        return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_SUB_MAGENTA;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_ADD_RED:            return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_ADD_RED;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_ADD_GREEN:          return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_ADD_GREEN;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_ADD_BLUE:           return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_ADD_BLUE;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_CORRECTION:         return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_CORRECTION;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_SCROLL:             return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_SCROLL;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_SEMAPHORE:          return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_SEMAPHORE;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_ADD_AMBER:          return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_ADD_AMBER;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_ADD_WHITE:          return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_ADD_WHITE;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_ADD_WARM_WHITE:     return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_ADD_WARM_WHITE;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_ADD_COOL_WHITE:     return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_ADD_COOL_WHITE;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_SUB_UV:             return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_SUB_UV;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_HUE:                return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_HUE;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_SATURATION:         return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_SATURATION;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_STATIC_GOBO_WHEEL:        return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_STATIC_GOBO_WHEEL;                                                                                       
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_ROTO_GOBO_WHEEL:          return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_ROTO_GOBO_WHEEL;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_PRISM_WHEEL:              return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_PRISM_WHEEL;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_EFFECTS_WHEEL:            return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_EFFECTS_WHEEL;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_BEAM_SIZE_IRIS:           return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_BEAM_SIZE_IRIS;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_EDGE:                     return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_EDGE;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_FROST:                    return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_FROST;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_STROBE:                   return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_STROBE;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_ZOOM:                     return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_ZOOM;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_FRAMING_SHUTTER:          return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_FRAMING_SHUTTER;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_SHUTTER_ROTATE:           return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_SHUTTER_ROTATE;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_DOUSER:                   return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_DOUSER;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_BARN_DOOR:                return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_BARN_DOOR;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_LAMP_CONTROL:             return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_LAMP_CONTROL;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_FIXTURE_CONTROL:          return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_FIXTURE_CONTROL;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_FIXTURE_SPEED:            return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_FIXTURE_SPEED;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_MACRO:                    return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_MACRO;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_POWER_CONTROL:            return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_POWER_CONTROL;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_FAN_CONTROL:              return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_FAN_CONTROL;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_HEATER_CONTROL:           return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_HEATER_CONTROL;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_FOUNTAIN_CONTROL:         return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_FOUNTAIN_CONTROL;
        case EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_UNDEFINED:                return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_UNDEFINED;
        default: DSTOP((kEveryone, "ConvertRDMValue_SLOT_INFO_SlotLabelIDEnum: Invalid Input-Value"));
    }
        
    return XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_INTENSITY; // TODO: Theres no default value at the moment check this later again. (19.10)
}


/*static*/ bool GdtfConverter::ConvertRDMValue_SLOT_INFO_SlotLabelIDEnum(const TXString& value, EGdtf_RDMValue_SLOT_INFO_SlotLabelID&	val)
{           
    if      (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_INTENSITY) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_INTENSITY; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_INTENSITY_MASTER) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_INTENSITY_MASTER; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_PAN) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_PAN; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_TILT) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_TILT; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_WHEEL) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_WHEEL; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_SUB_CYAN) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_SUB_CYAN; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_SUB_YELLOW) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_SUB_YELLOW; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_SUB_MAGENTA) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_SUB_MAGENTA; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_ADD_RED) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_ADD_RED; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_ADD_GREEN) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_ADD_GREEN; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_ADD_BLUE) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_ADD_BLUE; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_CORRECTION) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_CORRECTION; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_SCROLL) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_SCROLL; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_SEMAPHORE) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_SEMAPHORE; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_ADD_AMBER) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_ADD_AMBER; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_ADD_WHITE) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_ADD_WHITE; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_ADD_WARM_WHITE) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_ADD_WARM_WHITE; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_ADD_COOL_WHITE) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_ADD_COOL_WHITE; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_SUB_UV) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_SUB_UV; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_HUE) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_HUE; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_COLOR_SATURATION) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_COLOR_SATURATION; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_STATIC_GOBO_WHEEL) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_STATIC_GOBO_WHEEL; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_ROTO_GOBO_WHEEL) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_ROTO_GOBO_WHEEL; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_PRISM_WHEEL) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_PRISM_WHEEL; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_EFFECTS_WHEEL) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_EFFECTS_WHEEL; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_BEAM_SIZE_IRIS) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_BEAM_SIZE_IRIS; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_EDGE) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_EDGE; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_FROST) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_FROST; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_STROBE) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_STROBE; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_ZOOM) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_ZOOM; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_FRAMING_SHUTTER) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_FRAMING_SHUTTER; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_SHUTTER_ROTATE) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_SHUTTER_ROTATE; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_DOUSER) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_DOUSER; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_BARN_DOOR) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_BARN_DOOR; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_LAMP_CONTROL) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_LAMP_CONTROL; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_FIXTURE_CONTROL) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_FIXTURE_CONTROL; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_FIXTURE_SPEED) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_FIXTURE_SPEED; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_MACRO) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_MACRO; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_POWER_CONTROL) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_POWER_CONTROL; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_FAN_CONTROL) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_FAN_CONTROL; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_HEATER_CONTROL) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_HEATER_CONTROL; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_FOUNTAIN_CONTROL) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_FOUNTAIN_CONTROL; }
    else if (value == XML_GDTF_SLOT_INFO_SlotLabelID_ENUM_SD_UNDEFINED) { val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_UNDEFINED; }    
    else
    {
        val = EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_INTENSITY;   // TODO: Theres no default value at the moment check this later again. (19.10)
        DSTOP((kEveryone, "Unaspected Input for ConvertRDMValue_SLOT_INFO_SlotLabelIDEnum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_RDMParamNoMatchingEntry);
        SceneData::GdtfFixture::AddError(error);
    }

    return true;
}

/*static*/ TXString GdtfConverter::ConvertEGdtfColorSampleEnum(EGdtfColorSample value)
{
    switch (value)
    {
    case EGdtfColorSample::CES_01:			return XML_GDTF_ColorSample_1;
    case EGdtfColorSample::CES_02:			return XML_GDTF_ColorSample_2;
    case EGdtfColorSample::CES_03:			return XML_GDTF_ColorSample_3;
    case EGdtfColorSample::CES_04:			return XML_GDTF_ColorSample_4;
    case EGdtfColorSample::CES_05:			return XML_GDTF_ColorSample_5;
    case EGdtfColorSample::CES_06:			return XML_GDTF_ColorSample_6;
    case EGdtfColorSample::CES_07:			return XML_GDTF_ColorSample_7;
    case EGdtfColorSample::CES_08:			return XML_GDTF_ColorSample_8;
    case EGdtfColorSample::CES_09:			return XML_GDTF_ColorSample_9;
    case EGdtfColorSample::CES_10:			return XML_GDTF_ColorSample_10;
    case EGdtfColorSample::CES_11:			return XML_GDTF_ColorSample_11;
    case EGdtfColorSample::CES_12:			return XML_GDTF_ColorSample_12;
    case EGdtfColorSample::CES_13:			return XML_GDTF_ColorSample_13;
    case EGdtfColorSample::CES_14:			return XML_GDTF_ColorSample_14;
    case EGdtfColorSample::CES_15:			return XML_GDTF_ColorSample_15;
    case EGdtfColorSample::CES_16:			return XML_GDTF_ColorSample_16;
    case EGdtfColorSample::CES_17:			return XML_GDTF_ColorSample_17;
    case EGdtfColorSample::CES_18:			return XML_GDTF_ColorSample_18;
    case EGdtfColorSample::CES_19:			return XML_GDTF_ColorSample_19;
    case EGdtfColorSample::CES_20:			return XML_GDTF_ColorSample_20;
    case EGdtfColorSample::CES_21:			return XML_GDTF_ColorSample_21;
    case EGdtfColorSample::CES_22:			return XML_GDTF_ColorSample_22;
    case EGdtfColorSample::CES_23:			return XML_GDTF_ColorSample_23;
    case EGdtfColorSample::CES_24:			return XML_GDTF_ColorSample_24;
    case EGdtfColorSample::CES_25:			return XML_GDTF_ColorSample_25;
    case EGdtfColorSample::CES_26:			return XML_GDTF_ColorSample_26;
    case EGdtfColorSample::CES_27:			return XML_GDTF_ColorSample_27;
    case EGdtfColorSample::CES_28:			return XML_GDTF_ColorSample_28;
    case EGdtfColorSample::CES_29:			return XML_GDTF_ColorSample_29;
    case EGdtfColorSample::CES_30:			return XML_GDTF_ColorSample_30;
    case EGdtfColorSample::CES_31:			return XML_GDTF_ColorSample_31;
    case EGdtfColorSample::CES_32:			return XML_GDTF_ColorSample_32;
    case EGdtfColorSample::CES_33:			return XML_GDTF_ColorSample_33;
    case EGdtfColorSample::CES_34:			return XML_GDTF_ColorSample_34;
    case EGdtfColorSample::CES_35:			return XML_GDTF_ColorSample_35;
    case EGdtfColorSample::CES_36:			return XML_GDTF_ColorSample_36;
    case EGdtfColorSample::CES_37:			return XML_GDTF_ColorSample_37;
    case EGdtfColorSample::CES_38:			return XML_GDTF_ColorSample_38;
    case EGdtfColorSample::CES_39:			return XML_GDTF_ColorSample_39;
    case EGdtfColorSample::CES_40:			return XML_GDTF_ColorSample_40;
    case EGdtfColorSample::CES_41:			return XML_GDTF_ColorSample_41;
    case EGdtfColorSample::CES_42:			return XML_GDTF_ColorSample_42;
    case EGdtfColorSample::CES_43:			return XML_GDTF_ColorSample_43;
    case EGdtfColorSample::CES_44:			return XML_GDTF_ColorSample_44;
    case EGdtfColorSample::CES_45:			return XML_GDTF_ColorSample_45;
    case EGdtfColorSample::CES_46:			return XML_GDTF_ColorSample_46;
    case EGdtfColorSample::CES_47:			return XML_GDTF_ColorSample_47;
    case EGdtfColorSample::CES_48:			return XML_GDTF_ColorSample_48;
    case EGdtfColorSample::CES_49:			return XML_GDTF_ColorSample_49;
    case EGdtfColorSample::CES_50:			return XML_GDTF_ColorSample_50;
    case EGdtfColorSample::CES_51:			return XML_GDTF_ColorSample_51;
    case EGdtfColorSample::CES_52:			return XML_GDTF_ColorSample_52;
    case EGdtfColorSample::CES_53:			return XML_GDTF_ColorSample_53;
    case EGdtfColorSample::CES_54:			return XML_GDTF_ColorSample_54;
    case EGdtfColorSample::CES_55:			return XML_GDTF_ColorSample_55;
    case EGdtfColorSample::CES_56:			return XML_GDTF_ColorSample_56;
    case EGdtfColorSample::CES_57:			return XML_GDTF_ColorSample_57;
    case EGdtfColorSample::CES_58:			return XML_GDTF_ColorSample_58;
    case EGdtfColorSample::CES_59:			return XML_GDTF_ColorSample_59;
    case EGdtfColorSample::CES_60:			return XML_GDTF_ColorSample_60;
    case EGdtfColorSample::CES_61:			return XML_GDTF_ColorSample_61;
    case EGdtfColorSample::CES_62:			return XML_GDTF_ColorSample_62;
    case EGdtfColorSample::CES_63:			return XML_GDTF_ColorSample_63;
    case EGdtfColorSample::CES_64:			return XML_GDTF_ColorSample_64;
    case EGdtfColorSample::CES_65:			return XML_GDTF_ColorSample_65;
    case EGdtfColorSample::CES_66:			return XML_GDTF_ColorSample_66;
    case EGdtfColorSample::CES_67:			return XML_GDTF_ColorSample_67;
    case EGdtfColorSample::CES_68:			return XML_GDTF_ColorSample_68;
    case EGdtfColorSample::CES_69:			return XML_GDTF_ColorSample_69;
    case EGdtfColorSample::CES_70:			return XML_GDTF_ColorSample_70;
    case EGdtfColorSample::CES_71:			return XML_GDTF_ColorSample_71;
    case EGdtfColorSample::CES_72:			return XML_GDTF_ColorSample_72;
    case EGdtfColorSample::CES_73:			return XML_GDTF_ColorSample_73;
    case EGdtfColorSample::CES_74:			return XML_GDTF_ColorSample_74;
    case EGdtfColorSample::CES_75:			return XML_GDTF_ColorSample_75;
    case EGdtfColorSample::CES_76:			return XML_GDTF_ColorSample_76;
    case EGdtfColorSample::CES_77:			return XML_GDTF_ColorSample_77;
    case EGdtfColorSample::CES_78:			return XML_GDTF_ColorSample_78;
    case EGdtfColorSample::CES_79:			return XML_GDTF_ColorSample_79;
    case EGdtfColorSample::CES_80:			return XML_GDTF_ColorSample_80;
    case EGdtfColorSample::CES_81:			return XML_GDTF_ColorSample_81;
    case EGdtfColorSample::CES_82:			return XML_GDTF_ColorSample_82;
    case EGdtfColorSample::CES_83:			return XML_GDTF_ColorSample_83;
    case EGdtfColorSample::CES_84:			return XML_GDTF_ColorSample_84;
    case EGdtfColorSample::CES_85:			return XML_GDTF_ColorSample_85;
    case EGdtfColorSample::CES_86:			return XML_GDTF_ColorSample_86;
    case EGdtfColorSample::CES_87:			return XML_GDTF_ColorSample_87;
    case EGdtfColorSample::CES_88:			return XML_GDTF_ColorSample_88;
    case EGdtfColorSample::CES_89:			return XML_GDTF_ColorSample_89;
    case EGdtfColorSample::CES_90:			return XML_GDTF_ColorSample_90;
    case EGdtfColorSample::CES_91:			return XML_GDTF_ColorSample_91;
    case EGdtfColorSample::CES_92:			return XML_GDTF_ColorSample_92;
    case EGdtfColorSample::CES_93:			return XML_GDTF_ColorSample_93;
    case EGdtfColorSample::CES_94:			return XML_GDTF_ColorSample_94;
    case EGdtfColorSample::CES_95:			return XML_GDTF_ColorSample_95;
    case EGdtfColorSample::CES_96:			return XML_GDTF_ColorSample_96;
    case EGdtfColorSample::CES_97:			return XML_GDTF_ColorSample_97;
    case EGdtfColorSample::CES_98:			return XML_GDTF_ColorSample_98;
    case EGdtfColorSample::CES_99:			return XML_GDTF_ColorSample_99;
    }

	DSTOP((kEveryone, "Unknown Enum for EGdtfColorSample"));

    return XML_GDTF_ColorSample_1;
}

/*static*/ bool GdtfConverter::ConvertEGdtfColorSampleEnum(const TXString& inVal, EGdtfColorSample& outVal)
{    
    if      (inVal == XML_GDTF_ColorSample_1)  { outVal = EGdtfColorSample::CES_01; }
    else if (inVal == XML_GDTF_ColorSample_2)  { outVal = EGdtfColorSample::CES_02; }
    else if (inVal == XML_GDTF_ColorSample_3)  { outVal = EGdtfColorSample::CES_03; }
    else if (inVal == XML_GDTF_ColorSample_4)  { outVal = EGdtfColorSample::CES_04; }
    else if (inVal == XML_GDTF_ColorSample_5)  { outVal = EGdtfColorSample::CES_05; }
    else if (inVal == XML_GDTF_ColorSample_6)  { outVal = EGdtfColorSample::CES_06; }
    else if (inVal == XML_GDTF_ColorSample_7)  { outVal = EGdtfColorSample::CES_07; }
    else if (inVal == XML_GDTF_ColorSample_8)  { outVal = EGdtfColorSample::CES_08; }
    else if (inVal == XML_GDTF_ColorSample_9)  { outVal = EGdtfColorSample::CES_09; }
    else if (inVal == XML_GDTF_ColorSample_10) { outVal = EGdtfColorSample::CES_10; }
    else if (inVal == XML_GDTF_ColorSample_11) { outVal = EGdtfColorSample::CES_11; }
    else if (inVal == XML_GDTF_ColorSample_12) { outVal = EGdtfColorSample::CES_12; }
    else if (inVal == XML_GDTF_ColorSample_13) { outVal = EGdtfColorSample::CES_13; }
    else if (inVal == XML_GDTF_ColorSample_14) { outVal = EGdtfColorSample::CES_14; }
    else if (inVal == XML_GDTF_ColorSample_15) { outVal = EGdtfColorSample::CES_15; }
    else if (inVal == XML_GDTF_ColorSample_16) { outVal = EGdtfColorSample::CES_16; }
    else if (inVal == XML_GDTF_ColorSample_17) { outVal = EGdtfColorSample::CES_17; }
    else if (inVal == XML_GDTF_ColorSample_18) { outVal = EGdtfColorSample::CES_18; }
    else if (inVal == XML_GDTF_ColorSample_19) { outVal = EGdtfColorSample::CES_19; }
    else if (inVal == XML_GDTF_ColorSample_20) { outVal = EGdtfColorSample::CES_20; }
    else if (inVal == XML_GDTF_ColorSample_21) { outVal = EGdtfColorSample::CES_21; }
    else if (inVal == XML_GDTF_ColorSample_22) { outVal = EGdtfColorSample::CES_22; }
    else if (inVal == XML_GDTF_ColorSample_23) { outVal = EGdtfColorSample::CES_23; }
    else if (inVal == XML_GDTF_ColorSample_24) { outVal = EGdtfColorSample::CES_24; }
    else if (inVal == XML_GDTF_ColorSample_25) { outVal = EGdtfColorSample::CES_25; }
    else if (inVal == XML_GDTF_ColorSample_26) { outVal = EGdtfColorSample::CES_26; }
    else if (inVal == XML_GDTF_ColorSample_27) { outVal = EGdtfColorSample::CES_27; }
    else if (inVal == XML_GDTF_ColorSample_28) { outVal = EGdtfColorSample::CES_28; }
    else if (inVal == XML_GDTF_ColorSample_29) { outVal = EGdtfColorSample::CES_29; }
    else if (inVal == XML_GDTF_ColorSample_30) { outVal = EGdtfColorSample::CES_30; }
    else if (inVal == XML_GDTF_ColorSample_31) { outVal = EGdtfColorSample::CES_31; }
    else if (inVal == XML_GDTF_ColorSample_32) { outVal = EGdtfColorSample::CES_32; }
    else if (inVal == XML_GDTF_ColorSample_33) { outVal = EGdtfColorSample::CES_33; }
    else if (inVal == XML_GDTF_ColorSample_34) { outVal = EGdtfColorSample::CES_34; }
    else if (inVal == XML_GDTF_ColorSample_35) { outVal = EGdtfColorSample::CES_35; }
    else if (inVal == XML_GDTF_ColorSample_36) { outVal = EGdtfColorSample::CES_36; }
    else if (inVal == XML_GDTF_ColorSample_37) { outVal = EGdtfColorSample::CES_37; }
    else if (inVal == XML_GDTF_ColorSample_38) { outVal = EGdtfColorSample::CES_38; }
    else if (inVal == XML_GDTF_ColorSample_39) { outVal = EGdtfColorSample::CES_39; }
    else if (inVal == XML_GDTF_ColorSample_40) { outVal = EGdtfColorSample::CES_40; }
    else if (inVal == XML_GDTF_ColorSample_41) { outVal = EGdtfColorSample::CES_41; }
    else if (inVal == XML_GDTF_ColorSample_42) { outVal = EGdtfColorSample::CES_42; }
    else if (inVal == XML_GDTF_ColorSample_43) { outVal = EGdtfColorSample::CES_43; }
    else if (inVal == XML_GDTF_ColorSample_44) { outVal = EGdtfColorSample::CES_44; }
    else if (inVal == XML_GDTF_ColorSample_45) { outVal = EGdtfColorSample::CES_45; }
    else if (inVal == XML_GDTF_ColorSample_46) { outVal = EGdtfColorSample::CES_46; }
    else if (inVal == XML_GDTF_ColorSample_47) { outVal = EGdtfColorSample::CES_47; }
    else if (inVal == XML_GDTF_ColorSample_48) { outVal = EGdtfColorSample::CES_48; }
    else if (inVal == XML_GDTF_ColorSample_49) { outVal = EGdtfColorSample::CES_49; }
    else if (inVal == XML_GDTF_ColorSample_50) { outVal = EGdtfColorSample::CES_50; }
    else if (inVal == XML_GDTF_ColorSample_51) { outVal = EGdtfColorSample::CES_51; }
    else if (inVal == XML_GDTF_ColorSample_52) { outVal = EGdtfColorSample::CES_52; }
    else if (inVal == XML_GDTF_ColorSample_53) { outVal = EGdtfColorSample::CES_53; }
    else if (inVal == XML_GDTF_ColorSample_54) { outVal = EGdtfColorSample::CES_54; }
    else if (inVal == XML_GDTF_ColorSample_55) { outVal = EGdtfColorSample::CES_55; }
    else if (inVal == XML_GDTF_ColorSample_56) { outVal = EGdtfColorSample::CES_56; }
    else if (inVal == XML_GDTF_ColorSample_57) { outVal = EGdtfColorSample::CES_57; }
    else if (inVal == XML_GDTF_ColorSample_58) { outVal = EGdtfColorSample::CES_58; }
    else if (inVal == XML_GDTF_ColorSample_59) { outVal = EGdtfColorSample::CES_59; }
    else if (inVal == XML_GDTF_ColorSample_60) { outVal = EGdtfColorSample::CES_60; }
    else if (inVal == XML_GDTF_ColorSample_61) { outVal = EGdtfColorSample::CES_61; }
    else if (inVal == XML_GDTF_ColorSample_62) { outVal = EGdtfColorSample::CES_62; }
    else if (inVal == XML_GDTF_ColorSample_63) { outVal = EGdtfColorSample::CES_63; }
    else if (inVal == XML_GDTF_ColorSample_64) { outVal = EGdtfColorSample::CES_64; }
    else if (inVal == XML_GDTF_ColorSample_65) { outVal = EGdtfColorSample::CES_65; }
    else if (inVal == XML_GDTF_ColorSample_66) { outVal = EGdtfColorSample::CES_66; }
    else if (inVal == XML_GDTF_ColorSample_67) { outVal = EGdtfColorSample::CES_67; }
    else if (inVal == XML_GDTF_ColorSample_68) { outVal = EGdtfColorSample::CES_68; }
    else if (inVal == XML_GDTF_ColorSample_69) { outVal = EGdtfColorSample::CES_69; }
    else if (inVal == XML_GDTF_ColorSample_70) { outVal = EGdtfColorSample::CES_70; }
    else if (inVal == XML_GDTF_ColorSample_71) { outVal = EGdtfColorSample::CES_71; }
    else if (inVal == XML_GDTF_ColorSample_72) { outVal = EGdtfColorSample::CES_72; }
    else if (inVal == XML_GDTF_ColorSample_73) { outVal = EGdtfColorSample::CES_73; }
    else if (inVal == XML_GDTF_ColorSample_74) { outVal = EGdtfColorSample::CES_74; }
    else if (inVal == XML_GDTF_ColorSample_75) { outVal = EGdtfColorSample::CES_75; }
    else if (inVal == XML_GDTF_ColorSample_76) { outVal = EGdtfColorSample::CES_76; }
    else if (inVal == XML_GDTF_ColorSample_77) { outVal = EGdtfColorSample::CES_77; }
    else if (inVal == XML_GDTF_ColorSample_78) { outVal = EGdtfColorSample::CES_78; }
    else if (inVal == XML_GDTF_ColorSample_79) { outVal = EGdtfColorSample::CES_79; }
    else if (inVal == XML_GDTF_ColorSample_80) { outVal = EGdtfColorSample::CES_80; }
    else if (inVal == XML_GDTF_ColorSample_81) { outVal = EGdtfColorSample::CES_81; }
    else if (inVal == XML_GDTF_ColorSample_82) { outVal = EGdtfColorSample::CES_82; }
    else if (inVal == XML_GDTF_ColorSample_83) { outVal = EGdtfColorSample::CES_83; }
    else if (inVal == XML_GDTF_ColorSample_84) { outVal = EGdtfColorSample::CES_84; }
    else if (inVal == XML_GDTF_ColorSample_85) { outVal = EGdtfColorSample::CES_85; }
    else if (inVal == XML_GDTF_ColorSample_86) { outVal = EGdtfColorSample::CES_86; }
    else if (inVal == XML_GDTF_ColorSample_87) { outVal = EGdtfColorSample::CES_87; }
    else if (inVal == XML_GDTF_ColorSample_88) { outVal = EGdtfColorSample::CES_88; }
    else if (inVal == XML_GDTF_ColorSample_89) { outVal = EGdtfColorSample::CES_89; }
    else if (inVal == XML_GDTF_ColorSample_90) { outVal = EGdtfColorSample::CES_90; }
    else if (inVal == XML_GDTF_ColorSample_91) { outVal = EGdtfColorSample::CES_91; }
    else if (inVal == XML_GDTF_ColorSample_92) { outVal = EGdtfColorSample::CES_92; }
    else if (inVal == XML_GDTF_ColorSample_93) { outVal = EGdtfColorSample::CES_93; }
    else if (inVal == XML_GDTF_ColorSample_94) { outVal = EGdtfColorSample::CES_94; }
    else if (inVal == XML_GDTF_ColorSample_95) { outVal = EGdtfColorSample::CES_95; }
    else if (inVal == XML_GDTF_ColorSample_96) { outVal = EGdtfColorSample::CES_96; }
    else if (inVal == XML_GDTF_ColorSample_97) { outVal = EGdtfColorSample::CES_97; }
    else if (inVal == XML_GDTF_ColorSample_98) { outVal = EGdtfColorSample::CES_98; }
    else if (inVal == XML_GDTF_ColorSample_99) { outVal = EGdtfColorSample::CES_99; }

    DSTOP((kEveryone, "Unknown Value for EGdtfColorSample"));
    GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_EnumNoMatchingEntry);
    SceneData::GdtfFixture::AddError(error);
       
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
	
    GdtfParsingError error (GdtfDefines::EGdtfParsingError::eMissingFile);
    SceneData::GdtfFixture::AddError(error);
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
    if (strVal.Find(",") == -1)
    {
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_WrongFormat);
        SceneData::GdtfFixture::AddError(error);
    }
	while (pos > 0 )
	{
		// Copy string
		TXString strValInner;
		for (ptrdiff_t i = 0; i < pos; i++)	{ strValInner += strVal.GetAt(i); }
		
		// Try to cast
		TXString con (strValInner);
		doubleArr.push_back(con.atof());
		
		// Delete and find next
		strVal.Delete(0, pos + 1);
		pos = strVal.Find(",");
	}
	
	
	// Delete and find next
	TXString con(strVal);
	doubleArr.push_back(con.atof());
		
	return true;
}

/*static*/ bool GdtfConverter::Deserialize(const TXString& value, TSint32Array & intArray)
{
	// Split string
	TXString strVal = value;
	
	// Find first entry
	ptrdiff_t pos = strVal.Find(",");
	while (pos > 0 )
	{
		// Copy string
		TXString strValInner;
		for (ptrdiff_t i = 0; i < pos; i++)	{ strValInner += strVal.GetAt(i); }
		
		// Try to cast
		intArray.push_back(strValInner.atoi());
		
		// Delete and find next
		strVal.Delete(0, pos + 1);
		pos = strVal.Find(",");
	}
	
	// Delete and find next
	intArray.push_back(strVal.atoi());
	
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

DmxValue GdtfConverter::GetChannelMaxDmx(EGdtfChannelBitResolution chanlReso)
{
	DmxValue maxVal = 0;
	switch (chanlReso)
	{
		case VectorworksMVR::GdtfDefines::eGdtfChannelBitResolution_8: maxVal = 256 ; break;
		case VectorworksMVR::GdtfDefines::eGdtfChannelBitResolution_16:maxVal = 256 * 256; break;
		case VectorworksMVR::GdtfDefines::eGdtfChannelBitResolution_24:maxVal = 256 * 256 * 256; break;
		case VectorworksMVR::GdtfDefines::eGdtfChannelBitResolution_32:maxVal = 4294967296; break; 
		/* The compiler gives a warning here, if we do a normal calculation here, so we just pick the value (256 * 256 * 256 * 256)*/
	}

    ASSERTN(kEveryone, maxVal != 0);
	
	return (maxVal - 1);

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

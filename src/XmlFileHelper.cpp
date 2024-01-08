//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------

#include "Prefix/StdAfx.h"
using namespace VectorworksMVR::VWFC;

#include "SceneDataExchange.h"
#include "GDTFManager.h"
#include "XmlFileHelper.h"
#include "HashManager.h"
#include "GdtfError.h"
#include "Utility.h"

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

	
	return vwUuid;
	
}

/*static*/ bool GdtfConverter::ConvertUUID(const TXString& inValue, const IXMLFileNodePtr& node, VWFC::Tools::VWUUID& uuid)
{
	// First check if theinValuelength is as aspected
    TXString uuidForRead;
	if (inValue.GetLength() == 47)	
    {
        // Remove white space
        TXString value = inValue;
	    value.Replace(" ", "");
	
        uuidForRead.SetLength(38);
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

    }
    else if(inValue.GetLength() == 36)
    {
        uuidForRead += '{';
        uuidForRead += inValue;
        uuidForRead += '}';
    }
    else if(inValue.GetLength() == 0)
    {
        return false;
    }
    else
    {
        DSTOP((kEveryone, "Invalid UUID Format"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_UuidHasWrongFormat, node);
        SceneData::GdtfFixture::AddError(error); 
    }
    
	uuid = VWUUID(uuidForRead);
	
	return true;
	
}


/*static*/ bool GdtfConverter::ConvertUUID(const TXString& inValue, MvrUUID& inUuid)
{
	VWFC::Tools::VWUUID uuid;
	// First check if theinValuelength is as aspected
    TXString uuidForRead;
	if (inValue.GetLength() == 47)	
    {
        // Remove white space
        TXString value = inValue;
	    value.Replace(" ", "");
	
        uuidForRead.SetLength(38);
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

    }
    else if(inValue.GetLength() == 36)
    {
        uuidForRead += '{';
        uuidForRead += inValue;
        uuidForRead += '}';
    }
    else if(inValue.GetLength() == 0)
    {
        return false;
    }
    
	VWUUID u;
	bool result = uuid.FromString(uuidForRead);
	uuid.GetUUID(inUuid.a, inUuid.b, inUuid.c, inUuid.d);
	
	return result;
}

/*static*/ TXString GdtfConverter::IntToString2Digits(Sint64 value) 
/* Converts the int to an string with 2 digits. If the int has only one digit the string will get a leading "0".*/ 
{
    ASSERTN(kEveryone ,value < 100);

    if (value < 10)
    {
        return "0" + TXString().itoa(value);
    }

    return TXString().itoa(value);    
}

/*static*/ TXString GdtfConverter::ConvertDate(const STime& date)
/* Return the date in UTC Format:  	yyyy-mm-ddThh:mm:ss 
*/
{
	TXString result;
	result += TXString().itoa(date.fYear);
	result += "-";
	result += IntToString2Digits(date.fMonth);
	result += "-";
    result += IntToString2Digits(date.fDay);	
	
    result += "T";

	result += IntToString2Digits(date.fHour);
	result += ":";
	result += IntToString2Digits(date.fMinute);
	result += ":";
	result += IntToString2Digits(date.fSecond);
	
    return result;
}

/*static*/ bool GdtfConverter::ConvertDate(const TXString& value, const IXMLFileNodePtr& node, STime& date)
/* Convert from UTC Format (yyyy-mm-ddThh:mm:ss) */
{
	// ------------------------------------------------------------
	// Check if the string is empty, use the 0 date
	if (value.IsEmpty()) { date.fYear = 0; date.fMonth = 0; date.fDay = 0; date.fHour = 0; date.fMinute = 0; date.fSecond = 0; return true; }
	
	// ------------------------------------------------------------
	// Split string
	TXString strVal = value;
	
	// Prepare Array
	TSint32Array d_arr;
	
	DeserializeUTC_Date(strVal, node,  d_arr);
	
	
	// ------------------------------------------------------------
	// Check if you have three valies
	ASSERTN(kEveryone, d_arr.size() == 6);
	if (d_arr.size() != 6)
    {
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_DateHasWrongFormat, node);
        SceneData::GdtfFixture::AddError(error);
		date.fYear = 0; date.fMonth = 0; date.fDay = 0; date.fHour = 0; date.fMinute = 0; date.fSecond = 0;
		return false;
    }
	
	// Set Out Date
	date.fYear = d_arr[0]; date.fMonth  = d_arr[1]; date.fDay    = d_arr[2]; 
    date.fHour = d_arr[3]; date.fMinute = d_arr[4]; date.fSecond = d_arr[5];
	
	return true;
}



/*static*/ TXString GdtfConverter::ConvertColor(const CCieColor& color)
{
	return (TXString() << color.Get_x() << "," << color.Get_y() << "," << color.Get_Y_luminance() );
}

/*static*/ bool GdtfConverter::ConvertColor(const TXString& value, const IXMLFileNodePtr& node, CCieColor& color)
{
	// ------------------------------------------------------------
	// Check if the string is empty, use the default color
	if (value.IsEmpty()) { color = CCieColor(); return true; }
	
	// ------------------------------------------------------------
	// Split string
	TXString strVal = value;
	
	// Prepare Array
	std::vector<double> d_arr;
	
	Deserialize(strVal, node,  d_arr);
	
	// ------------------------------------------------------------
	// Check if you have three valies
	ASSERTN(kEveryone, d_arr.size() == 3);
	if (d_arr.size() != 3)
    {
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_ColorHasWrongFormat, node);
        SceneData::GdtfFixture::AddError(error);
        color = CCieColor();
        return false;
    }
	
	// Set Out Color and return true
	color = CCieColor(d_arr[0],d_arr[1],d_arr[2]);
	
	return true;
}

TXString SceneData::GdtfConverter::ConvertColorArray(TCCieColorArray & colors)
/* Takes an CCieColor-Array and returns it as string in the format: "{x,y,Y}{x,y,Y}...{x,y,Y}" */
{   
    TXString arrayStr;
    
    // Add the Values
    for (size_t idx = 0; idx < colors.size(); idx++)
    {
		CCieColorPtr color = colors.at(idx);
        arrayStr << "{" << color->Get_x() << "," << color->Get_y() << "," << color->Get_Y_luminance() << "}";       
    }

    return arrayStr;
}

bool SceneData::GdtfConverter::ConvertColorArray(TXString values, const IXMLFileNodePtr& node, TCCieColorArray& colorArray)
/* Takes string in the format: "{x,y,Y}{x,y,Y}...{x,y,Y}" and fills the values into the colorArray. */
{
    // ----------------------------------------------------------------
	// If the String is empty, use the DefaultMatrix
	if (values.IsEmpty()) { return true; }

	TXString strVal = values;
	// ----------------------------------------------------------------
	// Delete first element
	ASSERTN(kEveryone, strVal.GetAt(0) == '{');
	if (strVal.GetAt(0) == '{') { strVal.Delete(0,1); }
    else
    {
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_ColorArrayWrongFormat, node);
        SceneData::GdtfFixture::AddError(error); 
    }
	
	// Delete last element
	ASSERTN(kEveryone, strVal.GetLast() == '}');
	if (strVal.GetLast() == '}') { strVal.DeleteLast(); }
    else
    {
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_ColorArrayWrongFormat, node);
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

	// Append the rest
	lines.push_back(strVal);
	
	// ----------------------------------------------------------------
	// Do the conversion
	for (size_t i = 0; i < lines.size(); i++)
	{
		std::vector<double> arr;
		Deserialize(lines.at(i), node, arr);
		
		// Use this for 4x4 matrix and 4x3 matrix
		if (arr.size() == 3)
		{
			CCieColorPtr color = new CCieColor(arr[0], arr[1], arr[2]);
			colorArray.push_back(color);
		}
		else
		{
			DSTOP((kEveryone, "Unexpected Format of ColorArray"));
            GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_ColorArrayWrongFormat, node);
            SceneData::GdtfFixture::AddError(error);
		}
	}

	return true;
}

/*static*/ TXString GdtfConverter::ConvertDouble(double value)
{
	TXString valueStr;
	valueStr << value;
	return valueStr;
}

/*static*/ bool GdtfConverter::ConvertDouble(const TXString& value, const IXMLFileNodePtr& node, double& doubleValue) // TODO: XXX unused Param node
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

#ifdef IS64BIT
/*static*/ TXString GdtfConverter::ConvertInteger(Uint32 value)
{
	TXString valueStr;
	valueStr << value;
	return valueStr;
}
#endif

/*static*/ bool GdtfConverter::ConvertDmxBreak(const TXString& value, const IXMLFileNodePtr& node,Sint32& intValue)
{
    if(value.IsEmpty()) return false;
    if(value == XML_GDTF_DMXChannelDMXBreak_OverwriteValue) { intValue = 0; return true; }

	intValue = value.atoi();
	return true;
}

/*static*/ bool GdtfConverter::ConvertInteger(const TXString& value, const IXMLFileNodePtr& node,Sint8& intValue)
{
    if(value.IsEmpty()) return false;

	intValue = value.atoi();
	return true;
}

/*static*/ bool GdtfConverter::ConvertInteger(const TXString& value, const IXMLFileNodePtr& node, Uint8& intValue)
{
    if(value.IsEmpty()) return false;

	intValue = value.atoi();
	return true;
}

/*static*/ bool GdtfConverter::ConvertInteger(const TXString& value, const IXMLFileNodePtr& node,size_t& intValue)
{
    if(value.IsEmpty()) return false;
	
    intValue = value.atoi();
	return true;
}

/*static*/ bool GdtfConverter::ConvertInteger(const TXString& value, const IXMLFileNodePtr& node,Sint32& intValue)
{
    if(value.IsEmpty()) return false;
	
    intValue = value.atoi();
	return true;
}

#ifdef IS64BIT
/*static*/ bool GdtfConverter::ConvertInteger(const TXString& value, const IXMLFileNodePtr& node, Uint32& intValue)
{
    if(value.IsEmpty()) return false;
	
    intValue = value.atoi();
	return true;
}
#endif

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

TXString SceneData::GdtfConverter::ConvertIntegerArray(TSint32Array & values, bool includeBrackets)
/* Takes an Int-Array and returns it as string in the format: "{Int, Int, ... Int}" */
{   
    TXString arrayStr;
    
	if(includeBrackets) { arrayStr += "{"; }
    
    // Add the Values
    for (size_t idx = 0; idx < values.size(); idx++)
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
	if(includeBrackets) { arrayStr += "}"; }

    return arrayStr;
}

bool SceneData::GdtfConverter::ConvertIntegerArray(TXString values, const IXMLFileNodePtr& node, TSint32Array & intArray)
/* Takes string in the format: "{Int, Int, ... Int}" and fills the values into the IntArray. */
{
    TXString intArrayString = values;
    if (values.IsEmpty()) { return false; }

    // Remove the barcets "{" and "}"
    values.Replace("{", "");
    values.Replace("}", "");

    // Seperate the string by ","
    GdtfConverter::Deserialize(values, node, intArray);
    return true;
}

TXString SceneData::GdtfConverter::ConvertDoubleArray(TDoubleArray & values, bool includeBrackets)
/* Takes an Int-Array and returns it as string in the format: "{Int, Int, ... Int}" */
{   
    TXString arrayStr;
    
	if(includeBrackets) { arrayStr += "{"; }
    
    // Add the Values
    for (size_t idx = 0; idx < values.size(); idx++)
    {        
        arrayStr += (TXString() << values.at(idx));
        
        // The last index is size-1. We want that no "," is appended at the last item 
        // so only append "," for idx < last_idx.
        if (idx < values.size() - 1) 
        {
            arrayStr += ",";
        }        
    }    

    // Close the Array Str
	if(includeBrackets) { arrayStr += "}"; }

    return arrayStr;
}

bool SceneData::GdtfConverter::ConvertDoubleArray(TXString values, const IXMLFileNodePtr& node, TDoubleArray & doubleArray)
/* Takes string in the format: "{double, double, ... double}" and fills the values into the doubleArray. */
{
    TXString doubleArrayString = values;
    if (values.IsEmpty()) { return false; }

    // Remove the brackets "{" and "}"
    values.Replace("{", "");
    values.Replace("}", "");

    // Separate the string by ","
    GdtfConverter::Deserialize(values, node, doubleArray);
    return true;
}

/*static*/ TXString GdtfConverter::ConvertInteger(size_t value)
{	
	// Otherwise return the value
	TXString valueStr;
	valueStr = TXString().itoa(value);
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

/*static*/ bool GdtfConverter::ConvertInteger(const TXString& value, const IXMLFileNodePtr& node,Sint32& intValue, bool& noneValue)
{
	noneValue = false;
	
	if (value == XML_GDTF_DMXFChannel_NONEVALUE)		{ noneValue = true; intValue = 0; return true; ; }
	
	return ConvertInteger(value, node, intValue);;
}

bool SceneData::GdtfConverter::ConvertDMXAdress(const TXString& value, const IXMLFileNodePtr& node, DMXAddress & intValue)
/* Convert String to DMXAdress*/
{
    if(value.IsEmpty()) {intValue = 1; return false;}

	ptrdiff_t dotPos = value.Find('.');

	bool error = false;

	if(dotPos > 0){
		Uint16 universe = value.Left(dotPos).atoi();
		Uint16 address  = value.Right(value.GetLength() - dotPos - 1).atoi();

		if (universe <= 0 || address <= 0 || address > 512)	
		{
	    	ASSERTN(kEveryone, false);
			error = true;
		}

		intValue = (universe - 1) * 512 + address;

	}else{
		intValue = value.atoi();
    	ASSERTN(kEveryone, intValue > 0);

		if (intValue <= 0)	
		{
			error = true;
		}
	}

	if(error){
		GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_DmxAdressHasWrongValue, node);
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

bool SceneData::GdtfConverter::ConvertDMXValue(const TXString& strValue, const IXMLFileNodePtr& node, EGdtfChannelBitResolution chanlReso, DmxValue & intValue)
/* Converts a string to a DmxValue. returns succes of the opeation as bool (XXX this is always true at the moment.)*/
{
	if(strValue.IsEmpty())
	{
		intValue = 0;
		return true;
	}

	// Split the String ("ValRaw/byteSpecifier")
	TXString 	firstPart;
	TXString 	secndPart;
	bool		byteShifting = false;

	// Find first entry
	ptrdiff_t splitPos = strValue.Find("/");
	if (splitPos == -1)
    {
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_DmxValueHasWrongValue, node);
        SceneData::GdtfFixture::AddError(error);
        return false;
    }

	SplitStr(strValue, firstPart, secndPart, (size_t)splitPos);
	//-----------------------------------------------------------------------------------

	if(secndPart.GetLast() == 's')
	{
		byteShifting = true;
		secndPart.Truncate(secndPart.GetLength() - 1);
	}
	
	double dmxValueRaw    = firstPart.atof();
	Sint32 byteSpecifier = secndPart.atoi();

	if( ! (firstPart.IsCompleteNumber() && secndPart.IsCompleteNumber()))
	{
		GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_DmxValueHasWrongValue, node);
        SceneData::GdtfFixture::AddError(error);
		dmxValueRaw 	= 0;
		byteSpecifier 	= 1;
	}

	// Check if the ByteSpecifier is different to the ChannelResolution.
	intValue = dmxValueRaw;

	if(byteShifting)
	{
		if (byteSpecifier != chanlReso) 
		{
			Sint32 shift = (8 * (chanlReso - byteSpecifier));
			if(shift >= 0) 	{ intValue = intValue << shift; }
			else			{ intValue = intValue >> -shift; }
		}	
		else
		{
			// We can take the value as it is defined in the document without scaling it to another BitResolution.
			intValue = dmxValueRaw; 
		}

	}
	else
	{
		if (byteSpecifier != chanlReso) 
		{
			DmxValue maxResolution  = GetChannelMaxDmx((EGdtfChannelBitResolution)byteSpecifier);        
			DmxValue maxChannelUnit = GetChannelMaxDmx(chanlReso);

			double percentage = (dmxValueRaw / maxResolution);

			intValue = percentage * maxChannelUnit;

		}	
		else
		{
			// We can take the value as it is defined in the document without scaling it to another BitResolution.
			intValue = dmxValueRaw; 
		}
	}
	
	

    if ( GetChannelMaxDmx(chanlReso) < intValue)
    {
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_DmxValueHasWrongValue, node);
        SceneData::GdtfFixture::AddError(error);
        return false;
    }

	return true;
}

bool SceneData::GdtfConverter::ConvertDMXValue(const TXString & strValue, const IXMLFileNodePtr& node, EGdtfChannelBitResolution chanlReso, DmxValue & intValue, bool & noneValue)
/* Converts a string to a DmxValue */
{	
	noneValue = false; 

	if (strValue == XML_GDTF_DMXFChannel_NONEVALUE) 
	{
		noneValue = true; 
		return true;
	}

	ConvertDMXValue(strValue, node, chanlReso, intValue);

	return true;
}

/*static*/ TXString GdtfConverter::ConvertPrimitiveType(EGdtfModel_PrimitiveType value)
{
	switch (value)
	{
		case eGdtfModel_PrimitiveType_Cube:				return XML_GDTF_PrimitiveTypeEnum_Cube;
		case eGdtfModel_PrimitiveType_Sphere:			return XML_GDTF_PrimitiveTypeEnum_Sphere;
		case eGdtfModel_PrimitiveType_Cylinder:			return XML_GDTF_PrimitiveTypeEnum_Cylinder;
		case eGdtfModel_PrimitiveType_Undefined:		return XML_GDTF_PrimitiveTypeEnum_Undefined;
		case eGdtfModel_PrimitiveType_Base:				return XML_GDTF_PrimitiveTypeEnum_Base;
		case eGdtfModel_PrimitiveType_Head:				return XML_GDTF_PrimitiveTypeEnum_Head;
		case eGdtfModel_PrimitiveType_Yoke:				return XML_GDTF_PrimitiveTypeEnum_Yoke;
		case eGdtfModel_PrimitiveType_Scanner:			return XML_GDTF_PrimitiveTypeEnum_Scanner;
		case eGdtfModel_PrimitiveType_Conventional:		return XML_GDTF_PrimitiveTypeEnum_Conventional;
        case eGdtfModel_PrimitiveType_Pigtail:      	return XML_GDTF_PrimitiveTypeEnum_Pigtail;
		case eGdtfModel_PrimitiveType_Base1_1:      	return XML_GDTF_PrimitiveTypeEnum_Base1_1;
		case eGdtfModel_PrimitiveType_Scanner1_1:      	return XML_GDTF_PrimitiveTypeEnum_Scanner1_1;
		case eGdtfModel_PrimitiveType_Conventional1_1:	return XML_GDTF_PrimitiveTypeEnum_Conventional1_1;
		default: 										return XML_GDTF_PrimitiveTypeEnum_Undefined;
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
                        value == eGdtfModel_PrimitiveType_Pigtail ||
						value == eGdtfModel_PrimitiveType_Base1_1 ||
						value == eGdtfModel_PrimitiveType_Scanner1_1 ||
						value == eGdtfModel_PrimitiveType_Conventional1_1);
	
	// Return default value
	return XML_GDTF_PrimitiveTypeEnum_Undefined;
}


/*static*/ bool GdtfConverter::ConvertPrimitiveType(const TXString& value, const IXMLFileNodePtr& node, EGdtfModel_PrimitiveType& type)
{
	if		(value == XML_GDTF_PrimitiveTypeEnum_Cube)				{ type = eGdtfModel_PrimitiveType_Cube;		}
	else if (value == XML_GDTF_PrimitiveTypeEnum_Sphere)			{ type = eGdtfModel_PrimitiveType_Sphere;	}
	else if (value == XML_GDTF_PrimitiveTypeEnum_Cylinder)			{ type = eGdtfModel_PrimitiveType_Cylinder;	}
	else if (value == XML_GDTF_PrimitiveTypeEnum_Base)				{ type = eGdtfModel_PrimitiveType_Base;	}
	else if (value == XML_GDTF_PrimitiveTypeEnum_Head)				{ type = eGdtfModel_PrimitiveType_Head;	}
	else if (value == XML_GDTF_PrimitiveTypeEnum_Yoke)				{ type = eGdtfModel_PrimitiveType_Yoke;	}
	else if (value == XML_GDTF_PrimitiveTypeEnum_Scanner)			{ type = eGdtfModel_PrimitiveType_Scanner;	}
	else if (value == XML_GDTF_PrimitiveTypeEnum_Conventional)		{ type = eGdtfModel_PrimitiveType_Conventional;	}
	else if (value == XML_GDTF_PrimitiveTypeEnum_Undefined)			{ type = eGdtfModel_PrimitiveType_Undefined; }
    else if (value == XML_GDTF_PrimitiveTypeEnum_Pigtail)			{ type = eGdtfModel_PrimitiveType_Pigtail; }
	else if (value == XML_GDTF_PrimitiveTypeEnum_Base1_1)			{ type = eGdtfModel_PrimitiveType_Base1_1; }
	else if (value == XML_GDTF_PrimitiveTypeEnum_Scanner1_1)		{ type = eGdtfModel_PrimitiveType_Scanner1_1; }
	else if (value == XML_GDTF_PrimitiveTypeEnum_Conventional1_1)	{ type = eGdtfModel_PrimitiveType_Conventional1_1; }
	else if (value == "")											{ type = eGdtfModel_PrimitiveType_Undefined; }
	else
    {
        type = eGdtfModel_PrimitiveType_Undefined; DSTOP((kEveryone, "Unexpected Input for Primitive Type Enum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_NoMatchInEnum_ConvertPrimitiveType, node);
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

/*static*/ bool GdtfConverter::ConvertSpecialAttrEnum(const TXString& value, const IXMLFileNodePtr& node,EGdtfSpecial& special)
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
        special = EGdtfSpecial::None; DSTOP((kEveryone, "Unexpected Input for EGdtfSpecial Enum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_NoMatchInEnum_ConvertSpecialAttr, node);
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

/*static*/ bool GdtfConverter::ConvertPhysicalUnitEnum(const TXString& value, const IXMLFileNodePtr& node,EGdtfPhysicalUnit& unit)
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
        unit = EGdtfPhysicalUnit::None; DSTOP((kEveryone, "Unexpected Input for EGdtfPhysicalUnit Enum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_NoMatchInEnum_ConvertPhysicalUnit, node);
        SceneData::GdtfFixture::AddError(error); 
    }
	
	// Return true
	return true;
}
/*static*/ bool GdtfConverter::ConvertBeamType(const TXString& value, const IXMLFileNodePtr& node,EGdtfBeamType& unit)
{
	if		(value == XML_GDTF_BeamTypeEnum_Wash)			{ unit = EGdtfBeamType::eGdtfBeamType_Wash;		 	}
	else if (value == XML_GDTF_BeamTypeEnum_Spot)			{ unit = EGdtfBeamType::eGdtfBeamType_Spot;		 	}
	else if (value == XML_GDTF_BeamTypeEnum_None)			{ unit = EGdtfBeamType::eGdtfBeamType_None;		 	}
	else if (value == XML_GDTF_BeamTypeEnum_Rectangle)		{ unit = EGdtfBeamType::eGdtfBeamType_Rectangle; 	}
	else if (value == XML_GDTF_BeamTypeEnum_PC)				{ unit = EGdtfBeamType::eGdtfBeamType_PC;			}
	else if (value == XML_GDTF_BeamTypeEnum_Fresnel)		{ unit = EGdtfBeamType::eGdtfBeamType_Fresnel; 		}
	else if (value == XML_GDTF_BeamTypeEnum_Glow)			{ unit = EGdtfBeamType::eGdtfBeamType_Glow; 		}
	else if (value == "")									{ unit = EGdtfBeamType::eGdtfBeamType_Wash;		 	}
	else													
    {
        unit = EGdtfBeamType::eGdtfBeamType_Wash; DSTOP((kEveryone, "Unexpected Input for EGdtfBeamType Enum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_NoMatchInEnum_ConvertBeamType, node);
        SceneData::GdtfFixture::AddError(error); 
    }
	
	// Return true
	return true;
}

/*static*/ TXString GdtfConverter::ConvertBeamType(EGdtfBeamType value)
{
	switch (value)
	{
		case eGdtfBeamType_Rectangle: 	return XML_GDTF_BeamTypeEnum_Rectangle;
		case eGdtfBeamType_None: 		return XML_GDTF_BeamTypeEnum_None;
		case eGdtfBeamType_Spot: 		return XML_GDTF_BeamTypeEnum_Spot;
		case eGdtfBeamType_Wash: 		return XML_GDTF_BeamTypeEnum_Wash;
		case eGdtfBeamType_PC: 			return XML_GDTF_BeamTypeEnum_PC;
		case eGdtfBeamType_Fresnel: 	return XML_GDTF_BeamTypeEnum_Fresnel;
		case eGdtfBeamType_Glow: 		return XML_GDTF_BeamTypeEnum_Glow;
			
		default: DSTOP((kEveryone,"This enum for EGdtfBeamType was not implemented!")); break;
	}
	
	// Return true
	return XML_GDTF_BeamTypeEnum_Wash;
}

/*static*/ TXString GdtfConverter::ConvertVector3(const VWPoint3D& value)
{
	TXString vectorString;
	vectorString << "{" << value.x << "," << value.y << "," << value.z << "}";
	return vectorString;
}

/*static*/ bool GdtfConverter::ConvertVector3(const TXString& value, const IXMLFileNodePtr& node, VWPoint3D& vector)
{
	// ----------------------------------------------------------------
	// If the String is empty, use the DefaultMaterix
	if (value.IsEmpty()) { vector = VWPoint3D(); return true; }
	
	
	// ----------------------------------------------------------------
	// Split string
	TXString strVal = value;
	
	
	// ----------------------------------------------------------------
	// Delete first element
	ASSERTN(kEveryone, strVal.GetAt(0) == '{');
	if (strVal.GetAt(0) == '{') { strVal.Delete(0,1); }
    else
    {
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_MatrixFormatMissingFirstBracket, node);
        SceneData::GdtfFixture::AddError(error); 
    }
	
	// Delete last element
	ASSERTN(kEveryone, strVal.GetLast() == '}');
	if (strVal.GetLast() == '}') { strVal.DeleteLast(); }
    else
    {
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_MatrixFormatMissingLastBracket, node);
        SceneData::GdtfFixture::AddError(error);
    }

	std::vector<double> vectorAsArray;
	Deserialize(strVal, node, vectorAsArray);

	if (vectorAsArray.size() != 3)
	{
		DSTOP((kEveryone, "Unexpected Format of Vector"));
		GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_MatrixFormatTooMuchOrTooLessEntries, node);
		SceneData::GdtfFixture::AddError(error);
		return false;
	}
	else
	{
		vector.SetPoint(vectorAsArray[0], vectorAsArray[1], vectorAsArray[2]);
	}

	return true;
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

/*static*/ bool GdtfConverter::ConvertMatrix(const TXString& value, const IXMLFileNodePtr& node,VWTransformMatrix& matrix)
{
	// ----------------------------------------------------------------
	// If the String is empty, use the DefaultMatrix
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
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_MatrixFormatMissingFirstBracket, node);
        SceneData::GdtfFixture::AddError(error); 
    }
	
	// Delete last element
	ASSERTN(kEveryone, strVal.GetLast() == '}');
	if (strVal.GetLast() == '}') { strVal.DeleteLast(); }
    else
    {
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_MatrixFormatMissingLastBracket, node);
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

	// Append the rest
	lines.push_back(strVal);

	if (lines.size() != 4)
	{
		DSTOP((kEveryone,"Failed to split the Matrix into vertices"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_MatrixFormatTooMuchOrTooLessLines, node);
        SceneData::GdtfFixture::AddError(error);
		return false;
	}
	
	// ----------------------------------------------------------------
	// Do the conversion
	for (size_t i = 0; i < lines.size(); i++)
	{
		std::vector<double> arr;
		Deserialize(lines.at(i), node, arr);
		
		// Use this for 4x4 matrix and 4x3 matrix
		if (arr.size() < 3 || arr.size() > 4)
		{
			DSTOP((kEveryone, "Unexpected Format of Matrix"));
            GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_MatrixFormatTooMuchOrTooLessEntries, node);
            SceneData::GdtfFixture::AddError(error);
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

// TODO
// look carefully for each parsing call in ConvertRota
/*static*/ bool GdtfConverter::ConvertRotation(const TXString& value, const IXMLFileNodePtr& node, VWTransformMatrix& matrix)
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
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_MatrixRotationFormatMissingFirstBracket, node);
        SceneData::GdtfFixture::AddError(error); 
    }
	
	// Delete second last element
	ASSERTN(kEveryone, strVal.GetLast() == '}');
	if (strVal.GetLast() == '}')	{ strVal.DeleteLast(); }
	else
    {
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_MatrixRotationFormatMissingLastBracket, node);
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
	
	// Apped the rest
	lines.push_back(strVal);
	
	if (lines.size() != 3)
	{
		DSTOP((kEveryone,"Failed to split the Matrix into vertices"));
		GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_MatrixRotationTooMuchOrTooLessLines, node);
        SceneData::GdtfFixture::AddError(error);
        return false;
	}
	
	// ----------------------------------------------------------------
	// Do the conversion
	for (size_t i = 0; i < lines.size(); i++)
	{
		std::vector<double> arr;
		Deserialize(lines.at(i), node, arr);
		
		if (arr.size() != 3)
		{
			DSTOP((kEveryone, "Unexpected amount of entries in Matrix"));
            GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_MatrixRotationTooMuchOrTooLessEntries, node);
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
		case eGdtfLampType_LED:			return XML_GDTF_LampTypeEnum_LED;
		case eGdtfLampType_Halogen:		return XML_GDTF_LampTypeEnum_Halogen;
		case eGdtfLampType_Tungsten:	return XML_GDTF_LampTypeEnum_Tungsten;
		case eGdtfLampType_Dischange:	return XML_GDTF_LampTypeEnum_Discharge;	
	}
	
	// Make Assert
	ASSERTN(kEveryone,	value == eGdtfLampType_LED ||
			value == eGdtfLampType_Halogen ||
			value == eGdtfLampType_Tungsten ||
			value == eGdtfLampType_Dischange);
	
	// Return default value
	return XML_GDTF_LampTypeEnum_Discharge;
}

/*static*/ bool GdtfConverter::ConvertLampeType(const TXString& value, const IXMLFileNodePtr& node,EGdtfLampType& lampType)
{
	if		(value == XML_GDTF_LampTypeEnum_Discharge)	{ lampType = eGdtfLampType_Dischange;	}
	else if (value == XML_GDTF_LampTypeEnum_Halogen)	{ lampType = eGdtfLampType_Halogen;		}
	else if (value == XML_GDTF_LampTypeEnum_Tungsten)	{ lampType = eGdtfLampType_Tungsten;	}
	else if (value == XML_GDTF_LampTypeEnum_LED)		{ lampType = eGdtfLampType_LED;			}
	else if (value == "")								{ lampType = eGdtfLampType_Dischange;	}
	else
    {
        lampType = eGdtfLampType_Dischange; DSTOP((kEveryone, "Unexpected Input for Lamp Type Enum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_NoMatchInEnum_ConvertLampeType, node);
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

/*static*/ bool GdtfConverter::ConvertSnapEnum(const TXString& value, const IXMLFileNodePtr& node,EGdtfDmxSnap& snap)
{
	if		(value == XML_GDTF_DMXSnapEnum_No)	{ snap = eGdtfDmxMaster_No;		}
	else if (value == XML_GDTF_DMXSnapEnum_On)	{ snap = eGdtfDmxMaster_On;		}
	else if (value == XML_GDTF_DMXSnapEnum_Off)	{ snap = eGdtfDmxMaster_Off;	}
	else if (value == XML_GDTF_DMXSnapEnum_Yes)	{ snap = eGdtfDmxMaster_Yes;	}
	else if (value == "")						{ snap = eGdtfDmxMaster_No;		}
	else
    {
        snap = eGdtfDmxMaster_No; DSTOP((kEveryone, "Unexpected Input for EGdtfDmxSnap Enum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_NoMatchInEnum_ConvertSnap, node);
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

/*static*/ bool GdtfConverter::ConvertMasterEnum(const TXString& value, const IXMLFileNodePtr& node,EGdtfDmxMaster& master)
{
	if		(value == XML_GDTF_DMXMasterEnum_None)	{ master = eGdtfDmxMaster_None;	}
	else if (value == XML_GDTF_DMXMasterEnum_Grand)	{ master = eGdtfDmxMaster_Grand;}
	else if (value == XML_GDTF_DMXMasterEnum_Group)	{ master = eGdtfDmxMaster_Group;}
	else if (value == "")							{ master = eGdtfDmxMaster_None;	}
	else
    {
        master = eGdtfDmxMaster_None; DSTOP((kEveryone, "Unexpected Input for EGdtfDmxMaster Enum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_NoMatchInEnum_ConvertMaster, node);
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

/*static*/ bool GdtfConverter::ConvertRelationEnum(const TXString& value, const IXMLFileNodePtr& node,EGdtfDmxRelationType& relation)
{
	if      (value == XML_GDTF_DMXMasterEnum_Multiply)	{ relation = eGdtfDmxRelationType_Multiply;		}
	else if (value == XML_GDTF_DMXMasterEnum_Override)	{ relation = eGdtfDmxRelationType_Override;		}
	else if (value == "")								{ relation = eGdtfDmxRelationType_Override;			}
	else
    {
        relation = eGdtfDmxRelationType_Override; DSTOP((kEveryone, "Unexpected Input for EGdtfDmxRelationType Enum"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_NoMatchInEnum_ConvertRelation, node);
        SceneData::GdtfFixture::AddError(error);
    }
	
	// Return true
	return true;
	
	
}

/*static*/ TXString GdtfConverter::ConvertDmxOffset(DMXAddress coarse, DMXAddress fine, DMXAddress ultra, DMXAddress uber)
{
	TSint32Array array;
	bool c = true;
	if(c && coarse > 0) { array.push_back(coarse); } else { c = false; }
	if(c && fine   > 0) { array.push_back(fine);   } else { c = false; }
	if(c && ultra  > 0) { array.push_back(ultra);  } else { c = false; }
	if(c && uber   > 0) { array.push_back(uber);   } else { c = false; }
	
	return ConvertIntegerArray(array, false);
}

/*static*/ bool GdtfConverter::ConvertDmxOffset(const TXString& inVal, const IXMLFileNodePtr& node, DMXAddress& coarse, DMXAddress& fine, DMXAddress& ultra, DMXAddress& uber)
{
	coarse 	= 0;
	fine 	= 0;
	ultra	= 0;
	uber 	= 0;

	TSint32Array array;
	if(ConvertIntegerArray(inVal, node, array))
	{
		for(size_t i = 0; i < array.size(); i++)
		{
			if(i==0) { coarse = array[i]; ASSERTN(kEveryone,coarse > 0); }
			if(i==1) { fine   = array[i]; ASSERTN(kEveryone,fine   > 0); }
			if(i==2) { ultra  = array[i]; ASSERTN(kEveryone,ultra  > 0); }
			if(i==3) { uber   = array[i]; ASSERTN(kEveryone,uber   > 0); }
		}
		
		return true;
	}
	
	return false;
}

CCieColor SceneData::GdtfConverter::ConvertCColor(const CieColor & color)
{
    return CCieColor(color.fx, color.fy, color.f_Y);
}

CieColor SceneData::GdtfConverter::ConvertCColor(const CCieColor & color)
{
    CieColor colStruct;

    colStruct.fx   = color.Get_x();
    colStruct.fy   = color.Get_y();
    colStruct.f_Y  = color.Get_Y_luminance();
    
    return colStruct;
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

/*static*/ bool GdtfConverter::ConvertEGdtfColorSampleEnum(const TXString& inVal, const IXMLFileNodePtr& node, EGdtfColorSample& outVal)
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
    GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_NoMatchInEnum_ConvertColorSample, node);
    SceneData::GdtfFixture::AddError(error);
       
    return true;
}

/*static*/ TXString GdtfConverter::ConvertEGdtfColorSpace(EGdtfColorSpace value)
{
    switch (value)
    {
    case EGdtfColorSpace::sRGB:			return XML_GDTF_ColorSpaceEnum_sRGB;
    case EGdtfColorSpace::Custom:		return XML_GDTF_ColorSpaceEnum_Custom;
    case EGdtfColorSpace::ProPhoto:		return XML_GDTF_ColorSpaceEnum_ProPhoto;
    case EGdtfColorSpace::ANSI:			return XML_GDTF_ColorSpaceEnumr_ANSI;
    }

	DSTOP((kEveryone, "Unknown Enum for EGdtfColorSpace"));

    return XML_GDTF_ColorSpaceEnum_sRGB;
}

/*static*/ bool GdtfConverter::ConvertEGdtfColorSpace(const TXString& inVal, const IXMLFileNodePtr& node, EGdtfColorSpace& outVal)
{
     if        (inVal == XML_GDTF_ColorSpaceEnum_sRGB)      { outVal = EGdtfColorSpace::sRGB; }     
     else if   (inVal == XML_GDTF_ColorSpaceEnum_Custom)    { outVal = EGdtfColorSpace::Custom; }
     else if   (inVal == XML_GDTF_ColorSpaceEnum_ProPhoto)  { outVal = EGdtfColorSpace::ProPhoto; }
     else if   (inVal == XML_GDTF_ColorSpaceEnumr_ANSI)     { outVal = EGdtfColorSpace::ANSI;  }
     else 
     {
        DSTOP((kEveryone, "Unknown Value for EGdtfColorSpace"));
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_NoMatchInEnum_ConvertColorSample, node);
        SceneData::GdtfFixture::AddError(error);
     }       

    return true;
}

/*static*/ TXString GdtfConverter::ConvertEGdtfInterpolationTo(EGdtfInterpolationTo value)
{

    switch (value)
    {
    case EGdtfInterpolationTo::Linear:  return XML_GDTF_InterpolationTo_Linear;
    case EGdtfInterpolationTo::Step:    return XML_GDTF_InterpolationTo_Step;
    case EGdtfInterpolationTo::Log:     return XML_GDTF_InterpolationTo_Log;
    }

	DSTOP((kEveryone, "Unknown Enum for EGdtfInterpolationTo"));

    return XML_GDTF_InterpolationTo_Linear;
}


/*static*/ bool GdtfConverter::ConvertEGdtfInterpolationTo(const TXString& inVal, const IXMLFileNodePtr& node, EGdtfInterpolationTo& outVal)
{
	if        (inVal == XML_GDTF_InterpolationTo_Linear)   { outVal = EGdtfInterpolationTo::Linear; }     
	else if   (inVal == XML_GDTF_InterpolationTo_Step)     { outVal = EGdtfInterpolationTo::Step; }
	else if   (inVal == XML_GDTF_InterpolationTo_Log)      { outVal = EGdtfInterpolationTo::Log; }     
	else if   (inVal.IsEmpty())    						{ outVal = EGdtfInterpolationTo::Linear; } 
	else 
	{
	DSTOP((kEveryone, "Unknown Value for EGdtfInterpolationTo"));
	GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_NoMatchInEnum_InterpolationTo, node);
	SceneData::GdtfFixture::AddError(error);

	outVal = EGdtfInterpolationTo::Linear;
	}
       
    return true;
}

/*static*/ TXString GdtfConverter::ConvertEGdtfCanHaveChildren(bool value)
{
    return value ? XML_GDTF_CanHaveChildren_Yes : XML_GDTF_CanHaveChildren_No;
}


/*static*/ bool GdtfConverter::ConvertEGdtfCanHaveChildren(const TXString& inVal, const IXMLFileNodePtr& node, bool& outVal)
{
	if        (inVal == XML_GDTF_CanHaveChildren_Yes)	{ outVal = true; }     
	else if   (inVal == XML_GDTF_CanHaveChildren_No)   	{ outVal = false; }    
	else if   (inVal.IsEmpty())    						{ outVal = true; } 
	else 
	{
		DSTOP((kEveryone, "Unknown Value for EGdtfCanHaveChildren"));
		GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_NoMatchInEnum_CanHaveChildren, node);
		SceneData::GdtfFixture::AddError(error);

		outVal = true;
	}
       
    return true;
}

/*static*/ TXString GdtfConverter::Convert2DPoint(double p_X, double p_Y)
{
	TDoubleArray array {p_X, p_Y};
	
	return ConvertDoubleArray(array, false);
}


/*static*/ bool GdtfConverter::Convert2DPoint(const TXString& inVal, const IXMLFileNodePtr& node, double& p_X, double& p_Y)
{
    p_X = 0.0;
	p_Y = 0.0;

	TDoubleArray array;
	if(ConvertDoubleArray(inVal, node, array) && array.size() >= 2)
	{
		p_X = array[0];
		p_Y = array[1];
		
		return true;
	}

	return false;
}

/*static*/ TXString GdtfConverter::ConvertBool(bool value)
{
	if(value) 	{ return TXString("true"); }
	else 		{ return TXString("false"); }
	
}


/*static*/ bool GdtfConverter::ConvertBool(const TXString& inVal, const IXMLFileNodePtr& node, bool& outVal)
{
	outVal = false;
	if(inVal == "true") 		{ outVal = true; }
	else if(inVal == "false") 	{ outVal = false; }
	else						{ return false; }

	return true;
}

/*static*/ TXString GdtfConverter::ConvertESourceType(GdtfDefines::ESourceType value)
{
    switch (value)
    {
		case ESourceType::NDI:				return XML_Val_SourceTypeNDI;
		case ESourceType::File:				return XML_Val_SourceTypeFile;
		case ESourceType::CITP:				return XML_Val_SourceTypeCITP;
		case ESourceType::CaptureDevice:	return XML_Val_SourceTypeCaptureDevice;
    }

	DSTOP((kEveryone, "Unknown Enum for ESourceType"));

    return XML_Val_SourceTypeNDI;
}


/*static*/ bool GdtfConverter::ConvertESourceType(const TXString& inVal, const IXMLFileNodePtr& node, GdtfDefines::ESourceType& outVal)
{
	if        (inVal == XML_Val_SourceTypeNDI)				{ outVal = ESourceType::NDI; }     
	else if   (inVal == XML_Val_SourceTypeFile)   			{ outVal = ESourceType::File; } 
	else if   (inVal == XML_Val_SourceTypeCITP)   			{ outVal = ESourceType::CITP; }
	else if   (inVal == XML_Val_SourceTypeCaptureDevice)	{ outVal = ESourceType::CaptureDevice; }   
	else if   (inVal.IsEmpty())    							{ outVal = ESourceType::NDI; } 
	else 
	{
		DSTOP((kEveryone, "Unknown Value for ESourceType"));
		outVal = ESourceType::NDI;
	}
       
    return true;
}

/*static*/ TXString GdtfConverter::ConvertEScaleHandlingType(GdtfDefines::EScaleHandlingType value)
{
    switch (value)
    {
		case EScaleHandlingType::ScaleKeepRatio:				return XML_Val_ScaleHandlingTypeScaleKeepRatio;
		case EScaleHandlingType::ScaleIgnoreRatio:				return XML_Val_ScaleHandlingTypeScaleIgnoreRatio;
		case EScaleHandlingType::KeepSizeCenter:				return XML_Val_ScaleHandlingTypeKeepSizeCenter;
    }

	DSTOP((kEveryone, "Unknown Enum for EScaleHandlingType"));

    return XML_Val_ScaleHandlingTypeScaleKeepRatio;
}


/*static*/ bool GdtfConverter::ConvertEScaleHandlingType(const TXString& inVal, const IXMLFileNodePtr& node, GdtfDefines::EScaleHandlingType& outVal)
{
	if        (inVal == XML_Val_ScaleHandlingTypeScaleKeepRatio)	{ outVal = EScaleHandlingType::ScaleKeepRatio; }     
	else if   (inVal == XML_Val_ScaleHandlingTypeScaleIgnoreRatio)  { outVal = EScaleHandlingType::ScaleIgnoreRatio; } 
	else if   (inVal == XML_Val_ScaleHandlingTypeKeepSizeCenter)	{ outVal = EScaleHandlingType::KeepSizeCenter; }  
	else if   (inVal.IsEmpty())    									{ outVal = EScaleHandlingType::ScaleKeepRatio; } 
	else 
	{
		DSTOP((kEveryone, "Unknown Value for EScaleHandlingType"));
		outVal = EScaleHandlingType::ScaleKeepRatio;
	}
       
    return true;
}


/*static*/ TXString GdtfConverter::ConvertLaserColorTypeEnum(GdtfDefines::EGdtfLaserColorType value)
{
    switch (value)
    {
		case EGdtfLaserColorType::RGB:							return XML_Val_LaserColorTypeRGB;
		case EGdtfLaserColorType::SingleWaveLength:				return XML_Val_LaserColorTypeSingleWaveLength;
    }

	DSTOP((kEveryone, "Unknown Enum for EGdtfLaserColorType"));

    return XML_Val_LaserColorTypeRGB;
}

/*static*/ bool GdtfConverter::ConvertLaserColorTypeEnum(const TXString& inVal, const IXMLFileNodePtr& node, GdtfDefines::EGdtfLaserColorType& outVal)
{
	if        (inVal == XML_Val_LaserColorTypeRGB)				{ outVal = EGdtfLaserColorType::RGB; }     
	else if   (inVal == XML_Val_LaserColorTypeSingleWaveLength) { outVal = EGdtfLaserColorType::SingleWaveLength; }
	else if   (inVal.IsEmpty())    								{ outVal = EGdtfLaserColorType::RGB; } 
	else 
	{
		DSTOP((kEveryone, "Unknown Value for EGdtfLaserColorType"));
		outVal = EGdtfLaserColorType::RGB;
	}
       
    return true;
}


/*static*/ TXString GdtfConverter::ConvertComponentTypeEnum(GdtfDefines::EGdtfComponentType value)
{
    switch (value)
    {
		case EGdtfComponentType::Input:				return XML_Val_ComponentTypeInput;
		case EGdtfComponentType::Output:			return XML_Val_ComponentTypeOutput;
		case EGdtfComponentType::PowerSource:		return XML_Val_ComponentTypePowerSource;
		case EGdtfComponentType::Consumer:			return XML_Val_ComponentTypeConsumer;
		case EGdtfComponentType::Fuse:				return XML_Val_ComponentTypeFuse;
		case EGdtfComponentType::NetworkProvider:	return XML_Val_ComponentTypeNetworkProvider;
		case EGdtfComponentType::NetworkInput:		return XML_Val_ComponentTypeNetworkInput;
		case EGdtfComponentType::NetworkOutput:		return XML_Val_ComponentTypeNetworkOutput;
		case EGdtfComponentType::NetworkInOut:		return XML_Val_ComponentTypeNetworkInOut;
    }

	DSTOP((kEveryone, "Unknown Enum for EGdtfComponentType"));

    return XML_Val_ComponentTypeInput;
}

/*static*/ bool GdtfConverter::ConvertComponentTypeEnum(const TXString& inVal, const IXMLFileNodePtr& node, GdtfDefines::EGdtfComponentType& outVal)
{
	if        (inVal == XML_Val_ComponentTypeInput)				{ outVal = EGdtfComponentType::Input; }     
	else if   (inVal == XML_Val_ComponentTypeOutput) 			{ outVal = EGdtfComponentType::Output; }
	else if   (inVal == XML_Val_ComponentTypePowerSource) 		{ outVal = EGdtfComponentType::PowerSource; }
	else if   (inVal == XML_Val_ComponentTypeConsumer) 			{ outVal = EGdtfComponentType::Consumer; }
	else if   (inVal == XML_Val_ComponentTypeFuse) 				{ outVal = EGdtfComponentType::Fuse; }
	else if   (inVal == XML_Val_ComponentTypeNetworkProvider) 	{ outVal = EGdtfComponentType::NetworkProvider; }
	else if   (inVal == XML_Val_ComponentTypeNetworkInput) 		{ outVal = EGdtfComponentType::NetworkInput; }
	else if   (inVal == XML_Val_ComponentTypeNetworkOutput) 	{ outVal = EGdtfComponentType::NetworkOutput; }
	else if   (inVal == XML_Val_ComponentTypeNetworkInOut) 		{ outVal = EGdtfComponentType::NetworkInOut; }
	else if   (inVal.IsEmpty())    								{ outVal = EGdtfComponentType::Input; } 
	else 
	{
		DSTOP((kEveryone, "Unknown Value for EGdtfComponentType"));
		outVal = EGdtfComponentType::Input;
	}
       
    return true;
}


/*static*/ TXString GdtfConverter::ConvertOrientationEnum(GdtfDefines::EGdtfOrientation value)
{
    switch (value)
    {
		case EGdtfOrientation::Left:	return XML_Val_OrientationLeft;
		case EGdtfOrientation::Right:	return XML_Val_OrientationRight;
		case EGdtfOrientation::Top:		return XML_Val_OrientationTop;
		case EGdtfOrientation::Bottom:	return XML_Val_OrientationBottom;
    }

	DSTOP((kEveryone, "Unknown Enum for EGdtfOrientation"));

    return XML_Val_OrientationLeft;
}

/*static*/ bool GdtfConverter::ConvertOrientationEnum(const TXString& inVal, const IXMLFileNodePtr& node, GdtfDefines::EGdtfOrientation& outVal)
{
	if      (inVal == XML_Val_OrientationLeft)		{ outVal = EGdtfOrientation::Left; }
	else if	(inVal == XML_Val_OrientationRight)		{ outVal = EGdtfOrientation::Right; }
	else if (inVal == XML_Val_OrientationTop)		{ outVal = EGdtfOrientation::Top; }
	else if (inVal == XML_Val_OrientationBottom)	{ outVal = EGdtfOrientation::Bottom; }

	else if (inVal.IsEmpty())    					{ outVal = EGdtfOrientation::Left; } 
	else 
	{
		DSTOP((kEveryone, "Unknown Value for EGdtfOrientation"));
		outVal = EGdtfOrientation::Left;
	}
       
    return true;
}


/*static*/ TXString GdtfConverter::ConvertFuseRatingEnum(GdtfDefines::EGdtfFuseRating value)
{
    switch (value)
    {
		case EGdtfFuseRating::B:	return XML_Val_FuseRatingB;
		case EGdtfFuseRating::C:	return XML_Val_FuseRatingC;
		case EGdtfFuseRating::D:	return XML_Val_FuseRatingD;
		case EGdtfFuseRating::K:	return XML_Val_FuseRatingK;
		case EGdtfFuseRating::Z:	return XML_Val_FuseRatingZ;
    }

	DSTOP((kEveryone, "Unknown Enum for EGdtfFuseRating"));

    return XML_Val_FuseRatingB;
}

/*static*/ bool GdtfConverter::ConvertFuseRatingEnum(const TXString& inVal, const IXMLFileNodePtr& node, GdtfDefines::EGdtfFuseRating& outVal)
{
	if		(inVal == XML_Val_FuseRatingB)	{ outVal = EGdtfFuseRating::B; }
	else if (inVal == XML_Val_FuseRatingC)	{ outVal = EGdtfFuseRating::C; }
	else if (inVal == XML_Val_FuseRatingD)	{ outVal = EGdtfFuseRating::D; }
	else if (inVal == XML_Val_FuseRatingK)	{ outVal = EGdtfFuseRating::K; }
	else if (inVal == XML_Val_FuseRatingZ)	{ outVal = EGdtfFuseRating::Z; }

	else if	(inVal.IsEmpty())    			{ outVal = EGdtfFuseRating::B; } 
	else 
	{
		DSTOP((kEveryone, "Unknown Value for EGdtfFuseRating"));
		outVal = EGdtfFuseRating::B;
	}
       
    return true;
}

/*static*/ TXString GdtfConverter::ConvertStructureTypeEnum(GdtfDefines::EGdtfStructureType value)
{
    switch (value)
    {
		case EGdtfStructureType::CenterLineBased:	return XML_Val_StructureTypeCenterLineBased;
		case EGdtfStructureType::Detail:			return XML_Val_StructureTypeDetail;
    }

	DSTOP((kEveryone, "Unknown Enum for EGdtfStructureType"));

    return XML_Val_StructureTypeCenterLineBased;
}

/*static*/ bool GdtfConverter::ConvertStructureTypeEnum(const TXString& inVal, const IXMLFileNodePtr& node, GdtfDefines::EGdtfStructureType& outVal)
{
	if		(inVal == XML_Val_StructureTypeCenterLineBased)	{ outVal = EGdtfStructureType::CenterLineBased; }
	else if (inVal == XML_Val_StructureTypeDetail)			{ outVal = EGdtfStructureType::Detail; }
	else if	(inVal.IsEmpty())    							{ outVal = EGdtfStructureType::CenterLineBased; }

	else 
	{
		DSTOP((kEveryone, "Unknown Value for EGdtfStructureType"));
		outVal = EGdtfStructureType::CenterLineBased;
	}
       
    return true;
}

/*static*/ TXString GdtfConverter::ConvertCrossSectionTypeEnum(GdtfDefines::EGdtfCrossSectionType value)
{
    switch (value)
    {
		case EGdtfCrossSectionType::TrussFramework:	return XML_Val_CrossSectionTypeTrussFramework;
		case EGdtfCrossSectionType::Tube:			return XML_Val_CrossSectionTypeTube;
    }

	DSTOP((kEveryone, "Unknown Enum for EGdtfCrossSectionType"));

    return XML_Val_CrossSectionTypeTrussFramework;
}

/*static*/ bool GdtfConverter::ConvertCrossSectionTypeEnum(const TXString& inVal, const IXMLFileNodePtr& node, GdtfDefines::EGdtfCrossSectionType& outVal)
{
	if		(inVal == XML_Val_CrossSectionTypeTrussFramework)	{ outVal = EGdtfCrossSectionType::TrussFramework; }
	else if (inVal == XML_Val_CrossSectionTypeTube)				{ outVal = EGdtfCrossSectionType::Tube; }
	else if	(inVal.IsEmpty())    								{ outVal = EGdtfCrossSectionType::TrussFramework; }

	else 
	{
		DSTOP((kEveryone, "Unknown Value for EGdtfCrossSectionType"));
		outVal = EGdtfCrossSectionType::TrussFramework;
	}
       
    return true;
}

/*static*/ TXString GdtfConverter::ConvertSupportTypeEnum(GdtfDefines::EGdtfSupportType value)
{
    switch (value)
    {
		case EGdtfSupportType::Rope:			return XML_Val_SupportTypeRope;
		case EGdtfSupportType::GroundSupport:	return XML_Val_SupportTypeGroundSupport;
    }

	DSTOP((kEveryone, "Unknown Enum for EGdtfSupportType"));

    return XML_Val_SupportTypeRope;
}

/*static*/ bool GdtfConverter::ConvertSupportTypeEnum(const TXString& inVal, const IXMLFileNodePtr& node, GdtfDefines::EGdtfSupportType& outVal)
{
	if		(inVal == XML_Val_SupportTypeRope)			{ outVal = EGdtfSupportType::Rope; }
	else if (inVal == XML_Val_SupportTypeGroundSupport)	{ outVal = EGdtfSupportType::GroundSupport; }
	else if	(inVal.IsEmpty())    						{ outVal = EGdtfSupportType::Rope; }

	else 
	{
		DSTOP((kEveryone, "Unknown Value for EGdtfSupportType"));
		outVal = EGdtfSupportType::Rope;
	}
       
    return true;
}

/*static*/ TXString GdtfConverter::ConvertSubPhysicalUnitTypeEnum(GdtfDefines::EGdtfSubPhysicalUnitType value)
{
    switch (value)
    {
		case EGdtfSubPhysicalUnitType::PlacementOffset:	return XML_Val_SubPhysicalUnitTypePlacementOffset;
		case EGdtfSubPhysicalUnitType::Amplitude:		return XML_Val_SubPhysicalUnitTypeAmplitude;
		case EGdtfSubPhysicalUnitType::AmplitudeMin:	return XML_Val_SubPhysicalUnitTypeAmplitudeMin;
		case EGdtfSubPhysicalUnitType::AmplitudeMax:	return XML_Val_SubPhysicalUnitTypeAmplitudeMax;
		case EGdtfSubPhysicalUnitType::Duration:		return XML_Val_SubPhysicalUnitTypeDuration;
		case EGdtfSubPhysicalUnitType::DutyCycle:		return XML_Val_SubPhysicalUnitTypeDutyCycle;
		case EGdtfSubPhysicalUnitType::TimeOffset:		return XML_Val_SubPhysicalUnitTypeTimeOffset;
		case EGdtfSubPhysicalUnitType::MinimumOpening:	return XML_Val_SubPhysicalUnitTypeMinimumOpening;
		case EGdtfSubPhysicalUnitType::Value:			return XML_Val_SubPhysicalUnitTypeValue;
		case EGdtfSubPhysicalUnitType::RatioHorizontal:	return XML_Val_SubPhysicalUnitTypeRatioHorizontal;
		case EGdtfSubPhysicalUnitType::RatioVertical:	return XML_Val_SubPhysicalUnitTypeRatioVertical;
    }

	DSTOP((kEveryone, "Unknown Enum for EGdtfSubPhysicalUnitType"));

    return XML_Val_SubPhysicalUnitTypePlacementOffset;
}

/*static*/ bool GdtfConverter::ConvertSubPhysicalUnitTypeEnum(	const TXString& inVal, const IXMLFileNodePtr& node, GdtfDefines::EGdtfSubPhysicalUnitType& outVal)
{
	if		(inVal == XML_Val_SubPhysicalUnitTypePlacementOffset)	{ outVal = EGdtfSubPhysicalUnitType::PlacementOffset; }
	else if (inVal == XML_Val_SubPhysicalUnitTypeAmplitude)			{ outVal = EGdtfSubPhysicalUnitType::Amplitude; }
	else if (inVal == XML_Val_SubPhysicalUnitTypeAmplitudeMin)		{ outVal = EGdtfSubPhysicalUnitType::AmplitudeMin; }
	else if (inVal == XML_Val_SubPhysicalUnitTypeAmplitudeMax)		{ outVal = EGdtfSubPhysicalUnitType::AmplitudeMax; }
	else if (inVal == XML_Val_SubPhysicalUnitTypeDuration)			{ outVal = EGdtfSubPhysicalUnitType::Duration; }
	else if (inVal == XML_Val_SubPhysicalUnitTypeDutyCycle)			{ outVal = EGdtfSubPhysicalUnitType::DutyCycle; }
	else if (inVal == XML_Val_SubPhysicalUnitTypeTimeOffset)		{ outVal = EGdtfSubPhysicalUnitType::TimeOffset; }
	else if (inVal == XML_Val_SubPhysicalUnitTypeMinimumOpening)	{ outVal = EGdtfSubPhysicalUnitType::MinimumOpening; }
	else if (inVal == XML_Val_SubPhysicalUnitTypeValue)				{ outVal = EGdtfSubPhysicalUnitType::Value; }
	else if (inVal == XML_Val_SubPhysicalUnitTypeRatioHorizontal)	{ outVal = EGdtfSubPhysicalUnitType::RatioHorizontal; }
	else if (inVal == XML_Val_SubPhysicalUnitTypeRatioVertical)		{ outVal = EGdtfSubPhysicalUnitType::RatioVertical; }
	else if	(inVal.IsEmpty())    									{ outVal = EGdtfSubPhysicalUnitType::PlacementOffset; }

	else 
	{
		DSTOP((kEveryone, "Unknown Value for EGdtfSubPhysicalUnitType"));
		outVal = EGdtfSubPhysicalUnitType::PlacementOffset;
	}
       
    return true;
}


bool SceneDataZip::AddFileToZip(IZIPFilePtr& zipFile, const IFileIdentifierPtr& file, ERessourceType resType, bool deleteFile, bool mustExist)
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
	TXString nameFile;	file->GetFileName(nameFile);
	
    // Append the SubFoldername for resources.
    nameFile = SceneData::SceneDataZip::GetResourceSubFolder(resType) + nameFile;

	//-------------------------------------------------------------------------------------------------
	// Write the  file
	zipFile->AddFile(nameFile, file);
	
	//-------------------------------------------------------------------------------------------------
	// HouseKeeping
	if (deleteFile) {
		file->DeleteOnDisk();
	}
	
	return true;
	
}

void SceneDataZip::AddFileToZip(IZIPFilePtr& zipFile, ISceneDataZipBuffer& buffer,const TXString &name)
{
    //-------------------------------------------------------------------------------------------------
    // Write the  file
    zipFile->AddFile(name, &buffer);
}

TXString SceneData::SceneDataZip::GetResourceSubFolder(ERessourceType resType)
{    
    switch (resType) 
    {
    case ERessourceType::ImageWheel:
        return "wheels" + TXString(kSeperator);
    case ERessourceType::Model3DS:
        return "models" + TXString(kSeperator) + "3ds" + TXString(kSeperator);
	case ERessourceType::Model3DSLow:
        return "models" + TXString(kSeperator) + "3ds_low" + TXString(kSeperator);
	case ERessourceType::Model3DSHigh:
        return "models" + TXString(kSeperator) + "3ds_high" + TXString(kSeperator);
    case ERessourceType::ModelSVG:
        return "models" + TXString(kSeperator) + "svg" + TXString(kSeperator);
	case ERessourceType::ModelGLTF:
        return "models" + TXString(kSeperator) + "gltf" + TXString(kSeperator);
	case ERessourceType::ModelGLTFLow:
        return "models" + TXString(kSeperator) + "gltf_low" + TXString(kSeperator);
	case ERessourceType::ModelGLTFHigh:
        return "models" + TXString(kSeperator) + "gltf_high" + TXString(kSeperator);
	case ERessourceType::ModelSVGSide:
        return "models" + TXString(kSeperator) + "svg_side" + TXString(kSeperator);
	case ERessourceType::ModelSVGFront:
        return "models" + TXString(kSeperator) + "svg_front" + TXString(kSeperator);
    case ERessourceType::RessoureFixture:
        return  "";
	default:
		break;
    }    

    DSTOP((kEveryone, "Unexpected Enum for GetResourceSubFolder(ERessourceType resType)"));

    return  "";
}


/*static*/ bool GdtfConverter::Deserialize(const TXString& value, const IXMLFileNodePtr& node,std::vector<double>& doubleArr)
{
	// Split string
	TXString strVal = value;
	
	// Find first entry
	ptrdiff_t pos = strVal.Find(",");
    if (strVal.Find(",") == -1)
    {
        // TODO
        // (line column)
        GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_NoCommaFound, node);
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

/*static*/ bool GdtfConverter::Deserialize(const TXString& value, const IXMLFileNodePtr& node, TSint32Array & intArray, TXChar seperatorChar)
{
	// Split string
	TXString strVal = value;
	
	// Find first entry
	ptrdiff_t pos = strVal.Find(seperatorChar);
	while (pos > 0 )
	{
		// Copy string
		TXString strValInner;
		for (ptrdiff_t i = 0; i < pos; i++)	{ strValInner += strVal.GetAt(i); }
		
		// Try to cast
		intArray.push_back(strValInner.atoi());
		
		// Delete and find next
		strVal.Delete(0, pos + 1);
		pos = strVal.Find(seperatorChar);
	}
	
	// Delete and find next
	intArray.push_back(strVal.atoi());
	
	return true;
}

/*static*/ bool GdtfConverter::DeserializeUTC_Date(const TXString& value, const IXMLFileNodePtr& node, TSint32Array& intArray)
/* Convert from UTC Format (yyyy-mm-ddThh:mm:ss) to intArray */
{
	// Split string
	TXString strVal = value;
	size_t strLength = strVal.GetLength();

    ASSERTN(kEveryone, strLength == 19); // UTC Strings always have a length of 19 chars!

    //--------------------------------------------------------------------------------
	// Split Date and time
	ptrdiff_t pos = strVal.Find("T");
    ASSERTN(kEveryone, pos > 0);
	if (pos > 0)
	{
		// Copy Strings in container
		TXString strValCalender;
        for (ptrdiff_t i = 0; i < pos; i++) {strValCalender += strVal.GetAt(i); }
		
        TXString strValClock;
		for (size_t i = pos+1 ; i < strLength; i++) { strValClock += strVal.GetAt(i);}
        
        // Date
        TSint32Array calender;
		Deserialize(strValCalender, node, calender, '-');
        ASSERTN(kEveryone, calender.size() == 3);
        
        // Time
        TSint32Array time;
		Deserialize(strValClock, node, time, ':');
        ASSERTN(kEveryone, time.size() == 3);

        if(time.size() == 3 && calender.size() == 3)
        {
            intArray.insert(intArray.end(), calender.begin(), calender.end());
            intArray.insert(intArray.end(), time.begin(), time.end());
        }
	}	

	return true;
}

/*static*/ bool GdtfConverter::ConvertDMXValue_UnitTest(const char* value, EGdtfChannelBitResolution chanlReso,	DmxValue& intValue)
{
	return GdtfConverter::ConvertDMXValue(value,nullptr, chanlReso, intValue);
}

void GdtfConverter::TraverseNodes(IXMLFileNodePtr root, const TXString& childContainerNodeName, const TXString& childNodeName, TProcessNodeCall processNodeFunction)
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

GdtfDefines::EGdtfPhysicalUnit GdtfConverter::GetUnitFromSubPhysical(GdtfDefines::EGdtfSubPhysicalUnitType subPhysicalUnit)
{
	switch(subPhysicalUnit)
	{
		case EGdtfSubPhysicalUnitType::PlacementOffset: return EGdtfPhysicalUnit::Angle;
		case EGdtfSubPhysicalUnitType::Amplitude: 		return EGdtfPhysicalUnit::Percent;
		case EGdtfSubPhysicalUnitType::AmplitudeMin: 	return EGdtfPhysicalUnit::Percent;
		case EGdtfSubPhysicalUnitType::AmplitudeMax: 	return EGdtfPhysicalUnit::Percent;
		case EGdtfSubPhysicalUnitType::Duration: 		return EGdtfPhysicalUnit::Time;
		case EGdtfSubPhysicalUnitType::DutyCycle: 		return EGdtfPhysicalUnit::Percent;
		case EGdtfSubPhysicalUnitType::TimeOffset: 		return EGdtfPhysicalUnit::Percent;
		case EGdtfSubPhysicalUnitType::MinimumOpening: 	return EGdtfPhysicalUnit::Percent;
		case EGdtfSubPhysicalUnitType::Value: 			return EGdtfPhysicalUnit::Percent;
		case EGdtfSubPhysicalUnitType::RatioHorizontal: return EGdtfPhysicalUnit::Percent;
		case EGdtfSubPhysicalUnitType::RatioVertical:	return EGdtfPhysicalUnit::Percent;
		default: 										return EGdtfPhysicalUnit::Percent;
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



VCOMError ISceneDataZipBuffer::WriteToFile(IFileIdentifierPtr file) 
{
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

/*static*/ bool GdtfConverter::ConvertHexValue(const TXString & inVal, const IXMLFileNodePtr & node, size_t& outValue)
{
	outValue = 0;
	if(inVal.Left(2).Equal(TXString("0x")))
	{
		TXString hexCont = inVal.Mid(2);
		hexCont.MakeUpper();
		for(size_t i = 0; i < hexCont.GetLength(); i++)
		{
			outValue = outValue*16;
			size_t fact = 0;
			TXChar c = hexCont.GetAt(i); 
			switch (c) 
			{ 	
				case TXChar('0'): fact =  0; break;
				case TXChar('1'): fact =  1; break;
				case TXChar('2'): fact =  2; break;
				case TXChar('3'): fact =  3; break;
				case TXChar('4'): fact =  4; break;
				case TXChar('5'): fact =  5; break;
				case TXChar('6'): fact =  6; break;
				case TXChar('7'): fact =  7; break;
				case TXChar('8'): fact =  8; break;
				case TXChar('9'): fact =  9; break;
				case TXChar('A'): fact = 10; break;
				case TXChar('B'): fact = 11; break;
				case TXChar('C'): fact = 12; break;
				case TXChar('D'): fact = 13; break;
				case TXChar('E'): fact = 14; break;
				case TXChar('F'): fact = 15; break;
				default: 
				{
					GdtfParsingError error (GdtfDefines::EGdtfParsingError::eHexConversion_InvalidChar, node);
					SceneData::GdtfFixture::AddError(error);
					return false; 
				} break;
			}
			outValue += fact; 
		}
	}
	else if( ! inVal.IsEmpty())
	{
		GdtfParsingError error (GdtfDefines::EGdtfParsingError::eHexConversion_InvalidChar, node);
		SceneData::GdtfFixture::AddError(error);
	}
	
	
	if(outValue > 65535)
	{
		GdtfParsingError error (GdtfDefines::EGdtfParsingError::eHexConversion_ValueToHight, node);
        SceneData::GdtfFixture::AddError(error);
		outValue = 65535;
		return false;
	}
	return true;
}

/*static*/ TXString GdtfConverter::ConvertHexValue(size_t value)
{
	TXString outString ("0x");
	if(value > 65535)
	{
		return TXString("0xFFFF");
	}
	if(value == 0)
	{
		return TXString("0x0");
	}
	while(value > 0)
	{
		size_t cCode = value % 16;
		value = (value-cCode)/16;
		TXString c = TXString('0');
		switch (cCode)
		{
			case  0: c = TXString('0'); break;
			case  1: c = TXString('1'); break;
			case  2: c = TXString('2'); break;
			case  3: c = TXString('3'); break;
			case  4: c = TXString('4'); break;
			case  5: c = TXString('5'); break;
			case  6: c = TXString('6'); break;
			case  7: c = TXString('7'); break;
			case  8: c = TXString('8'); break;
			case  9: c = TXString('9'); break;
			case 10: c = TXString('A'); break;
			case 11: c = TXString('B'); break;
			case 12: c = TXString('C'); break;
			case 13: c = TXString('D'); break;
			case 14: c = TXString('E'); break;
			case 15: c = TXString('F'); break;
		
			default:
				break;
		}
		outString.Insert(2, c);
	}
	return outString;
}

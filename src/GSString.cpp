//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


/* Includes */
/* -------- */
#include "StdHeaders.h"	// DO NOT MOVE THIS LINE FROM BEING FIRST NON-COMMENT LINE.  [DMB, 10/30/95]

#if !_WINDOWS || _MINICAD_ || _GSESDK_
// Windows externals get this module's code from "MiniCad.lib". [DMB 11/25/96]

#include <stdarg.h>

#if _WINDOWS
	
	#include <Usp10.h>
	#include "Kernel/GSUtil.h" // For inrange function; not sure where why Mac is okay
#else
	#include <ctype.h>
#endif

#if _WINDOWS
	#include "Shlwapi.h"
#endif

#include "GSString.h"

#if GS_MAC
#include <CoreFoundation/CoreFoundation.h>
#endif

#if GS_WIN	// Windows
	#include <Windows.h>  
	#include <MBCType.h>
	#include <MBString.h>
#elif GS_LIN
	#include <locale>
	#include <codecvt>
#else	// Mac
	#include <Carbon/Carbon.h>
#endif

#include "VectorworksSDK.h"

// This must follow all header files.
#undef THIS_FILE
DECLARE_THIS_FILE


/*============================================================================*/
/*============================================================================*/

void NNAUppercaseText(char* textPtr, Sint32 len, int scriptCode)
{
#if GS_MAC
	CFStringRef nonUppercaseString = CFStringCreateWithBytes(NULL,
															 (Uint8*)textPtr,
															 len,
															 kCFStringEncodingUTF8,
															 false);
	
	if (!VERIFYN(kEveryone, nonUppercaseString != NULL))
		return;
	
	CFMutableStringRef candidateString = CFStringCreateMutableCopy(NULL,
																   len,
																   nonUppercaseString);
	
	CFRelease(nonUppercaseString);
	if (!VERIFYN(kEveryone, nonUppercaseString != NULL))
		return;
	
	CFStringUppercase(candidateString, CFLocaleGetSystem());
	
	CFStringGetBytes(candidateString,
					 CFRangeMake(0, len),
					 kCFStringEncodingUTF8,
					 0,
					 false,
					 (Uint8*)textPtr,
					 len,
					 NULL);
	
	CFRelease(candidateString);
#elif GS_LIN
	// LINUX_IMPLEMENTATION - done
	std::string str( textPtr, len );
	std::transform( str.begin(), str.end(), str.begin(), ::toupper );
#else
	LCID locale = LOCALE_SYSTEM_DEFAULT;
	if (scriptCode == -2)
	{
		locale = LOCALE_USER_DEFAULT;
	}

	// Non-Unicode
	LCMapStringA(locale, LCMAP_UPPERCASE, textPtr, len, textPtr, len);
#endif
}



void NNANumToString(Sint32 num, unsigned char* str, size_t strSize)
{
	TXString::ToStringInt(num).CopyInto(str, strSize);
}

void NNANumToString(Sint32 num, TXString& str)
{
	str = TXString::ToStringInt(num);
}

void NNAStringToNum(const unsigned char * theString, Sint32 *theNum)
{
	if (!VERIFYN(kEveryone, theNum != NULL))
		return;

	TXString candidateString(theString);
	*theNum = candidateString.atoi();
}

/**************************************************/
/* Unicode Character String Manipulation Routines */
/**************************************************/


/***************************************/
/* Unicode Encoding Converter Routines */
/***************************************/

//*****************************************************************************
//
// Function Name:  StringToUnicodeMaxChars
//
// Description:
//	Returns the maximum number of Unicode characters (with a terminating NULL
//	word) required to represent a non-Unicode C- or Pascal-style string of the
//	specified number of character bytes.  Note that this is completely
//	simplistic, is based only on the length of the string and ignores its
//	encoding.
//
// Parameters:
//	srcLen - Number of character bytes in the C- or Pascal-style string to be
//	          converted (simply call strlen or GetLength on the string)
//
// Return Value:
//	Maximum number of Unicode characters (including NULL terminator) required
//	to represent a string of the specified length in a non-Unicode encoding
//
// Created by:  Michael Hartman, January 2005
//
//*****************************************************************************

size_t StringToUnicodeMaxChars (size_t srcLen)
{
	return(srcLen + 1);
} // StringToUnicodeMaxChars


//*****************************************************************************
//
// Function Name:  StringToUnicode (character array version)
//
// Description:
//	Converts the characters of the specified encoding in a character array to
//	an array of Unicode characters in UTF-16 encoding form.  Precomposed
//	Unicode characters are preferred in the converted string (but the
//	Macintosh does not permit specifying this as of OS X 10.3.7).
//	A terminating NULL word is NOT added following the converted characters.
//
// Parameters:
//	srcEncoding - Platform-specific text encoding value for the source
//	               string's characters
//	srcArray    - Pointer to an array containing the characters to be
//	               converted; these may be 8- or 16-bit depending on encoding
//	srcLen      - Number of 8-bit bytes (always) in srcArray containing
//	               characters to be converted
//	dstUCArray  - Pointer to an array of 16-bit words for the converted
//	               Unicode characters to be returned in (no terminator added)
//	maxDstChars - Maximum number of 16-bit words that dstUCArray can hold (note
//	               that surrogate and decomposed characters are > 16 bits)
//	pDstLen     - Returns the number of 16-bit words the converted characters
//	               occupy in dstUCArray
//
// Return Value:
//	Whether the conversion was successful.  Failures include not enough space
//	in the destination array; source characters that can't be converted are
//	not considered a failure [a richer return type could be considered].
//
// Created by:  Michael Hartman, December 2004
//
//*****************************************************************************

bool StringToUnicode (GSTextEncoding srcEncoding, const char* srcArray,
                       size_t srcLen, UCCharPtr dstUCArray,
                       size_t maxDstChars, size_t* pDstLen)
{
	bool	success = false;
	
	/* Check the Destination Array Provided */
	/* ------------------------------------ */
	if (maxDstChars == 0) {
		*pDstLen = 0;
		return(false);
	}
	if (!VERIFYPOINTER(kMike, dstUCArray, (maxDstChars*sizeof(UCChar)))) {
		*pDstLen = 0;
		return(false);
	}
	
	/* Convert the Supplied Characters to Unicode */
	/* ------------------------------------------ */
	if (srcLen == 0) {
		/* Source Array Is Empty */
		/* --------------------- */
		dstUCArray[0] = NULL;  // Just for grins; room available in this case
		*pDstLen = 0;
		success = true;
		}
	else {
		/* Source Array Is Not Empty */
		/* ------------------------- */
#if GS_WIN
		/* Convert the Source Text in the Specified */
		/*  Encoding to Unicode and Check for Error */
		// Non-zero options are a problem for some encodings, but we don't
		// want accented Unicode characters becoming two characters, so
		// we use MB_PRECOMPOSED unless srcEncoding is CP_SYMBOL; if this
		// is changed, a corresponding change should be made to the
		// WideCharToMultiByte call in UnicodeToString below
		DWORD mapOptions;
		if (srcEncoding == CP_SYMBOL || CP_UTF8)
			mapOptions = 0;
		else
			mapOptions = MB_PRECOMPOSED;
		*pDstLen = MultiByteToWideChar(srcEncoding, mapOptions, 
		                 srcArray, (int)srcLen, (LPWSTR) dstUCArray, (int)maxDstChars);
		success = (*pDstLen != 0);  // Zero always returned on failure, unlike Mac
#elif GS_LIN
		// LINUX_IMPLEMENTATION - done
		size_t ss = sizeof(TXString);
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring str = converter.from_bytes( std::string(srcArray, srcLen) );
		*pDstLen = str.size();
		if ( dstUCArray )
		{
			for(size_t i=0; i<*pDstLen; i++)
				dstUCArray[i] = str[i];
		}
#else
        // This was sometimes called with strings that weren't null-terminated.
        // Just to be sure, create temporary string and append null.
        char tempString[srcLen+1];
        strncpy(tempString, srcArray, srcLen);
        tempString[srcLen] = '\0';
        CFStringRef cfStr = CFStringCreateWithCString(NULL, tempString, srcEncoding);
        if (cfStr)
        {
            CFIndex len = CFStringGetLength(cfStr);
            if (len)
            {
                CFStringGetBytes(cfStr, CFRangeMake(0, len), kCFStringEncodingUnicode, '?', false, (UInt8 *)dstUCArray, maxDstChars * sizeof(UCChar), (CFIndex*)pDstLen);
                *pDstLen /= sizeof(UniChar);
                success = true;
            }
			else
			{
				*pDstLen = 0;
				success = false;
			}
            CFRelease(cfStr);
        }
#endif  // GS_WIN
	}
	return(success);
} // StringToUnicode


//*****************************************************************************
//
// Function Name:  StringToUnicode (C string version)
//
// Description:
//	Converts the characters of the specified encoding in a C-style string to
//	an array of Unicode characters in UTF-16 encoding form.  Precomposed
//	Unicode characters are preferred in the converted string (but the
//	Macintosh does not permit specifying this as of OS X 10.3.7).
//	A terminating NULL word is added following the converted characters.
//
// Parameters:
//	srcEncoding - Platform-specific text encoding value for the source
//	               string's characters
//	srcStr      - Pointer to a C-style string containing the characters to be
//	               converted
//	dstUCStr    - Pointer to an array of 16-bit words for the converted
//	               Unicode characters to be returned in (NULL-word terminated)
//	maxDstChars - Maximum number of 16-bit words that dstUCStr can hold (note
//	               that surrogate and decomposed characters are > 16 bits);
//	               to handle all encodings safely, this must be:
//	               maxDstChars = (strlen(srcStr) * 3) + 1
//	pDstLen     - Returns the number of 16-bit words the converted string
//	               occupies in dstUCStr, not including the NULL-word terminator
//
// Return Value:
//	Whether the conversion was successful.  Failures include not enough space
//	in the destination array; source characters that can't be converted are
//	not considered a failure [a richer return type could be considered].
//
// Created by:  Michael Hartman, December 2004
//
//*****************************************************************************

bool StringToUnicode (GSTextEncoding srcEncoding, const char* srcStr,
              UCStrPtr dstUCStr, size_t maxDstChars, size_t* pDstLen)
{
	bool	success;
	
	/* Call the Character Array Version and Append   */
	/*  a NULL-Word Terminator to the Returned Array */
	success = StringToUnicode(srcEncoding, srcStr, strlen(srcStr),
	                           dstUCStr, (maxDstChars-1), pDstLen);
	if (success || (*pDstLen < maxDstChars))
	  dstUCStr[*pDstLen] = NULL;
	return(success);
} // StringToUnicode


//*****************************************************************************
//
// Function Name:  StringToUnicode (Pascal string version)
//
// Description:
//	Converts the characters of the specified encoding in a Pascal-style string
//	to an array of Unicode characters in UTF-16 encoding form.  Precomposed
//	Unicode characters are preferred in the converted string (but the
//	Macintosh does not permit specifying this as of OS X 10.3.7).
//	A terminating NULL word is added following the converted characters.
//	Note that this routine simply converts the source string to C-style and
//	calls its routine.
//
// Parameters:
//	srcEncoding - Platform-specific text encoding value for the source
//	               string's characters
//	srcStr      - Pascal-style string containing the characters to be converted
//	dstUCStr    - Pointer to an array of 16-bit words for the converted
//	               Unicode characters to be returned in (NULL-word terminated)
//	maxDstChars - Maximum number of 16-bit words that dstUCStr can hold (note
//	               that surrogate and decomposed characters are > 16 bits);
//	               to handle all encodings safely, this must be:
//	               maxDstChars = (GetLength(srcStr) * 3) + 1
//	pDstLen     - Returns the number of 16-bit words the converted string
//	               occupies in dstUCStr, not including the NULL-word terminator
//
// Return Value:
//	Whether the conversion was successful.  Failures include not enough space
//	in the destination array; source characters that can't be converted are
//	not considered a failure [a richer return type could be considered].
//
// Created by:  Michael Hartman, December 2004
//
//*****************************************************************************

bool StringToUnicode (GSTextEncoding srcEncoding, ConstGSStr255Param srcStr,
              UCStrPtr dstUCStr, size_t maxDstChars, size_t* pDstLen)
{
	bool	success;
	
	/* Call the Character Array Version and Append   */
	/*  a NULL-Word Terminator to the Returned Array */
	success = StringToUnicode(srcEncoding, (char*)&srcStr[1], GetLength(srcStr),
	                           dstUCStr, (maxDstChars-1), pDstLen);
	if (success || (*pDstLen < maxDstChars))
	  dstUCStr[*pDstLen] = NULL;
	return(success);
} // StringToUnicode


//*****************************************************************************
//
// Function Name:  UnicodeToStringMaxChars
//
// Description:
//	Returns the maximum number of UTF-8 bytes in a C- or
//	Pascal-style string (with a terminating NULL character or preceding length
//	byte) required to represent the specified number of Unicode characters.
//	Note that this calculates
//	the worst case.  But using this and reallocating the string buffer
//	after calling UnicodeToString should usually be faster than doing the
//	conversion an extra time beforehand to get the character count.
//
// Parameters:
//	srcLen - Number of characters in the Unicode string to be converted
//
// Return Value:
//	Maximum number of UTF-8 bytes (including NULL terminator
//	or preceding length byte) required to represent a Unicode string of the
//	specified length in UTF-8 encoding
//
// Created by:  Michael Hartman, January 2005
//
//*****************************************************************************

size_t UnicodeToStringMaxChars (size_t srcLen)
{
	return((size_t)(srcLen * 4) + 1);
} // UnicodeToStringMaxChars


//*****************************************************************************
//
// Function Name:  UnicodeToString (character array version)
//
// Description:
//	Converts the characters of Unicode encoding and UTF-16 form in an array to
//	a character array in the specified encoding.  A terminating NULL byte is
//	NOT added following the converted characters.
//
// Parameters:
//	dstEncoding - Platform-specific text encoding value for the destination
//	               string's characters
//	srcUCArray  - Pointer to an array of 16-bit words containing the Unicode
//	               characters to be converted
//	srcLen      - Number of words in srcUCArray containing characters to be
//	               converted
//	dstArray    - Pointer to an array for the converted characters to be
//	               returned in (may be 8- or 16-bit depending on encoding)
//	maxDstBytes - Maximum number of 8-bit bytes (always) that dstArray can
//	               hold; to handle all encodings, this must be:
//	               maxDstChars = (srcLen * 1.5) + 1
//	               (just call UnicodeToStringMaxChars)
//	pDstLen     - Returns the number of 8-bit bytes the converted characters
//	               occupy in dstArray
//
// Return Value:
//	Whether the conversion was successful.  Failures include not enough space
//	in the destination string; source characters that can't be converted are
//	not considered a failure [a richer return type could be considered].
//
// Created by:  Michael Hartman, December 2004
//
//*****************************************************************************

bool UnicodeToString (GSTextEncoding dstEncoding, ConstUCCharPtr srcUCArray,
      size_t srcLen, char* dstArray, size_t maxDstBytes, size_t* pDstLen)
{
	/* Check the Destination String Provided */
	/* ------------------------------------- */
	if (maxDstBytes == 0) return(false);
	if (!VERIFYPOINTER(kMike, dstArray, maxDstBytes)) {
		*pDstLen = 0;
		return(false);
	}
	
	if (srcLen == 0) {
		/* Source Array Is Empty */
		/* --------------------- */
		dstArray[0] = NULL;  // Just for grins; room available in this case
		*pDstLen = 0;
		return(true);
	}
	else {
		/* Source Array Is Not Empty */
		/* ------------------------- */
#if GS_WIN
		
		/* Convert the Unicode Text to the Specified */
		/*  Destination Encoding and Check for Error */
		// Non-zero mapping options are a problem with some encodings,
		//  but we don't want accented Unicode characters becoming two
		*pDstLen = WideCharToMultiByte(dstEncoding, WC_COMPOSITECHECK, (LPCWSTR) srcUCArray, 
		            (int)srcLen, dstArray, (int)maxDstBytes, NULL, NULL);
		
		if (*pDstLen == 0)
			return false;

		return true;
#elif GS_LIN
		// LINUX_IMPLEMENTATION - done
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::string str = converter.to_bytes( std::wstring((const wchar_t*)srcUCArray, srcLen) );
		*pDstLen = str.size();
		if ( dstArray )
		{
			for(size_t i=0; i<*pDstLen; i++)
				dstArray[i] = str[i];
		}
#else
        bool success = false;
		CFStringRef cfStr = CFStringCreateWithCharacters(NULL, srcUCArray, srcLen);
        if (cfStr)
        {
            int len = CFStringGetLength(cfStr);
            CFRange fullRange = CFRangeMake(0, len);            
            if (CFStringGetBytes(cfStr, fullRange, dstEncoding, '?', 0, (UInt8 *)dstArray, maxDstBytes, (CFIndex *)pDstLen))
                success = true;
            
            CFRelease(cfStr);
        }
        
        return success;
#endif  // GS_WIN
	}
} // UnicodeToString


//*****************************************************************************
//
// Function Name:  UnicodeToString (C string version)
//
// Description:
//	Converts the characters of Unicode encoding and UTF-16 form in an array to
//	a C-style string in the specified encoding.
//
// Parameters:
//	dstEncoding - Platform-specific text encoding value for the destination
//	               string's characters
//	srcUCStr    - Pointer to an array of 16-bit words containing the Unicode
//	               characters to be converted, terminated with a NULL word
//	dstStr      - Pointer to a C-style string for the converted characters
//	               to be returned in
//	maxDstBytes - Maximum number of 8-bit bytes that dstStr can hold
//	               (including the terminating NULL); to handle all
//	               encodings, this must be:
//	               maxDstChars = (StringLength(srcUCStr) * 1.5) + 1
//	               (just call UnicodeToStringMaxChars)
//	pDstLen     - Returns the number of 8-bit bytes the converted characters
//	               occupy in dstStr, not including the terminating NULL byte
//
// Return Value:
//	Whether the conversion was successful.  Failures include not enough space
//	in the destination string; source characters that can't be converted are
//	not considered a failure [a richer return type could be considered].
//
// Created by:  Michael Hartman, December 2004
//
//*****************************************************************************

bool UnicodeToString (GSTextEncoding dstEncoding, ConstUCStrPtr srcUCStr,
                       char* dstStr, size_t maxDstBytes, size_t* pDstLen)
{
	bool		success;
	
	/* Call the Character Array Version and Append   */
	/*  a NULL-Byte Terminator to the Returned Array */
	success = UnicodeToString(dstEncoding, srcUCStr, StringLength(srcUCStr),
	                           dstStr, (maxDstBytes-1), pDstLen);
	if (success || (*pDstLen < maxDstBytes))
	  dstStr[*pDstLen] = NULL;
	return(success);
} // UnicodeToString


//*****************************************************************************
//
// Function Name:  UnicodeToString (Pascal string version)
//
// Description:
//	Converts the characters of Unicode encoding and UTF-16 form in an array to
//	a Pascal-style string in the specified encoding.  Note that this routine
//	simply calls the C-style routine and converts its result to Pascal-style.
//
// Parameters:
//	dstEncoding - Platform-specific text encoding value for the destination
//	               string's characters
//	srcUCStr    - Pointer to an array of 16-bit words containing the Unicode
//	               characters to be converted, terminated with a NULL word
//	dstStr      - Pointer to a Pascal-style string for the converted characters
//	               to be returned in
//	maxDstBytes - Maximum number of 8-bit bytes that dstStr can hold
//	               (including the preceding length byte); to handle all
//	               encodings, this must be:
//	               maxDstChars = (StringLength(srcUCStr) * 1.5) + 1
//	               (just call UnicodeToStringMaxChars)
//	pDstLen     - Returns the number of 8-bit bytes the converted characters
//	               occupy in dstStr, not including the preceding length byte
//
// Return Value:
//	Whether the conversion was successful.  Failures include not enough space
//	in the destination string; source characters that can't be converted are
//	not considered a failure [a richer return type could be considered].
//
// Created by:  Michael Hartman, December 2004
//
//*****************************************************************************

bool UnicodeToString (GSTextEncoding dstEncoding, ConstUCStrPtr srcUCStr,
                       GSStringPtr dstStr, size_t maxDstBytes, size_t* pDstLen)
{
	bool	success;
	char	dstCStr[256];
	
	/* Call the C-String Version and Copy a  */
	/*  Successful Result to a Pascal String */
	ASSERTN(kMike, (maxDstBytes <= 256));
	success = UnicodeToString(dstEncoding, srcUCStr, dstCStr, sizeof(dstCStr),
	                           pDstLen);
	if (success) {
		StringCopy(dstCStr, dstStr, maxDstBytes);
		if (strlen(dstCStr) > (maxDstBytes - 1)) success = false;
		}
	else {
		SetLength(dstStr, 0);
	}
	*pDstLen = GetLength(dstStr);
	return(success);
} // UnicodeToString


/*============================================================================*/
/****************************************/
/* Unicode String Manipulation Routines */
/****************************************/


//*****************************************************************************
//
// Function Name:  StringLength
//
// Description:
//	Determines the number of 16-bit words that contain characters in a Unicode
//	string.  For our purposes, a Unicode string is an array of UTF-16
//	characters that is terminated with a NULL word (not included in length).
//	This is thus a syntactic rather than semantic character count
//	(e.g. a decomposed character counts per code-point, not as one character,
//	and a surrogate pair counts as two words, not as one character).
//
// Parameters:
//	ucString - Pointer to a UTF-16 string (NULL-word terminated UCChar array)
//
// Return Value:
//	Whether a cluster break was located
//
// Created by:  Michael Hartman, February 2005
//
//*****************************************************************************

size_t StringLength (ConstUCStrPtr ucString)
{
	size_t	len;
	
	len = 0;
	while (ucString[len] != 0) {
		len++;
	}
	return(len);
} // StringLength


//*****************************************************************************
//
// Function Name:  StringEqual (terminated string version)
//
// Description:
//	Determines whether the two strings of UTF-16 characters are equivalent
//	according to Unicode rules (as implemented in the underlying OS).  This
//	means, for example, that precomposed and decomposed versions of a character
//	are equal.  The comparison can be specified as case-insensitive or not.
//
// Parameters:
//	str1 - Pointer to a UTF-16 string (NULL-word terminated UCChar array)
//	str2 - Pointer to a UTF-16 string (NULL-word terminated UCChar array)
//
// Return Value:
//	Whether the two strings are equivalent by Unicode rules
//
// Created by:  Michael Hartman, December 2004
//
//*****************************************************************************

bool StringEqual (ConstUCStrPtr str1, ConstUCStrPtr str2, bool ignoreCase)
{
	return(StringEqual(str1, StringLength(str1), str2, StringLength(str2),
	        ignoreCase));
} // StringEqual


//*****************************************************************************
//
// Function Name:  StringEqual (character array version)
//
// Description:
//	Determines whether the two arrays of UTF-16 characters are equivalent
//	according to Unicode rules (as implemented in the underlying OS).  This
//	means, for example, that precomposed and decomposed versions of a character
//	are equal.  The comparison can be specified as case-insensitive or not.
//
// Parameters:
//	chars1 - Pointer to an array of 16-bit words containing the UTF-16
//	          characters to be compared
//	len1   - Number of 16-bit words in 1 containing characters to be compared
//	chars2 - Pointer to an array of 16-bit words containing the UTF-16
//	          characters to be compared
//	len2   - Number of 16-bit words in 2 containing characters to be compared
//
// Return Value:
//	Whether the two arrays of characters are equivalent by Unicode rules
//
// Created by:  Michael Hartman, December 2004
//
//*****************************************************************************

bool StringEqual (ConstUCCharPtr chars1, size_t len1,
                   ConstUCCharPtr chars2, size_t len2, bool ignoreCase)
{
	bool	equalResult;
	
	if ((len1 == 0) || (len2 == 0)) return(len1 == len2);
	
#if GS_WIN
	Uint32	compareFlags;
	Sint32	orderResult;
	
	compareFlags = NORM_IGNOREWIDTH | SORT_STRINGSORT;
	if (ignoreCase) compareFlags |= NORM_IGNORECASE;
	orderResult = CompareStringW(LOCALE_USER_DEFAULT, compareFlags,
	                              (LPCWSTR) chars1, (int)len1, (LPCWSTR) chars2, (int)len2);
	equalResult = (orderResult == CSTR_EQUAL);  // If error, != more probable
	
#elif GS_LIN
	// LINUX_IMPLEMENTATION - done
	std::wstring str1( (const wchar_t*)chars1, len1 );
	std::wstring str2( (const wchar_t*)chars2, len2 );
	if ( ignoreCase )
	{
		std::transform( str1.begin(), str1.end(), str1.begin(), ::toupper );
		std::transform( str2.begin(), str2.end(), str2.begin(), ::toupper );
	}
	equalResult = (str1 == str2);
#else  /* Macintosh */
	
	CFStringRef str1 = CFStringCreateWithCharacters(NULL, chars1, len1);
	CFStringRef str2 = CFStringCreateWithCharacters(NULL, chars2, len2);
	
	int compareResult = 0;
	
	if(ignoreCase)
		compareResult = CFStringCompare(str1, str2, kCFCompareLocalized | kCFCompareCaseInsensitive);
	else
		compareResult = CFStringCompare(str1, str2, kCFCompareLocalized);
	
	CFRelease(str1);
	CFRelease(str2);
	 	
	if(compareResult == 0)
		equalResult = true;
	else
		equalResult = false;
	
#endif  // GS_WIN
	
	return(equalResult);
} // StringEqual


//*****************************************************************************
//
// Function Name:  StringCopy (terminated string version)
//
// Description:
//	Copies one string of UTF-16 characters to another string variable.  If the
//	length of the source string exceeds the specified size of the destination
//	string, the copy is truncated at a character cluster break.
//
// Parameters:
//	srcStr      - Pointer to a UTF-16 string to be copied from
//	dstStr      - Pointer to a UTF-16 string to be copied into
//	maxDstBytes - Size in bytes of the destination string parameter (in bytes
//	               rather than characters so can call sizeof(dstStr) to get;
//	               if instead have a character count (including NULL term)
//	               for an allocated buffer, multiply that by sizeof(UCChar)
//
// Return Value:
//	None
//
// Created by:  Michael Hartman, February 2005
//
//*****************************************************************************

void StringCopy (ConstUCStrPtr srcStr, UCStrPtr dstStr, size_t maxDstBytes)
{
	size_t	srcLen, maxDstChars, charsToCopy;
	bool		success;
	
	/* Determine How Many Characters from the String Will Fit, */
	/*  Making Sure to Truncate the Copy on a Cluster Boundary */
	srcLen = StringLength(srcStr);
	maxDstChars = (size_t) (maxDstBytes / sizeof(UCChar));
	if (maxDstChars > srcLen)
		charsToCopy = srcLen;
	else {
		charsToCopy = maxDstChars - 1;
		success = FindCharClusterBreak(srcStr, srcLen, charsToCopy, kFindRev,
		                                &charsToCopy);
	}
	
	/* Copy the Source Characters that Fit to the Destination String */
	if (!VERIFYPOINTER(kMike, dstStr, ((charsToCopy+1)*sizeof(UCChar))))
		dstStr[0] = NULL;
	else {
		memcpy(dstStr, srcStr, (charsToCopy*sizeof(UCChar)));
		dstStr[charsToCopy] = NULL;
	}
} // StringCopy

void StringCopy (ConstUCStrPtr srcStr, wchar_t * dstStr, size_t maxDstBytes)
{
	size_t	srcLen, maxDstChars, charsToCopy;
	bool		success;
	
	/* Determine How Many Characters from the String Will Fit, */
	/*  Making Sure to Truncate the Copy on a Cluster Boundary */
	srcLen = StringLength(srcStr);
	maxDstChars = (size_t) (maxDstBytes / sizeof(UCChar));
	if (maxDstChars > srcLen)
		charsToCopy = srcLen;
	else {
		charsToCopy = maxDstChars - 1;
		success = FindCharClusterBreak(srcStr, srcLen, charsToCopy, kFindRev,
		                                &charsToCopy);
	}
	
	/* Copy the Source Characters that Fit to the Destination String */
	if (!VERIFYPOINTER(kMike, dstStr, ((charsToCopy+1)*sizeof(UCChar))))
		dstStr[0] = NULL;
	else {
		memcpy(dstStr, srcStr, (charsToCopy*sizeof(UCChar)));
		dstStr[charsToCopy] = NULL;
	}
} // StringCopy


//*****************************************************************************
//
// Function Name:  FindCharClusterBreak
//
// Description:
//	Finds the Unicode character cluster break at or nearest the specified
//	position in the character array, looking in the direction specified.
//	Note that the starting position specified and the cluster position
//	returned of "n" ask/state that a cluster ends with the character at (n-1).
//	The caller should always pass a pointer to the beginning of the character
//	array being scanned and its full length rather than simply a pointer to
//	(or trimmed length of) the starting position, because it is assumed that
//	the character array as specified begins and ends on a cluster break.
//
// Parameters:
//	charArray - Pointer to an array of 16-bit words containing the UTF-16
//	             characters to be searched for the cluster break;
//               it is assumed that this begins and ends on a cluster break
//	length    - Number of 16-bit words in charArray that contain characters
//	             to be searched
//	startPos  - Zero-based starting position to search for a cluster break;
//	             note that the value of "length" is valid when moving backwards
//	forward   - Whether to move forward or backward from startPos if
//	             it is not at a cluster break
//	pBreakPos - Returns the nearest-found character position that is the
//	             boundary between clusters (this character starts new cluster);
//	             if an error occurs, startPos is returned as the best guess
//
// Return Value:
//	Whether a cluster break was located
//
// Created by:  Michael Hartman, December 2004
//
//*****************************************************************************

bool FindCharClusterBreak (ConstUCCharPtr charArray, size_t length,
		             size_t startPos, bool forward, size_t* pBreakPos)
{
	bool		success = false;
	
	/* Return Result Immediately for Trivial Cases */
	/*  (Assume Array Contains Complete Clusters)  */
	/* ------------------------------------------- */
	if (startPos > length) startPos = length;
	if ((startPos == 0) || (startPos == length)) {
		*pBreakPos = startPos;
		return(true);
	}
	
	/* Look for the Nearest Character Cluster Break Either */
	/*  At, Following or Preceding the Specified Position  */
	/* --------------------------------------------------- */
#if GS_WIN
	const	Uint32	kMaxCombine = 4;  // Guessed maximum of combining chars
	const	Sint32  kBadStartValue = -99;
	
	ptrdiff_t		searchPos, numCharsCheck, pos;
	SCRIPT_ITEM		scriptItems[kMaxCombine*4];
	SCRIPT_LOGATTR	scriptAttrs[kMaxCombine*4];
	Sint32				numScriptItems;
	Sint32			itemWithStart, item;
	bool			found;
	HRESULT			err;

	itemWithStart = kBadStartValue;
	
	/* Parse an Area of Twice the Expected Combining Characters around */
	/*  the Specified Start Position (for Speed and Memory Reasons)    */
	success = false;
	*pBreakPos = startPos;
	searchPos = std::max((startPos-(kMaxCombine*2)), (size_t)0);
	numCharsCheck  = std::min((startPos+(kMaxCombine*2)), length) - searchPos + 1;
	
	/* Determine the Individually Shapeable Runs (by Text Direction or  */
	/*  Glyph Shaping Engine), and Find the One with the Start Position */
	err = ScriptItemize((const WCHAR *) &charArray[searchPos], (int)numCharsCheck,
	             (sizeof(scriptItems)/sizeof(SCRIPT_ITEM)), NULL, NULL,
	             scriptItems, &numScriptItems);
	if (err == S_OK) {
		for (item = 0; item < (numScriptItems-1); item++) {
			if ((scriptItems[item].iCharPos <= (Sint32)startPos) &&
			 ((Sint32)startPos <= scriptItems[item+1].iCharPos)) {
			 	itemWithStart = item;
				break;
			}
		}
	}
	
	/* Get the Attributes for the Characters in that Run, then */
	/*  Search for a Cluster Break in the Specified Direction; */
	/*  We Can Limit Our Search to the One Run Because a Run   */
	/*  Must Begin With and Be Followed By a Cluster Break     */
	if (err == S_OK && itemWithStart != kBadStartValue) {
		searchPos = scriptItems[itemWithStart].iCharPos;
		numCharsCheck = scriptItems[itemWithStart+1].iCharPos - searchPos;
		err = ScriptBreak((const WCHAR *) &charArray[searchPos],(int) numCharsCheck,
		                   &scriptItems[itemWithStart].a, scriptAttrs);
		if (err == S_OK) {
			found = false;
			if (forward) {
				for (pos = (startPos-searchPos); pos < numCharsCheck; pos++) {
					if (scriptAttrs[pos].fCharStop == 1) {
						*pBreakPos = pos + searchPos;
						break;
					}
				}
				if (!found) *pBreakPos = numCharsCheck + searchPos;  // Okay
			}
			else {
				for (pos = (startPos-searchPos); pos >= 0; pos--) {
					if (scriptAttrs[pos].fCharStop == 1) {
						*pBreakPos = pos + searchPos;
						break;
					}
				}
				if (!found) *pBreakPos = searchPos;  // Should never happen
			}
			success = true;
		}
	}
	
#elif GS_LIN
	// LINUX_IMPLEMENTATION
#else  /* Macintosh */
    CFStringRef cfs = CFStringCreateWithCharacters(NULL, charArray, length);
    if (cfs && startPos < length)
    {
        CFRange r = CFStringGetRangeOfComposedCharactersAtIndex(cfs, startPos);
		
        if (forward)
        {
            if (startPos == r.location)
                *pBreakPos = r.location;
            else
                *pBreakPos = r.location + r.length;
        }
        else
            *pBreakPos = r.location;
    }
    else
    {
        *pBreakPos = startPos;
        success = false;
    }
    
    if(cfs)
        CFRelease(cfs);
	
#endif  // GS_WIN
	
	return(success);
} // FindCharClusterBreak


/*============================================================================*/
/*============================================================================*/
/***********************************************************************/
/* Non-Unicode Pascal and C String Manuipulation Routines and Classes */
/***********************************************************************/


/*============================================================================*/
// System and Application Encoding Retrieval Routines


//*****************************************************************************
//
// Function Name:  GetSystemEncoding
//
// Description:
//	Returns the encoding to use in Unicode conversion functions for text
//	that is in the current "system" encoding.  This actually reflects the
//	choice of the user in the "International" system configuration preferences.
//	Note that the meaning of the encoding value returned is defined by the
//	Macintosh and Windows platforms independently (platform constants).
//
// Parameters:
//	None
//
// Return Value:
//	Platform-defined value specifying the current default "system" (user-set)
//	character encoding
//
// Created by:  Robert McBride, ????
//
//*****************************************************************************

GSTextEncoding GetSystemEncoding ()
{
	static bool isFirstExec = true;
	static GSTextEncoding encoding;
	
	if(isFirstExec)
	{
	
#if GS_WIN
		encoding = GetACP();
#elif GS_LIN
		// LINUX_IMPLEMENTATION
#else
		// note that CFStringGetSystemEncoding does not return Icelandic in MacOS 10.10 and later
		// -- this is a workaround replacement
		bool isIcelandic = [[[NSLocale preferredLanguages] objectAtIndex:0] hasPrefix:@"is"];

		encoding = isIcelandic ? kCFStringEncodingMacIcelandic : CFStringGetSystemEncoding();
		
#endif
		
		isFirstExec = false;
	}
	
	return encoding ;
}


// ===========================================================================
// == Strings
// ==

// ---------------------------------------------------------------------------
// -- StringCopy

void StringCopy(ConstGSStr255Param src, GSStringPtr dst, size_t n)
// Pascal- to Pascal-style string copy. Includes length byte so
// to copy m characters n should be m + 1. Example: to copy to
// Str255, n = 256 or sizeof(Str255).
{
	if (n == 0 || !dst) 
		return /*dst*/;
	if (!src || src[0] == 0) { 
		*dst = 0;
		return /*dst*/;
	}
	
	ASSERTN(kChao, n <= 256);
		
	size_t		i = (((size_t)(*src + 1) < n) ? *src : n - 1);
	
	//IFPRINT(*src > n - 1, "### StringCopy - source too Sint32; truncating to fit.");

	*dst = (unsigned char) i;
	dst++, src++;
	for (; i > 0; i--) 
		*dst++ = *src++;
	
	return /*d*/;
}

void StringCopy(const char *src, GSStringPtr dst, size_t n)
// C- to Pascal-style string copy. Includes length byte so
// to copy m characters n should be m + 1. Example: to copy to
// Str255, n = 256 or sizeof(Str255).
{
	size_t				l = 0;				// Length counter.
	const GSStringPtr	d = dst;			// Save original dst pointer.
	
	if (n <= 0 || !dst)
		return /*dst*/;
		
	ASSERTN(kChao, n <= 256);
	if (n > 256) n = 256;
				
	if (src) {
		dst++;								// Skip over length byte.
		while (l < n - 1 && (*dst++ = *src++) != 0) // Copy characters, keeping track of how many.
			l++;
	}
	*d = (unsigned char) l;					// Set length byte.
	return /*d*/;
}

void StringCopy(const void *src, size_t len, GSStringPtr dst, size_t n)
// Raw storage to Pascal-style string copy. Includes length byte so
// to copy m characters n should be m + 1. Example: to copy to
// Str255, n = 256 or sizeof(Str255) and len is up to 255 (bigger len
// is ok but will be truncated).
{
	if (!dst || n == 0) 
		return /*dst*/;
	
	if (src) {
		const char *		src_p = (const char *) src;
	
		ASSERTN(kChao, n <= 256);
		
		n = Min(n-1, len);
		*dst++ = (unsigned char) n;
		for (; n > 0; n--) 
			*dst++ = *src_p++;
		return;
	}
	else {
		*dst = 0;
		return;
	}
}

void StringCopy(ConstGSStr255Param src, char *dst, size_t n)
// Pascal- to C-style string copy. Includes length byte/null terminator so
// to copy m characters n should be m + 1. Example: to copy from
// Str255 to a char[256], n = 256.
{
	if (n <= 0 || !dst) return /*dst*/;
	
	if (src) {
		ASSERTN(kChao, n <= 256);
		
		size_t sl = Min((size_t) src[0], n-1);
		dst[sl] = '\0';	// Terminate destination, since strncpy won't do it.
		if (sl)
			/*return*/ strncpy(dst, (const char *) &src[1], sl);
		return;
	}
	else {
		*dst = '\0';
		return /*dst*/;
	}
}

void StringCopy(const char *src, char *dst, size_t n)
// C- to C-style string copy. Includes null terminator so
// to copy m characters n should be m + 1.
{
	// NOTE: This function is NOT the same as strncpy, because strncpy
	// won't necessarily null-terminate the destination, and doesn't
	// handle null string pointers!
	
	if (n <= 0 || !dst) 
		return /*dst*/;
	
	if (src) {
		size_t sl = Min(strlen(src), n-1);
		dst[sl] = '\0';
		if (sl)
			/*return*/ strncpy(dst, src, sl);
		return;
	}
	else {
		*dst = '\0';
		return /*dst*/;
	}
}

void StringCopy(const void *src, size_t len, char *dst, size_t n)
// Raw storage to C-style string copy. Includes null terminator so
// to copy m characters n should be m + 1. 
{
	if (!dst || n <= 0) 
		return /*dst*/;

	if (src) {
		//char * const		d = dst;
		const char *		src_p = (const char *) src;

		n = Min(n-1, len);
		for (; n > 0; n--) 
			*dst++ = *src_p++;
		*dst = '\0';
		return /*d*/;
	}
	else {
		*dst = '\0';
		return /*dst*/;
	}
}

// ---------------------------------------------------------------------------
// -- StringCat

GSStringPtr StringCat(GSStringPtr dst, ConstGSStr255Param src, size_t n)
	// ## Catenate Pascal- to Pascal-style string.
{
	if (n <= (size_t) (GetLength(dst) + 1) || !dst || !src) return dst;
	
	const GSStringPtr	d = dst;
	size_t				copylen = ((size_t)(*dst + *src + 1) <= n) ? *src : n - *dst - 1;
	
	#if 0
	IFPRINT(copylen != *src, "### StringCat - result would be too Sint32; truncating to fit.");
	#endif
	
	dst += *dst + 1;	// Step to end of destination string.
	src++;				// Skip past length byte of source.
	*d += (Uchar) copylen;		// Increment length of destination.
	for (; copylen > 0; copylen--) *dst++ = *src++;	// Do the copy.
	
	return d;
}

GSStringPtr StringCat(GSStringPtr dst, const char *src, size_t n)
	// ## Catenate C- to Pascal-style string.
{
	if (n <= (size_t) GetLength(dst) + 1 || !dst || !src) return dst;
	
	const GSStringPtr	d = dst;
	size_t				copylen = n - GetLength(dst) - 1;
	
	for (dst += *dst + 1; copylen > 0 && *src; copylen--)
		(*d)++, *dst++ = *src++;
	
	return d;
}

GSStringPtr StringCat(GSStringPtr dst, const void *src, size_t len, size_t n)
	// ## Catenate raw storage to Pascal-style string.
{
	if (n <= (size_t) GetLength(dst) + 1 || !dst || !src) return dst;
	
	const GSStringPtr	d = dst;
	const char		   *src_p = (const char *) src;
	size_t				copylen = Min(n - GetLength(dst) - 1, len);
	
	for (dst += *dst + 1; copylen > 0; copylen--)
		(*d)++, *dst++ = *src_p++;
	
	return d;
}

char * StringCat(char *dst, ConstGSStr255Param src, size_t n)
	// ## Catenate Pascal- to C-style string.
{
	if (n > 0 && src && dst) {
		size_t dl = strlen(dst);
		char *dst2 = dst+dl;
		StringCopy(src, dst2, n > dl ? n-dl : 0);
		return dst2;
	}
	return dst;
}

char * StringCat(char *dst, const char *src, size_t n)
	// ## Catenate C- to C-style string.
{
	if (n > 0 && src && dst) {
		size_t dl = strlen(dst);
		StringCopy(src, dst+dl, n > dl ? n-dl : 0);
	}
	return dst;
}

char * StringCat(char *dst, const void *src, size_t len, size_t n)
	// ## Catenate raw storage to Pascal-style string.
{
	if (n > 0 && src && dst) {
		size_t dl = strlen(dst);
		StringCopy((const char *) src, len, dst+dl, n > dl ? n-dl : 0);
	}
	return dst;
}

// ---------------------------------------------------------------------------
// -- StringEqual

Bool8 StringEqual(const TXString& a, const TXString& b)
{
	return (a.Equal(b));
}

// ---------------------------------------------------------------------------
// -- StringEqualIgnoringCase
Bool8 StringEqualIgnoringCase(const TXString& a, const TXString& b)
{
	return (a.EqualNoCase(b));
}


// ---------------------------------------------------------------------------
// -- StringCompare
short StringCompare(const TXString& str1, const TXString& str2)
{
	return str1.Compare(str2);
}


// ---------------------------------------------------------------------------
// -- StringCompareIgnoringCase

short StringCompareIgnoringCase(const TXString& a, const TXString& b)
{
	return a.CompareNoCase(b);
}


// ---------------------------------------------------------------------------
// -- StringInsert

void StringInsert(ConstGSStr255Param src, GSStringPtr dst, Uint8 index)
{
	/* NOTE: In the event that the full result is bigger than 255
		characters, StringInsert will preserve all of dst in preference
		to inserting all of src.  E.g., if you ask to insert a string
		of 255 x's in the middle of "foobar", you'll get "foo<249 x's>bar",
		not "foo<252 x's>".
	*/
	
	if (!src || !dst) return;
	if (!inrange(index, 1, 255)) return;
	
	ptrdiff_t	copylen = (*src + *dst > 255) ? 255 - *dst : *src;
	ptrdiff_t	x = (ptrdiff_t)index + copylen;
	
	memmove(&dst[x], &dst[index], 255 - x);
	memmove(&dst[index], &src[1], copylen);
	
	dst[0] += (unsigned char) copylen;
}

// ---------------------------------------------------------------------------
// -- StringDelete

void StringDelete(GSStringPtr s, Uint8 start, Uint8 count)
{
	if (!s) return;
	if (start > *s) return;
	
	if (start + count - 1 > *s) count = *s - start;
	
	GSStringPtr	src = s + start + count, dst = s + start;
	short		copylen = *s - start - count + 1;

	*s -= count;
	for (; copylen > 0; copylen--) *dst++ = *src++;
}	

void StringDelete(char *s, size_t start, size_t count)
{
	if (!s) return;
	
	size_t		len = strlen(s);
	
	if (start > len) return;
	if (start + count > len) count = len - start;
	if (count < 1) return;
	
	memmove(s + start, s + start + count, len - start - count + 1);
}


#ifdef _MINICAD_

// ---------------------------------------------------------------------------
// -- StringPos

short StringPos (ConstGSStr255Param findStr, ConstGSStr255Param str)
/* Searches for the first occurrence of findStr within str, and returns */
/*  its starting position.  If findStr is not found, 0 is returned.     */
/*  The comparison is case and diacritical sensitive, and may not yield */
/*  the proper result with 2-byte script systems.                       */
{
	size_t foundPos = 0;
	size_t findLen = GetLength(findStr);
	size_t strLen  = GetLength(str);
	void *buf = (void *) (&str[1]);
	void *pat = (void *) (&findStr[1]);
	if ((findLen > 0) && (strLen > 0) && (findLen <= strLen)) {
		void *loc = VWMM::Partition::MemMem(buf, strLen, pat, findLen);
		if (loc != NULL)
		{
			foundPos = (((size_t) loc) - ((size_t) buf));
			++foundPos;	// zero-based to one-based.
		}
	}

	return((short)foundPos);
}

#endif // _MINICAD_

//=======================================================================================
// Use OS to compare strings.
short OSStringCompare(const TXString& string1, const TXString& string2, bool convertWinDash)
{
	
#if _WINDOWS
	
	short compareValue = 0;

	if(string1.IsEmpty() && string2.IsEmpty())
	{
		compareValue = 0; // Equal.
	}
	else if (string1.IsEmpty())
	{
		compareValue = 1; // Greater than.
	}
	else if (string2.IsEmpty())
	{
		compareValue = -1; // Less than.
	}
	else
	{
		// StrCmpLogicalW ignores dash characters, which causes a problem
		// when this is used to sort classes. So for the sorting, convert
		// all dashes to exclamation points.
		// It also seems to ignore control characters, which also causes
		// a problem when used to sort classes, so convert any of these
		// characters to exclamation points also.
		if (convertWinDash)
		{
			TXString str1 = string1;
			TXString str2 = string2;
			size_t len1 = str1.GetLength();
			size_t len2 = str2.GetLength();
			
			for (int i = 0; i < len1; i++)
			{
				if (str1[i] == '-' || str1[i] < 0x20)
					str1[i] = '!';
			}
			
			for (int j = 0; j < len2; j++)
			{
				if (str2[j] == '-' || str2[j] < 0x20)
					str2[j] = '!';
			}

			compareValue = StrCmpLogicalW(str1.GetData(), str2.GetData());
		}
		else
		{
			compareValue = StrCmpLogicalW(string1.GetData(), string2.GetData());
		}
	}
	
	return compareValue;
	
#elif GS_LIN
	// LINUX_IMPLEMENTATION

#else	// Mac

	CFComparisonResult compareValue = kCFCompareEqualTo;
	
	if (string1.IsEmpty() && string2.IsEmpty())
	{
		compareValue = kCFCompareEqualTo;
	}
	else if (string1.IsEmpty() && !string2.IsEmpty())
	{
		compareValue = kCFCompareGreaterThan;
	}
	else if (!string1.IsEmpty() && string2.IsEmpty())
	{
		compareValue = kCFCompareLessThan;
	}
	else
	{
		CFStringRef cfStr1 = string1.GetCFStringRef();
		CFStringRef cfStr2 = string2.GetCFStringRef();
		
		if (!cfStr1)
		{
			compareValue = kCFCompareGreaterThan;
		}
		else if (!cfStr2)
		{
			compareValue = kCFCompareLessThan;
		}
		else
		{
			compareValue = CFStringCompare(cfStr1,
										   cfStr2,
										   kCFCompareCaseInsensitive | kCFCompareDiacriticInsensitive | kCFCompareNumerically );
		}
		
		if (compareValue == kCFCompareEqualTo)
		{
			compareValue = CFStringCompare(cfStr1,
										   cfStr2,
										   kCFCompareCaseInsensitive | kCFCompareNumerically );
		}
		
		if (compareValue == kCFCompareEqualTo)
		{
			compareValue = CFStringCompare(cfStr1,
										   cfStr2,
										   kCFCompareCaseInsensitive );
		}
		
		if(cfStr1)
		{
			CFRelease( cfStr1 );
		}
		
		if (cfStr2)
		{
			CFRelease( cfStr2 );
		}
	}
	
	return (short)compareValue;
	
#endif
	
}

// ---------------------------------------------------------------------------
// -- Other functions

#if !_WINDOWS

Sint32 stricmp(const char *a, const char *b)
{
	char ua, ub;
	for (; *a && *b; ++a, ++b) {
		ua = toupper(*a);
		ub = toupper(*b);
		if (ua != ub)
			return (ua < ub ? -1 : 1);
	}
	// At this point at least one of *a or *b is equal to 0.
	return (*a == *b) ? 0 : (*a ? 1 : -1);
}

Sint32 strnicmp(const char *a, const char *b, size_t max)
{
	char ua, ub;
	size_t n;
	for (n=0; *a && *b && n<max; ++a, ++b, ++n) {
		ua = toupper(*a);
		ub = toupper(*b);
		if (ua != ub)
			return (ua < ub ? -1 : 1);
	}
	// At this point, either we have reached 'max' or at least one of *a or *b is equal to 0.
	return (*a == *b || n >= max) ? 0 : (*a ? 1 : -1);
}


#endif // !_WINDOWS

#endif // !_WINDOWS || _MINICAD_ || _GSESDK_

/*============================================================================*/

//=======================================================================================
Boolean IsMultiByteLanguage( )
{
	static bool isFirstTimeExecution = true;
	static bool isMultibyteLanguage = false;
	
	// The following block is only executed once.
	if(isFirstTimeExecution)
	{
#if GS_WIN
		if(GetACP() == 932 || GetACP() == 936)	// Japanese and simplified Chinese
		{
			isMultibyteLanguage = true;
		}
#elif GS_LIN
	// LINUX_IMPLEMENTATION
#else
		CFStringEncoding cfStringEncoding = CFStringGetSystemEncoding();
		
		if (cfStringEncoding == kCFStringEncodingMacJapanese		// Japanese
			|| cfStringEncoding == kCFStringEncodingMacChineseSimp)	// Simplified Chinese
		{
			isMultibyteLanguage = true;
		}
#endif
		
		isFirstTimeExecution = false;
	}

	return isMultibyteLanguage;
}


//=======================================================================================
// Required for translation of strings
//
// Used for a few other special cases also.  Do not use this without talking to Payne or Ian first.
//
void GetFarEastCharacterTypeArray(const char *pStr, ECharacterType *pCharByteType, size_t strLength)
    //
    // Description:
    // Populate char byte type array based on the source.
    //
{
	if (pStr && pCharByteType)
	{
		if(!IsMultiByteLanguage())
		{	// This is not multi-byte string.
			for (size_t i = 0; i < strLength; i++)
			{
				pCharByteType[i] = eSingle;
			}
		}
		else
		{	// This is multi-byte string.
		 
#if GS_WIN	// Windows
			Sint32 lastType = _MBC_SINGLE;
			Sint32 thisType;
			
			for (size_t i = 0; i < strLength; i++)
			{
				thisType = _mbbtype(pStr[i], lastType );
				lastType = thisType;
				
				if(thisType == _MBC_SINGLE)
				{
					pCharByteType[i] = eSingle;
				}
				else if(thisType == _MBC_LEAD)
				{
					pCharByteType[i] = eLead;
				}
				else if(thisType == _MBC_TRAIL)
				{
					pCharByteType[i] = eTrail;
				}
				else
				{
					pCharByteType[i] = eSingle;
				}
			}
#elif GS_LIN
	// LINUX_IMPLEMENTATION
			
#else		// Mac
			{
				int strLen = 0;	// NSString length
				
				for(int i = 0; i < strLength; ++i)
				{
					// Create a two-byte string.
                    NSString *nsStr = [[NSString alloc] initWithBytes:(void*)(pStr + i)
                                                               length:2
                                                             encoding:[NSString defaultCStringEncoding]];
                    
                    if (i == (strLength - 1) && nsStr == nil)
                    {
                        // The last byte is part of a multi byte character but the NSString can't be constructed from
                        // an invalid string so it's nil.  A nil string will return a length of 0, so we need to handle
                        // this as a special case here instead of handling it lower.
                        pCharByteType[i] = eLead;
                    }
                    else
                    {
                        // Get the length of the string.
                        strLen = [nsStr length];
                        
                        if(strLen == 0)	// The first byte is a one-byte character. The second byte is a leading byte.
                        {
                            pCharByteType[i] = eSingle;
                        }
                        else if(strLen == 1)	// charLen == 1: one two-byte character
                        {
                            pCharByteType[i] = eLead;
                            ++i;
                            
                            if(i < strLength)
                            {
                                pCharByteType[i] = eTrail;
                            }
                        }
                        else	// charLen == 2: two single byte characters.
                        {
                            pCharByteType[i] = eSingle;
                            ++i;
                            
                            if(i < strLength)
                            {
                                pCharByteType[i] = eSingle;
                            }
                        }
                    }
				}
			}
#endif
		}
	}
}

// This function will check if the last byte of a multi-byte encoded string is the start of a new multi byte character.
// If it is, we want to remove that byte because it isn't valid.  Leaving this byte can corrupt the string.
// This is currently only used during reverse translation.

// For C string
void TrimInvalidCharsFromMultiByteEncodedCString(char* buffer, size_t bufferSize)
{
	// Process it only if in multi-byte language and the buffer is not empty.
	if (IsMultiByteLanguage() && bufferSize > 0)
	{
		ECharacterType *charTypeArr = new ECharacterType[bufferSize];
		GetFarEastCharacterTypeArray(buffer, charTypeArr, bufferSize);

		// Make sure the C string is null terminated.
		buffer[bufferSize - 1] = '\0';
		
		// If the byte before the terminal byte is a lead, remove it.
		if (bufferSize > 1 && charTypeArr[bufferSize - 2] == eLead) {
				buffer[bufferSize - 2] = '\0';
		}

		delete[] charTypeArr;
	}
}

// For Pascal string
void TrimInvalidCharsFromMultiByteEncodedPString(unsigned char* buffer, size_t bufferSize)
{
	// Process it only if in multi-byte language and the buffer is not empty.
	if (IsMultiByteLanguage() && bufferSize >= 2)
	{
		ECharacterType *charTypeArr = new ECharacterType[bufferSize - 1];
		
		// The first byte is the lenght. Skip it.
		GetFarEastCharacterTypeArray((const char*)(buffer + 1), charTypeArr, bufferSize - 1);
		
		// If the last byte is a lead, remove it.
		if (charTypeArr[bufferSize - 2] == eLead) {
			buffer[bufferSize - 1] = '\0';
		}
		
		delete[] charTypeArr;
	}
}



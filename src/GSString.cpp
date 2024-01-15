//
//	Copyright (c) Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
// TXString class implementation.
//


/* Includes */
/* -------- */
#include "Prefix/StdAfx.h"
#include "GSIntTypes.h"

#define _GSString_X_

#include <iostream>
#include <codecvt>
#include <iomanip>

#if GS_WIN
// For Unicode normalization form (precomposed v.s. decomposed)
//	#include <WinNls.h> 
#include <cstring>
#include <cctype>
#elif GS_LIN
#include <cstring>
#include <string>
#include <algorithm>
#else
//#include <AppKit/AppKit.h>
#endif

#include "GSString.h"
namespace VectorworksMVR
{


inline void utf32ToTXCharBuffer(char32_t input, TXChar* output);
inline void utf32BufferToTXCharBuffer(const char32_t* input, TXChar* output, size_t numInputChars = -1);
inline void txCharBufferToUtf32Buffer(const TXChar* input, char32_t* output, size_t bufElemNum = -1);
inline void utf8BufferToTXCharBuffer(const char* const input, TXChar* output, size_t inputLen);

//#######################################################################################
// TXString class
//#######################################################################################

//***********************************************************************************
// Constructors and destructor
//***********************************************************************************

//=======================================================================================
// Default constructor
TXString::TXString()
	: charPtr(nullptr)
	, charBufSize(0)
{
}

//=======================================================================================
// Copy constructor
TXString::TXString(const TXString& src)
	: stdUStr(src.stdUStr)
	, charPtr(nullptr)
	, charBufSize(0)
{
}

//=======================================================================================
// Move constructor
TXString::TXString(TXString&& src)
	: stdUStr(std::move(src.stdUStr))
	, charPtr(nullptr)
	, charBufSize(0)
{
}

//=======================================================================================
// Copy constructor from StdUstr
TXString::TXString(const StdUStr& src)
	: stdUStr(src)
	, charPtr(nullptr)
	, charBufSize(0)
{
}

//=======================================================================================
// Move constructor from StdUStr
TXString::TXString(StdUStr&& src)
	: stdUStr(std::move(src))
	, charPtr(nullptr)
	, charBufSize(0)
{
}

//=======================================================================================
// Construct from a std string. On Windows, invalid chars are replaced with replacement
// characters. On Mac, the string is empty if there is any invalid chars.
TXString::TXString(const std::string& src,
	ETXEncoding e)		// ETXEncoding::eUTF8
	: charPtr(nullptr)
	, charBufSize(0)
{
	SetStdUStrFromCharBuffer(src.data(), -1, e);
}

//=======================================================================================
// Construct from a std wstring.
#if GS_WIN
TXString::TXString(const std::wstring& src)
	: charPtr(nullptr)
	, charBufSize(0)
{
	stdUStr = src.data();
}
#elif GS_LIN
	// not defined
#elif GS_MAC
TXString::TXString(const std::wstring& src)
	: charPtr(nullptr)
	, charBufSize(0)
{
	std::unique_ptr<TXChar[]> ucchars(new TXChar[src.length() * 2 + 1]);
	utf32BufferToTXCharBuffer((const char32_t*)src.data(), ucchars.get());
	stdUStr = ucchars.get();
}
#endif

//=======================================================================================
// Construct with initial size. size_t version.
TXString::TXString(size_t nInitialSize)
	: stdUStr(nInitialSize, 0)
	, charPtr(nullptr)
	, charBufSize(0)
{
}

//=======================================================================================
// Construct with initial capacity. int version.
TXString::TXString(int nInitialSize)
	: stdUStr(nInitialSize, 0)
	, charPtr(nullptr)
	, charBufSize(0)
{
}

//=======================================================================================
// Construct from a char buffer. On Windows, invalid chars are replaced with replacement
// characters. On Mac, the string is empty if there is any invalid chars.
TXString::TXString(const char* src,
	ETXEncoding e)		// ETXEncoding::eUTF8
	: charPtr(nullptr)
	, charBufSize(0)
{
	SetStdUStrFromCharBuffer(src, -1, e);
}

//=======================================================================================
// Construct from a char buffer. On Windows, invalid chars are replaced with replacement
// characters. On Mac, the string is empty if there is any invalid chars.
TXString::TXString(const char* src,
	size_t lenInBytes,
	ETXEncoding e)		// ETXEncoding::eUTF8
	: charPtr(nullptr)
	, charBufSize(0)
{
	SetStdUStrFromCharBuffer(src, lenInBytes, e);
}

//=======================================================================================
// Construct from unsigned char buffer. UTF-8 is the default encoding.
TXString::TXString(const unsigned char* src,
	ETXEncoding e)		// ETXEncoding::eUTF8
	: charPtr(nullptr)
	, charBufSize(0)
{
	if (src && *src != 0)
	{
		char charBuf[256];

		// Copy bytes to the buffer.
		strncpy(charBuf, (const char *)src + 1, src[0]);

		// Add terminating character to the end of the buffer.
		charBuf[src[0]] = 0;

		// Set Unicode string.
		SetStdUStrFromCharBuffer(charBuf, -1, e);
	}
}

//=======================================================================================
// Construct from an unsiged short buffer.
TXString::TXString(const UCChar* src)
	: charPtr(nullptr)
	, charBufSize(0)
{
	if (src)
	{
		stdUStr.assign((const TXChar*)src);
	}
}

//=======================================================================================
// Construct from an unsiged short buffer. The first 'numUCChars' characters are used. The
// terminating character is NOT counted in numUCChars.
TXString::TXString(const UCChar* src, size_t numUCChars)
	: charPtr(nullptr)
	, charBufSize(0)
{
	if (src)
	{
		// Determine the length of characters to use.
		size_t length = 0;
		while (length < numUCChars && src[length] != 0) ++length;

		stdUStr.assign((const TXChar*)src, length);
	}
}

//=======================================================================================
// Construct from a wchar_t buffer.
TXString::TXString(const wchar_t* src)
	: charPtr(nullptr)
	, charBufSize(0)
{
	if (src)
	{
#if GS_WIN
		stdUStr = src;
#elif GS_LIN
		std::u32string wStr((const char32_t*)src);
		std::wstring_convert<std::codecvt_utf16<char32_t>, char32_t> convert;
		std::string bytes = convert.to_bytes(wStr);

		std::u16string result;
		result.reserve(bytes.size() / 2);

		for (size_t i = 0; i < bytes.size(); i += 2) {
			result.push_back(static_cast<char16_t>(static_cast<unsigned char>(bytes[i]) * 256 + static_cast<unsigned char>(bytes[i + 1])));
		}

		stdUStr = result;
#else
		std::unique_ptr<TXChar[]> ucchars(new TXChar[wcslen(src) * 2 + 1]);
		utf32BufferToTXCharBuffer((const char32_t*)src, ucchars.get());
		stdUStr = ucchars.get();
#endif
	}
}

//=======================================================================================
// Construct from a wchar_t buffer. numWChars is the number of characters. Terminating
// character is NOT counted in numWChars.
TXString::TXString(const wchar_t* src, size_t numWChars)
	: charPtr(nullptr)
	, charBufSize(0)
{
	if (src)
	{
		// Determine the length of characters to use.
		size_t length = 0;
		while (length < numWChars && src[length] != 0) ++length;

#if GS_WIN
		stdUStr.assign(src, length);
#elif GS_LIN
		std::u32string wSrc((const char32_t*)src, numWChars);
		std::wstring_convert<std::codecvt_utf16<char32_t>, char32_t> convert;
		std::string bytes = convert.to_bytes(wSrc);

		std::u16string result;
		result.reserve(bytes.size() / 2);

		for (size_t i = 0; i < bytes.size(); i += 2) {
			result.push_back(static_cast<char16_t>(static_cast<unsigned char>(bytes[i]) * 256 + static_cast<unsigned char>(bytes[i + 1])));
		}

		stdUStr = result;
#else
		std::unique_ptr<TXChar[]> txChars(new TXChar[ length * 2 + 1]);
		utf32BufferToTXCharBuffer((const char32_t*)src, txChars.get(), length);
		stdUStr = txChars.get();
#endif
	}
}

//=======================================================================================
// Fill the string with "count" number of "ch"
TXString::TXString(char ch, size_t count /* 1 */)
	: stdUStr(count, (unsigned char)ch)
	, charPtr(nullptr)
	, charBufSize(0)
{
}

//=======================================================================================
// Fill the string with "count" number of "ch"
TXString::TXString(unsigned char ch, size_t count /* 1 */)
	: stdUStr(count, ch)
	, charPtr(nullptr)
	, charBufSize(0)
{
}

//=======================================================================================
// Fill the string with "count" number of "ch"
TXString::TXString(UCChar ch, size_t count /* 1 */)
	: stdUStr(count, ch)
	, charPtr(nullptr)
	, charBufSize(0)
{
}

//=======================================================================================
// Fill the string with "count" number of "ch"
#if GS_WIN
TXString::TXString(wchar_t ch, size_t count /* 1 */)
	: stdUStr(count, ch)
	, charPtr(nullptr)
	, charBufSize(0)
{
}
#elif GS_LIN
TXString::TXString(wchar_t ch, size_t count /* 1 */)
	: stdUStr(count, ch)
	, charPtr(nullptr)
	, charBufSize(0)
{
}
#else
TXString::TXString(wchar_t w, size_t count /* 1 */)
	: charPtr(nullptr)
	, charBufSize(0)
{
	if((int)w <= 0xffff)
	{
		stdUStr.assign(count, (TXChar) w);
	}
	else
	{
		UCChar u[3];
		utf32ToTXCharBuffer((char32_t)w, u);

		for(int i = 0; i < count; ++i)
		{
			stdUStr.append(u);
		}
	}
}
#endif

//=======================================================================================
// Destructor
TXString::~TXString()
{
	if (charPtr) delete charPtr;
}


//***********************************************************************************
// Assignments
//***********************************************************************************

//=======================================================================================
// Copy assignment operator
TXString& TXString::operator=(const TXString& src)
{
	stdUStr = src.stdUStr;
	return *this;
}

//=======================================================================================
// Move assignment operator
TXString& TXString::operator=(TXString&& src)
{
	stdUStr = std::move(src.stdUStr);
	return *this;
}

//=======================================================================================
// Assignment operator from std::string
TXString& TXString::operator=(const std::string& src)
{
	SetStdUStrFromCharBuffer(src.data());
	return *this;
}

//=======================================================================================
// Assignment operator from std::wstring
TXString& TXString::operator=(const std::wstring& src)
{
#if GS_WIN
	stdUStr = src.data();
#elif GS_LIN
	std::u32string wSrc((const char32_t*)src.data());
	std::wstring_convert<std::codecvt_utf16<char32_t>, char32_t> convert;
	std::string bytes = convert.to_bytes(wSrc);

	std::u16string result;
	result.reserve(bytes.size() / 2);

	for (size_t i = 0; i < bytes.size(); i += 2) {
		result.push_back(static_cast<char16_t>(static_cast<unsigned char>(bytes[i]) * 256 + static_cast<unsigned char>(bytes[i + 1])));
	}

	stdUStr = result;
#else
	std::unique_ptr<TXChar[]> ucChars(new TXChar[src.length() * 2 + 1]);
	utf32BufferToTXCharBuffer((const char32_t*)src.data(), ucChars.get());
	stdUStr = ucChars.get();
#endif
	return *this;
}

//=======================================================================================
// Assignment from a const char buffer. UTF-8 is the encoding. If 'src' is 
// nullptr, the string is cleared.
TXString& TXString::operator=(const char* src)
{
	if (src)
	{
		SetStdUStrFromCharBuffer(src);
	}
	else
	{
		stdUStr.clear();
	}

	return *this;
}

//=======================================================================================
// Assignment from a const unsigned char buffer. UTF-8 encoding is assumed. If 'src' is
// nullptr, the string is cleared.
TXString& TXString::operator=(const unsigned char* src)
{
	if (src && *src != 0)
	{
		char charBuf[256];
		std::strncpy(charBuf, (const char *)src + 1, src[0]);
		charBuf[src[0]] = 0;
		SetStdUStrFromCharBuffer(charBuf);
	}
	else
	{
		stdUStr.clear();
	}

	return *this;
}

//=======================================================================================
// Assignment from a const UCChar buffer. If 'src' is nullptr, the string is cleared.
TXString& TXString::operator=(const UCChar* src)
{
	if (src)
	{
		stdUStr = (const TXChar*)src;
	}
	else
	{
		stdUStr.clear();
	}

	return *this;
}

//=======================================================================================
// Assignment from a const wchar_t buffer. If 'src' is nullptr, the string is cleared.
TXString& TXString::operator=(const wchar_t* src)
{
	if (src)
	{
#if GS_WIN
		stdUStr = src;
#elif GS_LIN
		TXString tx (src);
		stdUStr = std::move(tx.stdUStr);
#else
		TXString tx (src);
		stdUStr = std::move(tx.stdUStr);
#endif
	}
	else
	{
		stdUStr.clear();
	}

	return *this;
}

//=======================================================================================
// Assignment from a char
TXString& TXString::operator=(char ch)
{
	// On Windows, char to wchar_t conversion is not what is expected. Thus, char is
	// converted to unsigned char.
	stdUStr = (unsigned char)ch;
	return *this;
}

//=======================================================================================
// Assignment from an unsigned char
TXString& TXString::operator=(unsigned char ch)
{
	stdUStr = ch;
	return *this;
}

//=======================================================================================
// Assignment from an UCChar
TXString& TXString::operator=(UCChar ch)
{
	stdUStr = (TXChar)ch;
	return *this;
}

//=======================================================================================
// Assignment from an wchar_t
TXString& TXString::operator=(wchar_t w)
{
#if GS_WIN
	stdUStr = w;
#elif GS_LIN
	// TODO
	stdUStr = w;
#else
		if((int) w <= 0xffff)
	{
		stdUStr = (TXChar) w;
	}
	else
	{
		UCChar u[3];
		utf32ToTXCharBuffer((char32_t)w, u);
		stdUStr = u;
	}
#endif

	return *this;
}

//***********************************************************************************
// Length related functions
//***********************************************************************************

//=======================================================================================
// Returns the number of characters. The terminal null character is NOT included.
size_t TXString::GetLength() const
{
	return stdUStr.length();
}

//=======================================================================================
// Return the size in bytes. Terminal character is not counted.
size_t TXString::GetByteSize() const
{
	return (stdUStr.length() * sizeof(TXChar));
}

//=======================================================================================
// Returns the number of bytes when encoding is Mac, Win, Sys, or UTF-8. Returns the 
// number of UTF-16 code points when the encoding is UTF-16. UTF-16 encoding is added to 
// support LenEncoding(...) VS function. To get the number of UTF-16 code points in C++
// code, TXString::GetLength() should be used. Terminal character is not counted.
size_t TXString::GetEncodingLength(ETXEncoding e) const
{
	size_t encodingLen = 0;

	if (e == ETXEncoding::eUTF16)
	{
		encodingLen = stdUStr.length();
	}
	else
	{
		PrepareCharBuffer(e);
		encodingLen = strlen(charPtr);
	}

	return encodingLen;
}

//=======================================================================================
// Return true if string is empty. Return false otherwise.
bool TXString::IsEmpty() const
{
	return stdUStr.empty();
}

//=======================================================================================
// Resize to 'len' characters. Return TXString itself.
TXString& TXString::SetLength(size_t len)
{
	if (len < stdUStr.length())
	{
		stdUStr.resize(len);
		TrimRightInvalidCharacter();
	}
	else
	{
		stdUStr.resize(len);
	}

	return *this;
}

//=======================================================================================
// Fill string with 'len' number of 'ch'. Always return true.
TXString& TXString::SetLength(size_t len, TXChar ch)
{
	if (ch == 0)
	{
		stdUStr.clear();
	}
	else
	{
		stdUStr.resize(len, ch);
	}

	return *this;
}

//=======================================================================================
// Keep 'len' number of characters and reduce the length to 'len'. Null character is not
// counted in 'len'. If len is not less than the current length, does nothing.
TXString& TXString::Truncate(size_t len)
{
	if (len < stdUStr.length())
	{
		stdUStr.resize(len);
		TrimRightInvalidCharacter();
	}

	return *this;
}

//=======================================================================================
// Erase the contents. TXString becomes empty and length is zero.
TXString& TXString::Clear()
{
	stdUStr.clear();

	return *this;
}


//***********************************************************************************
// Element access
//***********************************************************************************

//=======================================================================================
// Return the reference of character at 'nIndex'. If 'nIndex' is invalid, a reference to
// a static TXChar (zero) is returned.
TXChar& TXString::operator[](ptrdiff_t nIndex)
{
	//ASSERTN(kPChang, nIndex >= 0 && nIndex < (ptrdiff_t)stdUStr.length());
	if (nIndex >= 0 && nIndex < (ptrdiff_t)stdUStr.length())
	{
		return stdUStr[nIndex];
	}
	else
	{
		static TXChar zero;
		zero = 0;
		return zero;
	}
}

//=======================================================================================
// Return a copy of character at index 'nIndex'. If nIndex is out of range, 0 is returned.
TXChar TXString::operator[](ptrdiff_t nIndex) const
{
	//ASSERTN(kPChang, nIndex >= 0 && nIndex < (ptrdiff_t)stdUStr.length());
	if (nIndex >= 0 && nIndex < (ptrdiff_t)stdUStr.length())
	{
		return stdUStr[nIndex];
	}
	else
	{
		return 0;
	}
}

//=======================================================================================
// Return a reference of the character at index 'nIndex'. If nIndex is out of range, a 
// reference to a static TXChar (zero) is returned.
TXChar& TXString::GetAt(size_t nIndex)
{
	//ASSERTN(kPChang, nIndex < stdUStr.length());
	if (nIndex < stdUStr.length())
	{
		return stdUStr[nIndex];
	}
	else
	{
		static TXChar zero;
		zero = 0;
		return zero;
	}
}

//=======================================================================================
// Return a copy of the character at index 'nIndex'. If nIndex is out of range, 0 is
// returned.
TXChar TXString::GetAt(size_t nIndex) const
{
	//ASSERTN(kPChang, nIndex < stdUStr.length());
	if (nIndex < stdUStr.length())
	{
		return stdUStr[nIndex];
	}
	else
	{
		return 0;
	}
}

//=======================================================================================
// Return a reference of the last character. If this string is empty, returns dummy ref.
TXChar& TXString::GetLast()
{
	//ASSERTN(kPChang, !stdUStr.empty());
	if (stdUStr.empty())
	{
		static TXChar zero;
		zero = 0;
		return zero;
	}
	else
	{
		return stdUStr.back();
	}
}

//=======================================================================================
// Return a copy of the last character. If this string is empty, returns 0.
TXChar TXString::GetLast() const
{
	//ASSERTN(kPChang, !stdUStr.empty());
	if (stdUStr.empty())
	{
		return 0;
	}
	else
	{
		return stdUStr.back();
	}
}

//=======================================================================================
// Set character at index 'nIndex' to 'ch'. If nIndex is out of range, does nothing.
TXString& TXString::SetAt(size_t nIndex, TXChar ch)
{
	//ASSERTN(kPChang, nIndex < stdUStr.length());
	if (nIndex < stdUStr.length())
	{
		stdUStr[nIndex] = ch;
	}

	return *this;
}


//***************************************************************************************
// Concatenation
//***************************************************************************************

//=======================================================================================
// Extends string by appending another TXString object
TXString& TXString::operator+=(const TXString& src)
{
	stdUStr += src.stdUStr;
	return *this;
}

//=======================================================================================
// Concatenate const char buffer (UTF-8). If 'src' is nullptr, does nothing.
TXString& TXString::operator+=(const char* src)
{
	//ASSERTN(kPChang, src != nullptr);
	if (src != nullptr)
	{
		stdUStr += TXString(src).stdUStr;
	}

	return *this;
}

//=======================================================================================
// Concatenate const unsigned char buffer (UTF-8). If 'src' is nullptr, does nothing.
TXString& TXString::operator+=(const unsigned char *src)
{
	if (src && *src != 0)
	{
		char charBuf[256];
		strncpy(charBuf, (const char *)src + 1, src[0]);
		charBuf[src[0]] = 0;
		stdUStr += TXString(charBuf).stdUStr;
	}

	return *this;
}

//=======================================================================================
// Concatenate const UCChar buffer. If 'src' is nullptr, does nothing.
TXString& TXString::operator+=(const UCChar* src)
{
	//ASSERTN(kPChang, src != nullptr);
	if (src != nullptr)
	{
		stdUStr += (const TXChar*)src;
	}

	return *this;
}

//=======================================================================================
// Concatenate const wchar_t buffer. If 'src' is nullptr, does nothing.
TXString& TXString::operator+=(const wchar_t* src)
{
	//ASSERTN(kPChang, src != nullptr);
	if (src != nullptr)
	{
#if GS_WIN
		stdUStr += src;
#elif GS_LIN
		stdUStr += TXString(src).stdUStr;
#else
		stdUStr += TXString(src).stdUStr;
#endif
	}

	return *this;
}

//=======================================================================================
// Appends one char
TXString& TXString::operator+=(char ch)
{
	stdUStr += (unsigned char)ch;	// The casting is necessary on Windows.
	return *this;
}

#ifdef GS_LIN
// Appends one char
TXString& TXString::operator+=(TXChar ch)
{
	stdUStr += ch;
	return *this;
}
#endif

//=======================================================================================
// Appends one unsigned char
TXString& TXString::operator+=(unsigned char ch)
{
	stdUStr += ch;
	return *this;
}

//=======================================================================================
// Appends one UCChar
TXString& TXString::operator+=(UCChar ch)
{
	stdUStr += (TXChar)ch;
	return *this;
}

//=======================================================================================
// Appends one wchar_t
TXString& TXString::operator+=(wchar_t w)
{
#if GS_WIN
	stdUStr += w;
#elif GS_LIN
	stdUStr += w;
#else
		if((int) w <= 0xffff)
	{
		stdUStr += (TXChar) w;
	}
	else
	{
		UCChar u[3];
		utf32ToTXCharBuffer(w, u);
		stdUStr += u;
	}
#endif

	return *this;
}

//=======================================================================================
// Concatenates another TXString object
TXString& TXString::operator<<(const TXString& src)
{
	stdUStr += src.stdUStr;
	return *this;
}

//=======================================================================================
// Concatenates char buffer (UTF-8). If 'src' is nullptr, does nothing.
TXString& TXString::operator<<(const char* src)
{
	return (*this += src);
}

//=======================================================================================
// Concatenates unsigned char buffer (UTF-8). If 'src' is nullptr, does nothing.
TXString& TXString::operator<<(const unsigned char *src)
{
	return (*this += src);
}

//=======================================================================================
// Concatenates UCChar buffer. If 'src' is nullptr, does nothing.
TXString& TXString::operator<<(const UCChar* src)
{
	return (*this += src);
}

//=======================================================================================
// Concatenates wchar_t buffer. If 'src' is nullptr, does nothing.
TXString& TXString::operator<<(const wchar_t* src)
{
	return (*this += src);
}

//=======================================================================================
// Appends one char
TXString& TXString::operator<<(char ch)
{
	stdUStr += (unsigned char)ch;
	return *this;
}

//=======================================================================================
// Appends one unsigned char
TXString& TXString::operator<<(unsigned char ch)
{
	stdUStr += ch;
	return *this;
}

//=======================================================================================
// Appends one UCChar
TXString& TXString::operator<<(UCChar ch)
{
	stdUStr += (TXChar)ch;
	return *this;
}

//=======================================================================================
// Appends one wchar_t
TXString& TXString::operator<<(wchar_t ch)
{
	return (*this += ch);
}

//=======================================================================================
// Appends signed int 32 number as string
TXString& TXString::operator<<(Sint32 n)
{
	return (*this += std::to_string(n).c_str());
}

//=======================================================================================
// Appends one signed int 64 number as string
TXString& TXString::operator<<(Sint64 n)
{
	return (*this += std::to_string(n).c_str());
}

//=======================================================================================
// Appends unsigned int 32 number as string
TXString& TXString::operator<<(Uint32 n)
{
	return (*this += std::to_string(n).c_str());
}

//=======================================================================================
// Appends one unsigned int 64 number as string
TXString& TXString::operator<<(Uint64 n)
{
	return (*this += std::to_string(n).c_str());
}

//=======================================================================================
// Appends one real number
TXString& TXString::operator<<(double number)
{
	return (*this += std::to_string(number).c_str());
}

//=======================================================================================
// Appends one size_t number as string
#if GS_MAC // Uint64 is different than size_t on the mac
TXString& TXString::operator<<(size_t n)
{
	return (*this += std::to_string(n).c_str());
}
#endif

//***************************************************************************************
// Insertion and deletion
//***************************************************************************************

//=======================================================================================
// Insert another TXString at position 'pos'. If pos is larger than length, the new
// string is append to the end.
TXString& TXString::Insert(size_t pos, const TXString& src)
{
	if (pos < stdUStr.length())
	{
		stdUStr.insert(pos, src.stdUStr);
	}
	else
	{
		stdUStr.append(src.stdUStr);
	}

	return *this;
}

//=======================================================================================
// Insert one const char buffer at position 'pos'. If pos is larger than length, the new
// string is append to the end. UTF-8 is assumed.
TXString& TXString::Insert(size_t pos, const char* src)
{
	//ASSERTN(kPChang, src != nullptr);
	if (src != nullptr)
	{
		Insert(pos, TXString(src));
	}

	return *this;
}

//=======================================================================================
// Insert unsigned char buffer at position 'pos'. If pos is larger than length, the new
// string is append to the end. UTF-8 is assumed.
TXString& TXString::Insert(size_t pos, const unsigned char* src)
{
	//ASSERTN(kPChang, src != nullptr);
	if (src != nullptr)
	{
		Insert(pos, TXString(src));
	}

	return *this;
}

//=======================================================================================
// Insert UCChar buffer at position 'pos'. If pos is larger than length, the new
// string is append to the end.
TXString& TXString::Insert(size_t pos, const UCChar* src)
{
	//ASSERTN(kPChang, src != nullptr);
	if (src != nullptr)
	{
		if (pos < stdUStr.length())
		{
			stdUStr.insert(pos, (const TXChar*)src);
		}
		else
		{
			stdUStr.append((const TXChar*)src);
		}
	}

	return *this;
}

//=======================================================================================
// Insert wchar_t buffer at position 'pos'. If pos is larger than length, the new
// string is append to the end.
TXString& TXString::Insert(size_t pos, const wchar_t* src)
{
	//ASSERTN(kPChang, src != nullptr);
	if (src != nullptr)
	{
#if GS_WIN
		if (pos < stdUStr.length())
		{
			stdUStr.insert(pos, src);
		}
		else
		{
			stdUStr.append(src);
		}
#elif GS_LIN
		if (pos < stdUStr.length())
		{
			stdUStr.insert(pos, TXString(src).stdUStr);
		}
		else
		{
			stdUStr.append(TXString(src).stdUStr);
		}
#else
		if (pos < stdUStr.length())
		{
			stdUStr.insert(pos, TXString(src).stdUStr);
		}
		else
		{
			stdUStr.append(TXString(src).stdUStr);
		}
#endif
	}

	return *this;
}

//=======================================================================================
// Insert one character 'ch' at position 'pos'. If pos is larger than length, the new
// character is append to the end.
TXString& TXString::Insert(size_t pos, char ch)
{
	if (pos < stdUStr.length())
	{
		stdUStr.insert(pos, 1, (unsigned char)ch);	// The casting is necessary.
	}
	else
	{
		stdUStr.append(1, (unsigned char)ch);
	}

	return *this;
}

//=======================================================================================
// Insert one character 'ch' at position 'pos'. If pos is larger than length, the new
// character is append to the end.
TXString& TXString::Insert(size_t pos, unsigned char ch)
{
	if (pos < stdUStr.length())
		stdUStr.insert(pos, 1, ch);
	else
		stdUStr.append(1, ch);

	return *this;
}

//=======================================================================================
// Insert one character 'ch' at position 'pos'. If pos is larger than length, the new
// character is append to the end.
TXString& TXString::Insert(size_t pos, UCChar ch)
{
	if (pos < stdUStr.length())
		stdUStr.insert(pos, 1, (TXChar)ch);
	else
		stdUStr.append(1, (TXChar)ch);

	return *this;
}

//=======================================================================================
// Insert one character 'ch' at position 'pos'. If pos is larger than length, the new
// character is append to the end.
TXString& TXString::Insert(size_t pos, wchar_t w)
{
#if GS_WIN
	if (pos < stdUStr.length())
	{
		stdUStr.insert(pos, 1, w);
	}
	else
	{
		stdUStr.append(1, w);
	}
#elif GS_LIN
	if (pos < stdUStr.length())
	{
		stdUStr.insert(pos, 1, w);
	}
	else
	{
		stdUStr.append(1, w);
	}
#else
	if((int) w <= 0xffff)
	{
		if(pos < stdUStr.length())
		{
			stdUStr.insert(pos, 1, (TXChar) w);
		}
		else
		{
			stdUStr.append(1, (TXChar) w);
		}
	}
	else
	{
		UCChar u[3];
		utf32ToTXCharBuffer(w, u);
		
		if(pos < stdUStr.length())
		{
			stdUStr.insert(pos, u);
		}
		else
		{
			stdUStr.append(u);
		}
	}
#endif

	return *this;
}

//=======================================================================================
// Erases characters starting from 'pos' for 'len' characters. If 'pos' is greater than
// the length, nothing happens. If 'len' is larger than the number of characters could be
// removed, it erases characters from 'pos' to the end.
TXString& TXString::Delete(size_t pos, size_t len /* -1 */)
{
	if (pos < stdUStr.length())
	{
		stdUStr.erase(pos, len);
	}

	return *this;
}

//=======================================================================================
// Delete the last character. Does nothing if the string is empty.
TXString& TXString::DeleteLast()
{
	if (!stdUStr.empty())
	{
		stdUStr.pop_back();
	}

	return *this;
}

//=======================================================================================
// Trims white spaces (' ', '\t') at left end.
TXString& TXString::TrimLeft()
{
	ptrdiff_t pos = FindNotOneOf(" \t");

	if (pos >= 0)
	{
		stdUStr.erase(0, pos);
	}
	else
	{
		// Everything in the string is either a space or a tab, so remove everything.
		stdUStr.clear();
	}

	return *this;
}

//=======================================================================================
// Trims white spaces (' ', '\t') at right end.
TXString& TXString::TrimRight()
{
	ptrdiff_t pos = ReverseFindNotOneOf(" \t");

	if (pos >= 0)
	{
		stdUStr.erase(pos + 1);
	}
	else
	{
		// Everything in the string is either a space or a tab, so remove everything.
		stdUStr.clear();
	}

	return *this;
}

//=======================================================================================
// Trims white spaces (' ', '\t') at both ends.
TXString& TXString::Trim()
{
	TrimLeft();
	TrimRight();

	return *this;
}

//=======================================================================================
// Trims invalid chars at the left end. When the string is changed or created, such as
// Right(...), it is possible that the first or the last character is part of a pair of
// UTF-16 surrogates. This function remove invalid character at the left end so they won't
// appear like garbage character there.
TXString& TXString::TrimLeftInvalidCharacter()
{
	if (!stdUStr.empty())
	{
		// Trim left end
		if (stdUStr[0] >= 0xDC00 && stdUStr[0] <= 0xDFFF)
		{
			stdUStr.erase(0, 1);
		}
	}

	return *this;
}

//=======================================================================================
// This function remove invalid character at the right end.
TXString& TXString::TrimRightInvalidCharacter()
{
	if (!stdUStr.empty())
	{
		// Trim right end
		if (stdUStr.back() >= 0xD800 && stdUStr.back() <= 0xDBFF)
		{
			stdUStr.pop_back();
		}
	}

	return *this;
}

//=======================================================================================
// Trims invalid chars at both ends.
TXString& TXString::TrimInvalidCharacters()
{
	if (!stdUStr.empty())
	{
		// Trim left end
		TrimLeftInvalidCharacter();

		// Trim right end
		TrimRightInvalidCharacter();
	}

	return *this;
}


//***************************************************************************************
// Replacement, case conversion, reversion
//***************************************************************************************

//=======================================================================================
// Replaces all 'oldStr' with 'newSTr'. If 'bIgnoreCase' is true, case is ignored.
TXString& TXString::Replace(const TXString& oldStr, const TXString& newStr, bool bIgnoreCase /* false */)
{
	size_t dstStartPos = 0;

	if (bIgnoreCase)
	{
		TXString lowerSrcStr(*this);
		lowerSrcStr.MakeLower();

		TXString lowerOldStr(oldStr);
		lowerOldStr.MakeLower();

		size_t srcStartPos = 0;

		// For keeping the position in the destination
		const size_t delta = (size_t)newStr.stdUStr.length() - (int)oldStr.stdUStr.length();
		size_t deltaSum = 0;

		while ((srcStartPos = (size_t)lowerSrcStr.stdUStr.find(lowerOldStr.stdUStr, srcStartPos)) != StdUStr::npos)
		{
			dstStartPos = srcStartPos + deltaSum;
			stdUStr.replace(dstStartPos, oldStr.stdUStr.length(), newStr.stdUStr);
			deltaSum += delta;
			srcStartPos += (size_t)oldStr.stdUStr.length();
		}
	}
	else
	{
		while ((dstStartPos = (size_t)stdUStr.find(oldStr.stdUStr, dstStartPos)) != StdUStr::npos)
		{
			stdUStr.replace(dstStartPos, oldStr.stdUStr.length(), newStr.stdUStr);
			dstStartPos += (size_t)newStr.stdUStr.length();
		}
	}

	return *this;
}

//=======================================================================================
// Convert all characters to upper case.
TXString& TXString::MakeUpper()
{
#if GS_WIN
    CharUpperBuffW((LPWSTR)stdUStr.data(), (DWORD)stdUStr.size());	// LCMapStringEx
#elif GS_LIN
	// LINUX_IMPLEMENTATION - done
	std::transform(stdUStr.begin(), stdUStr.end(), stdUStr.begin(), ::toupper);
#else
	size_t len = stdUStr.size();

	CFMutableStringRef	cfUniStr = CFStringCreateMutableWithExternalCharactersNoCopy(
																			kCFAllocatorDefault, 
																			(UCChar*)stdUStr.data(), 
																			len, 
																			len, 
																			kCFAllocatorNull);

	if (cfUniStr) 
	{
		// If there is issue with nil, try CFLocaleCopyCurrent or CFLocaleCopyPreferredLanguages
		CFStringUppercase(cfUniStr, nil);
		CFRelease(cfUniStr);
	}
#endif

	return *this;
}

//=======================================================================================
// Convert all characters to lower case.
TXString& TXString::MakeLower()
{
#if GS_WIN
    CharLowerBuffW((LPWSTR)stdUStr.data(), (DWORD)stdUStr.size());	// LCMapStringEx
#elif GS_LIN
	// LINUX_IMPLEMENTATION - done
	std::transform(stdUStr.begin(), stdUStr.end(), stdUStr.begin(), ::tolower);
#else
	size_t len = stdUStr.size();

	CFMutableStringRef	cfUniStr = CFStringCreateMutableWithExternalCharactersNoCopy(
																			kCFAllocatorDefault, 
																			(UniChar*)stdUStr.data(), 
																			len, 
																			len, 
																			kCFAllocatorNull);

	if (cfUniStr) 
	{
		// If there is issue with nil, try CFLocaleCopyCurrent or CFLocaleCopyPreferredLanguages
		CFStringLowercase(cfUniStr, nil);
		CFRelease(cfUniStr);
	}
#endif

	return *this;
}

//=======================================================================================
// Reverse the string.
TXString& TXString::MakeReverse()
{
	if (stdUStr.length() > 0)
	{
		for (size_t i = 0, j = stdUStr.length() - 1; i < j; ++i, --j)
		{
			TXChar ch = stdUStr[i];
			stdUStr[i] = stdUStr[j];
			stdUStr[j] = ch;
		}
	}

	return *this;
}

//***************************************************************************************
// Getting data and casting
//***************************************************************************************

//=======================================================================================
// Returns const pointer to the TXChar buffer.
const TXChar* TXString::GetData() const
{
	return stdUStr.data();
}

//=======================================================================================
// Returns const pointer to the TXChar buffer.
const TXChar* TXString::GetTXCharPtr() const
{
	return stdUStr.data();
}

//=======================================================================================
// Returns a pointer to const UTF-8 char buffer.
TXString::operator const char*() const
{
	PrepareCharBuffer();
	return charPtr;
}

//=======================================================================================
// Returns a pointer to const UTF-8 unsigned char buffer.
TXString::operator const unsigned char*() const
{
	PrepareCharBuffer();

	size_t len = strlen(charPtr);

	if (len > 255)
		len = 255;

	memmove(charPtr + 1, charPtr, len);

	charPtr[0] = (char)len;

	return (const unsigned char*)charPtr;
}

//=======================================================================================
// Returns a pointer to const UCChar buffer.
TXString::operator const UCChar*() const
{
	return (const UCChar*)stdUStr.c_str();
}

//=======================================================================================
// Returns a pointer to const wchar_t buffer. On Mac, returns a pointer to a TEMPORARY
// wchar_t buffer.
TXString::operator const wchar_t*() const
{
#if GS_WIN
	return stdUStr.c_str();
#elif GS_LIN
	wStr = GetStdWString();
	return wStr.data();
#else
	wStr = GetStdWString();
	return wStr.data();
#endif
}

//=======================================================================================
// Returns a std::string object with 'e' encoding
std::string TXString::GetStdString(ETXEncoding e) const	// Default: eUTF8
{
	PrepareCharBuffer(e);

	return std::string(charPtr);
}

//=======================================================================================
// Returns a std::wstring object
std::wstring TXString::GetStdWString() const
{
#if GS_WIN
	return std::wstring(stdUStr.c_str());
#elif GS_LIN
	std::wstring_convert<std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>> converter;

	return converter.from_bytes((const char*)stdUStr.data(), (const char*)(stdUStr.data() + stdUStr.length()));
#else
	std::wstring_convert<std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>> converter;

	return converter.from_bytes((const char*)stdUStr.data(), (const char*)(stdUStr.data() + stdUStr.length()));
#endif
}

//=======================================================================================
// Returns a CFStringRef. The client is responsible of releasing the returned ref.
#if GS_MAC
CFStringRef TXString::GetCFStringRef() const
{
	return CFStringCreateWithCharacters(NULL, stdUStr.data(), stdUStr.length());
}
#endif

//***************************************************************************************
// Copying data into external buffer
//***************************************************************************************

//=======================================================================================
// 'bufSize' is the size of the buffer in bytes. For example, "xyz" needs four bytes to
// include '\0' at the end.
void TXString::CopyInto(char *dst,
	size_t bufSize,
	ETXEncoding e) const	// ETXEncoding::eUTF8
{
	//ASSERTN(kPChang, dst != nullptr);

	if (dst && bufSize > 0)
	{
		PrepareCharBuffer(e);

		size_t len = strlen(charPtr);

		if (len >= bufSize)
		{
			len = bufSize - 1;
		}

		strncpy(dst, charPtr, len);
		dst[len] = '\0';
	}
}

//=======================================================================================
// Copy string data into 'dst' unsigned char buffer based on 'e' encoding.
// bufSize is the size of the buffer.
void TXString::CopyInto(unsigned char* ps,
	size_t bufSize,
	ETXEncoding e) const	// ETXEncoding::eUTF8
{
	//ASSERTN(kPChang, ps != nullptr);

	if (ps && bufSize > 0)
	{
		PrepareCharBuffer(e);

		size_t len = strlen(charPtr);

		if (len > bufSize - 1)
			len = bufSize - 1;

		if (len > 255)
			len = 255;

		strncpy((char *)ps + 1, charPtr, len);

		ps[0] = (unsigned char)len;
	}
}

//=======================================================================================
// Copy string data into 'dst' UCChar buffer. bufElemNum is the number of elements in
// the buffer. '\0' will be added to the end of string even if buffer is not big enough.
void TXString::CopyInto(UCChar* dst, size_t bufElemSize) const
{
	//ASSERTN(kPChang, dst);

	if (dst && bufElemSize != 0)
	{
		size_t len = stdUStr.length();

		if (len < bufElemSize)
		{
			// Buffer is large enough to store the string.
			stdUStr.copy((TXChar*)dst, len);
			dst[len] = 0;
		}
		else
		{
			// Buffer is NOT large enough to store the string.
			stdUStr.copy((TXChar*)dst, bufElemSize - 1);
			dst[bufElemSize - 1] = 0;
		}
	}
}

//=======================================================================================
// Copy string data into 'dst' wchar_t buffer. bufElemNum is the number of elements in
// the buffer. '\0' will be added to the end of string even if buffer is not big enough.
void TXString::CopyInto(wchar_t* dst, size_t bufElemSize) const
{
	//ASSERTN(kPChang, dst != nullptr);

	if (dst && bufElemSize != 0)
	{
#if GS_WIN
		size_t len = stdUStr.length();

		if (len < bufElemSize)
		{
			// Buffer is large enough to store the string.
			stdUStr.copy(dst, len);
			dst[len] = 0;
		}
		else
		{
			// Buffer is NOT large enough to store the string.
			stdUStr.copy(dst, bufElemSize - 1);
			dst[bufElemSize - 1] = 0;
		}
#elif GS_LIN
		std::string bytes;
		bytes.reserve(stdUStr.size() * 2);

		for (const char16_t c : stdUStr) {
			bytes.push_back(static_cast<char>(c / 256));
			bytes.push_back(static_cast<char>(c % 256));
		}

		std::wstring_convert<std::codecvt_utf16<char32_t>, char32_t> convert;
		std::u32string u32Str = convert.from_bytes(bytes);


		size_t len = u32Str.length();

		if (len < bufElemSize)
		{
			// Buffer is large enough to store the string.
			u32Str.copy((char32_t*)dst, len);
			dst[len] = 0;
		}
		else
		{
			// Buffer is NOT large enough to store the string.
			u32Str.copy((char32_t*)dst, bufElemSize - 1);
			dst[bufElemSize - 1] = 0;
		}
#else
		txCharBufferToUtf32Buffer(stdUStr.data(), (char32_t*)dst, bufElemSize);
#endif
	}
}


//***************************************************************************************
// Find functions
//***************************************************************************************

//=======================================================================================
// Return the position of the first found 'sub' in the string. The search starts from
// position 'posFirst'. If 'bIgnoreCase' is true, case insensitive search is performed. If
// TXString or 'sub' is empty, returns -1.
ptrdiff_t TXString::Find(const TXString &sub,
	size_t posFirst,			// 0
	bool bIgnoreCase) const	// false
{
	if (sub.GetLength() == 0) return -1;

	size_t pos;

	if (bIgnoreCase)
	{
		// Ignore case is more expensive.
		TXString srcStr(*this);
		srcStr.MakeLower();

		TXString subStr(sub);
		subStr.MakeLower();

		pos = srcStr.stdUStr.find(subStr.stdUStr, posFirst);
	}
	else
	{
		pos = stdUStr.find(sub.stdUStr, posFirst);
	}

	if (pos == stdUStr.npos) pos = -1;

	return pos;
}

//=======================================================================================
// Return the position of the first found 'ch' in the string. The search starts from
// position 'posFirst'. If 'bIgnoreCase' is true, case insensitive search is performed.
// 'ch' can be type of unsigned char, UCChar, or wchar_t.
ptrdiff_t TXString::Find(int ch,
	size_t posFirst,			// 0
	bool bIgnoreCase) const	// false
{
	size_t pos;

	if (bIgnoreCase)
	{	// Ignore case is more expensive.
		TXString strCh((TXChar)ch);
		strCh.MakeLower();

		TXString strCopy(*this);
		strCopy.MakeLower();

		pos = strCopy.stdUStr.find(strCh.stdUStr[0], posFirst);
	}
	else
	{
		pos = stdUStr.find(ch, posFirst);
	}

	if (pos == stdUStr.npos) pos = -1;

	return pos;
}

//=======================================================================================
// Return the position of the first found 'ch' in the string. The search starts from
// position 'posFirst'. If 'bIgnoreCase' is true, case insensitive search is performed.
ptrdiff_t TXString::Find(char ch,
	size_t posFirst,			// 0
	bool bIgnoreCase) const	// false
{
	return Find((unsigned char)ch, posFirst, bIgnoreCase);
}

//=======================================================================================
// Searches from right to left. Returns the starting index of a sub-string.
// posLast is the position of the last character to be considered in the search.
// If 'bIgnoreCase' is true, case insensitive search is performed.
// Return -1 if not found.
ptrdiff_t TXString::ReverseFind(const TXString &sub,
	size_t posLast,			// -1
	bool bIgnoreCase) const	// false
{
	if (sub.GetLength() == 0) return -1;

	size_t pos;

	if (bIgnoreCase)
	{	// Ignore case is more expensive.
		TXString srcStr(*this);
		srcStr.MakeLower();

		TXString subStr(sub);
		subStr.MakeLower();

		pos = srcStr.stdUStr.rfind(subStr.stdUStr, posLast);
	}
	else
	{
		pos = stdUStr.rfind(sub.stdUStr, posLast);
	}

	if (pos == stdUStr.npos) pos = -1;

	return pos;
}

//=======================================================================================
// Searches from right to left. Returns the position of the first found 'ch'.
// 'posLast' is the last possible found position.
// If 'bIgnoreCase' is true, case is ignored.
// The type of 'ch' can be unsigned char, UCChar, wchar_t.
ptrdiff_t TXString::ReverseFind(int ch,
	size_t posLast,			// -1
	bool bIgnoreCase) const	// false
{
	size_t pos;

	if (bIgnoreCase)
	{	// Ignore case is more expensive.
		TXString srcStr(*this);
		srcStr.MakeLower();

		TXString chStr((TXChar)ch);
		chStr.MakeLower();

		pos = srcStr.stdUStr.rfind(chStr.stdUStr[0], posLast);
	}
	else {
		pos = stdUStr.rfind(ch, posLast);
	}

	if (pos == stdUStr.npos) pos = -1;

	return pos;
}

//=======================================================================================
// Searches from right to left. Returns the position of the first found 'ch'.
// posLast is the position of the last character to be considered in the search.
// If 'bIgnoreCase' is true, case is ignored.
ptrdiff_t TXString::ReverseFind(char ch,
	size_t posLast,			// -1
	bool bIgnoreCase) const	// false
{
	return ReverseFind((unsigned char)ch, posLast, bIgnoreCase);
}

//=======================================================================================
// Return the position of the first found character in charSet. 
// 'posFirst'is the first character to be considered in the search.
// Return -1 if none is found.
ptrdiff_t TXString::FindOneOf(const TXString &charSet,
	size_t posFirst) const	// 0
{
	size_t pos = stdUStr.find_first_of(charSet.stdUStr, posFirst);

	if (pos == stdUStr.npos) pos = -1;

	return pos;
}

//=======================================================================================
// Return the position of the last character in the string that matchs one of the
// characters in 'charSet'. 
// 'posLast'is the last character to be considered in the search.
// Return -1 if no match.
ptrdiff_t TXString::ReverseFindOneOf(const TXString &charSet,
	size_t posLast) const		// -1
{
	size_t pos = stdUStr.find_last_of(charSet.stdUStr, posLast);

	if (pos == stdUStr.npos) pos = -1;

	return pos;
}

//=======================================================================================
// Return the position of the first found character NOT in charSet. 
// 'posFirst'is the first character to be considered in the search.
// Return -1 if none is found.
ptrdiff_t TXString::FindNotOneOf(const TXString &charSet,
	size_t posFirst) const	// 0
{
	size_t pos = stdUStr.find_first_not_of(charSet.stdUStr, posFirst);

	if (pos == stdUStr.npos) pos = -1;

	return pos;
}

//=======================================================================================
// Return the position of the last character in the string that does NOT match any of
// the characters in 'charSet'. 
// 'posLast'is the last character to be considered in the search.
// Return -1 if none found.
ptrdiff_t TXString::ReverseFindNotOneOf(const TXString &charSet,
	size_t posLast) const	// -1
{
	size_t pos = stdUStr.find_last_not_of(charSet.stdUStr, posLast);

	if (pos == stdUStr.npos) pos = -1;

	return pos;
}

//***************************************************************************************
// Creating sub-string
//***************************************************************************************

//=======================================================================================
// Returns a copy of sub-string containing 'len' characters starting from 'nFirst'.
// If 'len' is greater than the length, characters from 'nFirst' to the end is returned.
TXString TXString::Mid(size_t nFirst, size_t len) const
{
	// If there is any exception, return an empty string.
	try {
		if (nFirst >= stdUStr.length()) return TXString();

		return TXString(stdUStr.substr(nFirst, len)).TrimInvalidCharacters();
	}
	catch (...) {
		//DSTOP((kPChang, "Error in TXString::Mid(...)"));	// Something wrong!
		return TXString();
	}
}

//=======================================================================================
// Returns a copy of string containing the left 'len' number of characters. If 'len'
// is greater than the length, the whole string is returned.
TXString TXString::Left(size_t len) const
{
	return TXString(stdUStr.substr(0, len)).TrimRightInvalidCharacter();
}

//=======================================================================================
// Returns a copy of string containing the right 'len' number of characters. If 'len'
// is greater than the length, the whole string is returned.
TXString TXString::Right(size_t len) const
{
	// If there is any exception, return an empty string.
	try {
		if (len >= stdUStr.length()) return *this;

		return TXString(stdUStr.substr(stdUStr.length() - len)).TrimLeftInvalidCharacter();
	}
	catch (...) {
		//DSTOP((kPChang, "Error in TXString::Right(...)"));	// Something wrong!
		return TXString();
	}
}

//=======================================================================================
// Splits string on every occasion of ch and stores result in an array
// Results do not contain ch
std::vector<TXString> TXString::Split(char ch) const
{
	std::vector<TXString> result;

	size_t lastOccurrence = 0;

	while(lastOccurrence < size_t(-1))
	{
		size_t pos = Find(ch, lastOccurrence + 1);
		if(pos != 0)
		{
			result.push_back(Mid(lastOccurrence, pos - lastOccurrence));
		}
		lastOccurrence = pos + 1;
		if(pos + 1 == GetLength())
		{
			break;
		}
	}

	return result;
}

//=======================================================================================
// Splits string on every occasion of ch and stores result in an array
// Results do not contain ch
std::vector<TXString> TXString::Split(TXString ch) const
{
	
	std::vector<TXString> result;

	size_t lastOccurrence = 0;

	while(lastOccurrence < size_t(-1))
	{
		size_t pos = Find(ch, lastOccurrence + 1);
		if(pos != 0)
		{
			result.push_back(Mid(lastOccurrence, pos - lastOccurrence));
		}
		lastOccurrence = pos + 1;
		if(pos + 1 == GetLength())
		{
			break;
		}
	}

	return result;
}


//***************************************************************************************
// Convertion to and from numerics
//***************************************************************************************

//=======================================================================================
// Returns Sint32 value based on the string. If the string is not valid to converted to
// an integer, returns 0. White spaces in the beginning are ignored. The first valid
// number is returned. e.g. " 123 123 " returns 123.
Sint32 TXString::atoi() const
{
	return ::atoi(*this);
}

//=======================================================================================
// Returns Sint64 value based on the string. If the string is not valid to be converted
// to an integer, returns 0. White spaces in the beginning are ignored. The first valid
// number is returned. e.g. " 123 123 " returns 123.
Sint64 TXString::atoi64() const
{
	return ::atoi(*this);
}

//=======================================================================================
// Returns double value based on the string. If the string is not valid to be converted,
// returns 0. White spaces in the beginning are ignored. The first valid number is
// returned.
Real64 TXString::atof() const
{
	return ::atof(*this);
}

//=======================================================================================
// Sets the current string to the input value
TXString& TXString::itoa(Sint64 value)
{
	return (*this = std::to_string(value));
}

//=======================================================================================
// Sets the current string to the input value
TXString& TXString::ftoa(Real64 value)
{
	return (*this = std::to_string(value));
}

//=======================================================================================
// Sets the current string to the input value
TXString& TXString::ftoa(Real64 value, Sint32 precision)
{
	return (*this = TXString::ToStringReal(value, precision));
}

bool TXString::IsCompleteNumber()
{
	auto it = stdUStr.begin();
    while (it != stdUStr.end() && std::isdigit(*it)) ++it;
    return !stdUStr.empty() && it == stdUStr.end();

}

//=======================================================================================
/*static*/ TXString TXString::ToStringInt(Sint64 value)
{
	return std::to_string(value);
}

//=======================================================================================
/*static*/ TXString TXString::ToStringInt(Sint64 value, Sint32 width, wchar_t paddingChar)
{
	std::wstringstream out;
	out << std::setfill(paddingChar) << std::setw(width) << value;

	std::wstring wStr = out.str();
	return TXString(wStr.data());
}

//=======================================================================================
/*static*/ TXString TXString::ToStringReal(Real64 value)
{
	return std::to_string(value);
}

//=======================================================================================
/*static*/ TXString TXString::ToStringReal(Real64 value, Sint32 precision, bool fixed)
{
	std::wstringstream out;
	if (fixed)
		out << std::fixed;
	out << std::setprecision(precision);
	out << value;
	out << std::setprecision(0);	// restore

	std::wstring wStr = out.str();
	return TXString(wStr.data());
}

//=======================================================================================
/*static*/ bool TXString::IsPunctuation(TXChar aTXChar)
{
#if GS_WIN
	return iswpunct(aTXChar) != 0;
#elif GS_LIN
	// LINUX_IMPLEMENTATION - done
	return std::ispunct(aTXChar);
#else
	return std::ispunct(aTXChar);
#endif
}

//=======================================================================================
/*static*/ bool TXString::IsWhitespace(TXChar aTXChar)
{
#if GS_WIN
	return iswspace(aTXChar) != 0;
#elif GS_LIN
	// LINUX_IMPLEMENTATION - done
	return std::isspace(aTXChar);
#else
	return std::isspace(aTXChar);
#endif
}


//***********************************************************************************
// Comparison
//***********************************************************************************

//=======================================================================================
// Return true if this euqals str. This is CASE SENSITIVE.
bool TXString::Equal(const TXString &str) const
{
	return (stdUStr == str.stdUStr);
}

//=======================================================================================
// Return true if this euqals str. This is CASE INSENSITIVE.
bool TXString::EqualNoCase(const TXString &str) const
{
	return (this->CompareNoCase(str) == 0);
}

//=======================================================================================
// Compares this string with str. This comparison is case sensitive.
Sint32 TXString::Compare(const TXString &str) const
{
	return stdUStr.compare(str.stdUStr);
}

//=======================================================================================
// Compares this string with str. This comparision is case insensitive.
Sint32 TXString::CompareNoCase(const TXString &str) const
{
#if GS_WIN
    return lstrcmpiW(stdUStr.c_str(), str.stdUStr.c_str());
#elif GS_LIN

	std::u16string str1(this->stdUStr);
	std::u16string str2(str.stdUStr);

	std::transform(str1.begin(), str1.end(), str1.begin(), ::toupper);
	std::transform(str2.begin(), str2.end(), str2.begin(), ::toupper);

	return str1.compare(str2);
#else
	CFStringRef cs1 = this->GetCFStringRef();
    CFStringRef cs2 = str.GetCFStringRef();
	
	ASSERTN(kBWilliams, cs1 && cs2);
	if(cs1 && cs2)
	{
		CFComparisonResult result = CFStringCompare(cs1, cs2, kCFCompareCaseInsensitive);
		CFRelease(cs1);
		CFRelease(cs2);
		return result;
	}
	
	if(cs1) CFRelease(cs1);
	if(cs2) CFRelease(cs2);
	
    return Compare(str);  // if error converting to CFString, that's pretty bad - use regular Compare as backup... 
#endif
}

//=======================================================================================
// Compares this string end with suffix.
bool TXString::EndsWith(const TXString &suffix) const
{
    return stdUStr.size() >= suffix.stdUStr.size() && 0 == stdUStr.compare(stdUStr.size()-suffix.stdUStr.size(), suffix.stdUStr.size(), suffix.stdUStr);
}

//=======================================================================================
// '==' comparison operator. This comparison is case insensitive.
bool operator==(const TXString& lhs, const TXString& rhs)
{
	return (lhs.CompareNoCase(rhs) == 0);
}

//=======================================================================================
// '==' comparison operator. This comparison is case insensitive. If 'rhs' is nullptr, 
// return false.
bool operator==(const TXString& lhs, const char* rhs)
{
	if (!rhs) return false;
	return (lhs.CompareNoCase(rhs) == 0);
}

//=======================================================================================
// '==' comparison operator. This comparison is case insensitive. If 'lhs' is nullptr, 
// return false.
bool operator==(const char* lhs, const TXString& rhs)
{
	if (!lhs) return false;
	return (TXString(lhs).CompareNoCase(rhs) == 0);
}

//=======================================================================================
// '==' comparison operator. This comparison is case insensitive. If 'rhs' is nullptr, 
// return false.
bool operator==(const TXString& lhs, const TXChar* rhs)
{
	if (!rhs) return false;
	return (lhs.CompareNoCase(TXString(rhs)) == 0);
}

//=======================================================================================
// '==' comparison operator. This comparison is case insensitive. If 'lhs' is nullptr, 
// return false.
bool operator==(const TXChar* lhs, const TXString& rhs)
{
	if (!lhs) return false;
	return (TXString(lhs).CompareNoCase(rhs) == 0);
}

//=======================================================================================
// '!=' comparison operator. This comparison is case insensitive.
bool operator!=(const TXString& lhs, const TXString& rhs)
{
	return !(lhs == rhs);
}

//=======================================================================================
// '!=' comparison operator. This comparison is case insensitive. Return true if 'rhs' 
// is nullptr.
bool operator!=(const TXString& lhs, const char* rhs)
{
	if (!rhs) return true;
	return !(lhs == rhs);
}

//=======================================================================================
// '!=' comparison operator. This comparison is case insensitive. Return true if 'lhs' is 
// nullptr.
bool operator!=(const char* lhs, const TXString& rhs)
{
	if (!lhs) return true;
	return !(lhs == rhs);
}

//=======================================================================================
// '!=' comparison operator. This comparison is case insensitive. Return true if 'rhs' is 
// nullptr.
bool operator!=(const TXString& lhs, const TXChar* rhs)
{
	if (!rhs) return true;
	return !(lhs == rhs);
}

//=======================================================================================
// '!=' comparison operator. This comparison is case insensitive. Return true if 'lhs' is 
// nullptr.
bool operator!=(const TXChar* lhs, const TXString& rhs)
{
	if (!lhs) return true;
	return !(lhs == rhs);
}

//=======================================================================================
// '>=' comparison operator. This comparison is case insensitive. 
bool operator>=(const TXString& lhs, const TXString& rhs)
{
	return (lhs.CompareNoCase(rhs) >= 0);
}

//=======================================================================================
// '<=' comparison operator. This comparison is case insensitive. 
bool operator<=(const TXString& lhs, const TXString& rhs)
{
	return (lhs.CompareNoCase(rhs) <= 0);
}

//=======================================================================================
// '>' comparison operator. This comparison is case insensitive. 
bool operator>(const TXString& lhs, const TXString& rhs)
{
	return (lhs.CompareNoCase(rhs) > 0);
}

//=======================================================================================
// '<' comparison operator. This comparison is case insensitive. 
bool operator<(const TXString& lhs, const TXString& rhs)
{
	return (lhs.CompareNoCase(rhs) < 0);
}

//=======================================================================================
// '+' operator
TXString operator+(const TXString& lhs, const TXString& rhs)
{
	return TXString(lhs.stdUStr + rhs.stdUStr);
}

//=======================================================================================
// '+' operator
TXString operator+(const TXString& lhs, TXChar rhs)
{
	if (rhs == 0) return lhs;
	return TXString(lhs.stdUStr + rhs);
}

//=======================================================================================
// '+' operator
TXString operator+(TXChar lhs, const TXString& rhs)
{
	if (lhs == 0) return rhs;
	return TXString(lhs + rhs.stdUStr);
}

//=======================================================================================
// '+' operator
TXString operator+(const TXString& lhs, const TXChar* rhs)
{
	if (rhs == 0) return lhs;
	return TXString(lhs.stdUStr + rhs);
}

//=======================================================================================
// '+' operator
TXString operator+(const TXChar* lhs, const TXString& rhs)
{
	if (lhs == 0) return rhs;
	return TXString(lhs + rhs.stdUStr);
}

//=======================================================================================
TXString& TXString::Format(const TXString& format)
{
	*this = format;
	return *this;
}
//=======================================================================================
// Prepare char buffer based on "encoding" encoding.
void TXString::PrepareCharBuffer(ETXEncoding encoding) const
{
#if GS_WIN

    // Determine copde page.
    UINT codePage = CP_UTF8;

    if (encoding == ETXEncoding::eMacEncoded)
    {
        codePage = CP_MACCP;
    }
    else if (encoding == ETXEncoding::eWinEncoded || encoding == ETXEncoding::eSysEncoded)
    {
        codePage = CP_ACP;
    }

    // Length of the char buffer. Four bytes for each character is enough. 1 for terminal character.
    size_t len = (size_t)stdUStr.length() * 4 + 1;

    if (len > charBufSize)
    {
        charBufSize = len;
        // Delete existing pointer
        if (charPtr) { ::operator delete(charPtr); charPtr = nullptr; }
        // Try to allocate new memprs
        try
        {
            charPtr = (char*)::operator new(charBufSize);
        }
        catch (std::bad_alloc)
        {
            ASSERTN(false, "Allocate new failed (exception)");
            charPtr = nullptr;
        }
    }

    // (CodePage, Flags, WideCharStr, WideCharCount, MultiByteStr, MultiByteCount, DefaultChar, UsedDefaultChar)
    WideCharToMultiByte(codePage, 0, stdUStr.c_str(), -1, charPtr, len, (codePage == CP_UTF8) ? NULL : "?", NULL);
#elif GS_LIN
	size_t len = (size_t)stdUStr.length() * 4 + 1;

	if (len > charBufSize)
	{
		charBufSize = len;
		if (charPtr) delete charPtr;
		charPtr = (char*)::operator new(charBufSize);
	}

	std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
	std::string str = convert.to_bytes(stdUStr);

	size_t strLen = str.size();
	for (size_t i = 0; i < charBufSize && i < strLen; i++)
		charPtr[i] = str[i];
	charPtr[strLen] = 0;
#else 
	
	// Prepare enough memory for all cases
	if(charBufSize < 4 * stdUStr.length() + 1) 
	{
		charBufSize = 4 * (int)stdUStr.length() + 1;	// 1 is reserved for terminal character.
	
		// Delete existing pointer
		if(charPtr)  { ::operator delete(charPtr); charPtr = nullptr; }
		// Try to allocate new memprs
		try
		{
			charPtr = (char*)::operator new(charBufSize);
		}
		catch(std::bad_alloc) 
		{
			ASSERTN(false, "Allocate new failed (exception)");
			charPtr = nullptr;
		}

	}
	// Create a CFString to do the conversion
	CFStringRef cfStr = CFStringCreateWithCharactersNoCopy(kCFAllocatorDefault,
		stdUStr.data(),
		stdUStr.length(),
		kCFAllocatorNull);

	if(cfStr)
	{
		CFStringEncoding cfStrEncoding = kCFStringEncodingUTF8;	// Default for eUTF8 and eUnknown
		
		if(encoding == ETXEncoding::eMacEncoded || encoding == ETXEncoding::eSysEncoded)
		{
			cfStrEncoding = CFStringGetSystemEncoding();
		}
		/* 
		// I have removed this for now MS 11/16/18
		else if(encoding == ETXEncoding::eWinEncoded)
		{
			static const bool bIsFarEast = [[[NSLocale preferredLanguages] objectAtIndex:0] hasPrefix:@"ja"]
										|| [[[NSLocale preferredLanguages] objectAtIndex:0] hasPrefix:@"zh-Hans"];

			if(bIsFarEast)	// Win and Mac encodings are the same in Japanese and Chinese environments.
			{
				cfStrEncoding = CFStringGetSystemEncoding();
			}
			else
			{
				cfStrEncoding = kCFStringEncodingWindowsLatin1;
			}
		}
		*/

		CFIndex usedBufLen = 0;
		
		CFStringGetBytes(cfStr,
						 CFRangeMake(0, CFStringGetLength(cfStr)),
						 cfStrEncoding,
						 '?',
						 false,
						 (UInt8*)charPtr,
						 charBufSize - 1,	// Reserved one byte for terminal character
						 &usedBufLen);
		
		charPtr[usedBufLen] = 0;			// Add terminal character to the end.
		
		CFRelease(cfStr);
	}

#endif

}

//=======================================================================================
// Set stdUStr from 'src' based on "encoding". 'srcLenToUse' does NOT include the
// terminating character.
void TXString::SetStdUStrFromCharBuffer(const char* src, size_t srcLenToUse, ETXEncoding encoding)
{
	if (srcLenToUse == 0 || src == nullptr || *src == '\0') {
		stdUStr.clear();
		return;
	}

	// Determine the source length to use.
	size_t strLen = 0;
	while (strLen < srcLenToUse && src[strLen] != 0) ++strLen;

#if GS_WIN
    if (encoding == ETXEncoding::eUTF8)	// UTF-8
    {
        std::unique_ptr<TXChar[]> txChars(new TXChar[strLen + 1]);	// The buffer is big enough.
        utf8BufferToTXCharBuffer(src, txChars.get(), strLen);
        stdUStr = txChars.get();
    }
    else
    {
        UINT codePage = CP_ACP;			// Windows ANSI encoding.

        if (encoding == ETXEncoding::eMacEncoded)
        {
            codePage = CP_MACCP;		// Mac encoding.
        }

        std::unique_ptr<TXChar[]> txChars(new TXChar[strLen + 1]);	// The buffer is big enough.
        int newLen = MultiByteToWideChar(codePage, MB_PRECOMPOSED, src, (int)strLen, txChars.get(), int(strLen + 1));
        txChars.get()[newLen] = 0;		// Add 0 to the end.
        stdUStr = txChars.get();
    }
#elif GS_LIN
	// LINUX_IMPLEMENTATION - done
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
	std::string strSrc = std::string(src, strLen);
	stdUStr = converter.from_bytes(strSrc);
#else	// Mac
	if(encoding == ETXEncoding::eUTF8)
	{
		std::unique_ptr<TXChar[]> txChars(new TXChar[strLen + 1]);
		utf8BufferToTXCharBuffer(src, txChars.get(), strLen);
		stdUStr = txChars.get();
	}
	else
	{
		CFStringEncoding selectedEncoding = CFStringGetSystemEncoding();

		if(encoding == ETXEncoding::eWinEncoded)
		{
			selectedEncoding = kCFStringEncodingWindowsLatin1;
		}

		CFStringRef cfStr = CFStringCreateWithBytes(kCFAllocatorDefault,
			(const UInt8*)src,
			strLen,
			selectedEncoding,
			false);

		if (cfStr)
		{
			CFIndex cfStrLen = CFStringGetLength(cfStr);
			CFRange cfStrRange = CFRangeMake(0, cfStrLen);

			std::unique_ptr<UniChar[]> uniChars(new UniChar[cfStrLen + 1]);
			CFStringGetCharacters(cfStr, cfStrRange, uniChars.get());
			uniChars[cfStrLen] = '\0';
			stdUStr = uniChars.get();
			CFRelease(cfStr);
		}
		else
		{
			//DSTOP((kPChang, "Error in TXString::SetStdUStrFromCharBuffer(...)"));
		}
	}

#endif
}

void TXString::swap(TXString& other)
{
	std::swap(stdUStr, other.stdUStr);
	std::swap(charPtr, other.charPtr);
	std::swap(charBufSize, other.charBufSize);
}

void swap(TXString& lhs, TXString& rhs)
{
	lhs.swap(rhs);
}

//=======================================================================================
// http://unicode.org/faq/utf_bom.html#utf16-3

static const UCChar LEAD_OFFSET = 0xD800 - (0x10000 >> 10);

// UTF-32 to UTF-16 conversion. 'output' should be TXChar[3].
inline void utf32ToTXCharBuffer(char32_t input, TXChar* output)
{
	if (input <= 0xFFFFUL)
	{
		*output++ = (TXChar)input;
	}
	else if (input <= 0x10FFFFUL)
	{
		*output++ = LEAD_OFFSET + (TXChar)(input >> 10);
		*output++ = 0xDC00 + (input & 0x3FF);
	}
	else
	{
		*output++ = '?';
		//DSTOP((kPChang, "Invalid wchar_t value"));
	}

	*output = 0;	// Terminal character.
}

//=======================================================================================
// char32_t* to TXChar*. 'output' needs one extra element to store terminating character.
void utf32BufferToTXCharBuffer(const char32_t* input, TXChar* output, size_t numInputChars)
{
	for (size_t i = 0; i < numInputChars && input[i] != 0; ++i) {
		if (input[i] <= 0xFFFFUL)
		{
			*output++ = (TXChar)input[i];
		}
		else if (input[i] <= 0x10ffffUL)
		{
			*output++ = LEAD_OFFSET + (TXChar)(input[i] >> 10);
			*output++ = 0xDC00 + (input[i] & 0x3FF);
		}
		else
		{
			*output++ = '?';
			//DSTOP((kPChang, "Invalid wchar_t value"));
		}
	}

	*output = 0;	// Terminal
}

//=======================================================================================
// TXChar* to char32_t*
static const char32_t SURROGATE_OFFSET = 0x10000 - (0xD800 << 10) - 0xDC00;

inline void txCharBufferToUtf32Buffer(const TXChar* input, char32_t* output, size_t bufElemNum /* -1 */)
{
	size_t outputIndex = 0;
	size_t len = bufElemNum - 1;

	while (outputIndex < len && *input != 0) {
		const UCChar uc = *input++;

		if (uc < 0xD800 || uc > 0xDFFF)
		{
			// One UTF-16 code unit for one UTF-32 code unit
			*output++ = uc;
			++outputIndex;
		}
		else
		{
			// Two UTF-16 code units for one UTF-32 code unit
			if (uc < 0xdc00 && (*input) >= 0xdc00 && (*input) <= 0xdfff)
			{
				*output++ = (uc << 10) + (*input++) + SURROGATE_OFFSET;
			}
			else
			{
				*output++ = '?';
				//DSTOP((kPChang, "Failed to convert UCChar buffer to wchar_t buffer"));
			}

			++outputIndex;
		}
	}

	*output = 0;
}

//=======================================================================================
// UTF-8 buffer to TXChar buffer. 'inputLen' is the number of characters. 'output'
// buffer should have size with one more character for the terminal character.
inline void utf8BufferToTXCharBuffer(const char* const input, TXChar* output, size_t inputLen)
{
	TXChar u[3];
	char32_t w;
	size_t inputIndex = 0;

	while (inputIndex < inputLen)
	{
		if ((*(input + inputIndex) & 0x80) == 0)	// 1 byte
		{
			if (inputIndex >= inputLen) break;
			*output++ = *(input + inputIndex);
			inputIndex++;
		}
		else if ((*(input + inputIndex) & 0xE0) == 0xC0)	// 2 bytes
		{
			if ((inputIndex + 1) >= inputLen) break;
			w = ((*(input + inputIndex) & 0x1F) << 6)
				+ (*(input + inputIndex + 1) & 0x3F);
			utf32ToTXCharBuffer(w, u);
			*output++ = u[0];
			if (u[1]) *output++ = u[1];
			inputIndex += 2;
		}
		else if ((*(input + inputIndex) & 0xF0) == 0xE0)	// 3 bytes
		{
			if ((inputIndex + 2) >= inputLen) break;
			w = ((*(input + inputIndex) & 0x0F) << 12)
				+ ((*(input + inputIndex + 1) & 0x3F) << 6)
				+ (*(input + inputIndex + 2) & 0x3F);
			utf32ToTXCharBuffer(w, u);
			*output++ = u[0];
			if (u[1]) *output++ = u[1];
			inputIndex += 3;
		}
		else if ((*(input + inputIndex) & 0xF8) == 0xF0)	// 4 bytes
		{
			if ((inputIndex + 3) >= inputLen) break;
			w = ((*(input + inputIndex) & 0x07) << 18)
				+ ((*(input + inputIndex + 1) & 0x3F) << 12)
				+ ((*(input + inputIndex + 2) & 0x3F) << 6)
				+ (*(input + inputIndex + 3) & 0x3F);
			utf32ToTXCharBuffer(w, u);
			*output++ = u[0];
			if (u[1]) *output++ = u[1];
			inputIndex += 4;
		}
		else	// Invalid byte.
		{
			*output++ = '?';
			inputIndex++;
			//DSTOP((kPChang, "Failed to convert UF-8 char buffer to TXChar buffer"));
		}
	}

	while (inputIndex++ < inputLen)
	{
		*output++ = '?';
	}

	*output = 0;
}

}

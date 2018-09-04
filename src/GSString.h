//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#ifndef _GSSTRING_
#define _GSSTRING_

#pragma once

#include <stdarg.h>
#include <algorithm>

#include "GSDebug.h"
#include "GSIntTypes.h"

#if _MINICAD_
	#define GS_STRING_API	GS_COMP_API
#else
	#define GS_STRING_API	GS_API
#endif

class TXString;

enum ECharacterType {
    eSingle,
    eLead,
    eTrail,
    eIllegal
};

/* Constants */
/* --------- */
/* For comparison and search routines */
const bool	kDoIgnoreCase   = true;
const bool	kDontIgnoreCase = false;
const bool	kFindFwd = true;
const bool	kFindRev = false;


/* Types */
/* ----- */
/* Character encoding standard--uses platform-specific values */
typedef Uint32			GSTextEncoding;


void NNAUppercaseText(char* textPtr, Sint32 len, int scriptCode);
void NNANumToString(Sint32 num, unsigned char* str, size_t strSize);
void NNANumToString(Sint32 num, TXString& str);
void NNAStringToNum(const unsigned char * theString, Sint32 *theNum);


/**************************************************/
/* Unicode Character String Manipulation Routines */
/**************************************************/

/* Unicode Encoding Converter Routines */
size_t	StringToUnicodeMaxChars (size_t srcLen);
bool	StringToUnicode (GSTextEncoding srcEncoding, const char* srcArray,
			 size_t srcLen, UCCharPtr dstUCArray, size_t maxDstChars,
			 size_t* pDstLen);
bool	StringToUnicode (GSTextEncoding srcEncoding, const char* srcStr,
             UCStrPtr dstUCStr, size_t maxDstChars, size_t* pDstLen);
bool	StringToUnicode (GSTextEncoding srcEncoding, ConstGSStr255Param srcStr,
             UCStrPtr dstUCStr, size_t maxDstChars, size_t* pDstLen);
size_t	UnicodeToStringMaxChars (size_t srcLen);
bool	UnicodeToString (GSTextEncoding dstEncoding,
			ConstUCCharPtr srcUCArray, size_t srcLen,
			char* dstArray, size_t maxDstBytes, size_t* pDstLen);
bool	UnicodeToString (GSTextEncoding dstEncoding, ConstUCStrPtr srcUCStr,
			char* dstStr, size_t maxDstBytes, size_t* pDstLen);
bool	UnicodeToString (GSTextEncoding dstEncoding, ConstUCStrPtr srcUCStr,
			GSStringPtr dstStr, size_t maxDstBytes, size_t* pDstLen);

/* Unicode String Manipulation Routines */
size_t	StringLength (ConstUCStrPtr ucString);
bool		StringEqual (ConstUCStrPtr str1, ConstUCStrPtr str2, bool ignoreCase);
bool		StringEqual (ConstUCCharPtr chars1, size_t len1,
			              ConstUCCharPtr chars2, size_t len2, bool ignoreCase);
void		StringCopy (ConstUCStrPtr srcStr, UCStrPtr dstStr, size_t maxDstBytes);
void		StringCopy (ConstUCStrPtr srcStr, wchar_t * dstStr, size_t maxDstBytes);
bool		FindCharClusterBreak (ConstUCCharPtr charArray, size_t length,
		             size_t startPos, bool forward, size_t* pBreakPos);

// Trims invalid multi byte characters at the end of a string
void	TrimInvalidCharsFromMultiByteEncodedCString(char*          buffer, size_t bufferSize);	// For C string
void	TrimInvalidCharsFromMultiByteEncodedPString(unsigned char* buffer, size_t bufferSize);	// For Pascal string

// Creates an array that identifies each type of char in a mac encoded string
// Only used for translation of strings during reverse translation, and a few other special cases.
// Do not use this without talking to Payne or Ian first.
void	GetFarEastCharacterTypeArray(const char *pStr, ECharacterType *pCharByteType, size_t strLength);

// Determines if the current system locale is running in a multi byte language.  This should only be used during translation
Boolean IsMultiByteLanguage( );



/*============================================================================*/
/*============================================================================*/
/***********************************************************************/
/* Non-Unicode Pascal and C String Manuipulation Routines and Classes */
/***********************************************************************/


////////////////////////////////////////////////////////////////////////////////
// OS-Specific Character Encoding Routines

enum EStringExpansion {
	eAllowStringExpansion,
	eDontAllowStringExpansion
};

#if GS_WIN
extern Boolean	gl_MapUpperChars;	// Where is this defined?
#endif // GS_WIN

// System Encoding Retrieval Routines
GSTextEncoding	GetSystemEncoding ();


////////////////////////////////////////////////////////////////////////////////
#if __cplusplus

/*
	For complete documentation on the things in this section, see the
	Graphsoft String Library document.
	
	Most of the routines here are overloaded to accept any mix of Pascal-
	style (unsigned char *) and C-style (char *) strings.  In any function
	that takes a string size (i.e. StringCopy and StringCat), the size is
	the total number of bytes occupied by the string, which is one greater
	than the maximum character length.  We do this so you can pass sizeof(T)
	as the length.  For example, to copy a string into a GSStr255, you would
	say "StringCopy(someString, aStr255, sizeof(GSStr255))".
	
	All of the functions can accept "unusual" input values, i.e. null pointers
	and negative lengths.  An input of a null pointer or non-positive string
	length is interpreted like an empty string, if given as an output, nothing
	will be written to it.
*/


////////////////////////////////////////
// Length tests: GetLength (formerly length), IsEmpty.

//   NOTE: IsEmpty(s) is faster than GetLength(s) == 0, particularly for C-style strings.
inline Uint8	GetLength(ConstGSStr255Param s)		{ return s ? s[0] : 0; }
inline size_t	GetLength(const char *s)			{ return s ? strlen(s) : 0; }
inline Bool8	IsEmpty(ConstGSStr255Param s)		{ return !s || s[0] == 0; }
inline Bool8	IsEmpty(const char *s)				{ return !s || s[0] == '\0'; }


////////////////////////////////////////
// SetLength

inline void SetLength(GSStringPtr s, Uint8 len)	{ if (s) s[0] = len; }
inline void SetLength(char *s, size_t len)		{ if (s) s[len] = '\0'; }


////////////////////////////////////////
// StringCopy

// These functions all return void now to get around a bug in the Visual C++ 4.1 & 4.2 linker. [DMB 12/4/96]
void GS_STRING_API StringCopy(ConstGSStr255Param src, GSStringPtr dst, size_t sizeofDst);
void GS_STRING_API StringCopy(const char *src, GSStringPtr dst, size_t sizeofDst);
void GS_STRING_API StringCopy(const void *src, size_t len, GSStringPtr dst, size_t sizeofDst);
void GS_STRING_API StringCopy(ConstGSStr255Param src, char *dst, size_t sizeofDst);
void GS_STRING_API StringCopy(const char *src, char *dst, size_t sizeofDst);
void GS_STRING_API StringCopy(const void *src, size_t len, char *dst, size_t sizeofDst);


////////////////////////////////////////
// StringCat

GSStringPtr GS_STRING_API StringCat(GSStringPtr dst, ConstGSStr255Param src, size_t sizeofDst);
GSStringPtr GS_STRING_API StringCat(GSStringPtr dst, const char *src, size_t sizeofDst);
GSStringPtr GS_STRING_API StringCat(GSStringPtr dst, const void *src, size_t len, size_t sizeofDst);
char GS_STRING_API * StringCat(char *dst, ConstGSStr255Param src, size_t sizeofDst);
char GS_STRING_API * StringCat(char *dst, const char *src, size_t sizeofDst);
char GS_STRING_API * StringCat(char *dst, const void *src, size_t len, size_t sizeofDst);

//======================================
// String equality
Bool8 GS_STRING_API StringEqual(const TXString& a, const TXString& b);				// Case sensitive
Bool8 GS_STRING_API	StringEqualIgnoringCase(const TXString& a, const TXString& b);	// Case insensitive

//======================================
// String comparison
short GS_STRING_API StringCompare(const TXString& a, const TXString& b);				// Case sensitive
short GS_STRING_API StringCompareIgnoringCase(const TXString& a, const TXString& b);	// Case insensitive


////////////////////////////////////////
// StringInsert

void GS_STRING_API StringInsert(ConstGSStr255Param src, GSStringPtr dst, Uint8 index);


////////////////////////////////////////
// StringDelete

void GS_STRING_API StringDelete(GSStringPtr s, Uint8 start, Uint8 count);
void GS_STRING_API StringDelete(char *s, size_t start, size_t count);


////////////////////////////////////////
// StringPos

#ifdef _MINICAD_
short GS_STRING_API StringPos (ConstGSStr255Param findStr, ConstGSStr255Param str);
#endif



//=======================================================================================
// SortStringsUsingOS
//
// To use, implement GetStringForSorting(const Type &obj) for your Type

template<class Type>
const TXString& GetStringForSorting(const Type &obj);

short GS_STRING_API OSStringCompare(const TXString& string1, const TXString& string2, bool convertWinDash = false);

template<class Type>
class OSComparator
{
public:
	bool operator()(const Type& s1, const Type& s2)
	{
		return OSStringCompare(GetStringForSorting(s1), GetStringForSorting(s2)) < 0;
	}
};

template<typename IteratorType>
inline void SortStringsUsingOS(IteratorType begin, IteratorType end)
{
	std::sort(begin, end, OSComparator<typename IteratorType::value_type>());
}


//=======================================================================================
// Truncate (formerly trunc)

inline void Truncate(GSStringPtr s, Uint8 len)		{ if (s && GetLength(s) > len) SetLength(s, len); }
inline void Truncate(char *s, size_t len)		{ if (s) s[len] = '\0'; }


////////////////////////////////////////
// str*cmp

#if !_WINDOWS
Sint32 stricmp(const char *a, const char *b);
Sint32 strnicmp(const char *a, const char *b, size_t max);
#endif // !_WINDOWS


////////////////////////////////////////
/* USAGE FOR NULLSTR, DUMMYSTR, _ccp, _cucp:

	Since IBM PC compilers don't generally know about the \p convention for strings,
	you should avoid the use of string literals in your code.  If you need an empty
	string, use NULLSTR.  If you need an innocuous but non-empty string, use DUMMYSTR.
	(This case usually turns up with AppendMenu, which treats certain characters
	specially.  DUMMYSTR is not guaranteed to be anything in particular, but is
	guaranteed to not make AppendMenu do something strange.)
	
	If you need your own string literal, define it like this: _cucp "\011my string".
	You must encode the length byte explicitly, since the IBM PC compilers can't handle
	\p; the _cucp (shorthand for "const unsigned char pointer"), casts the string
	to the standard type for Pascal-style string literals; const unsigned char *.
	_ccp (const char *) casts to a standard C-style string

	_ccp  == (ConstGSCStrPtr)
	_cucp == (ConstGSStringPtr)
*/
#define _ccp		   (const char *)
#define _cucp	       (const unsigned char *)
#if GS_MAC
	#define NULLSTR   ((const unsigned char *) "\p")
	#define DUMMYSTR  ((const unsigned char *) "\px")
#else
	#define NULLSTR   ((const unsigned char *) "\0")
	#define DUMMYSTR  ((const unsigned char *) "\001x")
#endif



////////////////////////////////////////////////////////////////////////////////
// - PStr<>

template <size_t maxCharLen>
class PStr {
#if GS_WIN
	friend class PStr<maxCharLen>;  // Updated for CW Pro 6
#endif
	
	private:
		Uint8 buf[maxCharLen+1 + ((maxCharLen+1)%2)];
	
	public:
		/* - Constructors
		*/
		PStr()											{ buf[0] = 0; }
		PStr(const PStr &s)								{ StringCopy(s.buf, buf, maxCharLen+1); }
		PStr(ConstGSStringPtr s)						{ StringCopy(s, buf, maxCharLen+1); }
		PStr(const char *s)								{ StringCopy(s, buf, maxCharLen+1); }
		PStr(const void *s, size_t size)				{ StringCopy(s, size, buf, maxCharLen+1); }
		PStr(const TXString& s);
		

		template <size_t maxCharLen2>
		PStr(const PStr<maxCharLen2>& s) { StringCopy(s, buf, maxCharLen+1);  }

		
		/* - Assignment operators
		*/
		PStr& operator=(ConstGSStringPtr s)				{ StringCopy(s, buf, maxCharLen+1); return *this; }
		PStr& operator=(const char *s)					{ StringCopy(s, buf, maxCharLen+1); return *this; }

		template <size_t maxCharLen2>
		PStr& operator=(const PStr<maxCharLen2>& s){
			StringCopy(s, buf, maxCharLen+1); 
			return *this; 
		}
		
		PStr& operator=(const TXString& s);

		void CopyToStr(unsigned char* s) const 			{ StringCopy(buf, s, maxCharLen+1); }

		/* - Casts
		*/
		operator GSStringPtr() 							{ return buf; }
//		operator ConstGSStr255Param() const				{ return buf; }
		operator ConstGSStringPtr() const				{ return buf; }

		/* - String length
		*/
		Uint8 GetLength() const							{ return buf[0]; }
		static Uint8 GetMaxLength()						{ return (Uint8) maxCharLen; }
		static Uint8 MaxLength()						{ return (Uint8) maxCharLen; }
		void SetLength(Uint8 len)						{ buf[0] = len; }
		void Truncate(Uint8 len)						{ if (GetLength() > len) SetLength(len); }
		Bool8 IsEmpty() const							{ return GetLength() == 0; }
		void Clear()									{ buf[0] = 0; }
		
		/* - Subscript operators
		*/
		#if 0
		// Both Mac and Win compilers find these operators ambiguous when
		// you say aString[i], due to being able to implicitly cast to char*.
		unsigned char& operator[](Uint8 i)				{ return buf[i]; }
		unsigned char operator[](Uint8 i) const			{ return buf[i]; }
		#endif
		
		/* - Comparison operators
		*/
		Bool8 operator==(ConstGSStringPtr s) const 		{ return StringEqualIgnoringCase(buf, s); }
		// TODO template <size_t maxCharLen>
		Bool8 operator==(const PStr<maxCharLen>& s) const 	{ return StringEqualIgnoringCase(buf, s); }

		Bool8 operator!=(const PStr &s)					{ return !StringEqualIgnoringCase(buf, s); }
		Bool8 operator!=(ConstGSStringPtr s)	 		{ return !StringEqualIgnoringCase(buf, s); }
		Bool8 operator!=(ConstGSStringPtr s) const 		{ return !StringEqualIgnoringCase(buf, s); }
		Bool8 operator==(const char * const s) const	{ return StringEqualIgnoringCase(buf, s); }
		Bool8 operator!=(const char * s) const			{ return !StringEqualIgnoringCase(buf, s); }
		Bool8 operator!=(const char * s)				{ return !StringEqualIgnoringCase(buf, s); }

		Bool8 operator==(char c) const					{ return GetLength() == 1 && ((const char *) buf)[1] == c; }
		Bool8 operator!=(char c) const					{ return GetLength() != 1 || ((const char *) buf)[1] != c; }
		Bool8 operator<(ConstGSStringPtr s) const		{ return StringCompare(buf, s) < 0; }
		Bool8 operator<(const char *s) const			{ return StringCompare(buf, s) < 0; }
		
		template<size_t maxCharLen2>
		Bool8 operator==(const PStr<maxCharLen2> &s) const			{ return StringEqualIgnoringCase(buf, s); }
		
		/* - Append operators
		*/
		PStr& operator<<(ConstGSStr255Param s)			{ StringCat(buf, s, maxCharLen+1); return *this; }
		PStr& operator<<(const char *s)					{ StringCat(buf, s, maxCharLen+1); return *this; }
		PStr& operator<<(Sint32 n);
        PStr& operator<<(Sint64 n);
		PStr& operator<<(short n)						{ return (*this << (Sint32) n); } 
		PStr& operator<<(char c)						{ if (buf[0] < maxCharLen) buf[++buf[0]] = c; return *this; }
		PStr& operator<<(unsigned char c)				{ if (buf[0] < maxCharLen) buf[++buf[0]] = c; return *this; }

		template <size_t maxCharLen2>
		PStr& operator<<(const PStr<maxCharLen2>& s)	{ return *this << (ConstGSStr255Param) s; }

		//PStr& operator<<(float_param f);				// NOT IMPLEMENTED!
		//PStr& operator<<(double_param d);				// NOT IMPLEMENTED!
		
		/* - Searching
		*/
		Sint32 Find(char ch) const							{ return Find(1, ch); }
		Sint32 Find(Uint8 start, char ch) const;
		Sint32 ReverseFind(char ch) const					{ return ReverseFind(GetLength(), ch); }
		Sint32 ReverseFind(Uint8 start, char ch) const;
		
		/* - Substrings
		*/
		PStr Left(Uint8 count) const						{ Uint8 len = GetLength(); if (count > len) count = len; return PStr<maxCharLen>(&buf[1], count); }
		PStr Right(Uint8 count) const					{ Uint8 len = GetLength(); if (count > len) count = len; return PStr<maxCharLen>(&buf[len - count + 1], count); }
		PStr Mid(Uint8 start, Uint8 count = 255) const;
		
		/* - Formatted output
		*/
		Uint8 Format(ConstGSStr255Param format, ...);
		Uint8 Format(const char *format, ...);
};


template <size_t maxCharLen>
PStr<maxCharLen>& PStr<maxCharLen>::operator<<(Sint32 n)
{
	PStr<15> s;
	s.Format("%ld", n);
	StringCat(buf, s, maxCharLen+1);
	return *this; 
}

template <size_t maxCharLen>
PStr<maxCharLen>& PStr<maxCharLen>::operator<<(Sint64 n)
{
	PStr<32> s;
	s.Format(PRId64, n);
	StringCat(buf, s, maxCharLen+1);
	return *this;
}

template <size_t maxCharLen>
Sint32 PStr<maxCharLen>::Find(Uint8 start, char ch) const
{
	if (start > 0)
		for (Uint8 i = start; i <= GetLength(); ++i)
			if (buf[i] == ch) return i;
	return 0;
}

template <size_t maxCharLen>
Sint32 PStr<maxCharLen>::ReverseFind(Uint8 start, char ch) const
{
	if (start > GetLength())
		start = GetLength();
	for (Uint8 i = start; i > 0; --i)
		if (buf[i] == ch) return i;
	return 0;
}

template <size_t maxCharLen>
PStr<maxCharLen> PStr<maxCharLen>::Mid(Uint8 start, Uint8 count) const
{
	if (start > GetLength())
		count = 0;
	else if (start + count - 1 > GetLength())
		count = GetLength() - start + 1;
	
	return PStr<maxCharLen>(&buf[start], count);
}

template <size_t maxCharLen>
Uint8 PStr<maxCharLen>::Format(ConstGSStr255Param format, ...)
{
	va_list ap;
	va_start(ap, format);

	char szFormat[256];
	StringCopy(format, szFormat, 256);

	this->buf[0] = vsprintf((char*) &this->buf[1], szFormat, ap);

	va_end(ap);
	return this->buf[0];
}

template <size_t maxCharLen>
Uint8 PStr<maxCharLen>::Format(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);

	this->buf[0] = vsprintf((char*) &this->buf[1], format, ap);

	va_end(ap);
	return this->buf[0];
}



////////////////////////////////////////////////////////////////////////////////
// - CStr<>

template <size_t maxCharLen>
class CStr : public TDebugObject {
	private:
		char buf[maxCharLen+1 + ((maxCharLen+1)%2)];
	
	public:
		/* - Constructors
		*/
		CStr()											{ buf[0] = 0; }
		CStr(const CStr &s)								{ StringCopy(s.buf, buf, maxCharLen+1); }
		CStr(ConstGSStr255Param s)						{ StringCopy(s, buf, maxCharLen+1); }
		CStr(const char *s)								{ StringCopy(s, buf, maxCharLen+1); }
		CStr(const void *s, size_t size)				{ StringCopy(s, size, buf, maxCharLen+1); }
		// TODO template <size_t maxCharLen>
		CStr(const PStr<maxCharLen>& s)					{ StringCopy(s, buf, maxCharLen+1); }
		
		/* - Assignment operators
		*/
		CStr& operator=(const CStr& s)					{ StringCopy(s.buf, buf, maxCharLen+1); return *this; }
		CStr& operator=(ConstGSStr255Param s)			{ StringCopy(s, buf, maxCharLen+1); return *this; }
		CStr& operator=(const char *s)					{ StringCopy(s, buf, maxCharLen+1); return *this; }
		
		// TODO template <size_t maxCharLen>
		CStr& operator=(const PStr<maxCharLen>& s)		{ StringCopy(s, buf, maxCharLen+1); return *this; }
		
		/* - Casts
		*/
		operator char *()								{ return buf; }
		operator const char *() const					{ return buf; }

		/* - String length
		*/
		size_t GetLength() const						{ return strlen(buf); }
		static size_t GetMaxLength()					{ return maxCharLen; }
		void SetLength(size_t len)						{ if (VERIFYN(kChris, len <= maxCharLen)) buf[len] = '\0'; }
		void Truncate(size_t len)						{ if (len <= maxCharLen) buf[len] = '\0'; }
		Bool8 IsEmpty() const							{ return buf[0] == '\0'; }
		void Clear()									{ buf[0] = '\0'; }
		
		/* - Subscript operators
		*/
		#if 0
		// Both Mac and Win compilers find these operators ambiguous when
		// you say aString[i], due to being able to implicitly cast to char*.
		char& operator[](size_t i)						{ return buf[i]; }
		char operator[](size_t i) const					{ return buf[i]; }
		#endif
		
		/* - Comparison operators
		*/
		Bool8 operator==(ConstGSStr255Param s) const 	{ return StringEqualIgnoringCase(buf, s); }
		Bool8 operator!=(ConstGSStr255Param s) const 	{ return !StringEqualIgnoringCase(buf, s); }
		Bool8 operator==(const char *s) const			{ return StringEqualIgnoringCase(buf, s); }
		Bool8 operator!=(const char *s) const			{ return !StringEqualIgnoringCase(buf, s); }
		Bool8 operator==(char c) const					{ return buf[0] == c && buf[1] == '\0'; }
		Bool8 operator!=(char c) const					{ return buf[0] != c || buf[1] != '\0'; }
		Bool8 operator<(ConstGSStr255Param s) const		{ return StringCompare(buf, s) < 0; }
		Bool8 operator<(const char *s) const			{ return StringCompare(buf, s) < 0; }
		Bool8 operator==(const CStr &s) const			{ return s == buf; }
		
		/* - Append operators
		*/
		CStr& operator<<(ConstGSStr255Param s)			{ StringCat(buf, s, maxCharLen+1); return *this; }
		CStr& operator<<(const char *s)					{ StringCat(buf, s, maxCharLen+1); return *this; }
		CStr& operator<<(Sint32 n);						
		CStr& operator<<(short n)						{ return (*this << (Sint32) n); }
		CStr& operator<<(char c)						{ size_t pos = strlen(buf); if (pos < maxCharLen) { buf[pos] = c; buf[pos+1] = '\0'; } return *this; }
		CStr& operator<<(unsigned char c)				{ size_t pos = strlen(buf); if (pos < maxCharLen) { buf[pos] = c; buf[pos+1] = '\0'; } return *this; }
		//CStr& operator<<(float_param f);				// NOT IMPLEMENTED!
		//CStr& operator<<(double_param d);				// NOT IMPLEMENTED!
		
		/* - Searching
		*/
		Sint32 Find(char ch) const							{ return Find(0, ch); }
		Sint32 Find(size_t start, char ch) const;
		Sint32 ReverseFind(char ch) const					{ return ReverseFind(GetLength() - 1, ch); }
		Sint32 ReverseFind(size_t start, char ch) const;
		
		/* - Substrings
		*/
		CStr Left(size_t count) const					{ size_t len = GetLength(); if (count > len) count = len; return CStr<maxCharLen>(&buf[0], count); }
		CStr Right(size_t count) const					{ size_t len = GetLength(); if (count > len) count = len; return CStr<maxCharLen>(&buf[len - count], count); }
		CStr Mid(size_t start, size_t count = 1024) const;
		
		/* - Formatted output
		*/
		Sint32 Format(ConstGSStr255Param format, ...);
		Sint32 Format(const char *format, ...);

		/* - Debugging
		*/
		DECLARE_CLASS_DEBUGGING
};

template <size_t maxCharLen>
CStr<maxCharLen>& CStr<maxCharLen>::operator<<(Sint32 n)
{ 
	#if _WINDOWS
	
		char sz[12];
		_itoa(n, sz, 10);
	
		StringCat(buf, sz, maxCharLen+1);
		return *this;

	#elif _LINUX

		char s[16];
        NNANumToString(n, (GSStringPtr) s, 16);
        StringCat(buf, s, maxCharLen+1);
		return *this;

	#else
	
        Str15 s;
        NNANumToString(n, (GSStringPtr) s, 16);
        StringCat(buf, s, maxCharLen+1);
		return *this; 
	#endif
}

template <size_t maxCharLen>
Sint32 CStr<maxCharLen>::Find(size_t start, char ch) const
{
	size_t i; const char *p;
	
	for (i = start, p = &buf[i]; i <= maxCharLen && *p != '\0'; i++, p++)
		if (*p == ch) return (Sint32) i; 
	return -1;
}

template <size_t maxCharLen>
Sint32 CStr<maxCharLen>::ReverseFind(size_t start, char ch) const
{
	Sint32 i; const char *p;
	
	for (i = (Sint32) start, p = &buf[i]; i >= 0 && *p != '\0'; i--, p--) 
		if (*p == ch) return i;
	return -1;
}

template <size_t maxCharLen>
CStr<maxCharLen> CStr<maxCharLen>::Mid(size_t start, size_t count) const
{
	if (start > GetLength())
		count = 0;
	else if (start + count - 1 > GetLength())
		count = GetLength() - start + 1;
	
	return CStr<maxCharLen>(&buf[start], count);
}

template <size_t maxCharLen>
Sint32 CStr<maxCharLen>::Format(ConstGSStr255Param format, ...)
{
	Sint32 result;
	va_list ap;
	va_start(ap, format);

	char szFormat[256];
	StringCopy(format, szFormat, 256);

	result = vsprintf(this->buf, szFormat, ap);

	va_end(ap);
	return result;
}

template <size_t maxCharLen>
Sint32 CStr<maxCharLen>::Format(const char *format, ...)
{
	Sint32 result;
	va_list ap;
	va_start(ap, format);

	result = vsprintf(this->buf, format, ap);

	va_end(ap);
	return result;
}


////////////////////////////////////////////////////////////////////////////////

#define STRINGTYPE_INTERFACE(maxCharLen) typedef PStr<maxCharLen> PStr##maxCharLen


//typedef PStr<255>	PStr255;    // Unicode_Revisit_RemoveAfterPStr255ToTXStringConversionComplete

//typedef PStr<63>	PStr63;     // Unicode_Revisit_RemoveAfterPStr63ToTXStringConversionComplete
//typedef PStr<31>	PStr31;     // Unicode_Revisit_RemoveAfterPStr31ToTXStringConversionComplete
//typedef PStr<20>	PStr20;     // Unicode_Revisit_RemoveAfterPStr20ToTXStringConversionComplete
//typedef PStr<15>	PStr15;     // Unicode_Revisit_RemoveAfterPStr15ToTXStringConversionComplete
//typedef PStr<8>	PStr8;      // Unicode_Revisit_RemoveAfterPStr8ToTXStringConversionComplete
//typedef PStr<7>	PStr7;      // Unicode_Revisit_RemoveAfterPStr7ToTXStringConversionComplete

typedef PStr<63>	PStr63Verified;     // Unicode_Revisit_RemoveAfterPStr63ToTXStringConversionComplete
typedef PStr<31>	PStr31Verified;     // Unicode_Revisit_RemoveAfterPStr31ToTXStringConversionComplete
typedef PStr<20>	PStr20Verified;     // Unicode_Revisit_RemoveAfterPStr20ToTXStringConversionComplete
typedef PStr<15>	PStr15Verified;     // Unicode_Revisit_RemoveAfterPStr15ToTXStringConversionComplete
typedef PStr<8>		PStr8Verified;      // Unicode_Revisit_RemoveAfterPStr8ToTXStringConversionComplete
typedef PStr<7>		PStr7Verified;      // Unicode_Revisit_RemoveAfterPStr7ToTXStringConversionComplete

typedef PStr<255>	PStr255Verified;    
//typedef PStr255Verified		PString;    // Unicode_Revisit_RemoveAfterPStringToTXStringConversionComplete

typedef PStr255Verified		PStringVerified; // Unicode_Revisit_RemoveAfterPStringToTXStringConversionComplete

typedef CStr<512>	CStr512;
typedef CStr<256>	CStr256;
typedef CStr<255>	CStr255;
typedef CStr<63>	CStr63;
typedef CStr<31>	CStr31;
typedef CStr<27>	CStr27;
typedef CStr<20>	CStr20;
typedef CStr<15>	CStr15;
typedef CStr<8>		CStr8;
typedef CStr<7>		CStr7;


#endif  // __cplusplus

/*============================================================================*/
/*============================================================================*/

// This function is left unimplemented in the SDK as all plugins should implement it individially.
// If they dont, there will be a linker error of undefined external symbol
// The purpose of the function is to provide the VWR file name for each plugin when using TXResStr, TXResource, and TXLegacyResource APIs.
// All string related functions in the SDK use this function to get the base for resource files
const char* DefaultPluginVWRIdentifier();

#endif  // _GSSTRING_

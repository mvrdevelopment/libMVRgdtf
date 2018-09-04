//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
//	TXString class
//


#ifndef _GSSTRINGX_
#define _GSSTRINGX_

#pragma once

#if !_MINICAD_
// ASSERTTHISCLASS is not available in the external SDK
# ifndef ASSERTTHISCLASS
#  define ASSERTTHISCLASS(toWhom)
# endif
#endif


// For Unicode string literal
#if GS_WIN
#include <Windows.h>
#define txu(string) L##string
#define txuc(string) L##string
#elif GS_LIN
#define txu(string) L##string
#define txuc(string) L##string
#else
#include <CoreFoundation/CoreFoundation.h>
#define txu(string) (const UCChar*)u##string
#define txuc(ch) (const UCChar)u##ch
#endif


#include "GSString.h"

#include <string>
#include <vector>
#include <memory>
#include <sstream>

#define NNA_WARN_ABOUT_EMPTY_STRING_RESOURCES 1

extern VWMM::Partition* gVWMM;

//---------------------------------------------------------------------------------------
// EEmptyStringResourceHandling - how do we deal with warning about empty string resources.
//
enum EEmptyStringResourceHandling {
	eDontWarnAboutEmptyStringResult = 1,
	eWarnAboutEmptyStringResult = 2
};


enum EEmptyHandling {
	eAllowEmptyResult = eDontWarnAboutEmptyStringResult,
	eDontAllowEmptyResult = eWarnAboutEmptyStringResult 
};


// Used to specify the encoding of TXString (char buffer).
enum class ETXEncoding {
    eMacEncoded,
    eWinEncoded,
	eSysEncoded,	// use Windows encoding on Windows and Mac encoding on Mac
    eUTF8,
	eUTF16,			// UTF-16 little endian
	eUnkown
};


// For unit tests
namespace UnitTests
{
	class TXStringUnitTest;
}


// TXString character type
#if GS_WIN
typedef wchar_t TXChar;
#elif GS_LIN
typedef char16_t TXChar;
#else
typedef UniChar TXChar;
#endif


// StdUStr definition
#if GS_WIN
// Allocator for StdUStr
template <typename T>
class TXAlloc
{
public:
	// Type definitions
	typedef size_t			size_type;
	typedef ptrdiff_t		difference_type;
	typedef T*				pointer;
	typedef const T*		const_pointer;
	typedef T&				reference;
	typedef const T&		const_reference;
	typedef T				value_type;

	// Rebind allocator to type U
	template <typename U>
	struct rebind {
		typedef TXAlloc<U> other;
	};

	// Return address of values
	pointer			address(reference value) const { return &value; }
	const_pointer	address(const_reference value) const { return &value; }

	// Constructors and distructors
	TXAlloc() throw() {}
	TXAlloc(const TXAlloc&) throw() {}
	template <typename U> TXAlloc(const TXAlloc<U>&) throw() {}
	~TXAlloc() throw() {}

	// Max size
	size_type max_size() const throw() { return (size_type)(-1) / sizeof(T); }

	// Allocation
	pointer allocate(size_type num, const void* hint = 0)
	{
		return (pointer) gVWMM->TXStringAllocate(num * sizeof(T));
	}
  
	// Deallocation
	void deallocate(pointer p, size_type) 
	{
		gVWMM->TXStringDeallocate(p);
	}

	// Construction
	void construct(pointer p, const_reference value) { new (p) T(value); }

	// Destruction
	void destroy(pointer p) { p->~T(); }

	inline bool operator==(TXAlloc const&) throw() { return true; }
    inline bool operator!=(TXAlloc const&) throw() { return false; }
};

template <typename T>
bool operator==(const TXAlloc<T>& lhs, const TXAlloc<T>& rhs) throw() {
	return true;
}

// StrUStr definition
typedef std::basic_string<TXChar, std::char_traits<TXChar>, TXAlloc<TXChar>> StdUStr;

#elif GS_LIN
typedef std::basic_string<TXChar> StdUStr;
#else	// Mac
typedef std::basic_string<TXChar> StdUStr;
#endif


//#######################################################################################
// TXString class
// Please refer to GSString.X.cpp for more detailed descriptions. [PChang]
//#######################################################################################
class GS_COMP_API GS_HIDDEN_VISIBILITY TXString : public TDebugObject
{
public:
	
	//***********************************************************************************
	// Constructors and destructor
	//***********************************************************************************
	
	TXString();									// Default constructor
	TXString(const TXString& src);				// Copy constructor
	TXString(TXString&& src);					// Move constructor
	TXString(const StdUStr& src);				// Copy constructor from StdUStr
	TXString(StdUStr&& src);					// Move constructor from StdUStr

	// From other string type
	TXString(const std::string& src, ETXEncoding e = ETXEncoding::eUTF8);

#if GS_WIN
	TXString(const std::wstring& src);
#elif GS_LIN
	// not defined
#elif GS_MAC
	TXString(const std::wstring& src);
	TXString(const CFStringRef& src);			// Construct from CFStringRef&
#endif

	// Specify initial size
	explicit TXString(size_t nInitialSize);		// Specify size (size_t version)
	explicit TXString(int nInitialSize);		// Specify size	(int version)

	// From a buffer
	TXString(const char* src, ETXEncoding e = ETXEncoding::eUTF8);
	TXString(const char* src, size_t len, ETXEncoding e = ETXEncoding::eUTF8);

	TXString(const unsigned char* src, ETXEncoding e = ETXEncoding::eUTF8);

	TXString(const UCChar* src);
	TXString(const UCChar* src, size_t len);

	TXString(const wchar_t* src);
	TXString(const wchar_t* src, size_t len);
	
	// From a character
	explicit TXString(char ch, size_t count = 1);
	explicit TXString(unsigned char ch, size_t count = 1);
	explicit TXString(UCChar ch, size_t count = 1);
	explicit TXString(wchar_t ch, size_t count = 1);
	
	// Destructor
	virtual ~TXString();
	
	
	//***********************************************************************************
	// Assignments
	//***********************************************************************************
	
	TXString& operator=(const TXString& src);		// Copy assignment operator
	TXString& operator=(TXString&& src);			// Move assignment operator
	TXString& operator=(const std::string& src);	// Assignment from std::string
	TXString& operator=(const std::wstring&src);	// Assignment from std::wstring
#if GS_MAC
	TXString& operator=(const CFStringRef& src);	// Assignment from CFStringRef&
#endif
	
	// From a buffer
	TXString& operator=(const char *src);
	TXString& operator=(const unsigned char* src);
	TXString& operator=(const UCChar* src);
	TXString& operator=(const wchar_t* src);
	
	// From single character
	TXString& operator=(char ch);
	TXString& operator=(unsigned char ch);
	TXString& operator=(UCChar ch);
	TXString& operator=(wchar_t ch);
	TXString& operator=(int codePoint);		// For example: txString = 0x27
	
	
	//***********************************************************************************
	// Length and width related functions
	//***********************************************************************************
	
	size_t GetLength() const;
	size_t GetByteSize() const;
	size_t GetEncodingLength(ETXEncoding e) const;
	
	bool IsEmpty() const;
	
	TXString& SetLength(size_t len);
	TXString& SetLength(size_t len, TXChar ch);
	TXString& Truncate(size_t len);
	TXString& Clear();
	
	size_t GetWidthInNumOfStdChar() const;	// Get width in number of standard character width.
	
	//***********************************************************************************
	// Element access
	//***********************************************************************************
	
	TXChar& operator[](ptrdiff_t nIndex);
	TXChar operator[](ptrdiff_t nIndex) const;
	TXChar& GetAt(size_t nIndex);
	TXChar GetAt(size_t nIndex) const;
	TXChar& GetLast();
	TXChar GetLast() const;
	TXString& SetAt(size_t nIndex, TXChar ch);
	
	
	//***********************************************************************************
	// Concatenation
	//***********************************************************************************
	
	// Extends string from another TXString object
	TXString& operator+=(const TXString& src);
	
	// Extends string from character buffer
	TXString& operator+=(const char* src);			// UTF-8
	TXString& operator+=(const unsigned char* src);	// UTF-8
	TXString& operator+=(const UCChar* src);
	TXString& operator+=(const wchar_t* src);
	
	// Extends string by one character
	TXString& operator+=(char ch);
	TXString& operator+=(unsigned char ch);
	TXString& operator+=(UCChar ch);
	TXString& operator+=(wchar_t ch);
	TXString& operator+=(int n);				// Unicode code point, for example: 0x63
												// This is different behaviour than operator<< which appends the number as value
	
	// String concatenation by using '<<'
	TXString& operator<<(const TXString& src);
	
	// Extends string from character buffer
	TXString& operator<<(const char *src);			// UTF-8
	TXString& operator<<(const unsigned char* src);	// UTF-8
	TXString& operator<<(const UCChar* src);
	TXString& operator<<(const wchar_t* src);
	
	// Extends string by one character
	TXString& operator<<(char ch);
	TXString& operator<<(unsigned char ch);
	TXString& operator<<(UCChar ch);
	TXString& operator<<(wchar_t ch);
	
	// Append a number as string
	TXString& operator<<(Sint32 number);
	TXString& operator<<(Sint64 number);
	TXString& operator<<(Uint32 number);
	TXString& operator<<(Uint64 number);
	TXString& operator<<(double number);
#if GS_MAC
	TXString& operator<<(size_t number); // size_t is different from Uint64 on the mac
#endif
	TXString& operator<<(const GSHandle h); // as number
	
	
	//***********************************************************************************
	// Insertion and deletion
	//***********************************************************************************
	
	// Insert another TXString at position 'pos'.
	TXString& Insert(size_t pos, const TXString& src);
	
	// Insert one buffer at position 'pos'.
	TXString& Insert(size_t pos, const char* src);
	TXString& Insert(size_t pos, const unsigned char* src);		// UTF-8
	TXString& Insert(size_t pos, const UCChar* src);
	TXString& Insert(size_t pos, const wchar_t* src);
	
	// Insert one character 'ch' at position 'pos'.
	TXString& Insert(size_t pos, char ch);
	TXString& Insert(size_t pos, unsigned char ch);
	TXString& Insert(size_t pos, UCChar ch);
	TXString& Insert(size_t pos, wchar_t ch);
	TXString& Insert(size_t pos, int ch);						// e.g. 0xA5, '¥'
	
	// Delete characters starting from 'pos' for 'len' characters.
	TXString& Delete(size_t pos, size_t len = (size_t) -1);
	
	// Delete the last character
	TXString& DeleteLast();
	
	// Trims white spaces (' ', '\t') or invalid chars
	TXString& TrimLeft();
	TXString& TrimRight();
	TXString& Trim();

	TXString& TrimLeftInvalidCharacter();
	TXString& TrimRightInvalidCharacter();
	TXString& TrimInvalidCharacters();
	
	
	//***********************************************************************************
	// Replacement, case conversion, reversion, Unicode normalization form conversion
	//***********************************************************************************
	
	// Replaces all 'oldStr' with 'newSTr'.
	TXString& Replace(const TXString& oldStr, const TXString& newStr, bool bIgnoreCase = false);
	
	// Upper case and lower case conversion
	TXString& MakeUpper();
	TXString& MakeLower();
	
	// Reverse the string.
	TXString& MakeReverse();
	
	// Conversion to a Unicode normalization form
	TXString& ToPrecomposed();
	TXString& ToDecomposed();
	
	
	//***********************************************************************************
	// Getting data and casting
	//***********************************************************************************
	
	// Returns const pointer to the TXChar buffer.
	const TXChar* GetData() const;
	const TXChar* GetTXCharPtr() const;
	
	// Casting operators
	operator const char*() const;				// UTF-8
	operator const unsigned char*() const;		// UTF-8
	operator const UCChar*() const;				// Unsigned short, UTF-16
	operator const wchar_t*() const;			// wchar_t: Win:UTF-16, Mac:UTF-32
	
	// Casting operators in function form.
	const char* GetCharPtr() const { return (operator const char*()); }
	const unsigned char* GetUCharPtr() const { return (operator const unsigned char*()); }
	const UCChar* GetUCCharPtr() const { return (operator const UCChar*()); }
	const wchar_t* GetWCharPtr() const { return (operator const wchar_t*()); }
	
	// Returns a std string or wstring
	std::string GetStdString(ETXEncoding e = ETXEncoding::eUTF8) const;
	std::wstring GetStdWString() const;
#if GS_MAC
	CFStringRef GetCFStringRef() const;
#endif
	
	
	//***********************************************************************************
	// Copying data into external buffer
	//
	// Note: 'bufSize' is the size of the buffer in bytes. For example, "xyz" needs four bytes to include '\0' at the end.
	//
	//***********************************************************************************
	void CopyInto(char* dst,
				  size_t bufSize,
				  ETXEncoding e = ETXEncoding::eUTF8) const;

	void CopyInto(unsigned char* ps,
				  size_t bufSize,
				  ETXEncoding e = ETXEncoding::eUTF8) const;
	
	void CopyInto(UCChar* dst, size_t bufElemSize) const;

	void CopyInto(wchar_t* dst, size_t bufElemSize) const;
	
	
	//***********************************************************************************
	// Find functions
	//***********************************************************************************
	ptrdiff_t Find(const TXString &subStr, size_t posFirst = 0, bool bIgnoreCase = false) const;
	ptrdiff_t Find(int ch, size_t posFirst = 0, bool bIgnoreCase = false) const;
	ptrdiff_t Find(char ch, size_t posFirst = 0, bool bIgnoreCase = false) const;
	
	ptrdiff_t ReverseFind(const TXString &subStr, size_t posLast = -1, bool bIgnoreCase = false) const;
	ptrdiff_t ReverseFind(int ch, size_t posLast = -1, bool bIgnoreCase = false) const;
	ptrdiff_t ReverseFind(char ch, size_t posLast = -1, bool bIgnoreCase = false) const;
	
	ptrdiff_t FindOneOf(const TXString &charSet, size_t posFirst = 0) const;
	ptrdiff_t ReverseFindOneOf(const TXString &charSet, size_t posLast = -1) const;
	
	ptrdiff_t FindNotOneOf(const TXString &charSet, size_t posFirst = 0) const;
	ptrdiff_t ReverseFindNotOneOf(const TXString &charSet, size_t posLast = -1) const;
	
	bool SurrogatePairAt(size_t nIndex) const;
	bool HasSurrogatePair() const;
	
	
	//***********************************************************************************
	// Creating sub-string
	//***********************************************************************************
	TXString Mid(size_t nFirst, size_t len = -1) const;
	TXString Left(size_t len) const;
	TXString Right(size_t len) const;
	
	
	//***********************************************************************************
	// Conversion to and from numerics
	//***********************************************************************************
	Sint32 atoi() const;
	Sint64 atoi64() const;
	Real64 atof() const;
	TXString& itoa(Sint64 value);
	TXString& ftoa(Real64 value);
	TXString& ftoa(Real64 value, Sint32 precision);
	static TXString	ToStringInt(Sint64 value);
	static TXString	ToStringInt(Sint64 value, Sint32 width, wchar_t paddingChar);
	static TXString	ToStringReal(Real64 value);
	static TXString	ToStringReal(Real64 value, Sint32 precision, bool fixed=true);
	template<typename T>
	static TXString ToString(T value);
	template<typename T>
	static TXString ToStringHex(T value, bool upperCase = true, size_t symbolsCnt = size_t(-1));
	
	static bool IsPunctuation(TXChar aTXChar);
	static bool IsWhitespace(TXChar aTXChar);

	
	//***********************************************************************************
	// Comparison and plus operator
	//***********************************************************************************
	
	// Equality functions
	bool Equal(const TXString &str) const;
	bool EqualNoCase(const TXString &str) const;
	
	// Comparison functions
	Sint32 Compare(const TXString &str) const;
	Sint32 CompareNoCase(const TXString &str) const;

	// Comparison operators
	friend bool operator==(const TXString& lhs, const TXString& rhs);
	friend bool operator==(const TXString& lhs, const char* rhs);
	friend bool operator==(const char* lhs, const TXString& rhs);
	friend bool operator==(const TXString& lhs, const TXChar* rhs);
	friend bool operator==(const TXChar* lhs, const TXString& rhs);

	friend bool operator!=(const TXString& lhs, const TXString& rhs);
	friend bool operator!=(const TXString& lhs, const char* rhs);
	friend bool operator!=(const char* lhs, const TXString& rhs);
	friend bool operator!=(const TXString& lhs, const TXChar* rhs);
	friend bool operator!=(const TXChar* lhs, const TXString& rhs);

	friend bool operator<=(const TXString& lhs, const TXString& rhs);
	friend bool operator>=(const TXString& lhs, const TXString& rhs);

	friend bool operator<(const TXString& lhs, const TXString& rhs);
	friend bool operator>(const TXString& lhs, const TXString& rhs);
	
	// Plus operator
	friend TXString operator+(const TXString& lhs, const TXString& rhs);
	friend TXString operator+(const TXString& lhs, TXChar rhs);
	friend TXString operator+(TXChar lhs, const TXString& rhs);
	friend TXString operator+(const TXString& lhs, const TXChar* rhs);
	friend TXString operator+(const TXChar* lhs, const TXString& rhs);
		
	// Strict type formatting functions to replace the Format function
	// It will substitute any %x in the string with the specified value. NOTE: No modifies supported
	// These use std::wstringstream and operator << to concatenate to the string
	// VisualStudio 2010 doesnt support variadic templates still, so i'm forced in doing this
	TXString&	Format(const TXString& format);
	template<typename T0>
	TXString&	Format(const TXString& format, const T0& val0);
	template<typename T0, typename T1>
	TXString&	Format(const TXString& format, const T0& val0, const T1& val1);
	template<typename T0, typename T1, typename T2>
	TXString&	Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2);
	template<typename T0, typename T1, typename T2, typename T3>
	TXString&	Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3);
	template<typename T0, typename T1, typename T2, typename T3, typename T4>
	TXString&	Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4);
	template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
	TXString&	Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5);
	template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	TXString&	Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5, const T6& val6);
	template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
	TXString&	Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5, const T6& val6, const T7& val7);
	template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
	TXString&	Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5, const T6& val6, const T7& val7, const T8& val8);
	template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
	TXString&	Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5, const T6& val6, const T7& val7, const T8& val8, const T9& val9);
	template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
	TXString&	Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5, const T6& val6, const T7& val7, const T8& val8, const T9& val9, const T10& val10);
	template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
	TXString&	Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5, const T6& val6, const T7& val7, const T8& val8, const T9& val9, const T10& val10, const T11& val11);

	// static tool functions: Formatted
	template<typename T0>
	static TXString		Formatted(const TXString& format, const T0& val0)																											{ return TXString().Format( format, val0 ); }
	template<typename T0, typename T1>
	static TXString		Formatted(const TXString& format, const T0& val0, const T1& val1)																							{ return TXString().Format( format, val0, val1 ); }
	template<typename T0, typename T1, typename T2>
	static TXString		Formatted(const TXString& format, const T0& val0, const T1& val1, const T2& val2)																			{ return TXString().Format( format, val0, val1, val2 ); }
	template<typename T0, typename T1, typename T2, typename T3>
	static TXString		Formatted(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3)															{ return TXString().Format( format, val0, val1, val2, val3 ); }
	template<typename T0, typename T1, typename T2, typename T3, typename T4>
	static TXString		Formatted(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4)											{ return TXString().Format( format, val0, val1, val2, val3, val4 ); }
	template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
	static TXString		Formatted(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5)							{ return TXString().Format( format, val0, val1, val2, val3, val4, val5 ); }
	template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	static TXString		Formatted(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5, const T6& val6)			{ return TXString().Format( format, val0, val1, val2, val3, val4, val5, val6 ); }

#if 1
	//***********************************************************************************
	// Methods we want to get rid of
	//***********************************************************************************
	// PStr
	template <size_t maxCharLen>
	TXString(const PStr<maxCharLen>& src)
		: charPtr(nullptr)
		, charBufSize(0)
	{
		char temp[256];
		strncpy(temp, (const char *)((const unsigned char *)src) + 1, src.GetLength());
		temp[src[0]] = 0;
		*this = temp;
	}
	
	template <size_t maxCharLen>
	TXString& operator=(const PStr<maxCharLen>& src)
	{
		char temp[256];
		strncpy(temp, (const char *)((const unsigned char *)src) + 1, src.GetLength());
		temp[src[0]] = 0;
		*this = temp;
		return *this;
	}
	
	template <size_t maxCharLen>
	const TXString& operator+=(const PStr<maxCharLen>& src)
	{
		char temp[256];
		strncpy(temp, (const char *)((const unsigned char *)src) + 1, src.GetLength());
		temp[src[0]] = 0;
		*this += temp;
		return *this;
	}
	
	template <size_t maxCharLen>
	TXString& operator<<(const PStr<maxCharLen>& src)
	{
		char temp[256];
		strncpy(temp, (const char *)((const unsigned char *)src) + 1, src.GetLength());
		temp[src[0]] = 0;
		*this += temp;
		return *this;
	}
	
	
#endif
	
	// Swap function
	void swap(TXString& rhs);
	
	//***********************************************************************************
	// Private members
	//***********************************************************************************
private:
	StdUStr stdUStr;
	
	void SetStdUStrFromCharBuffer(const char* src, size_t len = -1, ETXEncoding e = ETXEncoding::eUTF8);
	
	// For char buffer. TXString might be better to return a std::string instead of
	// returning const char* in the future.
	mutable char* charPtr;
	mutable int charBufSize;
	void PrepareCharBuffer(ETXEncoding e = ETXEncoding::eUTF8) const;

#if GS_MAC || GS_LIN
	mutable std::wstring wStr;
#endif

	// Unit tests
	friend class UnitTests::TXStringUnitTest;
};


// Comparison operators
bool operator==(const TXString& lhs, const TXString& rhs);
bool operator==(const TXString& lhs, const char* rhs);
bool operator==(const char* lhs, const TXString& rhs);
bool operator==(const TXString& lhs, const TXChar* rhs);
bool operator==(const TXChar* lhs, const TXString& rhs);

bool operator!=(const TXString& lhs, const TXString& rhs);
bool operator!=(const TXString& lhs, const char* rhs);
bool operator!=(const char* lhs, const TXString& rhs);
bool operator!=(const TXString& lhs, const TXChar* rhs);
bool operator!=(const TXChar* lhs, const TXString& rhs);

bool operator<=(const TXString& lhs, const TXString& rhs);
bool operator>=(const TXString& lhs, const TXString& rhs);

bool operator<(const TXString& lhs, const TXString& rhs);
bool operator>(const TXString& lhs, const TXString& rhs);

// Plus operator
TXString operator+(const TXString& lhs, const TXString& rhs);
TXString operator+(const TXString& lhs, TXChar rhs);
TXString operator+(TXChar lhs, const TXString& rhs);
TXString operator+(const TXString& lhs, const TXChar* rhs);
TXString operator+(const TXChar* lhs, const TXString& rhs);

// Non-member swap function
void swap(TXString& lhs, TXString& rhs);

namespace std
{
	template<>
	void swap<TXString>(TXString& lhs, TXString& rhs);
}


//#######################################################################################
// TXStringArray
// Please refer to GSString.X.cpp for more detailed descriptions. [PChang]
//#######################################################################################

#if GS_WIN
typedef std::vector<TXString, TXAlloc<TXString>> StrVec;
#else
typedef std::vector<TXString> StrVec;
#endif

class TXStringArray
{
public:

	// Constructors and destructor
					TXStringArray(size_t nInitialSize = 0);		// Default constructor
					TXStringArray(const TXStringArray &src);	// Copy constructor
					TXStringArray(TXStringArray &&src);			// Move constructor
	virtual			~TXStringArray();							// Destructor

	// Assignment operators
	TXStringArray&	operator=(const TXStringArray &src);		// Copy assignment
	TXStringArray&	operator=(TXStringArray &&src);				// Move assignment

	// Size related functions
	TXStringArray&	SetSize(size_t size);
	size_t			GetSize() const;
	bool			IsEmpty() const;

	// Element access
	TXStringArray&	SetAt(size_t nIndex, const TXString &string);
	const TXString&	GetAt(size_t nIndex) const;
	TXString&		GetAt(size_t nIndex);
	const TXString&	operator[](size_t nIndex) const;
	TXString&		operator[](size_t nIndex);

	// Append
	TXStringArray&	Append(const TXString &string);
	TXStringArray&	Append(const TXStringArray &src);

	// Prepend
	TXStringArray&	Prepend(const TXString &string);


	// Erase and clear
	TXStringArray&	Erase(size_t nIndex, size_t nCount = 1);
	TXStringArray&	Clear();

	// Find
	ptrdiff_t		Find(const TXString& str, bool bIgnoreCase = false) const;

	// Sort
	TXStringArray&	Sort(std::function<bool (const TXString&, const TXString&)> sortFunction = nullptr);

	// traversing functions to be used with C++11 for(auto it : arr)
	StrVec::iterator		begin();
	StrVec::iterator		end();
	StrVec::const_iterator	begin() const;
	StrVec::const_iterator	end() const;

private:
	StrVec			strVec;

	// Unit tests
	friend class UnitTests::TXStringUnitTest;
};



//#######################################################################################
class TXResource
{
public:
	TXResource(const char* resourceIdentifier, const char* resourceStringIdentifier, EEmptyHandling allowEmpty = eDontAllowEmptyResult);
	TXResource(const char* resourceIdentifier);
	~TXResource();

	operator const TXString&();

	const char*		c_str();
	size_t			Size() const;
	const void*		Buffer() const;
	GSHandle 		GetHandle();

protected:
	TXResource(const TXResource& src);
	TXResource& operator = (const TXResource& src);

private:
	TXString	fString;
	GSHandle	fResource;
};

// TXResStr is a convenience type intended to standardize requests for localized strings
//  in a concise way.  It assumes the default vwr contains the file in a "Strings" directory,
//  and that the strings file has extension ".vwstrings"
class TXResStr
{
public:
	TXResStr(const char* stringsFileNameWithoutPathOrExtension, const char* resourceStringIdentifier, EEmptyHandling allowEmpty=eDontAllowEmptyResult);
	operator const TXString&();
private:
	TXString	fString;
};


//#######################################################################################
class TXLegacyResource
{
public:
	TXLegacyResource(short stringResID, short indexID, EEmptyHandling allowEmpty = eDontAllowEmptyResult);
	TXLegacyResource(const char* defaultResourceIdentifier, short stringResID, short indexID, EEmptyHandling allowEmpty = eDontAllowEmptyResult);
	TXLegacyResource(short textResID);
	TXLegacyResource(const char* resourceType, short resourceID);
	// I introduce this constructor only to help replace the legacy ISDK::GSGetResourceString call
	// there are 500+ calls and it is pain (high risk) to change those calls just like that
	TXLegacyResource(short stringResID, short indexID, TXString& outString);
	~TXLegacyResource();

	operator const TXString&();

	const char*		c_str();
	size_t			Size() const;
	const void*		Buffer() const;
	GSHandle 		GetHandle();

protected:
	TXLegacyResource(const TXLegacyResource& src);
	TXLegacyResource& operator = (const TXLegacyResource& src);

private:
	TXString	fString;
	GSHandle	fResource;
};

//#######################################################################################
class TXLegacyDialogResource
{
public:
	TXLegacyDialogResource(short dialogResourceID);

	operator const char*();

private:
	TXString	fString;
};



/////////////////////////////////////////////////////////////////////////////////////////
// convenicence std library version functions
/////////////////////////////////////////////////////////////////////////////////////////

#if GS_WIN
inline size_t UCStrLen(ConstUCStrPtr s)						{ return wcslen((const wchar_t*)s); }
inline size_t UCStrLen(const wchar_t* s)					{ return wcslen(s); }
inline int    UCStrCmp(ConstUCStrPtr s1, ConstUCStrPtr s2)	{ return wcscmp((const wchar_t*)s1, (const wchar_t*)s2); }
inline void   UCStrCpy(UCStrPtr dest, ConstUCStrPtr src)    { wcscpy((wchar_t*)dest, (const wchar_t*)src); }
#elif GS_LIN
inline size_t UCStrLen(ConstUCStrPtr s)						{ return wcslen((const wchar_t*)s); }
inline size_t UCStrLen(const wchar_t* s)					{ return wcslen(s); }
inline int    UCStrCmp(ConstUCStrPtr s1, ConstUCStrPtr s2)	{ return wcscmp((const wchar_t*)s1, (const wchar_t*)s2); }
inline void   UCStrCpy(UCStrPtr dest, ConstUCStrPtr src)    { wcscpy((wchar_t*)dest, (const wchar_t*)src); }
#else
inline size_t UCStrLen(ConstUCStrPtr s)						{ return StdUStr((const TXChar*)s).length(); }
inline int    UCStrCmp(ConstUCStrPtr s1, ConstUCStrPtr s2)	{ return StdUStr((const TXChar*)s1).compare((const TXChar*)s2); }
inline void   UCStrCpy(UCStrPtr dest, ConstUCStrPtr src)    { StdUStr in((const TXChar*)src); memcpy(dest, in.c_str(), (in.length() + 1) * 2); }
#endif

inline size_t UCByteLen(ConstUCStrPtr s)					{ return (UCStrLen(s) + 1) * sizeof(UCChar); }


/////////////////////////////////////////////////////////////////////////////////////////
// TXGenericArray //
/////////////////////////////////////////////////////////////////////////////////////////

template<class T> class TXGenericArray
{
public:
					TXGenericArray(size_t nInitialSize=0, size_t nGrowBy=10);
					TXGenericArray(const TXGenericArray &src);
	virtual			~TXGenericArray();

	TXGenericArray&	operator=(const TXGenericArray &src);

	size_t			GetSize() const;
	bool			SetSize(size_t size);

	bool			IsEmpty() const;

	const T&		GetAt(size_t nIndex) const;
	T&				GetAt(size_t nIndex);
	const T&		operator[](size_t nIndex) const;
	T&				operator[](size_t nIndex);

	void 			SetAt(size_t nIndex, const T & value);

	bool 			Append(const T & value);
	bool 			Append(const TXGenericArray & src);

	void 			Erase(size_t nIndex, size_t nCount = 1);
	void 			Clear();

	// return size_t(-1) if not found
	size_t			Find(const T& value);

private:
	void 			Init(size_t nInitialSize, size_t nGrowBy);
	bool 			EnsureArraySize(size_t nSize);

	size_t		fGrowBy;
	size_t		fNumStringsStored;
	size_t		fMaxStringsStored;
	T*			fValuesPtr;
};


/////////////////////////////////////////////////////////////////////////////////////////
// TXGenericArray Routines //
/////////////////////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------------------
template<class T> TXGenericArray<T>::TXGenericArray(size_t nInitialSize, size_t nGrowBy)
{
	this->Init(nInitialSize, nGrowBy);
}

//---------------------------------------------------------------------------------------
template<class T> TXGenericArray<T>::TXGenericArray(const TXGenericArray<T> & src)
{
	this->Init(src.GetSize(), src.fGrowBy);
	this->Append(src);
}

//---------------------------------------------------------------------------------------
template<class T> TXGenericArray<T>::~TXGenericArray()
{
	this->Clear();
}

//---------------------------------------------------------------------------------------
template<class T> TXGenericArray<T>& TXGenericArray<T>::operator=(const TXGenericArray<T> & src)
{
	this->Init(src.GetSize(), src.fGrowBy);
	this->Append(src);
	return *this;
}

//---------------------------------------------------------------------------------------
template<class T> bool TXGenericArray<T>::SetSize(size_t nSize)
{
	if (nSize < fNumStringsStored) {
		this->RemoveAt(nSize, fNumStringsStored - nSize);
	}
	else if (nSize > fNumStringsStored) {
		if (this->EnsureArraySize(nSize)) {
			fNumStringsStored = nSize;
		}
		else
			return false;
	}
	return true;
}

//---------------------------------------------------------------------------------------
template<class T> size_t TXGenericArray<T>::GetSize() const
{
	return fNumStringsStored;
}

//---------------------------------------------------------------------------------------
template<class T> bool TXGenericArray<T>::IsEmpty() const
{
	return fNumStringsStored == 0;
}

//---------------------------------------------------------------------------------------
template<class T> const T& TXGenericArray<T>::GetAt(size_t nIndex) const
{
	ASSERTN(kDave, nIndex < fNumStringsStored);
	return fValuesPtr[nIndex];
}

//---------------------------------------------------------------------------------------
template<class T> T& TXGenericArray<T>::GetAt(size_t nIndex)
{
	ASSERTN(kDave, nIndex < fNumStringsStored);
	return fValuesPtr[nIndex];
}

//---------------------------------------------------------------------------------------
template<class T> const T& TXGenericArray<T>::operator[](size_t nIndex) const
{
	return GetAt(nIndex);
}

//---------------------------------------------------------------------------------------
template<class T> T& TXGenericArray<T>::operator[](size_t nIndex)
{
	return GetAt(nIndex);
}

//---------------------------------------------------------------------------------------
template<class T> void TXGenericArray<T>::SetAt(size_t nIndex, const T & value)
{
	if (this->EnsureArraySize(nIndex+1)) {
		fValuesPtr[nIndex] = value;
		if (nIndex+1 > fNumStringsStored) {
			fNumStringsStored = nIndex+1;
		}
	}
}

//---------------------------------------------------------------------------------------
template<class T> bool TXGenericArray<T>::Append(const T & value)
{
	if (EnsureArraySize(fNumStringsStored+1)) {
		fValuesPtr[fNumStringsStored] = value;
		++fNumStringsStored;
		return true;
	}
	return false;
}

//---------------------------------------------------------------------------------------
template<class T> bool TXGenericArray<T>::Append(const TXGenericArray<T> & src)
{
	const size_t nNumToAppend = src.GetSize();

	if (this->EnsureArraySize(fNumStringsStored + nNumToAppend)) {

		for (size_t i=0; i<nNumToAppend; ++i) {
			this->Append(src[i]);
		}
		return true;
	}
	return false;
}

//---------------------------------------------------------------------------------------
template<class T> void TXGenericArray<T>::Erase(size_t nIndex, size_t nCount)
{
	// The method used here may seem weird, but it doesn't require
	// any new memory to be allocated, so it can't fail.

	// Check and correct parameters.
	if (nIndex < fNumStringsStored && nCount > 0) {
	
		// for the starting index specified, determine the maximum legal count
		size_t maxCount = fNumStringsStored - nIndex;
	
		// pin count to the max legal range
		if (nCount > maxCount)
			nCount = maxCount;

		// slide the remaining strings down one by one
		for (size_t i = nIndex; i + nCount < fNumStringsStored; i++) {
			fValuesPtr[i] = fValuesPtr[i + nCount];
		}
		
		fNumStringsStored -= nCount;		
	}
}


// this is the source of a gargantuan memory leak. TXGenericArray is defined to grow in chunks of 10 or more strings.
// so the maximum size is usually greater than the occupied size. When we were disposing of these arrays (which are used
// all over the place) we were only disposing of the strings being used and leaking the unused strings at the end of the array. - PCP

//---------------------------------------------------------------------------------------
template<class T> void TXGenericArray<T>::Clear()
{
	// Delete each value in the array.
	for (size_t i=0; i<fMaxStringsStored; ++i) {
		fValuesPtr[i].~T();
	}

	char*		pBuffer		= (char*) fValuesPtr;
	if ( pBuffer ) {
		char*	pTheData		= pBuffer - 1;
		char	memoryCode		= *pTheData;

		void TXGenericArray_Dispose(char memoryCode, char* pTheData);
		TXGenericArray_Dispose( memoryCode, pTheData );
	}

	fValuesPtr = NULL;

	fNumStringsStored = fMaxStringsStored = 0;
}


//---------------------------------------------------------------------------------------
template<class T> void TXGenericArray<T>::Init(size_t nInitialSize, size_t nGrowBy)
{
	fGrowBy = nGrowBy;
	fNumStringsStored = fMaxStringsStored = 0;
	fValuesPtr = NULL;
	
	this->EnsureArraySize(nInitialSize);
}

//---------------------------------------------------------------------------------------
template<class T> bool TXGenericArray<T>::EnsureArraySize(size_t nSize)
{
	if (fMaxStringsStored < nSize) {

		size_t nRoundedSize = (nSize / fGrowBy) * fGrowBy;
		if (nSize % fGrowBy) nRoundedSize += fGrowBy;

		char	memoryCode		= 0;

		// Allocate new, larger buffer for all of the value pointers.
		char* TXGenericArray_Allocate(char& memoryCode, size_t sz);
		char*	newBuf		= TXGenericArray_Allocate( memoryCode, 1 + sizeof(T) * nRoundedSize );

		if ( newBuf == NULL )
			return false;

		*newBuf			= memoryCode;

		T*	pNewArray = (T*) (newBuf + 1);
		if (pNewArray) {
			for(size_t i=0; i<nRoundedSize; i++) {
				if ( i < fNumStringsStored ) {
					new (&pNewArray[i]) T( fValuesPtr[i] );
				}
				else {
					new (&pNewArray[i]) T();
				}
			}

			size_t	numStringsStored = fNumStringsStored;
			for(size_t i=0; i<numStringsStored; i++) {
				pNewArray[i]	= fValuesPtr[i];
			}

			this->Clear();

			fValuesPtr			= pNewArray;
			fMaxStringsStored	= nRoundedSize;
			fNumStringsStored	= numStringsStored;

			return true;
		}
		return false;
	}
	return true;
}

template<class T> size_t TXGenericArray<T>::Find(const T& value)
{
	for (size_t i = 0; i < fNumStringsStored; i++) {
		if ( this->GetAt (i) == value ) {
			return i;
		}
	}

	return size_t(-1);
}


template <size_t maxCharLen> PStr<maxCharLen>&  PStr<maxCharLen>::operator=(const TXString& s)
{ 
	StringCopy((const char *)s, buf, maxCharLen+1); 
	return *this; 
}

template <size_t maxCharLen> PStr<maxCharLen>::PStr(const TXString& s)
{ 
	StringCopy((const char *)s, buf, maxCharLen+1); 
}


//---------------------------------------------------------------------------------------
// Replaces format specifiers (%d, %s, %.20s, %02d, etc.) with given parameters in a given string.
// Iterates through a list of parameters and for each one searches the original string
// for a format specifier that matches the parameter type.
// If no match is found, the format specifier is copied "as is" in the output result.
// The formating continues until end of source is reached.
//
// NOTES:
// 1. The order and type of the parameters need to match between what is expected and what is passed in.
// For example:
//    opstext.text1 = "This is a %s string and number = %d"
//
//    Unsafe code:
//       char buffer[100];
//       snprintf_Safe( buffer, sizeof(buffer), opstext.text1, "test", 123 );
//       snprintf_Safe( buffer, sizeof(buffer), "%s", opstext.text1 );
//       buffer = "This is a test string and number = 123"
//
//    Safe code - right way to use it:
//       char buffer[100];
//       CFormatString( opstext.text1, buffer, sizeof(buffer)).Param("test").Param(123).Format();
//       buffer = "This is a test string and number = 123"
//    Safe code - wrong way to use it:
//       char buffer[100];
//       CFormatString( opstext.text1, buffer, sizeof(buffer)).Param(123).Param("test").Format();
//       buffer = "This is a %s string and number = %d"
// NOTE:
// The following is not a supported scenario:
//    If the width specification is an asterisk(*), an int argument from the argument list supplies the value.
//    The width argument must precede the value that's being formatted in the argument list, as shown in this example:
//    printf("%0*f", 5, 3); /* 00003 is output */
//---------------------------------------------------------------------------------------
class CFormatString
{
public:
				CFormatString(const TXString& format);
	virtual		~CFormatString();

	TXString	Format();

	CFormatString&	Param(short value);
	CFormatString&	Param(int value);
	CFormatString&	Param(long value);
	CFormatString&	Param(long long value);
	CFormatString&	Param(unsigned short value);
	CFormatString&	Param(unsigned int value);
	CFormatString&	Param(unsigned long value);
	CFormatString&	Param(unsigned long long value);
	CFormatString&	Param(double value);
	CFormatString&	Param(const char value);
	CFormatString&	Param(const char* value);
	CFormatString&	Param(const wchar_t value);
	CFormatString&	Param(const wchar_t* value);
	CFormatString&	Param(const void* value);
	CFormatString&	Param(const TXString& value);

private:
	enum class EParamType
	{
		  PT_SHORT
		, PT_INT
		, PT_LONG
		, PT_LONGLONG
		, PT_USHORT
		, PT_UINT
		, PT_ULONG
		, PT_ULONGLONG
		, PT_REAL
		, PT_CHAR
		, PT_VOIDPTR
		, PT_STRING
	};

	struct SParameter
	{
		EParamType		fType;

		short				fValShort;
		long				fValLong;
		int					fValInt;
		long long			fValLongLong;
		unsigned short		fValUShort;
		unsigned int		fValUInt;
		unsigned long		fValULong;
		unsigned long long	fValULongLong;
		double				fValReal;
		wchar_t				fValChar;
		const void*			fValVoid;
		TXString			fValStr;

		SParameter()
		{
			fType			= EParamType::PT_INT;
			fValShort		= 0;
			fValLong		= 0;
			fValInt			= 0;
			fValLongLong	= 0;
			fValUShort		= 0;
			fValUInt		= 0;
			fValULong		= 0;
			fValULongLong	= 0;
			fValReal		= 0;
			fValChar		= 0;
			fValVoid		= nullptr;
		}

		short				GetValueShort() const;
		int					GetValueInt() const;
		long				GetValueLong() const;
		long long			GetValueLongLong() const;
		unsigned short		GetValueUShort() const;
		unsigned int		GetValueUInt() const;
		unsigned long		GetValueULong() const;
		unsigned long long	GetValueULongLong() const;
		double				GetValueReal() const;
		wchar_t				GetValueChar() const;
		const void*			GetValueVoidPtr() const;
		TXString			GetValueString() const;
	};

	// the string to format
	TXString	fStrToFormat;

	// output buffer and its size
	TXString	fOutBuffer;

	// list of parameters to process
	std::vector<SParameter>	farrParams;
};

template<typename T0>
TXString& TXString::Format(const TXString& format, const T0& val0)
{
	CFormatString	formatter( format );
	formatter.Param( val0 );
	*this = formatter.Format();
	return *this;
}

template<typename T0, typename T1>
TXString& TXString::Format(const TXString& format, const T0& val0, const T1& val1)
{
	CFormatString	formatter( format );
	formatter.Param( val0 );
	formatter.Param( val1 );
	*this = formatter.Format();
	return *this;
}

template<typename T0, typename T1, typename T2>
TXString& TXString::Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2)
{
	CFormatString	formatter( format );
	formatter.Param( val0 );
	formatter.Param( val1 );
	formatter.Param( val2 );
	*this = formatter.Format();
	return *this;
}

template<typename T0, typename T1, typename T2, typename T3>
TXString& TXString::Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3)
{
	CFormatString	formatter( format );
	formatter.Param( val0 );
	formatter.Param( val1 );
	formatter.Param( val2 );
	formatter.Param( val3 );
	*this = formatter.Format();
	return *this;
}

template<typename T0, typename T1, typename T2, typename T3, typename T4>
TXString& TXString::Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4)
{
	CFormatString	formatter( format );
	formatter.Param( val0 );
	formatter.Param( val1 );
	formatter.Param( val2 );
	formatter.Param( val3 );
	formatter.Param( val4 );
	*this = formatter.Format();
	return *this;
}

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
TXString& TXString::Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5)
{
	CFormatString	formatter( format );
	formatter.Param( val0 );
	formatter.Param( val1 );
	formatter.Param( val2 );
	formatter.Param( val3 );
	formatter.Param( val4 );
	formatter.Param( val5 );
	*this = formatter.Format();
	return *this;
}

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
TXString& TXString::Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5, const T6& val6)
{
	CFormatString	formatter( format );
	formatter.Param( val0 );
	formatter.Param( val1 );
	formatter.Param( val2 );
	formatter.Param( val3 );
	formatter.Param( val4 );
	formatter.Param( val5 );
	formatter.Param( val6 );
	*this = formatter.Format();
	return *this;
}

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
TXString& TXString::Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5, const T6& val6, const T7& val7)
{
	CFormatString	formatter( format );
	formatter.Param( val0 );
	formatter.Param( val1 );
	formatter.Param( val2 );
	formatter.Param( val3 );
	formatter.Param( val4 );
	formatter.Param( val5 );
	formatter.Param( val6 );
	formatter.Param( val7 );
	*this = formatter.Format();
	return *this;
}

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
TXString& TXString::Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5, const T6& val6, const T7& val7, const T8& val8)
{
	CFormatString	formatter( format );
	formatter.Param( val0 );
	formatter.Param( val1 );
	formatter.Param( val2 );
	formatter.Param( val3 );
	formatter.Param( val4 );
	formatter.Param( val5 );
	formatter.Param( val6 );
	formatter.Param( val7 );
	formatter.Param( val8 );
	*this = formatter.Format();
	return *this;
}

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
TXString& TXString::Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5, const T6& val6, const T7& val7, const T8& val8, const T9& val9)
{
	CFormatString	formatter( format );
	formatter.Param( val0 );
	formatter.Param( val1 );
	formatter.Param( val2 );
	formatter.Param( val3 );
	formatter.Param( val4 );
	formatter.Param( val5 );
	formatter.Param( val6 );
	formatter.Param( val7 );
	formatter.Param( val8 );
	formatter.Param( val9 );
	*this = formatter.Format();
	return *this;
}

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
TXString& TXString::Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5, const T6& val6, const T7& val7, const T8& val8, const T9& val9, const T10& val10)
{
	CFormatString	formatter( format );
	formatter.Param( val0 );
	formatter.Param( val1 );
	formatter.Param( val2 );
	formatter.Param( val3 );
	formatter.Param( val4 );
	formatter.Param( val5 );
	formatter.Param( val6 );
	formatter.Param( val7 );
	formatter.Param( val8 );
	formatter.Param( val9 );
	formatter.Param( val10 );
	*this = formatter.Format();
	return *this;
}

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
TXString& TXString::Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5, const T6& val6, const T7& val7, const T8& val8, const T9& val9, const T10& val10, const T11& val11)
{
	CFormatString	formatter( format );
	formatter.Param( val0 );
	formatter.Param( val1 );
	formatter.Param( val2 );
	formatter.Param( val3 );
	formatter.Param( val4 );
	formatter.Param( val5 );
	formatter.Param( val6 );
	formatter.Param( val7 );
	formatter.Param( val8 );
	formatter.Param( val9 );
	formatter.Param( val10 );
	formatter.Param( val11 );
	*this = formatter.Format();
	return *this;
}

// A wrapper of std::to_string(...)
template<typename T>
/*static*/ TXString TXString::ToString(T value)
{
	return std::to_string(value);
}

template<typename T>
/*static*/ TXString TXString::ToStringHex(T value, bool upperCase, size_t symbolsCnt)
{
	static const TXChar arrUpperByteChars[] = { TXChar('0'), TXChar('1'), TXChar('2'), TXChar('3'), TXChar('4'), TXChar('5'), TXChar('6'), TXChar('7'),  TXChar('8'), TXChar('9'), TXChar('A'), TXChar('B'), TXChar('C'), TXChar('D'), TXChar('E'), TXChar('F') };
	static const TXChar arrLowerByteChars[] = { TXChar('0'), TXChar('1'), TXChar('2'), TXChar('3'), TXChar('4'), TXChar('5'), TXChar('6'), TXChar('7'),  TXChar('8'), TXChar('9'), TXChar('a'), TXChar('b'), TXChar('c'), TXChar('d'), TXChar('e'), TXChar('f') };
	const TXChar* arrChars = upperCase ? arrUpperByteChars : arrLowerByteChars;

	TXString result;
	if ( symbolsCnt > 0 )
	{
		const char* p = (const char*)&value;
		p += sizeof(T) - 1;

		bool beginning = true;
		size_t iSymCnt = 2 * sizeof(T);
		if ( symbolsCnt != size_t(-1) && symbolsCnt > iSymCnt )
		{
			for(size_t i=iSymCnt; i<symbolsCnt; i++)
				result += TXChar('0');
			symbolsCnt = iSymCnt;
		}

		for(size_t iByte=0; iByte<sizeof(T); ++iByte, --p)
		{
			if ( beginning && *p == 0 && (symbolsCnt == size_t(-1) || (iSymCnt-2) > symbolsCnt))
			{
				iSymCnt--;
				iSymCnt--;
			}
			else
			{
				beginning = true;

				char ch1 = *p & 0x0F;
				char ch2 = (*p & 0xF0)>>4;
				if ( iSymCnt <= symbolsCnt) result += arrChars[ ch2 ];
				iSymCnt--;
				if ( iSymCnt <= symbolsCnt) result += arrChars[ ch1 ];
				iSymCnt--;
			}
		}
	}

	return result;
}

#endif  // _GSSTRINGX_

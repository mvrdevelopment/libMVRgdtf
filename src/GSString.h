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
#include "GSTypes.h"
#include "GSIntTypes.h"

// For Unicode string literal
#if GS_WIN
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


#include <string>
#include <vector>
#include <memory>
#include <sstream>
namespace VectorworksMVR
{
// Used to specify the encoding of TXString (char buffer).
enum class ETXEncoding {
	eMacEncoded,
	eWinEncoded,
	eSysEncoded,	// use Windows encoding on Windows and Mac encoding on Mac
	eUTF8,
	eUTF16,			// UTF-16 little endian
	eUnkown
};


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
		return (pointer)malloc(num * sizeof(T));
	}

	// Deallocation
	void deallocate(pointer p, size_type)
	{
		delete p;
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
//#######################################################################################
class TXString
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
	#ifdef GS_LIN
	TXString& operator+=(TXChar ch);
	#endif
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
	TXString& Insert(size_t pos, int ch);						// e.g. 0xA5, '�'

	// Delete characters starting from 'pos' for 'len' characters.
	TXString& Delete(size_t pos, size_t len = (size_t)-1);

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

	//***********************************************************************************
	// Creating sub-string
	//***********************************************************************************
	TXString Mid(size_t nFirst, size_t len = -1) const;
	TXString Left(size_t len) const;
	TXString Right(size_t len) const;

	// Splits string on every occasion of ch, result does not contain ch
	std::vector<TXString> Split(char ch) const;
	std::vector<TXString> Split(TXString ch) const;

	//***********************************************************************************
	// Conversion to and from numerics
	//***********************************************************************************
	Sint32 atoi() const;
	Sint64 atoi64() const;
	Real64 atof() const;
	TXString& itoa(Sint64 value);
	TXString& ftoa(Real64 value);
	TXString& ftoa(Real64 value, Sint32 precision);
	bool 			IsCompleteNumber();
	static TXString	ToStringInt(Sint64 value);
	static TXString	ToStringInt(Sint64 value, Sint32 width, wchar_t paddingChar);
	static TXString	ToStringReal(Real64 value);
	static TXString	ToStringReal(Real64 value, Sint32 precision, bool fixed = true);
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

	// Compare parts
	bool EndsWith(const TXString &suffix) const;

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
	static TXString		Formatted(const TXString& format, const T0& val0) { return TXString().Format(format, val0); }
	template<typename T0, typename T1>
	static TXString		Formatted(const TXString& format, const T0& val0, const T1& val1) { return TXString().Format(format, val0, val1); }
	template<typename T0, typename T1, typename T2>
	static TXString		Formatted(const TXString& format, const T0& val0, const T1& val1, const T2& val2) { return TXString().Format(format, val0, val1, val2); }
	template<typename T0, typename T1, typename T2, typename T3>
	static TXString		Formatted(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3) { return TXString().Format(format, val0, val1, val2, val3); }
	template<typename T0, typename T1, typename T2, typename T3, typename T4>
	static TXString		Formatted(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4) { return TXString().Format(format, val0, val1, val2, val3, val4); }
	template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
	static TXString		Formatted(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5) { return TXString().Format(format, val0, val1, val2, val3, val4, val5); }
	template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	static TXString		Formatted(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5, const T6& val6) { return TXString().Format(format, val0, val1, val2, val3, val4, val5, val6); }

	// Swap function
	void swap(TXString& rhs);

	// Hash function
	size_t hash() const { return std::hash<std::u16string>{}(*(std::u16string*)(&stdUStr)); }

	//***********************************************************************************
	// Private members
	//***********************************************************************************
private:
	StdUStr stdUStr;

	void SetStdUStrFromCharBuffer(const char* src, size_t len = -1, ETXEncoding e = ETXEncoding::eUTF8);

	// For char buffer. TXString might be better to return a std::string instead of
	// returning const char* in the future.
	mutable char* charPtr;
	mutable size_t charBufSize;
	void PrepareCharBuffer(ETXEncoding e = ETXEncoding::eUTF8) const;

#if GS_MAC || GS_LIN
	mutable std::wstring wStr;
#endif

};
typedef std::vector<TXString> TXStringArray;


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

#endif  // _GSSTRINGX_
}

namespace std {
template <>
struct hash<VectorworksMVR::TXString>
{
    std::size_t operator()(const VectorworksMVR::TXString& s) const
    {
        return s.hash();
    }
};
}
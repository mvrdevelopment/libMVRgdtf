#include "stdafx.h"
#include "CppUnitTest.h"
#include "GSString.h"
#include "math.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;


namespace libVectorworksMvrGdtfUnitTestWinDLLTXString
{		
	TEST_CLASS(UnitTestTXString)
	{
	public:
		
		
		/* Constructors and destructors necessary? (TODO, not implemented yet)
		TEST_METHOD(TestFromOtherStringTypeString)
		{
			const string expected("Hard to compare^1234567890ß´üöä+#-.,<°!\"§$%&/()=?`*'_:;>²³{[]}\\~|");
			const string actual("Hard to compare1");
			TXString txExpected(expected);
			TXString txActual(actual);
			Assert::AreEqual(string(txExpected),string(txActual));
		}
		/ TODO
		TEST_METHOD(TestFromOtherStringTypeWString)
		{
			const wstring expected(R"(Hard to compare^1234567890ß´üöä+#-.,<°!"§$%&/()=?`*'_:;>²³{[]}\~|)");
			const wstring actual(R"(Hard to compare2)");
			TXString txExpected(expected);
			TXString txActual(actual);
			Assert::
		}*/


		
		//***********************************************************************************
		// Assignments
		//***********************************************************************************

		TEST_METHOD(CopyAssignmentOperator)
		{

			TXString& operator=(const TXString& src);		// Copy assignment operator
		}
		/*
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
		
		*/
	};
}
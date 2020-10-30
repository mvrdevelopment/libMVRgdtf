//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	This file contains utility functions for the GraphSoft Core.
//

#ifndef _GS_UTIL_
#define _GS_UTIL_

#pragma once

#include "GSTypes.h"

#if _WINDOWS
	#if _MINICAD_EXTERNAL_ || _GSWINSDK_
		#if GS_INTERFACE_FACTORING
			
			#include "QTHeader.h"
			
		#else
			#include "MCTypes.h"
		#endif		
	#endif
#else
	#if TARGET_RT_MAC_CFM
		#include <MacTypes.h>
	#endif
#endif


#if __cplusplus

#if _WINDOWS
	// We are going to define min() and max() as templates; however, at this
	// point, they have already been defined as macros by "windef.h", so we
	// undefined them here.  [DMB, 10/19/95]
	#if defined(min)
		#undef min
	#endif
	#if defined(max)
		#undef max
	#endif
#endif // _WINDOWS

#include <algorithm>

///////////////////////////////////////////////////////////////////////////////
// Macros for unused parameters.  Use these instead of just commenting
// out the parameter name.

#ifdef __AFX_H__
	// MFC defines its own UNUSED macro that does not appear to have the same
	// meaning and use as our own. [DMB 7/27/99]
#else
	#define UNUSED(x)
#endif

#if GS_CLASSIC_SHELL
	#define CLASSIC_ONLY(x) x
#else
	#define CLASSIC_ONLY(x)
#endif

#if _WINDOWS
	#define MAC_ONLY(x)
	#define WIN_ONLY(x)    x
	#define MAC_WIN(m, w)  w
	#ifndef GS_LITTLE_ENDIAN
		#define GS_LITTLE_ENDIAN 1
	#endif
	#ifndef GS_BIG_ENDIAN
		#define GS_BIG_ENDIAN 0
	#endif
#else
	#define MAC_ONLY(x)  x
	#define WIN_ONLY(x)
	#define MAC_WIN(m, w)  m
#endif



inline Bool8 podd(SintptrT x) { return (x & 1) != 0; }

///////////////////////////////////////////////////////////////////////////////
//	Supplementary min and max functions to provide matches for min(x, <constant>).
//
inline int16_t	min(int16_t a,	int16_t b)		{ return a > b ? b : a; } 
inline int32_t	min(int32_t a,	int32_t b)		{ return a > b ? b : a; } 
inline int64_t	min(int64_t a,	int64_t b)		{ return a > b ? b : a; } 
inline size_t	min(size_t a,	size_t b)		{ return a > b ? b : a; } 
#if GS_MAC
inline uint32_t	min(uint32_t a,	uint32_t b)		{ return a > b ? b : a; }  //X64PRJ_REVISIT Miriam - Mac seemed to need this; but in Win it produced size_t conflict
#endif
inline float	min(float a,	float b)		{ return a > b ? b : a; }
inline double	min(double a,	double b)		{ return a > b ? b : a; }
//inline float	min(double a,	float b)		{ return (float)a > b ? b : (float)a; }
//inline float	min(float a,	double b)		{ return a > (float)b ? (float)b : a; }
//inline float	min(float a,	float b)		{ return a > b ? b : a; }

inline int16_t	max(int16_t a,	int16_t b)		{ return b > a ? b : a; } 
inline int32_t	max(int32_t a,	int32_t b)		{ return b > a ? b : a; } 
inline int64_t	max(int64_t a,	int64_t b)		{ return b > a ? b : a; } 
inline size_t	max(size_t a,	size_t b)		{ return b > a ? b : a; } 
inline float	max(float a,	float b)		{ return b > a ? b : a; }
inline double	max(double a,	double b)		{ return b > a ? b : a; }
//inline float	max(double a,	float b)		{ return (float)a > b ? b : (float)a; }
//inline float	max(float a,	double b)		{ return a > (float)b ? (float)b : a; }
//inline float	max(float a,	float b)		{ return a > b ? b : a; }

inline int32_t min(int16_t a, int32_t b)  { return min((int32_t) a, b); }
inline int32_t min(int32_t a, int16_t b)  { return min(a, (int32_t) b); }
inline int64_t min(int64_t a, int32_t b)  { return min(a, (int64_t) b); }
inline int64_t min(int32_t a, int64_t b)  { return min((int64_t) a, b); }

inline int32_t max(int16_t a, int32_t b)  { return max((int32_t) a, b); }
inline int32_t max(int32_t a, int16_t b)  { return max(a, (int32_t) b); }
inline int64_t max(int64_t a, int32_t b)  { return max(a, (int64_t) b); }
inline int64_t max(int32_t a, int64_t b)  { return max((int64_t) a, b); }

///////////////////////////////////////////////////////////////////////////////
//	PIN template function (constrains input v to be in the interval [lo, hi].)
//

template <class T1, class T2, class T3>
inline T1 PIN(const T1& v, const T2& lo, const T3& hi)
	{ return (v < (T1)lo) ? (T1)lo : (v >(T1) hi) ? (T1)hi : v; }


/*
template <class T>
inline const T& PIN(const T& v, const T& lo, const T& hi)
	{ return (v < lo) ? lo : (v > hi) ? hi : v; }

template <class IntegralType>
inline IntegralType PIN(IntegralType v, Sint32 lo, Sint32 hi)
	{ return (v < (IntegralType)lo) ? (IntegralType) lo : (v > (IntegralType)hi) ? (IntegralType) hi : v; }

inline Sint32 PIN(Sint32 v, Sint32 lo, Sint32 hi)
	{ return (v < lo) ? lo : (v > hi) ? hi : v; }
*/

inline Sint32 PIN(Sint32 v, Sint32 lo, Sint32 hi, Bool8& outWasPinned)
{
	Sint32 result = (v < lo) ? lo : (v > hi) ? hi : v;
	outWasPinned = (v == result) ? false : true;
	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	Casting macros (can be used as l-values.)
// Do not use these unless you need them. Do not use them for convenience.
// If you think you need to cast, try const_cast, static_cast, or static_cast.

#define CAST(Type, thing)	(*((Type *) &(thing)))
#define CAST_SHORT(x)		(*((short *) &(x)))
#define CAST_LONG(x)		(*((Sint32 *) &(x)))


///////////////////////////////////////////////////////////////////////////////

union HiLo {
#if GS_LITTLE_ENDIAN
	struct	{ short lo, hi; } shortWord;
	Sint32	longWord;
#else
	struct	{ short hi, lo; } shortWord;
	Sint32	longWord;
#endif
};	// Used for extracting short words from Sint32 words. THIS IS MACHINE DEPENDENT.

inline const short HiWrd(const Sint32& x) { return ((const HiLo *) &x)->shortWord.hi; }
inline const short LoWrd(const Sint32& x) { return ((const HiLo *) &x)->shortWord.lo; }
inline short& HiWrd(Sint32& x) { return ((HiLo *) &x)->shortWord.hi; }
inline short& LoWrd(Sint32& x) { return ((HiLo *) &x)->shortWord.lo; }
// XXX_JDW_MISC - maybe make a << and >> version called HighWord and LowWord that might be faster for some purposes

// See also PinToCoord in MCCoordTypes.h

///////////////////////////////////////////////////////////////////////////////
template<class A, class B, class C> 
inline bool inrange(A value, B lowerBound, C upperBound)
	{ return (value >= lowerBound && value <= upperBound); }

inline void ClipTop(short &x, short upperBound) { if (x > upperBound) x = upperBound; }
inline void ClipTop(Sint32  &x, Sint32  upperBound) { if (x > upperBound) x = upperBound; }
inline void ClipBottom(short &x, short lowerBound) { if (x < lowerBound) x = lowerBound; }
inline void ClipBottom(Sint32  &x, Sint32  lowerBound) { if (x < lowerBound) x = lowerBound; }

inline void ClipNum(short &x, short lowerBound, short upperBound)
	{ if (x < lowerBound) x = lowerBound; else if (x > upperBound) x = upperBound; }

inline void ClipNum(Sint32 &x, Sint32 lowerBound, Sint32 upperBound)
	{ if (x < lowerBound) x = lowerBound; else if (x > upperBound) x = upperBound; }

inline void ClipNum(double &x, double lowerBound, double upperBound)
	{ if (x < lowerBound) x = lowerBound; else if (x > upperBound) x = upperBound; }

///////////////////////////////////////////////////////////////////////////////

// Translate the bit position of a bit in a Motorola Sint32 to its position in
// a native Sint32.  [DMB, 6/15/95]
inline void TranslateBitPosition32(Sint32 *pBit)
{
	#if GS_LITTLE_ENDIAN
		// Translate the bit position of a bit in a big endian Sint32 to its
		// position in an little endian Sint32.
		if (*pBit < 8)		 *pBit += 24;
		else if (*pBit < 16) *pBit +=  8;
		else if (*pBit < 24) *pBit -=  8;
		else				 *pBit -= 24;
	#else
		// Translate the bit position of a bit in a Motorola Sint32 to its
		// position in a Motorola Sint32.
		// #pragma unused(pBit)
	#endif
}
//
// Work on Motorola byte order.
inline void		pbitclear(Sint32 &x, Sint32 bit)	{ x &= ~(1L << (bit&31)); }
inline Bool8	pbittest(Sint32 x, Sint32 bit)		{ return (x & (1L << (bit&31))) != 0; }
inline void		pbitset(Sint32 &x, Sint32 bit)		{ x |= (1L << (bit&31)); }
//
// Work on native byte order.
inline void		_pbitclear(Sint32 &x, Sint32 bit)	{ TranslateBitPosition32(&bit); pbitclear(x,bit); }
inline Bool8	_pbittest(Sint32 x, Sint32 bit)		{ TranslateBitPosition32(&bit); return pbittest(x,bit); }
inline void		_pbitset(Sint32 &x, Sint32 bit)		{ TranslateBitPosition32(&bit); pbitset(x,bit); }


/* for portability, different ways of expressing a char w/ all 1's */
#if _WINDOWS
	#define CHAR0xFF	('\xFF')
#else
	#define CHAR0xFF	(0xFF)
#endif


///////////////////////////////////////////////////////////////////////////////
// --- Sets

typedef Uint32 Set32;
typedef unsigned short Set16;
typedef unsigned char Set8;

Bool8 _setmember(Sint32 c, ...);


// 4/25/00 - JDW
template<class X, class T> inline bool setmember(X x, T a, T b)
	{ return (x == a || x == b); }
template<class X, class T> inline bool setmember(X x, T a, T b, T c)
	{ return (x == a || x == b || x == c); }
template<class X, class T> inline bool setmember(X x, T a, T b, T c, T d)
	{ return (x == a || x == b || x == c || x == d); }
template<class X, class T> inline bool setmember(X x, T a, T b, T c, T d, T e)
	{ return (x == a || x == b || x == c || x == d || x == e); }
template<class X, class T> inline bool setmember(X x, T a, T b, T c, T d, T e, T f)
	{ return (x == a || x == b || x == c || x == d || x == e || x == f); }
template<class X, class T> inline bool setmember(X x, T a, T b, T c, T d, T e, T f, T g)
	{ return (x == a || x == b || x == c || x == d || x == e || x == f || x == g); }
template<class X, class T> inline bool setmember(X x, T a, T b, T c, T d, T e, T f, T g, T h)
	{ return (x == a || x == b || x == c || x == d || x == e || x == f || x == g || x == h); }
template<class X, class T> inline bool setmember(X x, T a, T b, T c, T d, T e, T f, T g, T h, T i)
	{ return (x == a || x == b || x == c || x == d || x == e || x == f || x == g || x == h || x == i); }
template<class X, class T> inline bool setmember(X x, T a, T b, T c, T d, T e, T f, T g, T h, T i, T j)
	{ return (x == a || x == b || x == c || x == d || x == e || x == f || x == g || x == h || x == i || x == j); }
template<class X, class T> inline bool setmember(X x, T a, T b, T c, T d, T e, T f, T g, T h, T i, T j, T k)
	{ return (x == a || x == b || x == c || x == d || x == e || x == f || x == g || x == h || x == i || x == j || x == k); }
template<class X, class T> inline bool setmember(X x, T a, T b, T c, T d, T e, T f, T g, T h, T i, T j, T k, T l)
	{ return (x == a || x == b || x == c || x == d || x == e || x == f || x == g || x == h || x == i || x == j || x == k || x == l); }
template<class X, class T> inline bool setmember(X x, T a, T b, T c, T d, T e, T f, T g, T h, T i, T j, T k, T l, T m)
	{ return (x == a || x == b || x == c || x == d || x == e || x == f || x == g || x == h || x == i || x == j || x == k || x == l || x == m); }
template<class X, class T> inline bool setmember(X x, T a, T b, T c, T d, T e, T f, T g, T h, T i, T j, T k, T l, T m, T n)
	{ return (x == a || x == b || x == c || x == d || x == e || x == f || x == g || x == h || x == i || x == j || x == k || x == l || x == m || x == n); }
template<class X, class T> inline bool setmember(X x, T a, T b, T c, T d, T e, T f, T g, T h, T i, T j, T k, T l, T m, T n, T o)
	{ return (x == a || x == b || x == c || x == d || x == e || x == f || x == g || x == h || x == i || x == j || x == k || x == l || x == m || x == n || x == o); }


/* Set of 0..2047 */
class IntegerSet {
	private:
		enum { numLongs = 64 } ;
		enum { maxElement = numLongs * 32 - 1 } ;
		Sint32	bits[numLongs];
	public:
		IntegerSet();
		IntegerSet(short i0, short i1 = -1, short i2 = -1, short i3 = -1,
					short i4 = -1, short i5 = -1, short i6 = -1, short i7 = -1,
					short i8 = -1, short i9 = -1);
		IntegerSet(const IntegerSet &s);
		
		Bool8 contains(short i) const;
		void operator +=(short i);
		void operator +=(const IntegerSet &s);
		void operator -=(short i);
		void operator -=(const IntegerSet &s);
		IntegerSet& operator =(const IntegerSet &s);
};

Boolean OSIsMetric();

/////////////////////////
// TernaryXOR - 
// Returns true iff only one of the three values is true, otherwise false
/////////////////////////

inline bool TernaryXOR(bool a, bool b, bool c)
{
    return (!a && (b ^ c)) || (a && !(b || c));
}

/////////////////////////
// Cross-Platform byte swapping functions
/////////////////////////


// for ByteSwap conversion direction parameter
enum EByteSwapDirection {
	kReading,
	kWriting
};




inline void ByteSwapDouble(double *pld)
{
	char t;
	char *pb1 = (char *) pld;
	char *pb2 = pb1 + sizeof(Real64) - 1;
	while (pb2 > pb1) {
		t = *pb1;
		*pb1 = *pb2;
		*pb2 = t;
		++pb1;
		--pb2;
	}
}



inline void ByteSwapFloat(float *pf)
{
	char t;
	char *pb1 = (char *) pf;
	char *pb2 = pb1 + sizeof(float) - 1;
	while (pb2 > pb1) {
		t = *pb1;
		*pb1 = *pb2;
		*pb2 = t;
		++pb1;
		--pb2;
	}
}

inline void ByteSwapUint64(Uint64 *pld)
{
	char t;
	char *pb1 = (char *) pld;
	char *pb2 = pb1 + sizeof(Uint64) - 1;
	while (pb2 > pb1) {
		t = *pb1;
		*pb1 = *pb2;
		*pb2 = t;
		++pb1;
		--pb2;
	}
}

inline void ByteSwapUint32(Uint32 *pld)
{
	char t;
	char *pb1 = (char *) pld;
	char *pb2 = pb1 + sizeof(Uint32) - 1;
	while (pb2 > pb1) {
		t = *pb1;
		*pb1 = *pb2;
		*pb2 = t;
		++pb1;
		--pb2;
	}
}

inline void ByteSwapLONG(Sint32 *pl)
{
	char t;
	char* p1 = (char*)pl;
	char* p2 = p1 + 3;

	t = *p1;
	*p1 = *p2;
	*p2 = t;

	++p1; --p2;

	t = *p1;
	*p1 = *p2;
	*p2 = t;
}

#if GS_MAC && GS_PLATFORM32
//X64PRJ_REVISIT Hugues // QTREMOVAL
inline void ByteSwapLONG(long *pl)
{
    ByteSwapLONG((Sint32 *)pl);
}
#endif


inline void ByteSwapSHORT(Sint16 *ps)
{
	char *p1 = (char*)ps;
	char *p2 = p1 + 1;
	char t = *p1;
	*p1 = *p2;
	*p2 = t;
}

inline void ByteSwapDWORD(Uint32 *pl)
{
    ByteSwapLONG((Sint32 *)pl);
}

#if GS_MAC && GS_PLATFORM32
//X64PRJ_REVISIT Hugues // QTREMOVAL
inline void ByteSwapDWORD(unsigned long *pl)
{
    ByteSwapLONG((Sint32 *)pl);
}
#endif

inline void ByteSwapWORD(Uint16 *ps)
{
    ByteSwapSHORT((Sint16 *)ps);
}
	
inline Uint32 TruncatePointer(const void* ptr)
{
    return (Uint32)((UintptrT)ptr); //-V202
}


///////////////////////////////////////////////////////////////////////////////
//	Casting related functions.

// Intended use of DemoteTo, Trunctate, Round and PinTo.
//
// The DemoteTo casting function is intended to be used in any case where a cast is performed between numerical types in such a way
// that data can be lost depending on the value of the variable being cast. The .NET compiler on Windows will generate a warning or error
// in these cases if the cast is not explicit. 
//
// Rather than using an explicit cast to satisfy these cases, VectorWorks code is required to use the DemoteTo function as follows:
//
//      shortVariable = (short)longVariable;  //NOT PREFERRED
//
//      shortVariable = DemoteTo<short>(kVictor, longVariable);  //PREFERRED
//
// This allows the DemoteTo function to perform rigorous runtime checks to prevent unexpected data values from going unnoticed
// and causing subtle or serious functional problems.
//
// Cases where DemoteTo must be used:
// 
//     floating point to integer
//         (double to Sint32)
//     signed integer to unsigned integer of any size
//         (char to Uint32)
//     unsigned integer to signed integer of the same or smaller size
//         (unsigned short to short)
//     larger integer to smaller integer
//         (Sint32 to short or short to char)
//     larger floating point to smaller floating point
//         (double to float)
//     Sint32 integer to short floating point
//         (Sint32 to float)
// 
// Cases where a DemoteTo should not be used:
// 
//     integer to floating point
//         (Sint32 to double)
//     integer to boolean
//         (Sint32 to bool)
//     smaller integer to larger integer
//         (short to Sint32)
//     assignments between like types
//         (Sint32 to Sint32)
//     shorter floating point to longer floating point
//         (float to double)
//     non-numeric types
//         (handles, classes, strings, etc.)
//
// An important side effect of this requirement is that you understand that casting alone can no longer be used to intentionally
// truncate floating point values or pin or wrap integer values. The value passed into the DemoteTo function must be exactly
// representable by the destination variable or a runtime ASSERT message will be generated, which is unacceptable and must be
// fixed. The one exception to this is that normal roundoff errors due to the inability of shorter floating point types to represent longer
// floating point numbers are ignored:
//
//     longVariable = DemoteTo<Sint32>(kVictor, doubleVariable); 
//            This case is OK only if the value in doubleVariable is constrained to be in the range MINLONG to MAXLONG and has no
//            fractional component. e.g. it's illegal to pass 10.5 in doubleVariable.
//
//     longVariable = DemoteTo<Sint32>(kVictor, Round(doubleVariable));
//     longVariable = DemoteTo<Sint32>(kVictor, Truncate(doubleVariable));
//            This is more likely the correct way to approach this problem as you are guaranteeing that there is no fractional component.
//
//     longVariable = DemoteTo<Sint32>(kVictor, PinTo<Sint32>(kVictor, doubleVariable));
//            This specifies that the value be pinned either to the maximum or minimum of the destination type's range
//            if it is outside that range.

// NOTE: The Round and Truncate functions are defined in BasicMath.X.h

#include "GSDebug.h"
#include <typeinfo>
#include <limits>

#include <sstream>


#if GS_WIN
#define force_inline __forceinline

#else // mac

#define force_inline inline
#endif

Boolean DoublesAreNotNearlyEqual(double n1, double n2);

force_inline double fastFabs(double d) {return (d >= 0) ? d : -d; }  // six times faster than fabs on Windows (and maybe Intel Mac?) // [MAF 12/22/05]

//---------------------------------------------------------------------------------------
template <typename PinType, typename FromType> 
#if !(GS_MAC && TEST)
inline 
#endif
FromType PinTo(const TProgrammer& TEST_ONLY(toWhom), const FromType fromValue)
//
// Description:
//   Templated function to pin the specified value to the range of the specified pin type.
//
//   - Debug only behavior:
//     - Warns if type size is greater than maximum size
//     - Warns if identical types are being pinned between.
//     - Warns if pin type is larger than source type.
//
// Parameters:
//   toWhom    - input - the programmer to whom any DSTOP messages will be addressed.
//   fromValue - input - the value to be pinned.
//
// Returns:
//   FromType - the pinned value.
//
// Created by Victor Long on 04/09/2004.
//
{

	FromType		toValue;
	const size_t	kMaxByteSize = 8;
	size_t			pinTypeSize = sizeof(PinType);
	size_t			fromTypeSize = sizeof(FromType);
	bool			mayPinValue = true;
	PinType			minPinValue;
	PinType			maxPinValue;

	// Check to see if data type sizes are larger than maximum supported size
	// and if so send DSTOP message.
	if (pinTypeSize > kMaxByteSize || 
		fromTypeSize > kMaxByteSize) {
		mayPinValue = false;

#if TEST
		std::ostringstream outStream;

		outStream << "PINNING WITH LARGER THAN SUPPORTED TYPE. PLEASE STOP AND EVALUATE." << std::endl;
		outStream << std::endl;
		outStream << "Pinning has occured where the size of one or both " << std::endl;
		outStream << "of the source and pin types is greater " << std::endl;
		outStream << "than the pinning function's maximum supported size " << std::endl;
		outStream << "of " << kMaxByteSize << " bytes." << std::endl; //-V128
		outStream << std::endl;
		outStream << "Please remove the use of this pinning function," << std::endl;
		outStream << "or submit a bug that includes steps on how to reproduce this assert." << std::endl;
		outStream << std::endl << std::ends;

		DSTOP((toWhom, "%s", outStream.str().c_str()));
#endif
	}
	// Check to see if data types are identical 
	// and if so send DSTOP message.
	else if (typeid(FromType) == typeid(PinType)) {
		mayPinValue = false;

#if TEST
		std::ostringstream outStream;

		outStream << "PINNING BETWEEN IDENTICAL TYPES. PLEASE STOP AND EVALUATE." << std::endl;
		outStream << std::endl;
		outStream << "Pinning has occurred where no pin should be required." << std::endl;
		outStream << std::endl;
		outStream << "Please remove the use of this pinning function," << std::endl;
		outStream << "or submit a bug that includes steps on how to reproduce this assert." << std::endl;
		outStream << std::endl << std::ends;

		DSTOP((toWhom, "%s", outStream.str().c_str()));
#endif
	}
	// Check to see if casting results in promotion 
	// and if so send DSTOP message.
	else if (!(std::numeric_limits<FromType>::is_signed && !std::numeric_limits<PinType>::is_signed) &&
			 sizeof(PinType) > sizeof(FromType)) {
		mayPinValue = false;

#if TEST
		std::ostringstream outStream;
	
		outStream << "PINNING TO LARGER TYPE. PLEASE STOP AND EVALUATE." << std::endl;
		outStream << std::endl;
		outStream << "Pinning has occured where no pin should be required." << std::endl;
		outStream << std::endl;
		outStream << "Please remove the use of this pinning function," << std::endl;
		outStream << "or submit a bug that includes steps on how to reproduce this assert." << std::endl;
		outStream << std::endl << std::ends;

		DSTOP((toWhom, "%s", outStream.str().c_str()));
#endif
	}

	maxPinValue = std::numeric_limits<PinType>::max ();

	if (std::numeric_limits<PinType>::is_integer) {
		minPinValue = std::numeric_limits<PinType>::min ();
	}
	else {
		minPinValue = -std::numeric_limits<PinType>::max ();
	}
			 
	if (mayPinValue &&
		fromValue > maxPinValue) {
		toValue = maxPinValue;
	}
	else if (mayPinValue &&
			 fromValue < minPinValue) {
		toValue = minPinValue;
	}
	else {
		toValue = fromValue;
	}

	return toValue;
}

#if TEST
// Check for floating point loss during DemoteTo.  RBerge 08/27/2013.
//
// Split from DemoteTo so DemoteTo works with x64 data types.
// If needed, this can be specialized so e.g. OtherType == Uint64 is a noop, to prevent compiler warning
template <typename RealType, typename OtherType> 
#if !(GS_MAC && TEST)
inline 
#endif
bool DemotionDoubleTest(const RealType& realValue, const OtherType& otherValue)
{
	#if _WINDOWS
	#pragma warning ( push )
	#pragma warning( disable : 4244 ) // conversion from 'size_t' to 'double', possible loss of data.  The check itself will tell us.
	#endif
	return DoublesAreNotNearlyEqual (realValue, otherValue);
	#if _WINDOWS
	#pragma warning ( pop )
	#endif
}
#endif

//---------------------------------------------------------------------------------------
template <typename ToType, typename FromType> 
#if !(GS_MAC && TEST)
inline 
#endif
ToType DemoteTo(const TProgrammer& TEST_ONLY(toWhom), const FromType fromValue)
//
// Description:
//   Templated function to cast one data type to another.
//
//   - Debug only behavior:
//     - Warns if type size is greater than maximum size
//     - Warns if identical types are being cast between.
//     - Warns if value is actually being promoted, not demoted.
//     - Warns if loss of data has occurred.
//
// Parameters:
//   toWhom    - input - the programmer to whom any DSTOP messages will be addressed.
//   fromValue - input - the value to be cast from.
//
// Returns:
//   ToType - the value of the cast input value.
//
// Created by Victor Long on 03/31/2004.
//
{
	ToType toValue;

	// The input value is ALWAYS cast and returned.
	// This is to preserve existing casting behavior where this function is used.
	toValue = (ToType) fromValue;

#if TEST
	// This debug only section evaluates the casting operation
	// for certain problems (see function description above).

	const size_t	kMaxByteSize = 8;
	size_t			toTypeSize = sizeof(ToType);
	size_t			fromTypeSize = sizeof(FromType);
	bool			castingResultsInLossOfData = false;

	// Check to see if data type sizes are larger than maximum supported size
	// and if so send DSTOP message.
	if (toTypeSize > kMaxByteSize || 
		fromTypeSize > kMaxByteSize) {
		std::ostringstream outStream;
	
		outStream << "CASTING WITH LARGER THAN SUPPORTED TYPE. PLEASE STOP AND EVALUATE." << std::endl;
		outStream << std::endl;
		outStream << "Casting has occured where the size of one or both " << std::endl;
		outStream << "of the source and destination types is greater " << std::endl;
		outStream << "than the casting function's maximum supported size " << std::endl;
		outStream << "of " << kMaxByteSize << " bytes." << std::endl; //-V128
		outStream << std::endl;
		outStream << "Please remove the use of this casting function," << std::endl;
		outStream << "or submit a bug that includes steps on how to reproduce this assert." << std::endl;
		outStream << std::endl;
		outStream << "Cast of:" << std::endl;
		outStream << std::endl;
		outStream << "  " << typeid(FromType).name() << "  to  " << typeid(ToType).name() << std::endl;
		outStream << std::endl << std::ends;

		DSTOP((toWhom, "%s", outStream.str().c_str()));
	}
	else if ((typeid(FromType) == typeid(ToType)) && (sizeof(SintptrT) == sizeof(FromType)) && (sizeof(Sint32) == sizeof(ToType))) {
		// For x32, quietly allow SintptrT demote to (same size) Sint32. 
		// For x64, they're different sizes, so this case can't be hit
	}
	// Check to see if data types are identical 
	// and if so send DSTOP message.
	else if (typeid(FromType) == typeid(ToType)) {
		std::ostringstream outStream;
	
		outStream << "CASTING BETWEEN IDENTICAL TYPES. PLEASE STOP AND EVALUATE." << std::endl;
		outStream << std::endl;
		outStream << "Casting has occured where no cast should be required." << std::endl;
		outStream << std::endl;
		outStream << "Please remove the use of this casting function," << std::endl;
		outStream << "or submit a bug that includes steps on how to reproduce this assert." << std::endl;
		outStream << std::endl;
		outStream << "Cast of:" << std::endl;
		outStream << std::endl;
		outStream << "  " << typeid(FromType).name() << "  to  " << typeid(ToType).name() << std::endl;
		outStream << std::endl << std::ends;

		DSTOP((toWhom, "%s", outStream.str().c_str()));
	}
	// Check to see if casting results in promotion 
	// and if so send DSTOP message.
	else if (!(std::numeric_limits<FromType>::is_signed && !std::numeric_limits<ToType>::is_signed) &&
			 sizeof(ToType) > sizeof(FromType)) {
		std::ostringstream outStream;

		outStream << "CASTING RESULTS IN PROMOTION. PLEASE STOP AND EVALUATE." << std::endl;
		outStream << std::endl;
		outStream << "Casting has occured where no cast should be required." << std::endl;
		outStream << std::endl;
		outStream << "Please remove the use of this casting function," << std::endl;
		outStream << "or submit a bug that includes steps on how to reproduce this assert." << std::endl;
		outStream << std::endl;
		outStream << "Cast of:" << std::endl;
		outStream << std::endl;
		outStream << "  " << typeid(FromType).name() << "  to  " << typeid(ToType).name() << std::endl;
		outStream << std::endl << std::ends;

		DSTOP((toWhom, "%s", outStream.str().c_str()));
	}
	
	// Always check for loss of data due to casting
	// and if so send DSTOP message.
	if (std::numeric_limits<FromType>::is_integer || std::numeric_limits<ToType>::is_integer) {
		if (fromValue != toValue) {
			castingResultsInLossOfData = true;
		}
	}
	// check if floating point loss.
	// X64 RBerge - Split out to a separate template so template instantiation isn't blindly casting e.g. Uint64 to double when compiling these statements
	else if (std::numeric_limits<FromType>::is_integer && !std::numeric_limits<ToType>::is_integer && DemotionDoubleTest (toValue, fromValue)) {
		castingResultsInLossOfData = true;
	}
	else if (std::numeric_limits<ToType>::is_integer && !std::numeric_limits<FromType>::is_integer && DemotionDoubleTest (fromValue, toValue)) {
		castingResultsInLossOfData = true;
	}

	if (castingResultsInLossOfData) {
		std::ostringstream outStream;

		outStream << "CASTING RESULTS IN LOSS OF DATA. PLEASE STOP AND EVALUATE." << std::endl;
		outStream << std::endl;
		outStream << "Casting has caused a loss of data." << std::endl;
		outStream << std::endl;
		outStream << "Please evaluate this cast to determine what may be done to fix this error," << std::endl;
		outStream << "or submit a bug that includes steps on how to reproduce this assert." << std::endl;
		outStream << std::endl;
		outStream << "Cast of:" << std::endl;
		outStream << std::endl;
		outStream << "  " << typeid(FromType).name() << "  to  " << typeid(ToType).name() << std::endl;
		outStream << std::endl;
		outStream << "Has changed value from:" << std::endl;
		outStream << std::endl;
		outStream << "  " << fromValue << "  to  " << toValue << std::endl << std::ends;

		DSTOP((toWhom, "%s", outStream.str().c_str()));
	}
#endif // #if TEST #else !TEST
    
	// Return cast input value.
	return toValue;
}

template <typename ToType, typename FromType>
#if !(GS_MAC && TEST)
inline 
#endif
ToType CastToPointer(const TProgrammer& TEST_ONLY(toWhom), const FromType fromValue){
	ToType toValue;
	
	toValue = reinterpret_cast<ToType>(static_cast<uintptr_t>(fromValue));
	return toValue;
}

template <typename ToType, typename FromType>
#if !(GS_MAC && TEST)
inline 
#endif
ToType CastFromPointer(const TProgrammer& TEST_ONLY(toWhom), const FromType fromValue){
	ToType toValue;
	
	toValue = static_cast<ToType>(reinterpret_cast<uintptr_t>(fromValue));
	return toValue;
}

#endif // __cplusplus

#endif // _GS_UTIL_

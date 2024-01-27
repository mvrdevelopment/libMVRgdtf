//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	Declares most of the standard floating point data types used
//	in MiniCad & external code.
//


#ifndef _MCFLOAT_
#define _MCFLOAT_

#pragma once

#include <cfloat>

// XXX_JDW_ALTURA CLEANUP [2003-05-15]
#if GS_WIN
#include <math.h> // Want non-std defs of fabs, etc. for consistency with Windows,
#else
#include <cmath>
#endif
				//  so use this instead of <math.h> or <cmath>.  Also provides
                 //  80-bit floating-point functions.   MFH 03/01
// TODO before included <fp.h> for the Mac. Non-existant now in GCC.
#include "GSUtil.h"

// short double			64 bits
// double				64 bits
// long double			64 bits

namespace VectorworksMVR
{
	typedef Real64			double_gs;
	typedef Real32			float_gs;

#define double80(x)  Real64 x; short x##_pad

	typedef const float_gs	float_param;
	typedef const double_gs	double_param;


	/* The following functions and classes convert the ten bytes pointed to between an 80-bit number and
		a 64-bit number with 16 bits of padding on the end.  USE WITH EXTREME CAUTION!
	*/

	//////////////////////////
	// extended80_gs
	//////////////////////////
	//
	//	extended80_gs is Diehl Graphsoft's standard 80-bit floating point raw data storage type.
	//	
	//	On 68k platforms, it is a natively-supported extended.
	//	
	//	On all other platforms it is a structure containing 10 bytes which must be specifically
	//	converted to a floating point value before use. The Extended80 class is intended to
	//	do this transparently in most instances.
	//
	//	In some isolated cases, extended80_gs can be used directly, but great care must be used
	//	to access it correctly or you will get incorrect results.
	//
	//	extended80_gs can be freely cast to and from the Macintosh extended80 type, but we no longer
	//	use that type directly in order to achieve greater platform independence.
	//

	struct extended80_gs { short w[5]; };
	typedef struct extended80_gs extended80_gs;



#if GS_LITTLE_ENDIAN
#if GS_MAC
	double	GS_API x80todNNA(const extended80 *x80);
	void	GS_API dtox80NNA(const double *x, extended80 *x80);
#else
	/* These functions are defined in the 2.0 version of fp.x, but the Windows folk
		are still using 1.0, so they're defined here.  This bit should be removed
		when everyone is using Universal Headers 2.0.
	*/
	double	GS_API x80tod(const extended80_gs *x80);
	void	GS_API dtox80(const double *x, extended80_gs *x80);
#endif
#else
	// PowerMac versions of these are provided by the system and take a true extended80
#endif

#if BUG

	inline void ASSERT4BYTEALIGNMENT(const void *p, const char *name)
	{
		if (((size_t)p % 4) != 0)
			DSTOP((kBruce, "Misaligned floating point access to %s - SERIOUS PERFORMANCE PENALTY!", name));
	}
#define ASSERT4BYTEALIGNMENT(p, s) ASSERT4BYTEALIGNMENT(p, s)

#else

#define ASSERT4BYTEALIGNMENT(p, s) DEBUG_DO_NOTHING

#endif


//----------------------------------------------------------------------------------------

// I've decided to add a fudge factor below because WorldToViewCoordX, for example,
// would wind up with a value of 52.49999999999994 when using the speed factors 
// WorldToViewXOffset and WorldToViewFactor, but would come up with the value of
// exactly 52.5 when calculated using the more drawn out (but mathematically identical)
// method. This was causing some unsightly one pixel off drawing behaviors.
//
// I put the additive factor at the 10th digit because doubles have 15 digits of precision 
// and a short can have 5 digits to the left of the decimal point, so this should fix
// one off problems even for even very large short values. I can't believe a number like 
// 52.49999999999994 comes through here very often that actually needs to be rounded 
// down to 52. It's much more likely that it "means to be" 52.5.
//
// I'm not as comfortable doing this for DoubleToLong, so I'm not going to unless the need
// presents itself. [MAF 8/18/00]


	BUG_ONLY(void AssertNum2Short(double x));

	force_inline short Num2Short(double x)
{
	BUG_ONLY(AssertNum2Short(x));

	return (x >  32767) ? (short)  32767     :
	       (x < -32767) ? (short) -32767     :
		   (x >  0)     ? (short)  (x + 0.5000000001) :
		   (x <  0)     ? (short)  (x - 0.5000000001) :
					      (short)  0;
}

//----------------------------------------------------------------------------------------

	BUG_ONLY(void AssertDoubleToLong(double x));

	inline Sint32 DoubleToLong(double x)
{
	BUG_ONLY(AssertDoubleToLong(x));

	return (x > INT32_MAX) ? (Sint32)	INT32_MAX :
	       (x <	INT32_MIN) ? (Sint32)	INT32_MIN:
		   (x >  0)			 ? (Sint32)  (x + 0.5)  :
		   (x <  0)			 ? (Sint32)  (x - 0.5)  :
							   (Sint32)  0;
}

//----------------------------------------------------------------------------------------

	// XXX_JDW_ALTURA [2003-05-14] - are we using full precision on windows? maybe our 
	// settings should be adjusted so mac and windows have the same floating point behaviors
	/*
	"Floating-point precision of intermediate values is controlled by the _controlfp.
	 By default, _controlfp's precision control is set to 53 bits (_PC_53).
	 Linking with FP10.OBJ changes the default precision control to 64 bits (_PC_64).
	 On the linker command line, FP10.OBJ must appear before LIBC.LIB, LIBCMT.LIB, or MSVCRT.LIB."*/


	 ////////////////////////////////////////
#if _WINDOWS
////////////////////////////////////////

/*
C9X FUNCTION	MICROSOFTEQUIVALENT
copysign()		_copysign()
fmax()			__max()
fmin()			__min()
fpclassify()	_fpclass()
hypot()			_hypot()
isfinite()		_finite()
isnan()			_isnan()
logb()			_logb()
nextafter()		_nextafter()
scalb()			_scalb
*/

// from Apple's fp.h


// Decimal numbers

#define      FLOATDECIMAL   ((char)(0))
#define      FIXEDDECIMAL   ((char)(1))

// XXX_JDW_ALTURA [2003-05-14] - maybe change this to 36 like Mac version
#define SIGDIGLEN      20

	struct decimal {
		char                            sgn;                        /* sign 0 for +, 1 for - */
		char                            unused;
		short                           exp;                        /* decimal exponent */
		struct {
			unsigned char                   length;
			unsigned char                   text[SIGDIGLEN];        /* significant digits */
			unsigned char                   unused;
		}                               sig;
	};

	struct decform {
		char                            style;                      /*  FLOATDECIMAL or FIXEDDECIMAL */
		char                            unused;
		short                           digits;
	};

	void   num2dec(const decform *f, double x, decimal *d);
	double dec2num(const decimal *d);

	// Relational operators

typedef short relop;											/*	relational operator	*/
enum {
	GREATERTHAN = ( ( relop ) ( 0 ) ),
	LESSTHAN,
	EQUALTO,
	UNORDERED
	};


	// Floating point classification

#define	DOUBLE_SIZE		8

enum {
    FP_SNAN                     = 3,                            /*      signaling NaN                         */
    FP_QNAN                     = 4,                            /*      quiet NaN                             */
};


inline bool IsNAN		(double v) { return _isnan(v)!=0; }
inline bool IsFinite	(double v) { return _finite(v)!=0; }
inline bool IsInfinite	(double v) { return !_finite(v)==0; }
	   Sint32 FPClassify	(double v);

////////////////////////////////////////
#elif _LINUX
////////////////////////////////////////

// from Apple's fp.h


// Decimal numbers

#define      FLOATDECIMAL   ((char)(0))
#define      FIXEDDECIMAL   ((char)(1))

// XXX_JDW_ALTURA [2003-05-14] - maybe change this to 36 like Mac version
#define SIGDIGLEN      20

	struct decimal {
		char                            sgn;                        /* sign 0 for +, 1 for - */
		char                            unused;
		short                           exp;                        /* decimal exponent */
		struct {
			unsigned char                   length;
			unsigned char                   text[SIGDIGLEN];        /* significant digits */
			unsigned char                   unused;
		}                               sig;
	};

	struct decform {
		char                            style;                      /*  FLOATDECIMAL or FIXEDDECIMAL */
		char                            unused;
		short                           digits;
	};

	void   num2dec(const decform *f, double x, decimal *d);
	double dec2num(const decimal *d);

	// Relational operators

typedef short relop;											/*	relational operator	*/
enum {
GREATERTHAN = ( ( relop ) ( 0 ) ),
LESSTHAN,
EQUALTO,
UNORDERED
	};


	// Floating point classification

#define	DOUBLE_SIZE		8

enum {
   FP_SNAN                     = 3,                            /*      signaling NaN                         */
   FP_QNAN                     = 4,                            /*      quiet NaN                             */
};
inline bool IsNAN 		(double v) { return	std::isnan(v); }
inline bool IsFinite	(double v) { return std::isfinite(v); }
inline bool IsInfinite	(double v) { return !std::isfinite(v); }
inline Sint32 FPClassify	(double v) { return std::fpclassify(v); }

////////////////////////////////////////
#else // Mac
////////////////////////////////////////

inline bool IsNAN 		(double v) { return	std::isnan(v); }
inline bool IsFinite	(double v) { return std::isfinite(v); }
inline bool IsInfinite	(double v) { return !std::isfinite(v); }
inline Sint32 FPClassify	(double v) { return std::fpclassify(v); }

////////////////////////////////////////
#endif
////////////////////////////////////////

// note - denormal numbers are numbers that are almost zero; on some platforms calculations on denormal
// numbers are done in software emulation instead of on the chip, making them much slower. 

inline bool IsLegal				(double v) { return  setmember(FPClassify(v), (Sint32)FP_NORMAL, (Sint32)FP_SUBNORMAL, (Sint32)FP_ZERO); }
inline bool IsIllegal			(double v) { return !setmember(FPClassify(v), (Sint32)FP_NORMAL, (Sint32)FP_SUBNORMAL, (Sint32)FP_ZERO); }
inline bool IsZeroOrDenormal	(double v) { return  setmember(FPClassify(v), (Sint32)FP_ZERO, (Sint32)FP_SUBNORMAL); }


/////////////////////////
	// Cross-Platform byte swapping & conversion functions
	/////////////////////////

	void GS_API ByteSwapEXTENDED80(extended80_gs *p);

	// Moved to GSUtil.h. [MAF 10/10/02]
	// void GS_API ByteSwapDouble(Real64 *p);

	///////////////////
	//
	// ByteSwapDOUBLE80 is really the same as ByteSwapEXTENDED80, but it's used
	// for the types which needed ConvertFP in the past. Since FP types are now
	// stored as 8 byte doubles on disk now, this simply serves as a reminder
	// of how the types differ in older versions of the file format.
	//
	///////////////////

	inline void ByteSwapDOUBLE80(extended80_gs *p) { ByteSwapEXTENDED80(p); }


	//////////////////////////
	//	FP switch enumerations
	//////////////////////////
	// The following allow filing code to be written in a much more human-readable form,
	// which is a bug win since filing is so error prone.
	//

	// for ConvertFP conversion direction parameter
	enum EFPDirection {
		kConvert64to80FP,
		kConvert80to64FP
	};

	// for ConvertFP nativeByteOrder parameter
	enum EFPByteOrder {
		kNeedsByteSwapping,
		kNativeByteOrder
	};

	// for ByteSwap floating point format parameter
	enum EByteSwapFPMode {
		kModernFP,
		kArchaicFP
	};


	//////////////////////////
	//	ByteSwapFP
	//////////////////////////
	// This is the general floating point ByteSwap routine for swapping either
	// 64 or 80 bit floating point values. It swaps either 8 or 10 bytes depending
	// on the fpFormat parameter passed. 
	//


	// Duped from GSUtil.h. Where does this go so theat everyone who needs it can get to it?? [MAF 10/10/02]
inline void ByteSwapDoubleMAF(double *pld)
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




	inline EByteSwapFPMode ByteSwapFPMode(Bool8 archaicDouble)
	{
		if (archaicDouble)
			return kArchaicFP;	// swap 10 byte doubles
		else
			return kModernFP;	// swap 8 byte doubles
	}

	inline void ByteSwapFP(void* fpValue, EByteSwapFPMode fpFormat)
	{
		if (fpFormat == kArchaicFP) {
			ByteSwapDOUBLE80((extended80_gs *)fpValue);
		}
		else {
			ASSERTN(kEveryone, fpFormat == kModernFP);
			ByteSwapDoubleMAF((Real64 *)fpValue);
		}
	}

	//////////////////////////
	//	ConvertFP
	//////////////////////////
	// This is the preferred floating point translation routine for converting between
	// 64 & 80 bit floating point values. It requires the value to be in an 80 bit field
	// because it converts in place. It handles data in native and non-native byte order.
	//

	inline EFPByteOrder ByteOrder(Bool8 needsSwapping)
	{
		return needsSwapping ? kNeedsByteSwapping : kNativeByteOrder;
	}


	/*============================================================================*/

#if GS_WIN
#define Fabs fastFabs

#else // mac

#define Fabs fabs
#endif


	const extern double kNearlyEqualEpsilonForDoubles;
	const extern double kNearlyEqualEpsilonForNormalizedValues;


	//----------------------------------------------------------------------------------------
	//
	// Magnitude-based double Comparison Functions.
	//
	// All double comparisons should use these functions.
	//
	// These double comparison functions are necessary because most floating point numbers
	// that are not whole numbers cannot be represented exactly (they have floating point 
	// approximations). Double precision floating point numbers (doubles) are accurate to 15 
	// digits, but we'll consider doubles equal if they are the same up to the 13th significant 
	// digit (to allow for drift). Note that these functions must and do take the magnitude of the 
	// values into account. 100,000,000,000,000 must be considered equal to 100,000,000,000,001, 
	// and 1.00000000000000 must be considered equal to 1.00000000000001. [MAF 5/20/02]
	//
	// Note this exception: very small numbers that are not relatively close to each other are still
	// considered equal. This prevents us from doing nanocircuit design, but much of our application 
	// depends on this. For example:
	//
	//        1.233     is considered NOT nearly equal to 1.234
	//        1.233e+15 is considered NOT nearly equal to 1.234e+15
	//    but 1.233e-15 IS considered     nearly equal to 1.234e-15,
	//
	// because parts of our application need values that are very nearly zero to be considered zero.
	//
	//----------------------------------------------------------------------------------------
	force_inline Boolean DoublesAreNearlyEqual(const double& n1, const double& n2,
		double epsilon = kNearlyEqualEpsilonForDoubles)
	{
		//  return (Abs(1 - (n2 / n1)) < epsilon);

			// Factor out the division for speed and div0. Also, always use the 
			// larger value * epsilon so that DoublesAreNearlyEqual(x,y) == DoublesAreNearlyEqual(y,x)
		// IFed out     by JDW 2003-11-20 - fails if you have very different very small numbers (ie 1/parsecs == 1/lightyears in dxf units testing)
		// IFed back in by JDW 2003-12-23 - fails if you use create rectangle and enter .5 tab .5 tab .5 tab - first no longer displays as fraction
		double abs_n1 = Fabs(n1);
		double abs_n2 = Fabs(n2);
		double abs_n1n2 = Fabs(n1 - n2);
#if 1
		if ((abs_n1 <= epsilon) || (abs_n2 <= epsilon))   // if either is very nearly zero, don't take the magnitude into account
		return (abs_n1n2 <= epsilon);  
	else
#endif
		return (abs_n1n2 <= ( abs_n1 > abs_n2 ? abs_n1 : abs_n2 ) * epsilon);
}

inline Boolean DoubleIsNearlyZero(double n)
	{
		return DoublesAreNearlyEqual(n, 0);
	}

	inline Boolean DoublesAreNotNearlyEqual(double n1, double n2)
	{
		return (!DoublesAreNearlyEqual(n1, n2));
	}

	inline Boolean Double1_GE_Double2(double n1, double n2)
	{
		return ((n1 > n2) || DoublesAreNearlyEqual(n1, n2));
	}

inline Boolean Double1_GT_Double2(double n1, double n2)
{
	return ((n1 > n2) && (! DoublesAreNearlyEqual(n1, n2)));
}

inline Boolean Double1_LE_Double2(double n1, double n2)
	{
		return ((n1 < n2) || DoublesAreNearlyEqual(n1, n2));
	}

inline Boolean Double1_LT_Double2(double n1, double n2)
{
	return ((n1 < n2) && (! DoublesAreNearlyEqual(n1, n2)));
}

//----------------------------------------------------------------------------------------

	inline bool NearlyEqualFixedTolerance(double a, double b, double tolerance)
// Not using DoublesAreNearlyEqual because I need a fixed tolerance to match
//  what other text tolerance routines are doing - esp in DrawPad - PCP
{
	return (fabs(a-b) < tolerance);
}

inline Boolean IsANormalizedValue(double n)
	{
		return ((n >= -1 - kNearlyEqualEpsilonForNormalizedValues) && (n <= 1 + kNearlyEqualEpsilonForNormalizedValues));
	}

	//----------------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------------
	//
	// Magnitude-based double Comparison Functions For Normalized Values.
	//
	// All double comparisons for doubles that contain normalized values should use these functions.
	//
	// These double comparison functions are necessary because most floating point numbers
	// that are not whole numbers cannot be represented exactly (they have floating point 
	// approximations). Double precision floating point numbers (doubles) are accurate to 15 
	// digits, but we'll consider normalized value equal if they are the same up to the 6th significant 
	// digit (see kNearlyEqualEpsilonForNormalizedValues in MCFloat.cpp for reasons why). [MAF 5/20/02]
	//
	//----------------------------------------------------------------------------------------



	inline Boolean NormalizedValuesAreNearlyEqual(double n1, double n2)
	{
		//ASSERTN(kMark, (IsANormalizedValue(n1) && IsANormalizedValue(n2)));

		// Factor out the division for speed and div0. Also, always use the 
		// larger value * epsilon so that DoublesAreNearlyEqual(x,y) == DoublesAreNearlyEqual(y,x)
	if ((n1 == 0) || (n2 == 0))
		return (fastFabs(n1 - n2) <= kNearlyEqualEpsilonForNormalizedValues);
	else
		return (fastFabs(n1 - n2) <= ( fastFabs(n1) > fastFabs(n2) ? fastFabs(n1) : fastFabs(n2) ) * kNearlyEqualEpsilonForNormalizedValues);
}

inline Boolean NormalizedValueIsNearlyZero(double n)
	{
		return NormalizedValuesAreNearlyEqual(n, 0);
	}

	inline Boolean NormalizedValueIsNearlyOne(double n)
	{
		return NormalizedValuesAreNearlyEqual(n, 1);
	}

	//----------------------------------------------------------------------------------------


	short WholeNumberDigitsPin16(double_param inValue);
	double WholeNumberDigitsPow10PinE16(double_param inValue);
	short WholeNumberDigits(double_param inValue);
	double Modf(const double inNum, double* outIntegralPart,
		const double inEpsilon = kNearlyEqualEpsilonForDoubles);


	///////////////////////////////////////////////////////////////////////////////////////////////////////
	force_inline float DoubleToFloat(double dblVal)
		//
		// We use this func in case we ever end up needing it to
		// check for overflow.
		////////////////////////////////////////////////////////////
	{
	double pinnedDouble = PinTo<float>(kEveryone, dblVal);
	ASSERTN(kEveryone, (pinnedDouble == dblVal));

	return (float) pinnedDouble;
}	


	//**************************************************************************
	//
	// Data Structures Used By:	NNAFrac2X, NNAFix2X, NNAX2Fix, NNAX2Frac, NNAFracMul, & 
	//							NNALong2Fix
	//
	//**************************************************************************

	//**************************************************************************
	//
	// NNAFixed           16-bit signed integer plus 16-bit fraction
	//                 to represent fixed-point decimal
	//                 numbers in the interval:
	//
	//                 [-32768, 32767 + ((2^16 - 1)/2^16)]
	//
	//**************************************************************************

	typedef Sint32                          NNAFixed;
	typedef Sint32							NNAFract;

	double NNAFrac2X(NNAFract x);
	double NNAFix2X(NNAFixed x);
	NNAFixed NNAX2Fix(double x);
	NNAFract NNAX2Frac(double x);
	NNAFract NNAFracMul(NNAFract x, NNAFract y);
	NNAFixed NNALong2Fix(Sint32 x);

}
#endif // _MCFLOAT_

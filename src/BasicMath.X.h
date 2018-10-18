//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
// Contains basic math stuff. See also MCFloat.h and .cpp
//

#ifndef _BASICMATH_X_H_
#define _BASICMATH_X_H_ 1

#pragma once

#if _WINDOWS
#include <Math.h>
#endif

#include "MCFloat.h"


/////////////////////////////////////////////////////////////////////////////////////////
// Basic mathematical constants

// these are currently defined in MCCoordTypes.cpp

extern const double PI;

extern const double	kDegreesPerRadian;	// = 180.0 / PI
extern const double	kRadiansPerDegree;	// = PI / 180.0
extern const double kGradiansPerDegree;	// = 100.0 / 90.0;
extern const double kDegreesPerGradian;	// = 90.0 / 100.0;

const extern double	kHalfPi;			// = PI / 2.0
const extern double	kThreePiOver2;		// = 3.0 * PI / 2.0
const extern double	kTwoPi;				// = 2.0 * PI



/////////////////////////////////////////////////////////////////////////////////////////
//inline Real64		Abs(Real64 x)		{ return (Real64)fabs(x); }
inline double		Abs(double x)		{ return (x >= 0) ? x : -x; }  // six times faster than fabs on Windows (and maybe Intel Mac?) // [MAF 12/22/05]
inline Sint32		Abs(Sint32 x)			{ return (Sint32)labs(x); }
inline short		Abs(short x)		{ return abs(x); }
inline char			Abs(char x)			{ return abs(x); }
inline signed char	Abs(signed char x)	{ return abs(x); }


//---------------------------------------------------------------------------------------
inline Real32 Truncate(const Real32 fromValue)
//
// Description:
//   Truncates specified float value.
//
// Parameters:
//   fromValue - input - value to truncate.
//
// Returns:
//   float - truncated value.
//
// Created by Victor Long on 04/09/2004.
//
{
	Real32 toValue;
#if GS_WIN
	modf(fromValue, &toValue);
#else
	modff(fromValue, &toValue);
#endif

	return toValue;
}

//---------------------------------------------------------------------------------------
inline Real64 Truncate(const Real64 fromValue)
//
// Description:
//   Truncates specified double value.
//
// Parameters:
//   fromValue - input - value to truncate.
//
// Returns:
//   double - truncated value.
//
// Created by Victor Long on 04/09/2004.
//
{
	Real64 toValue;

	modf(fromValue, &toValue);

	return toValue;
}

//---------------------------------------------------------------------------------------
inline Real32 Round(Real32 value)
//
// Description:
//   Rounds specified float value.
//
// Parameters:
//   value - input - value to round.
//
// Returns:
//   float - rounded value.
//
// Created by Victor Long on 04/09/2004.
//
{
	return (floor(value + (float)0.5));
}

//---------------------------------------------------------------------------------------
inline Real64 Round(Real64 value)
//
// Description:
//   Rounds specified double value.
//
// Parameters:
//   value - input - value to round.
//
// Returns:
//   double - rounded value.
//
// Created by Victor Long on 04/09/2004.
//
{
	return (floor(value + 0.5));
}

//---------------------------------------------------------------------------------------
inline long double Round(long double value)
//
// Description:
//   Rounds specified long double value.
//
// Parameters:
//   value - input - value to round.
//
// Returns:
//   long double - rounded value.
//
// Created by Victor Long on 04/09/2004.
//
{
	return (floor(value + 0.5));
}

//---------------------------------------------------------------------------------------
inline Real64 Round5Digits(Real64 value)
//
// Description:
//   Rounds specified double value to 5 decimal places.
//
// Parameters:
//   value - input - value to round.
//
// Returns:
//   double - rounded value.
//
// Created by Hugues Tsafak on 02/12/2013.
//
{
	return (floor(value*100000 + 0.5)/100000);
}

//---------------------------------------------------------------------------------------
inline Real64 RoundDown(Real64 value, int decimal_places)
//
// Description:
//   Rounds down the specified double value to the specified number of decimal places.
//
// Parameters:
//   value - input - value to round.
//   decimal_places - input - number of decimal places
//
// Returns:
//   double - rounded value.
//
// Created by Hugues Tsafak on 02/12/2013.
//
{
    return (floor(value* pow(10, decimal_places))/pow(10, decimal_places));
}

//---------------------------------------------------------------------------------------
inline Real64 RoundUp(Real64 value, int decimal_places)
//
// Description:
//   Rounds up the specified double value to the specified number of decimal places.
//
// Parameters:
//   value - input - value to round.
//   decimal_places - input - number of decimal places
//
// Returns:
//   double - rounded value.
//
// Created by Hugues Tsafak on 02/12/2013.
//
{
    return (ceil(value* pow(10, decimal_places))/pow(10, decimal_places));
}

/////////////////////////////////////////////////////////////////////////////////////////
// Min and Max, 2 to 6 parameter versions. JDW.

template<class T> inline T	Max(T a, T b)		{ return( a > b ? a : b ); }
template<class T> inline T	Min(T a, T b)		{ return( a < b ? a : b ); }
template<class T> inline T	Max(T a, T b, T c)	{ return Max(Max(a,b), c); }
template<class T> inline T	Min(T a, T b, T c)	{ return Min(Min(a,b), c); }
template<class T> inline T	Max(T a, T b, T c, T d)				{ return Max(Max(a,b), Max(c,d)); }
template<class T> inline T	Min(T a, T b, T c, T d)				{ return Min(Min(a,b), Min(c,d)); }
template<class T> inline T	Max(T a, T b, T c, T d, T e)		{ return Max(Max(a,b), Max(c,d,e)); }
template<class T> inline T	Min(T a, T b, T c, T d, T e)		{ return Min(Min(a,b), Min(c,d,e)); }
template<class T> inline T	Max(T a, T b, T c, T d, T e, T f)	{ return Max(Max(a,b), Max(c,d), Max(e,f)); }
template<class T> inline T	Min(T a, T b, T c, T d, T e, T f)	{ return Min(Min(a,b), Min(c,d), Min(e,f)); }


/////////////////////////////////////////////////////////////////////////////////////////

#if 0
	// These will always give the correct result, even on compilers 
	// that use logical shift for >>. 
	inline Sint32 Div2(Sint32 x) 											{ return (x < 0 ? -((-x)>>1) : x >> 1); }
	inline Sint32 Div4(Sint32 x) 											{ return (x < 0 ? -((-x)>>2) : x >> 2); }
	inline Sint32 ASR(Sint32 x, short shiftBy)								{ return (x < 0 ? -((-x)>>shiftBy) : x >> shiftBy); }

#else
	// Use these if the compiler uses arithmetic shift for >>.
	inline Sint32 Div2(Sint32 x)											{ return x >> 1; }
	inline Sint32 Div4(Sint32 x)											{ return x >> 2; }
	inline Sint32 ASR(Sint32 x, short shiftBy)								{ return x >> shiftBy; }

#endif


/////////////////////////////////////////////////////////////////////////////////////////
inline double sqr(double x)	{ return x*x; }
inline double xpwr2(double x) { return x*x; }
inline double xpwr3(double x) { return x*x*x; }
inline double xpwr4(double x) { return x*x*x*x; }

inline double Sqrt(double x)		{ return sqrt(fastFabs(x)); }

/////////////////////////////////////////////////////////////////////////////////////////

// Modf() moved to MCFloat.h and .cpp

inline double FPRemainder(double_param num, double_param denom)
{
	#if _WINDOWS
		return fmod(num, denom);		
	#else
		return remainder(num, denom);
	#endif
}

inline double NormalizeAngle(double a)
{
	if (a < 0.0) {
		if (a < -360.0) {
			a = -FPRemainder(-a, 360.0);
		}
		a += 360.0;
	}
	else if (a >= 360.0) {
		a = FPRemainder(a, 360.0);
	}

	return a;
}


/////////////////////////////////////////////////////////////////////////////////////////
// Functions for returning whether two values of any type are approximately equal.

template <class Type> inline bool
ApproxEqual(Type x, Type y, Type fudgeFactor)
{
	return Abs(x-y) <= fudgeFactor;
}

template <class NumericType> inline bool
NotApproxEqual(NumericType x, NumericType y, NumericType fudgeFactor)
{
	return !ApproxEqual(x,y,fudgeFactor);
}


/////////////////////////////////////////////////////////////////////////////////////////

template <class NumType> inline NumType
IncModulo(NumType base, NumType modulo)
{
	return ( base == modulo-1 ? 0 : base+1 );
}

template <class NumType> inline NumType
DecModulo(NumType base, NumType modulo)
{
	return ( base == 0 ? modulo-1 : base-1 );
}


#endif // _BASICMATH_X_H_

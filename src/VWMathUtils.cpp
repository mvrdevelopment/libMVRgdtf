//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"


double	VWFC::Math::MathUtils::PI		= 3.1415926535897932384626433832795;
double	VWFC::Math::MathUtils::PI2		= 6.283185307179586476925286766559;
double	VWFC::Math::MathUtils::PIOver2	= 1.5707963267948966192313216916398;
double	VWFC::Math::MathUtils::PIOver4	= 0.78539816339744830961566084581988;
double	VWFC::Math::MathUtils::PI3Over2	= 4.7123889803846898576939650749193;

VWFC::Math::MathUtils::MathUtils()
{
}

VWFC::Math::MathUtils::~MathUtils()
{
}

bool VWFC::Math::MathUtils::Equalish(double num1, double num2, double dEpsilon)
{
	return ( Abs( num2 - num1 ) < dEpsilon );
}

bool VWFC::Math::MathUtils::Equalish(const VWPoint2D& a, const VWPoint2D& b, double dEpsilon)
{
	return
		( Abs( a.x - b.x ) < dEpsilon ) &&
		( Abs( a.y - b.y ) < dEpsilon );
}

bool VWFC::Math::MathUtils::Equalish(const VWPoint3D& a, const VWPoint3D& b, double dEpsilon)
{
	return
		( Abs( a.x - b.x ) < dEpsilon ) &&
		( Abs( a.y - b.y ) < dEpsilon ) &&
		( Abs( a.z - b.z ) < dEpsilon );
}

bool VWFC::Math::MathUtils::Equalish(double ax, double ay, double bx, double by, double dEpsilon)
{
	return
		( Abs( ax - bx ) < dEpsilon ) &&
		( Abs( ay - by ) < dEpsilon );
}

bool VWFC::Math::MathUtils::GEish(double num1, double num2, double dEpsilon)
{
	return	( (num1 >= num2) || ( num1 > (num2 - dEpsilon) ) );
}

bool VWFC::Math::MathUtils::LEish(double num1, double num2, double dEpsilon)
{
	return	( (num1 <= num2) || ( num1 < (num2 + dEpsilon) ) );
}

bool VWFC::Math::MathUtils::Greaterish(double num1, double num2, double dEpsilon)
{
	return	( (num1 > num2) && ( num1 >= (num2 + dEpsilon) ) );
}

bool VWFC::Math::MathUtils::Lesserish(double num1, double num2, double dEpsilon)
{
	return	( (num1 < num2) && ( num1 <= (num2 - dEpsilon) ) );
}

bool VWFC::Math::MathUtils::IsBetween(double a, double b, double c, double dEpsilon)
{
	return (c > b) ?	
		( ( ( a > b ) || MathUtils::Equalish( a, b, dEpsilon ) ) && ( ( a < c ) || MathUtils::Equalish( a, c, dEpsilon ) ) ) :
		( ( ( a < b ) || MathUtils::Equalish( a, b, dEpsilon ) ) && ( ( a > c ) || MathUtils::Equalish( a, c, dEpsilon ) ) );
}

bool VWFC::Math::MathUtils::IsBetween(const VWPoint2D& a, const VWPoint2D& b, const VWPoint2D& c, double dEpsilon)
{
	return ( MathUtils::IsBetween( a.x, b.x, c.x, dEpsilon ) && MathUtils::IsBetween( a.y, b.y, c.y, dEpsilon ) );
}

double VWFC::Math::MathUtils::FixedAngle(const VWPoint2D& p1, const VWPoint2D& p2)
{
	double						dx;
	double						dy;
	double						angle;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	if ( WorldCoordIsNearlyZero( dx ) )
	{
		if ( WorldCoordIsNearlyZero( dy ) )
		{
			angle = 0.0;
		}
		else
		{
			angle = ( dy < 0 ) ? 270.0 : 90.0;
		}
	}
	else {
		angle = atan2(dy, dx) * kDegreesPerRadian;
		if ( angle < 0 )
			angle += 360.0;
	}
	return angle;
}

double VWFC::Math::MathUtils::SpecialSin( double ang )
{
	if ( ang < 0 )		ang += 360.0;
	if ( ang > 360.0 )	ang -= 360.0;

	// calculate the component in the first quadrant
	double	normAng = ang;
	short	i = 0;
	
	while ( normAng > 90.0 ) {
		normAng -= 90.0;
		i++;
	}
			
	if ( i & 1 )	// odd means it is a complement of the original angle
		normAng = 90.0 - normAng;

	double fracComp = Abs( sin( normAng * kRadiansPerDegree ) );
	
	// calculate the sign
	if ( ( ang >= 0.0 ) && ( ang <= 180.0 ) )
		return fracComp;
	else
		return -fracComp;
}

double VWFC::Math::MathUtils::SpecialCos( double ang )
{
	if ( ang < 0 )		ang += 360.0;
	if ( ang > 360.0 )	ang -= 360.0;

	// calculate the component in the first quadrant
	double	normAng = ang;
	short	i = 0;
	
	while ( normAng > 90.0 ) {
		normAng -= 90.0;
		i++;
	}
	
	if ( i & 1 )	// odd means it is a complement of the original angle
		normAng = 90.0 - normAng;

	double fracComp = Abs( cos( normAng * kRadiansPerDegree ) );
	
	// calculate the sign
	if ( ( ( ang >= 0.0 ) && ( ang <= 90.0 ) ) || ( ( ang > 3 * 90.0 ) && ( ang <= 360.0 ) ) )
		return fracComp;
	else
		return -fracComp;
}

double VWFC::Math::MathUtils::Rad2Deg(double radAng)
{
	return radAng * kDegreesPerRadian;
}

double VWFC::Math::MathUtils::Deg2Rad(double degAng)
{
	return degAng * kRadiansPerDegree;
}

double VWFC::Math::MathUtils::RealRandom(double a1, double a2)
{
	if ( a2 < a1 ) {
		double	temp	= a1;
		a1				= a2;
		a2				= temp;
	}

	double_gs a = Abs( a2 - a1 );
	if ( a == 0 )
		return a1;

	return a * ( rand() / (double_gs) RAND_MAX ) + a1;
}

double VWFC::Math::MathUtils::Sign(const double dNum)
{
	double dSign = 1.0;
	if ( dNum < - VWPoint2D::sEpsilon ) {
		dSign = - 1.0;
	}

	return dSign;
}

double VWFC::Math::MathUtils::CalculateInterpolatedValue(double a, double b, double len, double interpolationLen)
{
	const double kEpsilon	= 0.000001;

	double	interpValue	= 0;
	if ( MathUtils::Equalish( interpolationLen, 0, kEpsilon ) ) {
		interpValue		= a;
	}
	else {
		if ( a < b ) {
			interpValue	= a + (interpolationLen / len) * (b - a);
		}
		else {
			interpValue	= b + ((len - interpolationLen) / len) * (a - b);
		}
	}

	return interpValue;
}


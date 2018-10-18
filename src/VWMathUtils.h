//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	namespace Math
	{
		class MathUtils
		{
		protected:
							MathUtils();
			virtual			~MathUtils();

		public:
			// check if for equal
			static bool		Equalish(double num1, double num2, double dEpsilon);
			static bool		Equalish(const VWPoint2D& a, const VWPoint2D& b, double dEpsilon);
			static bool		Equalish(const VWPoint3D& a, const VWPoint3D& b, double dEpsilon);
			static bool		Equalish(double ax, double ay, double bx, double by, double dEpsilon);
			// ... greater or equal
			static bool		GEish(double num1, double num2, double dEpsilon);
			// ... less or equal
			static bool		LEish(double num1, double num2, double dEpsilon);
			// ... greater
			static bool		Greaterish(double num1, double num2, double dEpsilon);
			// ... less
			static bool		Lesserish(double num1, double num2, double dEpsilon);

			// ... between
			static bool		IsBetween(double a, double b, double c, double dEpsilon);
			static bool		IsBetween(const VWPoint2D& a, const VWPoint2D& b, const VWPoint2D& c, double dEpsilon);

			// calculates the angle of (p2 - p1) to Ox axis
			static double	FixedAngle(const VWPoint2D& p1, const VWPoint2D& p2);
			// implements a periodic FracSin function - obtains a fast approximation of the sine of a Fixed number
			static double	SpecialSin( double ang );
			// implements a periodic FracCos function - obtains a fast approximation of the cosine of a Fixed number
			static double	SpecialCos( double ang );

			// convert radian angle value to degrees
			static double	Rad2Deg(double radAng);
			// convert degrees angle value to radian
			static double	Deg2Rad(double degAng);
			// this function generates a real random number between a1 and a2
			static double	RealRandom(double a1, double a2);

			// sign function
			static double	Sign(const double dNum);

			// calculate interpolated value of 'a' and 'b' at given 'interpolationLen'
			//   'interpolationLen' is the distance from 'a' to the interpolated value
			//   'len' is the distance from 'a' to 'b'
			static double	CalculateInterpolatedValue(double a, double b, double len, double interpolationLen);

		public:
			static double	PI;
			static double	PI2;
			static double	PIOver2;
			static double	PIOver4;
			static double	PI3Over2;
		};
	}
}
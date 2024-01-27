//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VectorworksMVR
{
	namespace VWFC
	{
		namespace Math
		{
			// --------------------------------------------------------------------------------
			class VWPoint2D
			{
			public:
				// construction
				VWPoint2D();
				VWPoint2D(const WorldPt& src);
				VWPoint2D(double x, double y);
				VWPoint2D(const VWPoint2D& src);
				~VWPoint2D();

				void		SetPoint(const WorldPt& pt);
				void		SetPoint(double x, double y);
				void		SetAngle(double radians);
				void		SetPointByAngle(double degAng, double length);

				// assignments
				VWPoint2D&	operator=(const VWPoint2D& src);
				VWPoint2D&	operator=(const WorldPt& src);

				bool		operator==(const VWPoint2D& p) const;
				bool		operator!=(const VWPoint2D& p) const;

				VWPoint2D	operator+(const VWPoint2D& p) const;
				VWPoint2D	operator-(const VWPoint2D& p) const;
				VWPoint2D	operator*(double scalar) const;
				VWPoint2D	operator/(double scalar) const;
				// dot product
				double		operator%(const VWPoint2D& p) const;

				VWPoint2D	operator-(void) const;

				VWPoint2D&	operator+=(const VWPoint2D& p);
				VWPoint2D&	operator-=(const VWPoint2D& p);
				VWPoint2D&	operator*=(double scalar);
				VWPoint2D&	operator/=(double scalar);

				// compatibility with SDK
				operator const WorldPt&() const;

				// Math functions
			public:
				// return the distance from (0,0) to this point
				double			Magnitude() const;
				// return the squared distance from (0,0) to this point.
				double			MagnitudeSquared() const;
				// return true if the specified point is equal within the given epsilon to this point
				bool			Equal(const VWPoint2D& pt, double dEpsilon) const;
				// calculate the distance from the specified point to this point
				double			DistanceTo(double x, double y) const;
				double			DistanceTo(const VWPoint2D& pt) const;
				// calculate the squared distance from the specified point to this point
				double			DistanceSquaredTo(double x, double y) const;
				double			DistanceSquaredTo(const VWPoint2D& pt) const;
				// rotate this point at specified angle in degrees and center point
				void			RotateAtDeg(const VWPoint2D& centerPt, double_gs dDegAngle);
				// rotate this point at specified angle in radians and center point
				void			RotateAtRad(const VWPoint2D& centerPt, double_gs dRadAngle);
				// return perpendicular point of this point
				VWPoint2D		Perp() const;
				// set this point to the perpendicullar of the specified point
				void			Perp(const VWPoint2D& pt);
				// get the angle of this point's vector from -180 to 180 deg
				double			CalcAng180() const;
				// get the angle of this point's vector from 0 to 360 deg
				double			CalcAng360() const;
				// get the angle between this point's vector and the specified vector (returned angle is between 0 and 180 degrees).
				double			CalcAngleTo(const VWPoint2D& vec) const;
				// set this points as the center of a circle passing thru 3 given points
				void			ThreePtCenter(const VWPoint2D& pt1, const VWPoint2D& pt2, const VWPoint2D& pt3);
				// translates this point into a coordinate system defined by 2 other points.
				void			RelativeCoords(const VWPoint2D& pt1, const VWPoint2D& pt2);
				// Cross product magnitude is primarily used for determining the left/right orientation of two vectors.
				double			CrossProductMagnitude(const VWPoint2D& pt) const;
				//The mathematical definition of Dot Product is:
				//		|a||b|cos theta or 
				//		the magnitude of 'a' times the magnitude of 'b' times the cosine of the angle between 'a' and 'b'
				double			DotProduct(const VWPoint2D& pt) const;
				// normalize this vector
				VWPoint2D&		Normalize();
				// get normalized of this vector.
				VWPoint2D		GetNormalized() const;
				// whether the current point is on the left of vector provided as parameter
				bool			IsPointOnTheRightOfVector(const VWPoint2D& vec) const;

				// data
			public:
				double		x, y;

				// Tools
			public:
				// area is negative if the triangle is CCW
				static double	TriArea(const VWPoint2D& pt1, const VWPoint2D& pt2, const VWPoint2D& pt3);
				// area is negative if the triangle is CCW
				static double	TriArea(double pt1x, double pt1y,
					double pt2x, double pt2y,
					double pt3x, double pt3y);
				static double	Distance(double x1, double y1, double x2, double y2);
				static double	DistanceSqare(double x1, double y1, double x2, double y2);

				// find the center and squared radius of triangle circumcircle. return whether it exists (triangle points are not collinear).
				static bool		GetTriCircumCircle(const VWPoint2D& pt0, const VWPoint2D& pt1, const VWPoint2D& pt2, VWPoint2D& outCenPt, double& outSqrRad);
				// find the squared radius of triangle inscribed circle. return whether it exists.
				static bool		GetTriInscribedCircleRadius(const VWPoint2D& pt0, const VWPoint2D& pt1, const VWPoint2D& pt2, double& outSqrRad);
				// find the center of triangle inscribed circle.
				static void		GetTriInscribedCircleCenter(const VWPoint2D& pt0, const VWPoint2D& pt1, const VWPoint2D& pt2, VWPoint2D& outCenPt);
				// get an estimation of the triangle aspect ratio. ratio can not be estimated for degenerate triangles.
				static bool		TriAspectRatioEval(const VWPoint2D& pt0, const VWPoint2D& pt1, const VWPoint2D& pt2, double& ratioEval);

				// check if given 3 points are collinear.
				static bool		ArePointsCollinear(const VWPoint2D& pt0, const VWPoint2D& pt1, const VWPoint2D& pt2, double dEpsilon);

				// get the angle between two vectors (returned angle is in radians between 0 and PI).
				static double	CalcAngleBetween(const VWPoint2D& vec1, const VWPoint2D& vec2, bool areNormalized = false);

				// static point defs
			public:
				// default epsilon for operator==
				static double	sEpsilon;
				// squared default epsilon.
				static double	sSqrEpsilon;
				// negative epsilons.
				static double	sNegEpsilon;
				static double	sNegSqrEpsilon;
				// raw (bigger) epsilon.
				static double	sRawEpsilon;
				// default epsilon for checking collinearity.
				static double	sEpsilonCollinear;
				// default epsilon for checking nearness between angles in radians.
				static double	sEpsilonRadians;

			private:
				WorldPt		fPoint;
			};

			// array of point defintion
			typedef		std::vector<VWPoint2D>									TSTLPoints2DArray;
		}
	}
}
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
		class VWLine3D;

		class VWPoint3D
		{
		public:
							VWPoint3D();
							VWPoint3D(const WorldPt3& pt);
							VWPoint3D(double x, double y, double z=0);
							VWPoint3D(const VWPoint2D& pt, double z=0);
							VWPoint3D(const VWPoint3D& src);
							~VWPoint3D();

		public:

			void			SetPoint(const WorldPt3& pt);
			void			SetPoint(double x, double y, double z=0);
			void			SetPoint(const VWPoint2D& pt, double z=0);

			bool			operator==(const VWPoint3D& p) const;
			bool			operator!=(const VWPoint3D& p) const;
			bool			operator==(const VWPoint2D& p) const;
			bool			operator!=(const VWPoint2D& p) const;

			VWPoint3D		operator+(const VWPoint3D& p) const;
			VWPoint3D		operator-(const VWPoint3D& p) const;
			VWPoint3D		operator*(double scalar) const;
			VWPoint3D		operator/(double scalar) const;
			VWPoint3D		operator-(void) const;
			// cross product
			VWPoint3D		operator*(const VWPoint3D& p) const;
			// dot product
			double			operator%(const VWPoint3D& p) const;

			VWPoint3D&		operator=(const WorldPt3& p);
			VWPoint3D&		operator=(const VWPoint3D& p);
			VWPoint3D&		operator=(const VWPoint2D& p);
			VWPoint3D&		operator+=(const VWPoint3D& p);
			VWPoint3D&		operator+=(const VWPoint2D& p);
			VWPoint3D&		operator-=(const VWPoint3D& p);
			VWPoint3D&		operator-=(const VWPoint2D& p);

			VWPoint3D&		operator*=(double s);
			VWPoint3D&		operator/=(double s);
			// cross product
			VWPoint3D&		operator*=(const VWPoint3D& p);

			// get projected on XY point
							operator VWPoint2D() const;
			// compatibility with SDK
							operator const WorldPt3&() const;

		// Math functions
		public:
			// return the distance from (0,0,0) to this point
			double			Magnitude() const;
			// return the squared distance from (0,0,0) to this point
			double			MagnitudeSquared() const;
			// return true if the specified point is equal within the given epsilon to this point
			bool			Equal(const VWPoint3D& pt, double dEpsilon) const;
			bool			Equal(const VWPoint2D& pt, double dEpsilon) const;
			// calculate the distance from the specified point to this point
			double			DistanceTo(double x, double y, double z);
			double			DistanceTo(const VWPoint3D& pt) const;
			//calculate the squared distance from the spcified point to this point
			double			DistanceSquaredTo(double x, double y, double z);
			double			DistanceSquaredTo(const VWPoint3D& pt) const;
			// cross product
			VWPoint3D		Cross(const VWPoint3D& pt) const;
			// dot product
			double			DotProduct(const VWPoint3D& pt) const;
			// normalize this vector
			VWPoint3D&		Normalize();
			// get normalized of this vector.
			VWPoint3D		GetNormalized() const;

			// checks whether the point lies on plane defined by point and two vectors lying on it.
			bool			IsOnPlane(const VWPoint3D& planePt, const VWPoint3D& planeVec0, const VWPoint3D& planeVec1,
									  double coordEpsilon, double radEpsilon) const;

			// checks whether a point lies inside a triangle (lies on triangle's plane and is inside triangle's area).
			bool			IsOnTriangle(const VWPoint3D& triPt0, const VWPoint3D& triPt1, const VWPoint3D& triPt2,
										 double coordEpsilon, double radEpsilon) const;

		// Tools
		public:
			// area is negative if the triangle is CCW
			static double	TriArea(const VWPoint3D& pt1, const VWPoint3D& pt2, const VWPoint3D& pt3);
			// area is negative if the triangle is CCW
			static double	TriArea(double pt1x, double pt1y, double pt1z,
									double pt2x, double pt2y, double pt2z,
									double pt3x, double pt3y, double pt3z);

			// find the center and squared radius of triangle circumcircle. return whether it exists (triangle points are not collinear).
			static bool		GetTriCircumCircle(const VWPoint3D& pt0, const VWPoint3D& pt1, const VWPoint3D& pt2, VWPoint3D& outCenPt, double& outSqrRad);
			// find the squared radius of triangle inscribed circle. return whether it exists.
			static bool		GetTriInscribedCircleRadius(const VWPoint3D& pt0, const VWPoint3D& pt1, const VWPoint3D& pt2, double& outSqrRad);
			// find the center of triangle inscribed circle.
			static void		GetTriInscribedCircleCenter(const VWPoint3D& pt0, const VWPoint3D& pt1, const VWPoint3D& pt2, VWPoint3D& outCenPt);
			// get an estimation of the triangle aspect ratio. ratio can not be estimated for degenerate triangles.
			static bool		TriAspectRatioEval(const VWPoint3D& pt0, const VWPoint3D& pt1, const VWPoint3D& pt2, double& ratioEval);

			// check if given 3 points are collinear.
			static bool		ArePointsCollinear(const VWPoint3D& pt0, const VWPoint3D& pt1, const VWPoint3D& pt2, double dEpsilon);

			// get longest triangle's edge.
			static VWLine3D	GetTriLongestEdge(const VWPoint3D& triPt0, const VWPoint3D& triPt1, const VWPoint3D& triPt2);

		// data
		public:
			double			x, y, z;

		// static point defs
		public:
			// default epsilon for operator==
			static double	sEpsilon;
			// squared default epsilon.
			static double	sSqrEpsilon;
			// raw (bigger) epsilon.
			static double	sRawEpsilon;
			// default epsilon for checking collinearity.
			static double	sEpsilonCollinear;
			// default epsilon for checking nearness between angles in radians.
			static double	sEpsilonRadians;

		private:
			WorldPt3		fPoint;
		};

		// array of point defintion
			typedef		std::vector<VWPoint3D>									TSTLPoints3DArray;
		}
	}
}
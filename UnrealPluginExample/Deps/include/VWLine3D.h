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
			class VWLine3D
			{
			public:
				VWLine3D();
				VWLine3D(const VWPoint3D& begPt, const VWPoint3D& endPt);
				VWLine3D(const VWLine3D& src);
				virtual				~VWLine3D();

				VWLine3D&			operator=(const VWLine3D& src);

				const VWPoint3D&	GetStart() const;
				VWPoint3D&			GetStart();
				const VWPoint3D&	GetEnd() const;
				VWPoint3D&			GetEnd();
				void				GetLine(VWPoint3D& outPtStart, VWPoint3D& outPtEnd) const;


				void				SetStart(const VWPoint3D& pt);
				void				SetEnd(const VWPoint3D& pt);
				void				SetLine(const VWPoint3D& ptStart, const VWPoint3D& ptEnd);

				void				ReverseSides();

				VWLine3D			operator+(const VWPoint3D& p) const;
				VWLine3D			operator-(const VWPoint3D& p) const;
				VWLine3D			operator*(double scalar) const;
				VWLine3D			operator/(double scalar) const;

				VWLine3D&			operator+=(const VWPoint3D& p);
				VWLine3D&			operator-=(const VWPoint3D& p);
				VWLine3D&			operator*=(double scalar);
				VWLine3D&			operator/=(double scalar);

				// math functions
			public:
			// return the center point of the line
			VWPoint2D			CenterPt() const;
			// return a point at a relative position on the line
			VWPoint3D			GetPointOnLine( double position );
			// return the length of the line
			double				GetLength() const;
			// min distance from a point to this line
				// this is the distance from the point to the nearest point on the line
				// which is the line perpendicular to the given one trough the specified point
				double				GetDistance(const VWPoint3D& pt) const;
				// get vertical distance from the point to the line
				// NOTE! no check if the point is on the projection of the line is check
				double				GetVerticalDistance(const VWPoint3D& pt) const;
				// return the direction vector of the line (end - start)
				VWPoint3D			GetDirectionVector() const;
				// return true if the specified point is on the line within an epsilon
				bool				PtOnLine(const VWPoint3D& pt, double dEpsilon, bool bIncludeLinePoints = true) const;
				bool				PtOnLineStart(const VWPoint3D& pt, double dEpsilon) const;
				bool				PtOnLineEnd(const VWPoint3D& pt, double dEpsilon) const;
				bool				PtOnLinePoints(const VWPoint3D& pt, double dEpsilon) const;
				bool				IsPtOnLine(const VWPoint3D& pt, double coordEpsilon, double radEpsilon) const;

				// checks whether the line intersects plane defined by point and two vectors lying on it.
				// returns if the line lies on the plane and the intersection line/point.
				bool				IntersectPlane(const VWPoint3D& planePt, const VWPoint3D& planeVec0, const VWPoint3D& planeVec1,
					VWLine3D& outIntersLine, bool& outLineOnPlane, double coordEpsilon, double radEpsilon) const;
				// checks whether the line intersects plane defined by point and two vectors lying on it.
				bool				IntersectPlane(const VWPoint3D& planePt, const VWPoint3D& planeVec0, const VWPoint3D& planeVec1,
					double coordEpsilon, double radEpsilon) const;

				// checks whether the line intersects another line.
				// returns if the two lines overlap and the intersection line/point.
				bool				IntersectLine(const VWLine3D& line, VWLine3D& outIntersLine, bool& outLinesOverlap,
					double coordEpsilon, double radEpsilon) const;
				// checks whether the line intersects another line.
				bool				IntersectLine(const VWLine3D& line, double coordEpsilon, double radEpsilon) const;

				// checks whether the line (line segment) intersects the triangle.
				// returns if the line lies on the triangle's plane and the intersection line/point.
				bool				IntersectTriangle(const VWPoint3D& triPt0, const VWPoint3D& triPt1, const VWPoint3D& triPt2,
					VWLine3D& outIntersLine, bool& outLineOnTriPlane, double coordEpsilon, double radEpsilon) const;
				// checks whether the line (line segment) intersects the triangle.
				bool				IntersectTriangle(const VWPoint3D& triPt0, const VWPoint3D& triPt1, const VWPoint3D& triPt2,
					double coordEpsilon, double radEpsilon) const;

				// providing that this line and the triangle lie on same 3D plane, checks whether the line intersects the triangle.
				// returns the intersection line/point.
				bool				IntersectTriangleOnSamePlane(const VWPoint3D& triPt0, const VWPoint3D& triPt1, const VWPoint3D& triPt2,
					VWLine3D& outIntersLine, double coordEpsilon, double radEpsilon) const;
				// providing that this line and the triangle lie on same 3D plane, checks whether the line intersects the triangle.
				bool				IntersectTriangleOnSamePlane(const VWPoint3D& triPt0, const VWPoint3D& triPt1, const VWPoint3D& triPt2,
					double coordEpsilon, double radEpsilon) const;

				// checks whether a line segment lies in the triangle (both line ends are in the triangle).
				bool				IsOnTriangle(const VWPoint3D& triPt0, const VWPoint3D& triPt1, const VWPoint3D& triPt2,
					double coordEpsilon, double radEpsilon) const;

		// tools
		public:
			static double	GetVerticalDistance(	double ax, double ay, double az,
													double bx, double by, double bz,
													double px, double py);

			protected:
				VWPoint3D			m_ptStart;
				VWPoint3D			m_ptEnd;
			};
		}
	}
}
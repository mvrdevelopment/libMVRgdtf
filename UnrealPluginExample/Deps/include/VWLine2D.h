//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#ifndef VECTORWORKS_LINE_2D__H
#define VECTORWORKS_LINE_2D__H

#pragma once

namespace VectorworksMVR
{
	namespace VWFC
	{
		namespace Math
		{
			class VWLine2D
			{
			public:
				VWLine2D();
				VWLine2D(double x1, double y1, double x2, double y2);
				VWLine2D(const VWPoint2D& begPt, const VWPoint2D& endPt);
				VWLine2D(const VWLine2D& src);
				virtual				~VWLine2D();

				VWLine2D&			operator=(const VWLine2D& src);

				const VWPoint2D&	GetStart() const;
				VWPoint2D&			GetStart();
				const VWPoint2D&	GetEnd() const;
				VWPoint2D&			GetEnd();
				void				GetLine(VWPoint2D& outPtStart, VWPoint2D& outPtEnd) const;


				void				SetStart(const VWPoint2D& pt);
				void				SetEnd(const VWPoint2D& pt);
				void				SetLine(double x1, double y1, double x2, double y2);
				void				SetLine(const VWPoint2D& ptStart, const VWPoint2D& ptEnd);

				void				ReverseSides();

				VWLine2D			operator+(const VWPoint2D& p) const;
				VWLine2D			operator-(const VWPoint2D& p) const;
				VWLine2D			operator*(double scalar) const;
				VWLine2D			operator/(double scalar) const;

				VWLine2D&			operator+=(const VWPoint2D& p);
				VWLine2D&			operator-=(const VWPoint2D& p);
				VWLine2D&			operator*=(double scalar);
				VWLine2D&			operator/=(double scalar);

				// math functions
			public:
				// return the center point of the line
				VWPoint2D			CenterPt() const;
				// return the length of the line
				double				GetLength() const;
				// calculate the line equation
				void				CalcLineEquation(double& outA, double& outB, double& outC) const;
				// return true if the specified point is on the line within an epsilon
				bool				PtOnLine(const VWPoint2D& pt, double dEpsilon) const;
				bool				PtOnLineStart(const VWPoint2D& pt, double dEpsilon) const;
				bool				PtOnLineEnd(const VWPoint2D& pt, double dEpsilon) const;
				bool				PtOnLinePoints(const VWPoint2D& pt, double dEpsilon) const;
				// checks if point is on left side of the line.
				bool				PtOnLeft(const VWPoint2D& pt) const;
				// get the angle 0 .. 90 from this line to the specified line
				double				GetAngle90(const VWLine2D& line) const;
				// return direction of the line: normal vector (b - a)
				VWPoint2D			GetDirection() const;
				// teturns a point on this line which is closest to the input point.
				VWPoint2D			PtPerpLine(double x, double y) const;
				VWPoint2D			PtPerpLine(const VWPoint2D& pt) const;
				// returns the closest point to this line segment or the closest end
				VWPoint2D			PtPerpLineSeg(const VWPoint2D& pt) const;
				// returns the closest point to this line segment or the closest segment end, also returns the squared distance to the found point.
				VWPoint2D			PtPerpLineSeg(const VWPoint2D& pt, double& outSqrDist) const;
				// return the distance from the specified point to the line
				double				Distance(double x, double y) const;
				double				Distance(const VWPoint2D& pt) const;
				double              DistanceSeg(const VWPoint2D& pt) const;
				// intersect the infinite lines. The result point can be outside the line segments
				// return false if the lines are parallel
				bool				IntersectLines(const VWLine2D& line, VWPoint2D& outIntersPt) const;
				bool				IntersectLines(const VWPoint2D& a, const VWPoint2D& b, VWPoint2D& outIntersPt) const;
				// intersect the infinite lines. The result point can be outside the line segments
				// return false if the lines are parallel
				// outPtOnLineSegs returns true if the intersection point lies on both line segments
				bool				IntersectLines(const VWLine2D& line, VWPoint2D& outIntersPt, bool& outPtOnLineSegs) const;
				bool				IntersectLines(const VWPoint2D& a, const VWPoint2D& b, VWPoint2D& outIntersPt, bool& outPtOnLineSegs) const;
				// interset the line segments.
				// return false if the lines are parallel or the line segments
				// doest intersect each oter in the bound of the segments
				bool				IntersectLineSegments(const VWLine2D& line, VWPoint2D& outIntersPt) const;
				bool				IntersectLineSegments(const VWPoint2D& a, const VWPoint2D& b, VWPoint2D& outIntersPt) const;
				// only check if line segments intersect. for faster check.
				bool				AreLineSegmentsIntersecting(const VWLine2D& line, double dEpsilon) const;
				bool				AreLineSegmentsIntersecting(const VWPoint2D& a, const VWPoint2D& b, double dEpsilon) const;
				bool				AreLineSegmentsIntersecting(const VWLine2D& line, VWPoint2D& outIntersPt, bool& outParallel, double epsilon) const;
				// return translated point into a coordinate system defined by this line.
				VWPoint2D			RelativeCoords(const VWPoint2D& pt) const;
				// rotate this point at specified angle in degrees and center point
				void				RotateAtDeg(const VWPoint2D& centerPt, double_gs dDegAngle);
				// rotate this point at specified angle in radians and center point
				void				RotateAtRad(const VWPoint2D& centerPt, double_gs dRadAngle);
				// return true if the specified two points are on the same side of the line
				bool				AreOnSameSide(double x1, double y1, double x2, double y2);
				bool				AreOnSameSide(const VWPoint2D& a, const VWPoint2D& b);

				// Boolean Functions			
				bool				Subtract(const VWLine2D& tool, std::vector<VWLine2D> results) const;

				// Tools
			public:
				static bool			PtOnLine(const VWPoint2D& pt, const VWPoint2D& lineA, const VWPoint2D& lineB, double dEpsilon);
				static void			IntersectLines(const VWPoint2D& p1, const VWPoint2D& p2, const VWPoint2D& p3, const VWPoint2D& p4, VWPoint2D& outInters, bool& outParallel, bool& outOnSegment1, bool& outOnSegment2);
				static void			IntersectLines(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double& outIntersX, double& outIntersY, bool& outParallel, bool& outOnSegment1, bool& outOnSegment2, double dEpsilon);
				static void			IntersectLines(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double& outIntersX, double& outIntersY, bool& outParallel, bool& outOnSeg1Pt1, bool& outOnSeg1Pt2, bool& outOnSegment1, bool& outOnSegment2, double epsilon);
				static void			IntersectLines(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double& outIntersX, double& outIntersY, bool& outParallel, bool& outOnSeg1Pt1, bool& outOnSeg1Pt2, bool& outOnSegment1, bool& outOnSegment2, double epsCoord, double epsCollinear);
				static void			IntersectLines(const VWPoint2D& a1, const VWPoint2D& a2, const VWPoint2D& b1, const VWPoint2D& b2, bool& intersect, bool& parallel, VWPoint2D& int0, double epsilon);
				static void			IntersectLines(const VWPoint2D& pt1, const VWPoint2D& pt2, const VWPoint2D& pt3, const VWPoint2D& pt4, VWLine2D& outIntersLine, bool& outParallel, bool& outOnSeg1, bool& outOnSeg2, double epsCoord, double epsCollinear);
				// only check if line segments intersect. for faster check.
				static bool			AreLineSegmentsIntersecting(const VWPoint2D& p1, const VWPoint2D& p2, const VWPoint2D& p3, const VWPoint2D& p4, double dEpsilon);
				static bool			AreLineSegmentsIntersecting(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double dEpsilon);
			static bool			AreLineSegmentsIntersecting(const VWPoint2D& p1, const VWPoint2D& p2, const VWPoint2D& p3, const VWPoint2D& p4, VWPoint2D& outIntersPt, bool& outParallel, double epsilon);
			static bool			AreLineSegmentsIntersecting(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double& outIntersX, double& outIntersY, bool& outParallel, double epsilon);
			// distance from point (x0,y0) to line [(x1,y1)(x2,y2)]
			static double		Distance(double x0, double y0, double x1, double y1, double x2, double y2 );
			// check for intersection between bounding boxes of line segments.
			static bool			DoLineSegmentsBoundsIntersect(const VWPoint2D& p1, const VWPoint2D& p2, const VWPoint2D& p3, const VWPoint2D& p4, double epsilon);
			static bool			DoLineSegmentsBoundsIntersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double epsilon);
				// returns the closest point to the line segment or the closest segment end, also returns the squared distance to the found point.
				static VWPoint2D	PtPerpLineSeg(const VWPoint2D& pt, const VWPoint2D& lnPt0, const VWPoint2D& lnPt1, double& outSqrDist);
				// returns the closest point to the line segment. it is a optimized/faster version which uses squared length.
				static void			PtPerpLine(double pX, double pY, double l1X, double l1Y, double l2X, double l2Y, double& outProjX, double& outProjY);
				// checks if point is on left side of the line defined by two points.
				static bool			PtOnLeftOfLine(const VWPoint2D& pt, const VWPoint2D& lnPt0, const VWPoint2D& lnPt1);
				// checks if point is on left side of the ray defined by ray point and vector.
				static bool			PtOnLeftOfRay(const VWPoint2D& pt, const VWPoint2D& rayPt, const VWPoint2D& rayVec);

			protected:
				VWPoint2D			m_ptStart;
				VWPoint2D			m_ptEnd;
			};

			// array of lines definition.
			typedef		std::vector<VWLine2D>								TSTLLines2DArray;
		}
	}
}

#endif // VECTORWORKS_LINE_2D__H
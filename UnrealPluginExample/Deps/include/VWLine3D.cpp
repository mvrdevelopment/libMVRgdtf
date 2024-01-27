//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "Prefix/StdAfx.h"

using namespace VectorworksMVR::VWFC::Math;

VWLine3D::VWLine3D()
{
}

VWLine3D::VWLine3D(const VWPoint3D& begPt, const VWPoint3D& endPt)
{
	m_ptStart	= begPt;
	m_ptEnd		= endPt;
}

VWLine3D::VWLine3D(const VWLine3D& src)
{
	m_ptStart	= src.m_ptStart;
	m_ptEnd		= src.m_ptEnd;
}

VWLine3D::~VWLine3D()
{
}

VWLine3D& VWLine3D::operator=(const VWLine3D& src)
{
	m_ptStart	= src.m_ptStart;
	m_ptEnd		= src.m_ptEnd;
	return *this;
}

const VWPoint3D& VWLine3D::GetStart() const
{
	return m_ptStart;
}

VWPoint3D& VWLine3D::GetStart()
{
	return m_ptStart;
}

const VWPoint3D& VWLine3D::GetEnd() const
{
	return m_ptEnd;
}

VWPoint3D& VWLine3D::GetEnd()
{
	return m_ptEnd;
}

void VWLine3D::GetLine(VWPoint3D& outPtStart, VWPoint3D& outPtEnd) const
{
	outPtStart		= m_ptStart;
	outPtEnd		= m_ptEnd;
}

void VWLine3D::SetStart(const VWPoint3D& pt)
{
	m_ptStart	= pt;
}

void VWLine3D::SetEnd(const VWPoint3D& pt)
{
	m_ptEnd		= pt;
}

void VWLine3D::SetLine(const VWPoint3D& ptStart, const VWPoint3D& ptEnd)
{
	m_ptStart	= ptStart;
	m_ptEnd		= ptEnd;
}

void VWLine3D::ReverseSides()
{
	VWPoint3D	pt	= m_ptStart;
	m_ptStart		= m_ptEnd;
	m_ptEnd			= pt;
}

VWLine3D VWLine3D::operator+(const VWPoint3D& p) const
{
	VWLine3D	line	= *this;
	line				+= p;
	return line;
}

VWLine3D VWLine3D::operator-(const VWPoint3D& p) const
{
	VWLine3D	line	= *this;
	line				-= p;
	return line;
}

VWLine3D VWLine3D::operator*(double scalar) const
{
	VWLine3D	line	= *this;
	line				*= scalar;
	return line;
}

VWLine3D VWLine3D::operator/(double scalar) const
{
	VWLine3D	line	= *this;
	line				/= scalar;
	return line;
}

VWLine3D& VWLine3D::operator+=(const VWPoint3D& p)
{
	m_ptStart		+= p;
	m_ptEnd			+= p;
	return *this;
}

VWLine3D& VWLine3D::operator-=(const VWPoint3D& p)
{
	m_ptStart		-= p;
	m_ptEnd			-= p;
	return *this;
}

VWLine3D& VWLine3D::operator*=(double scalar)
{
	m_ptStart		*= scalar;
	m_ptEnd			*= scalar;
	return *this;
}

VWLine3D& VWLine3D::operator/=(double scalar)
{
	m_ptStart		/= scalar;
	m_ptEnd			/= scalar;
	return *this;
}

////////////////////////////////////////////////////////////////////
// math functions
////////////////////////////////////////////////////////////////////
// return the center point of the line
VWPoint2D VWLine3D::CenterPt() const
{
	return ( m_ptStart + m_ptEnd ) / 2;
}

VWPoint3D VWLine3D::GetPointOnLine(double position)
{
	VWPoint3D dir = this->GetDirectionVector();
	ASSERTN(kEveryone, DoublesAreNotNearlyEqual( dir.Magnitude(), 0 ));
	dir.Normalize();
	dir *= position;
	return this->GetStart() + dir;
}

// return the length of the line
double VWLine3D::GetLength() const
{
	return m_ptStart.DistanceTo( m_ptEnd );
}

// min distance from a point to this line
// this is the distance from the point to the nearest point on the line
// which is the line perpendicular to the given one trough the specified point
double VWLine3D::GetDistance(const VWPoint3D& pt) const
{
/*	VWPoint3D	tangent	= (m_ptEnd - m_ptStart).Normalize();

	VWPoint3D	diff	= pt - m_ptStart;
	double		f		= diff % tangent;
	
	return diff.DistanceTo( tangent * f );
*/

	double	a	= ((m_ptEnd - m_ptStart) * (m_ptStart - pt)).Magnitude();
	double	b	= (m_ptEnd - m_ptStart).Magnitude();

	return a / b;
/*
	VWPoint3D	diff( pt - m_ptStart );
	VWPoint3D	m	= (m_ptEnd - m_ptStart).Normalize();

    double l = (m % m);
    if (l > 0.0f)
	{
        double t	= (m % diff) / l;
        diff		= diff - m*t;

        return diff.Magnitude();
    }
	else
	{
        // line is really a point...
        VWPoint3D v( pt - m_ptStart );
        return v.Magnitude();
    }
*/
}

// return the direction vector of the line (end - start)
VWPoint3D VWLine3D::GetDirectionVector() const
{
	return (m_ptEnd - m_ptStart).Normalize();
}

// get the vertical distance to 3D line - the Z value for the point so it lies on the 3D line.
// NOTE: no check whether the point is on the projection of the line.
double VWLine3D::GetVerticalDistance(const VWPoint3D& pt) const
{
	return  VWLine3D::GetVerticalDistance( m_ptStart.x, m_ptStart.y, m_ptStart.z, m_ptEnd.x, m_ptEnd.y, m_ptEnd.z, pt.x, pt.y );
}

// get the vertical distance to 3D line - the Z value for the point so it lies on the 3D line.
// NOTE: no check whether the point is on the projection of the line.
double VWLine3D::GetVerticalDistance(double ax, double ay, double az, double bx, double by, double bz, double px, double py)
{
	double		d		= VWPoint2D::Distance( ax, ay, bx, by );
	double		dp		= VWPoint2D::Distance( ax, ay, px, py );

	if ( Abs( d ) < VWPoint2D::sEpsilon )	// vertical 3D line.
	{
		// as result choose the Z of the lowest of the line end points.
		return	( az < bz ? az : bz );
	}

	double		pz		= 0;
	if ( az <= bz ) {
		pz		= ( bz - az ) * ( dp / d ) + az;
	}
	else {
		pz		= ( az - bz ) * ( (d - dp) / d ) + bz;
	}

	return pz;
}

bool VWLine3D::PtOnLine(const VWPoint3D& pt, double dEpsilon, bool bIncludeLinePoints) const
{
	// get projections of line end points.
	VWPoint2D	startPt2D( m_ptStart.x, m_ptStart.y );
	VWPoint2D	endPt2D( m_ptEnd.x, m_ptEnd.y );

	// check if the point's projection lies on line's projection.
	bool		ptOnLine	= VWLine2D::PtOnLine( VWPoint2D( pt.x, pt.y ), startPt2D, endPt2D, dEpsilon );

	if ( ptOnLine )			// go on.
	{
		// get the line length (in 2D).
		double	line2DLen	= startPt2D.DistanceTo( endPt2D );

		// check if the line is vertical.
		if ( line2DLen < dEpsilon )	// vertical.
		{
			// find line's minimum and maximum Zs.
			double	minLinZ, maxLinZ;
			if ( m_ptStart.z < m_ptEnd.z )
			{
				minLinZ		= m_ptStart.z;
				maxLinZ		= m_ptEnd.z;
			}
			else
			{
				minLinZ		= m_ptEnd.z;
				maxLinZ		= m_ptStart.z;
			}

			// check if the point's Z is between Zs of line end points.
			if ( bIncludeLinePoints )
			{
				ptOnLine	= ( MathUtils::GEish( pt.z, minLinZ, dEpsilon ) &&
								MathUtils::LEish( pt.z, maxLinZ, dEpsilon ) );
			}
			else
			{
				ptOnLine	= ( MathUtils::Greaterish( pt.z, minLinZ, dEpsilon ) &&
								MathUtils::Lesserish( pt.z, maxLinZ, dEpsilon ) );
			}
		}
		else	// non-vertical.
		{
			if ( ptOnLine && ! bIncludeLinePoints )
			{
				if ( MathUtils::Equalish( m_ptStart, pt, dEpsilon ) )
				{
					ptOnLine	= false;
				}
				else if ( MathUtils::Equalish( m_ptEnd, pt, dEpsilon ) )
				{
					ptOnLine	= false;
				}
			}

			if ( ptOnLine )
			{
				// Note that the line is non-vertical (already checked).
				double	mustBeZ	= this->GetVerticalDistance( VWPoint3D( pt.x, pt.y, 0.0 ) );
				ptOnLine		= MathUtils::Equalish( pt.z, mustBeZ, dEpsilon );
			}
		}
	}

	// result.
	return	( ptOnLine );
}

bool VWLine3D::PtOnLineStart(const VWPoint3D& pt, double dEpsilon) const
{
	return MathUtils::Equalish( m_ptStart, pt, dEpsilon );
}

bool VWLine3D::PtOnLineEnd(const VWPoint3D& pt, double dEpsilon) const
{
	return MathUtils::Equalish( m_ptEnd, pt, dEpsilon );
}

bool VWLine3D::PtOnLinePoints(const VWPoint3D& pt, double dEpsilon) const
{
	return MathUtils::Equalish( m_ptStart, pt, dEpsilon ) || MathUtils::Equalish( m_ptEnd, pt, dEpsilon );
}

// checks whether point lies on the line.
// uses different approach than the 'PtOnLine' function.
bool VWLine3D::IsPtOnLine(const VWPoint3D& pt, double coordEpsilon, double radEpsilon) const
{
	// init.
	bool				isOn		= false;

	const VWPoint3D&	lineBeg		= this->GetStart();
	const VWPoint3D&	lineEnd		= this->GetEnd();

	VWPoint3D			lineVec		= ( lineEnd - lineBeg );
	double				lineSqrLen	= lineVec.MagnitudeSquared();

	double				sqrEps		= sqr( coordEpsilon );

	if ( MathUtils::Equalish( lineSqrLen, 0.0, sqrEps ) )		// degenerate zero-length line.
	{
		isOn						= MathUtils::Equalish( pt, lineBeg, coordEpsilon );
	}
	else							// non-degenerate line.
	{
		// get cosine of the angle between 'lineVec' and ('lineBeg','pt').
		double			cosAng		= ( lineVec.GetNormalized() % ( ( pt - lineBeg ).Normalize() ) );	// dot product.

		if ( MathUtils::Equalish( cosAng, 1.0, radEpsilon ) )	// it is a zero angle.
		{
			double		sqrDist0	= pt.DistanceSquaredTo( lineBeg );
			double		sqrDist1	= pt.DistanceSquaredTo( lineEnd );

			isOn					= ( MathUtils::LEish( sqrDist0, lineSqrLen, sqrEps ) &&
										MathUtils::LEish( sqrDist1, lineSqrLen, sqrEps ) );
		}
	}

	// result.
	return	( isOn );
}

// checks whether the line intersects plane defined by point and two vectors lying on it.
// returns if the line lies on the plane and the intersection line/point.
//
// idea is based on the paper "A fast triangle to triangle intersection test for collision detection" by Oren Tropp, Ayellet Tal and Ilan Shimshoni.
//
// Description:
// let the line has point 'begLine' and 'endLine', and 'lineVec' is the vector ('begLine'->'endLine'), and ...
// ... the plane is defined by a point and two vectors: 'planePt', 'planeVec0', 'planeVec1'.
// ( planePt + alpha * planeVec0 + beta * planeVec1 = begLine + gamma * lineVec ) describes the intersection between the line and the plane.
// so we have: ( alpha * planeVec0 + beta * planeVec1 - gamma * lineVec = begLine - planePt ).
// in matrix form it becomes (planeVec0|planeVec1|lineVec) * (alpha, beta, -gamma) = vecL, where vecL = begLine - planePt.
// let also denote (planeVec0|planeVec1|lineVec) with A(lineVec).
// to find 'gamma', we can use the Cramer's rule: -gamma = det(A(vecL)) / det(A(lineVec)), where in A(vecL) we use 'vecL' instead of 'lineVec'.
// Optimization: as some 2x2 minors of A(lineVec) and A(vecL) are the same (having 'planeVec0' and 'planeVec1' are preserved), they are calculated just once.
bool VWLine3D::IntersectPlane(const VWPoint3D& planePt, const VWPoint3D& planeVec0, const VWPoint3D& planeVec1,
							  VWLine3D& outIntersLine, bool& outLineOnPlane, double coordEpsilon, double radEpsilon) const
{
	// init.
	bool					hasInters	= false;
	outLineOnPlane						= false;

	// first line.
	const VWPoint3D&		begLine		= this->GetStart();
	const VWPoint3D&		endLine		= this->GetEnd();

	const VWPoint3D&		lineVec		= ( endLine - begLine );
	double					lineLen		= lineVec.Magnitude();

	// check the line.
	if ( MathUtils::Equalish( lineLen, 0.0, coordEpsilon ) )	// degenerate zero-length line.
	{
		if ( begLine.IsOnPlane( planePt, planeVec0, planeVec1, coordEpsilon, radEpsilon ) )
		{
			hasInters					= true;
			outLineOnPlane				= true;
			outIntersLine				= ( *this );			// degenerate point-like line.
		}
	}
	else				// non-degenerate line.
	{
		// prepare the matrix (planeVec0|planeVec1|lineVec).
		VWTransformMatrix	matV0V1T;
		matV0V1T.SetMatrix( planeVec0, planeVec1, lineVec, true );

		// calculating the steady minors.
		double				minorR12C01	= matV0V1T.GetMinor2x2( 1, 2, 0, 1 );	// (rows 1,2; columns 0,1).
		double				minorR02C01	= matV0V1T.GetMinor2x2( 0, 2, 0, 1 );	// (rows 0,2; columns 0,1).
		double				minorR01C01	= matV0V1T.GetMinor2x2( 0, 1, 0, 1 );	// (rows 0,1; columns 0,1).

		// get determinant of the matrix (planeVec0|planeVec1|lineVec) using Laplace's formula for determinant in terms of minors.
		double				detALV		= ( ( lineVec.x /*matV0V1T( 0, 2 ) )*/ * minorR12C01 ) -
											( lineVec.y /*matV0V1T( 1, 2 ) )*/ * minorR02C01 ) +
											( lineVec.z /*matV0V1T( 2, 2 ) )*/ * minorR01C01 ) );

		// check the determinant. Note: use the collinearity epsilon here.
		if ( MathUtils::Equalish( detALV, 0.0, VWPoint3D::sSqrEpsilon ) )
		{
			// zero determinant => 'planeVec0' and 'planeVec1' are collinear (which would be a bad function input or ...
			// ... the vector 'lineVec' is parallel to the plane (defined by 'planePt', 'planeVec0', 'planeVec1').

			// check if an arbitrary point from the line (line segment) lies on the plane.
			if ( begLine.IsOnPlane( planePt, planeVec0, planeVec1, coordEpsilon, radEpsilon ) )
			{
				hasInters				= true;
				outLineOnPlane			= true;
				outIntersLine			= ( *this );
			}
		}
		else
		{
			// prepare the vecL vector.
			const VWPoint3D&	vecL	= ( begLine - planePt );

			// get determinant of the matrix (planeVec0|planeVec1|vecL) using Laplace's formula for determinant in terms of minors.
			double				detAL	= ( ( vecL.x * minorR12C01 ) -
											( vecL.y * minorR02C01 ) +
											( vecL.z * minorR01C01 ) );

			// get gamma.
			double				gamma	= - ( detAL / detALV );

			// prepare the epsilon for checking 'gamma' (for relevancy with the measurements).
			double				epsG	= ( coordEpsilon / lineLen );

			// check if 'gamma' is in the interval [0,1].
			if ( MathUtils::GEish( gamma, 0.0, epsG ) &&
				 MathUtils::LEish( gamma, 1.0, epsG ) )
			{
				// means that the vector 'lineVec' which is ('begLine'->'endLine') intersects the plane.
				hasInters				= true;

				// get the intersection point.
				VWPoint3D		inters	= ( begLine + ( lineVec * gamma ) );

				outIntersLine.SetLine( inters, inters );	// degenerate point-like line.
			}
		}
	}

	// result.
	return	( hasInters );
}

// checks whether the line intersects plane defined by point and two vectors lying on it.
// doesn't return if the line lies on the plane and the intersection line/point. (faster function).
bool VWLine3D::IntersectPlane(const VWPoint3D& planePt, const VWPoint3D& planeVec0, const VWPoint3D& planeVec1,
							  double coordEpsilon, double radEpsilon) const
{
	// init.
	bool					hasInters	= false;

	// first line.
	const VWPoint3D&		begLine		= this->GetStart();
	const VWPoint3D&		endLine		= this->GetEnd();

	const VWPoint3D&		lineVec		= ( endLine - begLine );
	double					lineLen		= lineVec.Magnitude();

	// check the line.
	if ( MathUtils::Equalish( lineLen, 0.0, coordEpsilon ) )	// degenerate zero-length line.
	{
		hasInters						= begLine.IsOnPlane( planePt, planeVec0, planeVec1, coordEpsilon, radEpsilon );
	}
	else				// non-degenerate line.
	{
		// prepare the matrix (planeVec0|planeVec1|lineVec).
		VWTransformMatrix	matV0V1T;
		matV0V1T.SetMatrix( planeVec0, planeVec1, lineVec, true );

		// calculating the steady minors.
		double				minorR12C01	= matV0V1T.GetMinor2x2( 1, 2, 0, 1 );	// (rows 1,2; columns 0,1).
		double				minorR02C01	= matV0V1T.GetMinor2x2( 0, 2, 0, 1 );	// (rows 0,2; columns 0,1).
		double				minorR01C01	= matV0V1T.GetMinor2x2( 0, 1, 0, 1 );	// (rows 0,1; columns 0,1).

		// get determinant of the matrix (planeVec0|planeVec1|lineVec) using Laplace's formula for determinant in terms of minors.
		double				detALV		= ( ( lineVec.x /*matV0V1T( 0, 2 ) )*/ * minorR12C01 ) -
											( lineVec.y /*matV0V1T( 1, 2 ) )*/ * minorR02C01 ) +
											( lineVec.z /*matV0V1T( 2, 2 ) )*/ * minorR01C01 ) );

		// check the determinant. Note: use the collinearity epsilon here.
		if ( MathUtils::Equalish( detALV, 0.0, VWPoint3D::sSqrEpsilon ) )
		{
			// zero determinant => 'planeVec0' and 'planeVec1' are collinear (which would be a bad function input or ...
			// ... the vector 'lineVec' is parallel to the plane (defined by 'planePt', 'planeVec0', 'planeVec1').

			// check if an arbitrary point from the line (line segment) lies on the plane.
			hasInters					= begLine.IsOnPlane( planePt, planeVec0, planeVec1, coordEpsilon, radEpsilon );
		}
		else
		{
			// prepare the vecL vector.
			const VWPoint3D&	vecL	= ( begLine - planePt );

			// get determinant of the matrix (planeVec0|planeVec1|vecL) using Laplace's formula for determinant in terms of minors.
			double				detAL	= ( ( vecL.x * minorR12C01 ) -
											( vecL.y * minorR02C01 ) +
											( vecL.z * minorR01C01 ) );

			// get gamma.
			double				gamma	= - ( detAL / detALV );

			// prepare the epsilon for checking 'gamma' (for relevancy with the measurements).
			double				epsG	= ( coordEpsilon / lineLen );

			// check if 'gamma' is in the interval [0,1].
			if ( MathUtils::GEish( gamma, 0.0, epsG ) &&
				 MathUtils::LEish( gamma, 1.0, epsG ) )
			{
				// means that the vector 'lineVec' which is ('begLine'->'endLine') intersects the plane.
				hasInters				= true;
			}
		}
	}

	// result.
	return	( hasInters );
}

// checks whether the line intersects another line.
// returns if the two lines overlap and the intersection line/point.
//
// idea is based on the paper "A fast triangle to triangle intersection test for collision detection" by Oren Tropp, Ayellet Tal and Ilan Shimshoni.
//
// Description:
// if we denote the first line vector with 'line0Vec' ('line0Beg'->'line0End') and the second one with 'line1Vec' ('line1Beg'->'line1End'), ...
// ... then: line0Beg + alpha * line0Vec = line1Beg + beta * line1Vec describes the intersection between the two infinite lines (if they lie on a 3D plane and are not parallel).
// so we have: alpha * line0Vec - beta * line1Vec = vecL, where vecL = line1Beg - line0Beg.
// crossing both sides of the equation with 'line1Vec' gives: alpha * (line0Vec x line1Vec) = (vecL x line1Vec) (as line1Vec x line1Vec is zero vector).
// dotting with (line0Vec x line1Vec) both sides of the equation leads to: alpha * (line0Vec x line1Vec)*(line0Vec x line1Vec) = (vecL x line1Vec)*(line0Vec x line1Vec).
// but (line0Vec x line1Vec)*(line0Vec x line1Vec) = cos( 0 ) * |(line0Vec x line1Vec)| * |(line0Vec x line1Vec)| = sqr( |line0Vec x line1Vec| )
// so we have alpha * sqr( |line0Vec x line1Vec| ) = (vecL x line1Vec)*(line0Vec x line1Vec) <=>
// alpha = ( (vecL x line1Vec)*(line0Vec x line1Vec) ) / sqr( |line0Vec x line1Vec| ). i.e. alpha = det(vecL|line1Vec|(line0Vec x line1Vec)) / sqr( |line0Vec x line1Vec| )
// similarly
// beta  = ( (line0Vec x vecL)*(line0Vec x line1Vec) ) / sqr( |line0Vec x line1Vec| ). i.e. beta  = det(vecL|line0Vec|(line0Vec x line1Vec)) / sqr( |line0Vec x line1Vec| )
// Optimization: as some 2x2 minors of (vecL|line1Vec|(line0Vec x line1Vec)) and (vecL|line0Vec|(line0Vec x line1Vec)) are the same (having vecL and (line0Vec x line1Vec) being preserved), they are calculated just once.
bool VWLine3D::IntersectLine(const VWLine3D& line, VWLine3D& outIntersLine, bool& outLinesOverlap,
							 double coordEpsilon, double radEpsilon) const
{
	// init.
	bool					hasInters	= false;
	outLinesOverlap						= false;

	// first line (this line).
	const VWPoint3D&		line0Beg	= this->GetStart();
	const VWPoint3D&		line0End	= this->GetEnd();
	const VWPoint3D&		line0Vec	= ( line0End - line0Beg );

	// second line ('line').
	const VWPoint3D&		line1Beg	= line.GetStart();
	const VWPoint3D&		line1End	= line.GetEnd();
	const VWPoint3D&		line1Vec	= ( line1End - line1Beg );

	// check the two lines.
	double					line0Len	= line0Vec.Magnitude();
	double					line1Len	= line1Vec.Magnitude();

	bool					isLine0Deg	= MathUtils::Equalish( line0Len, 0.0, coordEpsilon );
	bool					isLine1Deg	= MathUtils::Equalish( line1Len, 0.0, coordEpsilon );

	if ( isLine0Deg && isLine1Deg )		// both lines are degenerate zero-length lines.
	{
		if ( MathUtils::Equalish( line0Beg, line1Beg, coordEpsilon ) )
		{
			hasInters					= true;
			outIntersLine				= line;			// degenerate point-like line.
			outLinesOverlap				= true;
		}
	}
	else if ( isLine0Deg )				// this line is degenerate.
	{
		if ( line.IsPtOnLine( line0Beg, coordEpsilon, radEpsilon ) )
		{
			hasInters					= true;
			outIntersLine				= ( *this );	// degenerate point-like line.
			outLinesOverlap				= true;
		}
	}
	else if ( isLine1Deg )				// the 'line' is degenerate.
	{
		if ( this->IsPtOnLine( line1Beg, coordEpsilon, radEpsilon ) )
		{
			hasInters					= true;
			outIntersLine				= line;			// degenerate point-like line.
			outLinesOverlap				= true;
		}
	}
	else								// both lines are non-degenerate.
	{
		// prepare the 'vecL' vector.
		const VWPoint3D&	vecL		= ( line1Beg - line0Beg );

		// get cross product (line0Vec x line1Vec).
		const VWPoint3D&	cpL0L1		= ( line0Vec * line1Vec );
		double				sqrCPLen	= cpL0L1.MagnitudeSquared();

		// check the cross product.
		if ( MathUtils::Equalish( sqrCPLen, 0.0, VWPoint3D::sSqrEpsilon ) )
		{
			// means that the two lines are parallel.

			// check whether the lines (line segments) overlap and get the overlapping ends.
			VWPoint3D				endPts[ 2 ];
			size_t					endsCnt		= 0;

			const VWPoint3D*		l0Pts[ 2 ]	= { ( & line0Beg ), ( & line0End ) };
			for ( size_t i = 0 ; ( i < 2 ) && ( endsCnt < 2 ) ; ++ i )
			{
				const VWPoint3D&	pt			= ( * l0Pts[ i ] );
				if ( line.IsPtOnLine( pt, coordEpsilon, radEpsilon ) )
				{
					endPts[ endsCnt ]			= pt;
					++ endsCnt;
				}
			}

			if ( endsCnt < 2 )					// still not all cases examined.
			{
				const VWPoint3D*	l1Pts[ 2 ]	= { ( & line1Beg ), ( & line1End ) };
				for ( size_t i = 0 ; ( i < 2 ) && ( endsCnt < 2 ) ; ++ i )
				{
					const VWPoint3D&	pt		= ( * l1Pts[ i ] );
					if ( this->IsPtOnLine( pt, coordEpsilon, radEpsilon ) &&												// point on this line and ...
						 ( i != 0 || endsCnt != 1 || ! MathUtils::Equalish( endPts[ endsCnt - 1 ], pt, coordEpsilon ) ) )	// ... not already added.
					{
						endPts[ endsCnt ]		= pt;
						++ endsCnt;
					}
				}
			}

			if ( endsCnt > 0 )					// has intersections.
			{
				if		( endsCnt == 1 )		outIntersLine.SetLine( endPts[ 0 ], endPts[ 0 ] );	// degenerate point-like line.
				else if ( endsCnt == 2 )		outIntersLine.SetLine( endPts[ 0 ], endPts[ 1 ] );	// non-degenerate line.

				hasInters						= true;

				// mark if the lines (line segments) overlap.
				outLinesOverlap					= true;
			}
		}
		else
		{
			double			dotLCpL0L1	= ( vecL.GetNormalized() % cpL0L1.GetNormalized() );	// dot product of normalized vectors.

			// check the dot product.
			if ( MathUtils::Equalish( dotLCpL0L1, 0.0, radEpsilon ) )				// i.e. cos(angle) = 0.0 => angle = Pi/2 (90 degrees).
			{
				// this means that both lines lie on a 3D plane, and as they are not parallel, they will intersect each other.

				// prepare the matrix (vecL|line1Vec|(line0Vec x line1Vec)).
				VWTransformMatrix		matLL1CP;
				matLL1CP.SetMatrix( vecL, line1Vec, cpL0L1, true );

				// calculating the steady minors.
				double		minorR12C02	= matLL1CP.GetMinor2x2( 1, 2, 0, 2 );		// (rows 1,2; columns 0,2).
				double		minorR02C02	= matLL1CP.GetMinor2x2( 0, 2, 0, 2 );		// (rows 0,2; columns 0,2).
				double		minorR01C02	= matLL1CP.GetMinor2x2( 0, 1, 0, 2 );		// (rows 0,1; columns 0,2).

				// get determinant of the matrix (vecL|line1Vec|(line0Vec x line1Vec)) using Laplace's formula for determinant in terms of minors.
				double		detLL1CP	= ( ( line1Vec.y /*matLL1CP( 1, 1 )*/ * minorR02C02 ) -
											( line1Vec.x /*matLL1CP( 0, 1 )*/ * minorR12C02 ) -
											( line1Vec.z /*matLL1CP( 2, 1 )*/ * minorR01C02 ) );

				// get alpha.
				double		alpha		= ( detLL1CP / sqrCPLen );

				// prepare the epsilon for checking 'alpha' (for relevancy with the measurements).
				double		eps			= ( coordEpsilon / line1Len );

				// check if alpha is in the interval [0,1].
				if ( MathUtils::GEish( alpha, 0.0, eps ) &&
					 MathUtils::LEish( alpha, 1.0, eps ) )
				{
					// means that the intersection lies on the first line (this line).
					// check whether the intersection lies on the second line ('line')..

					// get the determinant of matrix (vecL|line0Vec|(line0Vec x line1Vec)) (using the steady minors).
					double	detLL0CP	= ( ( line0Vec.y * minorR02C02 ) -
											( line0Vec.x * minorR12C02 ) -
											( line0Vec.z * minorR01C02 ) );

					// get alpha.
					double	beta		= ( detLL0CP / sqrCPLen );

					// prepare the epsilon for checking 'beta' (for relevancy with the measurements).
					eps					= ( coordEpsilon / line0Len );

					// check if beta is in the interval [0,1].
					if ( MathUtils::GEish( beta, 0.0, eps ) &&
						 MathUtils::LEish( beta, 1.0, eps ) )
					{
						// means that the intersection lies on the both lines (line segments).
						hasInters		= true;

						// get the intersection point.
						VWPoint3D	inters	= ( line0Beg + ( line0Vec * alpha ) );

						outIntersLine.SetLine( inters, inters );	// degenerate point-like line.
					}
				}
			}
			// else: does not exist a 3D plane on which both lines lie. so they do not intersect.
		}
	}

	// result.
	return	( hasInters );
}

// checks whether the line intersects another line.
// doesn't return if the two lines overlap and the intersection line/point (faster function).
bool VWLine3D::IntersectLine(const VWLine3D& line, double coordEpsilon, double radEpsilon) const
{
	// init.
	bool					hasInters	= false;

	// first line (this line).
	const VWPoint3D&		line0Beg	= this->GetStart();
	const VWPoint3D&		line0End	= this->GetEnd();
	const VWPoint3D&		line0Vec	= ( line0End - line0Beg );

	// second line ('line').
	const VWPoint3D&		line1Beg	= line.GetStart();
	const VWPoint3D&		line1End	= line.GetEnd();
	const VWPoint3D&		line1Vec	= ( line1End - line1Beg );

	// check the two lines.
	double					line0Len	= line0Vec.Magnitude();
	double					line1Len	= line1Vec.Magnitude();

	bool					isLine0Deg	= MathUtils::Equalish( line0Len, 0.0, coordEpsilon );
	bool					isLine1Deg	= MathUtils::Equalish( line1Len, 0.0, coordEpsilon );

	if ( isLine0Deg && isLine1Deg )		// both lines are degenerate zero-length lines.
	{
		hasInters						= MathUtils::Equalish( line0Beg, line1Beg, coordEpsilon );
	}
	else if ( isLine0Deg )				// this line is degenerate.
	{
		hasInters						= line.IsPtOnLine( line0Beg, coordEpsilon, radEpsilon );
	}
	else if ( isLine1Deg )				// the 'line' is degenerate.
	{
		hasInters						= this->IsPtOnLine( line1Beg, coordEpsilon, radEpsilon );
	}
	else								// both lines are non-degenerate.
	{
		// prepare the 'vecL' vector.
		const VWPoint3D&	vecL		= ( line1Beg - line0Beg );

		// get cross product (line0Vec x line1Vec).
		const VWPoint3D&	cpL0L1		= ( line0Vec * line1Vec );
		double				sqrCPLen	= cpL0L1.MagnitudeSquared();

		// check the cross product.
		if ( MathUtils::Equalish( sqrCPLen, 0.0, VWPoint3D::sSqrEpsilon ) )
		{
			// means that the two lines are parallel.

			// check whether the lines (line segments) overlap (will be possible if both lines lie on a 3D plane).
			hasInters					= line.IsPtOnLine( line0Beg, coordEpsilon, radEpsilon );	// check if 'line0Beg' is on 'line'.
			if ( ! hasInters )			// still not determined.
			{
				hasInters				= this->IsPtOnLine( line1Beg, coordEpsilon, radEpsilon );	// check if 'line1Beg' is on this line.
				if ( ! hasInters )		// still not determined.
				{
					hasInters			= line.IsPtOnLine( line0End, coordEpsilon, radEpsilon );	// check if 'line0End' is on 'line'.
				}
			}
		}
		else
		{
			double			dotLCpL0L1	= ( vecL.GetNormalized() % cpL0L1.GetNormalized() );	// dot product of normalized vectors.

			// check the dot product.
			if ( MathUtils::Equalish( dotLCpL0L1, 0.0, radEpsilon ) )				// i.e. cos(angle) = 0.0 => angle = Pi/2 (90 degrees).
			{
				// this means that both lines lie on a 3D plane, and as they are not parallel, they will intersect each other.

				// prepare the matrix (vecL|line1Vec|(line0Vec x line1Vec)).
				VWTransformMatrix		matLL1CP;
				matLL1CP.SetMatrix( vecL, line1Vec, cpL0L1, true );

				// calculating the steady minors.
				double		minorR12C02	= matLL1CP.GetMinor2x2( 1, 2, 0, 2 );		// (rows 1,2; columns 0,2).
				double		minorR02C02	= matLL1CP.GetMinor2x2( 0, 2, 0, 2 );		// (rows 0,2; columns 0,2).
				double		minorR01C02	= matLL1CP.GetMinor2x2( 0, 1, 0, 2 );		// (rows 0,1; columns 0,2).

				// get determinant of the matrix (vecL|line1Vec|(line0Vec x line1Vec)) using Laplace's formula for determinant in terms of minors.
				double		detLL1CP	= ( ( line1Vec.y /*matLL1CP( 1, 1 )*/ * minorR02C02 ) -
											( line1Vec.x /*matLL1CP( 0, 1 )*/ * minorR12C02 ) -
											( line1Vec.z /*matLL1CP( 2, 1 )*/ * minorR01C02 ) );

				// get alpha.
				double		alpha		= ( detLL1CP / sqrCPLen );

				// prepare the epsilon for checking 'alpha' (for relevancy with the measurements).
				double		eps			= ( coordEpsilon / line1Len );

				// check if alpha is in the interval [0,1].
				if ( MathUtils::GEish( alpha, 0.0, eps ) &&
					 MathUtils::LEish( alpha, 1.0, eps ) )
				{
					// means that the intersection lies on the first line (this line).
					// check whether the intersection lies on the second line ('line')..

					// get the determinant of matrix (vecL|line0Vec|(line0Vec x line1Vec)) (using the steady minors).
					double	detLL0CP	= ( ( line0Vec.y * minorR02C02 ) -
											( line0Vec.x * minorR12C02 ) -
											( line0Vec.z * minorR01C02 ) );

					// get alpha.
					double	beta		= ( detLL0CP / sqrCPLen );

					// prepare the epsilon for checking 'beta' (for relevancy with the measurements).
					eps					= ( coordEpsilon / line0Len );

					// check if beta is in the interval [0,1].
					if ( MathUtils::GEish( beta, 0.0, eps ) &&
						 MathUtils::LEish( beta, 1.0, eps ) )
					{
						// means that the intersection lies on the both lines (line segments).
						hasInters		= true;
					}
				}
			}
			// else: does not exist a 3D plane on which both lines lie. so they do not intersect.
		}
	}

	// result.
	return	( hasInters );
}

// checks whether the line (line segment) intersects the triangle.
// returns if the line lies on the triangle's plane and the intersection line/point.
bool VWLine3D::IntersectTriangle(const VWPoint3D& triPt0, const VWPoint3D& triPt1, const VWPoint3D& triPt2,
								 VWLine3D& outIntersLine, bool& outLineOnTriPlane, double coordEpsilon, double radEpsilon) const
{
	// init.
	bool				hasInters		= false;
	outLineOnTriPlane					= false;

	VWLine3D			intersLine;

	// check if the triangle is degenerate.
	bool				isNonDegen		= true;

	if ( MathUtils::Equalish( triPt0, triPt1, coordEpsilon ) &&
		 MathUtils::Equalish( triPt1, triPt2, coordEpsilon ) )	// the three triangle's points coincide.
	{
		// this is a point-like triangle (all its points coincide).
		// check if it lies on the line.
		if ( this->IsPtOnLine( triPt0, coordEpsilon, radEpsilon ) )
		{
			hasInters					= true;
			outLineOnTriPlane			= true;
			outIntersLine.SetLine( triPt0, triPt0 );	// degenerate point-like line.
		}

		isNonDegen						= false;		// mark as degenerate.
	}
	else
	{
		// check if it is a line-like triangle (collinear points).
		// Note: don't normalize the vectors as we don't expect them to differ greatly in length. such cases will be caught in the standard case.
		VWPoint3D		crossP			= ( ( triPt0 - triPt1 ) * ( triPt2 - triPt1 ) );		// cross product.
		if ( MathUtils::Equalish( crossP.MagnitudeSquared(), 0.0, VWPoint3D::sSqrEpsilon ) )	// degenerate.
		{
			// this is a line-like triangle (collinear points).
			VWLine3D	triLine			= VWPoint3D::GetTriLongestEdge( triPt0, triPt1, triPt2 );

			// check for intersection between lines (line segments).
			bool		linesOverlap;
			if ( this->IntersectLine( triLine, intersLine, linesOverlap, coordEpsilon, radEpsilon ) )
			{
				hasInters				= true;
				outLineOnTriPlane		= linesOverlap;
				outIntersLine			= intersLine;
			}

			isNonDegen					= false;	// mark as degenerate.
		}
	}

	if ( isNonDegen )					// not a degenerate triangle.
	{
		bool			lineOnPlane;
		if ( this->IntersectPlane( triPt0, ( triPt1 - triPt0 ), ( triPt2 - triPt0 ), intersLine, lineOnPlane, coordEpsilon, radEpsilon ) )
		{
			// means that the line intersects the plane.
			// check the intersection.

			if ( lineOnPlane )			// the line lies on the same plane.
			{
				if ( this->IntersectTriangleOnSamePlane( triPt0, triPt1, triPt2, intersLine, coordEpsilon, radEpsilon ) )
				{
					hasInters			= true;
					outLineOnTriPlane	= true;
					outIntersLine		= intersLine;
				}
			}
			else						// it is a single point intersection
			{
				// the intersection line is a degenerate point-like line.
				const VWPoint3D& inters	= intersLine.GetStart();

				if ( inters.IsOnTriangle( triPt0, triPt1, triPt2, coordEpsilon, radEpsilon ) )
				{
					hasInters			= true;
					outLineOnTriPlane	= false;
					outIntersLine.SetLine( inters, inters );	// degenerate point-like line.
				}
			}
		}
	}

	// result.
	return	( hasInters );
}

// checks whether the line (line segment) intersects the triangle.
// doesn't return if the line lies on the triangle's plane and the intersection line/point (faster function).
bool VWLine3D::IntersectTriangle(const VWPoint3D& triPt0, const VWPoint3D& triPt1, const VWPoint3D& triPt2,
								 double coordEpsilon, double radEpsilon) const
{
	// init.
	bool				hasInters		= false;

	// check if the triangle is degenerate.
	bool				isNonDegen		= true;

	if ( MathUtils::Equalish( triPt0, triPt1, coordEpsilon ) &&
		 MathUtils::Equalish( triPt1, triPt2, coordEpsilon ) )	// the three triangle's points coincide.
	{
		// this is a point-like triangle (all its points coincide).
		// check if it lies on the line.
		hasInters						= this->IsPtOnLine( triPt0, coordEpsilon, radEpsilon );

		isNonDegen						= false;		// mark as degenerate.
	}
	else
	{
		// check if it is a line-like triangle (collinear points).
		// Note: don't normalize the vectors as we don't expect them to differ greatly in length. such cases will be caught in the standard case.
		VWPoint3D		crossP			= ( ( triPt0 - triPt1 ) * ( triPt2 - triPt1 ) );		// cross product.
		if ( MathUtils::Equalish( crossP.MagnitudeSquared(), 0.0, VWPoint3D::sSqrEpsilon ) )	// degenerate.
		{
			// this is a line-like triangle (collinear points).
			VWLine3D	triLine			= VWPoint3D::GetTriLongestEdge( triPt0, triPt1, triPt2 );

			// check for intersection between lines (line segments).
			hasInters					= this->IntersectLine( triLine, coordEpsilon, radEpsilon );

			isNonDegen					= false;	// mark as degenerate.
		}
	}

	if ( isNonDegen )					// not a degenerate triangle.
	{
		VWLine3D		intersLine;
		bool			lineOnPlane;
		if ( this->IntersectPlane( triPt0, ( triPt1 - triPt0 ), ( triPt2 - triPt0 ), intersLine, lineOnPlane, coordEpsilon, radEpsilon ) )
		{
			// means that the line intersects the plane.
			// check the intersection.

			if ( lineOnPlane )			// the line lies on the same plane.
			{
				hasInters				= this->IntersectTriangleOnSamePlane( triPt0, triPt1, triPt2, coordEpsilon, radEpsilon );
			}
			else						// it is a single point intersection
			{
				// the intersection line is a degenerate point-like line.
				const VWPoint3D& inters	= intersLine.GetStart();

				hasInters				= inters.IsOnTriangle( triPt0, triPt1, triPt2, coordEpsilon, radEpsilon );
			}
		}
	}

	// result.
	return	( hasInters );
}

// providing that this line and the triangle lie on same 3D plane, checks whether the line intersects the triangle.
// returns the intersection line/point.
bool VWLine3D::IntersectTriangleOnSamePlane(const VWPoint3D& triPt0, const VWPoint3D& triPt1, const VWPoint3D& triPt2,
											VWLine3D& outIntersLine, double coordEpsilon, double radEpsilon) const
{
	// init.
	bool						hasInters		= false;

	// get line ends.
	const VWPoint3D&			lineBeg			= this->GetStart();
	const VWPoint3D&			lineEnd			= this->GetEnd();

	// check if line's ends lie on the triangle.
	bool						begOnTri		= lineBeg.IsOnTriangle( triPt0, triPt1, triPt2, coordEpsilon, radEpsilon );
	bool						endOnTri		= lineEnd.IsOnTriangle( triPt0, triPt1, triPt2, coordEpsilon, radEpsilon );

	if ( begOnTri && endOnTri )					// both line points are on the triangle.
	{
		// means that the intersection coincides with the line.
		hasInters								= true;
		outIntersLine.SetLine( lineBeg, lineEnd );
	}
	else
	{
		// get the maximum possible count of intersections.
		size_t					intersMaxCount	= 2;
		if ( begOnTri || endOnTri )				// one of the line points is on triangle, the other one is outside.
		{
			// search for the single intersection with one of triangle's edges.
			intersMaxCount						= 1;	
		}
		//else: both line points are outside the triangle.

		// collect intersections.
		VWPoint3D				intersPts[ 2 ];
		size_t					intersCnt		= 0;

		VWLine3D				triEdge;

		// prepare an array for the next loop.
		const VWPoint3D*		tri[ 4 ]		= { ( & triPt0 ), ( & triPt1 ), ( & triPt2 ), ( & triPt0 ) };

		// loop the triangle's edges.
		for ( size_t i = 0 ; ( i < 3 ) && ( intersCnt < intersMaxCount ) ; ++ i )
		{
			const VWPoint3D&	pt0				= ( * tri[ i ] );
			const VWPoint3D&	pt1				= ( * tri[ i + 1 ] );

			triEdge.SetLine( pt0, pt1 );		// i-th edge of the triangle.

			VWLine3D			intersLine;
			bool				linesOverlap;
			if ( this->IntersectLine( triEdge, intersLine, linesOverlap, coordEpsilon, radEpsilon ) )
			{
				if ( linesOverlap )				// the lines overlap.
				{
					// use the overlapping.
					intersPts[ 0 ]				= intersLine.GetStart();
					intersPts[ 1 ]				= intersLine.GetEnd();
					intersCnt					= 2;
				}
				else							// not overlapping.
				{
					// use any end of the 'intersLine' (both ends coincide).
					intersPts[ intersCnt ]		= intersLine.GetStart();
					++ intersCnt;
				}
			}
		}

		// check.
		if ( intersCnt > 0 )					// intersections found.
		{
			if ( intersCnt == 2 )				// two intersection points found.
			{
				outIntersLine.SetLine( intersPts[ 0 ], intersPts[ 1 ] );
			}
			else if ( intersCnt == 1 )			// one intersection point found.
			{
				outIntersLine.SetStart( intersPts[ 0 ] );	// set it.

				// set the other one.
				if		( begOnTri )			outIntersLine.SetEnd( lineBeg );
				else if ( endOnTri )			outIntersLine.SetEnd( lineEnd );
				else							outIntersLine.SetEnd( intersPts[ 0 ] );	// touching.
			}

			hasInters							= true;
		}
	}

	// result.
	return	( hasInters );
}

// providing that this line and the triangle lie on same 3D plane, checks whether the line intersects the triangle.
// doesn't return the intersection line/point (faster function).
bool VWLine3D::IntersectTriangleOnSamePlane(const VWPoint3D& triPt0, const VWPoint3D& triPt1, const VWPoint3D& triPt2,
											double coordEpsilon, double radEpsilon) const
{
	// init.
	bool						hasInters	= false;

	// get line ends.
	const VWPoint3D&			lineBeg		= this->GetStart();
	const VWPoint3D&			lineEnd		= this->GetEnd();

	// check if line's ends lie on the triangle.
	bool						begOnTri	= lineBeg.IsOnTriangle( triPt0, triPt1, triPt2, coordEpsilon, radEpsilon );
	bool						endOnTri	= lineEnd.IsOnTriangle( triPt0, triPt1, triPt2, coordEpsilon, radEpsilon );

	if ( begOnTri && endOnTri )				// both line points are on the triangle.
	{
		// means that the intersection coincides with the line.
		hasInters							= true;
	}
	else
	{
		// check for intersections.
		VWLine3D				triEdge;

		// prepare an array for the next loop.
		const VWPoint3D*		tri[ 4 ]	= { ( & triPt0 ), ( & triPt1 ), ( & triPt2 ), ( & triPt0 ) };

		// loop the triangle's edges.
		for ( size_t i = 0 ; i < 3 ; ++ i )
		{
			const VWPoint3D&	pt0			= ( * tri[ i ] );
			const VWPoint3D&	pt1			= ( * tri[ i + 1 ] );

			triEdge.SetLine( pt0, pt1 );	// i-th edge of the triangle.

			if ( this->IntersectLine( triEdge, coordEpsilon, radEpsilon ) )
			{
				hasInters					= true;
				break;
			}
		}
	}

	// result.
	return	( hasInters );
}

// checks whether a line segment lies in the triangle (both line ends are in the triangle).
bool VWLine3D::IsOnTriangle(const VWPoint3D& triPt0, const VWPoint3D& triPt1, const VWPoint3D& triPt2,
							double coordEpsilon, double radEpsilon) const
{
	// result.
	return	( this->GetStart().IsOnTriangle( triPt0, triPt1, triPt2, coordEpsilon, radEpsilon ) &&
			  this->GetEnd().IsOnTriangle(	 triPt0, triPt1, triPt2, coordEpsilon, radEpsilon ) );
}
//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "Prefix/StdAfx.h"

using namespace VWFC::Math;

VWLine2D::VWLine2D()
{
}

VWLine2D::VWLine2D(double x1, double y1, double x2, double y2)
{
	this->SetLine( x1, y1, x2, y2 );
}

VWLine2D::VWLine2D(const VWPoint2D& begPt, const VWPoint2D& endPt)
{
	this->SetLine( begPt, endPt );
}

VWLine2D::VWLine2D(const VWLine2D& src)
{
	m_ptStart	= src.m_ptStart;
	m_ptEnd		= src.m_ptEnd;
}

VWLine2D::~VWLine2D()
{
}

VWLine2D& VWLine2D::operator=(const VWLine2D& src)
{
	m_ptStart	= src.m_ptStart;
	m_ptEnd		= src.m_ptEnd;
	return *this;
}

const VWPoint2D& VWLine2D::GetStart() const
{
	return m_ptStart;
}

VWPoint2D& VWLine2D::GetStart()
{
	return m_ptStart;
}

const VWPoint2D& VWLine2D::GetEnd() const
{
	return m_ptEnd;
}

VWPoint2D& VWLine2D::GetEnd()
{
	return m_ptEnd;
}

void VWLine2D::GetLine(VWPoint2D& outPtStart, VWPoint2D& outPtEnd) const
{
	outPtStart		= m_ptStart;
	outPtEnd		= m_ptEnd;
}

void VWLine2D::SetStart(const VWPoint2D& pt)
{
	m_ptStart		= pt;
}

void VWLine2D::SetEnd(const VWPoint2D& pt)
{
	m_ptEnd			= pt;
}

void VWLine2D::SetLine(double x1, double y1, double x2, double y2)
{
	m_ptStart.x		= x1;
	m_ptStart.y		= y1;
	m_ptEnd.x		= x2;
	m_ptEnd.y		= y2;
}

void VWLine2D::SetLine(const VWPoint2D& ptStart, const VWPoint2D& ptEnd)
{
	m_ptStart		= ptStart;
	m_ptEnd			= ptEnd;
}

void VWLine2D::ReverseSides()
{
	VWPoint2D	pt	= m_ptStart;
	m_ptStart		= m_ptEnd;
	m_ptEnd			= pt;
}

VWLine2D VWLine2D::operator+(const VWPoint2D& p) const
{
	VWLine2D	line	= *this;
	line				+= p;
	return line;
}

VWLine2D VWLine2D::operator-(const VWPoint2D& p) const
{
	VWLine2D	line	= *this;
	line				-= p;
	return line;
}

bool VWLine2D::Subtract(const VWLine2D& tool, std::vector<VWLine2D> results) const
{
	bool intersected = true;
	results.clear();
	if(MathUtils::Equalish(GetDirection().CrossProductMagnitude(tool.GetDirection()), 0, VWPoint2D::sEpsilonCollinear))
	{
		bool toolStartOnThis = PtOnLine(tool.GetStart(), VWPoint2D::sEpsilon); 
		bool toolEndOnThis = PtOnLine(tool.GetEnd(), VWPoint2D::sEpsilon); 
		bool thisStartOnTool = tool.PtOnLine(this->GetStart(), VWPoint2D::sEpsilon); 
		bool thisEndOnTool = tool.PtOnLine(this->GetEnd(), VWPoint2D::sEpsilon); 

		if(toolStartOnThis && toolEndOnThis)
		{
			if(RelativeCoords(tool.GetStart()).x < RelativeCoords(tool.GetEnd()).x)
			{
				results.push_back(VWLine2D(GetStart(), tool.GetStart()));
				results.push_back(VWLine2D(tool.GetEnd(), GetEnd()));
			}
			else
			{
				results.push_back(VWLine2D(GetStart(), tool.GetEnd()));
				results.push_back(VWLine2D(tool.GetEnd(), GetStart()));
			}
		}
		else if(thisStartOnTool && thisEndOnTool)
			results.push_back(*this);
		else if(thisStartOnTool)
		{
			if(toolStartOnThis)
				results.push_back(VWLine2D(GetStart(), tool.GetStart()));
			else
				results.push_back(VWLine2D(GetStart(), tool.GetEnd()));
		}
		else if(thisEndOnTool)
		{
			if(toolStartOnThis)
				results.push_back(VWLine2D(tool.GetStart(), GetEnd()));
			else
				results.push_back(VWLine2D(tool.GetEnd(), GetEnd()));
		}
		else 
			intersected = false;
		
	}	
	else 
		intersected = false;

	return intersected;
}

VWLine2D VWLine2D::operator*(double scalar) const
{
	VWLine2D	line	= *this;
	line				*= scalar;
	return line;
}

VWLine2D VWLine2D::operator/(double scalar) const
{
	VWLine2D	line	= *this;
	line				/= scalar;
	return line;
}

VWLine2D& VWLine2D::operator+=(const VWPoint2D& p)
{
	m_ptStart		+= p;
	m_ptEnd			+= p;
	return *this;
}

VWLine2D& VWLine2D::operator-=(const VWPoint2D& p)
{
	m_ptStart		-= p;
	m_ptEnd			-= p;
	return *this;
}

VWLine2D& VWLine2D::operator*=(double scalar)
{
	m_ptStart		*= scalar;
	m_ptEnd			*= scalar;
	return *this;
}

VWLine2D& VWLine2D::operator/=(double scalar)
{
	m_ptStart		/= scalar;
	m_ptEnd			/= scalar;
	return *this;
}

//////////////////////////////////////////////////////////////////////////
// math functions
//////////////////////////////////////////////////////////////////////////

// return the center point of the line
VWPoint2D VWLine2D::CenterPt() const
{
	return ( m_ptStart + m_ptEnd ) / 2;
}

// return the length of the line
double VWLine2D::GetLength() const
{
	return (m_ptStart-m_ptEnd).Magnitude();
}

void VWLine2D::CalcLineEquation(double& outA, double& outB, double& outC) const
{
	VWPoint2D	dir	= m_ptEnd - m_ptStart;
	VWPoint2D	perp( - dir.y, dir.x );
	perp.Normalize();

	outA			= perp.x;
	outB			= perp.y;
	outC			= - (m_ptStart.x * outA + m_ptStart.y * outB);
}

bool VWLine2D::PtOnLineStart(const VWPoint2D& pt, double dEpsilon) const
{
	return pt.Equal( m_ptStart, dEpsilon );
}

bool VWLine2D::PtOnLineEnd(const VWPoint2D& pt, double dEpsilon) const
{
	return pt.Equal( m_ptEnd, dEpsilon );
}

bool VWLine2D::PtOnLinePoints(const VWPoint2D& pt, double dEpsilon) const
{
	return pt.Equal( m_ptStart, dEpsilon ) || pt.Equal( m_ptEnd, dEpsilon );
}

// checks if point is on left side of the line.
bool VWLine2D::PtOnLeft(const VWPoint2D& pt) const
{
	return	( VWLine2D::PtOnLeftOfLine( pt, m_ptStart, m_ptEnd ) );
}

// fast check if a point is near the line segment.
bool VWLine2D::PtNearLine(const VWPoint2D& pt, VWPoint2D& outClosestPt, double tolerance) const
{
	return	( VWLine2D::PtNearLine( pt, m_ptStart, m_ptEnd, outClosestPt, tolerance ) );
}

// return true if the specified point is on the line within an epsilon
bool VWLine2D::PtOnLine(const VWPoint2D& pt, double dEpsilon) const
{
	return VWLine2D::PtOnLine( pt, m_ptStart, m_ptEnd, dEpsilon );
}

bool VWLine2D::PtOnLine(const VWPoint2D& pt, const VWPoint2D& lineA, const VWPoint2D& lineB, double dEpsilon)
{
	bool		bPtOnLine	= false;
	double		AB			= (lineB - lineA).Magnitude();
	double		AC			= (pt - lineA).Magnitude();
	double		CB			= (lineB - pt).Magnitude();

	if ( Abs( AB - (AC + CB) ) < dEpsilon ) {
		VWPoint2D	temp_pt		= pt;
		temp_pt.RelativeCoords( lineA, lineB );
		bPtOnLine				= ( temp_pt.y < 0 ? -temp_pt.y : temp_pt.y ) < dEpsilon;
	}

	return bPtOnLine;
}

// fast check if a point lies on a line segment.
bool VWLine2D::PtOnLine_Fast(const VWPoint2D& pt, const VWPoint2D& lnPt1, const VWPoint2D& lnPt2, double epsilon)
{
	bool					isOnLine	= false;

	// get line bounding box.
	VWRectangle2D			bboxLine(	lnPt1.x, lnPt2.x,	// left / right.
										lnPt1.y, lnPt2.y );	// top / bottom.

	if ( MathUtils::Equalish( bboxLine.GetWidth(),	0.0, epsilon ) ||
		 MathUtils::Equalish( bboxLine.GetHeight(),	0.0, epsilon ) )	// the line bounding box is too narrow.
	{
		// use the standard check here.
		isOnLine						= VWLine2D::PtOnLine( pt, lnPt1, lnPt2, epsilon );
	}
	else																// the line bounding box is wide enough.
	{
		// check if point is inside the line bounding box.
		// this will mean that point might lie on the line segment (limiting the search area).
		if ( bboxLine.IsPtInside( pt, epsilon ) )
		{
			// get the squared epsilon.
			double			sqrEpsilon	= ( epsilon * epsilon );

			double			sqrLineLen	= VWPoint2D::DistanceSqare( lnPt1.x, lnPt1.y, lnPt2.x, lnPt2.y );
			if ( sqrLineLen > sqrEpsilon )				// it is a correct line (its ends doesn't coincide).
			{
				// get squared distance to line.
				double		A			= ( (lnPt2.x - lnPt1.x) * (lnPt1.y - pt.y) - (lnPt1.x - pt.x) * (lnPt2.y - lnPt1.y) );
				double		sqrDist		= ( (A * A) / sqrLineLen );
				if ( sqrDist < sqrEpsilon )
				{
					isOnLine			= true;
				}
			}
		}
	}

	// result.
	return	isOnLine;
}

// get the angle 0 .. 90 from this line to the specified line
double VWLine2D::GetAngle90(const VWLine2D& line) const
{
	double_gs	lineLen		= line.GetLength();
	if ( DoubleIsNearlyZero( lineLen ) )
		return 0.0;

	VWPoint2D	projB1		= this->PtPerpLine( line.m_ptStart );
	VWPoint2D	projB2		= this->PtPerpLine( line.m_ptEnd );
	double		mag			= ( projB1 - projB2 ).Magnitude();
	double		cosalpha	= mag / lineLen;
	if ( cosalpha+0.00001 > 1 )
		cosalpha = 1.0;
	double		alpha		= acos( cosalpha );

	return MathUtils::Rad2Deg( alpha );
}

VWPoint2D VWLine2D::GetDirection() const
{
	VWPoint2D	dir		= m_ptEnd - m_ptStart;
	dir.Normalize();
	return dir;
}

// teturns a point on this line which is closest to the input point.
VWPoint2D VWLine2D::PtPerpLine(const VWPoint2D& pt) const
{
	VWPoint2D		temp_pt		= this->RelativeCoords( pt );

	VWPoint2D		e			= (m_ptEnd - m_ptStart).Normalize();
	VWPoint2D		perpLine	= m_ptStart + (e * temp_pt.x);
	return perpLine;
}

VWPoint2D VWLine2D::PtPerpLine(double x, double y) const
{
	return this->PtPerpLine( VWPoint2D( x, y ) );
}

VWPoint2D VWLine2D::PtPerpLineSeg(const VWPoint2D& pt) const
{
	double ds = pt.DistanceTo(this->m_ptStart);
	double de = pt.DistanceTo(this->m_ptEnd);
	if( ds <= this->GetLength() && de <= this->GetLength() )
	{
		return this->PtPerpLine( pt );
	}
	else if (ds < de) return this->m_ptStart;
	else return this->m_ptEnd;
}

// returns the closest point to this line segment or the closest segment end, also returns the squared distance to the found point. optimized function !
VWPoint2D VWLine2D::PtPerpLineSeg(const VWPoint2D& pt, double& outSqrDist) const
{
	return	( VWLine2D::PtPerpLineSeg( pt, m_ptStart, m_ptEnd, outSqrDist) );
}

// return the distance from the specified point to the line
double VWLine2D::Distance(const VWPoint2D& pt) const
{
	return this->Distance( pt.x, pt.y );
}

double VWLine2D::Distance(double x, double y) const
{
	double	distance	= VWLine2D::Distance( x, y, m_ptStart.x, m_ptStart.y, m_ptEnd.x, m_ptEnd.y );

#ifdef _DEBUG
	// innser test of the routine
	VWPoint2D	pt( x, y );
	VWPoint2D	projPt	= this->PtPerpLine( pt );
	double	oldWayDist	= projPt.DistanceTo( pt );
	VWFC_ASSERT( Abs(distance-oldWayDist) < 0.0001 );
#endif

	return distance;
}

double VWLine2D::DistanceSeg(const VWPoint2D& pt) const
{
	VWPoint2D relPnt = this->RelativeCoords(pt);
	double result;
	if( relPnt.x > this->GetLength() ) result = this->GetEnd().DistanceTo( pt );
	else if( relPnt.x < 0 ) result = this->GetStart().DistanceTo( pt );
	else result = this->Distance( pt );

	return result;
}

// return true if the specified two points are on the same side of the line
bool VWLine2D::AreOnSameSide(double x1, double y1, double x2, double y2)
{
	double A, B, C;
	this->CalcLineEquation( A, B, C );
	bool sign1	= A * x1 + B * y1 + C >= 0;
	bool sign2	= A * x2 + B * y2 + C >= 0;
	return sign1 == sign2;
}

bool VWLine2D::AreOnSameSide(const VWPoint2D& a, const VWPoint2D& b)
{
	return this->AreOnSameSide( a.x, a.y, b.x, b.y );
}

// gets the bounding box of this line.
VWRectangle2D VWLine2D::GetLineBounds() const
{
	// reorder coordinates.
	double			xMin, yMin, xMax, yMax;

	if ( m_ptStart.x < m_ptEnd.x )	{ xMin = m_ptStart.x;	xMax = m_ptEnd.x;	}
	else							{ xMin = m_ptEnd.x;		xMax = m_ptStart.x;	}
	if ( m_ptStart.y < m_ptEnd.y )	{ yMin = m_ptStart.y;	yMax = m_ptEnd.y;	}
	else							{ yMin = m_ptEnd.y;		yMax = m_ptStart.y;	}

	// result.
	return	( VWRectangle2D( xMin /*left*/, xMax /*right*/, yMax /*top*/, yMin /*bottom*/ ) );
}

// intersect the infinite lines. The result point can be outside the line segments
// return false if the lines are parallel
bool VWLine2D::IntersectLines(const VWLine2D& line, VWPoint2D& outIntersPt) const
{
	bool			bParallel, bIntOnSeg1, bIntOnSeg2;
	VWLine2D::IntersectLines( this->m_ptStart, this->m_ptEnd, line.m_ptStart, line.m_ptEnd, outIntersPt, bParallel, bIntOnSeg1, bIntOnSeg2 );
	return ! bParallel;
}

bool VWLine2D::IntersectLines(const VWPoint2D& a, const VWPoint2D& b, VWPoint2D& outIntersPt) const
{
	bool			bParallel, bIntOnSeg1, bIntOnSeg2;
	VWLine2D::IntersectLines( this->m_ptStart, this->m_ptEnd, a, b, outIntersPt, bParallel, bIntOnSeg1, bIntOnSeg2 );
	return ! bParallel;
}

// intersect the infinite lines. The result point can be outside the line segments
// return false if the lines are parallel
// outPtOnLineSegs returns true if the intersection point lies on both line segments
bool VWLine2D::IntersectLines(const VWLine2D& line, VWPoint2D& outIntersPt, bool& outPtOnLineSegs) const
{
	bool			bParallel, bIntOnSeg1, bIntOnSeg2;
	VWLine2D::IntersectLines( this->m_ptStart, this->m_ptEnd, line.m_ptStart, line.m_ptEnd, outIntersPt, bParallel, bIntOnSeg1, bIntOnSeg2 );
	outPtOnLineSegs		= bIntOnSeg1 && bIntOnSeg2;
	return ! bParallel;
}

bool VWLine2D::IntersectLines(const VWPoint2D& a, const VWPoint2D& b, VWPoint2D& outIntersPt, bool& outPtOnLineSegs) const
{
	bool			bParallel, bIntOnSeg1, bIntOnSeg2;
	VWLine2D::IntersectLines( this->m_ptStart, this->m_ptEnd, a, b, outIntersPt, bParallel, bIntOnSeg1, bIntOnSeg2 );
	outPtOnLineSegs		= bIntOnSeg1 && bIntOnSeg2;
	return ! bParallel;
}

// interset the line segments.
// return false if the lines are parallel or the line segments
// doest intersect each oter in the bound of the segments
bool VWLine2D::IntersectLineSegments(const VWLine2D& line, VWPoint2D& outIntersPt) const
{
	bool			bParallel, bIntOnSeg1, bIntOnSeg2;
	VWLine2D::IntersectLines( this->m_ptStart, this->m_ptEnd, line.m_ptStart, line.m_ptEnd, outIntersPt, bParallel, bIntOnSeg1, bIntOnSeg2 );
	return ! bParallel && bIntOnSeg1 && bIntOnSeg2;
}

bool VWLine2D::IntersectLineSegments(const VWPoint2D& a, const VWPoint2D& b, VWPoint2D& outIntersPt) const
{
	bool			bParallel, bIntOnSeg1, bIntOnSeg2;
	VWLine2D::IntersectLines( this->m_ptStart, this->m_ptEnd, a, b, outIntersPt, bParallel, bIntOnSeg1, bIntOnSeg2 );
	return ! bParallel && bIntOnSeg1 && bIntOnSeg2;
}

// only check if line segments intersect. for faster check.
bool VWLine2D::AreLineSegmentsIntersecting(const VWLine2D& line, double dEpsilon) const
{
	return	VWLine2D::AreLineSegmentsIntersecting( this->m_ptStart, this->m_ptEnd, line.m_ptStart, line.m_ptEnd, dEpsilon );
}

bool VWLine2D::AreLineSegmentsIntersecting(const VWPoint2D& a, const VWPoint2D& b, double dEpsilon) const
{
	return	VWLine2D::AreLineSegmentsIntersecting( this->m_ptStart, this->m_ptEnd, a, b, dEpsilon );
}

// only check if line segments intersect, returns intersection coordinates. this function is robust and fast.
// if there is intersection, the intersection point and 'outParallel' will be correctly calculated, otherwise don't count on it !
bool VWLine2D::AreLineSegmentsIntersecting(const VWLine2D& line, VWPoint2D& outIntersPt, bool& outParallel, double epsilon) const
{
	return	VWLine2D::AreLineSegmentsIntersecting( this->m_ptStart, this->m_ptEnd, line.m_ptStart, line.m_ptEnd, outIntersPt, outParallel, epsilon );
}

// return translated point into a coordinate system defined by this line.
VWPoint2D VWLine2D::RelativeCoords(const VWPoint2D& pt) const
{
	VWPoint2D		p	= pt;
	p.RelativeCoords( m_ptStart, m_ptEnd );
	return p;
}

// rotate this point at specified angle in degrees and center point
void VWLine2D::RotateAtDeg(const VWPoint2D& centerPt, double_gs dDegAngle)
{
	m_ptStart.RotateAtDeg( centerPt, dDegAngle );
	m_ptEnd.RotateAtDeg( centerPt, dDegAngle );
}

// rotate this point at specified angle in radians and center point
void VWLine2D::RotateAtRad(const VWPoint2D& centerPt, double_gs dRadAngle)
{
	m_ptStart.RotateAtRad( centerPt, dRadAngle );
	m_ptEnd.RotateAtRad( centerPt, dRadAngle );
}

// intersects line [(p1)(p2)] with [(p3)(p4)]
void VWLine2D::IntersectLines(const VWPoint2D& p1, const VWPoint2D& p2, const VWPoint2D& p3, const VWPoint2D& p4, VWPoint2D& outInters, bool& outParallel, bool& outOnSegment1, bool& outOnSegment2)
{
	VWLine2D::IntersectLines( p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y, outInters.x, outInters.y, outParallel, outOnSegment1, outOnSegment2, VWPoint2D::sEpsilon );
}

// intersects line [(x1,y1)(x2,y2)] with [(x3,y3)(x4,y4)]
void VWLine2D::IntersectLines(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double& outIntersX, double& outIntersY, bool& outParallel, bool& outOnSegment1, bool& outOnSegment2, double dEpsilon)
{
	bool	onSeg1Pt1, onSeg1Pt2;
	VWLine2D::IntersectLines( x1, y1, x2, y2, x3, y3, x4, y4, outIntersX, outIntersY, outParallel, onSeg1Pt1, onSeg1Pt2, outOnSegment1, outOnSegment2, dEpsilon );
}

// intersects line [(x1,y1)(x2,y2)] with [(x3,y3)(x4,y4)]
void VWLine2D::IntersectLines(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double& outIntersX, double& outIntersY, bool& outParallel, bool& outOnSeg1Pt1, bool& outOnSeg1Pt2, bool& outOnSegment1, bool& outOnSegment2, double epsilon)
{
	double		x2mx1		= (x2 - x1);
	double		x4mx3		= (x4 - x3);
	double		y2my1		= (y2 - y1);
	double		y4my3		= (y4 - y3);

	// get the cross product length.
	double		t			= ( (y4my3 * x2mx1) - (x4mx3 * y2my1) );

	// note: this following parallelism check is enough !
	if ( Abs(t) > epsilon )	// the lines are not parallel.
	{
		double	x1mx3		= (x1 - x3);
		double	y1my3		= (y1 - y3);

		double	ua			= ( ( (x4mx3 * y1my3) - (y4my3 * x1mx3) ) / t );
		double	ub			= ( ( (x2mx1 * y1my3) - (y2my1 * x1mx3) ) / t );

		outIntersX			= ( x1 + (ua * x2mx1) );
		outIntersY			= ( y1 + (ua * y2my1) );

		double	negEps		= (-epsilon);
		double	onePlusEps	= (1.0 + epsilon);

		outParallel			= false;
		outOnSegment1		= (negEps < ua) && (ua < onePlusEps);			// is 'ua' in [0,1] interval ?
		outOnSegment2		= (negEps < ub) && (ub < onePlusEps);			// is 'ub' in [0,1] interval ?
		outOnSeg1Pt1		= (negEps < ua) && (ua < epsilon);				// is 'ua' approximately 0.0 ?
		outOnSeg1Pt2		= ((1.0 - epsilon) < ua) && (ua < onePlusEps);	// is 'ua' approximately 1.0 ?
	}
	else		// collinear lines.
	{
		outParallel			= true;
		outOnSeg1Pt1		= false;
		outOnSeg1Pt2		= false;
		outOnSegment1		= false;
		outOnSegment2		= false;
	}
}

// intersects the infinite line [(x1,y1)(x2,y2)] with the infinite line [(x3,y3)(x4,y4)].
// returns the intersection point and whether it lies on line segment 1, on line segment 2, ...
// uses different epsilons for checking collinearity and coordinates closeness.
// note: the collinearity check is stable.
void VWLine2D::IntersectLines(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double& outIntersX, double& outIntersY, bool& outParallel, bool& outOnSeg1Pt1, bool& outOnSeg1Pt2, bool& outOnSegment1, bool& outOnSegment2, double epsCoord, double epsCollinear)
{
	double				x2mx1			= (x2 - x1);
	double				x4mx3			= (x4 - x3);
	double				y2my1			= (y2 - y1);
	double				y4my3			= (y4 - y3);

	// get lines' lengths.
	double				line1SqrLen		= ( (x2mx1 * x2mx1) + (y2my1 * y2my1) );
	double				line2SqrLen		= ( (x4mx3 * x4mx3) + (y4my3 * y4my3) );

	double				sqrEpsCoord		= sqr( epsCoord );

	if ( line1SqrLen > sqrEpsCoord && line1SqrLen > sqrEpsCoord )	// note: lengths are already >= 0 for sure.
	{
		// get the cross product length.
		double			t				= ( (y4my3 * x2mx1) - (x4mx3 * y2my1) );

		// since it is collinearity check it would be good to first normalize the cross product length.
		// otherwise, if the two lines differ greatly in length then the result becomes unstable.

		// normalize:
		double			tNorm			= ( t / sqrt(line1SqrLen * line2SqrLen) );

		// note: this following parallelism check is enough !
		if ( Abs(tNorm) > epsCollinear )	// the lines are not parallel.
		{
			double		x1mx3			= (x1 - x3);
			double		y1my3			= (y1 - y3);

			double		ua				= ( ( (x4mx3 * y1my3) - (y4my3 * x1mx3) ) / t );
			double		ub				= ( ( (x2mx1 * y1my3) - (y2my1 * x1mx3) ) / t );

			outIntersX					= ( x1 + (ua * x2mx1) );
			outIntersY					= ( y1 + (ua * y2my1) );

			double		negEps			= (-epsCoord);
			double		onePlusEps		= (1.0 + epsCoord);

			outParallel					= false;
			outOnSegment1				= (negEps < ua) && (ua < onePlusEps);			// is 'ua' in [0,1] interval ?
			outOnSegment2				= (negEps < ub) && (ub < onePlusEps);			// is 'ub' in [0,1] interval ?
			outOnSeg1Pt1				= (negEps < ua) && (ua < epsCoord);				// is 'ua' approximately 0.0 ?
			outOnSeg1Pt2				= ((1.0 - epsCoord) < ua) && (ua < onePlusEps);	// is 'ua' approximately 1.0 ?
		}
		else			// collinear lines.
		{
			outParallel					= true;
			outOnSeg1Pt1				= false;
			outOnSeg1Pt2				= false;
			outOnSegment1				= false;
			outOnSegment2				= false;
		}
	}
	// else: degenerate zero-length lines.
}

// This intersection code is based on a parametric definition of a line: p(a1, a2) = a1 + (1-t)(a2-a1) and p(b1, b2) = b1 + (1-s)(b2 - b1)
// t and s are includede [0,1].
// parameters:
// Input       a1:			start point of the first line.
//			   a2:			end point of the first line.
// 			   b1:			start point of the second line.
//			   b2:			end point of the second line.
// Output      parallel:	true if the two lines are parallel.
//			   intersect:	true if the intersection point is inside of the two lines.
//			   int0:		the intersection point.
// Author : Abdel 11/21/2005
void VWLine2D::IntersectLines(const VWPoint2D& a1, const VWPoint2D& a2, const VWPoint2D& b1, const VWPoint2D& b2, bool& intersect, bool& parallel, VWPoint2D& int0, double epsilon)
{
	// this is a determinant of the (t,s) linear equation. Geometrically we can notice that it is a a cross product of vectors
	// a2 - a1 and b2 - b1, if it is nil then the lines are parallel.
	double	part1		= ( b2.x - b1.x ) * ( a1.y - a2.y );
	double	part2		= ( a1.x - a2.x ) * ( b2.y - b1.y );

	parallel			= false;

	if ( MathUtils::Equalish( part1, part2, epsilon ) )
	{
		intersect		= false;
		parallel		= true;
	}
	else
	{
		double	d		= ( part1 - part2 );
		double	s		= ( ( a1.x - b1.x ) * ( a1.y - a2.y ) + ( a1.y - b1.y )	* ( a2.x - a1.x ) ) / d;
		double	t		= ( ( a1.x - b1.x ) * ( b1.y - b2.y ) + ( a1.y - b1.y )	* ( b2.x - b1.x ) ) / d;

		if ( a1.x == a2.x )
		{
			int0.x		= a1.x;
			int0.y		= s * ( b2.y - b1.y ) + b1.y;
			if ( MathUtils::IsBetween( int0, a1, a2, epsilon ) )
			{
				t		= 0.5;
			}
		}
		else if ( b1.x == b2.x )
		{
			int0.x		= b1.x;
			int0.y		= t * ( a2.y - a1.y ) + a1.y;
			if ( MathUtils::IsBetween( int0, b1, b2, epsilon ) )
			{
				s		= 0.5;
			}
		}
		else
		{
			int0.x		= t * ( a2.x - a1.x ) + a1.x;
			int0.y		= t * ( a2.y - a1.y ) + a1.y;
		}
		if( MathUtils::Greaterish(	s, 0, epsilon ) && 
			MathUtils::Lesserish(	s, 1, epsilon ) &&
			MathUtils::Greaterish(	t, 0, epsilon ) &&
			MathUtils::Lesserish(	t, 1, epsilon ) )
		{
			intersect	= true;
		}
		else
		{
			intersect	= false;
		}
	}
}

// checks if line [pt1,pt2] intersects with line [pt3,pt4], returns intersection line/point.
// note that even if lines are parallel, it checks for overlapping between them considered as intersection.
/*static*/ void VWLine2D::IntersectLines(const VWPoint2D& pt1, const VWPoint2D& pt2, const VWPoint2D& pt3, const VWPoint2D& pt4, VWLine2D& outIntersLine, bool& outParallel, bool& outOnSeg1, bool& outOnSeg2, double epsCoord, double epsCollinear)
{
	// init.
	outOnSeg1							= false;
	outOnSeg2							= false;
	outParallel							= false;

	// check whether bounding boxes of the line segments have common area.
	if ( VWLine2D::DoLineSegmentsBoundsIntersect( pt1.x, pt1.y, pt2.x, pt2.y, pt3.x, pt3.y, pt4.x, pt4.y, epsCoord ) )
	{
		// get lines' vectors.
		const VWPoint2D&	line1Vec	= ( pt2 - pt1 );
		const VWPoint2D&	line2Vec	= ( pt4 - pt3 );

		// check the two lines.
		double				line1Len	= line1Vec.Magnitude();
		double				line2Len	= line2Vec.Magnitude();

		bool				isLine1Deg	= MathUtils::Equalish( line1Len, 0.0, epsCoord );
		bool				isLine2Deg	= MathUtils::Equalish( line2Len, 0.0, epsCoord );

		if ( isLine1Deg && isLine2Deg )	// both lines are degenerate zero-length lines.
		{
			if ( MathUtils::Equalish( pt1, pt3, epsCoord ) )
			{
				outOnSeg1				= true;
				outOnSeg2				= true;
				outParallel				= true;

				// the intersection.
				outIntersLine.SetLine( pt1, pt1 );	// degenerate point-like line.
			}
		}
		else if ( isLine1Deg )			// first line is degenerate.
		{
			VWPoint2D		closestPt;
			if ( VWLine2D::PtNearLine( pt1, pt3, pt4, closestPt, epsCoord ) )
			{
				outOnSeg1				= true;
				outOnSeg2				= true;
				outParallel				= true;

				// the intersection.
				outIntersLine.SetLine( closestPt, closestPt );	// degenerate point-like line.
			}
		}
		else if ( isLine2Deg )			// the 'line' is degenerate.
		{
			VWPoint2D		closestPt;
			if ( VWLine2D::PtNearLine( pt3, pt1, pt2, closestPt, epsCoord ) )
			{
				outOnSeg1				= true;
				outOnSeg2				= true;
				outParallel				= true;

				// the intersection.
				outIntersLine.SetLine( closestPt, closestPt );	// degenerate point-like line.
			}
		}
		else							// both lines are non-degenerate.
		{
			double			x21			= ( pt2.x - pt1.x );
			double			x43			= ( pt4.x - pt3.x );
			double			y21			= ( pt2.y - pt1.y );
			double			y43			= ( pt4.y - pt3.y );

			// cross product of the vectors (pt1->pt2) and (pt3->pt4).
			double			t			= ( y43 * x21 - x43 * y21 );

			// XXX Bobi:
			// since this is a direction test the checked vectors must be normalized.
			// otherwise, if they differ greatly in length then the result becomes unstable.
			// knowing lengths we could fast and easily get the cross product of the normalized vectors.
			// note that here we already know that both lines are not zero-length lines.

			// get the cross product of the normalized vectors.
			double			tNorm		= ( t / ( line1Len * line2Len ) );

			if ( Abs( tNorm ) > epsCollinear )	// not parallel.
			{
				double		x13			= ( pt1.x - pt3.x );
				double		y13			= ( pt1.y - pt3.y );
				double		oneDivT		= ( 1 / t );

				double		ua			= ( x43 * y13 - y43 * x13 ) * oneDivT;
				double		ub			= ( x21 * y13 - y21 * x13 ) * oneDivT;

				// the intersection.
				VWPoint2D	intersPt( pt1.x + ( ua * x21 ), pt1.y + ( ua * y21 ) );
				outIntersLine.SetLine( intersPt, intersPt );	// degenerate point-like line.

				// prepare the epsilon for checking the x-coefficient.
				double		eps			= epsCoord;
				double		absX21		= Abs( x21 );
				if ( absX21 > VWPoint2D::sEpsilon )
				{
					eps					= ( epsCoord / absX21 );
				}

				// compare.
				outOnSeg1				= ( - eps < ua )	&& ( ua < 1.0 + eps );	// on segment 1.

				// prepare the epsilon for checking the y-coefficient.
				eps						= epsCoord;
				double		absY21		= Abs( y21 );
				if ( absY21 > VWPoint2D::sEpsilon )
				{
					eps					= ( epsCoord / absY21 );
				}

				// compare.
				outOnSeg2				= ( - eps < ub )	&& ( ub < 1.0 + eps );	// on segment 2.
			}
			else						// parallel.
			{
				outParallel				= true;

				VWPoint2D				closestPt;

				// check whether the lines (line segments) overlap and get the overlapping ends.
				VWPoint2D				endPts[ 2 ];
				size_t					endsCnt		= 0;

				const VWPoint2D*		l1Pts[ 2 ]	= { ( & pt1 ), ( & pt2 ) };
				for ( size_t i = 0 ; ( i < 2 ) && ( endsCnt < 2 ) ; ++ i )
				{
					const VWPoint2D&	pt			= ( * l1Pts[ i ] );
					if ( VWLine2D::PtNearLine( pt, pt3, pt4, closestPt, epsCoord ) )
					{
						endPts[ endsCnt ]			= pt;
						++ endsCnt;
					}
				}

				if ( endsCnt < 2 )					// still not all cases examined.
				{
					const VWPoint2D*	l2Pts[ 2 ]	= { ( & pt3 ), ( & pt4 ) };
					for ( size_t i = 0 ; ( i < 2 ) && ( endsCnt < 2 ) ; ++ i )
					{
						const VWPoint2D&	pt		= ( * l2Pts[ i ] );
						if ( VWLine2D::PtNearLine( pt, pt1, pt2, closestPt, epsCoord ) &&									// point on this line and ...
							 ( i != 0 || endsCnt != 1 || ! MathUtils::Equalish( endPts[ endsCnt - 1 ], pt, epsCoord ) ) )	// ... not already added.
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

					outOnSeg1						= true;
					outOnSeg2						= true;
				}
			}
		}
	}
}

// only checks if line segment [(x1,y1)(x2,y2)] intersects with line segment [(x3,y3)(x4,y4)]. for faster check.
bool VWLine2D::AreLineSegmentsIntersecting(const VWPoint2D& p1, const VWPoint2D& p2, const VWPoint2D& p3, const VWPoint2D& p4, double dEpsilon)
{
	return	VWLine2D::AreLineSegmentsIntersecting( p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y, dEpsilon );
}

// only checks if line segment [(x1,y1)(x2,y2)] intersects with line segment [(x3,y3)(x4,y4)]. for faster check.
bool VWLine2D::AreLineSegmentsIntersecting(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double dEpsilon)
{
	bool		hasInters	= false;

	// check whether bounding boxes of the line segments have common area.
	if ( VWLine2D::DoLineSegmentsBoundsIntersect( x1, y1, x2, y2, x3, y3, x4, y4, dEpsilon ) )
	{
		double	x21			= ( x2 - x1 );
		double	x43			= ( x4 - x3 );
		double	y21			= ( y2 - y1 );
		double	y43			= ( y4 - y3 );

		double	t			= ( y43 * x21 - x43 * y21 );
		if ( Abs(t) > dEpsilon )
		{
			double	x13		= ( x1 - x3 );
			double	y13		= ( y1 - y3 );
			double	oneDivT	= ( 1 / t );

			double	ua		= ( x43 * y13 - y43 * x13 ) * oneDivT;
			double	ub		= ( x21 * y13 - y21 * x13 ) * oneDivT;

			if ( ( Abs( ua ) > dEpsilon ) || ( Abs( ub ) > dEpsilon ) )				// ! parallel.
			{
				hasInters	= ( - dEpsilon < ua )	&& ( ua < 1.0 + dEpsilon )	&&	// on segment 1.
							  ( - dEpsilon < ub )	&& ( ub < 1.0 + dEpsilon );		// on segment 2.
			}
		}
	}

	// result.
	return	( hasInters );
}

// only checks if line segment [(x1,y1)(x2,y2)] intersects with line segment [(x3,y3)(x4,y4)], returns intersection coordinates. Note: this function is robust and fast.
// if there is intersection, the intersection point and 'outParallel' will be correctly calculated, otherwise don't count on it !
bool VWLine2D::AreLineSegmentsIntersecting(const VWPoint2D& p1, const VWPoint2D& p2, const VWPoint2D& p3, const VWPoint2D& p4, VWPoint2D& outIntersPt, bool& outParallel, double epsilon)
{
	return	VWLine2D::AreLineSegmentsIntersecting( p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y, outIntersPt.x, outIntersPt.y, outParallel, epsilon );
}

// only checks if line segment [(x1,y1)(x2,y2)] intersects with line segment [(x3,y3)(x4,y4)], returns intersection coordinates. Note: this function is robust and fast.
// if there is intersection, the intersection point and 'outParallel' will be correctly calculated, otherwise don't count on it !
bool VWLine2D::AreLineSegmentsIntersecting(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double& outIntersX, double& outIntersY, bool& outParallel, double epsilon)
{
	bool			hasInters	= false;

	// check whether bounding boxes of the line segments have common area.
	if ( VWLine2D::DoLineSegmentsBoundsIntersect( x1, y1, x2, y2, x3, y3, x4, y4, epsilon ) )
	{
		double		x21			= ( x2 - x1 );
		double		x43			= ( x4 - x3 );
		double		y21			= ( y2 - y1 );
		double		y43			= ( y4 - y3 );

		double		t			= ( y43 * x21 - x43 * y21 );

		if ( Abs( t ) > epsilon )
		{
			double	x13			= ( x1 - x3 );
			double	y13			= ( y1 - y3 );
			double	oneDivT		= ( 1 / t );

			double	ua			= ( x43 * y13 - y43 * x13 ) * oneDivT;
			double	ub			= ( x21 * y13 - y21 * x13 ) * oneDivT;

			outIntersX			= x1 + ua * x21;
			outIntersY			= y1 + ua * y21;

			outParallel			=	( Abs( ua ) < epsilon ) && ( Abs( ub ) < epsilon );

			hasInters			=	( - epsilon < ua )	&& ( ua < 1.0 + epsilon )	&&	// on segment 1.
									( - epsilon < ub )	&& ( ub < 1.0 + epsilon );		// on segment 2.
		}
		else
		{
			outParallel			= true;
		}
	}

	// result.
	return	( hasInters );
}

// distance from point (x0,y0) to line [(x1,y1)(x2,y2)]
double VWLine2D::Distance(double x0, double y0, double x1, double y1, double x2, double y2 )
{
	// http://mathworld.wolfram.com/Point-LineDistance2-Dimensional.html
	//
	//     |(x2 - x1)(y1 - y0) - (x1 - x0)(y2 - y1)|
	// d = -----------------------------------------
	//        sqrt( (x2 - x1)^2 + (y2 - y1)^2 )

	// prevent not 0 for the 'sqrt'
	if ( Abs((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)) < 0.000001 )
		return 0;

	double	a		= (x2 - x1)*(y1 - y0) - (x1 - x0)*(y2 - y1);
	double	b		= Sqrt( (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1) );
	double	dist	= Abs(a) / b;

#ifdef _DEBUG
	// innser test of the routine
	VWPoint2D	pt( x0, y0 );
	VWLine2D	line( x1, y1, x2, y2 );
	VWPoint2D	projPt	= line.PtPerpLine( pt );
	double	oldWayDist	= projPt.DistanceTo( pt );
	VWFC_ASSERT( Abs(dist-oldWayDist) < 0.0001 );
#endif

	return dist;
}

// checks whether bounding boxes of the two line segments [p1,p2] and [p3,p4] have common area.
bool VWLine2D::DoLineSegmentsBoundsIntersect(const VWPoint2D& p1, const VWPoint2D& p2, const VWPoint2D& p3, const VWPoint2D& p4, double epsilon)
{
	return	VWLine2D::DoLineSegmentsBoundsIntersect( p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y, epsilon );
}

// checks whether bounding boxes of the two line segments [(x1,y1)(x2,y2)] and [(x3,y3)(x4,y4)] have common area.
bool VWLine2D::DoLineSegmentsBoundsIntersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double epsilon)
{
	// reorder coordinates.
	double			x1a, y1a, x2a, y2a, x3a, y3a, x4a, y4a;

	// ... of the first line segment.
	if ( x1 < x2 )	{ x1a = x1; x2a = x2; }
	else			{ x1a = x2; x2a = x1; }
	if ( y1 < y2 )	{ y1a = y1; y2a = y2; }
	else			{ y1a = y2; y2a = y1; }

	// ... of the second line segment.
	if ( x3 < x4 )	{ x3a = x3; x4a = x4; }
	else			{ x3a = x4; x4a = x3; }
	if ( y3 < y4 )	{ y3a = y3; y4a = y4; }
	else			{ y3a = y4; y4a = y3; }

	// result.
	return	(	MathUtils::GEish( x4a, x1a, epsilon ) &&
				MathUtils::GEish( x2a, x3a, epsilon ) &&
				MathUtils::LEish( y3a, y2a, epsilon ) &&
				MathUtils::LEish( y1a, y4a, epsilon ) );
}

// returns the closest point to the line segment or the closest segment end, also returns the squared distance to the found point.
/*static*/ VWPoint2D VWLine2D::PtPerpLineSeg(const VWPoint2D& pt, const VWPoint2D& lnPt0, const VWPoint2D& lnPt1, double& outSqrDist)
{
	VWPoint2D	closestLinePt;

	// get the line vector.
	VWPoint2D	vecLine			= ( lnPt1 - lnPt0 );
	// get its perpendicular vector.
	VWPoint2D	vecPerp			= vecLine.Perp();

	// check if the point can be projected on the line segment.
	if ( VWLine2D::PtOnLeftOfLine( pt, lnPt0, ( lnPt0 + vecPerp ) ) &&		// on left of first perpendicular line and ...
		( ! VWLine2D::PtOnLeftOfLine( pt, lnPt1, ( lnPt1 + vecPerp ) ) ) )	// ... on right of second perpendicular line.
	{
		// so, the point can be projected on the line segment.
		// Note: this also means that it is not a zero-length line.

		// get the projection point.

		// get the length of the projection (start - proj), which is 'proj length' = ( dot product( vecLine, 'start->pt' ) / 'line length' ).
		// on the other hand the coefficient is 'proj length' / 'line length', so we have:
		double	coeff			= ( ( vecLine % ( pt - lnPt0 ) ) / vecLine.MagnitudeSquared() );

		// get the point (linear interpolation as it is expected to lie on the line segment).
		closestLinePt			= ( ( lnPt0 * ( 1.0 - coeff ) ) + ( lnPt1 * coeff ) );

		outSqrDist				= pt.DistanceSquaredTo( closestLinePt );
	}
	else						// point cannot be projected on the line segment.
	{
		double	dsSqr			= pt.DistanceSquaredTo( lnPt0 );
		double	deSqr			= pt.DistanceSquaredTo( lnPt1 );

		if ( dsSqr < deSqr )	// the projection is outside (before the start).
		{
			closestLinePt		= lnPt0;

			outSqrDist			= dsSqr;
		}
		else					// the projection is outside (after the end).
		{
			closestLinePt		= lnPt1;

			outSqrDist			= deSqr;
		}
	}

	// result.
	return	( closestLinePt );
}

// returns the closest point to the line segment. it is a optimized/faster version which uses squared length.
/*static*/ void VWLine2D::PtPerpLine(double pX, double pY, double l1X, double l1Y, double l2X, double l2Y, double& outProjX, double& outProjY)
{
	double		lineDeltaX		= ( l2X - l1X );
	double		lineDeltaY		= ( l2Y - l1Y );

	double		pXmL1X			= ( pX - l1X );
	double		pYmL1Y			= ( pY - l1Y );

	// calculate the dot product.
	double		dot				= ( ( lineDeltaX * pXmL1X ) + ( lineDeltaY * pYmL1Y ) );
	// get the line squared length.
	double		lineSqrLen		= ( sqr( lineDeltaX ) + sqr( lineDeltaY ) );

	double		oneOverSqrLen	= ( 1.0 / lineSqrLen );

	// prepare the result - the projected point coordinates.
	outProjX	= l1X + ( dot * lineDeltaX * oneOverSqrLen );
	outProjY	= l1Y + ( dot * lineDeltaY * oneOverSqrLen );
}

// fast check if a point is near the line segment.
/*static*/ bool VWLine2D::PtNearLine(const VWPoint2D& pt, const VWPoint2D& lnPt0, const VWPoint2D& lnPt1, VWPoint2D& outClosestPt, double tolerance)
{
	// init.
	bool			isNearLine	= false;

	// get line bounding box.
	VWRectangle2D	bboxLine(	lnPt0.x, lnPt1.x,	// left / right.
								lnPt0.y, lnPt1.y );	// top / bottom.

	// check if point is within the tolerance to the line bounding box.
	// this will mean that point might be near the line segment (limiting the search area).
	if ( bboxLine.IsPtInside( pt, tolerance ) )
	{
		double		sqrDistToLn;
		// get the closest point on line.
		outClosestPt			= VWLine2D::PtPerpLineSeg( pt, lnPt0, lnPt1, sqrDistToLn );

		// get if the point is near the line within the tolerance.
		isNearLine				= ( sqrDistToLn < sqr( tolerance ) );
	}

	// result.
	return	( isNearLine );
}

// checks if point is on left side of the line defined by two points.
/*static*/ bool VWLine2D::PtOnLeftOfLine(const VWPoint2D& pt, const VWPoint2D& lnPt0, const VWPoint2D& lnPt1)
{
	return	( ( lnPt1.x - lnPt0.x ) * ( pt.y - lnPt0.y ) >= ( lnPt1.y - lnPt0.y ) * ( pt.x - lnPt0.x ) );
}

// checks if point is on left side of the ray defined by ray point and vector.
/*static*/ bool VWLine2D::PtOnLeftOfRay(const VWPoint2D& pt, const VWPoint2D& rayPt, const VWPoint2D& rayVec)
{
	return	( rayVec.x * ( pt.y - rayPt.y ) >= rayVec.y * ( pt.x - rayPt.x ) );
}
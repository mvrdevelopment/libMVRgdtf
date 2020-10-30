//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "Prefix/StdAfx.h"

using namespace VectorworksMVR::VWFC::Math;



// default epsilon for operator==
double	VWPoint3D::sEpsilon				= 0.0000001;

// squared default epsilon.
double	VWPoint3D::sSqrEpsilon			= 0.00000000000001;	// sqr( VWPoint2D::sEpsilon )

// raw (bigger) epsilon.
double	VWPoint3D::sRawEpsilon			= 0.0001;

// default epsilon for checking collinearity.
double	VWPoint3D::sEpsilonCollinear	= 0.01;

// default epsilon for checking nearness between angles in radians.
double	VWPoint3D::sEpsilonRadians		= 0.001745329252;	// 0.1 degrees.

VWPoint3D::VWPoint3D()
{
	this->x	= 0;
	this->y	= 0;
	this->z	= 0;
}

VWPoint3D::VWPoint3D(const WorldPt3& pt)
{
	this->x	= pt.x;
	this->y	= pt.y;
	this->z	= pt.z;
}

VWPoint3D::VWPoint3D(double x, double y, double z)
{
	this->x	= x;
	this->y	= y;
	this->z	= z;
}

VWPoint3D::VWPoint3D(const VWPoint2D& pt, double z)
{
	this->x	= pt.x;
	this->y	= pt.y;
	this->z	= z;
}

VWPoint3D::VWPoint3D(const VWPoint3D& src)
{
	this->x	= src.x;
	this->y	= src.y;
	this->z	= src.z;
}

VWPoint3D::~VWPoint3D()
{
}

void VWPoint3D::SetPoint(double x, double y, double z)
{
	this->x	= x;
	this->y	= y;
	this->z	= z;
}

void VWPoint3D::SetPoint(const VWPoint2D& pt, double z)
{
	this->x	= pt.x;
	this->y	= pt.y;
	this->z	= z;
}

void VWPoint3D::SetPoint(const WorldPt3& pt)
{
	this->x	= pt.x;
	this->y	= pt.y;
	this->z	= pt.z;
}

bool VWPoint3D::operator==(const VWPoint3D& p) const
{
	return	this->Equal( p, VWPoint3D::sEpsilon );
}

bool VWPoint3D::operator!=(const VWPoint3D& p) const
{
	return	! this->Equal( p, VWPoint3D::sEpsilon );
}

bool VWPoint3D::operator==(const VWPoint2D& p) const
{
	return	this->Equal( p, VWPoint3D::sEpsilon );
}

bool VWPoint3D::operator!=(const VWPoint2D& p) const
{
	return	! this->Equal( p, VWPoint3D::sEpsilon );
}

VWPoint3D VWPoint3D::operator+(const VWPoint3D& p) const
{
	return VWPoint3D( x + p.x, y + p.y, z + p.z );
}

VWPoint3D VWPoint3D::operator-(const VWPoint3D& p) const
{
	return VWPoint3D( x - p.x, y - p.y, z - p.z );
}

VWPoint3D VWPoint3D::operator*(double scalar) const
{
	return VWPoint3D( x * scalar, y * scalar, z * scalar );
}

VWPoint3D VWPoint3D::operator/(double scalar) const
{
	return VWPoint3D( x / scalar, y / scalar, z / scalar );
}

VWPoint3D VWPoint3D::operator-(void) const
{
	return VWPoint3D( -x, -y, -z );
}

VWPoint3D& VWPoint3D::operator=(const WorldPt3& p)
{
	x	= p.x;
	y	= p.y;
	z	= p.z;
	return *this;
}

VWPoint3D& VWPoint3D::operator=(const VWPoint3D& p)
{
	x	= p.x;
	y	= p.y;
	z	= p.z;
	return *this;
}

VWPoint3D& VWPoint3D::operator=(const VWPoint2D& p)
{
	x	= p.x;
	y	= p.y;
	z	= 0;
	return *this;
}

VWPoint3D& VWPoint3D::operator+=(const VWPoint3D& p)
{
	x	+= p.x;
	y	+= p.y;
	z	+= p.z;
	return *this;
}

VWPoint3D& VWPoint3D::operator+=(const VWPoint2D& p)
{
	x	+= p.x;
	y	+= p.y;
	return *this;
}

VWPoint3D& VWPoint3D::operator-=(const VWPoint3D& p)
{
	x	-= p.x;
	y	-= p.y;
	z	-= p.z;
	return *this;
}

VWPoint3D& VWPoint3D::operator-=(const VWPoint2D& p)
{
	x	-= p.x;
	y	-= p.y;
	return *this;
}


VWPoint3D& VWPoint3D::operator*=(double s)
{
	x	*= s;
	y	*= s;
	z	*= s;
	return *this;
}

VWPoint3D& VWPoint3D::operator/=(double s)
{
	x	/= s;
	y	/= s;
	z	/= s;
	return *this;
}

// cross product
VWPoint3D VWPoint3D::operator*(const VWPoint3D& p) const
{
	return VWPoint3D(	this->y * p.z - this->z * p.y,
						this->z * p.x - this->x * p.z,
						this->x * p.y - this->y * p.x	);
}

VWPoint3D& VWPoint3D::operator*=(const VWPoint3D& p)
{
	this->SetPoint(	this->y * p.z - this->z * p.y,
					this->z * p.x - this->x * p.z,
					this->x * p.y - this->y * p.x	);
	return *this;
}

// dot product
double VWPoint3D::operator%(const VWPoint3D& p) const
{
	return this->x * p.x + this->y * p.y + this->z * p.z;
}

// compatibility with SDK
VWPoint3D::operator const WorldPt3&() const
{
	// fool the compiler
	// to allow us modify member variable
	WorldPt3*	pPt	= (WorldPt3*) & fPoint;
	pPt->Set( x, y, z );
	return (*pPt);
}

VWPoint3D::operator VWPoint2D() const
{
	return VWPoint2D( x, y );
}

//////////////////////////////////////////////////////////////////////////////////////
// Math functions
//////////////////////////////////////////////////////////////////////////////////////

// return the distance from (0,0,0) to this point
double VWPoint3D::Magnitude() const
{
	return sqrt( x*x + y*y + z*z );
}

// return the squared distance from (0,0,0) to this point
double VWPoint3D::MagnitudeSquared() const
{
	return x*x + y*y + z*z;
}

// return true if the specified point is equal within the given epsilon to this point
bool VWPoint3D::Equal(const VWPoint3D& pt, double dEpsilon) const
{
	double	xx	= (x - pt.x);
	double	yy	= (y - pt.y);
	double	zz	= (z - pt.z);
	return ((xx*xx) + (yy*yy) + (zz*zz)) < dEpsilon*dEpsilon;
}

bool VWPoint3D::Equal(const VWPoint2D& pt, double dEpsilon) const
{
	double	xx	= (x - pt.x);
	double	yy	= (y - pt.y);
	return ((xx*xx) + (yy*yy)) < dEpsilon*dEpsilon;
}

// calculate the distance from the specified point to this point
double VWPoint3D::DistanceTo(double x, double y, double z)
{
	double	xx	= this->x - x;
	double	yy	= this->y - y;
	double	zz	= this->z - z;
	return sqrt( xx*xx + yy*yy + zz*zz );
}

double VWPoint3D::DistanceTo(const VWPoint3D& pt) const
{
	return ( (*this) - pt ).Magnitude();
}

// calculate the distance from the specified point to this point
double VWPoint3D::DistanceSquaredTo(double x, double y, double z)
{
	double	xx	= this->x - x;
	double	yy	= this->y - y;
	double	zz	= this->z - z;
	return xx*xx + yy*yy + zz*zz ;
}

double VWPoint3D::DistanceSquaredTo(const VWPoint3D& pt) const
{
	return ( (*this) - pt ).MagnitudeSquared();
}

// cross product
VWPoint3D VWPoint3D::Cross(const VWPoint3D& pt) const
{
	return VWPoint3D(	this->y * pt.z - this->z * pt.y,
						this->z * pt.x - this->x * pt.z,
						this->x * pt.y - this->y * pt.x	);
}

// dot product
double VWPoint3D::DotProduct(const VWPoint3D& pt) const
{
	return this->x * pt.x + this->y * pt.y + this->z * pt.z;
}

// normalize this vector
VWPoint3D& VWPoint3D::Normalize()
{      
	double		len	= this->Magnitude();
	if ( len > 0.0 )
	{
		this->x	/= len;
		this->y	/= len;
		this->z	/= len;
	}
	return *this;
}

// get normalized of this vector.
VWPoint3D VWPoint3D::GetNormalized() const
{
	VWPoint3D	norm	= ( *this );
	norm.Normalize();

	// result.
	return	( norm );
}

// checks whether the point lies on plane defined by point and two vectors lying on it. 
bool VWPoint3D::IsOnPlane(const VWPoint3D& planePt, const VWPoint3D& planeVec0, const VWPoint3D& planeVec1,
						  double coordEpsilon, double radEpsilon) const
{
	// init.
	bool				isOn		= false;

	// get the normalized cross product of the two plane vectors.
	const VWPoint3D&	planeNorm	= ( planeVec0 * planeVec1 ).Normalize();

	// get the vector (planePt -> point).
	VWPoint3D			vec			= ( ( *this ) - planePt );

	if ( MathUtils::Equalish( vec.MagnitudeSquared(), 0.0, sqr( coordEpsilon ) ) )	// point and planePt coincide.
	{
		isOn						= true;
	}
	else							// different point and planePt.
	{
		// normalize the vector (planePt -> point).
		vec.Normalize();

		// get dot product.
		double			cosAng		= ( planeNorm % vec );

		// check angle.
		if ( MathUtils::Equalish( cosAng, 0.0, radEpsilon ) )
		{
			// it is a right angle (PI/2).
			// means that the point is on the plane.
			isOn					= true;
		}
	}

	// result.
	return	( isOn );
}

// checks whether a point lies inside a triangle (lies on triangle's plane and is inside triangle's area).
bool VWPoint3D::IsOnTriangle(const VWPoint3D& triPt0, const VWPoint3D& triPt1, const VWPoint3D& triPt2,
							 double coordEpsilon, double radEpsilon) const
{
	// init.
	bool				isOn		= false;
	const VWPoint3D&	pt			= ( *this );

	// check if triangle is degenerate.
	bool				isNonDegen	= true;

	if ( MathUtils::Equalish( triPt0, triPt1, coordEpsilon ) &&
		 MathUtils::Equalish( triPt1, triPt2, coordEpsilon ) )	// the three triangle's points coincide.
	{
		// this is a point-like triangle (all its points coincide).
		isOn						= MathUtils::Equalish( pt, triPt0, coordEpsilon );

		isNonDegen					= false;	// mark as degenerate.
	}
	else
	{
		// check if it is a line-like triangle (collinear points).
		// Note: don't normalize the vectors as we don't expect them to differ greatly in length. such cases will be caught in the standard case.
		VWPoint3D		crossP		= ( ( triPt0 - triPt1 ) * ( triPt2 - triPt1 ) );			// cross product.
		if ( MathUtils::Equalish( crossP.MagnitudeSquared(), 0.0, VWPoint3D::sSqrEpsilon ) )	// degenerate.
		{
			// this is a line-like triangle (collinear points).
			VWLine3D	line		= VWPoint3D::GetTriLongestEdge( triPt0, triPt1, triPt2 );

			isOn					= line.IsPtOnLine( pt, coordEpsilon, radEpsilon );

			isNonDegen				= false;	// mark as degenerate.
		}
	}

	if ( isNonDegen )				// not a degenerate triangle.
	{
		// this is a triangle with three different and not collinear points.
		// check whether the point is inside.

		// get normalized vectors from the point to every of triangle's vertices.
		VWPoint3D		norm0		= ( triPt0 - pt ).Normalize();
		VWPoint3D		norm1		= ( triPt1 - pt ).Normalize();
		VWPoint3D		norm2		= ( triPt2 - pt ).Normalize();

		// get angles adjacent to pt.
		double			cos0		= ( norm0 % norm1 );	// dot product.
		double			cos1		= ( norm1 % norm2 );	// dot product.
		double			cos2		= ( norm2 % norm0 );	// dot product.

		// get sum of the three angles.
		double			sumAng		= ( acos( cos0 ) + acos( cos1 ) + acos( cos2 ) );

		// if the angle is (close to) 2 * PI (zero Gaussian curvature) this means that the point lies inside the triangle.
		isOn						= MathUtils::Equalish( sumAng, MathUtils::PI2, radEpsilon );

		// so far we know whether the point is inside the triangle (including edges) but ...
		// ... the above check does not catch cases when the point coincides with some of the triangle's vertices.
		if ( ! isOn )			// do check for coincidence with some triangle's vertex.
		{
			isOn					= ( MathUtils::Equalish( pt, triPt0, coordEpsilon ) ||
										MathUtils::Equalish( pt, triPt1, coordEpsilon ) ||
										MathUtils::Equalish( pt, triPt2, coordEpsilon ) );
		}
	}

	// result.
	return	( isOn );
}

double VWPoint3D::TriArea(const VWPoint3D& pt1, const VWPoint3D& pt2, const VWPoint3D& pt3)
{
	// The area of a 3D triangle defined by the vertex P1, P2, P3 is half the magnitude of the cross product of the two edge vectors:
	// 0.5 * | P1P2 * P1P3 |

	VWPoint3D	cross	= (pt2 - pt1).Cross( pt3 - pt1 );
	
	return cross.Magnitude() / 2;
}

double VWPoint3D::TriArea(	double pt1x, double pt1y, double pt1z,
							double pt2x, double pt2y, double pt2z,
							double pt3x, double pt3y, double pt3z)
{
	// The area of a 3D triangle defined by the vertex P1, P2, P3 is half the magnitude of the cross product of the two edge vectors:
	// 0.5 * | P1P2 * P1P3 |

	double	P1P2x	= pt2x - pt1x;
	double	P1P2y	= pt2y - pt1y;
	double	P1P2z	= pt2z - pt1z;

	double	P1P3x	= pt3x - pt1x;
	double	P1P3y	= pt3y - pt1y;
	double	P1P3z	= pt3z - pt1z;

	double	crossX	= P1P2y * P1P3z - P1P2z * P1P3y;
	double	crossY	= P1P2z * P1P3x - P1P2x * P1P3z;
	double	crossZ	= P1P2x * P1P3y - P1P2y * P1P3x;

	double	sign	= crossZ < 0 ? -1 : 1;

	return sign * sqrt( crossX*crossX + crossY*crossY + crossZ*crossZ ) / 2;
}

// find the center and squared radius of triangle circumcircle. return whether it exists (triangle points are not collinear).
bool VWPoint3D::GetTriCircumCircle(const VWPoint3D& pt0, const VWPoint3D& pt1, const VWPoint3D& pt2, VWPoint3D& outCenPt, double& outSqrRad)
{
	bool		exists	= false;

	double		d0		= ( pt2 - pt0 ).DotProduct( pt1 - pt0 );
	double		d1		= ( pt2 - pt1 ).DotProduct( pt0 - pt1 );
	double		d2		= ( pt0 - pt2 ).DotProduct( pt1 - pt2 );

	double		c0		= ( d1 * d2 );
	double		c1		= ( d2 * d0 );
	double		c2		= ( d0 * d1 );
	double		sumc	= ( c2 + c1 + c0 );

	if ( ! MathUtils::Equalish( sumc, 0.0, VWPoint3D::sEpsilon ) ) {	// prevent division by zero.
		double	cs		= ( 0.5 / sumc );
		double	f0		= ( c2 + c1 ) * cs;
		double	f1		= ( c2 + c0 ) * cs;
		double	f2		= ( c0 + c1 ) * cs;

		// circum center.
		outCenPt.x		= ( ( f0 * pt0.x )  + ( f1 * pt1.x )  + ( f2 * pt2.x ) );
		outCenPt.y		= ( ( f0 * pt0.y )  + ( f1 * pt1.y )  + ( f2 * pt2.y ) );
		outCenPt.z		= ( ( f0 * pt0.z )  + ( f1 * pt1.z )  + ( f2 * pt2.z ) );

		// circum squared radius.
		outSqrRad		= outCenPt.DistanceSquaredTo( pt0 );

		exists			= true;
	}

	return		exists;
}

// find the squared radius of triangle inscribed circle. return whether it exists.
bool VWPoint3D::GetTriInscribedCircleRadius(const VWPoint3D& pt0, const VWPoint3D& pt1, const VWPoint3D& pt2, double& outSqrRad)
{
	bool		exists		= false;

	double		len0		= pt0.DistanceTo( pt1 );
	double		len1		= pt1.DistanceTo( pt2 );
	double		len2		= pt2.DistanceTo( pt0 );

	double		perim		= ( len0 + len1 + len2 ) * 0.5;

	if ( ! MathUtils::Equalish( perim, 0.0, VWPoint3D::sEpsilon ) ) {	// prevent division by zero.
		// get squared radius.
		outSqrRad			= ( ( perim - len0 ) * ( perim - len1 ) * ( perim - len2 ) ) / perim;

		exists				= true;
	}

	return	exists;
}

// find the center of triangle inscribed circle.
void VWPoint3D::GetTriInscribedCircleCenter(const VWPoint3D& pt0, const VWPoint3D& pt1, const VWPoint3D& pt2, VWPoint3D& outCenPt)
{
	// get center.
	VWPoint3D	dir1	= ( pt1 - pt0 );
	dir1.Normalize();
	VWPoint3D	dir2	= ( pt2 - pt0 );
	dir2.Normalize();
	VWPoint3D	dir3	= ( pt2 - pt1 );
	dir3.Normalize();

	VWPoint3D	dirB1	= ( dir1 + dir2 );
	VWPoint3D	dirB2	= ( dir3 - dir1 );
	
	dirB1.Normalize();
	dirB2.Normalize();

	VWLine3D	lineB1( pt0, dirB1 );
	outCenPt			= pt1 + dirB2 * lineB1.GetDistance( pt1 );
}

// get an estimation of the triangle aspect ratio. ratio can not be estimated for degenerate triangles.
bool VWPoint3D::TriAspectRatioEval(const VWPoint3D& pt0, const VWPoint3D& pt1, const VWPoint3D& pt2, double& ratioEval)
{
	bool			hasRatio	= false;

	// get squared radius of the circum circle.
	VWPoint3D		circumCenPt;
	double			circumSqrRadius;
	if ( VWPoint3D::GetTriCircumCircle( pt0, pt1, pt2, circumCenPt, circumSqrRadius ) ) {

		// get squared radius of the inscribed circle.
		double	inscribedSqrRadius;
		if ( VWPoint3D::GetTriInscribedCircleRadius( pt0, pt1, pt2, inscribedSqrRadius ) ) {

			if ( ! MathUtils::Equalish( inscribedSqrRadius, 0.0, VWPoint3D::sEpsilon ) ) {	// prevent division by zero.
				// evaluate the aspect ratio (can be done!).
				ratioEval		= ( circumSqrRadius / inscribedSqrRadius );
				hasRatio		= true;
			}
		}
	}

	return		hasRatio;
}

// check if given 3 points are collinear.
bool VWPoint3D::ArePointsCollinear(const VWPoint3D& pt0, const VWPoint3D& pt1, const VWPoint3D& pt2, double dEpsilon)
{
	bool		areCollinear		= false;

	// get two vectors that will be checked for collinearity.
	// since this is a direction test the vectors must be normalized.
	// otherwise, if they differ greatly in length then the result becomes unstable.
	const VWPoint3D&	vecA		= ( pt0 - pt1 ).Normalize();
	const VWPoint3D&	vecB		= ( pt2 - pt1 ).Normalize();

	// get cross product: normal vector to plane defined by the two vectors above.
	const VWPoint3D&	normalVec	= vecA.Cross( vecB );
	if ( MathUtils::Equalish( normalVec.Magnitude(), 0.0, dEpsilon ) )
	{
		areCollinear			= true;
	}

	return		areCollinear;
}

// get longest triangle's edge.
/*static*/ VWLine3D VWPoint3D::GetTriLongestEdge(const VWPoint3D& triPt0, const VWPoint3D& triPt1, const VWPoint3D& triPt2)
{
	VWLine3D		line;

	double			dist0		= triPt0.DistanceSquaredTo( triPt1 );
	double			dist1		= triPt1.DistanceSquaredTo( triPt2 );
	double			dist2		= triPt2.DistanceSquaredTo( triPt0 );

	// prepare the output line.
	if ( dist0 > dist1 )
	{
		if ( dist0 > dist2 )	line.SetLine( triPt0, triPt1 );
		else					line.SetLine( triPt2, triPt0 );
	}
	else
	{
		if ( dist1 > dist2 )	line.SetLine( triPt1, triPt2 );
		else					line.SetLine( triPt2, triPt0 );
	}

	// result.
	return	( line );
}
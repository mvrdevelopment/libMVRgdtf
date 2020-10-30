//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	
//	Declares most of the standard geometric data types used
//	in MiniCAD code. This includes all WorldCoord related types.
//
#include "Prefix/StdAfx.h"

#ifndef _MCCOORDTYPES_
#define _MCCOORDTYPES_

#pragma once

#if !(_MINICAD_EXTERNAL_)		// JAK 10/15/99 We cannot include Limits in SDK externals because conflict with fp.h or something.
#include <limits>
#endif

#include "BasicMath.X.h"

#if TEST
	#define WORLDRECTISEMPTY(rect, assert)	(rect.IsEmpty(assert))
	#define WORLDCUBEISEMPTY(cube, assert)	(cube.IsEmpty(assert))
#else
	#define WORLDRECTISEMPTY(rect, assert)	((rect.left > rect.right) || (rect.bottom > rect.top))
	#define WORLDCUBEISEMPTY(cube, assert)	((cube.left > cube.right) || (cube.bottom > cube.top) || (cube.back > cube.front))
#endif

//----------------------------------------------------------------------------------------
namespace VectorworksMVR
{	

const short MaxInt     		= 32767;  
const short kMaxShortInt	= 32767;    
const Sint32  MaxLongInt		= INT32_MAX;
const Sint32  kMaxLongInt		= INT32_MAX;


const extern double kWorldCoordsPerInch;   // 25.4
const extern double kInchesPerWorldCoord;
const extern double kWorldCoordsPerInch_Squared;

const extern double kDecimicronsPerInch;
const extern double kWorldCoordsPerDecimicron;

const extern double kWorldCoordsPerMM;     // 1

const extern short  kMaximumTotalDigitsOfPrecision;      
const extern short  kMaximumFractionalDigitsOfPrecision; 

const extern double kNearlyEqualEpsilonForWorldCoords;
const extern double kWorldCoordBumpEpsilon;

const extern double kNearlyEqualEpsilonForRadians;

const extern double kTypographicalPointsPerInch;

//----------------------------------------------------------------------------------------

typedef double WorldCoord;	// a one-dimensional coordinate
typedef double _WorldCoord;

//----------------------------------------------------------------------------------------

typedef	double WorldInches;

inline WorldCoord InchesToWorldCoord(WorldInches inches) { return inches * kWorldCoordsPerInch; }
inline double     WorldCoordToInches(WorldCoord coord)   { return coord * kInchesPerWorldCoord; }

//----------------------------------------------------------------------------------------

const extern WorldCoord kMaxLegalWorldCoord;
const extern WorldCoord kMaxOutOfRangeWorldCoord;

#define kMaxCoord kMaxOutOfRangeWorldCoord  // kMaxCoord is here to support old SDK references - don't use this if you can help it [MAF 11/30/00]

typedef WorldCoord WorldArea;	// WorldCoord * WorldCoord
typedef WorldCoord WorldVolume;	// WorldCoord^3

//----------------------------------------------------------------------------------------
//
// Magnitude-based WorldCoord Comparison Functions.
//
// All WorldCoord comparisons must use these functions.
//
// These WorldCoord comparison functions are necessary because most floating point numbers
// that are not whole numbers cannot be represented exactly (they have floating point 
// approximations). Double precision floating point numbers (doubles) are accurate to 15 
// digits, but we'll consider WorldCoords equal if they are the same up to the 13th significant 
// digit (to allow for drift). Note that these functions do and must take the magnitude of the 
// values into account. 100,000,000,000,000 must be considered equal to 100,000,000,000,001, 
// and 1.00000000000000 must be considered equal to 1.00000000000001. [MAF 5/20/02]
//
//----------------------------------------------------------------------------------------

inline Boolean WorldCoordsAreNearlyEqual(WorldCoord n1, WorldCoord n2)
{
	return DoublesAreNearlyEqual(n1, n2, kNearlyEqualEpsilonForWorldCoords);
}

inline Boolean WorldCoordIsNearlyZero(WorldCoord n)
{
	return WorldCoordsAreNearlyEqual(n, 0);
}

inline Boolean WorldCoordsAreNotNearlyEqual(WorldCoord n1, WorldCoord n2)
{
	return (! WorldCoordsAreNearlyEqual(n1, n2));
}

inline Boolean WorldCoord1_GE_WorldCoord2(WorldCoord n1, WorldCoord n2)
{
	return ((n1 > n2) || WorldCoordsAreNearlyEqual(n1, n2));
}

inline Boolean WorldCoord1_GT_WorldCoord2(WorldCoord n1, WorldCoord n2)
{
	return ((n1 > n2) && (! WorldCoordsAreNearlyEqual(n1, n2)));
}

inline Boolean WorldCoord1_LE_WorldCoord2(WorldCoord n1, WorldCoord n2)
{
	return ((n1 < n2) || WorldCoordsAreNearlyEqual(n1, n2));
}

inline Boolean WorldCoord1_LT_WorldCoord2(WorldCoord n1, WorldCoord n2)
{
	return ((n1 < n2) && (! WorldCoordsAreNearlyEqual(n1, n2)));
}


inline WorldCoord WorldCoordBumpedHigher(WorldCoord n)
{
	if (n == 0.0) {
//		DSTOP((kMark, "Bumping a zero value WorldCoord. Assuming 1e0 magnitude.\n"));
		return kWorldCoordBumpEpsilon;
	}
	else
		return n + (fabs(n) * kWorldCoordBumpEpsilon);
}

inline WorldCoord WorldCoordBumpedLower(WorldCoord n)
{
	if (n == 0.0) {
//		DSTOP((kMark, "Bumping a zero value WorldCoord. Assuming 1e0 magnitude.\n"));
		return -kWorldCoordBumpEpsilon;
	}
	else
		return n - (fabs(n) * kWorldCoordBumpEpsilon);
}


inline Boolean WorldCoordsAreRelativelyClose(const WorldCoord& n1, const WorldCoord& n2, const double& ratio = 1e-7)
{
	ASSERTN(kEveryone, (ratio > kNearlyEqualEpsilonForWorldCoords));

	return DoublesAreNearlyEqual(n1, n2, ratio);
}


typedef enum { eAssert, eDontAssert } EAssertStatus; // controlled assert behavior when manipulating WorldRects - TDW

typedef enum { eStandardValue, eSpecialValue } EEmptyKind;


//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//
// WorldPt
//
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//
//
// See "Coordinate conversions" in TDQuickDraw.h for conversion functions
//


class WorldPt;				/* A point in MiniCAD drawing space. */

WorldCoord CrossProductMagnitude(const WorldPt& a, const WorldPt& b);
WorldCoord DotProduct(const WorldPt& a, const WorldPt& b);
//--------------------------------------------------------------------
#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)

class _WorldPt : public TDebugObject
{
public:
	typedef WorldCoord WorldCoordType;
	_WorldCoord y, x;

	WorldCoord X() const { return x; }
	WorldCoord Y() const { return y; }

//	operator const WorldPt&() const			{ return *((const WorldPt *) this); }
//	operator WorldPt&()						{ return *((WorldPt *) this); }

	// As Mike H. points out, these are dangerous if other classes try to derive from _WorldPt (which of course they do).
	// We should move these to WorldPt. [MAF 10/5/01]
	WorldPt*       operator&(void)			{ return (WorldPt *) this; }
	const WorldPt* operator&(void) const 	{ return (const WorldPt *) this; }
	
	Boolean operator==(const _WorldPt& p) const { return WorldCoordsAreNearlyEqual(y, p.y) 
		                                              && WorldCoordsAreNearlyEqual(x, p.x); }
	Boolean operator!=(const _WorldPt& p) const { return !(*this == p);  }

	void ByteSwap();
};

#pragma pack(pop)	// END 2 BYTE STUCTURE AIGNMENT <.vwx file format>
//--------------------------------------------------------------------


//--------------------------------------------------------------------
#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)

class WorldPt : public _WorldPt {
public:

	WorldPt(void)				{ this->x = kMaxLegalWorldCoord; this->y = kMaxLegalWorldCoord;}
	WorldPt(WorldCoord x, WorldCoord y)	{ this->x = x; this->y = y; }

//	WorldPt(const WorldPt& p)	{ this->y = p.y; this->x = p.x; }
	WorldPt(const WorldPt& p)	{ memcpy(this, &p, sizeof(WorldPt)); }   // faster for misaligned doubles [MAF FP Speedup, 2/21/01]
	
	
	WorldPt(const _WorldPt& p)	{ this->y = p.y; this->x = p.x; }
	
	void Set(WorldCoord x, WorldCoord y) { this->x = x; this->y = y; }
	void SetAngle(double radians) { x = cos(radians); y = sin(radians); }

	Boolean operator==(const WorldPt& p) const { return WorldCoordsAreNearlyEqual(y, p.y) 
		                                             && WorldCoordsAreNearlyEqual(x, p.x); }
	Boolean operator!=(const WorldPt& p) const { return !(*this == p); }

	WorldPt operator+(const WorldPt& p) const	{ return WorldPt(x + p.x, y + p.y); }
	WorldPt operator-(const WorldPt& p) const	{ return WorldPt(x - p.x, y - p.y); }
	WorldPt	operator*(double scalar) const	{ return WorldPt((x * scalar), (y * scalar)); }
	WorldPt	operator/(double scalar) const	{ return WorldPt((x / scalar), (y / scalar)); }
	
	WorldPt operator-(void) const				{ return WorldPt(-x, -y); }
	
	WorldPt& operator=(const WorldPt& p) { memcpy(this, &p, sizeof(WorldPt)); return *this; }
	
	WorldPt& operator+=(const WorldPt& p) { x += p.x;    y += p.y;    return *this; }
	WorldPt& operator-=(const WorldPt& p) { x -= p.x;    y -= p.y;    return *this; }
	WorldPt& operator*=(double scalar) { x *= scalar; y *= scalar; return *this; }
	WorldPt& operator/=(double scalar) { x /= scalar; y /= scalar; return *this; }

	Boolean IsZero(void) const	{ return WorldCoordIsNearlyZero(x) && WorldCoordIsNearlyZero(y); } 

	WorldCoord Magnitude(void)        const { return sqrt(x*x + y*y); }
	WorldCoord MagnitudeSquared(void) const { return x*x + y*y; }
	void       Normalize(void) { if (!this->IsZero()) *this /= this->Magnitude(); }

	// This function assumes that the WorldPt is a vector. 
	// This poorly named function returns a unit vector, or a normalized vector, NOT a perpindicular vector.
	WorldPt    Normal(void) const { WorldPt r = *this; r.Normalize(); return r; }

	// returns a perpendicular 2d vector turning clockwise or counter-clockwise depending on the parameter
	WorldPt Perpendicular(bool clockwise = false) const {
		return clockwise ? WorldPt(y, -x) : WorldPt(-y, x);
	}

	bool Parallel(const WorldPt & p) const {
		const double Epsilon = 1e-9;

		WorldPt p1 = Normal();
		WorldPt p2 = p.Normal();

		return fabs(p1.x-p2.x)<Epsilon && fabs(p1.y-p2.y)<Epsilon;
	}
	// crossing 2d vectors is useful in that it revels a winding order.
	// This function returns the z value of the cross product.
	WorldCoord CrossMagnitude(const WorldPt & p) {
		return CrossProductMagnitude(*this, p);
	}
	// Perform dot product
	WorldCoord Dot(const WorldPt & p) {
		return DotProduct(*this, p);
	}
	WorldCoord DistanceFrom(WorldPt otherPoint)        const { return (*this - otherPoint).Magnitude(); }
	WorldCoord SquaredDistanceFrom(WorldPt otherPoint) const { return (*this - otherPoint).MagnitudeSquared(); }

	double AngleInDegrees(void) const { if (this->IsZero()) return 0.0; else return kDegreesPerRadian * atan2(y, x); }
	double DegreeAngleFrom(const WorldPt inOrigin) const	 { WorldPt p = *this - inOrigin; return p.AngleInDegrees(); }

	WorldPt Abs(void) const		{ return WorldPt(::Abs(x), ::Abs(y)); }
	WorldPt Half(void) const	{ return WorldPt(x / 2, y / 2); }

	DECLARE_CLASS_DEBUGGING
};

#pragma pack(pop)	// END 2 BYTE STUCTURE AIGNMENT <.vwx file format>
//--------------------------------------------------------------------


inline WorldPt operator*(const double scalar, const WorldPt thePt)	{ return WorldPt((thePt.x * scalar), (thePt.y * scalar)); }


inline Boolean WorldPtsAreRelativelyClose(WorldPt p1, WorldPt p2, double ratio = 1e-7)
{
	return ((WorldCoordsAreRelativelyClose(p1.x, p2.x, ratio))
		&&  (WorldCoordsAreRelativelyClose(p1.y, p2.y, ratio)));
}

inline WorldCoord CrossProductMagnitude(const WorldPt& a, const WorldPt& b)  { return a.x * b.y - a.y * b.x; }
// Assumes a and b are vectors
// Cross product magnitude is primarily used for determining the left/right orientation of two vectors.


inline WorldCoord DotProduct(const WorldPt& a, const WorldPt& b)   		     { return a.x * b.x + a.y * b.y; }
//The mathematical definition of Dot Product is:
//		|a||b|cos theta or 
//		the magnitude of 'a' times the magnitude of 'b' times the cosine of the angle between 'a' and 'b'

//The dot product is a general purpose value that can be used as part of a calculation to:
//
//		find the angle between two vectors
//		find the projection of one vector onto another vector
//		determine the forward/reverse orientation of two vectors




typedef WorldPt Vector2;



//////////////////////////////////////////////////////////////////////////////////////////
struct WorldRange
//
// A range is a 1-dimensional span, of a min and a max.  A range can be empty, it can be
// width 0 (min=max), or it can be of positive size.  If the max value is less than the
// min value, it is empty.
//
{
	public:
		WorldRange() { fMin = kMaxOutOfRangeWorldCoord; fMax = -kMaxOutOfRangeWorldCoord; }
		WorldRange(const WorldCoord& minVal, const WorldCoord& maxVal)
			{ this->Set(minVal, maxVal); }
		void Set(const WorldCoord& minVal, const WorldCoord& maxVal)
		{
			ASSERTN(kEveryone, minVal <= maxVal);
			fMin = minVal;
			fMax = maxVal;
		}
		bool IsEmpty() const { return fMax < fMin; }
		WorldCoord Min() const
		{
			ASSERTN(kEveryone, !this->IsEmpty());
			return fMin;
		}
		WorldCoord Max() const
		{
			ASSERTN(kEveryone, !this->IsEmpty());
			return fMax;
		}
		WorldCoord Extent() const
		{
			ASSERTN(kEveryone, !this->IsEmpty());
			return this->IsEmpty() ? 0 : fMax - fMin;
		}
		void UniteWith(const WorldRange& range)
		{
			if ( !range.IsEmpty() ) {
				fMin = ::Min(fMin, range.Min());
				fMax = ::Max(fMax, range.Max());
			}
		}
		void UniteWith(const WorldCoord& coord)
		{
			fMin = ::Min(fMin, coord);
			fMax = ::Max(fMax, coord);
		}
		void IntersectWith(const WorldRange& range)
		{
			fMin = ::Max(fMin, range.Min());
			fMax = ::Min(fMax, range.Max());
		}
	private:
		WorldCoord fMin, fMax;
};



//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//
// WorldRect
//
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//
// (See "Coordinate conversions" in TDQuickDraw.h for conversion functions.)
//
// _WorldRect is just 4 WorldCoords.
//
// WorldRect is based on _WorldRect but it maintains an invariant; that is, 
// it is required to maintain certain properties at all times (right >= left and 
// top >= bottom) for it be considered non-empty.
//
// To wit:
//
//     A  non-empty WorldRect has the property right >= left and top >= bottom.
//     A  point     WorldRect (which is non-empty) has the property right == left and top == bottom.
//     An empty     WorldRect has the property right < left or top < bottom.
//
// For operations involving an empty WorldRect, its behavior can be thought of as analogous to that
// of the empty set in set thoery (for unions and intersections, for example).
//
// An empty WorldRect can come about in many ways. A few of them are:
//
//    - if it is unitialized
//    - if it is set to the empty value (either accidentally or on purpose)
//    - as the result of the intersection of 2 non-touching WorldRects
//
// Any attempt to access an individual field of an empty WorldRect results in an assert and a return
// value of zero (since zero seems to be the safest arbitrary value to return).
//
// The fact that an empty WorldRect is represented internally by right < left and top < bottom is
// strictly an internal design decision. It is transparent to the user of this class and should 
// have no effect on the usage of this class. An empty WorldRect could (in theory) just have 
// easily been represented by a flag. What's important is that empty WorldRect behavior is proper 
// and predictable, and that illegal access and manipulation of empty WorldRects is asserted in
// development and explicitly addressed in all releases.
//
// [MAF 2/24/00]
//

class WorldRect;
class WorldCube;

//--------------------------------------------------------------------
#pragma pack(push, 2)	// BEGIN 2 BYTE STUCTURE AIGNMENT <.vwx file format>

class _WorldRect {
public:
//protected:
	_WorldCoord top, left, bottom, right;   // this should be protected, not public [MAF 10/5/99]
	
//	operator const WorldRect&() const		{ return *((const WorldRect *) this); }
//	operator WorldRect& ()					{ return *((WorldRect *) this); }
	WorldCoord				MinX() const { return left; }
	WorldCoord				MinY() const { return bottom; }
	WorldCoord				MaxX() const { return right; }
	WorldCoord				MaxY() const { return top; }

	WorldRect* operator&(void)				{ return (WorldRect *) this; }
	const WorldRect* operator&(void) const	{ return (const WorldRect *) this; }

	friend class WorldRect;	
	friend class WorldCube;
};

#pragma pack(pop)	// END 2 BYTE STUCTURE AIGNMENT <.vwx file format>
//--------------------------------------------------------------------

//--------------------------------------------------------------------
#pragma pack(push, 2)	// BEGIN 2 BYTE STUCTURE AIGNMENT <.vwx file format>

class WorldRect : public _WorldRect
//
// See comments above
//
{
public:

	WorldRect(void)                               { MakeEmpty(); }
	WorldRect(WorldCoord l, WorldCoord t, 
		      WorldCoord r, WorldCoord b)         { this->SetLTRB(l, t, r, b); }
	WorldRect(const WorldPt& pt)                  { this->SetLTRB(pt.x, pt.y, pt.x, pt.y); }

	// these constructors must not aggressively validate their data because
	// they are used in very general purpose (and implicit) situations.
	WorldRect(const WorldPt& a, const WorldPt& b) { this->SetLTRB(Min(a.x, b.x), Max(a.y, b.y), Max(a.x, b.x), Min(a.y, b.y)); }

//	WorldRect(const WorldRect& r)	   { this->SetLTRB(r.left, r.top, r.right, r.bottom); }
	WorldRect(const WorldRect& r)	   { memcpy(this, &r, sizeof(WorldRect)); }   // faster for misaligned doubles [MAF FP Speedup, 2/21/01]
		
	WorldRect(const _WorldRect& r)						{ this->SetLTRB(r.left, r.top, r.right, r.bottom); }
	WorldRect(const WorldPt& cen, WorldCoord radius)	{ this->Set(cen, radius); }

	void Set(WorldCoord l, WorldCoord t,             // set all rect dimensions
		     WorldCoord r, WorldCoord b)          { SetLTRB(l, t, r, b); }
	void Set(const WorldPt& a, const WorldPt& b);    // set based on point locations
	void SetCornersTLBR(WorldPt tl, WorldPt br);     // set the topLeft and bottomRight of the rect without adjusting to make rect correct
	void Set(const WorldPt& cen, WorldCoord radius); // set the center and outset distance
	void SetLTRB(WorldCoord l, WorldCoord t, 
		         WorldCoord r, WorldCoord b);        // set all rect dimensions
	void AdjustLTRB(WorldCoord l, WorldCoord t, 
		         WorldCoord r, WorldCoord b);        // adjust all rect dimensions
	void SetLTRBWithoutValidating(WorldCoord l, WorldCoord t, 
				  				  WorldCoord r, WorldCoord b); 
	
	// Gets for the individual fields. There are no individual Sets because setting left and right
	// individually could trip the IsEmpty checks overaggressively. The multi-field Sets above should
	// handle all cases (see me if they don't). [MAF 11/17/99]

	const WorldCoord Top()    const { return WORLDRECTISEMPTY((*this), eAssert) ? 0 : top;   }   
	const WorldCoord Left()   const { return WORLDRECTISEMPTY((*this), eAssert) ? 0 : left;  }   
	const WorldCoord Bottom() const { return WORLDRECTISEMPTY((*this), eAssert) ? 0 : bottom;}   
	const WorldCoord Right()  const { return WORLDRECTISEMPTY((*this), eAssert) ? 0 : right; }   

	friend class  WorldCube;

	const WorldPt TopLeft(void)  const { return WORLDRECTISEMPTY((*this), eAssert) ? WorldPt(0, 0) : WorldPt(left,  top); }
	const WorldPt BotRight(void) const { return WORLDRECTISEMPTY((*this), eAssert) ? WorldPt(0, 0) : WorldPt(right, bottom); }
	const WorldPt BotLeft(void)  const { return WORLDRECTISEMPTY((*this), eAssert) ? WorldPt(0, 0) : WorldPt(left,  bottom); }
	const WorldPt TopRight(void) const { return WORLDRECTISEMPTY((*this), eAssert) ? WorldPt(0, 0) : WorldPt(right, top); }

	WorldRect& operator=(const WorldRect& r) { memcpy(this, &r, sizeof(WorldRect)); return *this; }

	Boolean   operator==(const WorldRect& r) const;
	Boolean   operator!=(const WorldRect& r) const { return !(*this == r); }

	int		  Compare(const WorldRect& inwrRight) const;
	
	void      Inset(WorldCoord dx,  WorldCoord dy); 
	void      Outset(WorldCoord dx, WorldCoord dy); 

	void      Offset(const WorldPt& p); 

	void      Unite(const WorldPt&   p);	
	void	  UniteNoCheck(const WorldPt& p);
	void      Unite(const WorldRect& r);

	WorldRect Union(const WorldPt&   p) const;	
	WorldRect Union(const WorldRect& r) const;	

	void      Intersect(const WorldRect& r);        	
	WorldRect Intersection(const WorldRect& r) const;	
	
	WorldPt		Center(void) const	{ return WORLDRECTISEMPTY((*this), eAssert) ? WorldPt(0, 0) : WorldPt((left+right)/2,	(top+bottom)/2); }
	WorldPt		CenterLeft() const	{ return WORLDRECTISEMPTY((*this), eAssert) ? WorldPt(0, 0) : WorldPt(left,				(top+bottom)/2); }
	WorldPt		CenterTop() const	{ return WORLDRECTISEMPTY((*this), eAssert) ? WorldPt(0, 0) : WorldPt((left+right)/2,	top); }
	WorldPt		CenterRight() const	{ return WORLDRECTISEMPTY((*this), eAssert) ? WorldPt(0, 0) : WorldPt(right,			(top+bottom)/2); }
	WorldPt		CenterBottom() const{ return WORLDRECTISEMPTY((*this), eAssert) ? WorldPt(0, 0) : WorldPt((left+right)/2,	bottom); }
	WorldCoord	Height(void) const	{ return WORLDRECTISEMPTY((*this), eAssert) ? 0 : top   - bottom; }
	WorldCoord	Width(void) const	{ return WORLDRECTISEMPTY((*this), eAssert) ? 0 : right - left; }

	WorldCoord Perimeter()  const { return ((this->Width() * 2) + (this->Height() * 2));}


	Boolean IsEmpty(EAssertStatus as = eDontAssert) const; 
	Boolean IsAProperlyDefinedEmptyRect() const;
	void    MakeEmpty(EEmptyKind kind = eStandardValue);
	Boolean IsAPoint() const { return ((bottom == top) && (left == right)); }
	Boolean IsNotEmpty(EAssertStatus /*as = eDontAssert*/) const { return !WORLDRECTISEMPTY((*this), eDontAssert); }
	Boolean IsNotAPoint() const { return !this->IsAPoint(); }


	Boolean QuickAndDirtyIntersects(const WorldRect& r) const;
	Boolean Intersects(const WorldRect& r) const;    // True even if the two rects just share a point or a line.
	Boolean Overlaps(const WorldRect& r) const;      // True if the two rects share more than a point or a line.
	Boolean ContainsRect(const WorldRect& r) const;
	Boolean ContainsPoint(const WorldPt& p) const;

	
	WorldRect& operator*=(double scale) 
	{
		if (!WORLDRECTISEMPTY((*this), eAssert)) {
			left   *= scale; 
			top    *= scale; 
			right  *= scale; 
			bottom *= scale;
		}
			
		return *this;
	}

	WorldRect& operator/=(double scale) 
	{
		if (!WORLDRECTISEMPTY((*this), eAssert))
			*this *= 1 / scale;
			
		return *this;
	}

	WorldRect operator*(double s) const 
	{
		WorldRect ret = *this; ret *= s; return ret;
	}

	WorldRect operator/(double s) const 
	{
		WorldRect ret = *this; ret /= s; return ret;
	}

	void ByteSwap();
};

#pragma pack(pop)	// END 2 BYTE STUCTURE AIGNMENT <.vwx file format>
//--------------------------------------------------------------------

inline void WorldRect::MakeEmpty(EEmptyKind (kind))
// by default, this will use the standard empty value. If a special
// empty value is requested, a value will be assigned in the TEST and BUG
// version which will guarantee that the WorldRect will fail a test
// by IsAProperlyDefinedEmptyRect();

{
	#if TEST

	if (kind == eSpecialValue) {
		bottom = left = kMaxOutOfRangeWorldCoord/10.0;
		top = right = -kMaxOutOfRangeWorldCoord/10.0;
	}
	else
	#endif
	{
		bottom = left = kMaxOutOfRangeWorldCoord;
		top = right = -kMaxOutOfRangeWorldCoord;
	}
}

inline void WorldRect::Set(const WorldPt& a, const WorldPt& b)
// DOES swap values as necessary to make rect non-empty
{ 
	SetLTRB(Min(a.x, b.x), Max(a.y, b.y), Max(a.x, b.x), Min(a.y, b.y));
}

inline void WorldRect::SetCornersTLBR(WorldPt tl, WorldPt br)
// DOES NOT swap values as necessary to make rect non-empty
{
	SetLTRB(tl.x, tl.y, br.x, br.y);
}

inline void WorldRect::Set(const WorldPt& cen, WorldCoord radius)
{
	SetLTRB(cen.x - Abs(radius), cen.y + Abs(radius), cen.x + Abs(radius), cen.y - Abs(radius)); 
}

inline void WorldRect::SetLTRBWithoutValidating(WorldCoord l, WorldCoord t, WorldCoord r, WorldCoord b)
{
	left   = l; 
	top    = t; 
	right  = r; 
	bottom = b; 
}

inline void WorldRect::SetLTRB(WorldCoord l, WorldCoord t, WorldCoord r, WorldCoord b)
{ 
	left   = l; 
	top    = t; 
	right  = r; 
	bottom = b; 
	
#if TEST
	static Sint32 assertCount = 3;	// if you want more, change value in debugger to large number

	if ((l <= r) && (b <= t)) {   // valid non-empty rect

		// Is it legal?
		if (assertCount > 0) {
			if (!VERIFYN(kMark, ((left   >= -kMaxLegalWorldCoord)
							  && (bottom >= -kMaxLegalWorldCoord)
							  && (top    <=  kMaxLegalWorldCoord)
							  && (right  <=  kMaxLegalWorldCoord)))
			)
				assertCount--;
		}
	}
	else

		// The rect is empty

		if (!this->IsAProperlyDefinedEmptyRect()) {
			if (assertCount > 0) {
				DSTOP((kMark, "Invalid partially empty WorldRect specified. Check for uninitialized values."));
				assertCount--;
			}
		}

#endif
}

inline void WorldRect::AdjustLTRB(WorldCoord l, WorldCoord t, WorldCoord r, WorldCoord b)
{ 
	left   += l; 
	top    += t; 
	right  += r; 
	bottom += b; 
	
	#if TEST
	static Sint32 assertCount = 3;	// if you want more, change value in debugger to large number
	#endif

	if ((left <= right) && (bottom <= top)) {   // valid non-empty rect
		;

		#if TEST
		// Is it legal?
		if (assertCount > 0) {
			if (!VERIFYN(kMark, ((left   >= -kMaxLegalWorldCoord)
							  && (bottom >= -kMaxLegalWorldCoord)
							  && (top    <=  kMaxLegalWorldCoord)
							  && (right  <=  kMaxLegalWorldCoord)))
			)
				assertCount--;
		}
		#endif
	}
	else
		if (this->IsAProperlyDefinedEmptyRect())
			; // valid empty rect
		else {
			#if TEST
			if (assertCount > 0) {
				DSTOP((kMark, "Invalid partially empty WorldRect specified. Check for uninitialized values."));
				assertCount--;
			}
			#endif
			
			this->MakeEmpty();
		}
}

inline Boolean WorldRect::operator==(const WorldRect& r) const 
{ 
	if (WORLDRECTISEMPTY((*this), eDontAssert) && WORLDRECTISEMPTY(r, eDontAssert))
		return true;
	else
		if ((WORLDRECTISEMPTY((*this), eDontAssert)) ^ (WORLDRECTISEMPTY(r, eDontAssert)))
			return false;
		else
			return ((WorldCoordsAreNearlyEqual(top,    r.top)) 
			     && (WorldCoordsAreNearlyEqual(right,  r.right))
				 && (WorldCoordsAreNearlyEqual(left,   r.left))
				 && (WorldCoordsAreNearlyEqual(bottom, r.bottom))); 
}

inline int WorldRect::Compare(const WorldRect& inwrRight) const
// Returns
//  1	- we are greater than inwrRight
//  0	- we are equal to inwrRight
// -1	- we are less than inwrRight
{
	int result = 1;

	if (left < inwrRight.left)
		result = -1;
	else if (left == inwrRight.left) {

		if (top < inwrRight.top)
			result = -1;
		else if (top == inwrRight.top) {

			if (right < inwrRight.right)
				result = -1;
			else if (right == inwrRight.right) {

				if (bottom < inwrRight.bottom)
					result = -1;
				else if (bottom == inwrRight.bottom)
					result = 0;
			}
		}
	}

	return result;
}

inline void WorldRect::Inset(WorldCoord dx, WorldCoord dy) 
{ 
	if (!WORLDRECTISEMPTY((*this), eAssert)) {
		left   += dx; 
		right  -= dx; 
		bottom += dy; 
		top    -= dy; 
	}
}


inline void WorldRect::Outset(WorldCoord dx, WorldCoord dy) 
{ 
	if (!WORLDRECTISEMPTY((*this), eAssert)) {
		left   -= dx; 
		right  += dx; 
		bottom -= dy; 
		top    += dy; 
	}
}


inline void WorldRect::Offset(const WorldPt& p) 
{ 
	if (!WORLDRECTISEMPTY((*this), eAssert)) {
		left   += p.x; 
		right  += p.x; 
		bottom += p.y; 
		top    += p.y; 
	}
}



inline void WorldRect::Unite(const WorldPt& p)
{
	if (WORLDRECTISEMPTY((*this), eDontAssert)) 
		this->Set(p, p);
	else {
		left   = Min(left,   p.x);
		right  = Max(right,  p.x);
		bottom = Min(bottom, p.y);
		top    = Max(top,    p.y);
	}
}

inline void WorldRect::UniteNoCheck(const WorldPt& p)
{
	left = Min(left, p.x);
	right = Max(right, p.x);
	bottom = Min(bottom, p.y);
	top = Max(top, p.y);
}

inline WorldRect WorldRect::Union(const WorldPt& p) const
{
	WorldRect r = *this; r.Unite(p); return r;
}

inline void WorldRect::Unite(const WorldRect& r)
{
	if (!WORLDRECTISEMPTY(r, eDontAssert)) {
		if (WORLDRECTISEMPTY((*this), eDontAssert))
			*this = r;
		else {
			left 	= Min(left,   r.left);
			right 	= Max(right,  r.right);
			bottom 	= Min(bottom, r.bottom);
			top 	= Max(top,    r.top);
		}
	}
}

inline WorldRect WorldRect::Union(const WorldRect& r) const
{
	WorldRect ret = *this; ret.Unite(r); return ret;
}

inline void WorldRect::Intersect(const WorldRect& r)
{
	if (this->Intersects(r)) {
		top		= Min(top,    r.top);	
		left	= Max(left,   r.left);
		bottom	= Max(bottom, r.bottom);
		right	= Min(right,  r.right);

		// possible because WorldCoord1_GE_WorldCoord2 will return true if 
		// WorldCoord2 is infinitesimally greater than WorldCoord1, as
		// we consider them equal in that case
		if (bottom > top) 
			top = bottom;
		if (left > right)
			right = left;
	}
	else
		this->MakeEmpty();
}

inline WorldRect WorldRect::Intersection(const WorldRect& r) const
{
	WorldRect ret = *this; ret.Intersect(r); return ret;
}

inline Boolean WorldRect::QuickAndDirtyIntersects(const WorldRect& r) const
//does not include case where rectangles graze
{
	return (top		> r.bottom
		 && right	> r.left
		 && left	< r.right
		 && bottom	< r.top);
}

inline Boolean WorldRect::Intersects(const WorldRect& r) const
// True even if the two rects just share a point.
{ 
	if (WORLDRECTISEMPTY((*this), eDontAssert) || WORLDRECTISEMPTY(r, eDontAssert))
		return false;
	else
		return (WorldCoord1_GE_WorldCoord2(top, r.bottom) 
		     && WorldCoord1_GE_WorldCoord2(right, r.left) 
		     && WorldCoord1_LE_WorldCoord2(left, r.right) 
		     && WorldCoord1_LE_WorldCoord2(bottom, r.top)); 
}

inline Boolean WorldRect::Overlaps(const WorldRect& r) const
// True if the two rects share more than a point or a line.
{ 
	if (WORLDRECTISEMPTY((*this), eDontAssert) || WORLDRECTISEMPTY(r, eDontAssert))
		return false;
	else
		return (WorldCoord1_GT_WorldCoord2(top, r.bottom)
		     && WorldCoord1_GT_WorldCoord2(right, r.left)
			 && WorldCoord1_LT_WorldCoord2(left, r.right) 
			 && WorldCoord1_LT_WorldCoord2(bottom, r.top)); 
}

inline Boolean WorldRect::ContainsPoint(const WorldPt& p) const
{ 
	if (WORLDRECTISEMPTY((*this), eDontAssert))
		return false;
	else
		return (WorldCoord1_LE_WorldCoord2(left, p.x)
		     && WorldCoord1_GE_WorldCoord2(right, p.x)
			 && WorldCoord1_LE_WorldCoord2(bottom, p.y)
			 && WorldCoord1_GE_WorldCoord2(top, p.y));
}

inline Boolean WorldRect::ContainsRect(const WorldRect& r) const
{ 
	if (WORLDRECTISEMPTY((*this), eDontAssert) || WORLDRECTISEMPTY(r, eDontAssert))
		return false;
	else
		return (WorldCoord1_LE_WorldCoord2(left, r.left)
		    &&  WorldCoord1_GE_WorldCoord2(right, r.right)
			&&  WorldCoord1_LE_WorldCoord2(bottom, r.bottom)
			&&  WorldCoord1_GE_WorldCoord2(top, r.top)); 
}

inline Boolean WorldRect::IsEmpty(EAssertStatus (as)) const
{
	#if TEST
	static Sint32 assertCount = 4;	// if you want more, change value in debugger to large number //-V112
	if (as == eAssert && assertCount > 0) {
		if ((top < bottom) || (right < left)) {
			--assertCount;
			DSTOP((kMark, "Trying to operate on or access individual fields of an empty rect."));
		}
		if (((top < bottom) ^ (right < left)) && assertCount > 0) {
			--assertCount;
			DSTOP((kMark, "If Rect is empty in one dimension it should be empty in the other dimension too"));
		}
	}
	#endif
	
	return ((top < bottom) || (right < left)); 
}

inline Boolean WorldRect::IsAProperlyDefinedEmptyRect() const
{
	return ((top    == -kMaxOutOfRangeWorldCoord)
	&&      (right  == -kMaxOutOfRangeWorldCoord)
	&&      (bottom ==  kMaxOutOfRangeWorldCoord)
	&&      (left   ==  kMaxOutOfRangeWorldCoord));
}

const extern WorldRect kEmptyWorldRect;

inline WorldRect EmptyWorldRect()
{
//	return WorldRect();
	return kEmptyWorldRect;
}

//----------------------------------------------------------------------------------------
struct WorldPt3;

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//
// FloatPt3
//
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//--------------------------------------------------------------------
#pragma pack(push, 2)	// BEGIN 2 BYTE STUCTURE AIGNMENT <.vwx file format>
struct FloatPt3
{
	FloatPt3() : x(FLT_MAX), y(FLT_MAX), z(FLT_MAX) {}
	FloatPt3(float inx, float iny, float inz) : x(inx), y(iny), z(inz) {}

	FloatPt3(WorldCoord inx, WorldCoord iny, WorldCoord inz)	{ this->Set(inx, iny, inz); }
	FloatPt3(const WorldPt3& in)								{ this->Set(in); }

	void Set(float inx, float iny, float inz) { x = inx; y = iny; z = inz; }

	void GS_API Set(WorldCoord inx, WorldCoord iny, WorldCoord inz);
	void GS_API Set(const WorldPt3& in);

	// Data
	float x, y, z;

	void GS_API ByteSwap();
};
#pragma pack(pop)	// END 2 BYTE STUCTURE AIGNMENT <.vwx file format>
//--------------------------------------------------------------------


//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//
// WorldPt3
//
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------


// #define DEFINE_PT3(BaseType)
struct WorldCoordBase { 
	_WorldCoord x, y, z;
	WorldCoord&		operator[](ptrdiff_t i)       { ASSERTN(kMCCoordTypes, i >= 0 && i < 3); return ((WorldCoord *) this)[i]; }
	WorldCoord		operator[](ptrdiff_t i) const { ASSERTN(kMCCoordTypes, i >= 0 && i < 3); return ((const WorldCoord *) this)[i]; }
//	Boolean			operator==(const WorldCoordBase& p) const { return x == p.x && y == p.y && z == p.z; }
//	Boolean			operator!=(const WorldCoordBase& p) const { return x != p.x || y != p.y || z != p.z; }
	Boolean			operator==(const WorldCoordBase& p) const { return WorldCoordsAreNearlyEqual(x, p.x) 
																	&& WorldCoordsAreNearlyEqual(y, p.y)
																	&& WorldCoordsAreNearlyEqual(z, p.z);  }
	Boolean			operator!=(const WorldCoordBase& p) const { return !(*this == p); }
};


// constants for the array operators for point types
enum {
	kXIndex = 0,
	kYIndex = 1,
	kZIndex = 2
};

//--------------------------------------------------------------------
#pragma pack(push, 2)	// BEGIN 2 BYTE STUCTURE AIGNMENT <.vwx file format>

struct _WorldPt3 : public WorldCoordBase {
//	operator WorldPt3&()					{ return *((WorldPt3 *) this); }
//	operator const WorldPt3&() const		{ return *((const WorldPt3 *) this); }
	typedef WorldCoord WorldCoordType;
	
	WorldCoord X() const { return x; }	// XXX_JDW_MISC const ?
	WorldCoord Y() const { return y; }
	WorldCoord Z() const { return z; }

	WorldPt3* operator&(void)				{ return (WorldPt3 *) this; }
	const WorldPt3* operator&(void) const	{ return (const WorldPt3 *) this; }
};
#pragma pack(pop)	// END 2 BYTE STUCTURE AIGNMENT <.vwx file format>
//--------------------------------------------------------------------

WorldPt3 CrossProduct(const WorldPt3& p1, const WorldPt3& p2);
WorldCoord DotProduct(const WorldPt3& p1, const WorldPt3& p2);
//--------------------------------------------------------------------
#pragma pack(push, 2)	// BEGIN 2 BYTE STUCTURE AIGNMENT <.vwx file format>
struct WorldPt3 : public _WorldPt3 {

	WorldPt3(void)						{ this->x = kMaxLegalWorldCoord; this->y = kMaxLegalWorldCoord; this->z = kMaxLegalWorldCoord;}
	
//	WorldPt3(const WorldPt3& p)	  { x = p.x; y = p.y; z = p.z; }
	WorldPt3(const WorldPt3& p)	  { memcpy(this, &p, sizeof(WorldPt3)); }   // faster for misaligned doubles [MAF FP Speedup, 2/21/01]

	WorldPt3(WorldCoord x, WorldCoord y, WorldCoord z)	{ this->x = x; this->y = y; this->z = z; }
	WorldPt3(WorldPt p, WorldCoord z)		{ this->x = p.x; this->y = p.y; this->z = z; }
	WorldPt3(const _WorldPt3& p)		{ this->y = p.y; this->x = p.x; this->z = p.z; }
	WorldPt3(const FloatPt3& p)		{ this->x = p.x; this->y = p.y; this->z = p.z; }

	WorldPt AsWorldPt() const { return WorldPt(x, y); } // I would just cast, but for some horrible reason, WorldPt has y and x in opposite order

	void Set(WorldCoord x, WorldCoord y, WorldCoord z) { this->x = x; this->y = y; this->z = z; }
	
	void SetPoint(WorldPt p, WorldCoord z)	{ x = p.x; y = p.y; this->z = z; }

	Boolean operator==(const WorldPt3& p) const { return WorldCoordsAreNearlyEqual(x, p.x) 
	                                                  && WorldCoordsAreNearlyEqual(y, p.y)
	                                                  && WorldCoordsAreNearlyEqual(z, p.z); }
	Boolean operator!=(const WorldPt3& p) const { return !(*this == p); }

	int Compare(const WorldPt3& in) const	// facilitates use in std::map, set
	// Returns
	//  1	- we are greater than inwrRight
	//  0	- we are equal to inwrRight
	// -1	- we are less than inwrRight
	{
		int result = 1;

		if (x < in.x)
			result = -1;
		else if (x == in.x) {

			if (y < in.y)
				result = -1;
			else if (y == in.y) {

				if (z < in.z)
					result = -1;
				else if (z == in.z)
					result = 0;
			}
		}

		return result;
	}

	WorldPt3	operator+(const WorldPt3& p) const { return WorldPt3(x + p.x, y + p.y, z + p.z); }
	WorldPt3	operator-(const WorldPt3& p) const { return WorldPt3(x - p.x, y - p.y, z - p.z); }
	WorldPt3	operator-(void) const { return WorldPt3(-x, -y, -z); }

	WorldPt3&	operator=(const WorldPt3& p)  { memcpy(this, &p, sizeof(WorldPt3)); return *this; }
	WorldPt3&	operator+=(const WorldPt3& p) { x += p.x; y += p.y; z += p.z; return *this; }
	WorldPt3&	operator-=(const WorldPt3& p) { x -= p.x; y -= p.y; z -= p.z; return *this; }

	WorldPt3& operator*=(double s)			{ x *= s; y *= s; z *= s; return *this; }
	WorldPt3& operator/=(double s)			{ x /= s; y /= s; z /= s; return *this; }
	
	//WorldPt3 GS_API operator*(double_gs scalar) const;
	WorldPt3 GS_API operator/(double scalar) const;

	Boolean IsZero(void) const	{ return WorldCoordIsNearlyZero(x) && WorldCoordIsNearlyZero(y) && WorldCoordIsNearlyZero(z); } 
	
	WorldPt3 GS_API Abs(void) const;
	WorldPt3 Half(void) const { return WorldPt3(x/2, y/2, z/2); }		// XXX_JDW_MISC - maybe remove

	bool Parallel(const WorldPt3 & p) const {
		const double Epsilon = 1e-9;

		WorldPt3 p1 = Normal();
		WorldPt3 p2 = p.Normal();

		return fabs(p1.x-p2.x)<Epsilon && fabs(p1.y-p2.y)<Epsilon && fabs(p1.z-p2.z)<Epsilon;
	}

	// compute the distance from 'this' WorldPt3 to parameter 'p'
	double DistanceFrom(const WorldPt3 & p) const {
        return (*this-p).Magnitude();
	}

	// It's faster to compute squared distances
	double SquaredDistanceFrom(const WorldPt3 & p) const {
        return (*this-p).MagnitudeSquared();
	}

	WorldCoord Magnitude(void)        const { return (sqrt(xpwr2(x) + xpwr2(y) + xpwr2(z))); }
	WorldCoord MagnitudeSquared(void) const { return xpwr2(x) + xpwr2(y) + xpwr2(z); }

	WorldPt3	Cross(const WorldPt3 & p) const	{ return CrossProduct(*this, p); }
	WorldCoord	Dot(const WorldPt3 & p) const	{ return DotProduct(*this, p);	}

	void            Normalize(void) { if (!this->IsZero()) *this /= this->Magnitude(); }
	WorldPt3 GS_API Normal(void) const { WorldPt3 p (*this); p.Normalize(); return p; };
	Boolean         IsNormalized(void) const { return NormalizedValueIsNearlyOne(this->MagnitudeSquared()); }

	void GS_API ByteSwap();

	DECLARE_CLASS_DEBUGGING
};

#pragma pack(pop)	// END 2 BYTE STUCTURE AIGNMENT <.vwx file format>
//--------------------------------------------------------------------

// Real classes here eventually? [MAF VW10 Revisit, 2/28/00]
struct WorldPt3;
struct _WorldPt3;
typedef WorldPt3 Vector;
typedef WorldPt3 NormalVector;
typedef WorldPt3 WorldVector;
typedef _WorldPt3 _Vector;
typedef WorldPt3 ColorVector;	// XXX_JDW_MISC - this should maybe be somewhere else

// XXX_JDW_MISC - maybe template these if possible
inline WorldPt3	operator*(const double& scalar, const WorldPt3& thePt)
	{ return WorldPt3(thePt.x * scalar, thePt.y * scalar, thePt.z * scalar); }

inline WorldPt3 operator*(const WorldPt3& inPt, const double& inScalar)
	{ return WorldPt3(inPt.x * inScalar, inPt.y * inScalar, inPt.z * inScalar); }

inline Boolean WorldPt3sAreRelativelyClose(const WorldPt3& p1, const WorldPt3& p2, const double& ratio = 1e-7)
{
	return ((WorldCoordsAreRelativelyClose(p1.x, p2.x, ratio))
		&&  (WorldCoordsAreRelativelyClose(p1.y, p2.y, ratio))
		&&  (WorldCoordsAreRelativelyClose(p1.z, p2.z, ratio)));
}


// Make these methods of WorldPt3 [MAF 11/24/99]
// XXX_JDW_MISC - or Vector. The bottom 3 boggle me and i think they should die therefore.
// The 3D people like them - see me for explanation (so I can send you to Paul). [MAF 2/28/00]
// Yes, make these part of Vector. [MAF 11/29/00]
inline WorldPt3 CrossProduct(const WorldPt3& p1, const WorldPt3& p2)
	{ return WorldPt3(p2.z*p1.y - p1.z*p2.y, p2.x*p1.z - p1.x*p2.z, p2.y*p1.x - p1.y*p2.x); }

inline WorldCoord DotProduct(const WorldPt3& p1, const WorldPt3& p2)
	{ return (p2.x * p1.x) + (p2.y * p1.y) + (p2.z * p1.z); }

inline WorldCoord DotProductX(const WorldPt3& p)
//	{ return (p.x * 1) + (p.y * 0) + (p.z * 0); }
	{ return p.x; }

inline WorldCoord DotProductY(const WorldPt3& p)
//	{ return (p.x * 0) + (p.y * 1) + (p.z * 0); }
	{ return p.y; }

inline WorldCoord DotProductZ(const WorldPt3& p)
//	{ return (p.x * 0) + (p.y * 0) + (p.z * 1); }
	{ return p.z; }




//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//
// WorldCube
//
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

class WorldCube;

//--------------------------------------------------------------------
#pragma pack(push, 2)	// BEGIN 2 BYTE STUCTURE AIGNMENT <.vwx file format>

struct _WorldCube
//
// This structure defines a bounding Grid-Aligned
// Rectilinear Parallelepiped in 3-D space (I
// suppose one could call that a GARP, but somehow
// I doubt that name would catch on.)  This base
// version exists so we can put them in unions as
// it has no constructor.
//
{
	friend class WorldCube; // updated for compatibilty to CW 6 project
	//protected:
	WorldCoord				right, top, front;
	WorldCoord				left, bottom, back;
	public:
	
//	operator const WorldCube&() const		{ return *((const WorldCube *) this); }
//	operator WorldCube& ()					{ return *((WorldCube *) this); }
	WorldCoord				MinX() const { return left; }
	WorldCoord				MinY() const { return bottom; }
	WorldCoord				MinZ() const { return back; }
	WorldCoord				MaxX() const { return right; }
	WorldCoord				MaxY() const { return top; }
	WorldCoord				MaxZ() const { return front; }

	//WorldCube* operator&(void)				{ return (WorldCube *) this; }
	//const WorldCube* operator&(void) const	{ return (const WorldCube *) this; }

	void GS_API ByteSwap();
};

#pragma pack(pop)	// END 2 BYTE STUCTURE AIGNMENT <.vwx file format>
//--------------------------------------------------------------------


//--------------------------------------------------------------------
#pragma pack(push, 2)	// BEGIN 2 BYTE STUCTURE AIGNMENT <.vwx file format>

class WorldCube : public _WorldCube
//
// This derivation of the base _WorldCube adds
// constructors, accessors, etc.  The idea is that
// this class should always be maintained in a
// consistent state (max >= min for X,Y, and Z),
// unless it is empty.  Currently, emptiness is
// handled by setting all values to 0, which is a
// poor way to represent emptiness -- it's the
// same as a point-sized cube at the origin, and
// shouldn't be.
//
{
public:
	WorldCube(void) { MakeEmpty(); }
	WorldCube(const WorldCube& c);
	WorldCube(WorldCoord top, WorldCoord bottom, WorldCoord right, WorldCoord left, WorldCoord front, WorldCoord back)
		{ this->SetYyXxZz(top, bottom, right, left, front, back); }
	GS_API WorldCube(const WorldPt3& a, const WorldPt3& b);
	WorldCube(const _WorldCube& c);
		
	WorldPt3 High(void) const;
	WorldPt3 Low(void) const;
	WorldCoord				MinX() const { return this->_WorldCube::left; }
	WorldCoord				MinY() const { return this->_WorldCube::bottom; }
	WorldCoord				MinZ() const { return this->_WorldCube::back; }
	WorldCoord				MaxX() const { return this->_WorldCube::right; }
	WorldCoord				MaxY() const { return this->_WorldCube::top; }
	WorldCoord				MaxZ() const { return this->_WorldCube::front; }
	WorldCoord				Left() const { return this->_WorldCube::left; }
	WorldCoord				Bottom() const { return this->_WorldCube::bottom; }
	WorldCoord				Back() const { return this->_WorldCube::back; }
	WorldCoord				Right() const { return this->_WorldCube::right; }
	WorldCoord				Top() const { return this->_WorldCube::top; }
	WorldCoord				Front() const { return this->_WorldCube::front; }

	void GS_API ByteSwap() { this->_WorldCube::ByteSwap(); }

	void Clear() { MakeEmpty(); } 
	Boolean IsAProperlyDefinedEmptyCube() const;
	void MakeEmpty(EEmptyKind kind = eStandardValue);
	void Set(WorldCoord top, WorldCoord bottom, WorldCoord right, WorldCoord left, WorldCoord front, WorldCoord back)
		{ this->SetYyXxZz(top, bottom, right, left, front, back); }
	void SetYyXxZz(WorldCoord top, WorldCoord bottom, WorldCoord right, WorldCoord left, WorldCoord front, WorldCoord back);
	void SetYyXxZzWithoutValidating(WorldCoord top, WorldCoord bottom, WorldCoord right, WorldCoord left, WorldCoord front, WorldCoord back);
	void GS_API Set(const WorldPt3& a, const WorldPt3& b);
	// This is weird, a "unit" cube with edge lengths of two.  This is only used one place in
	// the code, and thus really shouldn't be a member function.
	void SetToUnitCube()
		//{ top = 1.0; bottom = -1.0; right = 1.0; left = -1.0; front = 1.0; back = -1.0; }
		{ this->SetYyXxZz(1.0, -1.0, 1.0, -1.0, 1.0, -1.0); }
	void SetToPoint(const WorldPt3& inP)
		{ top = bottom = inP.y; right = left = inP.x; front = back = inP.z; }
	void SetToPoint(const WorldCoord& x, const WorldCoord& y, const WorldCoord& z)
		{ top = bottom = y; right = left = x; front = back = z; }
	void SetHighLow(WorldPt3 high, WorldPt3 low)
		{ SetYyXxZz(high.y, low.y, high.x, low.x, high.z, low.z); }
		
	WorldCube& operator=(const WorldCube& c) { memcpy(this, &c, sizeof(WorldCube)); return *this; }

	Boolean operator==(const WorldCube& c) const;
	Boolean operator!=(const WorldCube& c) const;
	WorldCube&	operator*=(double s);
	WorldCube&	operator/=(double s);  
	WorldCube	operator*(double s) const; 
	WorldCube	operator/(double s) const;

	void Offset(const WorldPt3 &p);
	WorldCube GetOffset(const Vector& p) const;
	void UniteOffset(const Vector& p);
	void Inset(WorldCoord dx, WorldCoord dy, WorldCoord dz);

	void Unite(const WorldPt3 &p);
	void Unite(const WorldCube &c);
	void Unite(const WorldRect &r, const WorldCoord z);
	void Unite(const WorldCoord& x, const WorldCoord& y, const WorldCoord& z);
	
	Boolean Intersects(const WorldCube& c) const;
	void IntersectWith(const WorldCube& c);	
	WorldCube IntersectionWith(const WorldCube& c) const;
	WorldCube GS_API Union(const WorldCube &c) const;
	
	Boolean IsEmpty(EAssertStatus as = eDontAssert) const
		{ 	
			if (as == eAssert) {
				#if TEST
				static Sint32 assertCount = 4;	// if you want more, change value in debugger to large number //-V112
				if (as == eAssert && assertCount > 0) {
					if ((left > right || bottom > top || back > front)) 
					{
						--assertCount;
						DSTOP((kMCCoordTypes, "Trying to operate on or access individual fields of an empty cube."));
					}
					if (((top < bottom) ^ (right < left)) && assertCount > 0) 
					{
						--assertCount;
						DSTOP((kMCCoordTypes, "If cube is empty in one dimension it should be empty in the other dimensions too"));
					}
				}
				#endif
			}
			return (left > right || bottom > top || back > front);
		}
	Boolean IsZero(void) const
		{ return WORLDCUBEISEMPTY((*this), eDontAssert); }

	WorldPt3 Center(void) const
		{ return WORLDCUBEISEMPTY((*this), eAssert) ? WorldPt3(0,0,0) : WorldPt3((left + right) / 2.0, (bottom + top) / 2.0, (back + front) / 2.0); }
	WorldCoord CenterX(void) const	{ return WORLDCUBEISEMPTY((*this), eAssert) ? 0 : (left + right) / 2.0; }
	WorldCoord CenterY(void) const	{ return WORLDCUBEISEMPTY((*this), eAssert) ? 0 : (bottom + top) / 2.0; }
	WorldCoord CenterZ(void) const	{ return WORLDCUBEISEMPTY((*this), eAssert) ? 0 : (back + front) / 2.0; }

	Boolean ContainsPoint(const WorldPt3& p) const
		{ return WorldCoord1_GE_WorldCoord2(p.x, left) && 
				WorldCoord1_LE_WorldCoord2(p.x, right) && 
				WorldCoord1_GE_WorldCoord2(p.y, bottom) && 
				WorldCoord1_LE_WorldCoord2(p.y, top) && 
				WorldCoord1_GE_WorldCoord2(p.z, back) && 
				WorldCoord1_LE_WorldCoord2(p.z, front); }
	Boolean ContainsCube(const WorldCube& c) const
		{ WorldCube temp(*this); temp.Unite(c); return (temp == *this); }

	WorldCoord Height(void) const	{ return WORLDCUBEISEMPTY((*this), eAssert) ? 0 : top-bottom; }
	WorldCoord Width(void) const	{ return WORLDCUBEISEMPTY((*this), eAssert) ? 0 : right-left; }
	WorldCoord Depth(void) const	{ return WORLDCUBEISEMPTY((*this), eAssert) ? 0 : front-back; }

	// lower case means low value, upper case high value
	WorldPt3 Pointxyz() const { return WORLDCUBEISEMPTY((*this), eAssert) ? WorldPt3(0,0,0) : WorldPt3(MinX(), MinY(), MinZ()); } // left, bottom, back
	WorldPt3 PointxyZ() const { return WORLDCUBEISEMPTY((*this), eAssert) ? WorldPt3(0,0,0) : WorldPt3(MinX(), MinY(), MaxZ()); } // left, bottom, front
	WorldPt3 PointxYz() const { return WORLDCUBEISEMPTY((*this), eAssert) ? WorldPt3(0,0,0) : WorldPt3(MinX(), MaxY(), MinZ()); } // left, top, back
	WorldPt3 PointxYZ() const { return WORLDCUBEISEMPTY((*this), eAssert) ? WorldPt3(0,0,0) : WorldPt3(MinX(), MaxY(), MaxZ()); } // left, top, front
	WorldPt3 PointXyz() const { return WORLDCUBEISEMPTY((*this), eAssert) ? WorldPt3(0,0,0) : WorldPt3(MaxX(), MinY(), MinZ()); } // right, bottom, back
	WorldPt3 PointXyZ() const { return WORLDCUBEISEMPTY((*this), eAssert) ? WorldPt3(0,0,0) : WorldPt3(MaxX(), MinY(), MaxZ()); } // right, bottom, front
	WorldPt3 PointXYz() const { return WORLDCUBEISEMPTY((*this), eAssert) ? WorldPt3(0,0,0) : WorldPt3(MaxX(), MaxY(), MinZ()); } // right, top, back
	WorldPt3 PointXYZ() const { return WORLDCUBEISEMPTY((*this), eAssert) ? WorldPt3(0,0,0) : WorldPt3(MaxX(), MaxY(), MaxZ()); } // right, top, front

	WorldRect FrontWorldRect(void) const
		{ WorldRect r; r.top = top; r.left = left; r.bottom = bottom; r.right = right; return r; }
};

#pragma pack(pop) // END 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)
//--------------------------------------------------------------------

inline WorldCube::WorldCube(const WorldCube& c)
{
//	right = c.right; top = c.top; front = c.front;
//	left = c.left; bottom = c.bottom; back = c.back; 

	memcpy(this, &c, sizeof(WorldCube));    // faster for misaligned doubles [MAF FP Speedup, 2/21/01]
}

inline WorldCube::WorldCube(const _WorldCube& c)
{
	right = c.right; top = c.top; front = c.front;
	left = c.left; bottom = c.bottom; back = c.back; 
}
		
inline WorldPt3 WorldCube::High(void) const	
{ 
	return WORLDCUBEISEMPTY((*this), eAssert) ? WorldPt3(0,0,0) : WorldPt3(right, top, front);
}

inline WorldPt3 WorldCube::Low(void) const		
{ 
	return WORLDCUBEISEMPTY((*this), eAssert) ? WorldPt3(0,0,0) : WorldPt3(left, bottom, back); 
}

inline Boolean WorldCube::IsAProperlyDefinedEmptyCube() const
{
	return ((top    == -kMaxOutOfRangeWorldCoord)
	&&      (right  == -kMaxOutOfRangeWorldCoord)
	&&      (front  == -kMaxOutOfRangeWorldCoord)
	&&      (bottom ==  kMaxOutOfRangeWorldCoord)
	&&      (left   ==  kMaxOutOfRangeWorldCoord)
	&&      (back   ==  kMaxOutOfRangeWorldCoord));
}

inline void WorldCube::MakeEmpty(EEmptyKind (kind)) 
{
	#if TEST

	if (kind == eSpecialValue) {
		left = bottom = back = kMaxOutOfRangeWorldCoord/10.0;
		right = top = front = -kMaxOutOfRangeWorldCoord/10.0;
	}
	else
	#endif
	{
		left = bottom = back = kMaxOutOfRangeWorldCoord;
		right = top = front = -kMaxOutOfRangeWorldCoord;
	}
}

inline void WorldCube::SetYyXxZz(WorldCoord top, WorldCoord bottom, WorldCoord right, WorldCoord left, WorldCoord front, WorldCoord back)
{ 
	if(VERIFYN(kMCCoordTypes, left <= right && bottom <= top && back <= front)) {
		this->top = top; this->bottom = bottom; this->right = right;
		this->left = left; this->front = front; this->back = back; 
	}
}

inline void WorldCube::SetYyXxZzWithoutValidating(WorldCoord top, WorldCoord bottom, WorldCoord right, WorldCoord left, WorldCoord front, WorldCoord back)
{ 
	this->top = top; this->bottom = bottom; this->right = right;
	this->left = left; this->front = front; this->back = back; 
}

inline Boolean WorldCube::operator==(const WorldCube& c) const
{ 
	return WorldCoordsAreNearlyEqual(right,  c.right) 
		&& WorldCoordsAreNearlyEqual(top,    c.top) 
	    && WorldCoordsAreNearlyEqual(front,  c.front) 
		&& WorldCoordsAreNearlyEqual(left,   c.left) 
		&& WorldCoordsAreNearlyEqual(bottom, c.bottom) 
		&& WorldCoordsAreNearlyEqual(back,   c.back); 
}

inline Boolean WorldCube::operator!=(const WorldCube& c) const
{ 
	return !(*this == c); 
}

inline WorldCube&	WorldCube::operator*=(double s) 
{
	if ( !WORLDCUBEISEMPTY((*this), eAssert) )
	{
		left *= s; right *= s; top *= s; bottom *= s; front *= s; back *= s;
	}
	return *this;
}

inline WorldCube&	WorldCube::operator/=(double s)  
{
	if ( !WORLDCUBEISEMPTY((*this), eAssert) )
	{
		left /= s; right /= s; top /= s; bottom /= s; front /= s; back /= s;
	}
	return *this;
}

inline WorldCube	WorldCube::operator*(double s) const 
{
	if ( WORLDCUBEISEMPTY((*this), eAssert))
		return *this;
	return WorldCube(top * s, bottom * s, right * s, left * s, front * s, back * s);
}

inline WorldCube	WorldCube::operator/(double s) const
{
	if ( WORLDCUBEISEMPTY((*this), eAssert))
		return *this;
	return WorldCube(top / s, bottom / s, right / s, left / s, front / s, back / s);
}

inline void WorldCube::Offset(const WorldPt3 &p)
{
	if ( !WORLDCUBEISEMPTY((*this), eAssert))
	{
		 left += p.x; right += p.x; bottom += p.y; top += p.y; back += p.z; front += p.z;
	}
}

inline WorldCube WorldCube::GetOffset(const Vector& p) const
{
	if ( WORLDCUBEISEMPTY((*this), eAssert))
		return *this;
	 return WorldCube(top + p.y, bottom + p.y, right + p.x, left + p.x, front + p.z, back + p.z);
}

inline void WorldCube::UniteOffset(const Vector& p)
{
	if ( !WORLDCUBEISEMPTY((*this), eAssert))
		this->Unite(this->GetOffset(p));
}

inline void WorldCube::Inset(WorldCoord dx, WorldCoord dy, WorldCoord dz)
{
	if ( !WORLDCUBEISEMPTY((*this), eAssert)) {
		left += dx; right -= dx; bottom += dy; top -= dy; back += dz; front -= dz;
	}
}

inline void WorldCube::Unite(const WorldPt3 &p)
{ 
	this->Unite(p.x, p.y, p.z); 
}	

inline void WorldCube::Unite(const WorldCube &c)
{ 
	if (WORLDCUBEISEMPTY((*this), eDontAssert)) 
		*this = c;
	else if (!WORLDCUBEISEMPTY(c, eDontAssert)) {
		right = Max(right, c.right); top = Max(top, c.top); front = Max(front, c.front);
		left = Min(left, c.left); bottom = Min(bottom, c.bottom); back = Min(back, c.back); 
	}
}

inline void WorldCube::Unite(const WorldRect &r, const WorldCoord z)
{
	if (!WORLDRECTISEMPTY(r, eDontAssert)) {
		if (WORLDCUBEISEMPTY((*this), eDontAssert)) 
			this->SetYyXxZz(r.Top(), r.Bottom(), r.Right(), r.Left(), z, z);
		else {
			right = Max(right, r.Right()); top = Max(top, r.Top()); front = Max(front, z);
			left = Min(left, r.Left()); bottom = Min(bottom, r.Bottom()); back = Min(back, z); 
		}
	}
}

inline void WorldCube::Unite(const WorldCoord& x, const WorldCoord& y, const WorldCoord& z)
{ 
	if (WORLDCUBEISEMPTY((*this), eDontAssert)) 
		this->SetToPoint(x, y, z);
	else {
		if (x > right)			right = x;
		else if (x < left)		left = x;
		if (y > top)			top = y;
		else if (y < bottom)	bottom = y;
		if (z > front)			front = z;
		else if (z < back)		back = z;
	}
}


inline void WorldCube::IntersectWith(const WorldCube& c)
{ 
	if (this->Intersects(c)) {
		right = Min(right, c.right); top = Min(top, c.top); front = Min(front, c.front);
		left = Max(left, c.left); bottom = Max(bottom, c.bottom); back = Max(back, c.back); 
	}
	else
		this->MakeEmpty();
}

inline WorldCube WorldCube::IntersectionWith(const WorldCube& c) const
{
	WorldCube rc = *this;
	rc.IntersectWith(c);
	return rc;
}

inline Boolean WorldCube::Intersects(const WorldCube& c) const
// True even if the two cubes just share a point.
{ 
	if (WORLDCUBEISEMPTY((*this), eDontAssert) || WORLDCUBEISEMPTY(c, eDontAssert))
		return false;
	else
		return (WorldCoord1_GE_WorldCoord2(top, c.bottom) 
		     && WorldCoord1_LE_WorldCoord2(bottom, c.top)
		     && WorldCoord1_GE_WorldCoord2(right, c.left) 
		     && WorldCoord1_LE_WorldCoord2(left, c.right) 
		     && WorldCoord1_GE_WorldCoord2(front, c.back) 
		     && WorldCoord1_LE_WorldCoord2(back, c.front)); 
}

inline WorldCube EmptyWorldCube()
{
	return WorldCube();
}


//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//
// TransformMatrix
//
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

class TransformMatrix;


//--------------------------------------------------------------------
#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)

class _TransformMatrix 	
{
public:	
	union {
		
		#if GS_SDK_VW8_COMPATIBLE
		_WorldCoord	array[4][3];
		#endif
		
		_WorldCoord	mat[4][3];
		struct {
			double a00;    double a01;    double a02;
			double a10;    double a11;    double a12;
			double a20;    double a21;    double a22;
			_WorldCoord xOff;   _WorldCoord yOff;   _WorldCoord zOff;
		} v1;
		struct {
			_Vector		i, j, k;
			_WorldPt3	offset;
		} v2;
	};

	TransformMatrix* operator&(void)				{ return (TransformMatrix *) this; }
	const TransformMatrix* operator&(void) const	{ return (const TransformMatrix *) this; }
};

#pragma pack(pop) // END 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)
//--------------------------------------------------------------------


//--------------------------------------------------------------------
#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)

class TransformMatrix : public _TransformMatrix
// This is a standard 4x4 matrix with the right column vector (0 0 0 1) removed
// (perspective transformation & w).  It should always be orthogonal (all basis 
// vectors are orthonormal).
{
public:
	TransformMatrix()  { }

	TransformMatrix& operator=(const TransformMatrix& tm)	{ memcpy(this, &tm, sizeof(TransformMatrix)); return *this; }
	TransformMatrix(const _TransformMatrix& t)	{ this->v2.i = t.v2.i; this->v2.j = t.v2.j; this->v2.k = t.v2.k; this->v2.offset = t.v2.offset; }

	// XXX_JDW_MISC - maybe R0() R1() R2() P() C0() C1() C2() ?  XDir() YDir() ZDir() Pt() IDir() JDir() KDir() ? Review.

	//const NormalVector& R0() const	{ return reinterpret_cast<const NormalVector&>(v2.i); }	// mat[0][*]
	//const NormalVector& R1() const	{ return reinterpret_cast<const NormalVector&>(v2.j); }	// mat[1][*]
	//const NormalVector& R2() const	{ return reinterpret_cast<const NormalVector&>(v2.k); }	// mat[2][*]
	//const WorldPt3& P() const		{ return reinterpret_cast<const WorldPt3&>(v2.offset); }// mat[3][*]  rename? XXX_JDW_MISC
	
	NormalVector C0() const	{ return NormalVector(v1.a00, v1.a10, v1.a20); }	// mat[*][0]
	NormalVector C1() const	{ return NormalVector(v1.a01, v1.a11, v1.a21); }	// mat[*][1]
	NormalVector C2() const	{ return NormalVector(v1.a02, v1.a12, v1.a22); }	// mat[*][2]

	// I'm opposed to non-const ref returning functions like this -- it's basically the same as having
	// a public member variable -- but we have direct member access now anyway
	// so I'll live with it. -- ACB 1/28/00
	NormalVector& R0()				{ return reinterpret_cast<NormalVector&>(v2.i); }		// mat[0][*]
	NormalVector& R1()				{ return reinterpret_cast<NormalVector&>(v2.j); }		// mat[1][*]
	NormalVector& R2()				{ return reinterpret_cast<NormalVector&>(v2.k); }		// mat[2][*]
	WorldPt3& P()					{ return reinterpret_cast<WorldPt3&>(v2.offset); }		// mat[3][*]  rename? XXX_JDW_MISC

	// We might want to assert that the vectors are normalized, but the plan is to make
	// NormalVector do some of that and not just be a typedef.
	void SetRow0(const NormalVector& vec)
		{ mat[0][0] = vec.x; mat[0][1] = vec.y; mat[0][2] = vec.z; }
	void SetRow1(const NormalVector& vec)
		{ mat[1][0] = vec.x; mat[1][1] = vec.y; mat[1][2] = vec.z; }
	void SetRow2(const NormalVector& vec)
		{ mat[2][0] = vec.x; mat[2][1] = vec.y; mat[2][2] = vec.z; }
	
	WorldPt GetOffset2D() const				{ return WorldPt(v1.xOff, v1.yOff); }
	void SetOffset2D(const WorldPt& inwpt)	{ v1.xOff = inwpt.X(); v1.yOff = inwpt.Y(); }

	bool GS_API IsOrthogonal() const;
	bool 		Is2DOrHybrid() const		{ return (Abs(v2.k.z) == 1.0); };
	bool 		IsNearly2DOrHybrid() const	{ return NormalizedValueIsNearlyOne(Abs(v2.k.z)); };
	bool GS_API IsIdentity() const;
	bool GS_API HasNoRotation() const;
	bool		IsExactlyEqualTo(const TransformMatrix& m) const { return (memcmp(this, &m, sizeof(TransformMatrix)) == 0); }
	int	 GS_API Compare(const TransformMatrix& inRight) const;
	
	void GS_API SetToIdentity() {}; // TODO
	

	void GS_API ByteSwap();
};

#pragma pack(pop) // END 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)
//--------------------------------------------------------------------


struct TransformXMatrix
// 4x4 matrix of doubles. Unless you need the fourth column for something like perspective
// calculations, you should use the 3x4 TransformMatrix instead. 
{	
	double	mat[4][4];
	void GS_API SetToIdentity() {};  //TODO
};

// XXX_JDW_MINOR - Should rename TransformXMatrix to something like TransformMatrix4x4 or Matrix4 or...
//#if GS_SDK_VW8_COMPATIBLE
//typedef TransformMatrix4x4 TransformXMatrix;
//#endif


//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//
// CubeVerts
//
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

class CubeVerts
{
public:
	CubeVerts() {}
	CubeVerts(const CubeVerts& inCubeVerts)	{ this->Set(inCubeVerts); }
	CubeVerts(const WorldCube& inCube)		{ this->Set(inCube); }

	void Set(const CubeVerts& inCubeVerts)	{ memcpy(this, &inCubeVerts, sizeof(CubeVerts)); }

	void Set(const WorldCube& inCube)
	{
		topLeftFront		= inCube.PointxYZ();
		topRightFront		= inCube.PointXYZ();
		topLeftBack			= inCube.PointxYz();
		topRightBack		= inCube.PointXYz();
		bottomLeftFront		= inCube.PointxyZ();
		bottomRightFront	= inCube.PointXyZ();
		bottomLeftBack		= inCube.Pointxyz();
		bottomRightBack		= inCube.PointXyz();
	}

	void Offset(const WorldPt3& inpwpt3Off)				{ for_i(8) (*this)[i] += inpwpt3Off; }
	void GS_API Transform(const TransformMatrix& inMat);
	void GS_API InverseTransform(const TransformMatrix& inMat);

	CubeVerts& operator=(const WorldCube& inCube)		{ this->Set(inCube); return *this; }
	CubeVerts& operator=(const CubeVerts& inCubeVerts)	{ this->Set(inCubeVerts); return *this; }

	WorldPt3& operator[](ptrdiff_t i)					{ return ((WorldPt3 *) this)[i]; }
	const WorldPt3& operator[](ptrdiff_t i) const		{ return ((const WorldPt3 *) this)[i]; }

	WorldPt3 topLeftFront;
	WorldPt3 topRightFront;
	WorldPt3 topLeftBack;
	WorldPt3 topRightBack;
	WorldPt3 bottomLeftFront;
	WorldPt3 bottomRightFront;
	WorldPt3 bottomLeftBack;
	WorldPt3 bottomRightBack;
};

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//
// Axis
//
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

class Ray
{
public:
	Ray() {}
	Ray(const WorldPt3& inwpt3Vertex, const NormalVector& inwpt3Direction)
		: vertex(inwpt3Vertex), direction(inwpt3Direction) {}

	void GS_API Transform(const TransformMatrix &mat);
	void GS_API InverseTransform(const TransformMatrix &mat);

	WorldPt3		vertex;
	NormalVector	direction;	// XXX_JDW_MISC - was vector, need to make sure should always be normal vector before normalizing automatically
};


//--------------------------------------------------------------------
#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)

struct Axis {
	WorldPt3			vertex;
	Vector	 			k; // defines plane
	Vector	 			i; // base axis - pseudo-x
	Vector	 			j; // vertical axis - pseudo-y

	GS_API Axis(const WorldPt3& ini, const WorldPt3& inj, const WorldPt3& ink, const WorldPt3& inv) : vertex(inv), k(ink), i(ini), j(inj) {}
	GS_API Axis(void) : vertex(0,0,0), k(0,0,1), i(1,0,0), j(0,1,0)		{ }
	GS_API Axis(const Axis& a)											{ *this = a; }

	Axis& operator=(const Axis& a)		{ ::memcpy(this, &a, sizeof(Axis)); return *this; }

	Boolean operator==(const Axis& in) const { return ::memcmp(this, &in, sizeof(Axis)) == 0; }
	Boolean operator!=(const Axis& in) const { return !(*this == in);  }

	Boolean NearlyEqual(const Axis& in) const			{ return vertex==in.vertex && i==in.i && j==in.j && k==in.k; }
	Boolean OrientedNearlyEqual(const Axis& in) const	{ return i==in.i && j==in.j && k==in.k; }
	Boolean Oriented90Mult(const Axis& in) const
	{
		Boolean outb90Mult = true;

		if ( ! (i == in.i || i == in.j || i == in.k
				|| -i == in.i || -i == in.j || -i == in.k)) {

			outb90Mult = false;
		}
		else if ( ! (j == in.i || j == in.j || j == in.k
				|| -j == in.i || -j == in.j || -j == in.k)) {

			outb90Mult = false;
		}
		else if ( ! (k == in.i || k == in.j || k == in.k
				|| -k == in.i || -k == in.j || -k == in.k)) {

			outb90Mult = false;
		}

		return outb90Mult;
	}

	Ray& RayView(void) 					{ return *((Ray *) &this->vertex); }
	const Ray& RayView(void) const 		{ return *((const Ray *) &this->vertex); }

	void GS_API ByteSwap(EByteSwapFPMode fpFormat);
};

#pragma pack(pop) // END 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)
//--------------------------------------------------------------------

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//
// WorldRectVerts
//
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------


class WorldRectVerts
{
public:
	WorldPt				topLeft;
	WorldPt				topRight;
	WorldPt				bottomLeft;
	WorldPt				bottomRight;

	WorldRectVerts()							{ this->MakeEmpty(); }
	WorldRectVerts(const WorldRect& inR)		{ this->Set(inR); }

	WorldRectVerts& operator=(const WorldRectVerts& cv)	
		{ memcpy(this, &cv, sizeof(WorldRectVerts)); return *this; }

	WorldPt& operator[](ptrdiff_t i)					{ return ((WorldPt *) this)[PIN(i, 0, 3)]; }
	const WorldPt& operator[](ptrdiff_t i) const		{ return ((const WorldPt *) this)[PIN(i, 0, 3)]; }

	bool IsAPoint() const;
	bool IsEmpty() const;
	void MakeEmpty();

	WorldPt	Center() const			{ return (topLeft+bottomRight)/2; }
	WorldPt	CenterLeft() const		{ return (topLeft+bottomLeft)/2; }
	WorldPt	CenterTop() const		{ return (topLeft+topRight)/2; }
	WorldPt	CenterRight() const		{ return (topRight+bottomRight)/2; }
	WorldPt	CenterBottom() const	{ return (bottomLeft+bottomRight)/2; }

	WorldCoord Width() const		{ return topRight.DistanceFrom(topLeft); }
	WorldCoord Height() const		{ return bottomLeft.DistanceFrom(topLeft); }

	WorldPt&		ClockwiseFromTopLeft(size_t i)			{ Sint32 order[4] = {0,1,3,2};	return (*this)[order[PIN(i, 0, 3)]]; }
	const WorldPt&	ClockwiseFromTopLeft(size_t i) const	{ Sint32 order[4] = {0,1,3,2};	return (*this)[order[PIN(i, 0, 3)]]; }

	void GS_API Set(const WorldRect& inR);

	void GS_API SetRotatedRect(const WorldPt& pt1, const WorldPt& pt2, const TransformMatrix& mat);
	void GS_API GetBoundingBox(WorldRect& wr) const;

	void GS_API Transform(const TransformMatrix &mat);
	void GS_API InverseTransform(const TransformMatrix &mat);

	void Unite(const WorldRectVerts cwrv);
	WorldRectVerts Union(const WorldRectVerts cwrv) const;
	
	void Outset(WorldCoord dI, WorldCoord dJ);
	void Offset(const WorldPt& inwpt);
	WorldRectVerts& operator*=(double scale);

	bool IsFlipped() const;
};

void GS_API RotateWorldRect(const TransformMatrix &mat, const WorldRect &c, WorldRectVerts &verts);


typedef WorldPt				*WorldPtPtr;
typedef WorldPt3			*WorldPt3Ptr;
typedef Vector				*VectorPtr;
typedef WorldRect			*WorldRectPtr;
typedef WorldCube			*WorldCubePtr;

typedef TransformMatrix		*TransformMatrixPtr;
typedef TransformXMatrix	*TransformXMatrixPtr;


//////////////////////////////////////////////////////////////////////////////////////////

enum ECoordKind 
// Used by functions that display values to decide whether or not to add the user 
// origin offset.
//	--- This enum is also in WinExports.h ---
{
	eNoUserOrigin, 			// A relative value, such as an object length.
	eIncludeUserOriginX, 	// Absolute X and Y positions including the user 
	eIncludeUserOriginY, 	//    origin offsets.	
	eIncludeUserOrigin		// Include X and Y; this is used with points.
};

#if 0
XXX_JDW_MISC
enum EValueReduction {
	eDontReduceValue,
	eReduceValueSlightly
};
#endif



inline short LongToShort(Sint32 x)   // only checks positive
{
	return (VERIFYN(kEveryone, (x <= 32767))) ? (short) x : 32767;
}



//////////////////////////////////////////////////////////////////////////////////////////
// == Numerical classes
//////////////////////////////////////////////////////////////////////////////////////////

enum EAngleMeasure { eAngleError, eDegrees, eMinutes, eSeconds, eRadians, eGrads };

#if Chao && 0
// help find incorrect return types
typedef float	Degrees;
typedef float	Radians;
typedef float	QDDegrees;
typedef float	QDRadians;
typedef	float	UnknownAngleType;

#else
typedef double	Degrees;
typedef double	Radians;
typedef double	QDDegrees;  // All QDDegrees angles correspond to QuickDraw Definition. (0 north and positive clockwise)
typedef double	QDRadians;
typedef	double	UnknownAngleType;

#endif // Chao


Boolean RadiansAreNearlyEqual(Radians angle1, Radians angle2);

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

// This is test code for making a WorldCoord a class. It's not workable right now (nor will
// it be in the forseeable future due to C++ limitations and the way we currently consider
// doubles and WorldCoords interchangeable in the main code). I use this to flush out 
// certain ways WorldCoords are being used (e.g. finding all places constant values are being
// assigned to WorldCoord variables). Please leave this code here. [MAF 12/23/99]

#if 0

class WorldCoord {
public:
	double d;

	WorldCoord() { }
	WorldCoord(const short x)	{ d = x; }
	WorldCoord(const double x)	{ d = x; }

	operator double() const { return d; }

	double*       operator&(void)			{ return (double *) this; }
	const double* operator&(void) const 	{ return (const double *) this; }

//	WorldCoord operator=(const WorldCoord dIn)  { d = dIn; return *this; }
//	WorldCoord operator=(const short      dIn)  { d = dIn; return *this; }

	Boolean operator==(const WorldCoord x) const { return (d == x.d); }
	Boolean operator!=(const WorldCoord x) const { return (d != x.d); }
	Boolean operator> (const WorldCoord x) const { return (d >  x.d); }
	Boolean operator>=(const WorldCoord x) const { return (d >= x.d); }
	Boolean operator< (const WorldCoord x) const { return (d <  x.d); }
	Boolean operator<=(const WorldCoord x) const { return (d <= x.d); }
	Boolean operator==(const double x) const { return (d == x); }
	Boolean operator!=(const double x) const { return (d != x); }
	Boolean operator> (const double x) const { return (d >  x); }
	Boolean operator>=(const double x) const { return (d >= x); }
	Boolean operator< (const double x) const { return (d <  x); }
	Boolean operator<=(const double x) const { return (d <= x); }
	Boolean operator==(const Sint32 x) const { return (d == x); }
	Boolean operator!=(const Sint32 x) const { return (d != x); }
	Boolean operator> (const Sint32 x) const { return (d >  x); }
	Boolean operator>=(const Sint32 x) const { return (d >= x); }
	Boolean operator< (const Sint32 x) const { return (d <  x); }
	Boolean operator<=(const Sint32 x) const { return (d <= x); }

	WorldCoord operator-(void) const				{ return WorldCoord(-d); }

	WorldCoord operator+(const WorldCoord x) const	{ return WorldCoord(d + x.d); }
	WorldCoord operator-(const WorldCoord x) const	{ return WorldCoord(d - x.d); }
	WorldCoord operator*(const WorldCoord x) const	{ return WorldCoord(d * x.d); }
	WorldCoord operator/(const WorldCoord x) const	{ return WorldCoord(d / x.d); }

	WorldCoord operator+(const double x) const		{ return WorldCoord(d + x); }
	WorldCoord operator-(const double x) const		{ return WorldCoord(d - x); }
	WorldCoord operator*(const double x) const		{ return WorldCoord(d * x); }
	WorldCoord operator/(const double x) const		{ return WorldCoord(d / x); }

	WorldCoord operator+(const Sint32 x) const		{ return WorldCoord(d + x); }
	WorldCoord operator-(const Sint32 x) const		{ return WorldCoord(d - x); }
	WorldCoord operator*(const Sint32 x) const		{ return WorldCoord(d * x); }
	WorldCoord operator/(const Sint32 x) const		{ return WorldCoord(d / x); }

	WorldCoord operator+=(const WorldCoord x) 	{ d += x.d; return *this; }
	WorldCoord operator-=(const WorldCoord x) 	{ d -= x.d; return *this; }
	WorldCoord operator*=(const WorldCoord x) 	{ d *= x.d; return *this; }
	WorldCoord operator/=(const WorldCoord x) 	{ d /= x.d; return *this; }
};

//WorldCoord operator*(WorldCoord x1, double x2) { return x1 * x2; }
//WorldCoord operator*(WorldCoord x1, Sint32 x2)   { return x1 * x2; }
//WorldCoord operator*(WorldCoord x1, short x2)  { return x1 * x2; }

WorldCoord WORLDCOORD(double d) { return WorldCoord(d); }
#define WC (WorldCoord) 

#endif   // class WorldCoord test code
}


#endif  // #ifndef _MCCOORDTYPES_

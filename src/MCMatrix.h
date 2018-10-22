//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	
//	Declares a set of useful matrix classes & functions.
//


#ifndef _MCMATRIX_
#define _MCMATRIX_

#pragma once

#include "MCCoordTypes.h"


//**********************************************************************************
//******************************      Constants      *******************************
//**********************************************************************************

typedef short MajorAxisSpec;

const MajorAxisSpec kNoAxis = 0;
const MajorAxisSpec kXAxis = 1;
const MajorAxisSpec kYAxis = 2;
const MajorAxisSpec kZAxis = 3;


//**********************************************************************************
//**************************  TransformXMatrix Routines  ***************************
//**********************************************************************************

void GS_API MatrixToXMatrix(const TransformMatrix &source, TransformXMatrix &dest);
TransformXMatrix MatrixToXMatrix(const TransformMatrix &source);
void GS_API XMatrixToMatrix(const TransformXMatrix &source, TransformMatrix &dest);
TransformMatrix XMatrixToMatrix(const TransformXMatrix &source);
Boolean GS_API XMatrix2Matrix(const TransformXMatrix& source, TransformMatrix& dest);


// NEW MATRIX TRANSFORMS 3/3/97
void GS_API XPointTransformN(const WorldPt3 &a, const TransformXMatrix &mat, WorldPt3 &b);

inline WorldPt3 GS_API XPointTransformN(const WorldPt3 &a, const TransformXMatrix &mat)
// I made this inline to make render pipeline sweeping faster  -DLD 6/4/99
{	
	return WorldPt3(a.x * mat.mat[0][0] + a.y * mat.mat[1][0] + a.z * mat.mat[2][0] + mat.mat[3][0],
					a.x * mat.mat[0][1] + a.y * mat.mat[1][1] + a.z * mat.mat[2][1] + mat.mat[3][1], 
					a.x * mat.mat[0][2] + a.y * mat.mat[1][2] + a.z * mat.mat[2][2] + mat.mat[3][2]);
}

void GS_API InverseXPointTransformN(const WorldPt3 &a, const TransformXMatrix &mat, WorldPt3 &b);
WorldPt3 GS_API InverseXPointTransformN(const WorldPt3 &a, const TransformXMatrix &mat);
void GS_API VectorXTransformN(const Vector a, const TransformXMatrix &mat, Vector &b);
void GS_API InverseVectorXTransformN(const Vector a, const TransformXMatrix &mat, Vector &b);
void GS_API XMatrixMultiply(const TransformXMatrix &mat1, const TransformXMatrix &mat2, TransformXMatrix &dest);
TransformXMatrix XMatrixMultiply(const TransformXMatrix &m1, const TransformXMatrix &m2);
void GS_API SetAxisRotationXMatrix(MajorAxisSpec axis, double_param degrees, TransformXMatrix &mat);
void GS_API SetVectorRotationXMatrix(const Vector &axis, double_param degrees, TransformXMatrix &mat);
void GS_API MakeXMatrixOrthogonal(TransformXMatrix &mat);
void GS_API InvertXMatrix(const TransformXMatrix &source, TransformXMatrix &dest);
void GS_API AssignVectorsToXMatrix(const Vector &aVec, const Vector &bVec, const Vector &cVec, TransformXMatrix &mat);


//**********************************************************************************
//**************************  TransformMatrix Routines  ****************************
//**********************************************************************************

// NEW MATRIX TRANSFORMS 3/3/97
void GS_API PointTransformN(const WorldPt3 &a, const TransformMatrix &mat, WorldPt3 &b);
void GS_API NonLinearPointTransformN(const WorldPt3 &a, const TransformMatrix &mat, WorldPt3 &b);
void GS_API InversePointTransformN(const WorldPt3 &a, const TransformMatrix &mat, WorldPt3 &b);
void GS_API InversePointTransformN(const WorldPt3 &a, const TransformMatrix &mat, WorldPt3 &b);
void GS_API VectorTransformN(const Vector& a, const TransformMatrix& mat, Vector& b);
void GS_API VectorTransformN(const WorldPt3 &a, const TransformMatrix &mat, WorldPt3 &b);
void GS_API InverseVectorTransformN(const WorldPt3 &a, const TransformMatrix &mat, WorldPt3 &b);
void GS_API InverseVectorTransformN(const Vector &a, const TransformMatrix &mat, Vector &b);
void GS_API CubeTransformN(const WorldCube& in, const TransformMatrix& mat, WorldCube& out);

inline WorldPt3 operator*(const WorldPt3& inPt, const TransformMatrix& inMat)
// XPointTransformN for when there are many transforms to do and the code looks cluttered.
// John Williams, 3/24/99
{
	WorldPt3	outPt;
	PointTransformN(inPt, inMat, outPt);
	return outPt;
}

// NEW 2D TRANSFORMS
void InversePoint2DTransform(const WorldPt &a, const TransformMatrix &mat, WorldPt &b);

inline void Point2DTransform(const WorldPt &a, const TransformMatrix &mat, WorldPt &b)
{
#if 0
	ASSERT4BYTEALIGNMENT(&a, "Point2DTransform point a");
	ASSERT4BYTEALIGNMENT(&b, "Point2DTransform point b");
	ASSERT4BYTEALIGNMENT(&mat, "Point2DTransform matrix");
#endif

	WorldPt	p = a;

	b.x = 	p.x * mat.v1.a00 +
			p.y * mat.v1.a10 +
			mat.v1.xOff;
	b.y =	p.x * mat.v1.a01 +
			p.y * mat.v1.a11 +
			mat.v1.yOff;
}

void InverseVector2DTransform(const WorldPt &a, const TransformMatrix &mat, WorldPt &b);

////////////////////////////////////////////////////////////
inline void Vector2DTransform(const Vector2 &a, const TransformMatrix &mat, Vector2 &b)
{
#if 0
	ASSERT4BYTEALIGNMENT(&a, "Vector2DTransform point a");
	ASSERT4BYTEALIGNMENT(&b, "Vector2DTransform point b");
	ASSERT4BYTEALIGNMENT(&mat, "Vector2DTransform matrix");
#endif

	Vector2	p = a;

	b.x = 	p.x * mat.v1.a00 +
			p.y * mat.v1.a10;

	b.y =	p.x * mat.v1.a01 +
			p.y * mat.v1.a11;
}

void PointTransformTo2D(const WorldPt3 &a, const TransformMatrix &mat, WorldPt &b);


void GS_API IdentityMatrix(TransformMatrix &mat);
const GS_API TransformMatrix& IdentityMatrix();

TransformMatrix GS_API MatrixMultiply(const TransformMatrix &mat1, const TransformMatrix &mat2);

void GS_API MatrixMakeOrthogonal(TransformMatrix &mat);
void GS_API InvertMatrix(const TransformMatrix &source, TransformMatrix &dest);
void GS_API SetAxisRotationMatrix(MajorAxisSpec axis, double_param degrees, TransformMatrix &mat);
void GS_API SetAxisRotationMatrix(MajorAxisSpec axis, double_param degrees, const WorldPt3& center, TransformMatrix &mat);
void GS_API SetVectorRotationMatrix(const Vector &theVec, double_param degrees, TransformMatrix &mat);
void GS_API Set2DAxisFlipMatrix(const MajorAxisSpec axis, const WorldPt& origin, TransformMatrix& tm);
Boolean GS_API MakeVectorsOrthonormal(Vector &aVec, Vector &bVec, Vector &cVec, Boolean first);
void GS_API GetVectorsFromMatrix(const TransformMatrix &mat, Vector &aVec, Vector &bVec, Vector &cVec);
void GS_API AssignVectorsToMatrix(const Vector &aVec, const Vector &bVec, const Vector &cVec, TransformMatrix &mat);
void GS_API CreateMatrixFromAxis(const Axis &axis, TransformMatrix &mat);
void GS_API CreateAxisFromMatrix(const TransformMatrix &mat, Axis &axis);
void GS_API SetMatrixKI(const WorldPt3 &kDir, const WorldPt3 &iDir, TransformMatrix &mat);
void GS_API SetMatrixKJ(const WorldPt3 &kDir, const WorldPt3 &jDir, TransformMatrix &mat);
void GS_API SetMatrixIJ(const WorldPt3 &kDir, const WorldPt3 &iDir, TransformMatrix &mat);
void GS_API TranslateMatrix(TransformMatrix &f, WorldCoord x, WorldCoord y, WorldCoord z);
void GS_API SetMultiAxisSpinMatrix(	TransformMatrix &mat,
						MajorAxisSpec firstAxis,
						MajorAxisSpec secondAxis,
						MajorAxisSpec thirdAxis,
						double_param firstAngleDegrees,
						double_param secondAngleDegrees,
						double_param thirdAngleDegrees,
						const WorldPt3 &center,
						Boolean fromzero);
void GS_API GetAnglesFromMatrix(const TransformMatrix &inMat, Degrees &outAboutXAxis, Degrees &outAboutYAxis, Degrees &outAboutZAxis);

// This function calculates a transformation matrix (non afine)
// that transforms the first triangle (inPt1, inPt2, inPt3) into (transfPt1, transfPt2, transfPt3) triangle
bool GS_API CalcTransformFromOneTriToAnother(TransformMatrix& outMatrix,
											const WorldPt3& inPt1, const WorldPt3& inPt2, const WorldPt3& inPt3,
											const WorldPt3& transfPt1, const WorldPt3& transfPt2, const WorldPt3& transfPt3);

void GS_API RotateMatrix2D(double_param degrees, const WorldPt& center, TransformMatrix &mat);

bool RayPlaneIntersection(const WorldPt3& ptOnPlane, const WorldPt3& planeNormal, const Ray& ray, WorldPt3* pOutIntersection=NULL, double* pOutDistance=NULL);
bool RayPlaneIntersection(const TransformMatrix& plane, const Ray& ray, WorldPt3* pOutIntersection=NULL, double* pOutDistance=NULL);
bool RayPlaneIntersection(const Axis& plane, const Ray& ray, WorldPt3* pOutIntersection=NULL, double* pOutDistance=NULL);
bool IsPointNearLine(const WorldPt & inPoint, const WorldPt & inP0, const WorldPt & inP1, double inNearDist, Sint32 inLineType);
bool RayCubeIntersection(const WorldCube& inwc, const Ray& inRay,
						 WorldPt3* outpwpt3Int1=NULL, WorldPt3* outpwpt3Int2=NULL,
						 double* outpA1=NULL, double* outpA2=NULL) ;
bool LineIntersectsCube( const WorldCube& inWC, const WorldPt3& L1, const WorldPt3& L2, WorldPt3 &Hit1, WorldPt3 &Hit2 );

#if BUG
void BugVerifyTransformMatrix(const TransformMatrix& matrix);
#endif

inline void VerifyTransformMatrix(const TransformMatrix& BUG_ONLY(matrix))
{
#if BUG
	BugVerifyTransformMatrix(matrix);
#endif
}

//**********************************************************************************
//******************************  Inline transforms  *******************************
//**********************************************************************************

// NEW MATRIX TRANSFORMS 3/3/97

inline WorldPt3 PointTransformN(const WorldPt3 &a, const TransformMatrix &mat)
{
	WorldPt3 result;
	PointTransformN(a, mat, result);
	return result;
}

inline WorldPt3 NonLinearPointTransformN(const WorldPt3 &a, const TransformMatrix &mat)
{
	WorldPt3 result;
	NonLinearPointTransformN(a, mat, result);
	return result;
}

inline WorldPt3 InversePointTransformN(const WorldPt3 &a, const TransformMatrix &mat)
{
	WorldPt3 result;
	InversePointTransformN(a, mat, result);
	return result;
}

inline Vector VectorTransformN(const Vector &a, const TransformMatrix &mat)
{
	Vector result;
	VectorTransformN(a, mat, result);
	return result;
}

inline WorldPt3 InverseVectorTransformN(const Vector &a, const TransformMatrix &mat)
{
	Vector result;
	InverseVectorTransformN(a, mat, result);
	return result;
}


//**********************************************************************************
//*****************************  CoordSystem Classes  ******************************
//**********************************************************************************


class TOneWayCoordSystem
{
protected:
	Axis						fCSAxis; 
	TransformMatrix				fCSMat;
	
public:
	GS_API TOneWayCoordSystem(void);
	GS_API TOneWayCoordSystem(const TransformMatrix& csMatrix);
	GS_API TOneWayCoordSystem(const Axis& csAxis);

	TOneWayCoordSystem(const TOneWayCoordSystem& cs)				{ memcpy(this, &cs, sizeof(TOneWayCoordSystem)); }
	TOneWayCoordSystem& operator=(const TOneWayCoordSystem& cs)		{ memcpy(this, &cs, sizeof(TOneWayCoordSystem)); return *this; }

	const TransformMatrix&	GetMat() const		{ return this->fCSMat; }
	const Axis&				GetAxis() const		{ return this->fCSAxis; }
};


class TCoordSystem : public TOneWayCoordSystem
{
protected:
	TransformMatrix				fInverseCSMat; 
	
	void GS_API Setup(void);
	
public:
	GS_API TCoordSystem(void);
	GS_API TCoordSystem(const TOneWayCoordSystem& csSystem);
	GS_API TCoordSystem(const TransformMatrix& csMatrix);
	GS_API TCoordSystem(const Axis& csAxis);

	TCoordSystem(const TCoordSystem& cs)				{ memcpy(this, &cs, sizeof(TCoordSystem)); }
	TCoordSystem& operator=(const TCoordSystem& cs)		{ memcpy(this, &cs, sizeof(TCoordSystem)); return *this; }
	
	const TransformMatrix& GetInverseMat() const		{ return *((const TransformMatrix *) &this->fInverseCSMat); }
	bool IsOrthonormal() const							{ return fInverseCSMat.IsOrthogonal(); }
};


#endif

//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	
//	Implements a set of useful vector-math functions and classes.
//


#include "StdHeaders.h"	// DO NOT MOVE THIS LINE FROM BEING THE FIRST NON-COMMENT LINE.  [DMB, 10/30/95]

#if GS_WIN

	#include "Kernel/QTHeader.h"

#endif

#include "Kernel/MCCoordTypes.h"
#include "Kernel/MCVector.h"
#include "Kernel/MCMatrix.h"

// This must follow all header files.
#undef THIS_FILE
DECLARE_THIS_FILE



//////////////////////////////
// this test code will not work under Windows until Microsoft introduces compiler support for 
// aligning data (specifically doubles) on the stack. As it is, double precision data is aligned only
// ot 4 byte boundaries. In the future (MSVC 7 I hope) we can turn this code on for both platforms.
//
// Also, until we are able to change the file format, we cannot align data which is misaligned in structures
// which are stored on disk. Therefore this test code is good only for finding misaligned data in easily
// accessible data structures. It will remain turned off until needed. - PCP 2-12-2001
//////////////////////////////


#if MFarnan && GS_MAC && _MINICAD_
#include "PreferencesRec.h"
void ASSERTIfDataMisaligned(const void* p, char* name)
{
	// on Windows, we see a 10-20% speed hit when accessing misaligned double precision floating point data
	// but on the Mac, we see 6000% - 7500% speed hit. (in the context of accessing the data in a matrix)

	// this will break if double ever changes size - but I'm not expecting that anytime soon - PCP

	if (((Uint32)p % 4) != 0) {
		if ((gDC.fpDG->prefsHand) &&((*gDC.fpDG->prefsHand)->fMaxNumberOfUndos == 16))  // little hook in
			DSTOP((kMark, "Misaligned double precision floating point access to %s - SERIOUS PERFORMANCE PENALTY!", name));
	}
}

#define GS_ASSERTDOUBLEALIGNMENT(p) ASSERTIfDataMisaligned(p, #p)

#else

#define GS_ASSERTDOUBLEALIGNMENT(p) DEBUG_DO_NOTHING

#endif




//**********************************************************************************
//**********************************************************************************
//************************   External Library Routines   ***************************
//**********************************************************************************
//**********************************************************************************


void GS_API MatrixToXMatrix(const TransformMatrix &source, TransformXMatrix &dest)
{

	GS_ASSERTDOUBLEALIGNMENT(&source);
	GS_ASSERTDOUBLEALIGNMENT(&dest);

	short						a;
	short						b;

	for (a = 0; a < 3; a++) {
		for (b = 0; b < 3; b++) {
			dest.mat[a][b] = source.mat[a][b];
		}
	}
	for (b = 0; b < 3; b++) {
		dest.mat[3][b] = source.mat[3][b];
	}
	for (b = 0; b < 3; b++) {
		dest.mat[b][3] = 0.0;
	}
	dest.mat[3][3] = 1.0;
}

TransformXMatrix MatrixToXMatrix(const TransformMatrix &source)
// XXX_JDW_MISC - this is inefficient. 
{

	GS_ASSERTDOUBLEALIGNMENT(&source);

	TransformXMatrix dest;

	dest.mat[0][0] = source.mat[0][0];
	dest.mat[0][1] = source.mat[0][1];
	dest.mat[0][2] = source.mat[0][2];
	dest.mat[1][0] = source.mat[1][0];
	dest.mat[1][1] = source.mat[1][1];
	dest.mat[1][2] = source.mat[1][2];
	dest.mat[2][0] = source.mat[2][0];
	dest.mat[2][1] = source.mat[2][1];
	dest.mat[2][2] = source.mat[2][2];	
	
	dest.mat[3][0] = source.mat[3][0];
	dest.mat[3][1] = source.mat[3][1];
	dest.mat[3][2] = source.mat[3][2];

	dest.mat[0][3] = dest.mat[1][3] = dest.mat[2][3] = 0.0;
	dest.mat[3][3] = 1.0;

	return dest;
}


void GS_API XMatrixToMatrix(const TransformXMatrix &source, TransformMatrix &dest)
{
	GS_ASSERTDOUBLEALIGNMENT(&source);
	GS_ASSERTDOUBLEALIGNMENT(&dest);

	short						a;
	short						b;

	for (a = 0; a < 3; a++) {
		for (b = 0; b < 3; b++) {
			dest.mat[a][b] = source.mat[a][b];
		}
	}
	for (b = 0; b < 3; b++) {
		dest.mat[3][b] = source.mat[3][b];
	}
}

TransformMatrix XMatrixToMatrix(const TransformXMatrix &source)
{
	GS_ASSERTDOUBLEALIGNMENT(&source);

	TransformMatrix dest;

	dest.mat[0][0] = source.mat[0][0];
	dest.mat[0][1] = source.mat[0][1];
	dest.mat[0][2] = source.mat[0][2];
	dest.mat[1][0] = source.mat[1][0];
	dest.mat[1][1] = source.mat[1][1];
	dest.mat[1][2] = source.mat[1][2];
	dest.mat[2][0] = source.mat[2][0];
	dest.mat[2][1] = source.mat[2][1];
	dest.mat[2][2] = source.mat[2][2];

	dest.mat[3][0] = source.mat[3][0];
	dest.mat[3][1] = source.mat[3][1];
	dest.mat[3][2] = source.mat[3][2];

	return dest;
}

#if GS_SDK_VW8_COMPATIBLE
Boolean GS_API XMatrix2Matrix(const TransformXMatrix& source, TransformMatrix& dest)
//
// Same as XMatrixToMatrix, but returns true if the matrix could be converted, 
// false if overflow. If false, the destination matrix is set to the identity 
// matrix. 
//
// Created by John Williams, 3/5/99
{
	GS_ASSERTDOUBLEALIGNMENT(&source);
	GS_ASSERTDOUBLEALIGNMENT(&dest);

	short						a;
	short						b;

	for (a = 0; a < 3; a++) {
		for (b = 0; b < 3; b++) {
			dest.mat[a][b] = source.mat[a][b];
		}
	}


	return true;
}
#endif // GS_SDK_VW8_COMPATIBLE
//////////////////////////////////////////////////
static bool operator==(const TransformMatrix& matrix1, const TransformMatrix& matrix2)
//
// Simple comparison between two matrices, I haven't
// put it in the header because we haven't needed it
// before.
//
{
	GS_ASSERTDOUBLEALIGNMENT(&matrix1);
	GS_ASSERTDOUBLEALIGNMENT(&matrix2);

	return ( matrix1.v2.offset == matrix2.v2.offset
			&& matrix1.v2.i == matrix2.v2.i
			&& matrix1.v2.j == matrix2.v2.j
			&& matrix1.v2.k == matrix2.v2.k );
}

#if BUG
//////////////////////////////////////////////////
void BugVerifyTransformMatrix(const TransformMatrix& matrix)
//
// This debugging function is to be called to test
// that a transformation matrix is in fact a valid
// linear transformation matrix, by our rules.  That
// means that upper 3x3 section is orthogonal, and the
// offset part contains valid coordinate values.
//
{
	static bool oldMatch = false;
	static TransformMatrix oldMatchMatrix;
	if ( !oldMatch || !(matrix == oldMatchMatrix) ) {
		ASSERTN(kAndrewB, matrix.IsOrthogonal());
		ASSERTN(kAndrewB, matrix.v1.xOff >= -kMaxLegalWorldCoord && matrix.v1.xOff <= kMaxLegalWorldCoord);
		ASSERTN(kAndrewB, matrix.v1.yOff >= -kMaxLegalWorldCoord && matrix.v1.yOff <= kMaxLegalWorldCoord);
		ASSERTN(kAndrewB, matrix.v1.zOff >= -kMaxLegalWorldCoord && matrix.v1.zOff <= kMaxLegalWorldCoord);
	}
}
#endif // BUG

//**********************************************************************************
//******************************  XFMatrix Routines  *******************************
//**********************************************************************************


void GS_API XMatrixMultiply(const TransformXMatrix &mat1, const TransformXMatrix &mat2, TransformXMatrix &dest)
{
	GS_ASSERTDOUBLEALIGNMENT(&mat1);
	GS_ASSERTDOUBLEALIGNMENT(&mat2);
	GS_ASSERTDOUBLEALIGNMENT(&dest);

	TransformXMatrix returnMat;

	returnMat.mat[0][0] = mat2.mat[0][0]*mat1.mat[0][0]+mat2.mat[1][0]*mat1.mat[0][1]+mat2.mat[2][0]*mat1.mat[0][2]+mat2.mat[3][0]*mat1.mat[0][3];
	returnMat.mat[0][1] = mat2.mat[0][1]*mat1.mat[0][0]+mat2.mat[1][1]*mat1.mat[0][1]+mat2.mat[2][1]*mat1.mat[0][2]+mat2.mat[3][1]*mat1.mat[0][3];
	returnMat.mat[0][2] = mat2.mat[0][2]*mat1.mat[0][0]+mat2.mat[1][2]*mat1.mat[0][1]+mat2.mat[2][2]*mat1.mat[0][2]+mat2.mat[3][2]*mat1.mat[0][3];
	returnMat.mat[0][3] = mat2.mat[0][3]*mat1.mat[0][0]+mat2.mat[1][3]*mat1.mat[0][1]+mat2.mat[2][3]*mat1.mat[0][2]+mat2.mat[3][3]*mat1.mat[0][3];
	returnMat.mat[1][0] = mat2.mat[0][0]*mat1.mat[1][0]+mat2.mat[1][0]*mat1.mat[1][1]+mat2.mat[2][0]*mat1.mat[1][2]+mat2.mat[3][0]*mat1.mat[1][3];
	returnMat.mat[1][1] = mat2.mat[0][1]*mat1.mat[1][0]+mat2.mat[1][1]*mat1.mat[1][1]+mat2.mat[2][1]*mat1.mat[1][2]+mat2.mat[3][1]*mat1.mat[1][3];
	returnMat.mat[1][2] = mat2.mat[0][2]*mat1.mat[1][0]+mat2.mat[1][2]*mat1.mat[1][1]+mat2.mat[2][2]*mat1.mat[1][2]+mat2.mat[3][2]*mat1.mat[1][3];
	returnMat.mat[1][3] = mat2.mat[0][3]*mat1.mat[1][0]+mat2.mat[1][3]*mat1.mat[1][1]+mat2.mat[2][3]*mat1.mat[1][2]+mat2.mat[3][3]*mat1.mat[1][3];
	returnMat.mat[2][0] = mat2.mat[0][0]*mat1.mat[2][0]+mat2.mat[1][0]*mat1.mat[2][1]+mat2.mat[2][0]*mat1.mat[2][2]+mat2.mat[3][0]*mat1.mat[2][3];
	returnMat.mat[2][1] = mat2.mat[0][1]*mat1.mat[2][0]+mat2.mat[1][1]*mat1.mat[2][1]+mat2.mat[2][1]*mat1.mat[2][2]+mat2.mat[3][1]*mat1.mat[2][3];
	returnMat.mat[2][2] = mat2.mat[0][2]*mat1.mat[2][0]+mat2.mat[1][2]*mat1.mat[2][1]+mat2.mat[2][2]*mat1.mat[2][2]+mat2.mat[3][2]*mat1.mat[2][3];
	returnMat.mat[2][3] = mat2.mat[0][3]*mat1.mat[2][0]+mat2.mat[1][3]*mat1.mat[2][1]+mat2.mat[2][3]*mat1.mat[2][2]+mat2.mat[3][3]*mat1.mat[2][3];
	returnMat.mat[3][0] = mat2.mat[0][0]*mat1.mat[3][0]+mat2.mat[1][0]*mat1.mat[3][1]+mat2.mat[2][0]*mat1.mat[3][2]+mat2.mat[3][0]*mat1.mat[3][3];
	returnMat.mat[3][1] = mat2.mat[0][1]*mat1.mat[3][0]+mat2.mat[1][1]*mat1.mat[3][1]+mat2.mat[2][1]*mat1.mat[3][2]+mat2.mat[3][1]*mat1.mat[3][3];
	returnMat.mat[3][2] = mat2.mat[0][2]*mat1.mat[3][0]+mat2.mat[1][2]*mat1.mat[3][1]+mat2.mat[2][2]*mat1.mat[3][2]+mat2.mat[3][2]*mat1.mat[3][3];
	returnMat.mat[3][3] = mat2.mat[0][3]*mat1.mat[3][0]+mat2.mat[1][3]*mat1.mat[3][1]+mat2.mat[2][3]*mat1.mat[3][2]+mat2.mat[3][3]*mat1.mat[3][3];

	dest = returnMat;
}

TransformXMatrix XMatrixMultiply(const TransformXMatrix &m1, const TransformXMatrix &m2)
{
	GS_ASSERTDOUBLEALIGNMENT(&m1);
	GS_ASSERTDOUBLEALIGNMENT(&m2);

	#define M1 m1.mat
	#define M2 m2.mat

	TransformXMatrix returnMat;

	returnMat.mat[0][0] = M2[0][0] * M1[0][0] + M2[1][0] * M1[0][1] + M2[2][0] * M1[0][2] + M2[3][0] * M1[0][3];
	returnMat.mat[0][1] = M2[0][1] * M1[0][0] + M2[1][1] * M1[0][1] + M2[2][1] * M1[0][2] + M2[3][1] * M1[0][3];
	returnMat.mat[0][2] = M2[0][2] * M1[0][0] + M2[1][2] * M1[0][1] + M2[2][2] * M1[0][2] + M2[3][2] * M1[0][3];
	returnMat.mat[0][3] = M2[0][3] * M1[0][0] + M2[1][3] * M1[0][1] + M2[2][3] * M1[0][2] + M2[3][3] * M1[0][3];
	returnMat.mat[1][0] = M2[0][0] * M1[1][0] + M2[1][0] * M1[1][1] + M2[2][0] * M1[1][2] + M2[3][0] * M1[1][3];
	returnMat.mat[1][1] = M2[0][1] * M1[1][0] + M2[1][1] * M1[1][1] + M2[2][1] * M1[1][2] + M2[3][1] * M1[1][3];
	returnMat.mat[1][2] = M2[0][2] * M1[1][0] + M2[1][2] * M1[1][1] + M2[2][2] * M1[1][2] + M2[3][2] * M1[1][3];
	returnMat.mat[1][3] = M2[0][3] * M1[1][0] + M2[1][3] * M1[1][1] + M2[2][3] * M1[1][2] + M2[3][3] * M1[1][3];
	returnMat.mat[2][0] = M2[0][0] * M1[2][0] + M2[1][0] * M1[2][1] + M2[2][0] * M1[2][2] + M2[3][0] * M1[2][3];
	returnMat.mat[2][1] = M2[0][1] * M1[2][0] + M2[1][1] * M1[2][1] + M2[2][1] * M1[2][2] + M2[3][1] * M1[2][3];
	returnMat.mat[2][2] = M2[0][2] * M1[2][0] + M2[1][2] * M1[2][1] + M2[2][2] * M1[2][2] + M2[3][2] * M1[2][3];
	returnMat.mat[2][3] = M2[0][3] * M1[2][0] + M2[1][3] * M1[2][1] + M2[2][3] * M1[2][2] + M2[3][3] * M1[2][3];
	returnMat.mat[3][0] = M2[0][0] * M1[3][0] + M2[1][0] * M1[3][1] + M2[2][0] * M1[3][2] + M2[3][0] * M1[3][3];
	returnMat.mat[3][1] = M2[0][1] * M1[3][0] + M2[1][1] * M1[3][1] + M2[2][1] * M1[3][2] + M2[3][1] * M1[3][3];
	returnMat.mat[3][2] = M2[0][2] * M1[3][0] + M2[1][2] * M1[3][1] + M2[2][2] * M1[3][2] + M2[3][2] * M1[3][3];
	returnMat.mat[3][3] = M2[0][3] * M1[3][0] + M2[1][3] * M1[3][1] + M2[2][3] * M1[3][2] + M2[3][3] * M1[3][3];

	#undef M1
	#undef M2

	return returnMat;
}


void GS_API SetAxisRotationXMatrix(MajorAxisSpec axis, double_param degrees, TransformXMatrix &mat)

{
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	double_gs					myCos;
	double_gs					mySin;
	double_gs					radians;

	mat.SetToIdentity();
	radians = degrees * kRadiansPerDegree;

	////VW901 fix, bug#19245///////////////////////////////////////
	mySin = WorldCoordsAreNearlyEqual(Abs(sin(radians)), 0)? 0.0 : sin(radians);//sin(radians);
	myCos = WorldCoordsAreNearlyEqual(Abs(cos(radians)), 0)? 0.0 : cos(radians);//cos(radians);
	/////////////////////////////////////////////////////////////

	switch (axis) {
		case kXAxis: {
			mat.mat[0][0] = 1.0;
			mat.mat[1][1] = myCos;
			mat.mat[1][2] = mySin;
			mat.mat[2][1] = -mySin;
			mat.mat[2][2] = myCos;
			break;
		}
		case kYAxis: {
			mat.mat[2][0] = mySin;
			mat.mat[2][2] = myCos;
			mat.mat[0][0] = myCos;
			mat.mat[0][2] = -mySin;
			mat.mat[1][1] = 1.0;
			break;
		}
		case kZAxis: {
			mat.mat[0][0] = myCos;
			mat.mat[0][1] = mySin;
			mat.mat[1][0] = -mySin;
			mat.mat[1][1] = myCos;
			mat.mat[2][2] = 1.0;
			break;
		}
	}
}



void GS_API SetVectorRotationXMatrix(const Vector &axis, double_param degrees, TransformXMatrix &mat)
{
	GS_ASSERTDOUBLEALIGNMENT(&mat);
	GS_ASSERTDOUBLEALIGNMENT(&axis);

	double_gs					myCos;
	double_gs					mySin;
	double_gs					myt;

	// this algorithm assumes that axis is already normalized
	#ifdef _MINICAD_
	#ifdef BUG
//	if (Abs((axis.Magnitude() - 1.0)) > 0.0001)
//		DSTOP((kPaul, brief, "NON-Normal vector passed to SetVectorRotationXMatrix!!!"));
	ASSERTN(kMark, axis.IsNormalized());
	#endif
	#endif

	mat.SetToIdentity();
	if (degrees != 0.0) {
		double_gs radians = degrees * kRadiansPerDegree;
		mySin = sin(radians);
		myCos = cos(radians);
		myt = 1-myCos;

		mat.mat[0][0] = myt*axis.x*axis.x+myCos;
		mat.mat[0][1] = myt*axis.x*axis.y+mySin*axis.z;
		mat.mat[0][2] = myt*axis.x*axis.z-mySin*axis.y;
		mat.mat[1][0] = myt*axis.x*axis.y-mySin*axis.z;
		mat.mat[1][1] = myt*axis.y*axis.y+myCos;
		mat.mat[1][2] = myt*axis.y*axis.z+mySin*axis.x;
		mat.mat[2][0] = myt*axis.x*axis.z+mySin*axis.y;
		mat.mat[2][1] = myt*axis.y*axis.z-mySin*axis.x;
		mat.mat[2][2] = myt*axis.z*axis.z+myCos;
	}
}


void GS_API MakeXMatrixOrthogonal(TransformXMatrix &mat)
{
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	Vector						ortho1;
	Vector						ortho2;
	Vector						ortho3;
	Vector						row1;
	Vector						row2;
	Vector						row3;
	Vector temp1, temp2;


	row1.x = mat.mat[0][0];
	row1.y = mat.mat[0][1];
	row1.z = mat.mat[0][2];
	row2.x = mat.mat[1][0];
	row2.y = mat.mat[1][1];
	row2.z = mat.mat[1][2];
	row3.x = mat.mat[2][0];
	row3.y = mat.mat[2][1];
	row3.z = mat.mat[2][2];
	
	ortho1 = row1.Normal();
	ortho2 = (row2-(DotProduct(row2, ortho1) * ortho1)).Normal();
	temp1 = DotProduct(row3, ortho1) * ortho1;
	temp2 = DotProduct(row3, ortho2) * ortho2;
	ortho3 = (row3-(temp1 + temp2)).Normal();

	mat.mat[0][0] = ortho1.x;
	mat.mat[0][1] = ortho1.y;
	mat.mat[0][2] = ortho1.z;
	mat.mat[1][0] = ortho2.x;
	mat.mat[1][1] = ortho2.y;
	mat.mat[1][2] = ortho2.z;
	mat.mat[2][0] = ortho3.x;
	mat.mat[2][1] = ortho3.y;
	mat.mat[2][2] = ortho3.z;
}


#undef paulsdebug

#ifdef paulsdebug
Boolean CheckIdentity(const TransformXMatrix &m)
{
	GS_ASSERTDOUBLEALIGNMENT(&m);

	const double_gs				limit = 1.0e-7;
	short						i;
	short						j;
	double_gs					thisElem;


	DMSG((kEveryone, "Should be identity:\n"));
	DMSG((kEveryone, "%8.4lf    %8.4lf    %8.4lf    %8.4lf\n", m.mat[0][0], m.mat[0][1], m.mat[0][2], m.mat[0][3]));
	DMSG((kEveryone, "%8.4lf    %8.4lf    %8.4lf    %8.4lf\n", m.mat[1][0], m.mat[1][1], m.mat[1][2], m.mat[1][3]));
	DMSG((kEveryone, "%8.4lf    %8.4lf    %8.4lf    %8.4lf\n", m.mat[2][0], m.mat[2][1], m.mat[2][2], m.mat[2][3]));
	DMSG((kEveryone, "%8.4lf    %8.4lf    %8.4lf    %8.4lf\n", m.mat[3][0], m.mat[3][1], m.mat[3][2], m.mat[3][3]));




	
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (i == j) {
				thisElem = Abs(m.mat[i][j]-1.0);
				if (thisElem > limit)  {
					DMSG((kEveryone, " element %d, %d is out of tolerance by %lf\n", i, j, thisElem));
					return false;
				}
			}
			else {
				thisElem = Abs(m.mat[i][j]);
				if (thisElem > limit) {
					DMSG((kEveryone, " element %d, %d is out of tolerance by %lf\n", i, j, thisElem));
					return false;
				}
			}
		}
	}
	return true;
}
#endif



static void Invert4by4_ByeBye(void) {
#ifdef BUG
	DMSG((kEveryone, "Matrix Singular\n"));
#endif
}

void GS_API InvertXMatrix(const TransformXMatrix &source, TransformXMatrix &dest)
{
	GS_ASSERTDOUBLEALIGNMENT(&source);
	GS_ASSERTDOUBLEALIGNMENT(&dest);

	TransformXMatrix			a;
	double_gs					det;
	double_gs					temp;
	double_gs					pos;
	double_gs					neg;
	double_gs					mag;

	a = source;
	pos = 0.0;
	neg = 0.0;
	
	#if 0
	temp = a.mat[0][0]*a.mat[1][1]*a.mat[2][2];

	if (temp >= 0) 
		pos = pos+temp;
	else 
		neg = neg+temp;
	
	temp = a.mat[0][1]*a.mat[1][2]*a.mat[2][0];

	if (temp >= 0) 
		pos = pos+temp;
	else 
		neg = neg+temp;
	
	temp = a.mat[0][2]*a.mat[1][0]*a.mat[2][1];
	
	if (temp >= 0) 
		pos = pos+temp;
	else 
		neg = neg+temp;

	temp = -(a.mat[2][0]*a.mat[1][1]*a.mat[0][2]);
	
	if (temp >= 0) 
		pos = pos+temp;
	else 
		neg = neg+temp;

	temp = -(a.mat[2][1]*a.mat[1][2]*a.mat[0][0]);
	
	if (temp >= 0) 
		pos = pos+temp;
	else 
		neg = neg+temp;

	temp = -(a.mat[2][2]*a.mat[1][0]*a.mat[0][1]);
	
	if (temp >= 0) 
		pos = pos+temp;
	else 
		neg = neg+temp;
	
	#else
	
	temp = a.mat[0][0]*a.mat[1][1]*a.mat[2][2];		(temp >= 0 ? pos : neg) += temp;
	temp = a.mat[0][1]*a.mat[1][2]*a.mat[2][0];		(temp >= 0 ? pos : neg) += temp;
	temp = a.mat[0][2]*a.mat[1][0]*a.mat[2][1];		(temp >= 0 ? pos : neg) += temp;
	temp = -(a.mat[2][0]*a.mat[1][1]*a.mat[0][2]);	(temp >= 0 ? pos : neg) += temp;
	temp = -(a.mat[2][1]*a.mat[1][2]*a.mat[0][0]);	(temp >= 0 ? pos : neg) += temp;
	temp = -(a.mat[2][2]*a.mat[1][0]*a.mat[0][1]);	(temp >= 0 ? pos : neg) += temp;

	#endif
	
	det = pos+neg;
	mag = pos-neg;
	
	if (mag == 0.0) {
		Invert4by4_ByeBye();
		return;
	}
	else {
		temp = det/mag;
		if (DoubleIsNearlyZero(temp)) { 
			Invert4by4_ByeBye();
			return;
		}
	}
	
	dest.mat[0][0] = (a.mat[1][1]*a.mat[2][2]-a.mat[2][1]*a.mat[1][2])/det;
	dest.mat[0][1] = -((a.mat[0][1]*a.mat[2][2]-a.mat[2][1]*a.mat[0][2])/det);
	dest.mat[0][2] = (a.mat[0][1]*a.mat[1][2]-a.mat[1][1]*a.mat[0][2])/det;
	dest.mat[1][0] = -((a.mat[1][0]*a.mat[2][2]-a.mat[2][0]*a.mat[1][2])/det);
	dest.mat[1][1] = (a.mat[0][0]*a.mat[2][2]-a.mat[2][0]*a.mat[0][2])/det;
	dest.mat[1][2] = -((a.mat[0][0]*a.mat[1][2]-a.mat[1][0]*a.mat[0][2])/det);
	dest.mat[2][0] = (a.mat[1][0]*a.mat[2][1]-a.mat[2][0]*a.mat[1][1])/det;
	dest.mat[2][1] = -((a.mat[0][0]*a.mat[2][1]-a.mat[2][0]*a.mat[0][1])/det);
	dest.mat[2][2] = (a.mat[0][0]*a.mat[1][1]-a.mat[1][0]*a.mat[0][1])/det;
	dest.mat[3][0] = -(a.mat[3][0]*dest.mat[0][0]+a.mat[3][1]*dest.mat[1][0]+a.mat[3][2]*dest.mat[2][0]);
	dest.mat[3][1] = -(a.mat[3][0]*dest.mat[0][1]+a.mat[3][1]*dest.mat[1][1]+a.mat[3][2]*dest.mat[2][1]);
	dest.mat[3][2] = -(a.mat[3][0]*dest.mat[0][2]+a.mat[3][1]*dest.mat[1][2]+a.mat[3][2]*dest.mat[2][2]);
	dest.mat[0][3] = 0.0;
	dest.mat[1][3] = 0.0;
	dest.mat[2][3] = 0.0;
	dest.mat[3][3] = 1.0;
	
#ifdef paulsdebug
	{
		TransformXMatrix c;
		XMatrixMultiply(a, dest, c);
		if (!CheckIdentity(c)) {
			DMSG((kEveryone, "Invert4by4 FAILED!!!\n"));
		}
	}
#endif
}

void GS_API AssignVectorsToXMatrix(const Vector &aVec, const Vector &bVec, const Vector &cVec, TransformXMatrix &mat)
{
	GS_ASSERTDOUBLEALIGNMENT(&aVec);
	GS_ASSERTDOUBLEALIGNMENT(&bVec);
	GS_ASSERTDOUBLEALIGNMENT(&cVec);
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	mat.mat[0][0] = aVec.x;
	mat.mat[1][0] = aVec.y;
	mat.mat[2][0] = aVec.z;

	mat.mat[0][1] = bVec.x;
	mat.mat[1][1] = bVec.y;
	mat.mat[2][1] = bVec.z;

	mat.mat[0][2] = cVec.x;
	mat.mat[1][2] = cVec.y;
	mat.mat[2][2] = cVec.z;
}


// NEW MATRIX TRANSFORMS 3/3/97
// NOTE		- the *TransformN() routines define point and vector transformations in the mathematically
//			correct sense, which is opposite that used by MiniCad 5 and MiniCad 6 source code. Beware
//			when referring to code from older versions of MiniCad or MiniCad externals which have not
//			yet been converted to use the newer calls. See MCMatrix.h for a table of equivalent calls.

void GS_API XPointTransformN(const WorldPt3 &a, const TransformXMatrix &mat, WorldPt3 &b)
{	
	GS_ASSERTDOUBLEALIGNMENT(&a);
	GS_ASSERTDOUBLEALIGNMENT(&b);
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	// Linear algebra equivalent:
	// b = a MAT
	
	WorldPt3 d = a;

	b.x =	d.x * mat.mat[0][0] + d.y * mat.mat[1][0] + d.z * mat.mat[2][0] + mat.mat[3][0];
	b.y =	d.x * mat.mat[0][1] + d.y * mat.mat[1][1] + d.z * mat.mat[2][1] + mat.mat[3][1];
	b.z =	d.x * mat.mat[0][2] + d.y * mat.mat[1][2] + d.z * mat.mat[2][2] + mat.mat[3][2];
}

void GS_API InverseXPointTransformN(const WorldPt3 &a, const TransformXMatrix &mat, WorldPt3 &b)
{
	GS_ASSERTDOUBLEALIGNMENT(&a);
	GS_ASSERTDOUBLEALIGNMENT(&b);
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	// Linear algebra equivalent:
	// b = a MAT^{-1}

	WorldPt3				dOffset;

	dOffset.x = a.x-mat.mat[3][0];
	dOffset.y = a.y-mat.mat[3][1];
	dOffset.z = a.z-mat.mat[3][2];
	
	b.x =	dOffset.x * mat.mat[0][0] + dOffset.y * mat.mat[0][1] + dOffset.z * mat.mat[0][2];
	b.y =	dOffset.x * mat.mat[1][0] + dOffset.y * mat.mat[1][1] + dOffset.z * mat.mat[1][2];
	b.z =	dOffset.x * mat.mat[2][0] + dOffset.y * mat.mat[2][1] + dOffset.z * mat.mat[2][2];
}

WorldPt3 GS_API InverseXPointTransformN(const WorldPt3 &a, const TransformXMatrix &mat)
{
	GS_ASSERTDOUBLEALIGNMENT(&a);
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	// Linear algebra equivalent:
	// b = a MAT^{-1}

	WorldPt3 dOffset(a.x - mat.mat[3][0], a.y - mat.mat[3][1], a.z - mat.mat[3][2]);
	
	return WorldPt3(dOffset.x * mat.mat[0][0] + dOffset.y * mat.mat[0][1] + dOffset.z * mat.mat[0][2],
					dOffset.x * mat.mat[1][0] + dOffset.y * mat.mat[1][1] + dOffset.z * mat.mat[1][2],
					dOffset.x * mat.mat[2][0] + dOffset.y * mat.mat[2][1] + dOffset.z * mat.mat[2][2]);
}

void GS_API VectorXTransformN(const Vector a, const TransformXMatrix &mat, Vector &b)
{
	GS_ASSERTDOUBLEALIGNMENT(&b);
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	// Linear algebra equivalent:
	// b = a MAT (ignoring the offset of the matrix)

	b.x = a.x * mat.mat[0][0] + a.y * mat.mat[1][0] + a.z * mat.mat[2][0];
	b.y = a.x * mat.mat[0][1] + a.y * mat.mat[1][1] + a.z * mat.mat[2][1];
	b.z = a.x * mat.mat[0][2] + a.y * mat.mat[1][2] + a.z * mat.mat[2][2];
}

void GS_API InverseVectorXTransformN(const Vector a, const TransformXMatrix &mat, Vector &b) 
{
	GS_ASSERTDOUBLEALIGNMENT(&b);
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	// Linear algebra equivalent:
	// b = a MAT^{-1} (ignoring the offset of the matrix)

	b.x = a.x * mat.mat[0][0] + a.y * mat.mat[0][1] + a.z * mat.mat[0][2];
	b.y = a.x * mat.mat[1][0] + a.y * mat.mat[1][1] + a.z * mat.mat[1][2];
	b.z = a.x * mat.mat[2][0] + a.y * mat.mat[2][1] + a.z * mat.mat[2][2];
}

void GS_API CubeTransformN(const WorldCube& in, const TransformMatrix& mat, WorldCube& out)
// Linear algebra equivalent:  b = a MAT for each point of the cube. Could be more efficient.
// JDW, 3/18/99
{
	GS_ASSERTDOUBLEALIGNMENT(&in);
	GS_ASSERTDOUBLEALIGNMENT(&out);
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	if (in.IsEmpty(eAssert)) {
		out = in;
	}
	else {
		WorldCube		c;
		#if 1 // ACB 9/18/99
		c.SetToPoint(in.Pointxyz() * mat);

		c.Unite(in.PointxyZ() * mat);
		c.Unite(in.PointxYz() * mat);
		c.Unite(in.PointxYZ() * mat);
		c.Unite(in.PointXyz() * mat);
		c.Unite(in.PointXyZ() * mat);
		c.Unite(in.PointXYz() * mat);
		c.Unite(in.PointXYZ() * mat);
		#else
		const WorldCoord&	Y = in.top;
		const WorldCoord&	y = in.bottom;
		const WorldCoord&	X = in.right;
		const WorldCoord&	x = in.left;
		const WorldCoord&	Z = in.front;
		const WorldCoord&	z = in.back;

		c.SetToPoint(WorldPt3(X,Y,Z) * mat);	

		c.Unite(WorldPt3(X,Y,z) * mat);
		c.Unite(WorldPt3(X,y,Z) * mat);
		c.Unite(WorldPt3(X,y,z) * mat);
		c.Unite(WorldPt3(x,Y,Z) * mat);
		c.Unite(WorldPt3(x,Y,z) * mat);
		c.Unite(WorldPt3(x,y,Z) * mat);
		c.Unite(WorldPt3(x,y,z) * mat);
		#endif

		out = c;
	}
}

//**********************************************************************************
//****************************  FracXFMatrix Routines  *****************************
//**********************************************************************************



void GS_API IdentityMatrix(TransformMatrix &mat)
{
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	for (Sint32 i = 0; i <= 3; i++)
		for (Sint32 a = 0; a <= 2; a++)
			mat.mat[i][a] = (a == i) ? 1.0 : 0.0;
}


////////////////////////////////////////////////////////////
const GS_API TransformMatrix& IdentityMatrix()
//
// This function returns a const reference to an identity
// matrix (a singleton).
//
{
	static bool setToIdentity = false;
	static TransformMatrix iMatrix; // static, so it lasts until shutdown
	if ( !setToIdentity ) {
		IdentityMatrix(iMatrix);
		setToIdentity = true;
	}
	return iMatrix;
}


// NOTE - these functions do NOT call FFracMul as that is less efficient on mainstream machines
// than calling FracMul directly

// NEW MATRIX TRANSFORMS 3/3/97
// See comment above.
// See MCMatrix.h for a table of equivalent calls.

//////////////////////////////////////////////////
inline void BasePointTransformN(const WorldPt3 &a, const TransformMatrix &mat, WorldPt3 &b)
//
// The base transformation code, so we can have
// one version that checks the matrix is a linear
// transformation, and one that doesn't.
//
{
	GS_ASSERTDOUBLEALIGNMENT(&a);
	GS_ASSERTDOUBLEALIGNMENT(&b);
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	// presumably this copy is done so a and b can be the same object; we could simply pass
	// a by value though.  In fact, because of aliasing (the possibility that mat and b are
	// overlapping), we really should probably compute into d and then assign to b at the
	// end.  I don't want to have to deal with testing this at the moment, though. -- ACB
	WorldPt3 d = a;

	b.x =	d.x * mat.v1.a00 + d.y * mat.v1.a10 + d.z * mat.v1.a20 + mat.v1.xOff;
	b.y =	d.x * mat.v1.a01 + d.y * mat.v1.a11 + d.z * mat.v1.a21 + mat.v1.yOff;
	b.z =	d.x * mat.v1.a02 + d.y * mat.v1.a12 + d.z * mat.v1.a22 + mat.v1.zOff;
}

//////////////////////////////////////////////////
void GS_API NonLinearPointTransformN(const WorldPt3 &a, const TransformMatrix &mat, WorldPt3 &b)
//
// This function should be used in place of
// PointTransformN when the transformation isn't
// necessarily a rotation plus offset, such as a
// scaling operation.  It skips the verification of
// linearity done in PointTransformN.
//
{
	GS_ASSERTDOUBLEALIGNMENT(&a);
	GS_ASSERTDOUBLEALIGNMENT(&b);
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	BasePointTransformN(a, mat, b);
}

//////////////////////////////////////////////////
void GS_API PointTransformN(const WorldPt3 &a, const TransformMatrix &mat, WorldPt3 &b)
//
// This function performs what is assumed to be a
// linear transformation on a and puts the result
// in b.
//
{
	GS_ASSERTDOUBLEALIGNMENT(&a);
	GS_ASSERTDOUBLEALIGNMENT(&b);
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	VerifyTransformMatrix(mat);

	BasePointTransformN(a, mat, b);
}

void GS_API InversePointTransformN(const WorldPt3 &a, const TransformMatrix &mat, WorldPt3 &b)
{
	GS_ASSERTDOUBLEALIGNMENT(&a);
	GS_ASSERTDOUBLEALIGNMENT(&b);
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	WorldPt3				dOffset;

	dOffset.x = a.x - mat.v1.xOff;
	dOffset.y = a.y - mat.v1.yOff;
	dOffset.z = a.z - mat.v1.zOff;
	b.x =	dOffset.x * mat.v1.a00 + dOffset.y * mat.v1.a01 + dOffset.z * mat.v1.a02;
	b.y =	dOffset.x * mat.v1.a10 + dOffset.y * mat.v1.a11 + dOffset.z * mat.v1.a12;
	b.z =	dOffset.x * mat.v1.a20 + dOffset.y * mat.v1.a21 + dOffset.z * mat.v1.a22;
}

void GS_API VectorTransformN(const Vector &a, const TransformMatrix &mat, Vector &b) 
{
	GS_ASSERTDOUBLEALIGNMENT(&a);
	GS_ASSERTDOUBLEALIGNMENT(&b);
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	Vector d = a;  // need this for VectorTransformN(v, t, v);
	
	b.x =	d.x * mat.v1.a00 + d.y * mat.v1.a10 + d.z * mat.v1.a20;
	b.y =	d.x * mat.v1.a01 + d.y * mat.v1.a11 + d.z * mat.v1.a21;
	b.z =	d.x * mat.v1.a02 + d.y * mat.v1.a12 + d.z * mat.v1.a22;
}

void GS_API InverseVectorTransformN(const Vector &a, const TransformMatrix &mat, Vector &b)
{
	GS_ASSERTDOUBLEALIGNMENT(&a);
	GS_ASSERTDOUBLEALIGNMENT(&b);
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	Vector d = a;  // need this for InverseVectorTransformN(v, t, v);
	
	b.x =	d.x * mat.v1.a00  +  d.y * mat.v1.a01  +  d.z * mat.v1.a02;
	b.y =	d.x * mat.v1.a10  +  d.y * mat.v1.a11  +  d.z * mat.v1.a12;
	b.z =	d.x * mat.v1.a20  +  d.y * mat.v1.a21  +  d.z * mat.v1.a22;
}


// 2D point transform routines

void InversePoint2DTransform(const WorldPt &a, const TransformMatrix &mat, WorldPt &b)
{
	GS_ASSERTDOUBLEALIGNMENT(&a);
	GS_ASSERTDOUBLEALIGNMENT(&b);
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	WorldPt						dOffset;

	dOffset.x = a.x-mat.v1.xOff;
	dOffset.y = a.y-mat.v1.yOff;
	b.x =	dOffset.x * mat.v1.a00+
			dOffset.y * mat.v1.a01;
	b.y =	dOffset.x * mat.v1.a10+
			dOffset.y * mat.v1.a11;

}
void InverseVector2DTransform(const WorldPt &a, const TransformMatrix &mat, WorldPt &b)
{
	GS_ASSERTDOUBLEALIGNMENT(&a);
	GS_ASSERTDOUBLEALIGNMENT(&b);
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	WorldPt d = a;  // need this for when a and b are the same variable

	b.x =	d.x * mat.v1.a00+
			d.y * mat.v1.a01;
	b.y =	d.x * mat.v1.a10+
			d.y * mat.v1.a11;

}

void PointTransformTo2D(const WorldPt3 &a, const TransformMatrix &mat, WorldPt &b)
{
	GS_ASSERTDOUBLEALIGNMENT(&a);
	GS_ASSERTDOUBLEALIGNMENT(&b);
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	WorldPt3	p = a;
	
	b.x = 	p.x * mat.v1.a00 +
			p.y * mat.v1.a10 +
			p.z * mat.v1.a20 +
			mat.v1.xOff;
	b.y = 	p.x * mat.v1.a01 +
			p.y * mat.v1.a11 +
			p.z * mat.v1.a21 +
			mat.v1.yOff;
}


TransformMatrix GS_API MatrixMultiply(const TransformMatrix &mat1, const TransformMatrix &mat2)
{
	GS_ASSERTDOUBLEALIGNMENT(&mat1);
	GS_ASSERTDOUBLEALIGNMENT(&mat2);

	TransformMatrix				matTemp;

	matTemp.v1.a00 =	mat2.v1.a00 * mat1.v1.a00 +
						mat2.v1.a10 * mat1.v1.a01 +
						mat2.v1.a20 * mat1.v1.a02;
	matTemp.v1.a01 =	mat2.v1.a01 * mat1.v1.a00 +
						mat2.v1.a11 * mat1.v1.a01 +
						mat2.v1.a21 * mat1.v1.a02;
	matTemp.v1.a02 =	mat2.v1.a02 * mat1.v1.a00 +
						mat2.v1.a12 * mat1.v1.a01 +
						mat2.v1.a22 * mat1.v1.a02;
	matTemp.v1.a10 =	mat2.v1.a00 * mat1.v1.a10 +
						mat2.v1.a10 * mat1.v1.a11 +
						mat2.v1.a20 * mat1.v1.a12;
	matTemp.v1.a11 =	mat2.v1.a01 * mat1.v1.a10 +
						mat2.v1.a11 * mat1.v1.a11 +
						mat2.v1.a21 * mat1.v1.a12;
	matTemp.v1.a12 =	mat2.v1.a02 * mat1.v1.a10 +
						mat2.v1.a12 * mat1.v1.a11 +
						mat2.v1.a22 * mat1.v1.a12;
	matTemp.v1.a20 =	mat2.v1.a00 * mat1.v1.a20 +
						mat2.v1.a10 * mat1.v1.a21 +
						mat2.v1.a20 * mat1.v1.a22;
	matTemp.v1.a21 =	mat2.v1.a01 * mat1.v1.a20 +
						mat2.v1.a11 * mat1.v1.a21 +
						mat2.v1.a21 * mat1.v1.a22;
	matTemp.v1.a22 =	mat2.v1.a02 * mat1.v1.a20 +
						mat2.v1.a12 * mat1.v1.a21 +
						mat2.v1.a22 * mat1.v1.a22;
	matTemp.v1.xOff =	mat1.v1.xOff * mat2.v1.a00 +
						mat1.v1.yOff * mat2.v1.a10 +
						mat1.v1.zOff * mat2.v1.a20 + mat2.v1.xOff;
	matTemp.v1.yOff =	mat1.v1.xOff * mat2.v1.a01 +
						mat1.v1.yOff * mat2.v1.a11 +
						mat1.v1.zOff * mat2.v1.a21 + mat2.v1.yOff;
	matTemp.v1.zOff =	mat1.v1.xOff * mat2.v1.a02 +
						mat1.v1.yOff * mat2.v1.a12 +
						mat1.v1.zOff * mat2.v1.a22 + mat2.v1.zOff;

	// fix VB-111889
	for ( short a = 0; a < 3; ++a )
	{
		for ( short b = 0; b < 3; ++b )
		{
			if ( WorldCoordsAreNearlyEqual( matTemp.mat[a][b] , 0.0 ) )
			{
				matTemp.mat[a][b] = 0.0;
			}
		}
	}

	return matTemp;
}



void GS_API MatrixMakeOrthogonal(TransformMatrix &mat)
{
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	Vector	row1(mat.v2.i);
	Vector	row2(mat.v2.j);
	Vector	row3(mat.v2.k);
	Vector	ortho1, ortho2, ortho3, temp1, temp2;

	ortho1	= row1.Normal();
	ortho2	= (row2 - (DotProduct(row2, ortho1) * ortho1)).Normal();
	temp1	= DotProduct(row3, ortho1) * ortho1;
	temp2	= DotProduct(row3, ortho2) * ortho2;
	ortho3	= (row3 - (temp1 + temp2)).Normal();

	mat.mat[0][0] = ortho1.x;	// XXX_JDW_MISC project seamonkey get rid of the damned _WorldPt3 nonsense which keeps code from being pretty.
	mat.mat[0][1] = ortho1.y;
	mat.mat[0][2] = ortho1.z;
	mat.mat[1][0] = ortho2.x;
	mat.mat[1][1] = ortho2.y;
	mat.mat[1][2] = ortho2.z;
	mat.mat[2][0] = ortho3.x;
	mat.mat[2][1] = ortho3.y;
	mat.mat[2][2] = ortho3.z;
}


void GS_API InvertMatrix(const TransformMatrix &source, TransformMatrix &dest)
{
	GS_ASSERTDOUBLEALIGNMENT(&source);
	GS_ASSERTDOUBLEALIGNMENT(&dest);

	TransformXMatrix					tempMat;

	MatrixToXMatrix(source, tempMat);
	InvertXMatrix(tempMat, tempMat);
	XMatrixToMatrix(tempMat, dest);
}



void GS_API SetAxisRotationMatrix(MajorAxisSpec axis, double_param degrees, TransformMatrix &mat)
{
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	TransformXMatrix					tmpMat;

	SetAxisRotationXMatrix(axis, degrees, tmpMat);
	XMatrixToMatrix(tmpMat, mat);
}


void GS_API SetAxisRotationMatrix(MajorAxisSpec axis, double_param degrees, const WorldPt3& center, TransformMatrix &mat)
{
	GS_ASSERTDOUBLEALIGNMENT(&center);
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	TransformXMatrix					tmpMat;
	TransformMatrix						tmpFrac;

	IdentityMatrix(tmpFrac);
	TranslateMatrix(tmpFrac, -center.x, -center.y, -center.z);

	SetAxisRotationXMatrix(axis, degrees, tmpMat);
	XMatrixToMatrix(tmpMat, mat);

	mat = MatrixMultiply(tmpFrac, mat);	
	TranslateMatrix(mat, center.x, center.y, center.z);
}


static Degrees AdjustDegreesToRange(Degrees in, Degrees low, Degrees high)
// Helper for GetAnglesFromMatrix
{
	Degrees out = in;

	if (out < low) {

		while (out < low)
			out += 360;
	}
	else {

		while (out > high)
			out -= 360;
	}

	return out;
}

void GS_API GetAnglesFromMatrix(const TransformMatrix &inMat, Degrees &outAboutXAxis, Degrees &outAboutYAxis, Degrees &outAboutZAxis)
//
// Created by EJKerr 
//
// Reference: http://www.flipcode.com/documents/matrfaq.html#Q37
//
// We assume the matrix m is composed by concatenating R(z)*R(y)*R(x)
// where x,y,z are the rotation angles (in radians) about the corresponding axes.
// (That's how we concat in MP_SetWorkingPlane(x, y, z, ax, ay, az))
//
// (cx = cos(x), etc.)
//
// R(z)=			R(y)=			R(x)
// cz	sz	0		cy	0	-sy		1	0	0
// -sz	cz	0		0	1	0		0	cx	sx
// 0	0	1		sy	0	cy		0	-sx	cx
//
// R(y)*R(x) =
// cy	sysx	-sycx
// 0	cx		-sx
// sy	-cysx	cycx
//
// R(z)*R(y)*R(x) =
// czcy		czsysx+szcx		-czsycx+szsx
// -szcy	-szsysx+czcx	szsycx+czsx
// sy		-cysx			cycx
//
// Therefore
// y = asin(m[2][0])
// cy = cos(y)
//
// if cy is non zero
//	x = asin(-m[2][1]/cy) or preferably atan2(-m[2][1]/cy, m[2][2]/cy)
//  z = atan2(-m[1][0]/cy, m[0][0]/cy)
//
// otherwise cy=0, therefore y will be either 90 or -90, making sy either 1 or -1 (which we can observe in m[2][0]).
//  (if sy=-1 we get very much the same solution as with sy=1)
//  assume sy=1, and simplifying the matrix, we get
//
// R(z)*R(y)*R(x) =
// (sy=1)							(sy=-1)							
// 0	czsx+szcx	-czcx+szsx		0	-czsx+szcx	czcx+szsx		
// 0	-szsx+czcx	szcx+czsx		0	szsx+czcx	-szcx+czsx		
// 1	0			0				-1	0			0				
//
// which is of the form
//
// R(z)*R(y)*R(x) =
// 0	A	B
// 0	-B	A
// 1	0	0
// where A = czsx+szcx, B = -czcx+szsx
// These two values can be considered to be the sin and cosine of a single rotation axis.
// (I think what this means is that you can get here with a pure x, or pure z rotation.)
// We can assume x angle is zero, and solve for a z angle.
//
// x = 0, (sx=0, cx=1)
// 
// R(z)*R(y)*R(x) =
// (sy=1)			(sy=-1)
// 0	sz	-cz		 0	sz	cz
// 0	cz	sz		 0	cz	-sz
// 1	0	0		 -1	0	0
//
//  z = atan2(m[0][1], m[1][1])
//
{
	Radians Rx, Ry, Rz;

	Ry = asin(inMat.v1.a20);			// Calculate Y-axis angle

	double cy = cos(Ry);

	if (Abs(cy) > 0.005) {
		// No Gimball lock
		Rx = atan2(-inMat.v1.a21/cy, inMat.v1.a22/cy);	// Get X-axis angle
		Rz = atan2(-inMat.v1.a10/cy, inMat.v1.a00/cy);	// Get Z-axis angle
	}
    else {
		// Gimball lock has occurred
		Rx = 0;										// Set X-axis angle to zero
		Rz = atan2(inMat.v1.a01, inMat.v1.a11);		// And calculate Z-axis angle
	}

	outAboutXAxis = Rx * kDegreesPerRadian;
	outAboutYAxis = Ry * kDegreesPerRadian;
	outAboutZAxis = Rz * kDegreesPerRadian;

	outAboutXAxis = AdjustDegreesToRange(outAboutXAxis, 0, 360);
	outAboutYAxis = AdjustDegreesToRange(outAboutYAxis, 0, 360);
	outAboutZAxis = AdjustDegreesToRange(outAboutZAxis, 0, 360);
}

// JAK 10/15/99 DOES NOT COMPILE...illegal override...the type Degrees does not agree with the .h file which has double_param.
//void GS_API SetVectorRotationMatrix(const Vector& axis, const Degrees degrees, TransformMatrix& mat)
void GS_API SetVectorRotationMatrix(const Vector& axis, double_param degrees, TransformMatrix& mat)
// XXX_JDW_MISC - change to radians (but preserve API)
{
	GS_ASSERTDOUBLEALIGNMENT(&axis);
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	double_gs		myCos;
	double_gs		mySin;
	double_gs		myt;

	// this algorithm assumes that axis is already normalized
	#ifdef _MINICAD_
	#ifdef BUG
//	if (Abs((axis.Magnitude() - 1.0)) > 0.0001) // XXX_JDW_MISC 
//		DSTOP((kPaul, brief, "NON-Normal vector passed to SetVectorRotationMatrix!!!"));
	ASSERTN(kMark, axis.IsNormalized());
	#endif
	#endif

	mat.SetToIdentity();
	if (degrees != 0.0) {
		double_gs radians = degrees * kRadiansPerDegree;
		mySin = sin(radians);
		myCos = cos(radians);
		myt = 1 - myCos;

		mat.mat[0][0] = myt * axis.x * axis.x + myCos;
		mat.mat[0][1] = myt * axis.x * axis.y + mySin * axis.z;
		mat.mat[0][2] = myt * axis.x * axis.z - mySin * axis.y;
		mat.mat[1][0] = myt * axis.x * axis.y - mySin * axis.z;
		mat.mat[1][1] = myt * axis.y * axis.y + myCos;
		mat.mat[1][2] = myt * axis.y * axis.z + mySin * axis.x;
		mat.mat[2][0] = myt * axis.x * axis.z + mySin * axis.y;
		mat.mat[2][1] = myt * axis.y * axis.z - mySin * axis.x;
		mat.mat[2][2] = myt * axis.z * axis.z + myCos;
	}
}


//-----------------------------------------------------------------------------
void GS_API Set2DAxisFlipMatrix(const MajorAxisSpec axis, const WorldPt& origin, TransformMatrix& tm)
{
	GS_ASSERTDOUBLEALIGNMENT(&origin);
	GS_ASSERTDOUBLEALIGNMENT(&tm);


	TransformMatrix offmat1, offmat2;
	IdentityMatrix(offmat1);
	IdentityMatrix(offmat2);
	IdentityMatrix(tm);
	// set the two translation matrices: one to Move Center of flip to the
	// origin,	and one to Move the Center back to original position
	TranslateMatrix(offmat1, -origin.x, -origin.y, 0L);
	TranslateMatrix(offmat2, origin.x, origin.y, 0L);
	// Set the flip matrix
	if (axis == kYAxis)
		tm.v1.a00 = -tm.v1.a00;
	else if (axis == kXAxis)
		tm.v1.a11 = -tm.v1.a11;
	// find the final flip matrix
	tm = MatrixMultiply(offmat1, tm);
	tm = MatrixMultiply(tm, offmat2);
}

#if 0	// on or before June 99
Boolean GS_API MakeVectorsOrthonormal(Vector &aVec, Vector &bVec, Vector &cVec, Boolean first)
{
	GS_ASSERTDOUBLEALIGNMENT(&aVec);
	GS_ASSERTDOUBLEALIGNMENT(&bVec);
	GS_ASSERTDOUBLEALIGNMENT(&cVec);

	aVec = Normal(aVec);
	bVec = Normal(bVec);
	if (Abs(DotProduct(aVec, bVec)) < 0.9999) {
		cVec = Normal(CrossProduct(aVec, bVec));
		if (first) 
			aVec = Normal(CrossProduct(bVec, cVec));
		else 
			bVec = Normal(CrossProduct(cVec, aVec));
		return true;
	}
	else
	
		return false;
}

#else

Boolean GS_API MakeVectorsOrthonormal(Vector &aVec, Vector &bVec, Vector &cVec, Boolean first)
{
	GS_ASSERTDOUBLEALIGNMENT(&aVec);
	GS_ASSERTDOUBLEALIGNMENT(&bVec);
	GS_ASSERTDOUBLEALIGNMENT(&cVec);
	
	bool inputNotZero = !aVec.IsZero() && !bVec.IsZero();
	
	
	if (inputNotZero) {
		
		aVec.Normalize();
		bVec.Normalize();
		if (Abs(DotProduct(aVec, bVec)) < 0.9999) {	// XXX_JDW_MISC 
			cVec = (CrossProduct(aVec, bVec)).Normal();
			if (first) 
				aVec = (CrossProduct(bVec, cVec)).Normal();
			else 
				bVec = (CrossProduct(cVec, aVec)).Normal();
			return true;
		}
		else
		
			return false;
	}
	else
		return false;
}

#endif


void GS_API GetVectorsFromMatrix(const TransformMatrix &mat, Vector &aVec, Vector &bVec, Vector &cVec)
{

	GS_ASSERTDOUBLEALIGNMENT(&aVec);
	GS_ASSERTDOUBLEALIGNMENT(&bVec);
	GS_ASSERTDOUBLEALIGNMENT(&cVec);
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	aVec.x = mat.v1.a00;
	aVec.y = mat.v1.a10;
	aVec.z = mat.v1.a20;

	bVec.x = mat.v1.a01;
	bVec.y = mat.v1.a11;
	bVec.z = mat.v1.a21;

	cVec.x = mat.v1.a02;
	cVec.y = mat.v1.a12;
	cVec.z = mat.v1.a22;

}



void GS_API AssignVectorsToMatrix(const Vector &aVec, const Vector &bVec, const Vector &cVec, TransformMatrix &mat)
{

	GS_ASSERTDOUBLEALIGNMENT(&aVec);
	GS_ASSERTDOUBLEALIGNMENT(&bVec);
	GS_ASSERTDOUBLEALIGNMENT(&cVec);
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	mat.v1.a00 = aVec.x;
	mat.v1.a10 = aVec.y;
	mat.v1.a20 = aVec.z;

	mat.v1.a01 = bVec.x;
	mat.v1.a11 = bVec.y;
	mat.v1.a21 = bVec.z;

	mat.v1.a02 = cVec.x;
	mat.v1.a12 = cVec.y;
	mat.v1.a22 = cVec.z;
}


void GS_API CreateMatrixFromAxis(const Axis &axis, TransformMatrix &mat)
{
	GS_ASSERTDOUBLEALIGNMENT(&axis);
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	TransformMatrix				transMatrix;

	IdentityMatrix(mat);
	AssignVectorsToMatrix(axis.i, axis.j, axis.k, mat);

	IdentityMatrix(transMatrix);
	TranslateMatrix(transMatrix, -axis.vertex.x, -axis.vertex.y, -axis.vertex.z);
	mat = MatrixMultiply(transMatrix, mat);
}


void GS_API CreateAxisFromMatrix(const TransformMatrix &mat, Axis &axis)
{
	GS_ASSERTDOUBLEALIGNMENT(&axis);
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	GetVectorsFromMatrix(mat, axis.i, axis.j, axis.k);
	InversePointTransformN(WorldPt3(0L, 0L, 0L), mat, axis.vertex);
}



void GS_API SetMatrixKI(const WorldPt3 &kDir, const WorldPt3 &iDir, TransformMatrix &mat)
{
	GS_ASSERTDOUBLEALIGNMENT(&kDir);
	GS_ASSERTDOUBLEALIGNMENT(&iDir);
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	Vector						iVec;
	Vector						jVec;
	Vector						kVec;

	kVec = WorldPt3(kDir);
	iVec = WorldPt3(iDir);

	if (MakeVectorsOrthonormal(kVec, iVec, jVec, false)) {
		AssignVectorsToMatrix(iVec, jVec, kVec, mat);
	}
}


void GS_API SetMatrixKJ(const WorldPt3 &kDir, const WorldPt3 &jDir, TransformMatrix &mat)
{
	GS_ASSERTDOUBLEALIGNMENT(&kDir);
	GS_ASSERTDOUBLEALIGNMENT(&jDir);
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	Vector						iVec;
	Vector						jVec;
	Vector						kVec;

	kVec = WorldPt3(kDir);
	jVec = WorldPt3(jDir);
	if (MakeVectorsOrthonormal(jVec, kVec, iVec, true)) {
		AssignVectorsToMatrix(iVec, jVec, kVec, mat);
	}
	else
		DSTOP((kAndrewB, "Unable to make vectors orthonormal!"));
}


void GS_API SetMatrixIJ(const WorldPt3 &kDir, const WorldPt3 &iDir, TransformMatrix &mat)
{
	GS_ASSERTDOUBLEALIGNMENT(&kDir);
	GS_ASSERTDOUBLEALIGNMENT(&iDir);
	GS_ASSERTDOUBLEALIGNMENT(&mat);

	Vector						iVec;
	Vector						jVec;
	Vector						kVec;

	iVec = WorldPt3(kDir);
	jVec = WorldPt3(iDir);
	if (MakeVectorsOrthonormal(iVec, jVec, kVec, false)) {
		AssignVectorsToMatrix(iVec, jVec, kVec, mat);
	}
}


void GS_API TranslateMatrix(TransformMatrix &f, WorldCoord x, WorldCoord y, WorldCoord z)
{
	GS_ASSERTDOUBLEALIGNMENT(&f);

	f.v1.xOff += x;
	f.v1.yOff += y;
	f.v1.zOff += z;
}


void GS_API SetMultiAxisSpinMatrix(	TransformMatrix &mat,
						MajorAxisSpec firstAxis,
						MajorAxisSpec secondAxis,
						MajorAxisSpec thirdAxis,
						double_param firstAngleDegrees,
						double_param secondAngleDegrees,
						double_param thirdAngleDegrees,
						const WorldPt3 &center,
						Boolean fromzero)
{

	GS_ASSERTDOUBLEALIGNMENT(&mat);
	GS_ASSERTDOUBLEALIGNMENT(&center);

	TransformMatrix				tmpFrac;
	TransformMatrix				tmpFrac2;
	TransformXMatrix			tmpMat;

	IdentityMatrix(tmpFrac2);
	CAST(WorldPt3, tmpFrac2.v2.offset) = -center;
	SetAxisRotationXMatrix(firstAxis, firstAngleDegrees, tmpMat);
	XMatrixToMatrix(tmpMat, tmpFrac);
	tmpFrac = MatrixMultiply(tmpFrac2, tmpFrac);
	if (secondAxis != 0) {
		SetAxisRotationXMatrix(secondAxis, secondAngleDegrees, tmpMat);
		XMatrixToMatrix(tmpMat, tmpFrac2);
		tmpFrac = MatrixMultiply(tmpFrac, tmpFrac2);
	}
	if (thirdAxis != 0) {
		SetAxisRotationXMatrix(thirdAxis, thirdAngleDegrees, tmpMat);
		XMatrixToMatrix(tmpMat, tmpFrac2);
		tmpFrac = MatrixMultiply(tmpFrac, tmpFrac2);
	}
	IdentityMatrix(tmpFrac2);
	CAST(WorldPt3, tmpFrac2.v2.offset) = center;
	tmpFrac = MatrixMultiply(tmpFrac, tmpFrac2);
	mat = fromzero ? tmpFrac : MatrixMultiply(mat, tmpFrac);
}

void GS_API RotateMatrix2D(double_param degrees, const WorldPt& center, TransformMatrix &mat)
{
	GS_ASSERTDOUBLEALIGNMENT(&mat);
	GS_ASSERTDOUBLEALIGNMENT(&center);

	WorldPt3 rotCenter(center, 0L);
	TransformMatrix rotMat;
	SetAxisRotationMatrix(kZAxis, degrees, rotCenter, rotMat);
	mat = MatrixMultiply(mat, rotMat);
}

// This fucntion calculates a transformation matrix (non afine)
// that transforms the first triangle (inPt1, inPt2, inPt3) into (transfPt1, transfPt2, transfPt3) triangle
bool GS_API CalcTransformFromOneTriToAnother(TransformMatrix& outMatrix,
											const WorldPt3& inPt1, const WorldPt3& inPt2, const WorldPt3& inPt3,
											const WorldPt3& transfPt1, const WorldPt3& transfPt2, const WorldPt3& transfPt3)
{
	class CSystemOfLinearEq
	{
	public:
		CSystemOfLinearEq()
		{
			m_arrB[0] = m_arrB[1] = m_arrB[2] = m_arrB[3] = 0;
			for(Sint32 i=0; i<4*4; i++)
				m_A[i] = 0;
		}
		
		void Reset()
		{
			m_arrB[0] = m_arrB[1] = m_arrB[2] = m_arrB[3] = 0;
			for(Sint32 i=0; i<4*4; i++)
				m_A[i] = 0;
		}

		void SetEquation(Uint32 _iEqNumber, const double *_pdEqCoefficients, double _dEqResult )
		{
			ASSERTN( kVStanev, _iEqNumber < 4);

			m_A[4*_iEqNumber+0]	= _pdEqCoefficients[0];
			m_A[4*_iEqNumber+1]	= _pdEqCoefficients[1];
			m_A[4*_iEqNumber+2]	= _pdEqCoefficients[2];
			m_A[4*_iEqNumber+3]	= _pdEqCoefficients[3];

			m_arrB[_iEqNumber] = _dEqResult;
		}

		bool FindLUDecompSolution( double *_pSolution, double dZeroEpsilon )
		{
			ASSERTN( kVStanev, _pSolution );
			Sint32 piIndex[ 4 ];

			double p;
			double tmp[ 4*4 ];
			if ( ! LUDecomposition( m_A, tmp, p, piIndex, dZeroEpsilon ) ) {
				return false;
			}

			this->LUBackSubstitution( tmp, piIndex, &m_arrB[0], _pSolution);

			return true;
		}

		Sint32 LUDecomposition(double* arrMatrix, double* _rResult, double &_rdEven_Odd, Sint32 *_pRowIndex, double dZeroEpsilon ) const
		{
			Sint32		i, iMax, j, k;
//			long double	dBig, dDum, dSum, dTemp;  // [MAF Cleanup, 12/22/05]
			double dBig, dDum, dSum, dTemp;
			double Vec[4];

			
			_rdEven_Odd = 1.0;
			for( i=0; i<4*4; i++)
				_rResult[i] = arrMatrix[i];

			for( i=0; i<4; i++ )
			{
				dBig = 0.0;
				for( j=0; j<4; j++ )
					if( (dTemp = Abs( _rResult[4*i+j] )) > dBig )
						dBig = dTemp;
				
				if( Abs(dBig)< dZeroEpsilon )
					return 0;
				Vec[i] = 1.0/dBig;
			}

			for( j=0; j<4; j++ )
			{
				for ( i=0; i<j; i++)
				{
					dSum = _rResult[4*i+j];
					for( k=0; k<i; k++ )
						dSum -= _rResult[4*i+k] * _rResult[4*k+j];
					_rResult[4*i+j] = dSum;
				}
				dBig = 0.0;
				for( i=j; i<4; i++)
				{
					dSum = _rResult[4*i+j];
					for( k=0; k<j; k++ )
						dSum -= _rResult[4*i+k] * _rResult[4*k+j];
					_rResult[4*i+j] = dSum;
					if( ( dDum = Vec[i]*Abs(dSum) ) >= dBig )
					{
						dBig = dDum;
						iMax = i;
					}
				}

				if( j!=iMax )
				{
					for( k=0; k<4; k++ )
					{
						dDum = _rResult[4*iMax+k];
						_rResult[4*iMax+k] = _rResult[4*j+k];
						_rResult[4*j+k] = dDum;
					}
					_rdEven_Odd = -_rdEven_Odd;
					Vec[iMax] = Vec[j];
				}

				if( _pRowIndex )
					_pRowIndex[j]=iMax;

		//.....if pivot element is zero........................

				if( Abs(_rResult[4*j+j] ) < dZeroEpsilon )
					return 0;

				if( j!=(4-1) )
				{
					dDum = 1.0/_rResult[4*j+j];
					for( i=j+1; i<4; i++ )
						_rResult[4*i+j] *= dDum;
				}
			}
			return 1;
		}

		void LUBackSubstitution(double* arrMatrix, const Sint32 *_pcRowIndex, double *_pB, double *_pSolution ) const
		{
			ASSERTN( kVStanev, _pB );
			ASSERTN( kVStanev, _pSolution );

			Sint32    i, ip, j, ii=-1;
//			long double dSum; // [MAF Cleanup, 12/22/05]
			double dSum;

			_pSolution[0]	= _pB[0];
			_pSolution[1]	= _pB[1];
			_pSolution[2]	= _pB[2];
			_pSolution[3]	= _pB[3];
			
			for( i=0; i<4; i++ )
			{
				ip = _pcRowIndex[i];
				dSum = _pB[ip];
				_pB[ip] = _pB[i];
				if( ii != -1 )
					for( j=ii; j<i; j++ )
						dSum -= arrMatrix[4*i+j]*_pB[j];
				else 
					if(dSum)
						ii=i;
				_pB[i] = dSum;
			}

			for(i=4-1; i>=0; i--)
			{
				dSum = _pB[i];
				for ( j=i+1; j<4; j++ )
					dSum -= arrMatrix[4*i+j]*_pB[j];
				_pB[i] = dSum / arrMatrix[4*i+i];
			}
			
			if( _pSolution )
			{
				std::swap( _pSolution[0], _pB[0] );
				std::swap( _pSolution[1], _pB[1] );
				std::swap( _pSolution[2], _pB[2] );
				std::swap( _pSolution[3], _pB[3] );
			}
		}
	private:
		double		m_A[4*4];//Coefficient matrix
		double		m_arrB[4];//Equation result vector.
	}	system;

	// Find fourth couple
	WorldPt3	vecG4	= inPt1 + ::CrossProduct( inPt2 - inPt1, inPt3 - inPt1 );
	WorldPt3	vecL4	= transfPt1 + ::CrossProduct( transfPt2 - transfPt1, transfPt3 - transfPt1 );

	const WorldPt3*	arrGV[4] = { & inPt1, & inPt2, & inPt3, & vecG4 };
	const WorldPt3*	arrLV[4] = { & transfPt1, & transfPt2, & transfPt3, & vecL4 };

	double dTmpVec[4];	
	dTmpVec[3] = 1.0;
	for (Sint32 i=0; i<3; i++)	{
		// find the i-th row of the transformation matrix
		system.Reset();
		for( Sint32 j=0; j<4; j++ )
		{
			dTmpVec[0] = arrGV[j]->x;
			dTmpVec[1] = arrGV[j]->y;
			dTmpVec[2] = arrGV[j]->z;
			double	result = 0.0;
			if ( i == 0 )		result = arrLV[j]->x;
			else if ( i == 1 )	result = arrLV[j]->y;
			else if ( i == 2 )	result = arrLV[j]->z;
			system.SetEquation( j, dTmpVec, result );
		}

		double	_solution[4];
		if ( !system.FindLUDecompSolution( _solution, 1.192092896e-07F ) )
		{
			::IdentityMatrix( outMatrix );
			ASSERTN( kVStanev, false);
			return false; // Some points coincide - transormation undefined
		}

		outMatrix.mat[0][i]	= _solution[0];
		outMatrix.mat[1][i]	= _solution[1];
		outMatrix.mat[2][i]	= _solution[2];
		outMatrix.mat[3][i]	= _solution[3];
	}

	return true;
} // CalcTransformFromOneTriToAnother


bool RayPlaneIntersection(const WorldPt3& ptOnPlane, const WorldPt3& planeNormal, const Ray& ray, WorldPt3* pOutIntersection, double* pOutDistance)
{
	WorldPt3 p = ptOnPlane;
	WorldPt3 n = planeNormal;
	WorldPt3 o = ray.vertex;
	WorldPt3 d = ray.direction.Normal();


	double	den		= n.Dot(d);

	bool	bFound	= false;
	if ( ! DoublesAreNearlyEqual( den, 0 ) ) {
		double num = -n.Dot(o - p);

		double tt = num / den;
		if( pOutDistance ) {
			*pOutDistance = tt;
		}

		if ( pOutIntersection ) {
			*pOutIntersection = o + d * tt;
		}

		bFound	= true;
	}

	return bFound;
}

bool IsPointNearLine(const WorldPt & inPoint, const WorldPt & inP0, const WorldPt & inP1, double inNearDist, Sint32 inLineType)
// returns whether point is near a line.  line may be an infinite line, a ray or a segment.
//		inLineType - 1 == infinite line, 2 == ray from inP0 toward inP1, 3 == segment from inP0 to inP1
{
	const double kEpsilon = 1e-3;

	WorldPt vec1 = inP1 - inP0;
	if( std::abs((int)vec1.MagnitudeSquared()) < kEpsilon ) {  // if line is a point, do point near point test
		return inPoint.DistanceFrom(inP0) <= inNearDist;
	}

	WorldPt vec1Norm = vec1.Normal();
	WorldPt vec2 = inPoint - inP0;
	double dot = vec2.Dot(vec1Norm);
	
	if( inLineType == 2 ) {												// if line is a ray
		if( dot < -inNearDist ) {										// if pt on wrong side of ray
			return false;
		}
	} else if( inLineType == 3 ) {										// if line is a segment
		if( dot < -inNearDist || dot > vec1.Magnitude()+inNearDist ) {	// if pt outside of segment
			return false;
		}
	}

	double perpDot = vec2.CrossMagnitude(vec1Norm);
	return std::abs((int)perpDot) <= inNearDist;
}

bool RayPlaneIntersection(const TransformMatrix& plane, const Ray& ray, WorldPt3* pOutIntersection, double* pOutDistance)
{
	return ::RayPlaneIntersection( plane.v2.offset, plane.v2.k, ray, pOutIntersection, pOutDistance );
}

bool RayPlaneIntersection(const Axis& plane, const Ray& ray, WorldPt3* pOutIntersection, double* pOutDistance)
{
	return ::RayPlaneIntersection( plane.vertex, plane.k, ray, pOutIntersection, pOutDistance );
}

bool RayCubeIntersection(const WorldCube& inwc, const Ray& inRay,
						 WorldPt3* outpwpt3Int1/*=NULL*/, WorldPt3* outpwpt3Int2/*=NULL*/,
						 double* outpA1/*=NULL*/, double* outpA2/*=NULL*/) 
{
	bool outbHit = false;
	if (outpwpt3Int1) *outpwpt3Int1 = WorldPt3();
	if (outpwpt3Int2) *outpwpt3Int2 = WorldPt3();
	if (outpA1)	*outpA1 = 0;
	if (outpA2)	*outpA2 = 0;

	if (VERIFYN(kEJKerr, ! inRay.direction.IsZero())
		&& ! inwc.IsEmpty()) {

		#define EpsilonForCoord(x)	(kNearlyEqualEpsilonForWorldCoords * Fabs(x))

		WorldCube wcE(inwc);
		wcE.left	-= EpsilonForCoord(inwc.left);
		wcE.right	+= EpsilonForCoord(inwc.right);
		wcE.bottom	-= EpsilonForCoord(inwc.bottom);
		wcE.top		+= EpsilonForCoord(inwc.top);
		wcE.back	-= EpsilonForCoord(inwc.back);
		wcE.front	+= EpsilonForCoord(inwc.front);

		bool bParallelX = NormalizedValueIsNearlyZero(inRay.direction.x);
		bool bParallelY = NormalizedValueIsNearlyZero(inRay.direction.y);
		bool bParallelZ = NormalizedValueIsNearlyZero(inRay.direction.z);

		WorldPt3 wpt3[2];
		double a[2];
		int c = 0;
		int cMax = 2;
		// We can stop at 1 pt if they are only detecting a hit.
		// Otherwise we need the best pt in Int1, so we need to go for 2.
		if (outpwpt3Int1 == NULL && outpwpt3Int2==NULL)
			cMax = 1;

		if ( ! bParallelX) {
			a[c] = (inwc.MinX() - inRay.vertex.X()) / inRay.direction.X();
			wpt3[c].y = inRay.vertex.Y() + inRay.direction.Y() * a[c];
			if (wpt3[c].y > wcE.MinY() && wpt3[c].y < wcE.MaxY()) {
				wpt3[c].z = inRay.vertex.Z() + inRay.direction.Z() * a[c];
				if (wpt3[c].z > wcE.MinZ() && wpt3[c].z < wcE.MaxZ()) {
					wpt3[c].x = inwc.MinX();
					c++;
				}
			}

			if (c < cMax) {
				a[c] = (inwc.MaxX() - inRay.vertex.X()) / inRay.direction.X();
				wpt3[c].y = inRay.vertex.Y() + inRay.direction.Y() * a[c];
				if (wpt3[c].y > wcE.MinY() && wpt3[c].y < wcE.MaxY()) {
					wpt3[c].z = inRay.vertex.Z() + inRay.direction.Z() * a[c];
					if (wpt3[c].z > wcE.MinZ() && wpt3[c].z < wcE.MaxZ()) {
						wpt3[c].x = inwc.MaxX();
						c++;
					}
				}
			}
		}

		if ( ! bParallelY) {

			if (c < cMax) {
				a[c] = (inwc.MinY() - inRay.vertex.Y()) / inRay.direction.Y();
				wpt3[c].x = inRay.vertex.X() + inRay.direction.X() * a[c];
				if (wpt3[c].x > wcE.MinX() && wpt3[c].x < wcE.MaxX()) {
					wpt3[c].z = inRay.vertex.Z() + inRay.direction.Z() * a[c];
					if (wpt3[c].z > wcE.MinZ() && wpt3[c].z < wcE.MaxZ()) {
						wpt3[c].y = inwc.MinY();
						if (c==0 || wpt3[c] != wpt3[0])
							c++;
					}
				}
			}

			if (c < cMax) {
				a[c] = (inwc.MaxY() - inRay.vertex.Y()) / inRay.direction.Y();
				wpt3[c].x = inRay.vertex.X() + inRay.direction.X() * a[c];
				if (wpt3[c].x > wcE.MinX() && wpt3[c].x < wcE.MaxX()) {
					wpt3[c].z = inRay.vertex.Z() + inRay.direction.Z() * a[c];
					if (wpt3[c].z > wcE.MinZ() && wpt3[c].z < wcE.MaxZ()) {
						wpt3[c].y = inwc.MaxY();
						if (c==0 || wpt3[c] != wpt3[0])
							c++;
					}
				}
			}
		}

		if ( ! bParallelZ) {

			if (c < cMax) {
				a[c] = (inwc.MinZ() - inRay.vertex.Z()) / inRay.direction.Z();
				wpt3[c].x = inRay.vertex.X() + inRay.direction.X() * a[c];
				if (wpt3[c].x > wcE.MinX() && wpt3[c].x < wcE.MaxX()) {
					wpt3[c].y = inRay.vertex.Y() + inRay.direction.Y() * a[c];
					if (wpt3[c].y > wcE.MinY() && wpt3[c].y < wcE.MaxY()) {
						wpt3[c].z = inwc.MinZ();
						if (c==0 || wpt3[c] != wpt3[0])
							c++;
					}
				}
			}

			if (c < cMax) {
				a[c] = (inwc.MaxZ() - inRay.vertex.Z()) / inRay.direction.Z();
				wpt3[c].x = inRay.vertex.X() + inRay.direction.X() * a[c];
				if (wpt3[c].x > wcE.MinX() && wpt3[c].x < wcE.MaxX()) {
					wpt3[c].y = inRay.vertex.Y() + inRay.direction.Y() * a[c];
					if (wpt3[c].y > wcE.MinY() && wpt3[c].y < wcE.MaxY()) {
						wpt3[c].z = inwc.MaxZ();
						if (c==0 || wpt3[c] != wpt3[0])
							c++;
					}
				}
			}
		}

		if (c > 0) {
			outbHit = true;

			if (c==1) { // only 1 hit pt, must be corner or edge

				if (outpwpt3Int1)
					*outpwpt3Int1 = wpt3[0];

				if (outpA1)
					*outpA1 = a[0];
			}
			else { // 2 hits
				// First prefer positive projection over negative,
				// then prefer the closest.
				int cPreferred = 0;

				if (a[0] * a[1] < 0) { // one neg, one pos

					if (a[1] > 0)
						cPreferred = 1;
				}
				else { // both neg or both pos

					if (a[0] < 0) { // both neg

						if (a[1] > a[0]) 
							cPreferred = 1;
					}
					else { // both pos

						if (a[1] < a[0]) 
							cPreferred = 1;
					}
				}

				int cNotPreferred = ! cPreferred;

				if (outpwpt3Int1)
					*outpwpt3Int1 = wpt3[cPreferred];
				if (outpwpt3Int2)
					*outpwpt3Int2 = wpt3[cNotPreferred];

				if (outpA1)
					*outpA1 = a[cPreferred];
				if (outpA2)
					*outpA2 = a[cNotPreferred];
			}
		}
	}

	return outbHit;
}

bool inline GetIntersection( WorldCoord fDst1, WorldCoord fDst2, const WorldPt3& P1, const WorldPt3& P2, WorldPt3& Hit ) 
{
	if ( (fDst1 * fDst2) >= 0.0 ) 
		return false;
	if (fDst1 == fDst2) 
		return false; 

	Hit = P1 + (P2-P1) * ( -fDst1/(fDst2-fDst1) );
	return true;
}

bool inline InBox( const WorldPt3& Hit, const WorldPt3& B1, const WorldPt3& B2, const int Axis ) 
{
	if ( Axis==1 && Hit.z > B1.z && Hit.z < B2.z && Hit.y > B1.y && Hit.y < B2.y)
		return true;
	if ( Axis==2 && Hit.z > B1.z && Hit.z < B2.z && Hit.x > B1.x && Hit.x < B2.x)
		return true;
	if ( Axis==3 && Hit.x > B1.x && Hit.x < B2.x && Hit.y > B1.y && Hit.y < B2.y)
		return true;

	return false;
}

// returns true if line (L1, L2) intersects with the worldcube: inWC
// returns intersection points in Hit1 & Hit2
bool LineIntersectsCube( const WorldCube& inWC, const WorldPt3& L1, const WorldPt3& L2, WorldPt3 &Hit1, WorldPt3 &Hit2 )
{

	if (!inWC.IsEmpty()) {
		WorldPt3 B1 = inWC.Pointxyz(); 
		WorldPt3 B2 = inWC.PointXYZ(); 
		bool bPoint1Set = false;
		bool bPoint2Set = false;

		if (L2.x < B1.x && L1.x < B1.x)
			return false;

		if (L2.x > B2.x && L1.x > B2.x)
			return false;
		
		if (L2.y < B1.y && L1.y < B1.y)
			return false;
		
		if (L2.y > B2.y && L1.y > B2.y)
			return false;
		
		if (L2.z < B1.z && L1.z < B1.z)
			return false;
		
		if (L2.z > B2.z && L1.z > B2.z)
			return false;

		if (L1.x > B1.x && L1.x < B2.x &&
			L1.y > B1.y && L1.y < B2.y &&
			L1.z > B1.z && L1.z < B2.z) {
			Hit1 = L1; 
			bPoint1Set = true;
		}

		if (L2.x > B1.x && L2.x < B2.x &&
			L2.y > B1.y && L2.y < B2.y &&
			L2.z > B1.z && L2.z < B2.z) {
			Hit2 = L2; 
			bPoint2Set = true;
		}

		if (bPoint1Set && bPoint2Set){
			return true;
		}
		else {
			// Have an array of 2 points & intersect
			WorldPt3 pts[2];
			int i = 0;
			WorldPt3 wPt3;

			if (GetIntersection( L1.x-B1.x, L2.x-B1.x, L1, L2, wPt3) && InBox( wPt3, B1, B2, 1 )) 
				pts[i++] = wPt3;

			if (GetIntersection( L1.y-B1.y, L2.y-B1.y, L1, L2, wPt3) && InBox( wPt3, B1, B2, 2 )) 
				pts[i++] = wPt3;

			if ( i < 2 && GetIntersection( L1.z-B1.z, L2.z-B1.z, L1, L2, wPt3) && InBox( wPt3, B1, B2, 3 ) ) 
				pts[i++] = wPt3;

			if ( i < 2 && GetIntersection( L1.x-B2.x, L2.x-B2.x, L1, L2, wPt3) && InBox( wPt3, B1, B2, 1 ) ) 
				pts[i++] = wPt3;

			if ( i < 2 && GetIntersection( L1.y-B2.y, L2.y-B2.y, L1, L2, wPt3) && InBox( wPt3, B1, B2, 2 ) ) 
				pts[i++] = wPt3;

			if ( i < 2 && GetIntersection( L1.z-B2.z, L2.z-B2.z, L1, L2, wPt3) && InBox( wPt3, B1, B2, 3 ) )
				pts[i++] = wPt3;

			if (i > 0) {
				if (!bPoint1Set) {
					Hit1 = pts[0]; 
					bPoint1Set = true;
				}
				else {
					Hit2 = pts[0]; 
					bPoint2Set = true;
				}
				
				if (!bPoint2Set && (i > 1)) 
					Hit2 = pts[1];
				else if (!bPoint2Set) 
					Hit2 = pts[0]; 

				return true;
			}
		}

	}
	return false;
}

GS_API TOneWayCoordSystem::TOneWayCoordSystem(void)
{
	IdentityMatrix(fCSMat);
	CreateAxisFromMatrix(fCSMat, fCSAxis);
}

GS_API TOneWayCoordSystem::TOneWayCoordSystem(const TransformMatrix& csMatrix)
{
	fCSMat = csMatrix;
	CreateAxisFromMatrix(fCSMat, fCSAxis);
}

GS_API TOneWayCoordSystem::TOneWayCoordSystem(const Axis& csAxis)
{
	fCSAxis = csAxis;
	CreateMatrixFromAxis(fCSAxis, fCSMat);
}


void GS_API TCoordSystem::Setup(void)
{
	InvertMatrix(fCSMat, fInverseCSMat);
}


GS_API TCoordSystem::TCoordSystem(void)
{
	IdentityMatrix(fInverseCSMat);
}

GS_API TCoordSystem::TCoordSystem(const Axis& csAxis) :
	TOneWayCoordSystem(csAxis)
{
	Setup();
}

GS_API TCoordSystem::TCoordSystem(const TransformMatrix& csMatrix) :
	TOneWayCoordSystem(csMatrix)
{
	Setup();
}

GS_API TCoordSystem::TCoordSystem(const TOneWayCoordSystem& csSystem) :
	TOneWayCoordSystem(csSystem)
{
	Setup();
}






#if 0

//#############
// PCP - TESTING
//#############



void TestFunction(void)
{
	TCoordSystem		tcs;
	TransformMatrix		m, m2, m3;
	WorldPt3			p;
	
	
	IdentityMatrix(m);
	
	tcs = TCoordSystem(m);
	
	CreateMatrixFromAxis(tcs.GetAxis(), m2);
	
	
	m3 = tcs;
	
	p = tcs.GetAxis().k;
	
	PointTransform(p, tcs, p);
	
	PointTransform(tcs.GetAxis().vertex, tcs, p);
	VectorTransform(tcs.GetAxis().k, tcs, p);
}


#endif


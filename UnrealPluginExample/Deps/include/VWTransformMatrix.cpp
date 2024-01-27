//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "Prefix/StdAfx.h"

using namespace VectorworksMVR::VWFC::Math;

VWTransformMatrix::VWTransformMatrix()
{
	this->SetIdentity();
}

VWTransformMatrix::VWTransformMatrix(const VWPoint3D& uVec, const VWPoint3D& vVec, const VWPoint3D& wVec, bool bTransponse /*=false*/)
{
	this->SetMatrix( uVec, vVec, wVec, bTransponse );
}

VWTransformMatrix::VWTransformMatrix(const VWPoint3D& uVec, const VWPoint3D& vVec, const VWPoint3D& wVec, const VWPoint3D& offset, bool bTransponse /*=false*/)
{
	this->SetMatrix( uVec, vVec, wVec, offset, bTransponse );
}

VWTransformMatrix::VWTransformMatrix(const VWPoint3D& offset)
{
	this->SetMatrix( offset );
}

VWTransformMatrix::VWTransformMatrix(double scaleX, double scaleY, double scaleZ)
{
	this->SetMatrix( scaleX, scaleY, scaleZ );
}

VWTransformMatrix::VWTransformMatrix(const TransformMatrix& mat)
{
	fMatrix.mat[0][0] = mat.mat[0][0]; fMatrix.mat[0][1] = mat.mat[0][1]; fMatrix.mat[0][2] = mat.mat[0][2];
	fMatrix.mat[1][0] = mat.mat[1][0]; fMatrix.mat[1][1] = mat.mat[1][1]; fMatrix.mat[1][2] = mat.mat[1][2];
	fMatrix.mat[2][0] = mat.mat[2][0]; fMatrix.mat[2][1] = mat.mat[2][1]; fMatrix.mat[2][2] = mat.mat[2][2];
	fMatrix.mat[3][0] = mat.mat[3][0]; fMatrix.mat[3][1] = mat.mat[3][1]; fMatrix.mat[3][2] = mat.mat[3][2];
}

VWTransformMatrix::VWTransformMatrix(const VWTransformMatrix& mat)
{
	fMatrix.mat[0][0] = mat.fMatrix.mat[0][0]; fMatrix.mat[0][1] = mat.fMatrix.mat[0][1]; fMatrix.mat[0][2] = mat.fMatrix.mat[0][2];
	fMatrix.mat[1][0] = mat.fMatrix.mat[1][0]; fMatrix.mat[1][1] = mat.fMatrix.mat[1][1]; fMatrix.mat[1][2] = mat.fMatrix.mat[1][2];
	fMatrix.mat[2][0] = mat.fMatrix.mat[2][0]; fMatrix.mat[2][1] = mat.fMatrix.mat[2][1]; fMatrix.mat[2][2] = mat.fMatrix.mat[2][2];
	fMatrix.mat[3][0] = mat.fMatrix.mat[3][0]; fMatrix.mat[3][1] = mat.fMatrix.mat[3][1]; fMatrix.mat[3][2] = mat.fMatrix.mat[3][2];
}

VWTransformMatrix::~VWTransformMatrix()
{
}

VWTransformMatrix& VWTransformMatrix::operator=(const VWTransformMatrix& mat)
{
	fMatrix.mat[0][0] = mat.fMatrix.mat[0][0]; fMatrix.mat[0][1] = mat.fMatrix.mat[0][1]; fMatrix.mat[0][2] = mat.fMatrix.mat[0][2];
	fMatrix.mat[1][0] = mat.fMatrix.mat[1][0]; fMatrix.mat[1][1] = mat.fMatrix.mat[1][1]; fMatrix.mat[1][2] = mat.fMatrix.mat[1][2];
	fMatrix.mat[2][0] = mat.fMatrix.mat[2][0]; fMatrix.mat[2][1] = mat.fMatrix.mat[2][1]; fMatrix.mat[2][2] = mat.fMatrix.mat[2][2];
	fMatrix.mat[3][0] = mat.fMatrix.mat[3][0]; fMatrix.mat[3][1] = mat.fMatrix.mat[3][1]; fMatrix.mat[3][2] = mat.fMatrix.mat[3][2];
	return *this;
}

bool VWTransformMatrix::operator==(const VWTransformMatrix& mat) const
{
	return this->IsEqual( mat );
}

void VWTransformMatrix::SetIdentity()
{
	fMatrix.mat[0][0] = 1; fMatrix.mat[0][1] = 0; fMatrix.mat[0][2] = 0;
	fMatrix.mat[1][0] = 0; fMatrix.mat[1][1] = 1; fMatrix.mat[1][2] = 0;
	fMatrix.mat[2][0] = 0; fMatrix.mat[2][1] = 0; fMatrix.mat[2][2] = 1;
	fMatrix.mat[3][0] = 0; fMatrix.mat[3][1] = 0; fMatrix.mat[3][2] = 0;
}

bool VWTransformMatrix::IsIdentity() const
{
#define EQUAL(a,b)	(Abs(a-b)<0.0001)
	return
		EQUAL( fMatrix.mat[0][0], 1 ) && EQUAL( fMatrix.mat[0][1], 0 ) && EQUAL( fMatrix.mat[0][2], 0 ) &&
		EQUAL( fMatrix.mat[1][0], 0 ) && EQUAL( fMatrix.mat[1][1], 1 ) && EQUAL( fMatrix.mat[1][2], 0 ) &&
		EQUAL( fMatrix.mat[2][0], 0 ) && EQUAL( fMatrix.mat[2][1], 0 ) && EQUAL( fMatrix.mat[2][2], 1 ) &&
		EQUAL( fMatrix.mat[3][0], 0 ) && EQUAL( fMatrix.mat[3][1], 0 ) && EQUAL( fMatrix.mat[3][2], 0 );
#undef EQUAL
}

bool VWTransformMatrix::IsEqual(const VWTransformMatrix& mat) const
{
#define EQUAL(a,b)	(Abs(a-b)<0.0001)
	return
		EQUAL( fMatrix.mat[0][0], mat.fMatrix.mat[0][0] ) && EQUAL( fMatrix.mat[0][1], mat.fMatrix.mat[0][1] ) && EQUAL( fMatrix.mat[0][2], mat.fMatrix.mat[0][2] ) &&
		EQUAL( fMatrix.mat[1][0], mat.fMatrix.mat[1][0] ) && EQUAL( fMatrix.mat[1][1], mat.fMatrix.mat[1][1] ) && EQUAL( fMatrix.mat[1][2], mat.fMatrix.mat[1][2] ) &&
		EQUAL( fMatrix.mat[2][0], mat.fMatrix.mat[2][0] ) && EQUAL( fMatrix.mat[2][1], mat.fMatrix.mat[2][1] ) && EQUAL( fMatrix.mat[2][2], mat.fMatrix.mat[2][2] ) &&
		EQUAL( fMatrix.mat[3][0], mat.fMatrix.mat[3][0] ) && EQUAL( fMatrix.mat[3][1], mat.fMatrix.mat[3][1] ) && EQUAL( fMatrix.mat[3][2], mat.fMatrix.mat[3][2] );
#undef EQUAL
}

void VWTransformMatrix::SetRotation(double angleDeg, VWPoint3D axisRot)
{
	axisRot.Normalize();
	double dAng	= angleDeg * kRadiansPerDegree;
	double dSin = sin( dAng * 0.5 );
	
	double dA = axisRot.x * dSin;
	double dM = axisRot.y * dSin;
	double dN = axisRot.z * dSin;
	double dR = cos( dAng * 0.5 );

	double sqr_A = dA * dA;
	double sqr_M = dM * dM;
	double sqr_N = dN * dN;
	double sqr_R = dR * dR;

	double dNR = dN * dR;
	double dMR = dM * dR;
	double dAR = dA * dR;

	this->SetIdentity();

	fMatrix.mat[0][0] = sqr_A - sqr_M - sqr_N + sqr_R;
	fMatrix.mat[1][1] = sqr_M - sqr_A - sqr_N + sqr_R;
	fMatrix.mat[2][2] = sqr_N - sqr_M - sqr_A + sqr_R;

	fMatrix.mat[0][1] = fMatrix.mat[1][0] = dA * dM;
	fMatrix.mat[0][2] = fMatrix.mat[2][0] = dA * dN;
	fMatrix.mat[1][2] = fMatrix.mat[2][1] = dN * dM;

	fMatrix.mat[0][1] = 2.0 * ( fMatrix.mat[0][1] - dNR );
	fMatrix.mat[1][0] = 2.0 * ( fMatrix.mat[1][0] + dNR );
	fMatrix.mat[0][2] = 2.0 * ( fMatrix.mat[0][2] + dMR );
	fMatrix.mat[2][0] = 2.0 * ( fMatrix.mat[2][0] - dMR );
	fMatrix.mat[1][2] = 2.0 * ( fMatrix.mat[1][2] - dAR );
	fMatrix.mat[2][1] = 2.0 * ( fMatrix.mat[2][1] + dAR );

	// inverted variant
	/*fMatrix.mat[0][0] = sqr_A - sqr_M - sqr_N + sqr_R;
	fMatrix.mat[1][1] = sqr_M - sqr_A - sqr_N + sqr_R;
	fMatrix.mat[2][2] = sqr_N - sqr_M - sqr_A + sqr_R;

	fMatrix.mat[1][0] = fMatrix.mat[0][1] = dA * dM;
	fMatrix.mat[2][0] = fMatrix.mat[0][2] = dA * dN;
	fMatrix.mat[2][1] = fMatrix.mat[1][2] = dN * dM;

	fMatrix.mat[1][0] = 2.0 * ( fMatrix.mat[1][0] - dNR );
	fMatrix.mat[0][1] = 2.0 * ( fMatrix.mat[0][1] + dNR );
	fMatrix.mat[2][0] = 2.0 * ( fMatrix.mat[2][0] + dMR );
	fMatrix.mat[0][2] = 2.0 * ( fMatrix.mat[0][2] - dMR );
	fMatrix.mat[2][1] = 2.0 * ( fMatrix.mat[2][1] - dAR );
	fMatrix.mat[1][2] = 2.0 * ( fMatrix.mat[1][2] + dAR );*/
}

void VWTransformMatrix::SetRotation(VWPoint3D newU)
{
	SetUVector(newU.Normalize());
	if (newU.Equal(VWPoint3D(0,0,1),VWPoint3D::sEpsilon) ||
		newU.Equal(VWPoint3D(0,0,-1),VWPoint3D::sEpsilon))
	{
		// being here means that:
		// X axis is (approximately) rotated to the +/- Z axis, rotation is (again approximately) around the Y axis.
		// so using the Y axis (the old V) we can find the new W which is (new U x old V) (order of vectors matters), ...
		SetWVector(newU.Cross(GetVVector()).Normalize());
		// ... and after that to refine the new V (which is approximately the old V but we need it accurately calculated).
		SetVVector(GetWVector().Cross(newU).Normalize());
	}
	else
	{		
		SetVVector(VWPoint3D(0,0,1).Cross(newU).Normalize());
		SetWVector(newU.Cross(GetVVector()));
	}
}

void VWTransformMatrix::SetTranslation(double x, double y, double z)
{
	fMatrix.mat[3][0]		= x;
	fMatrix.mat[3][1]		= y;
	fMatrix.mat[3][2]		= z;
}

void VWTransformMatrix::SetTranslation(const VWPoint3D& pt)
{
	fMatrix.mat[3][0]		= pt.x;
	fMatrix.mat[3][1]		= pt.y;
	fMatrix.mat[3][2]		= pt.z;
}

void VWTransformMatrix::SetMatrix(const VWPoint3D& uVec, const VWPoint3D& vVec, const VWPoint3D& wVec, bool bTransponse /*=false*/)
{
	if ( ! bTransponse ) {
		fMatrix.mat[0][0] = uVec.x;	fMatrix.mat[0][1] = uVec.y;	fMatrix.mat[0][2] = uVec.z;	//	- u(x, y, z) 
		fMatrix.mat[1][0] = vVec.x;	fMatrix.mat[1][1] = vVec.y;	fMatrix.mat[1][2] = vVec.z;	//	- v(x, y, z)
		fMatrix.mat[2][0] = wVec.x;	fMatrix.mat[2][1] = wVec.y;	fMatrix.mat[2][2] = wVec.z;	//	- w(x, y, z)
	}
	else {
		fMatrix.mat[0][0] = uVec.x;	fMatrix.mat[0][1] = vVec.x;	fMatrix.mat[0][2] = wVec.x;	//	- u(x, y, z) 
		fMatrix.mat[1][0] = uVec.y;	fMatrix.mat[1][1] = vVec.y;	fMatrix.mat[1][2] = wVec.y;	//	- v(x, y, z)
		fMatrix.mat[2][0] = uVec.z;	fMatrix.mat[2][1] = vVec.z;	fMatrix.mat[2][2] = wVec.z;	//	- w(x, y, z)
	}

	fMatrix.mat[3][0] = 0;		fMatrix.mat[3][1] = 0;		fMatrix.mat[3][2] = 0;		//  - offset(x,y,z)
}

void VWTransformMatrix::SetMatrix(const VWPoint3D& uVec, const VWPoint3D& vVec, const VWPoint3D& wVec, const VWPoint3D& offset, bool bTransponse /*=false*/)
{
	if ( ! bTransponse ) {
		fMatrix.mat[0][0] = uVec.x;	fMatrix.mat[0][1] = uVec.y;	fMatrix.mat[0][2] = uVec.z;	//	- u(x, y, z) 
		fMatrix.mat[1][0] = vVec.x;	fMatrix.mat[1][1] = vVec.y;	fMatrix.mat[1][2] = vVec.z;	//	- v(x, y, z)
		fMatrix.mat[2][0] = wVec.x;	fMatrix.mat[2][1] = wVec.y;	fMatrix.mat[2][2] = wVec.z;	//	- w(x, y, z)
	}
	else {
		fMatrix.mat[0][0] = uVec.x;	fMatrix.mat[0][1] = vVec.x;	fMatrix.mat[0][2] = wVec.x;	//	- u(x, y, z) 
		fMatrix.mat[1][0] = uVec.y;	fMatrix.mat[1][1] = vVec.y;	fMatrix.mat[1][2] = wVec.y;	//	- v(x, y, z)
		fMatrix.mat[2][0] = uVec.z;	fMatrix.mat[2][1] = vVec.z;	fMatrix.mat[2][2] = wVec.z;	//	- w(x, y, z)
	}

	fMatrix.mat[3][0] = offset.x;	fMatrix.mat[3][1] = offset.y;	fMatrix.mat[3][2] = offset.z;	//  - offset(x,y,z)
}

void VWTransformMatrix::SetMatrix(const VWPoint3D& offset)
{
	this->SetIdentity();
	fMatrix.mat[3][0] = offset.x;	fMatrix.mat[3][1] = offset.y;	fMatrix.mat[3][2] = offset.z;	//  - offset(x,y,z)
}

void VWTransformMatrix::SetMatrix(double scaleX, double scaleY, double scaleZ)
{
	fMatrix.mat[0][0] = scaleX;	fMatrix.mat[0][1] = 0;		fMatrix.mat[0][2] = 0;		//	- u(x, y, z) 
	fMatrix.mat[1][0] = 0;		fMatrix.mat[1][1] = scaleY;	fMatrix.mat[1][2] = 0;		//	- v(x, y, z)
	fMatrix.mat[2][0] = 0;		fMatrix.mat[2][1] = 0;		fMatrix.mat[2][2] = scaleZ;	//	- w(x, y, z)
	fMatrix.mat[3][0] = 0;		fMatrix.mat[3][1] = 0;		fMatrix.mat[3][2] = 0;		//  - offset(x,y,z)
}

VWPoint3D VWTransformMatrix::GetUVector() const
{
	return VWPoint3D( fMatrix.mat[0][0], fMatrix.mat[0][1], fMatrix.mat[0][2] );
}

void VWTransformMatrix::SetUVector(double x, double y, double z)
{
	fMatrix.mat[0][0] = x;	fMatrix.mat[0][1] = y;	fMatrix.mat[0][2] = z;		//	- u(x, y, z) 
}

void VWTransformMatrix::SetUVector(const VWPoint3D& uVec)
{
	fMatrix.mat[0][0] = uVec.x;	fMatrix.mat[0][1] = uVec.y;	fMatrix.mat[0][2] = uVec.z;		//	- u(x, y, z) 
}

VWPoint3D VWTransformMatrix::GetVVector() const
{
	return VWPoint3D( fMatrix.mat[1][0], fMatrix.mat[1][1], fMatrix.mat[1][2] );
}

void VWTransformMatrix::SetVVector(double x, double y, double z)
{
	fMatrix.mat[1][0] = x;	fMatrix.mat[1][1] = y;	fMatrix.mat[1][2] = z;		//	- v(x, y, z)
}

void VWTransformMatrix::SetVVector(const VWPoint3D& vVec)
{
	fMatrix.mat[1][0] = vVec.x;	fMatrix.mat[1][1] = vVec.y;	fMatrix.mat[1][2] = vVec.z;		//	- v(x, y, z)
}

VWPoint3D VWTransformMatrix::GetWVector() const
{
	return VWPoint3D( fMatrix.mat[2][0], fMatrix.mat[2][1], fMatrix.mat[2][2] );
}

void VWTransformMatrix::SetWVector(double x, double y, double z)
{
	fMatrix.mat[2][0] = x;	fMatrix.mat[2][1] = y;	fMatrix.mat[2][2] = z;		//  - offset(x,y,z)
}

void VWTransformMatrix::SetWVector(const VWPoint3D& wVec)
{
	fMatrix.mat[2][0] = wVec.x;	fMatrix.mat[2][1] = wVec.y;	fMatrix.mat[2][2] = wVec.z;		//  - offset(x,y,z)
}

VWPoint3D VWTransformMatrix::GetOffset() const
{
	return VWPoint3D( fMatrix.mat[3][0], fMatrix.mat[3][1], fMatrix.mat[3][2] );
}

void VWTransformMatrix::SetOffset(double x, double y, double z)
{
	fMatrix.mat[3][0]		= x;
	fMatrix.mat[3][1]		= y;
	fMatrix.mat[3][2]		= z;
}

void VWTransformMatrix::SetOffset(const VWPoint3D& off)
{
	fMatrix.mat[3][0]		= off.x;
	fMatrix.mat[3][1]		= off.y;
	fMatrix.mat[3][2]		= off.z;
}

VWTransformMatrix& VWTransformMatrix::Invert()
{
	double	pos = 0.0;
	double	neg = 0.0;
	
	double	temp;
	temp =   fMatrix.mat[0][0] * fMatrix.mat[1][1] * fMatrix.mat[2][2];		(temp >= 0 ? pos : neg) += temp;
	temp =   fMatrix.mat[0][1] * fMatrix.mat[1][2] * fMatrix.mat[2][0];		(temp >= 0 ? pos : neg) += temp;
	temp =   fMatrix.mat[0][2] * fMatrix.mat[1][0] * fMatrix.mat[2][1];		(temp >= 0 ? pos : neg) += temp;
	temp = -(fMatrix.mat[2][0] * fMatrix.mat[1][1] * fMatrix.mat[0][2]);		(temp >= 0 ? pos : neg) += temp;
	temp = -(fMatrix.mat[2][1] * fMatrix.mat[1][2] * fMatrix.mat[0][0]);		(temp >= 0 ? pos : neg) += temp;
	temp = -(fMatrix.mat[2][2] * fMatrix.mat[1][0] * fMatrix.mat[0][1]);		(temp >= 0 ? pos : neg) += temp;

	double	det = pos + neg;
	double	mag = pos - neg;
	
	if ( Abs(mag) < 0.00000001 ) {
		// Invert4by4_ByeBye();
		temp = fMatrix.mat[0][1]; fMatrix.mat[0][1] = fMatrix.mat[1][0]; fMatrix.mat[1][0] = temp;
		temp = fMatrix.mat[0][2]; fMatrix.mat[0][2] = fMatrix.mat[2][0]; fMatrix.mat[2][0] = temp;
		temp = fMatrix.mat[2][1]; fMatrix.mat[2][1] = fMatrix.mat[1][2]; fMatrix.mat[1][2] = temp;
	}
	else {
		temp = det / mag;
		if ( Abs(temp) < 0.00000001 ) { 
			// Invert4by4_ByeBye();
			temp = fMatrix.mat[0][1]; fMatrix.mat[0][1] = fMatrix.mat[1][0]; fMatrix.mat[1][0] = temp;
			temp = fMatrix.mat[0][2]; fMatrix.mat[0][2] = fMatrix.mat[2][0]; fMatrix.mat[2][0] = temp;
			temp = fMatrix.mat[2][1]; fMatrix.mat[2][1] = fMatrix.mat[1][2]; fMatrix.mat[1][2] = temp;
		}
		else {
			VWTransformMatrix	dest;
			dest.fMatrix.mat[0][0] =  (  fMatrix.mat[1][1] * fMatrix.mat[2][2] - fMatrix.mat[2][1] * fMatrix.mat[1][2] ) / det;
			dest.fMatrix.mat[0][1] = -(( fMatrix.mat[0][1] * fMatrix.mat[2][2] - fMatrix.mat[2][1] * fMatrix.mat[0][2] ) / det );
			dest.fMatrix.mat[0][2] =  (  fMatrix.mat[0][1] * fMatrix.mat[1][2] - fMatrix.mat[1][1] * fMatrix.mat[0][2] ) / det;
			dest.fMatrix.mat[1][0] = -(( fMatrix.mat[1][0] * fMatrix.mat[2][2] - fMatrix.mat[2][0] * fMatrix.mat[1][2] ) / det );
			dest.fMatrix.mat[1][1] =  (  fMatrix.mat[0][0] * fMatrix.mat[2][2] - fMatrix.mat[2][0] * fMatrix.mat[0][2] ) / det;
			dest.fMatrix.mat[1][2] = -(( fMatrix.mat[0][0] * fMatrix.mat[1][2] - fMatrix.mat[1][0] * fMatrix.mat[0][2] ) / det );
			dest.fMatrix.mat[2][0] =  (  fMatrix.mat[1][0] * fMatrix.mat[2][1] - fMatrix.mat[2][0] * fMatrix.mat[1][1] ) / det;
			dest.fMatrix.mat[2][1] = -(( fMatrix.mat[0][0] * fMatrix.mat[2][1] - fMatrix.mat[2][0] * fMatrix.mat[0][1] ) / det );
			dest.fMatrix.mat[2][2] =  (  fMatrix.mat[0][0] * fMatrix.mat[1][1] - fMatrix.mat[1][0] * fMatrix.mat[0][1] ) / det;

			dest.fMatrix.mat[3][0] = -(  fMatrix.mat[3][0] * dest.fMatrix.mat[0][0] + fMatrix.mat[3][1] * dest.fMatrix.mat[1][0] + fMatrix.mat[3][2] * dest.fMatrix.mat[2][0] );
			dest.fMatrix.mat[3][1] = -(  fMatrix.mat[3][0] * dest.fMatrix.mat[0][1] + fMatrix.mat[3][1] * dest.fMatrix.mat[1][1] + fMatrix.mat[3][2] * dest.fMatrix.mat[2][1] );
			dest.fMatrix.mat[3][2] = -(  fMatrix.mat[3][0] * dest.fMatrix.mat[0][2] + fMatrix.mat[3][1] * dest.fMatrix.mat[1][2] + fMatrix.mat[3][2] * dest.fMatrix.mat[2][2] );

			*this	= dest;
		}
	}

	return *this;
}

VWTransformMatrix VWTransformMatrix::Invert() const
{
	VWTransformMatrix	m	= * this;
	return m.Invert();
}

VWTransformMatrix VWTransformMatrix::GetInverted() const
{
	VWTransformMatrix	m	= * this;
	return m.Invert();
}

bool VWTransformMatrix::IsFlipped() const
{
	VWPoint3D	uVec	= VWPoint3D( fMatrix.mat[0][0], fMatrix.mat[0][1], fMatrix.mat[0][2] );
	VWPoint3D	vVec	= VWPoint3D( fMatrix.mat[1][0], fMatrix.mat[1][1], fMatrix.mat[1][2] );
	VWPoint3D	wVec	= VWPoint3D( fMatrix.mat[2][0], fMatrix.mat[2][1], fMatrix.mat[2][2] );

	return uVec.DotProduct( vVec.Cross( wVec ) ) < 0.0001;
}

void VWTransformMatrix::FlipMatrix()
{
	VWPoint3D	uVec	= VWPoint3D( fMatrix.mat[0][0], fMatrix.mat[0][1], fMatrix.mat[0][2] );
	VWPoint3D	vVec	= VWPoint3D( fMatrix.mat[1][0], fMatrix.mat[1][1], fMatrix.mat[1][2] );

	this->SetUVector( vVec );
	this->SetVVector( uVec );
}

void VWTransformMatrix::TranslateAfter(double x, double y, double z)
{
	fMatrix.mat[3][0] += x;
	fMatrix.mat[3][1] += y;
	fMatrix.mat[3][2] += z;
}

void VWTransformMatrix::TranslateAfter(const VWPoint3D& offset)
{
	this->TranslateAfter( offset.x, offset.y, offset.z );
}

void VWTransformMatrix::TranslateBefore(double x, double y, double z)
{
	fMatrix.mat[3][0] += ( fMatrix.mat[0][0] * x + fMatrix.mat[1][0] * y + fMatrix.mat[2][0] * z );
	fMatrix.mat[3][1] += ( fMatrix.mat[0][1] * x + fMatrix.mat[1][1] * y + fMatrix.mat[2][1] * z );
	fMatrix.mat[3][2] += ( fMatrix.mat[0][2] * x + fMatrix.mat[1][2] * y + fMatrix.mat[2][2] * z );
}

void VWTransformMatrix::TranslateBefore(const VWPoint3D& offset)
{
	this->TranslateBefore( offset.x, offset.y, offset.z );
}

void VWTransformMatrix::RotateXAfter(double angleDeg)
{
	double ang	= angleDeg * kRadiansPerDegree;
	double c	= cos( ang );
	double s	= sin( ang );

	double m01	= fMatrix.mat[0][1] * c - fMatrix.mat[0][2] * s;
	double m11	= fMatrix.mat[1][1] * c - fMatrix.mat[1][2] * s;
	double m21	= fMatrix.mat[2][1] * c - fMatrix.mat[2][2] * s;
	double m31	= fMatrix.mat[3][1] * c - fMatrix.mat[3][2] * s;

	fMatrix.mat[0][2]		= fMatrix.mat[0][1] * s + fMatrix.mat[0][2] * c;
	fMatrix.mat[1][2]		= fMatrix.mat[1][1] * s + fMatrix.mat[1][2] * c;
	fMatrix.mat[2][2]		= fMatrix.mat[2][1] * s + fMatrix.mat[2][2] * c;
	fMatrix.mat[3][2]		= fMatrix.mat[3][1] * s + fMatrix.mat[3][2] * c;

	fMatrix.mat[0][1]		= m01;
	fMatrix.mat[1][1]		= m11;
	fMatrix.mat[2][1]		= m21;
	fMatrix.mat[3][1]		= m31;
}

void VWTransformMatrix::RotateYAfter(double angleDeg)
{
	double ang	= angleDeg * kRadiansPerDegree;
	double c	= cos( ang );
	double s	= sin( ang );

	double m00	= fMatrix.mat[0][0] * c + fMatrix.mat[0][2] * s;
	double m10	= fMatrix.mat[1][0] * c + fMatrix.mat[1][2] * s;
	double m20	= fMatrix.mat[2][0] * c + fMatrix.mat[2][2] * s;
	double m30	= fMatrix.mat[3][0] * c + fMatrix.mat[3][2] * s;

	fMatrix.mat[0][2]		= - fMatrix.mat[0][0] * s + fMatrix.mat[0][2] * c;
	fMatrix.mat[1][2]		= - fMatrix.mat[1][0] * s + fMatrix.mat[1][2] * c;
	fMatrix.mat[2][2]		= - fMatrix.mat[2][0] * s + fMatrix.mat[2][2] * c;
	fMatrix.mat[3][2]		= - fMatrix.mat[3][0] * s + fMatrix.mat[3][2] * c;

	fMatrix.mat[0][0]		= m00;
	fMatrix.mat[1][0]		= m10;
	fMatrix.mat[2][0]		= m20;
	fMatrix.mat[3][0]		= m30;
}

void VWTransformMatrix::RotateZAfter(double angleDeg)
{
	double ang	= angleDeg * kRadiansPerDegree;
	double c	= cos( ang );
	double s	= sin( ang );

	double m00	= fMatrix.mat[0][0] * c - fMatrix.mat[0][1] * s;
	double m10	= fMatrix.mat[1][0] * c - fMatrix.mat[1][1] * s;
	double m20	= fMatrix.mat[2][0] * c - fMatrix.mat[2][1] * s;
	double m30	= fMatrix.mat[3][0] * c - fMatrix.mat[3][1] * s;

	fMatrix.mat[0][1]		= fMatrix.mat[0][0] * s + fMatrix.mat[0][1] * c;
	fMatrix.mat[1][1]		= fMatrix.mat[1][0] * s + fMatrix.mat[1][1] * c;
	fMatrix.mat[2][1]		= fMatrix.mat[2][0] * s + fMatrix.mat[2][1] * c;
	fMatrix.mat[3][1]		= fMatrix.mat[3][0] * s + fMatrix.mat[3][1] * c;

	fMatrix.mat[0][0]		= m00;
	fMatrix.mat[1][0]		= m10;
	fMatrix.mat[2][0]		= m20;
	fMatrix.mat[3][0]		= m30;
}

void VWTransformMatrix::RotateXBefore(double angleDeg)
{
	double ang	= angleDeg * kRadiansPerDegree;
	double c	= cos( ang );
	double s	= sin( ang );
	
	double m10	= fMatrix.mat[1][0] * c + fMatrix.mat[2][0] * s;
	double m11	= fMatrix.mat[1][1] * c + fMatrix.mat[2][1] * s;
	double m12	= fMatrix.mat[1][2] * c + fMatrix.mat[2][2] * s;

	double m20	= - fMatrix.mat[1][0] * s + fMatrix.mat[2][0] * c;
	double m21	= - fMatrix.mat[1][1] * s + fMatrix.mat[2][1] * c;
	double m22	= - fMatrix.mat[1][2] * s + fMatrix.mat[2][2] * c;

	fMatrix.mat[1][0]		= m10;
	fMatrix.mat[1][1]		= m11;
	fMatrix.mat[1][2]		= m12;

	fMatrix.mat[2][0]		= m20;
	fMatrix.mat[2][1]		= m21;
	fMatrix.mat[2][2]		= m22;
}

void VWTransformMatrix::RotateYBefore(double angleDeg)
{
	double ang	= angleDeg * kRadiansPerDegree;
	double c	= cos( ang );
	double s	= sin( ang );

	double m00	= fMatrix.mat[0][0] * c - fMatrix.mat[2][0] * s;
	double m01	= fMatrix.mat[0][1] * c - fMatrix.mat[2][1] * s;
	double m02	= fMatrix.mat[0][2] * c - fMatrix.mat[2][2] * s;

	double m20	= fMatrix.mat[0][0] * s + fMatrix.mat[2][0] * c;
	double m21	= fMatrix.mat[0][1] * s + fMatrix.mat[2][1] * c;
	double m22	= fMatrix.mat[0][2] * s + fMatrix.mat[2][2] * c;

	fMatrix.mat[0][0]	= m00;
	fMatrix.mat[0][1]	= m01;
	fMatrix.mat[0][2]	= m02;

	fMatrix.mat[2][0]	= m20;
	fMatrix.mat[2][1]	= m21;
	fMatrix.mat[2][2]	= m22;
}

void VWTransformMatrix::RotateZBefore(double angleDeg)
{
	double ang	= angleDeg * kRadiansPerDegree;
	double c	= cos( ang );
	double s	= sin( ang );

	double m00	= fMatrix.mat[0][0] * c + fMatrix.mat[1][0] * s;
	double m01	= fMatrix.mat[0][1] * c + fMatrix.mat[1][1] * s;
	double m02	= fMatrix.mat[0][2] * c + fMatrix.mat[1][2] * s;

	fMatrix.mat[1][0]		= - fMatrix.mat[0][0] * s + fMatrix.mat[1][0] * c;
	fMatrix.mat[1][1]		= - fMatrix.mat[0][1] * s + fMatrix.mat[1][1] * c;
	fMatrix.mat[1][2]		= - fMatrix.mat[0][2] * s + fMatrix.mat[1][2] * c;
	 
	fMatrix.mat[0][0]		= m00;
	fMatrix.mat[0][1]		= m01;
	fMatrix.mat[0][2]		= m02;
}

void VWTransformMatrix::ScaleAfter(double scaleX, double scaleY, double scaleZ)
{
	fMatrix.mat[0][0] *= scaleX; fMatrix.mat[1][0] *= scaleX; fMatrix.mat[2][0] *= scaleX; fMatrix.mat[3][0] *= scaleX;
	fMatrix.mat[0][1] *= scaleY; fMatrix.mat[1][1] *= scaleY; fMatrix.mat[2][1] *= scaleY; fMatrix.mat[3][1] *= scaleY;
	fMatrix.mat[0][2] *= scaleZ; fMatrix.mat[1][2] *= scaleZ; fMatrix.mat[2][2] *= scaleZ; fMatrix.mat[3][2] *= scaleZ;
}

void VWTransformMatrix::RotateRoundPoint(const VWPoint3D& centerPt, double angXDeg, double angYDeg, double angZDeg)
{
	this->TranslateAfter( - centerPt.x, - centerPt.y, - centerPt.z );
	this->RotateXAfter( angXDeg );
	this->RotateYAfter( angYDeg );
	this->RotateZAfter( angZDeg );
	this->TranslateAfter( centerPt.x, centerPt.y, centerPt.z );
}

void VWTransformMatrix::ScaleWithCenter(const VWPoint3D& centerPt, double scaleX, double scaleY, double scaleZ)
{
	this->TranslateAfter( - centerPt.x, - centerPt.y, - centerPt.z );
	this->ScaleAfter( scaleX, scaleY, scaleZ );
	this->TranslateAfter( centerPt.x, centerPt.y, centerPt.z );
}

VWPoint2D VWTransformMatrix::PointTransform(const VWPoint2D& point) const
{
	VWPoint2D	res;
	res.x =	point.x * fMatrix.mat[0][0] + point.y * fMatrix.mat[1][0] + 0/*point.z*/ * fMatrix.mat[2][0] + fMatrix.mat[3][0];
	res.y =	point.x * fMatrix.mat[0][1] + point.y * fMatrix.mat[1][1] + 0/*point.z*/ * fMatrix.mat[2][1] + fMatrix.mat[3][1];
	//res.z =	point.x * fMatrix.mat[0][2] + point.y * fMatrix.mat[1][2] + 0/*point.z*/ * fMatrix.mat[2][2] + fMatrix.mat[3][2];
	return res;
}

VWPoint3D VWTransformMatrix::PointTransform(const VWPoint3D& point) const
{
	VWPoint3D	res;
	res.x =	point.x * fMatrix.mat[0][0] + point.y * fMatrix.mat[1][0] + point.z * fMatrix.mat[2][0] + fMatrix.mat[3][0];
	res.y =	point.x * fMatrix.mat[0][1] + point.y * fMatrix.mat[1][1] + point.z * fMatrix.mat[2][1] + fMatrix.mat[3][1];
	res.z =	point.x * fMatrix.mat[0][2] + point.y * fMatrix.mat[1][2] + point.z * fMatrix.mat[2][2] + fMatrix.mat[3][2];
	return res;
}

VWPoint2D VWTransformMatrix::InversePointTransform(const VWPoint2D& point) const
{
	// Linear algebra equivalent:
	// b = a MAT^{-1}

	VWPoint3D		dOffset;

	dOffset.x = point.x - fMatrix.mat[3][0];
	dOffset.y = point.y - fMatrix.mat[3][1];
	dOffset.z = 0/*point.z*/ - fMatrix.mat[3][2];
	
	VWPoint2D		res;
	res.x =	dOffset.x * fMatrix.mat[0][0] + dOffset.y * fMatrix.mat[0][1] + dOffset.z * fMatrix.mat[0][2];
	res.y =	dOffset.x * fMatrix.mat[1][0] + dOffset.y * fMatrix.mat[1][1] + dOffset.z * fMatrix.mat[1][2];
	//res.z =	dOffset.x * fMatrix.mat[2][0] + dOffset.y * fMatrix.mat[2][1] + dOffset.z * fMatrix.mat[2][2];
	return res;
}

VWPoint3D VWTransformMatrix::InversePointTransform(const VWPoint3D& point) const
{
	// Linear algebra equivalent:
	// b = a MAT^{-1}

	VWPoint3D		dOffset;

	dOffset.x = point.x - fMatrix.mat[3][0];
	dOffset.y = point.y - fMatrix.mat[3][1];
	dOffset.z = point.z - fMatrix.mat[3][2];
	
	VWPoint3D		res;
	res.x =	dOffset.x * fMatrix.mat[0][0] + dOffset.y * fMatrix.mat[0][1] + dOffset.z * fMatrix.mat[0][2];
	res.y =	dOffset.x * fMatrix.mat[1][0] + dOffset.y * fMatrix.mat[1][1] + dOffset.z * fMatrix.mat[1][2];
	res.z =	dOffset.x * fMatrix.mat[2][0] + dOffset.y * fMatrix.mat[2][1] + dOffset.z * fMatrix.mat[2][2];
	return res;
}

void VWTransformMatrix::TransformPoint(VWPoint2D& inOutPt) const
{
	double		inPtX		= inOutPt.x;
	//double	inPtY		= inOutPt.y;

	inOutPt.x	= inPtX * fMatrix.mat[0][0] + inOutPt.y * fMatrix.mat[1][0] /*+ 0/inOutPt.z/ * fMatrix.mat[2][0]*/ + fMatrix.mat[3][0];
	inOutPt.y	= inPtX * fMatrix.mat[0][1] + inOutPt.y * fMatrix.mat[1][1] /*+ 0/inOutPt.z/ * fMatrix.mat[2][1]*/ + fMatrix.mat[3][1];
	//inOutPt.z	= inPtX * fMatrix.mat[0][2] + inPtY * fMatrix.mat[1][2] + 0/*inOutPt.z*/ * fMatrix.mat[2][2] + fMatrix.mat[3][2];
}

void VWTransformMatrix::TransformPoint(VWPoint3D& inOutPt) const
{
	double		inPtX		= inOutPt.x;
	double		inPtY		= inOutPt.y;

	inOutPt.x	= inPtX * fMatrix.mat[0][0] + inPtY * fMatrix.mat[1][0] + inOutPt.z * fMatrix.mat[2][0] + fMatrix.mat[3][0];
	inOutPt.y	= inPtX * fMatrix.mat[0][1] + inPtY * fMatrix.mat[1][1] + inOutPt.z * fMatrix.mat[2][1] + fMatrix.mat[3][1];
	inOutPt.z	= inPtX * fMatrix.mat[0][2] + inPtY * fMatrix.mat[1][2] + inOutPt.z * fMatrix.mat[2][2] + fMatrix.mat[3][2];
}

void VWTransformMatrix::InverseTransformPoint(VWPoint2D& inOutPt) const
{
	// Linear algebra equivalent:
	// b = a MAT^{-1}

	double		offsetX		= inOutPt.x - fMatrix.mat[3][0];
	double		offsetY		= inOutPt.y - fMatrix.mat[3][1];
	double		offsetZ		= 0/*inOutPt.z*/ - fMatrix.mat[3][2];

	inOutPt.x	= offsetX * fMatrix.mat[0][0] + offsetY * fMatrix.mat[0][1] + offsetZ * fMatrix.mat[0][2];
	inOutPt.y	= offsetX * fMatrix.mat[1][0] + offsetY * fMatrix.mat[1][1] + offsetZ * fMatrix.mat[1][2];
	//inOutPt.z	= offsetX * fMatrix.mat[2][0] + offsetY * fMatrix.mat[2][1] + offsetZ * fMatrix.mat[2][2];
}

void VWTransformMatrix::InverseTransformPoint(VWPoint3D& inOutPt) const
{
	// Linear algebra equivalent:
	// b = a MAT^{-1}

	double		offsetX		= inOutPt.x - fMatrix.mat[3][0];
	double		offsetY		= inOutPt.y - fMatrix.mat[3][1];
	double		offsetZ		= inOutPt.z - fMatrix.mat[3][2];

	inOutPt.x	= offsetX * fMatrix.mat[0][0] + offsetY * fMatrix.mat[0][1] + offsetZ * fMatrix.mat[0][2];
	inOutPt.y	= offsetX * fMatrix.mat[1][0] + offsetY * fMatrix.mat[1][1] + offsetZ * fMatrix.mat[1][2];
	inOutPt.z	= offsetX * fMatrix.mat[2][0] + offsetY * fMatrix.mat[2][1] + offsetZ * fMatrix.mat[2][2];
}

void VWTransformMatrix::PointsTransform(TSTLPoints2DArray& inOutArr2DPoints) const
{
	size_t		ptsCnt		= inOutArr2DPoints.size();
	for ( size_t i = 0 ; i < ptsCnt ; ++ i )
	{
		this->TransformPoint( inOutArr2DPoints[i] );
	}
}

void VWTransformMatrix::PointsTransform(TSTLPoints3DArray& inOutArr3DPoints) const
{
	size_t		ptsCnt		= inOutArr3DPoints.size();
	for ( size_t i = 0 ; i < ptsCnt ; ++ i )
	{
		this->TransformPoint( inOutArr3DPoints[i] );
	}
}

void VWTransformMatrix::InversePointsTransform(TSTLPoints2DArray& inOutArr2DPoints) const
{
	size_t ptsCnt = inOutArr2DPoints.size();
	for ( size_t i = 0 ; i < ptsCnt ; ++ i )
	{
		 this->InverseTransformPoint( inOutArr2DPoints[i] );
	}
}

void VWTransformMatrix::InversePointsTransform(TSTLPoints3DArray& inOutArr3DPoints) const
{
	size_t ptsCnt = inOutArr3DPoints.size();
	for ( size_t i = 0 ; i < ptsCnt ; ++ i )
	{
		this->InverseTransformPoint( inOutArr3DPoints[i] );
	}
}

// operations

VWPoint2D VWTransformMatrix::operator*(const VWPoint2D& point) const
{
	return this->PointTransform( point );
}

VWPoint3D VWTransformMatrix::operator*(const VWPoint3D& point) const
{
	return this->PointTransform( point );
}

VWTransformMatrix VWTransformMatrix::operator*(const VWTransformMatrix& matrix) const
{
	VWTransformMatrix	m	= * this;
	return m *= matrix;
}

VWTransformMatrix& VWTransformMatrix::operator*=(const VWTransformMatrix& matrix)
{
	VWTransformMatrix	returnMat;	
	returnMat.fMatrix.mat[0][0] = matrix.fMatrix.mat[0][0] * this->fMatrix.mat[0][0] + matrix.fMatrix.mat[1][0] * this->fMatrix.mat[0][1] + matrix.fMatrix.mat[2][0] * this->fMatrix.mat[0][2];
	returnMat.fMatrix.mat[0][1] = matrix.fMatrix.mat[0][1] * this->fMatrix.mat[0][0] + matrix.fMatrix.mat[1][1] * this->fMatrix.mat[0][1] + matrix.fMatrix.mat[2][1] * this->fMatrix.mat[0][2];
	returnMat.fMatrix.mat[0][2] = matrix.fMatrix.mat[0][2] * this->fMatrix.mat[0][0] + matrix.fMatrix.mat[1][2] * this->fMatrix.mat[0][1] + matrix.fMatrix.mat[2][2] * this->fMatrix.mat[0][2];
	returnMat.fMatrix.mat[1][0] = matrix.fMatrix.mat[0][0] * this->fMatrix.mat[1][0] + matrix.fMatrix.mat[1][0] * this->fMatrix.mat[1][1] + matrix.fMatrix.mat[2][0] * this->fMatrix.mat[1][2];
	returnMat.fMatrix.mat[1][1] = matrix.fMatrix.mat[0][1] * this->fMatrix.mat[1][0] + matrix.fMatrix.mat[1][1] * this->fMatrix.mat[1][1] + matrix.fMatrix.mat[2][1] * this->fMatrix.mat[1][2];
	returnMat.fMatrix.mat[1][2] = matrix.fMatrix.mat[0][2] * this->fMatrix.mat[1][0] + matrix.fMatrix.mat[1][2] * this->fMatrix.mat[1][1] + matrix.fMatrix.mat[2][2] * this->fMatrix.mat[1][2];
	returnMat.fMatrix.mat[2][0] = matrix.fMatrix.mat[0][0] * this->fMatrix.mat[2][0] + matrix.fMatrix.mat[1][0] * this->fMatrix.mat[2][1] + matrix.fMatrix.mat[2][0] * this->fMatrix.mat[2][2];
	returnMat.fMatrix.mat[2][1] = matrix.fMatrix.mat[0][1] * this->fMatrix.mat[2][0] + matrix.fMatrix.mat[1][1] * this->fMatrix.mat[2][1] + matrix.fMatrix.mat[2][1] * this->fMatrix.mat[2][2];
	returnMat.fMatrix.mat[2][2] = matrix.fMatrix.mat[0][2] * this->fMatrix.mat[2][0] + matrix.fMatrix.mat[1][2] * this->fMatrix.mat[2][1] + matrix.fMatrix.mat[2][2] * this->fMatrix.mat[2][2];

	returnMat.fMatrix.mat[3][0] = matrix.fMatrix.mat[0][0] * this->fMatrix.mat[3][0] + matrix.fMatrix.mat[1][0] * this->fMatrix.mat[3][1] + matrix.fMatrix.mat[2][0] * this->fMatrix.mat[3][2] + matrix.fMatrix.mat[3][0];
	returnMat.fMatrix.mat[3][1] = matrix.fMatrix.mat[0][1] * this->fMatrix.mat[3][0] + matrix.fMatrix.mat[1][1] * this->fMatrix.mat[3][1] + matrix.fMatrix.mat[2][1] * this->fMatrix.mat[3][2] + matrix.fMatrix.mat[3][1];
	returnMat.fMatrix.mat[3][2] = matrix.fMatrix.mat[0][2] * this->fMatrix.mat[3][0] + matrix.fMatrix.mat[1][2] * this->fMatrix.mat[3][1] + matrix.fMatrix.mat[2][2] * this->fMatrix.mat[3][2] + matrix.fMatrix.mat[3][2];

	*this = returnMat;
	return *this;
}

// compatibility with SDK
VWTransformMatrix::operator const TransformMatrix&() const
{
	return fMatrix;
}

VWTransformMatrix::operator TransformMatrix&()
{
	return fMatrix;
}

// gets the minor from rows {row0, row1} and columns {col0, col1}.
double VWTransformMatrix::GetMinor2x2(size_t row0, size_t row1, size_t col0, size_t col1) const
{
	return	( ( fMatrix.mat[ row0 ][ col0 ] * fMatrix.mat[ row1 ][ col1 ] ) - 
			  ( fMatrix.mat[ row0 ][ col1 ] * fMatrix.mat[ row1 ][ col0 ] ) );
}
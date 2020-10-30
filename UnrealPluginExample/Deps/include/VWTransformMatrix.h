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
			class VWTransformMatrix
		{
		public:
									VWTransformMatrix();
									VWTransformMatrix(const VWPoint3D& uVec, const VWPoint3D& vVec, const VWPoint3D& wVec, bool bTransponse=false);
									VWTransformMatrix(const VWPoint3D& uVec, const VWPoint3D& vVec, const VWPoint3D& wVec, const VWPoint3D& offset, bool bTransponse=false);
									VWTransformMatrix(const VWPoint3D& offset);
									VWTransformMatrix(double scaleX, double scaleY, double scaleZ);
									VWTransformMatrix(const TransformMatrix& mat);
				VWTransformMatrix(const VWTransformMatrix& mat);
				virtual					~VWTransformMatrix();

				VWTransformMatrix&		operator=(const VWTransformMatrix& mat);

				bool					operator==(const VWTransformMatrix& mat) const;

			public:
				void					SetIdentity();
				bool					IsIdentity() const;

				bool					IsEqual(const VWTransformMatrix& mat) const;

				void					SetRotation(double angleDeg, VWPoint3D axisRot);
				void					SetRotation(VWPoint3D newZ, VWPoint3D newY);
			void					SetRotation(VWPoint3D newU);
			void					SetTranslation(double x, double y, double z);
			void					SetTranslation(const VWPoint3D& pt);
			void					SetMatrix(const VWPoint3D& uVec, const VWPoint3D& vVec, const VWPoint3D& wVec, bool bTransponse=false);
			void					SetMatrix(const VWPoint3D& uVec, const VWPoint3D& vVec, const VWPoint3D& wVec, const VWPoint3D& offset, bool bTransponse=false);
			void					SetMatrix(const VWPoint3D& offset);
			void					SetMatrix(double scaleX, double scaleY, double scaleZ);

				VWPoint3D				GetUVector() const;
				void					SetUVector(double x, double y, double z);
				void					SetUVector(const VWPoint3D& uVec);
				VWPoint3D				GetVVector() const;
				void					SetVVector(double x, double y, double z);
				void					SetVVector(const VWPoint3D& vVec);
				VWPoint3D				GetWVector() const;
				void					SetWVector(double x, double y, double z);
				void					SetWVector(const VWPoint3D& wVec);

				VWPoint3D				GetOffset() const;
				void					SetOffset(double x, double y, double z);
				void					SetOffset(const VWPoint3D& off);

				VWTransformMatrix&		Invert();
				VWTransformMatrix		Invert() const;
				VWTransformMatrix		GetInverted() const;

				bool					IsFlipped() const;
				void					FlipMatrix();

				void					TranslateAfter(double x, double y, double z);
				void					TranslateAfter(const VWPoint3D& offset);

				void					TranslateBefore(double x, double y, double z);
				void					TranslateBefore(const VWPoint3D& offset);

				void					RotateXAfter(double angleDeg);
				void					RotateYAfter(double angleDeg);
				void					RotateZAfter(double angleDeg);

				void					RotateXBefore(double angleDeg);
				void					RotateYBefore(double angleDeg);
				void					RotateZBefore(double angleDeg);

				void					RotateRoundPoint(const VWPoint3D& centerPt, double angXDeg, double angYDeg, double angZDeg);

				void					ScaleAfter(double scaleX, double scaleY, double scaleZ);

				void					ScaleWithCenter(const VWPoint3D& centerPt, double scaleX, double scaleY, double scaleZ);

				VWPoint2D				PointTransform(const VWPoint2D& point) const;
				VWPoint3D				PointTransform(const VWPoint3D& point) const;
				VWPoint2D				InversePointTransform(const VWPoint2D& point) const;
				VWPoint3D				InversePointTransform(const VWPoint3D& point) const;

				void					TransformPoint(VWPoint2D& inOutPt) const;
				void					TransformPoint(VWPoint3D& inOutPt) const;
				void					InverseTransformPoint(VWPoint2D& inOutPt) const;
				void					InverseTransformPoint(VWPoint3D& inOutPt) const;

				void					PointsTransform(TSTLPoints2DArray& inOutArr2DPoints) const;
				void					PointsTransform(TSTLPoints3DArray& inOutArr3DPoints) const;
				void					InversePointsTransform(TSTLPoints2DArray& inOutArr2DPoints) const;
				void					InversePointsTransform(TSTLPoints3DArray& inOutArr3DPoints) const;

				// operations
				VWPoint2D				operator*(const VWPoint2D& point) const;
				VWPoint3D				operator*(const VWPoint3D& point) const;
				VWTransformMatrix		operator*(const VWTransformMatrix& matrix) const;
				VWTransformMatrix&		operator*=(const VWTransformMatrix& matrix);

			public:
				// compatibility with SDK
				operator const TransformMatrix&() const;
				operator TransformMatrix&();


			public:
				// gets the minor from rows {row0, row1} and columns {col0, col1}.
				double					GetMinor2x2(size_t row0, size_t row1, size_t col0, size_t col1) const;

				// matrix data
			public:
				// fMatrix.mat[0][0] fMatrix.mat[0][1] fMatrix.mat[0][2]	- u(x, y, z) 
				// fMatrix.mat[1][0] fMatrix.mat[1][1] fMatrix.mat[1][2]	- v(x, y, z)
				// fMatrix.mat[2][0] fMatrix.mat[2][1] fMatrix.mat[2][2]	- w(x, y, z)
				// fMatrix.mat[3][0] fMatrix.mat[3][1] fMatrix.mat[3][2]  - offset(x,y,z)
				TransformMatrix		fMatrix;
			};
		}
	}
}
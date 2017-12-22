#include "Matrix.h"


namespace easym
{

	void Matrix::Identity()
	{
		_11 = 1; _12 = 0; _13 = 0; _14 = 0;
		_21 = 0; _22 = 1; _23 = 0; _24 = 0;
		_31 = 0; _32 = 0; _33 = 1; _34 = 0;
		_41 = 0; _42 = 0; _43 = 0; _44 = 1;
	}
	void Matrix::Zero()
	{
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				m[i][j] = 0;
	}
	bool Matrix::operator==(const Matrix& other) const
	{
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				if (equal(m[i][j], other.m[i][j]))
					return false;
		return true;
	}
	Matrix Matrix::operator+(const Matrix& other) const
	{
		Matrix mat;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				mat.m[i][j] = m[i][j] + other.m[i][j];
		return mat;
	}
	Matrix Matrix::operator-(const Matrix& other) const
	{
		Matrix mat;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				mat.m[i][j] = m[i][j] - other.m[i][j];
		return mat;
	}
	Matrix Matrix::operator*(const Matrix& other) const
	{
		Matrix mat;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
			{
				mat.m[j][i] = (m[j][0] * other.m[0][i]) +
					(m[j][1] * other.m[1][i]) +
					(m[j][2] * other.m[2][i]) +
					(m[j][3] * other.m[3][i]);
			}
		return mat;
	}

	 Vector4 operator* (const Vector4& v, const Matrix& m)
	{
		return Vector4(v.x * m._11 + v.y * m._21 + v.z * m._31 + v.w * m._41,
			v.x * m._12 + v.y * m._22 + v.z * m._32 + v.w * m._42,
			v.x * m._13 + v.y * m._23 + v.z * m._33 + v.w * m._43,
			v.x * m._14 + v.y * m._24 + v.z * m._34 + v.w * m._44);
	}

	//矩阵转置
	Matrix Matrix::transpose()const
	{
		return Matrix(
			_11, _21, _31, _41,
			_12, _22, _32, _42,
			_13, _23, _33, _43,
			_14, _24, _34, _44);
	}
	void Matrix::Transpose()
	{
		*this = Matrix(
			_11, _21, _31, _41,
			_12, _22, _32, _42,
			_13, _23, _33, _43,
			_14, _24, _34, _44);
	}

	//矩阵对应行列式	
	/************************************************************************/
	/* a11a22a33a44 - a11a22a34a43 - a11a23a32a44 + a11a23a34a42
	+ a11a24a32a43 - a11a24a33a42 - a12a21a33a44 + a12a21a34a43
	+ a12a23a31a44 - a12a23a34a41 - a12a24a31a43 + a12a24a33a41
	+ a13a21a32a44 - a13a21a34a42 - a13a22a31a44 + a13a22a34a41
	+ a13a24a31a42 - a13a24a32a41 - a14a21a32a43 + a14a21a33a42
	+ a14a22a31a43 - a14a22a33a41 - a14a23a31a42 + a14a23a32a41                                                                     */
	/************************************************************************/
	real Matrix::det()const
	{
		real result =
			_11*_22*_33*_44 - _11*_22*_34*_43 -
			_11*_23*_32*_44 + _11*_23*_34*_42 +

			_11*_24*_32*_43 - _11*_24*_33*_42 -
			_12*_21*_33*_44 + _12*_21*_34*_43 +

			_12*_23*_31*_44 - _12*_23*_34*_41 -
			_12*_24*_31*_43 + _12*_24*_33*_41 +

			_13*_21*_32*_44 - _13*_21*_34*_42 -
			_13*_22*_31*_44 + _13*_22*_34*_41 +

			_13*_24*_31*_42 - _13*_24*_32*_41 -
			_14*_21*_32*_43 + _14*_21*_33*_42 +

			_14*_22*_31*_43 - _14*_22*_33*_41 -
			_14*_23*_31*_42 + _14*_23*_32*_41;

		return result;
	}

	//伴随矩阵中的每一项 3*3矩阵对应的行列式值
	real Matrix::MatrixAdjElem(
		real a1, real a2, real a3,
		real b1, real b2, real b3,
		real c1, real c2, real c3)const
	{
		return a1*(b2*c3 - c2*b3) - a2*(b1*c3 - c1*b3) + a3*(b1*c2 - c1*b2);
	}

	//伴随矩阵 代数余子式组成的矩阵的转置
	Matrix Matrix::adjugate()const
	{
		real a1 = MatrixAdjElem(_22, _23, _24, _32, _33, _34, _42, _43, _44);
		real a2 = MatrixAdjElem(_21, _23, _24, _31, _33, _34, _41, _43, _44);
		real a3 = MatrixAdjElem(_21, _22, _24, _31, _32, _34, _41, _42, _44);
		real a4 = MatrixAdjElem(_21, _22, _23, _31, _32, _33, _41, _42, _43);
		real b1 = MatrixAdjElem(_12, _13, _14, _32, _33, _34, _42, _43, _44);
		real b2 = MatrixAdjElem(_11, _13, _14, _31, _33, _34, _41, _43, _44);
		real b3 = MatrixAdjElem(_11, _12, _14, _31, _32, _34, _41, _42, _44);
		real b4 = MatrixAdjElem(_11, _12, _13, _31, _32, _33, _41, _42, _43);
		real c1 = MatrixAdjElem(_12, _13, _14, _22, _23, _24, _42, _43, _44);
		real c2 = MatrixAdjElem(_11, _13, _14, _21, _23, _24, _41, _43, _44);
		real c3 = MatrixAdjElem(_11, _12, _14, _21, _22, _24, _41, _42, _44);
		real c4 = MatrixAdjElem(_11, _12, _13, _21, _22, _23, _41, _42, _43);
		real d1 = MatrixAdjElem(_12, _13, _14, _22, _23, _24, _32, _33, _34);
		real d2 = MatrixAdjElem(_11, _13, _14, _21, _23, _24, _31, _33, _34);
		real d3 = MatrixAdjElem(_11, _12, _14, _21, _22, _24, _31, _32, _34);
		real d4 = MatrixAdjElem(_11, _12, _13, _21, _22, _23, _31, _32, _33);

		Matrix result(
			a1, -a2, a3, -a4,
			-b1, b2, -b3, b4,
			c1, -c2, c3, -c4,
			-d1, d2, -d3, d4
		);
		return result.transpose();
	}

	Matrix Matrix::inverse()const
	{
		real d = abs(det());
		Matrix adj = adjugate();
		Matrix inverse;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
			{
				inverse.m[i][j] = adj.m[i][j] / d;
			}
		return inverse;
	}
}
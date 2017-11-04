#include "Matrix.h"


namespace easym
{

	void Matrix::Identity()
	{
		_11 = 1.f; _12 = 0.f; _13 = 0.f; _14 = 0.f;
		_21 = 0.f; _22 = 1.f; _23 = 0.f; _24 = 0.f;
		_31 = 0.f; _32 = 0.f; _33 = 1.f; _34 = 0.f;
		_41 = 0.f; _42 = 0.f; _43 = 0.f; _44 = 1.f;
	}
	void Matrix::Zero()
	{
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				m[i][j] = 0.0f;
	}
	bool Matrix::operator==(const Matrix& other) const
	{
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				if (equal(m[i][j],other.m[i][j]))
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

	inline Vector4 operator* (const Vector4& v, const Matrix& m)
	{
		return Vector4(v.x * m._11 + v.y * m._21 + v.z * m._31 + v.w * m._41,
			v.x * m._12 + v.y * m._22 + v.z * m._32 + v.w * m._42,
			v.x * m._13 + v.y * m._23 + v.z * m._33 + v.w * m._43,
			v.x * m._14 + v.y * m._24 + v.z * m._34 + v.w * m._44);
	}

	//矩阵转置
	Matrix Matrix::transpose(const Matrix& mat)const
	{
		return Matrix(mat._11, mat._21, mat._31, mat._41,
			mat._12, mat._22, mat._32, mat._42,
			mat._13, mat._23, mat._33, mat._43,
			mat._14, mat._24, mat._34, mat._44);
	}
	void Matrix::Transpose(const Matrix& mat)
	{
		*this = Matrix(mat._11, mat._21, mat._31, mat._41,
			mat._12, mat._22, mat._32, mat._42,
			mat._13, mat._23, mat._33, mat._43,
			mat._14, mat._24, mat._34, mat._44);
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
	float Matrix::det(const Matrix& mat)const
	{
		float result =
			mat._11*mat._22*mat._33*mat._44 - mat._11*mat._22*mat._34*mat._43 -
			mat._11*mat._23*mat._32*mat._44 + mat._11*mat._23*mat._34*mat._42 +

			mat._11*mat._24*mat._32*mat._43 - mat._11*mat._24*mat._33*mat._42 -
			mat._12*mat._21*mat._33*mat._44 + mat._12*mat._21*mat._34*mat._43 +

			mat._12*mat._23*mat._31*mat._44 - mat._12*mat._23*mat._34*mat._41 -
			mat._12*mat._24*mat._31*mat._43 + mat._12*mat._24*mat._33*mat._41 +

			mat._13*mat._21*mat._32*mat._44 - mat._13*mat._21*mat._34*mat._42 -
			mat._13*mat._22*mat._31*mat._44 + mat._13*mat._22*mat._34*mat._41 +

			mat._13*mat._24*mat._31*mat._42 - mat._13*mat._24*mat._32*mat._41 -
			mat._14*mat._21*mat._32*mat._43 + mat._14*mat._21*mat._33*mat._42 +

			mat._14*mat._22*mat._31*mat._43 - mat._14*mat._22*mat._33*mat._41 -
			mat._14*mat._23*mat._31*mat._42 + mat._14*mat._23*mat._32*mat._41;

		return result;
	}

	//伴随矩阵中的每一项 3*3矩阵对应的行列式值
	float Matrix::MatrixAdjElem(
		float a1, float a2, float a3,
		float b1, float b2, float b3,
		float c1, float c2, float c3)const
	{
		return a1*(b2*c3 - c2*b3) - a2*(b1*c3 - c1*b3) + a3*(b1*c2 - c1*b2);
	}

	//伴随矩阵 代数余子式组成的矩阵的转置
	Matrix Matrix::adjugate(const Matrix& mat)const
	{
		float a1 = MatrixAdjElem(mat._22, mat._23, mat._24, mat._32, mat._33, mat._34, mat._42, mat._43, mat._44);
		float a2 = MatrixAdjElem(mat._21, mat._23, mat._24, mat._31, mat._33, mat._34, mat._41, mat._43, mat._44);
		float a3 = MatrixAdjElem(mat._21, mat._22, mat._24, mat._31, mat._32, mat._34, mat._41, mat._42, mat._44);
		float a4 = MatrixAdjElem(mat._21, mat._22, mat._23, mat._31, mat._32, mat._33, mat._41, mat._42, mat._43);
		float b1 = MatrixAdjElem(mat._12, mat._13, mat._14, mat._32, mat._33, mat._34, mat._42, mat._43, mat._44);
		float b2 = MatrixAdjElem(mat._11, mat._13, mat._14, mat._31, mat._33, mat._34, mat._41, mat._43, mat._44);
		float b3 = MatrixAdjElem(mat._11, mat._12, mat._14, mat._31, mat._32, mat._34, mat._41, mat._42, mat._44);
		float b4 = MatrixAdjElem(mat._11, mat._12, mat._13, mat._31, mat._32, mat._33, mat._41, mat._42, mat._43);
		float c1 = MatrixAdjElem(mat._12, mat._13, mat._14, mat._22, mat._23, mat._24, mat._42, mat._43, mat._44);
		float c2 = MatrixAdjElem(mat._11, mat._13, mat._14, mat._21, mat._23, mat._24, mat._41, mat._43, mat._44);
		float c3 = MatrixAdjElem(mat._11, mat._12, mat._14, mat._21, mat._22, mat._24, mat._41, mat._42, mat._44);
		float c4 = MatrixAdjElem(mat._11, mat._12, mat._13, mat._21, mat._22, mat._23, mat._41, mat._42, mat._43);
		float d1 = MatrixAdjElem(mat._12, mat._13, mat._14, mat._22, mat._23, mat._24, mat._32, mat._33, mat._34);
		float d2 = MatrixAdjElem(mat._11, mat._13, mat._14, mat._21, mat._23, mat._24, mat._31, mat._33, mat._34);
		float d3 = MatrixAdjElem(mat._11, mat._12, mat._14, mat._21, mat._22, mat._24, mat._31, mat._32, mat._34);
		float d4 = MatrixAdjElem(mat._11, mat._12, mat._13, mat._21, mat._22, mat._23, mat._31, mat._32, mat._33);

		Matrix result(
			a1, -a2, a3, -a4,
			-b1, b2, -b3, b4,
			c1, -c2, c3, -c4,
			-d1, d2, -d3, d4
		);
		return transpose(result);
	}

	Matrix Matrix::inverse(const Matrix& mat)const
	{
		float d = abs(det(mat));
		Matrix adj = adjugate(mat);
		Matrix inverse;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
			{
				inverse.m[i][j] = adj.m[i][j] / d;
			}
		return inverse;
	}
}
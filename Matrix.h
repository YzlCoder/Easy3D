#pragma once
#include "Vector.h"

namespace easym
{
	class Matrix
	{
	public:
		union
		{
			float m[4][4];
			struct
			{
				float _11; float _12; float _13; float _14;
				float _21; float _22; float _23; float _24;
				float _31; float _32; float _33; float _34;
				float _41; float _42; float _43; float _44;
			};
		};

	public:
		Matrix() {
			_11 = 0; _12 = 0; _13 = 0; _14 = 0;
			_21 = 0; _22 = 0; _23 = 0; _24 = 0;
			_31 = 0; _32 = 0; _33 = 0; _34 = 0;
			_41 = 0; _42 = 0; _43 = 0; _44 = 0;
		}
		Matrix(float a1, float a2, float a3, float a4,
			float b1, float b2, float b3, float b4,
			float c1, float c2, float c3, float c4,
			float d1, float d2, float d3, float d4)
		{
			_11 = a1; _12 = a2; _13 = a3; _14 = a4;
			_21 = b1; _22 = b2; _23 = b3; _24 = b4;
			_31 = c1; _32 = c2; _33 = c3; _34 = c4;
			_41 = d1; _42 = d2; _43 = d3; _44 = d4;
		}

		Matrix(const Matrix& rhs)
		{
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 4; ++j)
					m[i][j] = rhs.m[i][j];
		}

		Matrix& operator= (const Matrix& rhs)
		{
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 4; ++j)
					m[i][j] = rhs.m[i][j];
			return *this;
		}

		void Identity();
		void Zero();
		bool operator== (const Matrix& rhs) const;
		Matrix operator+ (const Matrix& rhs) const;
		Matrix operator- (const Matrix& rhs) const;
		Matrix operator* (const Matrix& rhs) const;

		//转置
		Matrix transpose(const Matrix& mat)const;
		void Transpose(const Matrix& mat);

		//4*4行列式值
		float det(const Matrix& mat)const;

		//3*3行列式值
		float MatrixAdjElem(
			float a1, float a2, float a3,
			float b1, float b2, float b3,
			float c1, float c2, float c3)const;

		//伴随矩阵 代数余子式组成的矩阵的转置
		Matrix adjugate(const Matrix& mat)const;

		//逆矩阵 = 伴随矩阵/(行列式值的绝对值)
		Matrix inverse(const Matrix& mat)const;

	};

	Vector4 operator* (const Vector4& v, const Matrix& m);

}



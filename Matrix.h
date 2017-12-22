#pragma once
#include "MathDefine.h"
#include "Vector.h"

namespace easym
{
	class Matrix
	{
	public:
		union
		{
			real m[4][4];
			struct
			{
				real _11; real _12; real _13; real _14;
				real _21; real _22; real _23; real _24;
				real _31; real _32; real _33; real _34;
				real _41; real _42; real _43; real _44;
			};
		};

	public:
		Matrix() {
			_11 = 1; _12 = 0; _13 = 0; _14 = 0;
			_21 = 0; _22 = 1; _23 = 0; _24 = 0;
			_31 = 0; _32 = 0; _33 = 1; _34 = 0;
			_41 = 0; _42 = 0; _43 = 0; _44 = 1;
		}
		Matrix(real a1, real a2, real a3, real a4,
			real b1, real b2, real b3, real b4,
			real c1, real c2, real c3, real c4,
			real d1, real d2, real d3, real d4)
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
		Matrix transpose()const;
		void Transpose();

		//4*4行列式值
		real det()const;

		//3*3行列式值
		real MatrixAdjElem(
			real a1, real a2, real a3,
			real b1, real b2, real b3,
			real c1, real c2, real c3)const;

		//伴随矩阵 代数余子式组成的矩阵的转置
		Matrix adjugate()const;

		//逆矩阵 = 伴随矩阵/(行列式值的绝对值)
		Matrix inverse()const;

#ifdef DEBUG
		void DebugLog() const
		{
			std::cout << "|" << _11 << ", " << _12 << ", " << _13 << ", " << _14 << "|" << std::endl;
			std::cout << "|" << _21 << ", " << _22 << ", " << _23 << ", " << _24 << "|" << std::endl;
			std::cout << "|" << _31 << ", " << _32 << ", " << _33 << ", " << _34 << "|" << std::endl;
			std::cout << "|" << _41 << ", " << _42 << ", " << _43 << ", " << _44 << "|" << std::endl;
		}
#endif // DEBUG

	};

	Vector4 operator* (const Vector4& v, const Matrix& m);

}



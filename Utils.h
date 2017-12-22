#pragma once
#include "MathDefine.h"
#include "Matrix.h"

//左手坐标系
namespace easym
{
	inline real Clamp(real x, real mi, real mx)
	{
		return max(mi, min(x, mx));
	}

	//缩放矩阵
	Matrix scale(const Vector3& s);
	Matrix scale(const Vector3& s, const Matrix& mat);

	//平移矩阵
	Matrix translate(const Vector3& v);
	Matrix translate(const Vector3& v, const Matrix& mat);

	//旋转矩阵
	Matrix rotateX(real angle);
	Matrix rotateY(real angle);
	Matrix rotateZ(real angle);
	Matrix rotate(const Vector3& axis,real angle);

	//视野矩阵
	Matrix lookat(Vector3 eyePos, Vector3 lookAt, Vector3 up);

	//投影矩阵
	Matrix perspective(real fovy, real aspect, real zNear, real zFar);
	Matrix perspective(real fov, real width, real height, real zNear, real zFar);
	Matrix ortho(real left, real right, real bottom, real top, real zNear, real zFar);

	//视口矩阵
	Matrix viewport(int left, int top, int width, int heigt);

	//颜色to unit
	UINT color2Uint(const Vector3& color);
}

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
	inline Matrix scale(const Vector3& s);
	inline Matrix scale(const Vector3& s, const Matrix& mat);

	//平移矩阵
	inline Matrix translate(const Vector3& v);
	inline Matrix translate(const Vector3& v, const Matrix& mat);

	//旋转矩阵
	inline Matrix rotateX(real angle);
	inline Matrix rotateY(real angle);
	inline Matrix rotateZ(real angle);
	inline Matrix rotate(const Vector3& axis,real angle);

	//视野矩阵
	inline Matrix lookat(Vector3 eyePos, Vector3 lookAt, Vector3 up);

	//投影矩阵
	inline Matrix perspective(real fovy, real aspect, real zNear, real zFar);
	inline Matrix perspective(real fov, real width, real height, real zNear, real zFar);
	inline Matrix ortho(real left, real right, real bottom, real top, real zNear, real zFar);

	//颜色to unit
	inline unsigned int color2Uint(const Vector3& color);
}

#pragma once
#include "MathDefine.h"
#include "Matrix.h"

//��������ϵ
namespace easym
{

	inline real Clamp(real x, real mi, real mx)
	{
		return max(mi, min(x, mx));
	}

	//���ž���
	inline Matrix scale(const Vector3& s);
	inline Matrix scale(const Vector3& s, const Matrix& mat);

	//ƽ�ƾ���
	inline Matrix translate(const Vector3& v);
	inline Matrix translate(const Vector3& v, const Matrix& mat);

	//��ת����
	inline Matrix rotateX(real angle);
	inline Matrix rotateY(real angle);
	inline Matrix rotateZ(real angle);
	inline Matrix rotate(const Vector3& axis,real angle);

	//��Ұ����
	inline Matrix lookat(Vector3 eyePos, Vector3 lookAt, Vector3 up);

	//ͶӰ����
	inline Matrix perspective(real fovy, real aspect, real zNear, real zFar);
	inline Matrix perspective(real fov, real width, real height, real zNear, real zFar);
	inline Matrix ortho(real left, real right, real bottom, real top, real zNear, real zFar);

	//��ɫto unit
	inline unsigned int color2Uint(const Vector3& color);
}

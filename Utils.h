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
	Matrix scale(const Vector3& s);
	Matrix scale(const Vector3& s, const Matrix& mat);

	//ƽ�ƾ���
	Matrix translate(const Vector3& v);
	Matrix translate(const Vector3& v, const Matrix& mat);

	//��ת����
	Matrix rotateX(real angle);
	Matrix rotateY(real angle);
	Matrix rotateZ(real angle);
	Matrix rotate(const Vector3& axis,real angle);

	//��Ұ����
	Matrix lookat(Vector3 eyePos, Vector3 lookAt, Vector3 up);

	//ͶӰ����
	Matrix perspective(real fovy, real aspect, real zNear, real zFar);
	Matrix perspective(real fov, real width, real height, real zNear, real zFar);
	Matrix ortho(real left, real right, real bottom, real top, real zNear, real zFar);

	//�ӿھ���
	Matrix viewport(int left, int top, int width, int heigt);

	//��ɫto unit
	UINT color2Uint(const Vector3& color);
}

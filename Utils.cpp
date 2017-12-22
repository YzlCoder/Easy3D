#include "Utils.h"


namespace easym
{
	//Àı∑≈æÿ’Û
	Matrix scale(const Vector3& s)
	{
		return Matrix(
			s.x, 0, 0, 0,
			0, s.y, 0, 0,
			0, 0, s.z, 0,
			0, 0, 0, 1
		);
	}

	Matrix scale(const Vector3& s, const Matrix& mat)
	{
		return mat * scale(s);
	}

	//∆Ω“∆æÿ’Û
	Matrix translate(const Vector3& v)
	{
		return Matrix(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			v.x, v.y, v.z, 1
		);
	}

	Matrix translate(const Vector3& v, const Matrix& mat)
	{
		return mat * translate(v);
	}

	Matrix rotateX(real angle)
	{
		return Matrix(
			1, 0, 0, 0,
			0, cos(angle), sin(angle), 0,
			0, -sin(angle), cos(angle), 0,
			0, 0, 0, 1
		);
	}

	Matrix rotateY(real angle)
	{
		return Matrix(
			cos(angle), 0, -sin(angle), 0,
			0, 1, 0, 0,
			sin(angle), 0, cos(angle), 0,
			0, 0, 0, 1
		);
	}

	Matrix rotateZ(real angle)
	{
		return Matrix(
			cos(angle), sin(angle), 0, 0,
			-sin(angle), cos(angle), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	}

	Matrix rotate(const Vector3& axis, real angle)
	{
		return Matrix(
			axis.x * axis.x * (1 - cos(angle)) + cos(angle), axis.x * axis.y * (1 - cos(angle)) + axis.z * sin(angle), axis.x * axis.z * (1 - cos(angle)) - axis.y * sin(angle), 0,
			axis.x * axis.y * (1 - cos(angle)) - axis.z * sin(angle), axis.y * axis.y * (1 - cos(angle)) + cos(angle), axis.y * axis.z * (1 - cos(angle)) + axis.z * sin(angle), 0,
			axis.x * axis.z * (1 - cos(angle)) + axis.y * sin(angle), axis.y * axis.z * (1 - cos(angle)) - axis.x * sin(angle), axis.z * axis.z * (1 - cos(angle)) + cos(angle), 0,
			0, 0, 0, 1
		);
	}

	Matrix lookat(Vector3 eyePos, Vector3 lookAt, Vector3 up)
	{
		Vector3 zaxis = lookAt - eyePos;
		zaxis.Normalize();
		Vector3 xaxis = Cross(up, zaxis).normalize();
		Vector3 yaxis = Cross(zaxis, xaxis);

		return Matrix(
			xaxis.x, yaxis.x, zaxis.x, 0,
			xaxis.y, yaxis.y, zaxis.y, 0,
			xaxis.z, yaxis.z, zaxis.z, 0,
			- Dot(xaxis, eyePos), - Dot(yaxis, eyePos), - Dot(zaxis, eyePos), 1
		);
	}

	Matrix perspective(real fovy, real aspect, real zNear, real zFar)
	{
		assert(abs(aspect - std::numeric_limits<real>::epsilon()) > static_cast<real>(0));

		Matrix mat;
		mat.Zero();
		real height = cos(fovy * static_cast<real>(0.5)) / sin(fovy * static_cast<real>(0.5));
		mat._11 = height / aspect;
		mat._22 = height;
		mat._33 = zFar / (zFar - zNear);
		mat._34 = static_cast<real>(1);
		mat._43 = (zNear * zFar) / (zNear - zFar);
		return mat;
	}

	Matrix perspective(real fov, real width, real height, real zNear, real zFar)
	{
		assert(width > static_cast<real>(0));
		assert(height > static_cast<real>(0));
		assert(fov > static_cast<real>(0));

		real const rad = fov;
		real const h = cos(static_cast<real>(0.5) * rad) / sin(static_cast<real>(0.5) * rad);
		real const w = h * height / width;

		Matrix mat;
		mat.Zero();

		mat._11 = w;
		mat._22 = h;
		mat._34 = static_cast<real>(1);

		mat._33 = zFar / (zFar - zNear);
		mat._42 = -(zFar * zNear) / (zFar - zNear);

		return mat;
	}

	Matrix ortho(real left, real right, real bottom, real top, real zNear, real zFar)
	{
		Matrix mat;
		mat._11 = static_cast<real>(2) / (right - left);
		mat._22 = static_cast<real>(2) / (top - bottom);
		mat._41 = -(right + left) / (right - left);
		mat._42 = -(top + bottom) / (top - bottom);

		mat._33 = static_cast<real>(1) / (zFar - zNear);
		mat._43 = -zNear / (zFar - zNear);	

		return mat;
	}


	Matrix viewport(int left, int top, int width, int heigt)
	{
		return Matrix(
			width / 2, 0, 0, 0,
			0, -heigt / 2, 0, 0,
			0, 0, 1, 0,
			width / 2 + left, heigt / 2 + top, 0, 1
		);
	}


	UINT color2Uint(const Vector3& color)
	{
		unsigned char red = static_cast<unsigned char>(255 * color.x)/*  color.w*/;
		unsigned char green = static_cast<unsigned char>(255 * color.y)/* color.w*/;
		unsigned char blue = static_cast<unsigned char>(255 * color.z) /* color.w*/;
		return (unsigned int)((unsigned char)blue | (unsigned short)((unsigned char)green << 8) | (unsigned long)((unsigned char)red << 16));
	}
}


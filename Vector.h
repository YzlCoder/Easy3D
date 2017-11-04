#pragma once
#include "define.h"

namespace easym
{

	class Vector2
	{
	public:
		//constructed destructor
		Vector2() :x(0), y(0) {}
		Vector2(float _x, float _y) :x(_x), y(_y) {}
		Vector2(const Vector2& other) :x(other.x), y(other.y) {}
		~Vector2() {}

		//operator
		Vector2& operator=(const Vector2& other)
		{
			x = other.x;
			y = other.y;
			return *this;
		}
		bool operator==(const Vector2& other)
		{
			return equal(x, other.x) && equal(y, other.y);
		}
		bool operator!=(const Vector2& other)
		{
			return !(*this == other);
		}
		Vector2 operator+(const Vector2& other)const
		{
			return Vector2(x + other.x, y + other.y);
		}
		Vector2 operator-(const Vector2& other)const
		{
			return Vector2(x - other.x, y - other.y);
		}
		Vector2 operator-()const
		{
			return Vector2(-x, -y);
		}
		Vector2 operator*(float a)const
		{
			return Vector2(a * x, a * y);
		}
		Vector2 operator/(float a)const
		{
			float oneOverA = 1.0f / a;
			return Vector2(oneOverA * x, oneOverA * y);
		}
		Vector2& operator+=(const Vector2& other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		Vector2& operator-=(const Vector2& other)
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
		Vector2& operator*=(float a)
		{
			x *= a;
			y *= a;
			return *this;
		}
		Vector2& operator/=(float a)
		{
			float oneOverA = 1.0f / a;
			x *= oneOverA;
			y *= oneOverA;
			return *this;
		}

		//member func
		float magnitude()const
		{
			return sqrt(x*x + y*y);
		}
		float sqrMagnitude()const
		{
			return x*x + y*y;
		}
		Vector2 normalize()const
		{
			float len = magnitude();
			if (len > 0.0f)
			{
				float oneOverLen = 1.0f / len;
				return Vector2(x * oneOverLen, y * oneOverLen);
			}
			return zero;
		}
		void Normalize()
		{
			float len = magnitude();
			if (len > 0.0f)
			{
				float oneOverLen = 1.0f / len;
				x *= oneOverLen;
				y *= oneOverLen;
			}
		}

		//member data
		static const Vector2 left;
		static const Vector2 right;
		static const Vector2 up;
		static const Vector2 down;
		static const Vector2 zero;
		static const Vector2 one;
		float x, y;
	};


	class Vector3
	{
	public:
		//constructed destructor
		Vector3() :x(0), y(0), z(0) {}
		Vector3(float _x, float _y, float _z) :x(_x), y(_y), z(_z) {}
		Vector3(const Vector2 v2) : x(v2.x), y(v2.y), z(0) {}
		Vector3(const Vector3& other) :x(other.x), y(other.y), z(other.z) {}
		~Vector3() {}

		//operator
		Vector3& operator=(const Vector3& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			return *this;
		}
		bool operator==(const Vector3& other)
		{
			return equal(x, other.x) && equal(y, other.y) && equal(z, other.z);
		}
		bool operator!=(const Vector3& other)
		{
			return !(*this == other);
		}
		Vector3 operator+(const Vector3& other)const
		{
			return Vector3(x + other.x, y + other.y, z + other.z);
		}
		Vector3 operator-(const Vector3& other)const
		{
			return Vector3(x - other.x, y - other.y, z - other.z);
		}
		Vector3 operator-()const
		{
			return Vector3(-x, -y, -z);
		}
		Vector3 operator*(float a)const
		{
			return Vector3(a * x, a * y, a * z);
		}
		Vector3 operator/(float a)const
		{
			float oneOverA = 1.0f / a;
			return Vector3(oneOverA * x, oneOverA * y, oneOverA * z);
		}
		Vector3& operator+=(const Vector3& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}
		Vector3& operator-=(const Vector3& other)
		{
			x -= other.x;
			y -= other.y;
			z += other.z;
			return *this;
		}
		Vector3& operator*=(float a)
		{
			x *= a;
			y *= a;
			z *= a;
			return *this;
		}
		Vector3& operator/=(float a)
		{
			float oneOverA = 1.0f / a;
			x *= oneOverA;
			y *= oneOverA;
			z *= oneOverA;
			return *this;
		}

		//member func
		float magnitude()const
		{
			return sqrt(x*x + y*y + z*z);
		}
		float sqrMagnitude()const
		{
			return x*x + y*y + z*z;;
		}
		Vector3 normalize()const
		{
			float len = magnitude();
			if (len > 0.0f)
			{
				float oneOverLen = 1.0f / len;
				return Vector3(x * oneOverLen, y * oneOverLen, z * oneOverLen);
			}
			return zero;
		}
		void Normalize()
		{
			float len = magnitude();
			if (len > 0.0f)
			{
				float oneOverLen = 1.0f / len;
				x *= oneOverLen;
				y *= oneOverLen;
				z *= oneOverLen;
			}
		}

		//member data
		static const Vector3 left;
		static const Vector3 right;
		static const Vector3 up;
		static const Vector3 down;
		static const Vector3 forward;
		static const Vector3 back;
		static const Vector3 zero;
		static const Vector3 one;
		float x, y, z;
	};


	class Vector4
	{
	public:
		//constructed destructor
		Vector4() :x(0), y(0), z(0) {}
		Vector4(float _x, float _y, float _z, float _w) :x(_x), y(_y), z(_z), w(_w) {}
		Vector4(const Vector2 v2) : x(v2.x), y(v2.y), z(0), w(0) {}
		Vector4(const Vector3 v3) : x(v3.x), y(v3.y), z(v3.z), w(0) {}
		Vector4(const Vector4& other) :x(other.x), y(other.y), z(other.z), w(other.w) {}
		~Vector4() {}

		//operator
		Vector4& operator=(const Vector4& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			w = other.w;
			return *this;
		}
		bool operator==(const Vector4& other)
		{
			return equal(x, other.x) && equal(y, other.y) && equal(z, other.z) && equal(w, other.w);
		}
		bool operator!=(const Vector4& other)
		{
			return !(*this == other);
		}
		Vector4 operator+(const Vector4& other)const
		{
			return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
		}
		Vector4 operator-(const Vector4& other)const
		{
			return Vector4(x - other.x, y - other.y, z - other.z, w + other.w);
		}
		Vector4 operator-()const
		{
			return Vector4(-x, -y, -z, -w);
		}
		Vector4 operator*(float a)const
		{
			return Vector4(a * x, a * y, a * z, a * w);
		}
		Vector4 operator/(float a)const
		{
			float oneOverA = 1.0f / a;
			return Vector4(oneOverA * x, oneOverA * y, oneOverA * z, oneOverA * z);
		}
		Vector4& operator+=(const Vector4& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return *this;
		}
		Vector4& operator-=(const Vector4& other)
		{
			x -= other.x;
			y -= other.y;
			z += other.z;
			w += other.w;
			return *this;
		}
		Vector4& operator*=(float a)
		{
			x *= a;
			y *= a;
			z *= a;
			w *= a;
			return *this;
		}
		Vector4& operator/=(float a)
		{
			float oneOverA = 1.0f / a;
			x *= oneOverA;
			y *= oneOverA;
			z *= oneOverA;
			w *= oneOverA;
			return *this;
		}

		float x, y, z, w;
	};

	float Dot(const Vector2&, const Vector2&);
	float Dot(const Vector3&, const Vector3&);

	Vector2 Cross(const Vector2&, const Vector2&);
	Vector3 Cross(const Vector3&, const Vector3&);

	float Angle(const Vector2&, const Vector2&);
	float Angle(const Vector3&, const Vector3&);

	float Distance(const Vector2&, const Vector2&);
	float Distance(const Vector3&, const Vector3&);

	Vector2 Lerp(const Vector2&, const Vector2&, float t);
	Vector3 Lerp(const Vector3&, const Vector3&, float t);

	Vector2 Reflect(const Vector2&, const Vector2&);
	Vector3 Reflect(const Vector3&, const Vector3&);
}

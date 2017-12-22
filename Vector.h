#pragma once
#include "MathDefine.h"

namespace easym
{

	class Vector2
	{
	public:
		//constructed destructor
		Vector2() :x(0), y(0) {}
		Vector2(real _x, real _y) :x(_x), y(_y) {}
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
		Vector2 operator*(const Vector2& other)const
		{
			return Vector2(x * other.x, y * other.y);
		}
		Vector2 operator*(real a)const
		{
			return Vector2(a * x, a * y);
		}
		Vector2 operator/(real a)const
		{
			real oneOverA = 1.0f / a;
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
		Vector2& operator*=(real a)
		{
			x *= a;
			y *= a;
			return *this;
		}
		Vector2& operator/=(real a)
		{
			real oneOverA = 1.0f / a;
			x *= oneOverA;
			y *= oneOverA;
			return *this;
		}

		//member func
		real magnitude()const
		{
			return sqrt(x*x + y*y);
		}
		real sqrMagnitude()const
		{
			return x*x + y*y;
		}
		Vector2 normalize()const
		{
			real len = magnitude();
			if (len > 0.0f)
			{
				real oneOverLen = 1.0f / len;
				return Vector2(x * oneOverLen, y * oneOverLen);
			}
			return zero;
		}
		void Normalize()
		{
			real len = magnitude();
			if (len > 0.0f)
			{
				real oneOverLen = 1.0f / len;
				x *= oneOverLen;
				y *= oneOverLen;
			}
		}

#ifdef DEBUG
		void DebugLog() const
		{
			std::cout << "(" << x << ", " << y << ")" << std::endl;
		}
#endif // DEBUG

		//member data
		static const Vector2 left;
		static const Vector2 right;
		static const Vector2 up;
		static const Vector2 down;
		static const Vector2 zero;
		static const Vector2 one;

		union
		{
			struct
			{
				real x, y;
			};
			struct 
			{
				real u, v;
			};
		};
	};


	class Vector3
	{
	public:
		//constructed destructor
		Vector3() :x(0), y(0), z(0) {}
		Vector3(real _x, real _y, real _z) :x(_x), y(_y), z(_z) {}
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
		Vector3 operator*(Vector3 other)const
		{
			return Vector3(x * other.x, y * other.y, z * other.z);
		}
		Vector3 operator*(real a)const
		{
			return Vector3(a * x, a * y, a * z);
		}
		Vector3 operator/(real a)const
		{
			real oneOverA = 1.0f / a;
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
		Vector3& operator*=(real a)
		{
			x *= a;
			y *= a;
			z *= a;
			return *this;
		}
		Vector3& operator/=(real a)
		{
			real oneOverA = 1.0f / a;
			x *= oneOverA;
			y *= oneOverA;
			z *= oneOverA;
			return *this;
		}
		operator Vector2()const
		{
			return Vector2(x, y);
		}

		//member func
		real magnitude()const
		{
			return sqrt(x*x + y*y + z*z);
		}
		real sqrMagnitude()const
		{
			return x*x + y*y + z*z;;
		}
		Vector3 normalize()const
		{
			real len = magnitude();
			if (len > 0.0f)
			{
				real oneOverLen = 1.0f / len;
				return Vector3(x * oneOverLen, y * oneOverLen, z * oneOverLen);
			}
			return zero;
		}
		void Normalize()
		{
			real len = magnitude();
			if (len > 0.0f && !equal(len, 1.0f))
			{
				real oneOverLen = 1.0f / len;
				x *= oneOverLen;
				y *= oneOverLen;
				z *= oneOverLen;
			}
		}

#ifdef DEBUG
		void DebugLog() const
		{
			std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
		}
#endif // DEBUG

		//member data
		static const Vector3 left;
		static const Vector3 right;
		static const Vector3 up;
		static const Vector3 down;
		static const Vector3 forward;
		static const Vector3 back;
		static const Vector3 zero;
		static const Vector3 one;
		real x, y, z;
	};


	class Vector4
	{
	public:
		//constructed destructor
		Vector4() :x(0), y(0), z(0), w(0) {}
		Vector4(real _x, real _y, real _z, real _w) :x(_x), y(_y), z(_z), w(_w) {}
		Vector4(const Vector2 v2) : x(v2.x), y(v2.y), z(0), w(0) {}
		Vector4(const Vector3 v3) : x(v3.x), y(v3.y), z(v3.z), w(1) {}
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
		Vector4 operator*(const Vector4& other)const
		{
			return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
		}
		Vector4 operator*(real a)const
		{
			return Vector4(a * x, a * y, a * z, a * w);
		}
		Vector4 operator/(real a)const
		{
			real oneOverA = 1.0f / a;
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
		Vector4& operator*=(real a)
		{
			x *= a;
			y *= a;
			z *= a;
			w *= a;
			return *this;
		}
		Vector4& operator/=(real a)
		{
			real oneOverA = 1.0f / a;
			x *= oneOverA;
			y *= oneOverA;
			z *= oneOverA;
			w *= oneOverA;
			return *this;
		}
		operator Vector3()const
		{
			return Vector3(x, y, z);
		}

#ifdef DEBUG
		void DebugLog() const
		{
			std::cout << "(" << x << ", " << y << ", " << z << ", " << w << ")" << std::endl;
		}
#endif // DEBUG

		union
		{
			struct
			{
				real x, y, z, w;
			};
			struct
			{
				real u, v, s, t;
			};
		};

	};

	real Dot(const Vector2&, const Vector2&);
	real Dot(const Vector3&, const Vector3&);

	Vector2 Cross(const Vector2&, const Vector2&);
	Vector3 Cross(const Vector3&, const Vector3&);

	real Angle(const Vector2&, const Vector2&);
	real Angle(const Vector3&, const Vector3&);

	real Distance(const Vector2&, const Vector2&);
	real Distance(const Vector3&, const Vector3&);

	inline real Lerp(real mi, real mx, real t)
	{
		return mi + (mx - mi) * t;
	}
	Vector2 Lerp(const Vector2&, const Vector2&, real t);
	Vector3 Lerp(const Vector3&, const Vector3&, real t);
	Vector4 Lerp(const Vector4&, const Vector4&, real t);

	Vector2 Reflect(const Vector2&, const Vector2&);
	Vector3 Reflect(const Vector3&, const Vector3&);
}

#pragma once
#include "MathDefine.h"
#include "Vector.h"

namespace easym
{

	class Quaternion
	{
	public:
		Quaternion() :x(0), y(0), z(0), w(1) {}
		Quaternion(real _x, real _y, real _z, real _w) :x(_x), y(_y), z(_z), w(_w) {}
		Quaternion(Vector3 axis, real angle)
		{
			angle = radians(angle);
			axis.Normalize();
			real angleOver2 = angle * 0.5f;
			real sinAngle = sin(angleOver2);
			x = axis.x * sinAngle;
			y = axis.y * sinAngle;
			z = axis.z * sinAngle;
			w = cos(angleOver2);
		}
		~Quaternion() {}


		//opertor
		bool operator==(const Quaternion& other) const
		{
			return x == other.x && y == other.y && z == other.z && w == other.w;
		}

		bool operator!=(const Quaternion& other) const
		{
			return !(*this == other);
		}

		Quaternion operator-() const
		{
			return Quaternion(- x, - y, - z, - w);
		}

		Quaternion operator-(const Quaternion& other) const
		{
			return Quaternion(x - other.x, y - other.y, z - other.z, w - other.w);
		}

		Quaternion operator+(const Quaternion& other) const
		{
			return Quaternion(x + other.x, y + other.y, z + other.z, w + other.w);
		}

		Quaternion& operator=(const Quaternion& q)
		{
			x = q.x;
			y = q.y;
			z = q.z;
			w = q.w;
			return *this;
		}

		Quaternion operator*(const Quaternion& q)const
		{
			return Quaternion
			(
				w * q.x + x * q.w + y * q.z - z * q.y,
				w * q.y + y * q.w + z * q.x - x * q.z,
				w * q.z + z * q.w + x * q.y - y * q.x,
				w * q.w - x * q.x - y * q.y - z * q.z
			);
		}

		Vector3 operator*(const Vector3& v) const
		{
			Vector3 qvec(x, y, z);
			Vector3 uv = Cross(qvec, v);
			Vector3 uuv = Cross(qvec, uv);
			uv *= (2.0f * w);
			uuv *= 2.0f;
			return v + uv + uuv;
		}

		Vector3 ToEulerAngles()
		{
			real xangle = angles(asin(2 * w * x - 2 * y * z));

			if (equal(fabs(xangle), 90.0f))
			{
				return Vector3(
					xangle,
					angles(atan((w * y - x * z) / (0.5f - z * z - y * y))),
					0
				);
			}
			return Vector3(
				xangle,
				angles(atan((x * z + w * y) / (0.5f - x * x - y * y))),
				angles(atan((x * y + w * z) / (0.5f - x * x - z * z)))
			);
		}

		Quaternion inverse() const
		{
			return Quaternion(-x, -y, -z, w);
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

		Quaternion Normalize()const
		{
			real len = magnitude();
			if (len > 0.0f)
			{
				real oneOverLen = 1.0f / len;

				return Quaternion(x * oneOverLen,
					y * oneOverLen,
					z * oneOverLen,
					w * oneOverLen);
			}
			return ZERO;
		}

		inline void SetLookRotation(Vector3 forward, Vector3 upwords = Vector3(0, 1, 0))
		{
			*this = LookRotation(forward, upwords);
		}
		
		void ToAngleAxis(Vector3& axis, real& angle)const;

		friend inline real Dot(const Quaternion& a, const Quaternion& b);
		
		friend Quaternion FromToRotation(Vector3 fromDirection, Vector3 toDirection);
		
		friend Quaternion LookRotation(Vector3 forward, Vector3 upwords);

		friend Quaternion Slerp(Quaternion a, Quaternion b, real t);

		friend Quaternion SlerpUnclamped(Quaternion a, Quaternion b, real t);

		friend Quaternion Log(Quaternion q);

		friend Quaternion Exp(Quaternion q);

		friend Quaternion Pow(Quaternion q, real exp);

#ifdef DEBUG
		void DebugLog() const
		{
			std::cout << "(" << x << ", " << y << ", " << z << ", " << w << ")" << std::endl;
		}
#endif // DEBUG

private:
		//property
		real x, y, z, w;
		static const Quaternion ZERO, IDENTITY;
	};

	//µã³Ë
	inline real Dot(const Quaternion& a, const Quaternion& b)
	{
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
	}

	
	inline const Quaternion& AngleAxis(const Vector3& axis, real angle)
	{
		return Quaternion(axis, angle);
	}

	Quaternion FromToRotation(Vector3 fromDirection, Vector3 toDirection);

	Quaternion LookRotation(Vector3 forward, Vector3 upwords = Vector3(0,1,0));

	Quaternion Slerp(Quaternion q1, Quaternion q2, real t);

	Quaternion SlerpUnclamped(Quaternion q1, Quaternion q2, real t);

	Quaternion Log(Quaternion q);

	Quaternion Exp(Quaternion q);

	Quaternion Pow(Quaternion q, real exp);

	Quaternion Euler(real x, real y, real z);

}


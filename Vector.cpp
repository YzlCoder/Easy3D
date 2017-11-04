#include "Vector.h"


namespace easym
{
	const Vector2 Vector2::zero(0, 0);
	const Vector2 Vector2::one(1, 1);
	const Vector2 Vector2::left(-1, 0);
	const Vector2 Vector2::right(1, 0);
	const Vector2 Vector2::up(0, 1);
	const Vector2 Vector2::down(0, -1);


	const Vector3 left(-1, 0, 0);
	const Vector3 right(1, 0, 0);
	const Vector3 up(0, 1, 0);
	const Vector3 down(0, -1, 0);
	const Vector3 forward(0, 0, 1);
	const Vector3 back(0, 0, -1);
	const Vector3 one(1, 1, 1);
	const Vector3 zero(0, 0, 0);


	float Dot(const Vector2& a, const Vector2& b)
	{
		return a.x * b.x + a.y * b.y;
	}
	float Dot(const Vector3& a, const Vector3& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}
	Vector3 Cross(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x);
	}
	float Angle(const Vector2& a, const Vector2& b)
	{
		float dot = Dot(a, b);
		return acos(dot / a.magnitude() / b.magnitude());
	}
	float Angle(const Vector3& a, const Vector3& b)
	{
		float dot = Dot(a, b);
		return acos(dot / a.magnitude() / b.magnitude());
	}
	float Distance(const Vector2& a, const Vector2& b)
	{
		return (a - b).magnitude();
	}
	float Distance(const Vector3& a, const Vector3& b)
	{
		return (a - b).magnitude();
	}
	Vector2 Lerp(const Vector2& a, const Vector2& b, float t)
	{
		return Vector2(a.x + (b.x - a.x) * t,
			a.y + (b.y - a.y) * t);
	}
	Vector3 Lerp(const Vector3& a, const Vector3& b, float t)
	{
		return Vector3(a.x + (b.x - a.x) * t,
			a.y + (b.y - a.y) * t,
			a.z + (b.z - a.z) * t);
	}
	Vector2 Reflect(const Vector2& I, const Vector2& N)
	{
		float tmp = 2.f * Dot(N, I);
		return I - (N * tmp);
	}
	Vector3 Reflect(const Vector3& I, const Vector3& N)
	{
		float tmp = 2.f * Dot(N, I);
		return I - (N * tmp);
	}
}


#include "Quaternion.h"



namespace easym
{
	const Quaternion Quaternion::ZERO(0, 0, 0, 0);
	const Quaternion Quaternion::IDENTITY(1, 0, 0, 0);


	 void Quaternion::ToAngleAxis(Vector3& axis, real& angle)const
	{
		assert(w >= -1.0 && w <= 1.0);
		real angleOver2 = acos(w);
		real sinAngle = sin(angleOver2);
		real sinAngleOver1 = 1.0f / sinAngle;

		axis.x = x * sinAngleOver1;
		axis.y = y * sinAngleOver1;
		axis.z = z * sinAngleOver1;
		angle = angles(angleOver2 * 2);
	}

	Quaternion FromToRotation(Vector3 fromDirection, Vector3 toDirection)
	{
		fromDirection.Normalize();
		toDirection.Normalize();

		real cosTheta = Dot(fromDirection, toDirection);

		if (equal(cosTheta, -1.0))
		{
			Vector3 rotationAxis = Cross(Vector3(0.0f, 0.0f, 1.0f), fromDirection);
			if (rotationAxis.sqrMagnitude() < 0.01) // bad luck, they were parallel, try again!
			{
				rotationAxis = Cross(Vector3(0.0f, 0.0f, 1.0f), fromDirection);
			}
			rotationAxis.Normalize();
			return Quaternion(rotationAxis, 90.0f);
		}

		// Implementation from Stan Melax's Game Programming Gems 1 article
		Vector3 rotationAxis = Cross(fromDirection, toDirection);

		real s = sqrt((1 + cosTheta) * 2);
		real invs = 1 / s;

		return Quaternion(
			rotationAxis.x * invs,
			rotationAxis.y * invs,
			rotationAxis.z * invs,
			s * 0.5f
		);
	}

	Quaternion LookRotation(Vector3 forward, Vector3 upwords)
	{
		if (forward.sqrMagnitude() < 0.001f)
			return Quaternion();

		Vector3 right = Cross(forward, upwords);
		upwords = Cross(right, forward);

		Quaternion rot1 = FromToRotation(Vector3(0.0f, 0.0f, 1.0f), forward);
		Vector3 newUp = rot1 * Vector3(0.0f, 1.0f, 0.0f);
		Quaternion rot2 = FromToRotation(newUp, upwords);

	
		return rot2 * rot1; 
	}

	Quaternion Slerp(Quaternion q0, Quaternion q1, real t)
	{
		if (equal(t,0)) 
		{
			return q0;
		}
		
		if (equal(t, 1))
		{
			return q1;
		}

		real cosTheta = Dot(q0, q1);

		// q1 and q2 are already equal.
		// Force q2 just to be sure
		if (equal(cosTheta,1)) 
		{
			return q1;
		}

		real q1x = q1.x, q1y = q1.y, q1z = q1.z, q1w = q1.w;

		assert(cosTheta <= 1.0f);

		if (cosTheta < 0.0f)
		{
			q1x = -q1x;
			q1y = -q1y;
			q1z = -q1z;
			q1w = -q1w;
			cosTheta = -cosTheta;
		}
		
		real k0, k1;
		if (equal(cosTheta, 1))
		{
			k0 = 1.0f - t;
			k1 = t;
		}
		else
		{
			real sinTheta = sqrt(1.0f - cosTheta * cosTheta);
			real theta = atan2(sinTheta, cosTheta);
			real sinThetaOver1 = 1.0f / sinTheta;

			k0 = sin((1.0f - t) * theta) * sinThetaOver1;
			k1 = sin(t * theta) * sinThetaOver1;
		}

		Quaternion result;
		result.x = k0 * q0.x + k1 * q1x;
		result.y = k0 * q0.y + k1 * q1y;
		result.z = k0 * q0.z + k1 * q1z;
		result.w = k0 * q0.w + k1 * q1w;

		return result;
	}

	Quaternion SlerpUnclamped(Quaternion a, Quaternion b, real t)
	{
		Quaternion c = b * a.inverse();

		return Pow(c, t) * a;
	}

	Quaternion Pow(Quaternion q, real exp)
	{
		if (q.w < 0.9999f)
		{
			real alpha = acos(q.w);

			real newAlpha = alpha * exp;
			
			q.w = cos(newAlpha);

			real mult = sin(newAlpha) / sin(alpha);

			q.x *= mult;
			q.y *= mult;
			q.z *= mult;
		}
		return q;
	}

	Quaternion Log(Quaternion q)
	{
		assert(fabs(q.w) <= 1.0f);
		real fAngle = acos(q.w);
		real fSin = sin(fAngle);
		if (!equal(fSin, 0))
		{
			real fCoeff = fAngle / fSin;
			q.x *= fCoeff;
			q.y *= fCoeff;
			q.z *= fCoeff;
			q.w = 0;
		}
		return q;
	}

	Quaternion Exp(Quaternion q)
	{
		real fAngle(sqrt(q.x * q.x + q.y * q.y + q.z * q.z));
		real fSin = sin(fAngle);

		q.w = cos(fAngle);

		if (!equal(fSin,0))
		{
			real fCoeff = fSin / fAngle;
			q.x = fCoeff * q.x;
			q.y = fCoeff * q.y;
			q.z = fCoeff * q.z;
		}
		return q;
	}


	Quaternion Euler(real x, real y, real z)
	{
		x = radians(x);
		y = radians(y);
		z = radians(z);
		return Quaternion(0, sin(y / 2), 0, cos(y / 2)) * Quaternion(sin(x / 2), 0, 0, cos(x / 2)) * Quaternion(0, 0, sin(z / 2), cos(z / 2));

		/*real sinx2 = sin(x / 2), cosx2 = cos(x / 2);
		real siny2 = sin(y / 2), cosy2 = cos(y / 2);
		real sinz2 = sin(z / 2), cosz2 = cos(z / 2);

		return Quaternion(
			cosy2 * sinx2 * cosz2 + siny2 * cosx2 * sinz2,
			siny2 * cosx2 * cosz2 - cosy2 * sinx2 * sinz2,
			cosy2 * cosx2 * sinz2 - siny2 * sinx2 * cosz2,
			cosy2 * cosx2 * cosz2 + siny2 * sinx2 * sinz2
		);*/
	}



}

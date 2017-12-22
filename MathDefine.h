#pragma once
#include<cmath>
#include <assert.h>
#include <iostream>
#define _DOUBLE

namespace easym
{
//LOG
#ifdef DEBUG
#define  EASYM_LOG(obj) EasyM_Log(obj);
	template<typename T>
	void EasyM_Log(const T& obj)
	{
		obj.DebugLog();
	}

	template<typename T>
	void EasyM_Log(T* obj)
	{
		obj->DebugLog();
	}
#else
#define  EASYM_LOG(obj) 
#endif // DEBUG

#ifdef _DOUBLE
	typedef double real;
#else
	typedef float real;
#endif // _DOUBLE

	typedef unsigned int UINT;
	typedef unsigned short WORD;

	const real esp = 1e-5f;
	static real pi = static_cast<real>(3.1415926);

	inline bool equal(real a, real b)
	{
		return fabs(a - b) < esp;
	}


	inline real radians(real angle)
	{
		return angle * pi / 180.0f;
	}

	inline real angles(real radians)
	{
		return radians * 180.0f / pi;
	}

	template<typename T>
	T min(T a, T b)
	{
		return a > b ? b : a;
	}

	template<typename T>
	T max(T a, T b)
	{
		return a < b ? b : a;
	}

}


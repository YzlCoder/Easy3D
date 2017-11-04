#pragma once
#include<cmath>

const float esp = 1e-5;

inline bool equal(float a, float b)
{
	return fabs(a - b) < esp;
}
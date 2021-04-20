#pragma once

template<class T>
inline T& clamp(T& v, const T& lo, const T& hi)
{
	v = v > lo ? v : lo;
	v = v < hi ? v : hi;
	return v;
}

template<class T>
inline T square(const T &v)
{
	return v * v;
}
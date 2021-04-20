#pragma once

#define PI 3.14159265358979323846

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

class Vector2 
{
public:
	Vector2();
	Vector2(float x, float y);
	float x, y;

	void rotate(float angle);
	float dot(const Vector2& v2);
	Vector2& reflect(Vector2 &v2);
};

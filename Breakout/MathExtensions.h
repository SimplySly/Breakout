#pragma once

#define PI 3.14159265358979323846f

template<class T>
inline T& Clamp(T& v, const T& lo, const T& hi)
{
	v = v > lo ? v : lo;
	v = v < hi ? v : hi;
	return v;
}

template<class T>
inline T Square(const T &v)
{
	return v * v;
}

class Vector2 
{
public:
	Vector2();
	Vector2(float x, float y);
	float x, y;

	void Rotate(float angle);
	float Dot(const Vector2& v2);
	Vector2& Reflect(Vector2 &v2);
};

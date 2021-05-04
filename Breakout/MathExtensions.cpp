#include "MathExtensions.h"
#include <math.h>

Vector2::Vector2()
{
	x = y = 0.0f;
}

Vector2::Vector2(float x, float y) : x(x), y(y)
{
}

void Vector2::Rotate(float angle)
{
	x = x * cosf(angle) - y * sinf(angle);
	y = x * sinf(angle) + y * cosf(angle);
}

float Vector2::Dot(const Vector2& v)
{
	return x * v.x + y * v.y;
}

Vector2& Vector2::Reflect(Vector2& v)
{
	float k = Dot(v) / Dot(*this);

	v.x = -v.x + 2 * k * x;
	v.y = -v.y + 2 * k * y;

	return v;
}


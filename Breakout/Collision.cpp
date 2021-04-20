#include "Collision.h"
#include "MathExtensions.h"
#include <math.h>

using namespace std;

CollisionSide CircleAndRect(const Sprite& circle, const Sprite& rect)
{
	float collisionX, collisionY;

	collisionY = circle.centerY();

	clamp(collisionY, rect.top(), rect.bottom());

	if (circle.centerX() < rect.left())
	{
		collisionX = rect.left();

		if (CircleContainsDot(circle, collisionX, collisionY))
		{
			return COLLISION_LEFT;
		}
		else
		{
			return COLLISION_NONE;
		}
	}

	if (circle.centerX() > rect.right())
	{
		collisionX = rect.right();

		if (CircleContainsDot(circle, collisionX, collisionY))
		{
			return COLLISION_RIGHT;
		}
		else
		{
			return COLLISION_NONE;
		}
	}

	collisionX = circle.centerX();

	if (CircleContainsDot(circle, collisionX, collisionY))
	{
		if (circle.centerY() < rect.top())
		{
			return COLLISION_TOP;
		}
		else 
		{
			return COLLISION_BOTTOM;
		}
	}

	return COLLISION_NONE;
}

bool CircleContainsDot(Sprite circle, float x, float y)
{
	return square(circle.centerX() - x) + square(circle.centerY() - y) < square(circle.radius());
}

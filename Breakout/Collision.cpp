#include "Collision.h"
#include "MathExtensions.h"

using namespace std;

CollisionSide CircleAndRect(const Sprite& circle, const Sprite& rect)
{
	float collisionX, collisionY;

	collisionY = circle.centerY();

	clamp(collisionY, rect.top(), rect.bottom());

	if (circle.centerX() < rect.left())
	{
		collisionX = rect.left();
	}
	else if (circle.centerX() > rect.right())
	{
		collisionX = rect.right();
	}
	else
	{
		collisionX = circle.centerX();
	}

	collisionY = circle.centerY();
	clamp(collisionY, rect.top(), rect.bottom());

	if (CircleContainsDot(circle, collisionX, collisionY))
	{
		if (circle.centerX() < rect.left())
		{
			if (circle.centerY() < rect.top())
			{
				if (rect.left() - circle.centerX() < rect.top() - circle.centerY())
				{
					return COLLISION_TOP;
				}
				else
				{
					return COLLISION_LEFT;
				}
			}
			else if (circle.centerY() > rect.top())
			{
				if (rect.left() - circle.centerX() < circle.centerY() - rect.top())
				{
					return COLLISION_BOTTOM;
				}
				else
				{
					return COLLISION_LEFT;
				}
			}
			else
			{
				return COLLISION_LEFT;
			}
		}
		else if (circle.centerX() > rect.right())
		{
			if (circle.centerY() < rect.top())
			{
				if (circle.centerX() - rect.right() < rect.top() - circle.centerY())
				{
					return COLLISION_TOP;
				}
				else
				{
					return COLLISION_RIGHT;
				}
			}
			else if (circle.centerY() > rect.top())
			{
				if (circle.centerX() - rect.right() < circle.centerY() - rect.top())
				{
					return COLLISION_BOTTOM;
				}
				else
				{
					return COLLISION_RIGHT;
				}
			}
			else
			{
				return COLLISION_RIGHT;
			}
		}
		else
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
	}

	return COLLISION_NONE;
}



bool CircleContainsDot(Sprite circle, float x, float y)
{
	return square(circle.centerX() - x) + square(circle.centerY() - y) < square(circle.radius());
}

#include "Collision.h"
#include "MathExtensions.h"

using namespace std;

CollisionSide CircleAndRect(const Sprite& circle, const Sprite& rect)
{
	float collisionX, collisionY;

	collisionY = circle.CenterY();

	Clamp(collisionY, rect.Top(), rect.Bottom());

	if (circle.CenterX() < rect.Left())
	{
		collisionX = rect.Left();
	}
	else if (circle.CenterX() > rect.Right())
	{
		collisionX = rect.Right();
	}
	else
	{
		collisionX = circle.CenterX();
	}

	collisionY = circle.CenterY();
	Clamp(collisionY, rect.Top(), rect.Bottom());

	if (CircleContainsDot(circle, collisionX, collisionY))
	{
		if (circle.CenterX() < rect.Left())
		{
			if (circle.CenterY() < rect.Top())
			{
				if (rect.Left() - circle.CenterX() < rect.Top() - circle.CenterY())
				{
					return COLLISION_TOP;
				}
				else
				{
					return COLLISION_LEFT;
				}
			}
			else if (circle.CenterY() > rect.Top())
			{
				if (rect.Left() - circle.CenterX() < circle.CenterY() - rect.Top())
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
		else if (circle.CenterX() > rect.Right())
		{
			if (circle.CenterY() < rect.Top())
			{
				if (circle.CenterX() - rect.Right() < rect.Top() - circle.CenterY())
				{
					return COLLISION_TOP;
				}
				else
				{
					return COLLISION_RIGHT;
				}
			}
			else if (circle.CenterY() > rect.Top())
			{
				if (circle.CenterX() - rect.Right() < circle.CenterY() - rect.Top())
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
			if (circle.CenterY() < rect.Top())
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



bool CircleContainsDot(const Sprite &circle, float x, float y)
{
	return Square(circle.CenterX() - x) + Square(circle.CenterY() - y) < Square(circle.Radius());
}

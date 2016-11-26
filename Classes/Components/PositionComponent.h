#include "cocos2d.h"

struct PositionComponent {
	PositionComponent(float x = 0.0f, float y = 0.0f) : x(x), y(y)
	{
	}

	float x, y;
};
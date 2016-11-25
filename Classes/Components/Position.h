#include "cocos2d.h"

struct Position {
	Position(float x = 0.0f, float y = 0.0f) : x(x), y(y) 
	{
		sprite = cocos2d::Sprite::create("CloseNormal.png");
		sprite->setPosition(Point(x, y));
	}

	cocos2d::Sprite *sprite;

	float x, y;
};
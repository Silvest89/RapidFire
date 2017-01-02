#ifndef __BULLETCOMPONENT_H__
#define __BULLETCOMPONENT_H__
#include "cocos2d.h"

USING_NS_CC;

struct BulletComponent {
	float angle;
	Vec2 origin;
	int speed;
	Sprite *bulletSprite;

	BulletComponent(WeaponType weapon, float angle, Vec2 origin, float rotation)
	{
		bulletSprite = Sprite::create("bullet.png");
		bulletSprite->setPosition(origin);
		this->angle = angle;
		this->origin = origin;
		this->speed = 250;

		bulletSprite->setRotation(rotation);
		Game::_game->addChild(bulletSprite);
	}
};

#endif //__BULLETCOMPONENT_H__
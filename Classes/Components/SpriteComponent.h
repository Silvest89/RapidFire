#ifndef __SPRITECOMPONENT_H__
#define __SPRITECOMPONENT_H__
#include "cocos2d.h"

struct SpriteComponent {
	SpriteComponent(cocos2d::String spriteFile)
	{
		this->sprite = cocos2d::Sprite::create(spriteFile.getCString());
		//sprite->setPosition(cocos2d::Point(x, y));
	}

	cocos2d::Sprite *sprite;
};

#endif
#ifndef __SPRITECOMPONENT_H__
#define __SPRITECOMPONENT_H__

#include "cocos2d.h"

struct SpriteComponent {
	SpriteComponent(std::string spriteFile)
	{
		this->sprite = cocos2d::Sprite::create(spriteFile.c_str());
		//sprite->setPosition(cocos2d::Point(x, y));
		//label = cocos2d::Label::createWithTTF("Johnnie Ho", "fonts/Marker Felt.ttf", 14);
		label = cocos2d::Label::createWithBMFont("fonts/test.fnt", "Johnnie Ho");
		label->setColor(cocos2d::Color3B(0, 0, 0));		
	}
	cocos2d::Label *label;
	cocos2d::Sprite *sprite;
};

#endif
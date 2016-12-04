#ifndef __SPRITECOMPONENT_H__
#define __SPRITECOMPONENT_H__

#include "cocos2d.h"
#include "enums.h"

class Player;

USING_NS_CC;

struct SpriteComponent {
	Vec2 velocity;
	SpriteComponent(Player *player, std::string spriteFile)
	{
		this->sprite = Sprite::create(spriteFile.c_str());
		/*auto spriteBody = PhysicsBody::createBox(sprite->getContentSize(), PhysicsMaterial(0, 0, 0.3f));
		spriteBody->setRotationEnable(false);
		spriteBody->setCategoryBitmask(CATEGORY_PLAYER);
		spriteBody->setCollisionBitmask(CATEGORY_STATIC);
		spriteBody->setContactTestBitmask(CATEGORY_STATIC);
		spriteBody->setLinearDamping(0.5f);

		//spriteBody->getCPBody()->userData = player;
		sprite->setPhysicsBody(spriteBody);
		//sprite->setPosition(cocos2d::Point(x, y));*/
		//label = cocos2d::Label::createWithTTF("Johnnie Ho", "fonts/Marker Felt.ttf", 14);
	}
	
	cocos2d::Sprite *sprite;
};

#endif
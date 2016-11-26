#ifndef __PLAYER_H__
#define  __PLAYER_H__

#include "cocos2d.h"
#include "Entity/Creature.h"
#include <entityx/entityx.h>
#include "Components\SpriteComponent.h"

class Player
{
public:
	Player(entityx::Entity entity);
	~Player();

	//cocos2d::Sprite *playerSprite;

	//cocos2d::Sprite *getSprite();

	//AIState state;
	cocos2d::Point getPosition();

private:

	entityx::Entity entity;

	entityx::ComponentHandle<SpriteComponent> spriteComponent;

};

#endif
#ifndef __PLAYER_H__
#define  __PLAYER_H__

#include "cocos2d.h"
#include <entityx/entityx.h>
#include "Components\SkeletonComponent.h"
#include "Box2D\Box2D.h"

class Player
{
public:
	Player();
	~Player();

	//cocos2d::Sprite *playerSprite;

	//cocos2d::Sprite *getSprite();

	//AIState state;
	cocos2d::Point getPosition();

	void setEntity(entityx::Entity entity);

private:

	entityx::Entity entity;

	entityx::ComponentHandle<SkeletonComponent> skeletonComponent;

};

#endif
#include "Player.h"
#include "enums.h"
#include "Components\SpriteComponent.h"

USING_NS_CC;

Player::Player(entityx::Entity entity)
{
	this->entity = entity;

	spriteComponent = entity.component<SpriteComponent>();

	//this->state = AIState::STATE_FINDPATH;
	//this->pathFind = new PathFinding(this);
}

Player::~Player()
{

}

Point Player::getPosition() {
	return spriteComponent->sprite->getPosition();
}
#include "Player.h"
#include "Components\SpriteComponent.h"

USING_NS_CC;

Player::Player()
{

	//this->state = AIState::STATE_FINDPATH;
	//this->pathFind = new PathFinding(this);
}

Player::~Player()
{

}

void Player::setEntity(entityx::Entity entity)
{
	this->entity = entity;
	spriteComponent = entity.component<SpriteComponent>();
}

Point Player::getPosition() {
	if(spriteComponent)
		return spriteComponent->sprite->getPosition();
}
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
	return spriteComponent->sprite->getPosition();
}

Vec3 Player::getPosition3D()
{
	return spriteComponent->sprite->getPosition3D();
}
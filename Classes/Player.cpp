#include "Player.h"
#include "Components\SkeletonComponent.h"

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
	skeletonComponent = entity.component<SkeletonComponent>();
}

Point Player::getPosition() {
	if (skeletonComponent)
		return skeletonComponent->skeleton->getPosition();
	return Vec2(0, 0);
}
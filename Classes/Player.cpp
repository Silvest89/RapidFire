#include "Player.h"
#include "enums.h"

USING_NS_CC;

Player::Player(std::string name)
{
	this->name = name;
	this->initWithFile("CloseNormal.png");
	auto spriteBody = PhysicsBody::createBox(getContentSize(), PhysicsMaterial(0, 1, 0.6f));
	spriteBody->setRotationEnable(false);
	spriteBody->setLinearDamping(0.2f);
	spriteBody->setCategoryBitmask(CATEGORY_PLAYER);
	spriteBody->setCollisionBitmask(CATEGORY_STATIC);
	spriteBody->setContactTestBitmask(CATEGORY_STATIC);

	setPhysicsBody(spriteBody);
	jump = true;
}

Player::~Player()
{
}

bool Player::canJump()
{
	return this->jump;
}

void Player::setCanJump(bool canJump)
{
	this->jump = canJump;
}
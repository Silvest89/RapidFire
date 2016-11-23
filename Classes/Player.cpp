#include "Player.h"

USING_NS_CC;

Player::Player(std::string name)
{
	playerSprite = Sprite::create("CloseNormal.png");

	auto spriteBody = PhysicsBody::createBox(playerSprite->getContentSize(), PhysicsMaterial(0, 1, 5));
	playerSprite->setPhysicsBody(spriteBody);
}


Player::~Player()
{
}

Sprite *Player::getSprite() 
{
	return playerSprite;
}
#ifndef __PLAYER_H__
#define  __PLAYER_H__

#include "cocos2d.h"

class PathFinding;

class Player : public cocos2d::Sprite
{
public:
	Player(std::string name);
	~Player();

	//cocos2d::Sprite *playerSprite;

	//cocos2d::Sprite *getSprite();

	PathFinding *pathFind;

	bool canJump();
	void setCanJump(bool canJump);
	std::string name;

	void update();

	//AIState state;

	void moveTo(cocos2d::Point target);

private:
	bool jump;
};

#endif
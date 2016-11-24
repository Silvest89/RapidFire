#include "cocos2d.h"


class Player : public cocos2d::Sprite
{
public:
	Player(std::string name);
	~Player();

	//cocos2d::Sprite *playerSprite;

	//cocos2d::Sprite *getSprite();

	bool canJump();
	void setCanJump(bool canJump);
	std::string name;

private:
	bool jump;
};


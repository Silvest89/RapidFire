#include "cocos2d.h"


class Player
{
public:
	Player(std::string name);
	~Player();

	cocos2d::Sprite *playerSprite;

	cocos2d::Sprite *getSprite();
};


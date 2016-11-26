#include "cocos2d.h"
#include "Input/Controller.h"
#include "Game.h"

class GameController : public cocos2d::Node
{
public:
	static cocos2d::Scene* createScene();
	GameController();
	~GameController();

	static Controller *controller;

	virtual bool init();
	CREATE_FUNC(GameController);
};


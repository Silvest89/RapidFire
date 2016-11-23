#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "SneakyButton.h"
#include "SneakyButtonSkinnedBase.h"
#include "SneakyJoystickSkinnedBase.h"

class Game :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	void update(float) override;

	Player* player;
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	CREATE_FUNC(Game);

	SneakyJoystick *leftJoystick;
	SneakyButton *jumpBtn;

private:
	cocos2d::PhysicsWorld *physicsWorld;

	void setPhysicsWorld(cocos2d::PhysicsWorld *world) { physicsWorld = world; };
};

#endif // __GAME_SCENE_H__
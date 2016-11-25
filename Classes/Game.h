#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Controller.h"
#include <entityx/entityx.h>

class Game : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	void update(float) override;

	Player* player;
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	CREATE_FUNC(Game);

	Controller *controller;
	TMXTiledMap *map;

	void setViewPointCenter(Point position);
	Point worldToTilePosition(Point position);
	Point tileToWorldPosition(Point position);
	PointArray * walkableAdjacentTilesCoordForTileCoord(const Point & tileCoord) const;

	entityx::EntityX ex;

private:
	cocos2d::PhysicsWorld *physicsWorld;

	void setPhysicsWorld(cocos2d::PhysicsWorld *world) { physicsWorld = world; };
	bool onContactBegin(cocos2d::PhysicsContact &contact);
};

#endif // __GAME_SCENE_H__
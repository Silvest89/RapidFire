#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Input/Controller.h"
#include "Box2D\Box2D.h"

class entityx::EntityX;

class Game : public cocos2d::Layer
{
public:
	virtual bool init();
	static cocos2d::Scene* createScene();
	void update(float) override;
	
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	CREATE_FUNC(Game);

	TMXTiledMap *map;

	static b2World *world;
	b2Body *test;
	Sprite *testSprite;

	void setViewPointCenter(Point position);
	Point worldToTilePosition(Point position);
	Point tileToWorldPosition(Point position);
	PointArray * walkableAdjacentTilesCoordForTileCoord(const Point & tileCoord) const;

	Player* player;
	entityx::EntityX ex;
	void setPhysicsWorld(cocos2d::PhysicsWorld *world) { physicsWorld = world; };
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags);
	float accumulator;

private:
	cocos2d::PhysicsWorld *physicsWorld;


};

#endif // __GAME_SCENE_H__
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Input/Controller.h"
#include <entityx/entityx.h>
#include "Box2D\Box2D.h"


class Game : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	void update(float) override;

	
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	CREATE_FUNC(Game);

	static Controller *controller;
	TMXTiledMap *map;

	static b2World *world;

	void setViewPointCenter(Point position);
	Point worldToTilePosition(Point position);
	Point tileToWorldPosition(Point position);
	PointArray * walkableAdjacentTilesCoordForTileCoord(const Point & tileCoord) const;

	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags);

	Player* player;
	entityx::EntityX ex;
	

private:
	bool onContactBegin(cocos2d::PhysicsContact &contact);
};

#endif // __GAME_SCENE_H__
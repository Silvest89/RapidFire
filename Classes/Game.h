#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Input/Controller.h"
#include "Box2D\Box2D.h"

class Game : public cocos2d::Layer
{
public:
	virtual bool init();

	void update(float) override;
	
	CREATE_FUNC(Game);

	b2Body *test;
	Sprite *testSprite;

	void setupPhysicsWorld(bool debugDraw);
	b2World *getPhysicsWorld();
	void setupECS();
	void loadMap();
	TMXTiledMap *getMap();

	void setViewPointCenter(Point position);
	Point worldToTilePosition(Point position);
	Point tileToWorldPosition(Point position);

	PointArray * walkableAdjacentTilesCoordForTileCoord(const Point & tileCoord) const;

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags);

	static Game* _game;

private:
	b2World *physicsWorld;
	TMXTiledMap *tileMap;

	Player* player;
	entityx::EntityX ex;



};

#endif // __GAME_SCENE_H__
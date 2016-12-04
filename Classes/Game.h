#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Input/Controller.h"
#include "Box2D\Box2D.h"
#include <spine/spine-cocos2dx.h>

class Game : public cocos2d::Layer
{
public:
	virtual bool init();

	void update(float) override;
	
	CREATE_FUNC(Game);

	void setupECS();
	void loadMap();
	static TMXTiledMap *getMap();

	void setViewPointCenter(Point position);
	static Point worldToTilePosition(Point position);
	static Point tileToWorldPosition(Point position);

	PointArray * walkableAdjacentTilesCoordForTileCoord(const Point & tileCoord) const;

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

	static Game* _game;
	float angle;
	Sprite *testSprite;
	void goTest(spTrackEntry* entry, spEvent* event);

private:
	static TMXTiledMap *tileMap;

	Player* player;
	entityx::EntityX ex;

	bool physicsDebug;

};

#endif // __GAME_SCENE_H__
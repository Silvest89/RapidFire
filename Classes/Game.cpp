#include "Game.h"
#include "Input/Controller.h"
#include "enums.h"
#include "Components\RapidComponents.h"
#include "Systems/RenderSystem.h"
#include "Systems/InputSystem.h"
#include "Systems\MovementSystem.h"
#include "Systems\ProjectileSystem.h"
#include <entityx/entityx.h>
#include "GameController.h"
#include "CreatureBar.h"
#include "Player.h"
#include "GLES-Render.h"

#include "PhysicsLoader.h"
#include <fstream>

#include <spine/spine-cocos2dx.h>

USING_NS_CC;

using namespace spine;

Game *Game::_game = 0;
TMXTiledMap *Game::tileMap = 0;
entityx::EntityX Game::ex;

bool Game::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	_game = this;
	Director::getInstance()->setContentScaleFactor(1);

	//this->setupPhysicsWorld(false);
	this->loadMap();
	this->setupECS();
    

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	/*{
		testSprite = Sprite::create("Sprite-PNG-Clipart.png");
		testSprite->setPosition(150, 380);

		// Body of the ball
		b2BodyDef bodyDef; // Define the above Body
		b2FixtureDef fixtureDef; // Define some static features: friction, restitution, density, etc.

		//fixtureDef
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.0f;
		fixtureDef.restitution = 0.2f;
		fixtureDef.filter.categoryBits = CATEGORY_PLAYER;
		fixtureDef.filter.maskBits = CATEGORY_STATIC;

		//bodyDef
		bodyDef.type = b2_staticBody; // Dynamic collision
		//bodyDef.userData = player; // Attach to Sprite ball

								   // Set position, and remember to convert the unit
		bodyDef.position.Set((testSprite->getPosition().x - 103) / 32, (testSprite->getPosition().y - 103) / 32);

		//ballBody
		test = getPhysicsWorld()->CreateBody(&bodyDef); // Create Body
		//test->CreateFixture(&fixtureDef); // Create static features

		PhysicsLoader *loader = new PhysicsLoader();
		//loader->addShapesWithFile("test.plist");
		b2FixtureDef fixtureDef2; // Define some static features: friction, restitution, density, etc.

								 //fixtureDef
		fixtureDef2.density = 1.0f;
		fixtureDef2.friction = 0.0f;
		fixtureDef2.restitution = 0.2f;
		fixtureDef2.filter.categoryBits = CATEGORY_STATIC;
		fixtureDef2.filter.maskBits = CATEGORY_PLAYER;

		loader->addShapesWithJSON("test.json", fixtureDef2);
		loader->addFixturesToBody(test, "Name");
		loader->reset();
		//loader->addShapesWithJSON("test.json");

		//BodyEditorLoader *bLoader = new BodyEditorLoader("test");
		//bLoader->attachFixture(test, "Name", fixtureDef, 32.0f);

		addChild(testSprite);
	}*/
	auto layer1 = LayerGradient::create(Color4B(255, 0, 0, 255), Color4B(255, 0, 255, 255));
	layer1->setContentSize(Size(80, 80));
	layer1->setPosition(Vec2(50, 50));
	addChild(layer1);

	//skeletonNode->setTrackEventListener(test, CC_CALLBACK_2(Game::goTest, this));
	auto skeletonNode = SkeletonAnimation::createWithBinaryFile("spineboy.skel", "spineboy.atlas", 0.4f);
	skeletonNode->setPosition(Vec2(1050, 370));
	skeletonNode->setScaleX(-1);	
	spTrackEntry *test = skeletonNode->setAnimation(0, "idle", true);
	//skeletonNode->setScaleX(-1);
	/*skeletonNode->setTrackEventListener(test, [this](spTrackEntry * entry, spEvent * event) {
		this->goTest(entry, event);
	});*/
	addChild(skeletonNode);
	//skeletonNode->update(0.0f);

	spBone *rearBracer = skeletonNode->findBone("rear_upper_arm");
	spBone *rearBracer2 = skeletonNode->findBone("rear_bracer");
	rearBracer2->data->rotation = 50;
	spBone *gunTip = skeletonNode->findBone("gunTip");
	skeletonNode->updateWorldTransform();
	skeletonNode->update(0.0f);

	float rx, ry;

	rx = skeletonNode->getPositionX() - rearBracer->worldX;
	ry = skeletonNode->getPositionY() + rearBracer->worldY;
	//angle = rearBracer2->data->rotation;

	//skeletonNode->updateWorldTransform();
	float x, y;
	x = skeletonNode->getPositionX() - gunTip->worldX;
	y = skeletonNode->getPositionY() + gunTip->worldY;
	angle = atan2(y - ry, x - rx);
	//angle = 180 - angle;
	auto subSprite = Sprite::create("CloseNormal.png");
	subSprite->setPosition(rx, ry);
	addChild(subSprite);
	
	testSprite = Sprite::create("CloseNormal.png");
	testSprite->setPosition(x, y); 
	addChild(testSprite);
	this->scheduleUpdate();
	
	return true;
}

void Game::goTest(spTrackEntry * entry, spEvent * event)
{
	//log("%d event: %s, %d, %f, %s", entry->trackIndex, event->data->name, event->intValue, event->floatValue, event->stringValue);
}

void Game::update(float delta)
{
	Vec2 position = testSprite->getPosition();
	testSprite->setPosition(position.x + 50 * cos(angle) * delta, position.y + 50* sin(angle) * delta);
	ex.systems.update_all(delta);
	//getPhysicsWorld()->Step(1 / 60.0f, 8, 3);
	setViewPointCenter(player->getPosition());
	//CCLOG("body %f %f", test->GetPosition().x, test->GetPosition().y);
	//CCLOG("test %f %f", testSprite->getPosition().x, testSprite->getPosition().y);
	//setViewPointCenter(player->getPosition());
	//getPhysicsWorld()->ClearForces();
	//testSprite->setPosition(Vec2((test->GetPosition().x) * 32 + 103, (test->GetPosition().y) * 32 + 103));

}

void Game::setupECS() 
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	ex.systems.add<InputSystem>();
	ex.systems.add<MovementSystem>();
	ex.systems.add<RenderSystem>();
	ex.systems.add<ProjectileSystem>();
	ex.systems.configure();

	player = new Player();

	entityx::Entity playerEntity = ex.entities.create();

	playerEntity.assign<SkeletonComponent>("spineboy");
	entityx::ComponentHandle<SkeletonComponent> skeletonCP = playerEntity.component<SkeletonComponent>();
	if (skeletonCP) {
		skeletonCP->skeleton->setPosition(Point(50, visibleSize.height / 2 + origin.y + 300));
		addChild(skeletonCP->skeleton);
	}
	playerEntity.assign<CreatureComponent>("Johnnie Ho");
	entityx::ComponentHandle<CreatureComponent> creature = playerEntity.component<CreatureComponent>();
	if (creature) {
		//addChild(creature->getNameLabel());
		addChild(creature->getBar());
	}
	player->setEntity(playerEntity);
	//playerEntity.assign<PhysicsBodyComponent>(player);
	playerEntity.assign<MovementComponent>();
	playerEntity.assign<InputComponent>(GameController::controller);
	playerEntity.assign<WeaponComponent>(WEAPON_PISTOL);
}

void Game::loadMap()
{
	// create a TMX map
	tileMap = TMXTiledMap::create("maps/map.tmx");
	addChild(tileMap, -1);

	/*// loop over the object groups in this tmx file
	auto objectGroups = tileMap->getObjectGroups();
	for (auto& objectGroup : objectGroups)
	{
		auto objects = objectGroup->getObjects();
		for (auto& object : objects)
		{
			auto properties = object.asValueMap();

			b2Body *ballBody; // Body of the ball
			b2BodyDef bodyDef; // Define the above Body
			b2FixtureDef fixtureDef; // Define some static features: friction, restitution, density, etc.
			b2PolygonShape bodyShape; // the shape of body

			bodyShape.SetAsBox(properties.at("width").asFloat() / 64, properties.at("height").asFloat() / 64);
			//fixtureDef
			//fixtureDef.density = 10;
			fixtureDef.friction = 0.7f;
			//fixtureDef.restitution = 0.6;
			fixtureDef.filter.categoryBits = CATEGORY_STATIC;
			fixtureDef.filter.maskBits = CATEGORY_PLAYER | GROUND_SENSOR;
			fixtureDef.shape = &bodyShape; // point to bodyShape

										   //bodyDef
			bodyDef.type = b2_staticBody; // Dynamic collision

										  // Set position, and remember to convert the unit
			bodyDef.position.Set((properties.at("x").asFloat() + properties.at("width").asFloat() / 2) / 32, (properties.at("y").asFloat() + properties.at("height").asFloat() / 2) / 32);

			//ballBody
			ballBody = getPhysicsWorld()->CreateBody(&bodyDef); // Create Body
			ballBody->CreateFixture(&fixtureDef); // Create static features
		}
	}*/
	/*// all tiles are aliased by default, let's set them anti-aliased
	for (const auto& child : tileMap->getChildren())
	{
		static_cast<SpriteBatchNode*>(child)->getTexture()->setAntiAliasTexParameters();
	}*/
}

TMXTiledMap *Game::getMap()
{
	return tileMap;
}

void Game::setViewPointCenter(Point position) {

	Size winSize = Director::getInstance()->getWinSize();
	//winSize = Vec2(960, 500);

	float x = MAX(position.x, winSize.width / 2);
	float y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (getMap()->getMapSize().width * getMap()->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (getMap()->getMapSize().height * getMap()->getTileSize().height) - winSize.height / 2);
	Vec2 actualPosition = Vec2(x, y);

	Vec2 centerOfView = Vec2(winSize.width / 2, winSize.height / 2);
	Vec2 viewPoint;
	Vec2::subtract(centerOfView, actualPosition, &viewPoint);
	//this->setPosition(Vec2(viewPoint.x, snapTile - 128));

	Vec2 test = convertToNodeSpace(position);
	if (std::abs(viewPoint.x - this->getPositionX()) > 256 && !cameraRunning)
	{
		cameraRunning = true;
	}

	if (cameraRunning)
	{
		if (this->getPositionX() > (int)viewPoint.x)
			this->setPositionX((int)this->getPositionX() - 3);
		else if (this->getPositionX() < (int)viewPoint.x)
			this->setPositionX((int)this->getPositionX() + 3);

		if (std::abs(this->getPositionX() - viewPoint.x) <= 3)
			cameraRunning = false;
	}

	int remainder = viewPoint.y / 128;
	int snapY = (remainder - 2) * 128;
	if (this->getPositionY() > snapY)
		this->setPositionY(this->getPositionY() - 2);
	else if (this->getPositionY() < snapY)
		this->setPositionY(this->getPositionY() + 2);
}

bool Game::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	Point point = worldToTilePosition(touch->getLocation());
	Point point2 = tileToWorldPosition(point);
	CCLOG("onTouchBegan x = %f, y = %f", point.x, point.y);
	CCLOG("onTouchBegan x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
	CCLOG("onTouchBegan x = %f, y = %f", point2.x, point2.y);

	return true;
}

Point Game::worldToTilePosition(Point position)
{
	int x = position.x / getMap()->getTileSize().width;
	int y = ((getMap()->getMapSize().height * getMap()->getTileSize().height) - position.y) / getMap()->getTileSize().height;
	return Point(x, y);
}

Point Game::tileToWorldPosition(Point position)
{
	int x = position.x * getMap()->getTileSize().width;
	int y = (((getMap()->getMapSize().height*128) / getMap()->getTileSize().width) - position.y) * getMap()->getTileSize().width;
	return Point(x, y);
}

PointArray *Game::walkableAdjacentTilesCoordForTileCoord(const Point &tileCoord) const
{
	PointArray *tmp = PointArray::create(2);

	bool l = false;
	bool r = false;
	Point p;

	p.setPoint(tileCoord.x - 1, tileCoord.y);
	//if (this->isValidTileCoord(p) && !this->isWallAtTileCoord(p))
	//{
		tmp->addControlPoint(p);
		//l = true;
	//}

	p.setPoint(tileCoord.x + 1, tileCoord.y);
	//if (this->isValidTileCoord(p) && !this->isWallAtTileCoord(p))
	//{
		tmp->addControlPoint(p);
		//r = true;
	//}

	return tmp;
}
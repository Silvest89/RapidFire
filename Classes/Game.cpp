#include "Game.h"
#include "Input/Controller.h"
#include "enums.h"
#include "Components\RapidComponents.h"
#include "Systems/RenderSystem.h"
#include "Systems/InputSystem.h"
#include <entityx/entityx.h>
#include "GameController.h"
#include "HealthBar.h"
#include "Player.h"
#include "GLES-Render.h"

#include "PhysicsLoader.h"

#include "Box2D\Box2D.h"

USING_NS_CC;

b2World *Game::world = 0;

Scene* Game::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	
	//scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

	// 'layer' is an autorelease object
	auto layer = Game::create();
	//layer->setPhysicsWorld(scene->getPhysicsWorld());

	// add layer as a child to scene
	scene->addChild(layer);

	//layer->controller = new Controller();
	//scene->addChild(layer->controller);
	// return the scene
	return scene;
}

bool Game::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Director::getInstance()->setContentScaleFactor(1);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	b2Vec2 gravity = b2Vec2(0.0f, -9.8f);
	world = new b2World(gravity);

	ex.systems.add<InputSystem>();
	ex.systems.add<RenderSystem>();
	ex.systems.configure();
	
	player = new Player();

	entityx::Entity playerEntity = ex.entities.create();

	playerEntity.assign<SpriteComponent>(player, "CloseNormal.png");
	entityx::ComponentHandle<SpriteComponent> sprite = playerEntity.component<SpriteComponent>();
	if (sprite) {
		sprite->sprite->setPosition(Point(50, visibleSize.height / 2 + origin.y + 300));
		addChild(sprite->sprite);
	}
	playerEntity.assign<CreatureComponent>();
	entityx::ComponentHandle<CreatureComponent> creature = playerEntity.component<CreatureComponent>();
	if (creature) {
		addChild(creature->getNameLabel());
		addChild(creature->getHealthBar());
	}
	player->setEntity(playerEntity);
	playerEntity.assign<PhysicsBodyComponent>(player);
	playerEntity.assign<InputComponent>(GameController::controller);	
	//player->setEntity(playerEntity);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	// create a TMX map
	map = TMXTiledMap::create("maps/map.tmx");
	addChild(map, -1);

	auto edgeBody = PhysicsBody::createEdgeBox(map->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(map->getContentSize().width / 2, map->getContentSize().height / 2));
	edgeNode->setPhysicsBody(edgeBody);
	addChild(edgeNode);

	// loop over the object groups in this tmx file
	auto objectGroups = map->getObjectGroups();
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
			fixtureDef.filter.maskBits = CATEGORY_PLAYER;
			fixtureDef.shape = &bodyShape; // point to bodyShape

										   //bodyDef
			bodyDef.type = b2_staticBody; // Dynamic collision

										  // Set position, and remember to convert the unit
			bodyDef.position.Set((properties.at("x").asFloat() + properties.at("width").asFloat() / 2) / 32, (properties.at("y").asFloat() + properties.at("height").asFloat() / 2) / 32);

			//ballBody
			ballBody = world->CreateBody(&bodyDef); // Create Body
			ballBody->CreateFixture(&fixtureDef); // Create static features
		}
	}
	testSprite = Sprite::create("Sprite-PNG-Clipart.png");
	testSprite->setPosition(150, 380);

	// Body of the ball
	b2BodyDef bodyDef; // Define the above Body
	b2FixtureDef fixtureDef; // Define some static features: friction, restitution, density, etc.
	b2PolygonShape bodyShape; // the shape of body

	bodyShape.SetAsBox(0.5f, 0.5f);

	//fixtureDef
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f;
	fixtureDef.restitution = 0.2f;
	fixtureDef.filter.categoryBits = CATEGORY_PLAYER;
	fixtureDef.filter.maskBits = CATEGORY_STATIC;
	fixtureDef.shape = &bodyShape; // point to bodyShape

								   //bodyDef
	bodyDef.type = b2_dynamicBody; // Dynamic collision
	//bodyDef.userData = player; // Attach to Sprite ball

							   // Set position, and remember to convert the unit
	bodyDef.position.Set((testSprite->getPosition().x - 103) / 32, (testSprite->getPosition().y - 103) / 32);

	//ballBody
	test = world->CreateBody(&bodyDef); // Create Body
	//test->CreateFixture(&fixtureDef); // Create static features

	PhysicsLoader *loader = new PhysicsLoader();
	loader->addShapesWithFile("test.plist");
	b2BodyDef bodyDef2;
	//bodyDef2.position.Set(testSprite->getPosition().x / 32, testSprite->getPosition().y / 32);
	//bodyDef2.type = b2_dynamicBody;
	//test = world->CreateBody(&bodyDef2);

	loader->addFixturesToBody(test, "Sprite-PNG-Clipart");
	
	addChild(testSprite);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	flags += b2Draw::e_aabbBit;
	flags += b2Draw::e_pairBit;
	flags += b2Draw::e_centerOfMassBit;
	flags += b2Draw::e_aabbBit;
	auto debugDraw = new GLESDebugDraw(32);
	debugDraw->SetFlags(flags);
    world->SetDebugDraw(debugDraw);
	//world->DrawDebugData();

	scheduleUpdate();

	return true;
}

void Game::update(float delta)
{
	//accumulator += delta;
	/*if (getScene()->getPhysicsWorld()->isAutoStep())
	{
		getScene()->getPhysicsWorld()->setAutoStep(false);
		//getScene()->getPhysicsWorld()->setSubsteps(5);
	}*/
	

	//while (accumulator >= delta) {
		ex.systems.update_all(delta);
		CCLOG("body %f %f", test->GetPosition().x, test->GetPosition().y);
		CCLOG("test %f %f", testSprite->getPosition().x, testSprite->getPosition().y);

		test->ApplyForceToCenter(b2Vec2(5.0f, 0), true);
		world->Step(1/60.0f, 8, 5);
		//getScene()->getPhysicsWorld()->step(delta);
	    setViewPointCenter(player->getPosition());
		testSprite->setPosition(Vec2((test->GetPosition().x) * 32 + 103, (test->GetPosition().y) * 32 + 103));
		//accumulator -= delta;
		world->ClearForces();
		//setViewPointCenter(player->getPosition());
	//}
		

}

void Game::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags)
 { 
	cocos2d::Layer::draw(renderer, transform, flags);
	
		GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION);
	Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	world->DrawDebugData();
	
		Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void Game::setViewPointCenter(Point position) {

	Size winSize = Director::getInstance()->getWinSize();
	//winSize = Vec2(960, 500);

	float x = MAX(position.x, winSize.width / 2);
	float y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (map->getMapSize().width * map->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (map->getMapSize().height * map->getTileSize().height) - winSize.height / 2);
	Vec2 actualPosition = Vec2(x, y);

	Vec2 centerOfView = Vec2(winSize.width / 2, winSize.height / 2);
	Vec2 viewPoint;
	Vec2::subtract(centerOfView, actualPosition, &viewPoint);
	this->setPosition(viewPoint);
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
	int x = position.x / map->getTileSize().width;
	int y = ((map->getMapSize().height * map->getTileSize().height) - position.y) / map->getTileSize().height;
	return Point(x, y);
}

Point Game::tileToWorldPosition(Point position)
{
	int x = position.x * map->getTileSize().width;
	int y = (((map->getMapSize().height*128) / map->getTileSize().width) - position.y) * map->getTileSize().width;
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
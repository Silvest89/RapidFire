#include "Game.h"
#include "Controller.h"
#include "enums.h"
USING_NS_CC;

Scene* Game::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

	// 'layer' is an autorelease object
	auto layer = Game::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());

	// add layer as a child to scene
	scene->addChild(layer);

	layer->controller = new Controller();
	scene->addChild(layer->controller);
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

	//controller = new Controller();
	//addChild(controller);

	//Director::getInstance()->setContentScaleFactor(1);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, this);

	// create a TMX map
	map = TMXTiledMap::create("maps/map.tmx");
	addChild(map, -1);

	scheduleUpdate();
	auto edgeBody = PhysicsBody::createEdgeBox(map->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(map->getContentSize().width / 2, map->getContentSize().height / 2));
	edgeNode->setPhysicsBody(edgeBody);

	addChild(edgeNode);

	player = new Player("Johnnie");
	player->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 600));

	addChild(player);

	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// loop over the object groups in this tmx file
	auto objectGroups = map->getObjectGroups();
	for (auto& objectGroup : objectGroups)
	{
		auto objects = objectGroup->getObjects();
		for (auto& object : objects)
		{
			auto properties = object.asValueMap();
			Sprite *sprite = Sprite::create();
			
			auto spriteBody = PhysicsBody::createBox(Size(properties.at("width").asFloat(), properties.at("height").asFloat()), PhysicsMaterial(1, 0, 2));
			spriteBody->setDynamic(false);
			spriteBody->setCategoryBitmask(CATEGORY_STATIC);
			spriteBody->setCollisionBitmask(CATEGORY_PLAYER);
			spriteBody->setContactTestBitmask(CATEGORY_PLAYER);

			sprite->setPhysicsBody(spriteBody);
			sprite->setPosition(Vec2(properties.at("x").asFloat() + properties.at("width").asFloat() / 2, properties.at("y").asFloat() + properties.at("height").asFloat() / 2));
			addChild(sprite);
		}
	}

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Game::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);	

	return true;
}

bool Game::onContactBegin(cocos2d::PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();
	if ((1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()) || 
		(2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
	{
		Player *player = (Player*)a->getOwner();
		if (player) 
		{
			player->setCanJump(true);
		}
		
		CCLOG("Collision");
		return true;
	}
	return false;
}

void Game::update(float delta)
{
	if (controller->leftJoystick->getVelocity().x > 0) {
		CCLOG("Right");
		player->getPhysicsBody()->applyForce(Vec2(150, 0));
	}
	if (controller->leftJoystick->getVelocity().x < 0) {
		CCLOG("Left");
		player->getPhysicsBody()->applyForce(Vec2(-150, 0));
	}
	if (controller->leftJoystick->getVelocity().x == 0) {
		//CCLOG("0");
		//player->getSprite()->getPhysicsBody()->applyForce(Vec2(0, 0));
	}
	if (controller->jumpBtn->getValue() && player->canJump()) {
		player->getPhysicsBody()->applyImpulse(Vec2(0, 200));
		player->getPhysicsBody()->setVelocity(Vec2(0, 100));
		player->setCanJump(false);
	}
	setViewPointCenter(player->getPosition());
}

void Game::setViewPointCenter(Point position) {

	Size winSize = Director::getInstance()->getWinSize();

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
	CCLOG("onTouchBegan x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
	return true;
}
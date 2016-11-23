#include "Game.h"

USING_NS_CC;

Scene* Game::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

	// 'layer' is an autorelease object
	auto layer = Game::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());

	// add layer as a child to scene
	scene->addChild(layer);

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

	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(edgeBody);

	addChild(edgeNode);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, this);

	// create a TMX map
	auto map = TMXTiledMap::create("maps/map.tmx");
	addChild(map, -1);

	scheduleUpdate();

	player = new Player("Johnnie");
	player->getSprite()->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	addChild(player->getSprite());

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	Rect joystickBaseDimensions;
	joystickBaseDimensions = Rect(0, 0, 160.0f, 160.0f);

	Point joystickBasePosition;
	joystickBasePosition = Vec2(visibleSize.width * 0.2f, visibleSize.height*0.2f);

	SneakyJoystickSkinnedBase *joystickBase = new SneakyJoystickSkinnedBase();
	joystickBase->init();
	joystickBase->setPosition(joystickBasePosition);
	joystickBase->setBackgroundSprite(Sprite::create("test.png"));
	joystickBase->setThumbSprite(Sprite::create("res/stick.png"));

	SneakyJoystick *aJoystick = new SneakyJoystick();
	aJoystick->initWithRect(joystickBaseDimensions);

	aJoystick->autorelease();
	joystickBase->setJoystick(aJoystick);
	joystickBase->setPosition(joystickBasePosition);

	leftJoystick = joystickBase->getJoystick();
	leftJoystick->retain();
	this->addChild(joystickBase);

	return true;
}

void Game::update(float delta)
{
	if (leftJoystick->getVelocity().x > 0) {
		CCLOG("Right");
	}
	if (leftJoystick->getVelocity().x < 0) {
		CCLOG("Left");
	}
	if (leftJoystick->getVelocity().x == 0) {
		CCLOG("0");
	}
}

bool Game::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	CCLOG("onTouchBegan x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
	return true;
}
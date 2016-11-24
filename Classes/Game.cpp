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

	Director::getInstance()->setContentScaleFactor(1);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	// create a TMX map
	map = TMXTiledMap::create("maps/map.tmx");
	//addChild(map, -1);
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
	if ((a->getCategoryBitmask() & b->getCollisionBitmask()) || 
		(a->getCollisionBitmask() & b->getCategoryBitmask()))
	{
		const PhysicsContactData *contactData = contact.getContactData();
		Point contactPoint = contactData->points[0];
		
		if(a->getCategoryBitmask() & CATEGORY_PLAYER)
		{
			Player* playerTest = dynamic_cast<Player*>(a->getNode());
			CCLOG("Player name: %s", playerTest->name.c_str());
		}
		if (b->getCategoryBitmask() & CATEGORY_PLAYER)
		{
			Player* playerTest = dynamic_cast<Player*>(b->getNode());
			CCLOG("Player name: %s", playerTest->name.c_str());
		}

		
		if (a->getCategoryBitmask() & CATEGORY_PLAYER || b->getCategoryBitmask() & CATEGORY_PLAYER)
		{
			
			CCLOG("Lower shape touched %f %f.", contactPoint.y, player->getPosition().y);
			if (contactPoint.y < player->getPosition().y)
			{
				CCLOG("Enable jumping.");
				//CCLOG("Player position %i", test);
				player->setCanJump(true);
			}			
		}
		
		return true;
	}
	return false;
}

void Game::update(float delta)
{
	if (controller->leftJoystick->getVelocity().x > 0) {
		player->getPhysicsBody()->applyForce(Vec2(250, 0));
	}
	if (controller->leftJoystick->getVelocity().x < 0) {
		player->getPhysicsBody()->applyForce(Vec2(-250, 0));
	}
	if (controller->leftJoystick->getVelocity().x == 0) {
		//CCLOG("0");
		//player->getSprite()->getPhysicsBody()->applyForce(Vec2(0, 0));
	}
	if (controller->jumpBtn->getValue() && player->canJump()) {
		player->getPhysicsBody()->applyImpulse(Vec2(0, 400));
		player->getPhysicsBody()->setVelocity(Vec2(0, 150));
		player->setCanJump(false);
	}
	setViewPointCenter(player->getPosition());
	player->update();
	
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
	Point test(5, 46);
	player->moveTo(test);
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
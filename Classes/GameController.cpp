#include "GameController.h"
#include "InfiniteParallax.h"
#include "Game.h"
#include "Input/Controller.h"
#include "GLES-Render.h"

USING_NS_CC;

Controller *GameController::controller = 0;

Scene* GameController::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//scene->getPhysicsWorld()->setGravity(Vec2(0, -98.0f));

	auto layer = GameController::create();
	scene->addChild(layer);

	// return the scene
	return scene;
}

GameController::GameController()
{
}


GameController::~GameController()
{
}

bool GameController::init()
{
	if (!Node::init())
	{
		return false;
	}

	Director::getInstance()->setContentScaleFactor(1);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto parallaxLayer = InfiniteParallax::create();
	addChild(parallaxLayer);

	controller = new Controller();

	// 'layer' is an autorelease object
	auto gameLayer = Game::create();
	gameLayer->setName("Game");
	/*auto spritePos = Vec3(0,
		visibleSize.height / 4 + origin.y,
		0);
	auto camera = Camera::createOrthographic(5, 10, 1.0, 1000);
	camera->setPosition3D(spritePos);*/

	// add layer as a child to scene
	addChild(gameLayer);
	//camera->lookAt(spritePos, Vec3(0.0, 1.0, 0.0));
	//addChild(camera);
	addChild(controller);

	return true;
}
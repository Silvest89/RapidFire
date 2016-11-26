#include "MainMenu.h"
#include "GameController.h"

USING_NS_CC;

//Controller *Game::controller = 0;

Scene* MainMenu::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainMenu::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool MainMenu::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto menuPlay = MenuItemFont::create("Play", CC_CALLBACK_1(MainMenu::Play, this));
	auto menuSettings = MenuItemFont::create("Settings", CC_CALLBACK_1(MainMenu::Settings, this));
	auto menuQuit = MenuItemFont::create("Quit", CC_CALLBACK_1(MainMenu::Quit, this));

	auto *menu = Menu::create(menuPlay, menuSettings, menuQuit, NULL);
	menu->alignItemsVertically();
	this->addChild(menu);

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainMenu::Quit, this));
	
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto *menu2 = Menu::create(closeItem, NULL);

	menu2->setPosition(Vec2::ZERO);
	this->addChild(menu2, 1);
	return true;
}

void MainMenu::Play(cocos2d::Ref *pSender)
{
	CCLOG("Play");
	//Game::controller = new Controller();
	auto newScene = GameController::createScene();
	//auto newScene = InfiniteParallax::createScene();
	Director::getInstance()->replaceScene(newScene);
}

void MainMenu::Settings(cocos2d::Ref *pSender)
{
	CCLOG("Settings");
}

void MainMenu::Quit(cocos2d::Ref *pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
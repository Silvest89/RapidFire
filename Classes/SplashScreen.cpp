#include "SplashScreen.h"
#include "MainMenu.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

Scene* SplashScreen::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SplashScreen::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool SplashScreen::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	silveniaLabSprite = Sprite::create("splash_silvenia_labs.jpg");
	float scale = MAX(visibleSize.width / silveniaLabSprite->getContentSize().width, visibleSize.height / silveniaLabSprite->getContentSize().height);
	silveniaLabSprite->setScale(scale);
	silveniaLabSprite->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));

	this->addChild(silveniaLabSprite);

	//auto newScene = SplashScreen::createScene();

	//Director::getInstance()->replaceScene(TransitionFade::create(5, newScene));

	return true;
}

void SplashScreen::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();

	this->scheduleOnce(CC_SCHEDULE_SELECTOR(SplashScreen::goToMenu), 2);
	//auto newScene = SplashScreen::createScene();

	//Director::getInstance()->replaceScene(TransitionFade::create(5, newScene));
	/*
	auto delay = DelayTime::create(2.0f);
    auto func = CallFunc::create(CC_CALLBACK_0(SplashScene::runMenu, this));
    this->runAction(Sequence::create(delay, func, NULL));
	*/
}

void SplashScreen::goToMenu(float dt) 
{
	auto newScene = MainMenu::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(2, newScene));
}
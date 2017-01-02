#include "Controller.h"

USING_NS_CC;

Controller::Controller()
{
	init();
}

bool Controller::init()
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

	Rect joystickBaseDimensions;
	joystickBaseDimensions = Rect(0, 0, 160.0f, 160.0f);

	SneakyJoystickSkinnedBase *joystickBase = new SneakyJoystickSkinnedBase();
	joystickBase->init();
	joystickBase->setBackgroundSprite(Sprite::create("joystick/joystick-bg.png"));
	joystickBase->setThumbSprite(Sprite::create("joystick/joystick-knob.png"));

	SneakyJoystick *aJoystick = new SneakyJoystick();
	aJoystick->initWithRect(joystickBaseDimensions);

	Point joystickBasePosition;
	joystickBasePosition = Vec2(15 + joystickBase->getContentSize().width / 2, 15 + joystickBase->getContentSize().height / 2);
	
	aJoystick->autorelease();
	joystickBase->setJoystick(aJoystick);
	joystickBase->setPosition(joystickBasePosition);

	leftJoystick = joystickBase->getJoystick();
	leftJoystick->retain();
	this->addChild(joystickBase);

	Rect joystickBaseDimensions2;
	joystickBaseDimensions2 = Rect(0, 0, 160.0f, 160.0f);

	SneakyJoystickSkinnedBase *joystickBase2 = new SneakyJoystickSkinnedBase();
	joystickBase2->init();
	joystickBase2->setBackgroundSprite(Sprite::create("joystick/joystick-bg.png"));
	joystickBase2->setThumbSprite(Sprite::create("joystick/joystick-knob.png"));

	SneakyJoystick *aJoystick2 = new SneakyJoystick();
	aJoystick2->initWithRect(joystickBaseDimensions2);

	Point joystickBasePosition2;
	joystickBasePosition2 = Vec2(visibleSize.width - joystickBase2->getContentSize().width / 2, 15 + joystickBase2->getContentSize().height / 2);

	aJoystick2->autorelease();
	joystickBase2->setJoystick(aJoystick2);
	joystickBase2->setPosition(joystickBasePosition2);

	rightJoystick = joystickBase2->getJoystick();
	rightJoystick->retain();
	this->addChild(joystickBase2);

	Rect jumpButtonDimensions = Rect(0, 0, 64.0f, 64.0f);
	Point jumpButtonPosition;
	jumpButtonPosition = Vec2(visibleSize.width - 50, 30);

	SneakyButtonSkinnedBase *jumpButtonBase = new SneakyButtonSkinnedBase();
	jumpButtonBase->init();
	jumpButtonBase->setPosition(jumpButtonPosition);

	jumpButtonBase->setDefaultSprite(Sprite::create("joystick/joystick-knob.png"));
	jumpButtonBase->setActivatedSprite(Sprite::create("joystick/joystick-knob.png"));
	jumpButtonBase->setDisabledSprite(Sprite::create("joystick/joystick-knob.png"));
	jumpButtonBase->setPressSprite(Sprite::create("joystick/joystick-knob.png"));

	SneakyButton *ajumpButton = new SneakyButton();
	ajumpButton->initWithRect(jumpButtonDimensions);
	ajumpButton->autorelease();

	jumpButtonBase->setButton(ajumpButton);
	jumpButtonBase->setPosition(jumpButtonPosition);

	jumpBtn = jumpButtonBase->getSbutton();
	jumpBtn->retain();
	this->addChild(jumpButtonBase);

	return true;
}

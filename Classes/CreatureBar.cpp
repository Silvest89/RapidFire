#include "CreatureBar.h"

using namespace ui;

CreatureBar::CreatureBar(std::string name)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	healthBarBG = LoadingBar::create("Health-BG.png");
	healthBarBG->setName("LoadingBar");
	healthBarBG->setDirection(LoadingBar::Direction::LEFT);
	healthBarBG->setPercent(100);

	healthBarBG->setPosition(Point(0, 0));
	healthBarBG->setAnchorPoint(Vec2(0, 0));
	addChild(healthBarBG);

	healthBarFG = LoadingBar::create("Health-FG.png");
	healthBarFG->setName("LoadingBar");
	healthBarFG->setDirection(LoadingBar::Direction::LEFT);
	healthBarFG->setPercent(100);

	healthBarFG->setPosition(Point(Point(0, 0)));
	healthBarFG->setAnchorPoint(Vec2(0, 0));
	addChild(healthBarFG);

	nameLabel = cocos2d::Label::createWithBMFont("fonts/test.fnt", name.c_str());
	nameLabel->setColor(cocos2d::Color3B(0, 0, 0));
	nameLabel->setPosition(Vec2(55, 30));
	addChild(nameLabel);
}

CreatureBar::~CreatureBar()
{
}

void CreatureBar::updateHealth(int health, int maxHealth)
{
	float percent = (float)health / maxHealth * 100;
	healthBarFG->setPercent(percent);
}
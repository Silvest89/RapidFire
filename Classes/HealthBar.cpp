#include "HealthBar.h"

using namespace ui;

HealthBar::HealthBar()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	healthBarBG = LoadingBar::create("Health-BG.png");
	healthBarBG->setName("LoadingBar");
	healthBarBG->setDirection(LoadingBar::Direction::LEFT);
	healthBarBG->setPercent(100);

	healthBarBG->setPosition(Point(Point(180, visibleSize.height / 2 + origin.y + 200)));
	healthBarBG->setAnchorPoint(Vec2(0, 0));
	addChild(healthBarBG);

	healthBarFG = LoadingBar::create("Health-FG.png");
	healthBarFG->setName("LoadingBar");
	healthBarFG->setDirection(LoadingBar::Direction::LEFT);
	healthBarFG->setPercent(100);

	healthBarFG->setPosition(Point(Point(180, visibleSize.height / 2 + origin.y + 200)));
	healthBarFG->setAnchorPoint(Vec2(0, 0));
	addChild(healthBarFG);

}

HealthBar::~HealthBar()
{
}

void HealthBar::setBarPosition(Point &position)
{
	healthBarBG->setPosition(position);
	healthBarFG->setPosition(position);
}
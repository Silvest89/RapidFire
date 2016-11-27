#ifndef __HEALTHBAR_H__
#define __HEALTHBAR_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"

USING_NS_CC;
class HealthBar : public cocos2d::Node
{
public:
	ui::LoadingBar* healthBarBG;
	ui::LoadingBar* healthBarFG;
	HealthBar();
	~HealthBar();

	void setBarPosition(Vec2 position);
	void updateHealth(int health, int maxhealth);


};

#endif


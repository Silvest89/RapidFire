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

	void setBarPosition(Point &position);


};

#endif


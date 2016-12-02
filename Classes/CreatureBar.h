#ifndef __HEALTHBAR_H__
#define __HEALTHBAR_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"

USING_NS_CC;
class CreatureBar : public cocos2d::Node
{
public:
	ui::LoadingBar* healthBarBG;
	ui::LoadingBar* healthBarFG;
	cocos2d::Label *nameLabel;

	CreatureBar(std::string name);
	~CreatureBar();

	void updateHealth(int health, int maxhealth);


};

#endif


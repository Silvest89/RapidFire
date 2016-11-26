#include "cocos2d.h"
#include "HealthBar.h"

struct CreatureComponent {
	CreatureComponent()
	{
		this->health = 100;
		bar = new HealthBar();
	}

	std::string name;
	int health;
	HealthBar *bar;
	float speed;


};
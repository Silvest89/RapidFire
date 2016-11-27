#include "cocos2d.h"
#include "HealthBar.h"

struct CreatureComponent {
	CreatureComponent()
	{
		nameLabel = cocos2d::Label::createWithBMFont("fonts/test.fnt", "Johnnie Ho");
		nameLabel->setColor(cocos2d::Color3B(0, 0, 0));
		healthBar = new HealthBar();

		this->health = 50;
		this->maxHealth = 150;
	}

public:
	std::string getName()
	{
		return name;
	}

	int getHealth()
	{
		return health;
	}

	int getMaxHealth()
	{
		return maxHealth;
	}

	cocos2d::Label *getNameLabel()
	{
		return nameLabel;
	}

	HealthBar *getHealthBar()
	{
		return healthBar;
	}

	float getSpeed()
	{
		return speed;
	}


private:

	std::string name;
	int health, maxHealth;

	cocos2d::Label *nameLabel;
	HealthBar *healthBar;
	float speed;


};
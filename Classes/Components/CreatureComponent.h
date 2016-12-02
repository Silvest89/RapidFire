#include "cocos2d.h"
#include "CreatureBar.h"

struct CreatureComponent {
	CreatureComponent(std::string name)
	{
		creatureBar = new CreatureBar(name);

		this->name = name;
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

	CreatureBar *getBar()
	{
		return creatureBar;
	}

	float getSpeed()
	{
		return speed;
	}


private:

	std::string name;
	int health, maxHealth;

	CreatureBar *creatureBar;
	float speed;


};
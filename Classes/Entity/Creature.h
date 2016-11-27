#ifndef __CREATURE_H__
#define __CREATURE_H__

#include "cocos2d.h"
#include <entityx/entityx.h>

class Creature : public entityx::Entity
{
public:
	Creature();
	~Creature();
};

#endif
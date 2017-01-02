#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "cocos2d.h"
#include "SneakyButton.h"
#include "SneakyButtonSkinnedBase.h"
#include "SneakyJoystickSkinnedBase.h"

class Controller : public cocos2d::Layer
{
public:
	Controller();
	virtual bool init();

	SneakyJoystick *leftJoystick;
	SneakyJoystick *rightJoystick;
	SneakyButton *jumpBtn;
};

#endif // __CONTROLLER_H__
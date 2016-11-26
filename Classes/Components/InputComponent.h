#include "cocos2d.h"
#include "Input/Controller.h"

struct InputComponent {
	InputComponent(Controller *controller) : controller(controller)
	{
	}

	Controller *controller;
};
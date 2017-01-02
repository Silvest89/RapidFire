#ifndef __WEAPONCOMPONENT_H__
#define __WEAPONCOMPONENT_H__

#include "enums.h"

struct WeaponComponent {
	WeaponType getWeapon()
	{
		return weaponType;
	}

	void setWeapon(WeaponType weaponType)
	{
		this->weaponType = weaponType;
	}

	float getFireRate()
	{
		return fireRate;
	}

	void setFireRate(float fireRate)
	{
		this->fireRate = fireRate;
	}

	WeaponComponent(WeaponType weapon)
	{
		this->weaponType = weapon;
		this->fireRate = 5;
		this->fireRateTimer = 0;
	}

	float fireRateTimer;

private:
	WeaponType weaponType;
	float fireRate;
};

#endif //__WEAPONCOMPONENT_H__
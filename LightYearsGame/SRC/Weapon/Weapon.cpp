#include "Weapon/Weapon.h"

namespace ly {
	void Shooter::Shoot()
	{
		if (CanShot() && !IsOnCoolDown())
		{
			ShootImpl();
		}
	}
	Shooter::Shooter(Actor* owner)
		:mOwner{owner}
	{

	}
}
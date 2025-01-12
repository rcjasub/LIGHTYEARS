#include "Weapon.hpp"

namespace ly {
	void Shooter::Shoot()
	{
		if (CanShot() && !IsOnCoolDown())
		{
			ShootImpl();
		}
	}

	void Shooter::IncrementLevel(int amt)
	{
		if (mCurrentLevel == mMaxLevel) return;
		++mCurrentLevel;
	}
	
	Shooter::Shooter(Actor* owner)
		:mOwner{owner},
		mCurrentLevel{1},
		mMaxLevel{ 4 }
	{

	}
}
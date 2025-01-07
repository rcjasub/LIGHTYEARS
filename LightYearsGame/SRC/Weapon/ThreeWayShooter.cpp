#include "Weapon/ThreeWayShooter.h"

namespace ly
{
	ThreeWayShooter::ThreeWayShooter(Actor* owner, float coolDonwTime, const sf::Vector2f& localOffset)
		:Shooter{owner},
		mShooterLeft{owner, coolDonwTime, localOffset + sf::Vector2f{ 10, -10}, -30.f,"SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
		mShooterMid{ owner, coolDonwTime, localOffset, 0.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png" },
		mShooterRight{ owner, coolDonwTime, localOffset + sf::Vector2f{ 10, 10}, 30.f,"SpaceShooterRedux/PNG/Lasers/laserRed01.png" },
		mTopLevelShooterLeft{ owner, coolDonwTime, localOffset + sf::Vector2f{ 10, 10}, 15.f,"SpaceShooterRedux/PNG/Lasers/laserRed01.png" },
		mTopLevelShooterRight{ owner, coolDonwTime, localOffset + sf::Vector2f{ 10, -10}, -15.f,"SpaceShooterRedux/PNG/Lasers/laserRed01.png" }
	{
		
	}

	void ThreeWayShooter::IncrementLevel(int amt)
	{
		Shooter::IncrementLevel(amt);
		mShooterLeft.IncrementLevel(amt);
		mShooterMid.IncrementLevel(amt);
		mShooterRight.IncrementLevel(amt);

		mTopLevelShooterLeft.IncrementLevel(amt);
		mTopLevelShooterRight.IncrementLevel(amt);
	}

	void ThreeWayShooter::ShootImpl()
	{
		mShooterLeft.Shoot();
		mShooterMid.Shoot();
		mShooterRight.Shoot();

		if (GetCurrentLevel() == GetMaxLevel())
		{
			mTopLevelShooterLeft.Shoot();
			mTopLevelShooterRight.Shoot();
		}
	}  
}  
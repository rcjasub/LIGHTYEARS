#include "Weapon/ThreeWayShooter.h"

namespace ly
{
	ThreeWayShooter::ThreeWayShooter(Actor* owner, float coolDonwTime, const sf::Vector2f& localOffset)
		:Shooter{owner},
		mShooterLeft{owner, coolDonwTime, localOffset + sf::Vector2f{ 10, -.10}, -30.f,"SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
		mShooterMid{ owner, coolDonwTime, localOffset, 0.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png" },
		mShooterRight{ owner, coolDonwTime, localOffset + sf::Vector2f{ 10, .10}, 30.f,"SpaceShooterRedux/PNG/Lasers/laserRed01.png" }
	{
		
	}
	void ThreeWayShooter::ShootImpl()
	{
		mShooterLeft.Shoot();
		mShooterMid.Shoot();
		mShooterRight.Shoot();
	}  
}  
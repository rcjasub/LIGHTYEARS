#include "Weapon/FrontalWiper.h"

namespace ly
{
	FrontalWiper::FrontalWiper(Actor* owner, float coolDonwTime, const sf::Vector2f& localOffset, float Width)
		:Shooter{owner},
		mWidth{Width},
		mShooter1{ owner, coolDonwTime, {localOffset.x - Width / 2.f, localOffset.y}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png" },
		mShooter2{ owner, coolDonwTime, {localOffset.x - Width / 4.f, localOffset.y}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" },
		mShooter3{ owner, coolDonwTime, {localOffset.x + Width / 4.f, localOffset.y}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" },
		mShooter4{ owner, coolDonwTime, {localOffset.x + Width / 2.f, localOffset.y}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png" }
	{

	}

	void FrontalWiper::ShootImpl()
	{
		mShooter1.Shoot();
		mShooter2.Shoot();
		mShooter3.Shoot();
		mShooter4.Shoot();
	}
}
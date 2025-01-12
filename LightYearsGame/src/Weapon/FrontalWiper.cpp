#include "FrontalWiper.hpp"

namespace ly
{
	FrontalWiper::FrontalWiper(Actor* owner, float coolDonwTime, const sf::Vector2f& localOffset, float Width)
		:Shooter{owner},
		mWidth{Width},
		mShooter1{ owner, coolDonwTime, {localOffset.x, localOffset.y - Width / 2.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png" },
		mShooter2{ owner, coolDonwTime, {localOffset.x, localOffset.y - Width / 6.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" },
		mShooter3{ owner, coolDonwTime, {localOffset.x, localOffset.y + Width / 2.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" },
		mShooter4{ owner, coolDonwTime, {localOffset.x, localOffset.y + Width / 6.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png" },
		mShooter5{ owner, 0.1, {localOffset.x, localOffset.y + Width / 1.5f}, 15.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" },
		mShooter6{ owner, 0.1, {localOffset.x, localOffset.y - Width / 1.5f}, -15.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" }
	{

	}

	void FrontalWiper::IncrementLevel(int amt)
	{
		Shooter::IncrementLevel(amt);
		mShooter1.IncrementLevel(amt);
		mShooter2.IncrementLevel(amt);
		mShooter3.IncrementLevel(amt);
		mShooter4.IncrementLevel(amt);

		mShooter5.IncrementLevel(amt);
		mShooter6.IncrementLevel(amt);
	}

	void FrontalWiper::ShootImpl()
	{
		mShooter1.Shoot();
		mShooter2.Shoot();
		mShooter3.Shoot();
		mShooter4.Shoot();

		if(GetCurrentLevel() == GetMaxLevel())
		{
			mShooter5.Shoot();
			mShooter6.Shoot();
		}
	}
}
#include"Enemy/Vanguard.h"
#include"Weapon/BulletShooter.h"

namespace ly 
{
	Vanguard::Vanguard(World* owningWorld, const std::string& texturePath, const sf::Vector2f& mVelocity)
		: EnemySpaceShip{ owningWorld, texturePath },
		mShooter{ new BulletShooter{this, 1.f, {50.f, 0.f}} }
	{
		SpaceShip::setVelocity(mVelocity);
	}

	void Vanguard::Tick(float deltaTime)
	{
		EnemySpaceShip::Tick(deltaTime);
		Shoot();
	}

	void Vanguard::Shoot()
	{
		mShooter->Shoot();
	}
}
#include"Enemy/Vanguard.hpp"
#include"Weapon/BulletShooter.hpp"

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
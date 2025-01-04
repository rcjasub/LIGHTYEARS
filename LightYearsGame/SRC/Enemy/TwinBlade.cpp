#include"Enemy/TwinBlade.h"
#include"weapon/BulletShooter.h"

namespace ly 
{
	TwinBlade::TwinBlade(World* owningWorld, const std::string& texturePath, const sf::Vector2f& Velocity)
		:EnemySpaceShip{owningWorld, texturePath},
		mShooterLeft{ new BulletShooter{this, 1.f, {50.f, 20.f}} },
		mShooterRight{ new BulletShooter{this, 1.f, {50.f, -20.f}} }
	{
		setVelocity(Velocity);
	}

	void TwinBlade::Tick(float deltaTime)
	{
		EnemySpaceShip::Tick(deltaTime);
		Shoot();

	}
	void TwinBlade::Shoot()
	{
		mShooterLeft->Shoot();
		mShooterRight->Shoot();
	}
}
#include "Enemy/UFO.h"
#include "Weapon/BulletShooter.h"

namespace ly
{
	UFO::UFO(World* owningWorld, const sf::Vector2f& Velocity, const std::string& texturePath, float rotationSpeed)
		:EnemySpaceShip{owningWorld, texturePath},
		mShooter1{ new BulletShooter{this, .5f, sf::Vector2f{0.f, 0.f}, -60.f} },
		mShooter2{ new BulletShooter{this, .5f, sf::Vector2f{0.f, 0.f}, 60.f} },
		mShooter3{ new BulletShooter{this, .5f, sf::Vector2f{0.f, 0.f}, 180.f} },
		mRotationSpeed{rotationSpeed}
	{
		setVelocity(Velocity);
		setActorRotation(90.f);
	}
	void UFO::Tick(float deltaTime)
	{
		EnemySpaceShip::Tick(deltaTime);
		Shoot();
		addActorRotationOffset(mRotationSpeed * deltaTime);
	}
	void UFO::Shoot()
	{
		mShooter1->Shoot();
		mShooter2->Shoot();
		mShooter3->Shoot();
	}
}
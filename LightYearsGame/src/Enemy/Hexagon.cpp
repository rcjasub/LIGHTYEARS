#include"Enemy/Hexagon.h"
#include"Weapon/BulletShooter.h"

namespace ly
{
	Hexagon::Hexagon(World* owningWorld, const std::string& textturePath, const sf::Vector2f& Velocity)
		:EnemySpaceShip{ owningWorld, textturePath },
		mShooter1{ new BulletShooter{this, 1.f, sf::Vector2f{20.f, 50.f}, 30.f} },
		mShooter2{ new BulletShooter{this, 1.f, sf::Vector2f{20.f, -50.f}, -30.f} },
		mShooter3{ new BulletShooter{this, 1.f, sf::Vector2f{50.f, 0.0f}, } },
		mShooter4{ new BulletShooter{this, 1.f, sf::Vector2f{-50.f, 0.0f}, -100.f} },
		mShooter5{ new BulletShooter{this, 1.f, sf::Vector2f{-20.f, 50.f}, 120.f} },
		mShooter6{ new BulletShooter{this, 1.f, sf::Vector2f{-20.f, -50.f}, -120.f} }
	{
		setVelocity(Velocity);
		setActorRotation(90.f);
	}
	void Hexagon::Tick(float deltaTime)
	{
		EnemySpaceShip::Tick(deltaTime);
		Shoot();
	}

	void Hexagon::Shoot()
	{
		mShooter1->Shoot();
		mShooter2->Shoot();
		mShooter3->Shoot();
		mShooter4->Shoot();
		mShooter5->Shoot();
		mShooter6->Shoot();
	}

	
}
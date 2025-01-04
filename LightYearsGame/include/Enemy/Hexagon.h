#pragma once

#include"Enemy/EnemySpaceShip.h"

namespace ly
{
	class BulletShooter;
	class Hexagon  : public EnemySpaceShip
	{
	public:
		Hexagon(World* owningWorld, const std::string& textturePath = "SpaceShooterRedux/PNG/Enemies/enemyGreen4.png", const sf::Vector2f& Velocity = sf::Vector2f{ 0.f, 100 });

		virtual void Tick(float deltaTime) override;

	private:
		virtual void Shoot() override;

		unique < BulletShooter> mShooter1;
		unique < BulletShooter> mShooter2;
		unique < BulletShooter> mShooter3;
		unique < BulletShooter> mShooter4;
		unique < BulletShooter> mShooter5;
		unique < BulletShooter> mShooter6;
	};

}
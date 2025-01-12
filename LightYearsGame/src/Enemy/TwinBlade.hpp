#pragma once

#include "EnemySpaceShip.hpp"

namespace ly
{
	class BulletShooter;
	class TwinBlade : public EnemySpaceShip
	{
	public:

		 TwinBlade(World* owningWorld, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlack1.png", const sf::Vector2f& mVelocity = { 0.f, 120.f });
		 virtual void Tick(float deltaTime) override;
		 virtual void Shoot() override;

	private:

		unique<BulletShooter> mShooterLeft;
		unique<BulletShooter> mShooterRight;
	};

}
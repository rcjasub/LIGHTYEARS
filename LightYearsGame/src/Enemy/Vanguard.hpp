#pragma once

#include"Enemy/EnemySpaceShip.hpp"

namespace ly
{
	class BulletShooter;
	class Vanguard : public EnemySpaceShip
	{
	public:
		Vanguard(World* owningWorld, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlue3.png", const sf::Vector2f& mVelocity = {0.f, 150.f});
		virtual void Tick(float deltaTime) override;
	private:
		virtual void Shoot() override;
		unique<BulletShooter> mShooter;

    };
}
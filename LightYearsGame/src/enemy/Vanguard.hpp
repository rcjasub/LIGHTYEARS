

#pragma once
#include "EnemySpaceship.hpp"
#include "BulletShooter.hpp"

namespace ly
{

class Vanguard final : public EnemySpaceship
{
public:
    explicit Vanguard(World *owningWorld, Vector2Df velocity = {0, 30}, const std::string &texturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlue3.png");
    void Tick(float deltaTime) override;
private:
    void Shoot() override;
    unique<BulletShooter> mShooter;
};

}

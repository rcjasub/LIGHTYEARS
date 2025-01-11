#pragma once
#include "EnemySpaceship.hpp"
#include "BulletShooter.hpp"
#include "MultiShooter.hpp"

namespace ly
{
class TwinBlade final : public EnemySpaceship
{
public:
    explicit TwinBlade(World *owningWorld, Vector2Df velocity = {0, 30}, const std::string &texturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlack1.png");

private:
    void Shoot() final;
    void Tick(float deltaTime) final;

    unique<BulletShooter> mShooterLeft;
    unique<BulletShooter> mShooterRight;

    MultiShooter mMultiShooter;
};

}

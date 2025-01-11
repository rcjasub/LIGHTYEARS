
#pragma once
#include "BulletShooter.hpp"
#include "EnemySpaceship.hpp"
#include "MultiShooter.hpp"


namespace ly
{
class Octagon final : public EnemySpaceship
{
public:
    explicit Octagon(World *owningWorld, Vector2Df velocity = {0, 30}, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyGreen4.png");
    ~Octagon() override = default;

    void Tick(float deltaTime) override;

private:
    void Shoot() override;

    unique<BulletShooter> mShooter1;
    unique<BulletShooter> mShooter2;
    unique<BulletShooter> mShooter3;
    unique<BulletShooter> mShooter4;
    unique<BulletShooter> mShooter5;
    unique<BulletShooter> mShooter6;
    unique<BulletShooter> mShooter7;
    unique<BulletShooter> mShooter8;

    MultiShooter mMultiShooter;
};

}

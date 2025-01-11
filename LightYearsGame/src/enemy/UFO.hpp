

#pragma once
#include "EnemySpaceship.hpp"
#include "BulletShooter.hpp"
#include "MultiShooter.hpp"

namespace ly
{

class UFO final : public EnemySpaceship
{
public:
    explicit UFO(World *owningWorld, const Vector2Df velocity, float rotationSpeed = 40.0f, const std::string &texturePath = "SpaceShooterRedux/PNG/ufoBlue.png");

    void Tick(float deltaTime) override;
private:
    void Shoot() override;
    float mRotationSpeed;
    unique<BulletShooter> mShooter1;
    unique<BulletShooter> mShooter2;
    unique<BulletShooter> mShooter3;

    MultiShooter mMultiShooter;
};

}

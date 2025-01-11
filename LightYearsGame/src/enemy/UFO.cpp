//
// Created by wbowen on 11/3/24.
//


#include "UFO.hpp"

namespace ly {
    UFO::UFO(World *owningWorld, const Vector2Df velocity, float rotationSpeed, const std::string &texturePath):
        EnemySpaceship(owningWorld, texturePath),
        mRotationSpeed{rotationSpeed},
        mShooter1{std::make_unique<BulletShooter>(this, 0.5f, Vector2Df{0.0f, 0.0f}, -60.0f)},
        mShooter2{std::make_unique<BulletShooter>(this, 0.5f, Vector2Df{0.0f, 0.0f}, 60.0f)},
        mShooter3{std::make_unique<BulletShooter>(this, 0.5f, Vector2Df{0.0f, 0.0f}, 180.0f)},
        mMultiShooter{{*mShooter1, *mShooter2, *mShooter3}}
    {
        SetVelocity(velocity);
        SetActorRotation_degrees(90.0f);
    }

    void UFO::Tick(const float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);
        Shoot();
        AddActorRotationOffset(mRotationSpeed * deltaTime);
    }

    void UFO::Shoot()
    {
        EnemySpaceship::Shoot();
        mMultiShooter.ShootAll();
    }
}



#include "Octagon.hpp"

#include "BulletShooter.hpp"

namespace ly {
    Octagon::Octagon(World *owningWorld, const Vector2Df velocity, const std::string &texturePath):
        EnemySpaceship{owningWorld, texturePath},
        mShooter1{std::make_unique<BulletShooter>(this, 1.0f, Vector2Df{20.0f, 50.0f}, 30.0f)},
        mShooter2{std::make_unique<BulletShooter>(this, 1.0f, Vector2Df{20.0f, -50.0f}, -30.0f)},
        mShooter3{std::make_unique<BulletShooter>(this, 1.0f, Vector2Df{50.0f, 0.0f}, 0.0f)},
        mShooter4{std::make_unique<BulletShooter>(this, 1.0f, Vector2Df{-50.0f, 0.0f}, -180.0f)},
        mShooter5{std::make_unique<BulletShooter>(this, 1.0f, Vector2Df{-20.0f, 50.0f}, 120.0f)},
        mShooter6{std::make_unique<BulletShooter>(this, 1.0f, Vector2Df{-20.0f, -50.0f}, -120.0f)},
        mShooter7{std::make_unique<BulletShooter>(this, 1.0f, Vector2Df{0.0f, -50.0f}, -90.0f)},
        mShooter8{std::make_unique<BulletShooter>(this, 1.0f, Vector2Df{0.0f, 50.0f}, 90.0f)},
        mMultiShooter
        {
    {
            *mShooter1,
            *mShooter2,
            *mShooter3,
            *mShooter4,
            *mShooter5,
            *mShooter6,
            *mShooter7,
            *mShooter8
            }
        }
    {
        SetVelocity(velocity);
        SetActorRotation_degrees(90.0f);
    }

    void Octagon::Tick(const float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);
        Shoot();
    }

    void Octagon::Shoot()
    {
        EnemySpaceship::Shoot();
        mMultiShooter.ShootAll();
    }
}

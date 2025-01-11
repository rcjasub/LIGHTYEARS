

#include "TwinBlade.hpp"

namespace ly
{
    TwinBlade::TwinBlade(World *owningWorld, const Vector2Df velocity, const std::string &texturePath):
    EnemySpaceship{owningWorld, texturePath},
    mShooterLeft{std::make_unique<BulletShooter>(this, 0.75f, Vector2Df{50.0f, -20.0f}, 0.0f)},
    mShooterRight{std::make_unique<BulletShooter>(this, 0.75f, Vector2Df{50.0f, 20.0f}, 0.0f)},
    mMultiShooter{{*mShooterLeft, *mShooterRight}}
    {
        SetVelocity(velocity);
        SetActorRotation_degrees(90.0f);
    }

    void TwinBlade::Shoot()
    {
        EnemySpaceship::Shoot();
        mMultiShooter.ShootAll();
    }

    void TwinBlade::Tick(const float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);
        Shoot();
    }
}

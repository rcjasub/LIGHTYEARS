
#include "Vanguard.hpp"

namespace ly {
    Vanguard::Vanguard(World *owningWorld, const Vector2Df velocity, const std::string &texturePath):
     EnemySpaceship{owningWorld, texturePath},
     mShooter{std::make_unique<BulletShooter>(this, 0.5f, Vector2Df{50.0f, 0.0f}, 0.0f)}
    {
        SetVelocity(velocity);
        SetActorRotation_degrees(90.0f);
    }

    void Vanguard::Tick(const float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);
        if(!IsPendingDestroy())
        {
            Shoot();
        }
    }

    void Vanguard::Shoot()
    {
        EnemySpaceship::Shoot();
        mShooter->Shoot();
    }
}
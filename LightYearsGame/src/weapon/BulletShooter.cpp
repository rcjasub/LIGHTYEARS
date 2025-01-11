
#include "BulletShooter.hpp"
#include "Bullet.hpp"
#include "Core.hpp"
#include "World.hpp"

namespace ly
{
    BulletShooter::BulletShooter(Actor const * const owner, const float cooldownTime, const Vector2Df localPositionOffset , const float localRotationOffset, const std::string& bulletTexturePath):
        Shooter{owner},
        mCooldownClock{},
        mCooldownTime{cooldownTime},
        mLocalPositionOffset{localPositionOffset},
        mLocalRotationOffset{localRotationOffset},
        mBulletTexturePath(bulletTexturePath)
    {
    }

    bool BulletShooter::IsOnCooldown() const
    {
        if(mCooldownClock.getElapsedTime().asSeconds() > (mCooldownTime / static_cast<float>(GetCurrentLevel())))
        {
            return false;
        }
        return true;
    }

    void BulletShooter::IncrementCurrentLevel(const unsigned amount)
    {
        Shooter::IncrementCurrentLevel(amount);
    }

    void BulletShooter::SetBulletTexturePath(const std::string &bulletTexturePath)
    {
        mBulletTexturePath = bulletTexturePath;
    }

    void BulletShooter::ShootImpl()
    {
        const Vector2Df ownerForwardDir{GetOwner()->GetActorForwardDirection()};
        const Vector2Df ownerRightDir{GetOwner()->GetActorRightDirection()};
        mCooldownClock.restart();
        const weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner()->GetWorld(), GetOwner(), mBulletTexturePath, 600.0f, 10.0f);
        newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation() + ownerForwardDir * mLocalPositionOffset.GetX() + ownerRightDir * mLocalPositionOffset.GetY());
        newBullet.lock()->SetActorRotation_degrees(GetOwner()->GetActorRotation_rad() + mLocalRotationOffset);
    }
}

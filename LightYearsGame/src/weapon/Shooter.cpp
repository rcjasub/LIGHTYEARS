
#include "Shooter.hpp"
#include "Actor.hpp"

namespace ly
{
    void Shooter::Shoot()
    {
        if(CanShoot() && !IsOnCooldown() && !GetOwner()->IsPendingDestroy())
        {
            ShootImpl();
        }
    }

    void Shooter::IncrementCurrentLevel(const unsigned int level)
    {
        mCurrentLevel += level;
        mCurrentLevel = std::clamp(mCurrentLevel, 0U, mMaxLevel);
    }

    void Shooter::SetCurrentLevel(unsigned int level)
    {
        mCurrentLevel = level;
        mCurrentLevel = std::clamp(mCurrentLevel, 0U, mMaxLevel);
    }

    Shooter::Shooter(Actor const * const owner, const unsigned int currentLevel, const unsigned int maxLevel):
        mOwner{owner},
        mCurrentLevel{currentLevel},
        mMaxLevel{maxLevel}
    {

    }
}

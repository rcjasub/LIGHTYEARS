
#include "FrontalWiper.hpp"

namespace ly {
    FrontalWiper::FrontalWiper(const Actor *owner,
                               const float cooldownTime,
                               const Vector2Df &localPositionOffset,
                               float localRotationOffset,
                               const float width):
    BulletShooter{owner, 0.0},
    mWidth{width},
    mShooter1{owner, cooldownTime, {localPositionOffset.GetX(), localPositionOffset.GetY() - width/2.0f }, 0.0f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"},
    mShooter2{owner, cooldownTime, {localPositionOffset.GetX(), localPositionOffset.GetY() - width/6.0f }, 0.0f,  "SpaceShooterRedux/PNG/Lasers/laserBlue07.png"},
    mShooter3{owner, cooldownTime, {localPositionOffset.GetX(), localPositionOffset.GetY() + width/6.0f }, 0.0f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png"},
    mShooter4{owner, cooldownTime, {localPositionOffset.GetX(), localPositionOffset.GetY() + width/2.0f }, 0.0f,  "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"},
    mMultiShooter{mShooter1, mShooter2, mShooter3, mShooter4},
    mTopLevelShooterLeft{owner, cooldownTime / 1.5f, {localPositionOffset.GetX(), localPositionOffset.GetY() + width/1.5f }, 7.5f,  "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"},
    mTopLevelShooterRight{owner, cooldownTime / 1.5f, {localPositionOffset.GetX(), localPositionOffset.GetY() - width/1.5f }, -7.5f,  "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"},
    mTopLevelMultiShooter{mTopLevelShooterLeft, mTopLevelShooterRight}
    {
    }

    void FrontalWiper::IncrementCurrentLevel(const unsigned amount)
    {
        BulletShooter::IncrementCurrentLevel(amount);
        mMultiShooter.IncrementLevelAll(amount);
        mTopLevelMultiShooter.IncrementLevelAll(amount);
    }

    void FrontalWiper::SetCurrentLevel(unsigned int amount)
    {
        BulletShooter::SetCurrentLevel(amount);
        mMultiShooter.SetCurrentLevel(amount);
        mTopLevelMultiShooter.SetCurrentLevel(amount);
    }

    void FrontalWiper::ShootImpl()
    {
        mMultiShooter.ShootAll();
        if(GetCurrentLevel() >= GetMaxLevel())
        {
            mTopLevelMultiShooter.ShootAll();
        }
    }
}
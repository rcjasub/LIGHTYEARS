
#include "ThreeWayShooter.hpp"

namespace ly {
    ThreeWayShooter::ThreeWayShooter(const Actor *owner, float cooldownTime, const Vector2Df &localPositionOffset, float localRotationOffset):
    Shooter{owner},
    mShooterLeft{owner, cooldownTime, localPositionOffset + Vector2Df{10.0, -10.0}, localRotationOffset + -1*30, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
    mShooterMid{owner, cooldownTime, localPositionOffset + Vector2Df{0.0, 0.0}, localRotationOffset, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
    mShooterRight{owner, cooldownTime, localPositionOffset + Vector2Df{10.0, 10.0}, localRotationOffset + 30, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
    mMultiShooter{{mShooterLeft, mShooterMid, mShooterRight}},
    mTopLevelShooterLeft{owner, cooldownTime, localPositionOffset + Vector2Df{10.0, 10.0}, localRotationOffset + 15, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
    mTopLevelShooterRight{owner, cooldownTime, localPositionOffset + Vector2Df{10.0, -10.0}, localRotationOffset - 15, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
    mTopLevelMultiShooter{{mTopLevelShooterLeft, mTopLevelShooterRight}}
    {
    }

    void ThreeWayShooter::IncrementCurrentLevel(unsigned amount)
    {
        Shooter::IncrementCurrentLevel(amount);
        mMultiShooter.IncrementLevelAll(amount);
        mTopLevelMultiShooter.IncrementLevelAll(amount);
    }

    void ThreeWayShooter::SetCurrentLevel(unsigned amount)
    {
        Shooter::SetCurrentLevel(amount);
        mMultiShooter.SetCurrentLevel(amount);
        mTopLevelMultiShooter.SetCurrentLevel(amount);
    }

    void ThreeWayShooter::ShootImpl()
    {
        mMultiShooter.ShootAll();
        if(GetCurrentLevel() >= GetMaxLevel())
        {
            mTopLevelMultiShooter.ShootAll();
        }
    }
}

#pragma once
#include "BulletShooter.hpp"
#include "MultiShooter.hpp"

namespace ly {

class ThreeWayShooter final : public Shooter
{
public:
    explicit ThreeWayShooter(const Actor *owner, float cooldownTime = 0.3f, const Vector2Df &localPositionOffset = {}, float localRotationOffset = {});

    void IncrementCurrentLevel(unsigned amount) override;
    void SetCurrentLevel(unsigned amount) override;
private:
    BulletShooter mShooterLeft;
    BulletShooter mShooterMid;
    BulletShooter mShooterRight;
    MultiShooter mMultiShooter;

    BulletShooter mTopLevelShooterLeft;
    BulletShooter mTopLevelShooterRight;
    MultiShooter mTopLevelMultiShooter;

    void ShootImpl() override;
};

} // ly

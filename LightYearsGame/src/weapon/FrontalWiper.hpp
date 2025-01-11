
#pragma once
#include "BulletShooter.hpp"
#include "MultiShooter.hpp"

namespace ly
{

class FrontalWiper final : public BulletShooter
{
public:
    explicit FrontalWiper(const Actor *owner,
                 float cooldownTime = 0.3f,
                 const Vector2Df &localPositionOffset = {},
                 float localRotationOffset = {},
                 float width = 60.0f);

    void IncrementCurrentLevel(unsigned amount) override;
    void SetCurrentLevel(unsigned int amount) override;
private:
    void ShootImpl() override;

    float mWidth;

    BulletShooter mShooter1;
    BulletShooter mShooter2;
    BulletShooter mShooter3;
    BulletShooter mShooter4;
    MultiShooter mMultiShooter;

    BulletShooter mTopLevelShooterLeft;
    BulletShooter mTopLevelShooterRight;
    MultiShooter mTopLevelMultiShooter;
};

}

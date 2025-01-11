

#pragma once
#include "EnemySpaceship.hpp"
#include "FrontalWiper.hpp"
#include "MultiShooter.hpp"
#include "ThreeWayShooter.hpp"

namespace ly
{

class Boss final : public EnemySpaceship
{
public:
    explicit Boss(World* world);

protected:
    void Tick(float deltaTime) override;

private:
    void CheckMove();
    float mSpeed;
    float mBaseSpeed;
    float mSwitchDistanceToEdge;

    BulletShooter mBaseShooterLeft;
    BulletShooter mBaseShooterRight;
    MultiShooter mBaseShooters;

    ThreeWayShooter mThreeWayShooter;
    FrontalWiper mFrontalWiperShooterLeft;
    FrontalWiper mFrontalWiperShooterRight;
    MultiShooter mFrontalWiperShooters;

    BulletShooter mFinalStageShooterLeft;
    BulletShooter mFinalStageShooterRight;

    void ShootBaseShooters();
    void ShootThreeWayShooter();
    void ShootFrontalWiper();

    int mStage;
    void SetStage(int newStage);
    void IncreaseStage();
    void BeginPlay() override;
    void HealthChanged(float amount, float currentHealth, float maxHealth);
};

}

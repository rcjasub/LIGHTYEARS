
#include "Boss.hpp"

#include "MathUtility.hpp"

namespace ly
{
    Boss::Boss(World *world):
    EnemySpaceship{world,"SpaceShooterRedux/PNG/Enemies/boss.png"},
    mSpeed{100.0f},
    mBaseSpeed{100.0f},
    mSwitchDistanceToEdge{100.0f},
    mBaseShooterLeft{this, 0.5f, {50.0f, -50.0f}},
    mBaseShooterRight{this, 0.5f, {50.0f, 50.0f}},
    mBaseShooters({mBaseShooterLeft, mBaseShooterRight}),
    mThreeWayShooter{this, 4.0f, {100.0f, 0.0f}},
    mFrontalWiperShooterLeft{this, 5.0f, {80.0f, -100.0f}},
    mFrontalWiperShooterRight{this, 5.0f, {80.0f, 100.0f}},
    mFrontalWiperShooters{mFrontalWiperShooterLeft, mFrontalWiperShooterRight}, // todo -- fix
    mFinalStageShooterLeft{this, 0.3f, {50, -150}},
    mFinalStageShooterRight{this, 0.3f, {50, 150}},
    mStage{1}
    {
        SetActorRotation_degrees(90.0f);
        SetVelocity({mSpeed, 0.0f});
        SetRewardSpawnWeight(0.0f); // Todo -- fix
    }

    void Boss::Tick(float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);
        ShootBaseShooters();
        ShootFrontalWiper();
        ShootThreeWayShooter();
        if(mStage >= 4)
        {
            mFinalStageShooterLeft.Shoot();
            mFinalStageShooterRight.Shoot();
        }
        CheckMove();
    }

    void Boss::CheckMove()
    {
        if(GetActorLocation().GetX() > static_cast<float>(GetWidowSize().GetX()) - mSwitchDistanceToEdge)
        {
            SetVelocity({-mSpeed, 0.0f});
        }
        else if(GetActorLocation().GetX() < mSwitchDistanceToEdge)
        {
            SetVelocity({mSpeed, 0.0f});
        }
    }

    void Boss::ShootBaseShooters()
    {
        mBaseShooters.ShootAll();
    }

    void Boss::ShootThreeWayShooter()
    {
        mThreeWayShooter.Shoot();
    }

    void Boss::ShootFrontalWiper()
    {
        // mFrontalWiperShooters.ShootAll();
        mFrontalWiperShooterLeft.Shoot();
        mFrontalWiperShooterRight.Shoot();
    }

    void Boss::SetStage(const int newStage)
    {
        mStage = newStage;
        mBaseShooters.SetCurrentLevel(mStage);
        mThreeWayShooter.SetCurrentLevel(mStage);
        mFrontalWiperShooterLeft.SetCurrentLevel(mStage);
        mFrontalWiperShooterRight.SetCurrentLevel(mStage);
        mSpeed = static_cast<float>(mStage) * mBaseSpeed;
    }

    void Boss::IncreaseStage()
    {

    }

    void Boss::BeginPlay()
    {
        EnemySpaceship::BeginPlay();
        HealthComponent& healthComp{GetHealthComponent()};
        healthComp.SetInitialHealth(3000.0, 3000.0);
        healthComp.OnHealthChanged.BindAction(GetSelfWeakSRef(), &Boss::HealthChanged);
    }

    void Boss::HealthChanged(float amount, float currentHealth, float maxHealth)
    {
        const float percentLeft = currentHealth / maxHealth;

        unsigned int maxLevel {mBaseShooterLeft.GetMaxLevel()};

        if(MathUtility::NumberInRangeInclusive(percentLeft, 0.5f, 0.7f, 0.001))
        {
            SetStage(maxLevel / 3U);
        }
        else if(MathUtility::NumberInRangeInclusive(percentLeft, 0.3f, 0.5f, 0.001))
        {
            SetStage(maxLevel / 2);
        } else if (percentLeft < 0.3f)
        {
            SetStage(maxLevel);
        }

    }
}

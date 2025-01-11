
#pragma once
#include "Reward.hpp"
#include "Spaceship.hpp"

namespace ly {

class EnemySpaceship: public Spaceship
{
public:
    EnemySpaceship(World* owningWorld,
        const std::string& texturePath,
        float collisionDamage = 200.0f,
        float rewardSpawnRate = 0.5f,
        const List<RewardFactoryFunction> &rewardFactories =
        {
        CreateHealthReward,
        CreateThreeWayShooterReward,
        CreateFrontalSwiperReward,
        CreateDefaultWeaponReward,
        CreateLifeReward,
        });

    void SetScoreAmount(const uint8_t scoreAmount) {mScoreAmount = scoreAmount;}
    void SetRewardSpawnWeight(float weight);
protected:
    void Tick(float deltaTime) override;

private:
    float mCollisionDamage;
    float mRewardSpawnWeight;
    uint8_t mScoreAmount;

    virtual void SpawnReward();
    void Blew() override;
    void OnActorBeginOverlap(Actor *other) override;
    List<RewardFactoryFunction> mRewardFactories;
};

}

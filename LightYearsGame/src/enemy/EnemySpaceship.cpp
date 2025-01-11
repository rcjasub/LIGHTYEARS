

#include "EnemySpaceship.hpp"
#include "MathUtility.hpp"
#include "PlayerManager.hpp"

namespace ly
{
    EnemySpaceship::EnemySpaceship(World *owningWorld,
        const std::string &texturePath,
        const float collisionDamage,
        const float rewardSpawnRate,
        const List<RewardFactoryFunction> &rewardFactories):
        Spaceship{"Enemy Spaceship", owningWorld, texturePath},
        mCollisionDamage{collisionDamage},
        mRewardFactories{rewardFactories},
        mScoreAmount{10},
        mRewardSpawnWeight{rewardSpawnRate}
    {
        SetTeamId(2);
    }

    void EnemySpaceship::SetRewardSpawnWeight(float weight)
    {
        if(weight <= 0 || weight > 1)
        {
            return;
        }

        mRewardSpawnWeight = weight;
    }

    void EnemySpaceship::Tick(const float deltaTime)
    {
        Spaceship::Tick(deltaTime);
        if(IsActorOutOfWindowBounds(GetActorGlobalBounds().width * 2))
        {
            Destroy();
        }
    }

    void EnemySpaceship::SpawnReward() {
        if(mRewardFactories.empty()) return;

        if(mRewardSpawnWeight < MathUtility::RandomRange(0.0f, 1.0f))
        {
            return;
        }
        const auto pickIndex = static_cast<unsigned int>(MathUtility::RandomRange(0, mRewardFactories.size()));
        if(pickIndex >= 0 && pickIndex < mRewardFactories.size())
        {
            weak<Reward> newReward{mRewardFactories[pickIndex](GetWorld())};
            newReward.lock()->SetActorLocation(GetActorLocation());
        }
    }

    void EnemySpaceship::Blew()
    {
        SpawnReward();
        const auto player{PlayerManager::GetInstance().GetPlayer()};
        if(player != nullptr)
        {
            player->AddScore(mScoreAmount);
        }
    }

    void EnemySpaceship::OnActorBeginOverlap(Actor *other)
    {
        Spaceship::OnActorBeginOverlap(other);
        if(IsOtherHostile(other))
        {
            other->ApplyDamage(mCollisionDamage);
        }
    }
}

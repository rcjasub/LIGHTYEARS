
#pragma once
#include "Actor.hpp"
#include "World.hpp"

namespace ly
{
class Reward;
class PlayerSpaceship;

using RewardFunction = std::function<void(PlayerSpaceship*)>;
using RewardFactoryFunction = std::function<weak<Reward> (World*)>;
class Reward: public Actor
{
public:
    Reward(World* world, const std::string& texturePath, RewardFunction rewardFunction, float speed = 200.0f);

    void BeginPlay() override;
    void Tick(const float deltaTime) override;

private:
    void OnActorBeginOverlap(Actor *other) override;
    float mSpeed;
    RewardFunction mRewardFunction;

};

weak<Reward> CreateHealthReward(World* world);
weak<Reward> CreateThreeWayShooterReward(World* world);
weak<Reward> CreateFrontalSwiperReward(World* world);
weak<Reward> CreateDefaultWeaponReward(World* world);
weak<Reward> CreateLifeReward(World* world);

weak<Reward> CreateReward(World* world, const std::string& texturePath, const RewardFunction &rewardFunction);

void RewardHealth(PlayerSpaceship* player);
void RewardThreeWayShoot(PlayerSpaceship* player);
void RewardFrontalWiper(PlayerSpaceship* player);
void RewardDefaultWeapon(PlayerSpaceship* player);
void RewardLife(PlayerSpaceship* player);
}

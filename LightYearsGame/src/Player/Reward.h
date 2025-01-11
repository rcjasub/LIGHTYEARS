#pragma once 

#include <functional>
#include "framework/Actor.h"


namespace ly
{
	class Reward;
	class PlayerSpaceShip;
	using RewardFunc = std::function<void(PlayerSpaceShip*)>;
	using RewardFactoryFunc = std::function<weak<Reward>(World*)>;

	class Reward : public Actor
	{
	public:
		Reward(World* world, const std::string& texturePath, RewardFunc rewardFunc, float speed = 200.f);
		virtual void BeganPlay() override;
		virtual void Tick(float deltaTime) override;
		
	private:
		virtual void OnActorBeginOverlap(Actor* other) override;

		float mSpeed;
		RewardFunc mRewardFunc;
	};

	weak<Reward> CreateHealthReward(World* world);
	weak<Reward> CreateThreeWayShooterReward(World* world);
	weak<Reward> CreateFrontalWiperReward(World* world);

	weak<Reward> CreateReward(World* world, const std::string& texturePath, RewardFunc rewardFunc);

	void RewardHealth(PlayerSpaceShip* player);
	void RewardThreeWayShooter(PlayerSpaceShip* player);
	void RewardFrontalWiper(PlayerSpaceShip* player);
}


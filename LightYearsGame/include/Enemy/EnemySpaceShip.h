#pragma once

#include"SpaceShip/SpaceShip.h"
#include"Player/Reward.h"

namespace ly
{
	class EnemySpaceShip : public SpaceShip
	{
	public:
		EnemySpaceShip(World* owningWorld, 
			const std::string& texturePath, 
			float collisionDamge = 200.f,
			const list<RewardFactoryFunc>& reward = 
			{
				CreateHealthReward,
				CreateThreeWayShooterReward,
				CreateFrontalWiperReward
			}
		);

		virtual void Tick(float deltaTime) override;

	private:
		void SpawnReward();
		float mcollisionDamage;
		virtual void OnActorBeginOverlap(Actor* other) override;
		virtual void Blew() override;
		list<RewardFactoryFunc> mRewardFactories;

	};


}
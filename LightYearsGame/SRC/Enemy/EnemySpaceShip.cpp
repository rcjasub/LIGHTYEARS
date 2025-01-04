#include"Enemy/EnemySpaceShip.h"
#include"framework/MessUtility.h"

namespace ly
{
	EnemySpaceShip::EnemySpaceShip(World* owningWorld, const std::string& texturePath, float collisionDamge, const list<RewardFactoryFunc>& reward)
		:SpaceShip{ owningWorld, texturePath }, 
		mcollisionDamage{ collisionDamge }, 
		mRewardFactories{ reward }
	{
		setTeamId(2);
	}
	
	void EnemySpaceShip::Tick(float deltaTime)
	{
		SpaceShip::Tick(deltaTime);
		if (isActorIsOutOfWindowBound(GetActorGlobalBounds().width * 2.f))
		{
			Destroy();
		}
	}

	void EnemySpaceShip::SpawnReward()
	{
		if (mRewardFactories.size() == 0) { return; }	

		int pick = (int)RandomRange(0, mRewardFactories.size());

		if (pick >= 0 && pick < mRewardFactories.size())
		{
			weak<Reward> newReward = mRewardFactories[pick](GetWorld());
			newReward.lock()->SetActorLocation(GetActorLocation());
		}

	}

	void EnemySpaceShip::OnActorBeginOverlap(Actor* other)
	{
		SpaceShip::OnActorBeginOverlap(other);
		if (IsOtherHostile(other))
		{
			other->ApplyDamage(mcollisionDamage);
		}
	}

	void EnemySpaceShip::Blew()
	{
		SpawnReward();
	}
}
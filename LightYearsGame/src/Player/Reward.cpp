#include "Player/Reward.hpp"
#include "Player/PlayerSpaceShip.hpp"
#include "Weapon/ThreeWayShooter.hpp"
#include "Weapon/FrontalWiper.hpp"
#include "framework/world.hpp"

namespace ly
{
	Reward::Reward(World* world, const std::string& texturePath, RewardFunc rewardFunc, float speed)
		: Actor(world, texturePath)
		, mSpeed(speed)
		, mRewardFunc(rewardFunc)
	{
	}

	void Reward::BeganPlay()
	{
		Actor::BeganPlay();
		setEnablePhysics(true);
	}

	void Reward::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		addActorLocationOffset({ 0.f, mSpeed * deltaTime });
	}

	void Reward::OnActorBeginOverlap(Actor* other)
	{
		PlayerSpaceShip* playerSpaceShip = dynamic_cast<PlayerSpaceShip*>(other);
		if (playerSpaceShip != nullptr && !playerSpaceShip->IsPendingDestroy())
		{
			mRewardFunc(playerSpaceShip);
			Destroy();
		}
	}

	weak<Reward> CreateHealthReward(World* world)
	{
		return	CreateReward(world, "SpaceShooterRedux/PNG/Power-ups/pill_green.png", RewardHealth);
	}

	weak<Reward> CreateThreeWayShooterReward(World* world)
	{
		return	CreateReward(world, "SpaceShooterRedux/PNG/pickups/three_shooter_pickup.png", RewardThreeWayShooter);
	}

	weak<Reward> CreateFrontalWiperReward(World* world)
	{
		return	CreateReward(world, "SpaceShooterRedux/PNG/pickups/front_row_shooter_pickup.png", RewardFrontalWiper);
	}

	weak<Reward> CreateReward(World* world, const std::string& texturePath, RewardFunc rewardFunc)
	{
		weak<Reward> reward = world->SpamActor<Reward>(texturePath, rewardFunc);
		return reward;
	}

	void RewardHealth(PlayerSpaceShip* player)
	{
		static float rewardAmt = 10.f;
		if (player && !player->IsPendingDestroy())
		{
			player->GetHealthComponent().ChangeHealth(rewardAmt);
		}
	}

	void RewardThreeWayShooter(PlayerSpaceShip* player)
	{
		if (player && !player->IsPendingDestroy())
		{
			player->SetShooter(unique<Shooter>{new ThreeWayShooter{ player, 0.4f, {50.f, 0.f} }});
		}
	}

	void RewardFrontalWiper(PlayerSpaceShip* player)
	{
		if (player && !player->IsPendingDestroy())
		{
			player->SetShooter(unique<Shooter>{new FrontalWiper{ player, 0.4f, {50.f, 0.f} }});
		}
	}
}
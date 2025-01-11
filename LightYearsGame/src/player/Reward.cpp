
#include "Reward.hpp"

#include "FrontalWiper.hpp"
#include "PlayerManager.hpp"
#include "PlayerSpaceship.hpp"
#include "ThreeWayShooter.hpp"

namespace ly
{
    Reward::Reward(World *world, const std::string &texturePath, RewardFunction rewardFunction, float speed):
    Actor{"Reward", world, texturePath},
    mSpeed{speed},
    mRewardFunction{std::move(rewardFunction)}
    {
    }

    void Reward::BeginPlay()
    {
        Actor::BeginPlay();
        SetEnablePhysics(true);
    }

    void Reward::Tick(const float deltaTime)
    {
        Actor::Tick(deltaTime);
        AddActorLocationOffset({0.0f, mSpeed * deltaTime});
    }

    void Reward::OnActorBeginOverlap(Actor *other)
    {
        if(other == nullptr  ||  other->IsPendingDestroy())
        {
            return;
        }
        if(PlayerManager::GetInstance().GetPlayer() == nullptr)
        {
            return;
        }

        const weak<PlayerSpaceship> playerSpaceship{PlayerManager::GetInstance().GetPlayer()->GetCurrentPlayerSpaceship()};
        if(playerSpaceship.expired() || playerSpaceship.lock()->IsPendingDestroy())
        {
            return;
        }

        if(playerSpaceship.lock()->GetUniqueId() == other->GetUniqueId())
        {
            mRewardFunction(playerSpaceship.lock().get());
            Destroy();
        }

    }

    weak<Reward> CreateHealthReward(World *world)
    {
        return CreateReward(world, "SpaceShooterRedux/PNG/pickups/pill_green.png", RewardHealth);
    }

    weak<Reward> CreateThreeWayShooterReward(World *world)
    {
        return CreateReward(world, "SpaceShooterRedux/PNG/pickups/three_shooter_pickup.png", RewardThreeWayShoot);
    }

    weak<Reward> CreateFrontalSwiperReward(World *world)
    {
        return CreateReward(world, "SpaceShooterRedux/PNG/pickups/front_row_shooter_pickup.png", RewardFrontalWiper);
    }

    weak<Reward> CreateDefaultWeaponReward(World *world)
    {
        return CreateReward(world, "SpaceShooterRedux/PNG/Lasers/laserBlue09.png", RewardDefaultWeapon);
    }

    weak<Reward> CreateLifeReward(World *world)
    {
        return CreateReward(world, "SpaceShooterRedux/PNG/pickups/playerLife1_blue.png", RewardLife);
    }

    weak<Reward> CreateReward(World *world, const std::string &texturePath, const RewardFunction &rewardFunction)
    {
        weak<Reward> reward = world->SpawnActor<Reward>(world,texturePath, rewardFunction);
        return reward;
    }

    void RewardHealth(PlayerSpaceship *player)
    {
        static float rewardAmount = 10.0f;
        if (player != nullptr && !player->IsPendingDestroy())
        {
            player->GetHealthComponent().ChangeHealth(rewardAmount);
        }
    }

    void RewardThreeWayShoot(PlayerSpaceship *player)
    {
        if (player != nullptr && !player->IsPendingDestroy())
        {
            player->SetShooter(unique<Shooter>{std::make_unique<ThreeWayShooter>(player, 0.4f, Vector2Df{50.0f, 0.0f})});
        }
    }

    void RewardFrontalWiper(PlayerSpaceship *player)
    {
        if (player != nullptr && !player->IsPendingDestroy())
        {
            player->SetShooter(unique<Shooter>{std::make_unique<FrontalWiper>(player, 0.4f, Vector2Df{50.0f, 0.0f})});
        }
    }

    void RewardDefaultWeapon(PlayerSpaceship *player)
    {
        if (player != nullptr && !player->IsPendingDestroy())
        {
            player->SetShooter(unique<Shooter>{std::make_unique<BulletShooter>(player, 0.15f, Vector2Df{50.0f, 0.0f})});
        }
    }

    void RewardLife(PlayerSpaceship *player)
    {
        if (PlayerManager::GetInstance().GetPlayer() == nullptr)
        {
            return;
        }

        PlayerManager::GetInstance().GetPlayer()->AddLifeCount(1U);
    }
}

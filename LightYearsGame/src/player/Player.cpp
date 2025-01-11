
#include "Player.hpp"
#include "PlayerSpaceship.hpp"
#include "World.hpp"

namespace ly
{
    Player::Player(const std::string& name):
    Object{name},
    mPlayerLifeCount{3},
    mScore{0},
    mCurrentPlayerSpaceship{}
    {
    }

    weak<PlayerSpaceship> Player::SpawnPlayerSpaceship(World *world)
    {
        if(mPlayerLifeCount > 0)
        {
            --mPlayerLifeCount;
            const auto windowSize = world->GetWindowSize();
            mCurrentPlayerSpaceship = world->SpawnActor<PlayerSpaceship>("PlayerSpaceship", world, "SpaceShooterRedux/PNG/playerShip1_blue.png");
            mCurrentPlayerSpaceship.lock()->SetActorLocation({static_cast<float>(windowSize.GetX()) / 2.0f, static_cast<float>(windowSize.GetY()) - 100.0f});
            mCurrentPlayerSpaceship.lock()->SetActorRotation_degrees(-90.0f);
            onLifeChanged.Broadcast(static_cast<int>(mPlayerLifeCount));
            return mCurrentPlayerSpaceship;
        }
        else
        {
            mCurrentPlayerSpaceship = weak<PlayerSpaceship>{};
            onLifeExhausted.Broadcast();
            return weak<PlayerSpaceship>{};
        }
    }

    void Player::AddLifeCount(const unsigned int count)
    {
        if(count > 0)
        {
            mPlayerLifeCount += count;
            onLifeChanged.Broadcast(static_cast<int>(mPlayerLifeCount));
        }
    }

    void Player::AddScore(const unsigned int amount)
    {
        if(amount > 0)
        {
            mScore += amount;
            onScoreChanged.Broadcast(static_cast<int>(mScore));
        }
    }
}

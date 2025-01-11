#include "Player.h"
#include "framework/world.h"
#include "Player/PlayerSpaceShip.h"

namespace ly
{
	Player::Player()
		:mLifeCount(3),
		 mScore(0),
		 mCurrentPlayerSpaceShip{}
	{
	}

	weak<PlayerSpaceShip> Player::SpawnSpaceShip(World* world)
	{
		if (mLifeCount > 0)
		{
			--mLifeCount;

			auto WindowSize = world->GetWindowSize();
			mCurrentPlayerSpaceShip = world->SpamActor<PlayerSpaceShip>();
			mCurrentPlayerSpaceShip.lock()->SetActorLocation(sf::Vector2f(WindowSize.x/2.f, WindowSize.y - 100.f));
			mCurrentPlayerSpaceShip.lock()->setActorRotation(-90.f);
			OnLifeChange.BroadCast(mLifeCount);
			return mCurrentPlayerSpaceShip;
		}
		else
		{
			OnLifeExhausted.BroadCast();
		}
		return weak<PlayerSpaceShip>{};
	}

	void Player::AddLifeCount(unsigned int count)
	{
		if (count > 0)
		{
			mLifeCount += count;
			OnLifeChange.BroadCast(mLifeCount);
		}
	}

	void Player::AddScore(unsigned int amt)
	{
		if (amt > 0)
		{
			mScore = amt;
			OnScoreChange.BroadCast(mScore);
		}
	}
}
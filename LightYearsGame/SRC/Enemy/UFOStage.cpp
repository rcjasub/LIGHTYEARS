#include "Enemy/UFOStage.h"
#include "framework/MessUtility.h"
#include "framework/world.h"
#include "Enemy/UFO.h"

namespace ly
{
	UFOStage::UFOStage(World* world)
		:GameStage{world},
		mSpawnInterval{4.f},
		mSpawnAmt{10},
		mCurrentSpawnAmt{0},
		mUFOspeed{200.f}
	{
	}

	void UFOStage::StartStage()
	{
		mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &UFOStage::SpawnUFO, mSpawnInterval, true);
	}

	void UFOStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(mSpawnTimer);
	}

	sf::Vector2f UFOStage::GetRandomSpawnLoc() const
	{
		auto windowSize = GetWorld()->GetWindowSize();

		float SpawnLeft = RandomRange(-1, 1);
		float SpawnLockX = 0;

		if (SpawnLeft < 0)
		{
			SpawnLockX = windowSize.x + 100.f;
		}
		else
		{
			SpawnLockX = -100.f;
		}

		float spawnLockY = RandomRange(0, windowSize.y);
		
		return sf::Vector2f{ SpawnLockX, spawnLockY };
	}

	void UFOStage::SpawnUFO()
	{
		sf::Vector2f SpawnLoc = GetRandomSpawnLoc();
		auto windowSize = GetWorld()->GetWindowSize();
		sf::Vector2f center{ windowSize.x / 2.f, windowSize.y / 2.f };
		sf::Vector2f spawmnLocToCenter{ center.x - SpawnLoc.x, center.y - SpawnLoc.y };
		Normalize(spawmnLocToCenter);

		sf::Vector2f spawnVelocity = spawmnLocToCenter * mUFOspeed;

		weak<UFO> newUFO = GetWorld()->SpamActor<UFO>(spawnVelocity);
		newUFO.lock()->SetActorLocation(SpawnLoc);

		if (++mCurrentSpawnAmt == mSpawnAmt)
		{
			FinishStage();
		}

	}

}
#include"Enemy/VanguardStage.h"
#include"framework/world.h"
#include"Enemy/Vanguard.h"
#include"Weapon/BulletShooter.h"

namespace ly
{
	VanguardStage::VanguardStage(World* world)
		:GameStage{ world },
		mSpawnInterval{ 4.f },
		mSwitchInterval{ 6.f },
		mSpawnDistanceToEdge{ 100.f },
		mLeftSpawnLoc{ 0.0f, 0.0f },
		mRightSpawnLoc{ 0.0f, 0.0f },
		mSpawnLoc{ 0.0f, 0.0f },
		mRowsToSpawn{ 4 },
		mRowsSpawnCount{ 0 },
		mCurrentRowVanguardCount{ 0 },
		mVarguardsPerRow{ 5 }

	{
	}

	void VanguardStage::StartStage()
	{
		auto windowSize = GetWorld()->GetWindowSize();
		mLeftSpawnLoc = sf::Vector2f{ mSpawnDistanceToEdge, -100.f };
		mRightSpawnLoc = sf::Vector2f{ windowSize.x - mSpawnDistanceToEdge, -100 };

		SwitchRow();
	}

	void VanguardStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(mSpawnTimerHandle);
		TimerManager::Get().ClearTimer(mSwitchTimerHandle);
	}

	void VanguardStage::SpawnVanguard()
	{
		weak<Vanguard> newVanguard = GetWorld()->SpamActor<Vanguard>();
		newVanguard.lock()->SetActorLocation(mSpawnLoc);
		++mCurrentRowVanguardCount;

		if (mCurrentRowVanguardCount == mVarguardsPerRow)
		{
			TimerManager::Get().ClearTimer(mSpawnTimerHandle);
			mSwitchTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SwitchRow, mSwitchInterval, false);
			mCurrentRowVanguardCount = 0;
		}
	}

	void VanguardStage::SwitchRow()
	{
		if (mRowsSpawnCount == mRowsToSpawn)
		{
			FinishStage();
			return;
		}

		if (mSpawnLoc == mLeftSpawnLoc)
		{
			mSpawnLoc == mRightSpawnLoc;
		}

		else
		{
			mSpawnLoc == mLeftSpawnLoc;
		}

        mSpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SpawnVanguard, mSpawnInterval, true);
		
		++mRowsSpawnCount;
	}

} 


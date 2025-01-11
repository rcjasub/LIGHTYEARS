#include"Enemy/TwinBladeStage.h"
#include"framework/world.h"
#include"Enemy/TwinBlade.h"
#include"Weapon/BulletShooter.h"

namespace ly
{
	TwinBladeStage::TwinBladeStage(World* world)
		:GameStage{ world },
		mSpawnInterval{ 1.5f },
		mSpawnDistanceToCenter{ 100.f },
		mLeftSpawnLoc{ world->GetWindowSize().x/2.f - mSpawnDistanceToCenter, -100.f },
		mRightSpawnLoc{ world->GetWindowSize().x + mSpawnDistanceToCenter, -100.f },
		mSpawnLoc{mLeftSpawnLoc},
		mSpawnAmt{10},
		mCurrentSpawnCount{0}

	{
	}

	void TwinBladeStage::StartStage()
	{
		mSpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &TwinBladeStage::SpawnTwinBlade, mSpawnInterval, true);

	}
	void TwinBladeStage::SpawnTwinBlade()
	{
		weak<TwinBlade> newTwinBlade = GetWorld()->SpamActor <TwinBlade> ();
		newTwinBlade.lock()->SetActorLocation(mSpawnLoc);
		if (mSpawnLoc == mLeftSpawnLoc)
		{
			mSpawnLoc = mRightSpawnLoc;
		}
		else
		{
			mSpawnLoc = mRightSpawnLoc;
		}

		++mCurrentSpawnCount;
		if (mCurrentSpawnCount == mSpawnAmt)
		{
			FinishStage();
		}
	}

	void TwinBladeStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(mSpawnTimerHandle);
	}
}
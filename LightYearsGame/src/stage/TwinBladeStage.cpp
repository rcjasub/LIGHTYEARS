
#include "TwinBladeStage.hpp"
#include "TwinBlade.hpp"
#include "World.hpp"

namespace ly
{
    TwinBladeStage::TwinBladeStage(World *world):
        GameStage{"TwinBlade Stage", world},
        mSpawnInterval{1.5f},
        mSpawnDistanceToCenter{100.0f},
        mLeftSpawnLocation{static_cast<float>(world->GetWindowSize().GetX()) / 2.0f - mSpawnDistanceToCenter, -100.0f},
        mRightSpawnLocation{static_cast<float>(world->GetWindowSize().GetX()) / 2.0f + mSpawnDistanceToCenter, -100.0f},
        mSpawnLocation{mLeftSpawnLocation},
        mSpawnAmount{10},
        mCurrentSpawnCount{0}
    {
    }

    void TwinBladeStage::StartStage()
    {
        GameStage::StartStage();
        mSpawnTimerHandle = TimerManager::Get().SetTimer(GetSelfWeakSRef(), &TwinBladeStage::SpawnTwinBlade, mSpawnInterval, true);
    }

    void TwinBladeStage::SpawnTwinBlade()
    {
        const weak<TwinBlade> newTwinBlade = GetWorld()->SpawnActor<TwinBlade>(GetWorld(), Vector2Df{0.0f, 100.0f});
        newTwinBlade.lock()->SetActorLocation({mSpawnLocation.GetX(), mSpawnLocation.GetY()});
        newTwinBlade.lock()->SetTeamId(2);;
        if(mSpawnLocation == mLeftSpawnLocation)
        {
            mSpawnLocation = mRightSpawnLocation;
        }
        else
        {
            mSpawnLocation = mLeftSpawnLocation;
        }
        ++mCurrentSpawnCount;
        if(mCurrentSpawnCount == mSpawnAmount)
        {
            FinishStage();
        }
    }

    void TwinBladeStage::StageFinished()
    {
        GameStage::StageFinished();
        TimerManager::Get().ClearTimer(mSpawnTimerHandle);
    }
}



#include "VanguardStage.hpp"
#include "GameStage.hpp"
#include "Vanguard.hpp"
#include "World.hpp"

namespace ly
{
    VanguardStage::VanguardStage(World *world) :
        GameStage{"Vanguard Stage", world},
        mSpawnInterval{2.5f},
        mSwitchInterval{2.0f},
        mSpawnDistanceToEdge{100.0f},
        mLeftSpawnLocation{0.0f, 0.0f},
        mRightSpawnLocation{0.0f, 0.0f},
        mSpawnLocation{0.0f, 0.0f},
        mRowsToSpawn{2},
        mRowSpawnCount{0},
        mVanguardsPerRow{5},
        mCurrentRowVanguardCount{0}
    {
    }

    void VanguardStage::StartStage()
    {
        GameStage::StartStage();
        const auto windowSize = GetWorld()->GetWindowSize();
        mLeftSpawnLocation = {mSpawnDistanceToEdge, -100.0f};
        mRightSpawnLocation = {static_cast<float>(windowSize.GetX()) - mSpawnDistanceToEdge, -100.0f};

        SwitchRow();
    }

    void VanguardStage::StageFinished()
    {
        GameStage::StageFinished();
        TimerManager::Get().ClearTimer(mSpawnTimerHandle);
        TimerManager::Get().ClearTimer(mSwitchTimerHandle);
    }

    void VanguardStage::SpawnVanguard()
    {
        const weak<Vanguard> newVanguard = GetWorld()->SpawnActor<Vanguard>(GetWorld(), Vector2Df{0.0f, 100.0f});
        newVanguard.lock()->SetActorLocation({mSpawnLocation.GetX(), mSpawnLocation.GetY()});
        newVanguard.lock()->SetTeamId(2);
        ++mCurrentRowVanguardCount;
        if (mCurrentRowVanguardCount >= mVanguardsPerRow)
        {
            TimerManager::Get().ClearTimer(mSpawnTimerHandle);
            mSwitchTimerHandle = TimerManager::Get().SetTimer(GetSelfWeakSRef(), &VanguardStage::SwitchRow, mSwitchInterval, false);
            mCurrentRowVanguardCount = 0;
        }
    }

    void VanguardStage::SwitchRow()
    {
        if(mRowSpawnCount >= mRowsToSpawn)
        {
            FinishStage();
            return;
        }
        if(mSpawnLocation == mLeftSpawnLocation)
        {
            mSpawnLocation = mRightSpawnLocation;
        }
        else
        {
            mSpawnLocation = mLeftSpawnLocation;
        }

        mSpawnTimerHandle = TimerManager::Get().SetTimer(GetSelfWeakSRef(), &VanguardStage::SpawnVanguard, mSpawnInterval, true);
        mRowSpawnCount++;
    }
}

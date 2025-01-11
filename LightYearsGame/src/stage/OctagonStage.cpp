

#include "OctagonStage.hpp"

#include "Octagon.hpp"
#include "World.hpp"

namespace ly
{
    OctagonStage::OctagonStage(World *world):
    GameStage{"Octagon Stage", world},
    mSpawnInterval{5.0f},
    mSideSpawnOffset{80.0f},
    mSpawnGroupAmount{5},
    mSpawnCurrentCount{0},
    mMidSpawnLocation{static_cast<float>(world->GetWindowSize().GetX())/2.0f, -100.0f},
    mLeftSpawnLocation{static_cast<float>(world->GetWindowSize().GetX())/2.0f + mSideSpawnOffset, -100.0f - mSideSpawnOffset},
    mRightSpawnLocation{static_cast<float>(world->GetWindowSize().GetX())/2.0f - mSideSpawnOffset, -100.0f - mSideSpawnOffset}
    {
    }

    void OctagonStage::StartStage()
    {
        GameStage::StartStage();
        mSpawnTimer = TimerManager::Get().SetTimer(GetSelfWeakSRef(), &OctagonStage::SpawnOctagon, mSpawnInterval, true);
    }

    void OctagonStage::StageFinished()
    {
        GameStage::StageFinished();
        TimerManager::Get().ClearTimer(mSpawnTimer);
    }

    void OctagonStage::SpawnOctagon()
    {
        const weak<Octagon> newMidOctagon = GetWorld()->SpawnActor<Octagon>(GetWorld(), Vector2Df{0.0f, 100.0f});
        newMidOctagon.lock()->SetActorLocation({mMidSpawnLocation.GetX(), mMidSpawnLocation.GetY()});

        const weak<Octagon> newRightOctagon = GetWorld()->SpawnActor<Octagon>(GetWorld(), Vector2Df{0.0f, 100.0f});
        newRightOctagon.lock()->SetActorLocation({mRightSpawnLocation.GetX(), mRightSpawnLocation.GetY()});

        const weak<Octagon> newLeftOctagon = GetWorld()->SpawnActor<Octagon>(GetWorld(), Vector2Df{0.0f, 100.0f});
        newLeftOctagon.lock()->SetActorLocation({mLeftSpawnLocation.GetX(), mLeftSpawnLocation.GetY()});

        if(++mSpawnCurrentCount == mSpawnGroupAmount)
        {
            FinishStage();
        }
    }
}


#include "ChaosStage.hpp"

#include "MathUtility.hpp"
#include "Octagon.hpp"
#include "TwinBlade.hpp"
#include "UFO.hpp"
#include "Vanguard.hpp"

namespace ly
{
    ChaosStage::ChaosStage(World *world):
    GameStage{"ChaosStage ", world},
    mSpawnInterval{4.0f},
    mMinSpawnInterval{0.8f},
    mSpawnIntervalDecrement{0.5f},
    mSpawnIntervalDecrementInterval{5.0f},
    mStageDuration{60.0f}
    {
    }

    void ChaosStage::StartStage()
    {
        GameStage::StartStage();
        mSpawnTimer = TimerManager::Get().SetTimer(GetSelfWeakSRef(), &ChaosStage::SpawnVanguard, mSpawnInterval);
        mDifficultTimerHandle = TimerManager::Get().SetTimer(GetSelfWeakSRef(), &ChaosStage::IncreaseDifficulty, mSpawnIntervalDecrement, true);
        TimerManager::Get().SetTimer(GetSelfWeakSRef(), &ChaosStage::StageDurationReached, mStageDuration);
    }

    void ChaosStage::StageFinished()
    {
        GameStage::StageFinished();
        TimerManager::Get().ClearTimer(mDifficultTimerHandle);
        TimerManager::Get().ClearTimer(mSpawnTimer);
    }

    void ChaosStage::SpawnVanguard()
    {
        const weak<Vanguard> newVanguard{GetWorld()->SpawnActor<Vanguard>(GetWorld(), Vector2Df{0.0f, 100.0f})};
        newVanguard.lock()->SetActorLocation(GetRandomSpawnPositionTop());
        mSpawnTimer = TimerManager::Get().SetTimer(GetSelfWeakSRef(), &ChaosStage::SpawnTwinBlade, mSpawnInterval);
    }

    void ChaosStage::SpawnTwinBlade()
    {
        const weak<TwinBlade> newTwinBlade{GetWorld()->SpawnActor<TwinBlade>(GetWorld(), Vector2Df{0.0f, 100.0f})};
        newTwinBlade.lock()->SetActorLocation(GetRandomSpawnPositionTop());
        mSpawnTimer = TimerManager::Get().SetTimer(GetSelfWeakSRef(), &ChaosStage::SpawnOctoGun, mSpawnInterval);
    }

    void ChaosStage::SpawnOctoGun()
    {
        const weak<Octagon> newOctoGun{GetWorld()->SpawnActor<Octagon>(GetWorld(), Vector2Df{0.0f, 100.0f})};
        newOctoGun.lock()->SetActorLocation(GetRandomSpawnPositionTop());
        mSpawnTimer = TimerManager::Get().SetTimer(GetSelfWeakSRef(), &ChaosStage::SpawnUFO, mSpawnInterval);
    }

    void ChaosStage::SpawnUFO()
    {
        const Vector2Df spawnLoc{GetRandomSpawnPositionSide()};
        const auto windowSize = GetWorld()->GetWindowSize();
        const auto center = Vector2Df(static_cast<float>(windowSize.GetX()) / 2.0f, static_cast<float>(windowSize.GetY()) / 2.0f);
        Vector2Df directionToCenter = center - spawnLoc;

        MathUtility::Normalize(directionToCenter);

        const weak<UFO> newUFO{GetWorld()->SpawnActor<UFO>(GetWorld(), directionToCenter * 200.0f)};
        newUFO.lock()->SetActorLocation(spawnLoc);

        mSpawnTimer = TimerManager::Get().SetTimer(GetSelfWeakSRef(), &ChaosStage::SpawnVanguard, mSpawnInterval);
    }

    void ChaosStage::IncreaseDifficulty()
    {
        mSpawnInterval += mSpawnIntervalDecrement;
        if(mMinSpawnInterval < mSpawnInterval)
        {
            mSpawnInterval = mMinSpawnInterval;
        }
    }

    void ChaosStage::StageDurationReached()
    {
        FinishStage();
    }

    Vector2Df ChaosStage::GetRandomSpawnPositionTop() const
    {
        const auto windowSize = GetWorld()->GetWindowSize();
        float spawnX = MathUtility::RandomRange(100.0f, static_cast<float>(windowSize.GetX()) - 100.0f);
        float spawnY = 100.0f;

        return {spawnX, spawnY};
    }

    Vector2Df ChaosStage::GetRandomSpawnPositionSide() const
    {
        const auto windowSize{GetWorld()->GetWindowSize()};
        const float spawnLeft = MathUtility::RandomRange(-1, 1);
        float spawnLocX = 0;
        if(spawnLeft < 0)
        {
            spawnLocX = static_cast<float>(windowSize.GetX()) + 100.0f;
        }
        else
        {
            spawnLocX = -100.0f;
        }

        const float spawnLocY = MathUtility::RandomRange(0, static_cast<float>(windowSize.GetY()));
        return Vector2Df{spawnLocX, spawnLocY};
    }
}
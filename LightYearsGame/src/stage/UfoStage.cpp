

#include "UfoStage.hpp"

#include "MathUtility.hpp"
#include "UFO.hpp"
#include "World.hpp"

namespace ly {
    UfoStage::UfoStage(World *world, unsigned int spawnAmount):
        GameStage{"UFO Stage", world},
        mSpawnInterval{4.0f},
        mSpawnAmount{spawnAmount},
        mCurrentSpawnCount{0},
        mUfoSpeed{200.0f}
    {
    }

    void UfoStage::StartStage()
    {
        GameStage::StartStage();
        mSpawnTimer = TimerManager::Get().SetTimer(GetSelfWeakSRef(), &UfoStage::SpawnUFO, mSpawnInterval, true);
    }

    void UfoStage::StageFinished()
    {
        GameStage::StageFinished();
        TimerManager::Get().ClearTimer(mSpawnTimer);
    }

    Vector2Df UfoStage::GetRandomSpawnLocation()
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

    void UfoStage::SpawnUFO()
    {
        const Vector2Df spawnLocation = GetRandomSpawnLocation();
        const auto windowSize{GetWorld()->GetWindowSize()};
        const Vector2Df center{static_cast<float>(windowSize.GetX()) / 2.0f, static_cast<float>(windowSize.GetY()) / 2.0f};
        Vector2Df spawnLocCenter{center.GetX() - spawnLocation.GetX(), center.GetY() - spawnLocation.GetY()};
        MathUtility::Normalize(spawnLocCenter);

        const Vector2Df spawnVelocity{spawnLocCenter * mUfoSpeed};

        const weak<UFO> newUFO = GetWorld()->SpawnActor<UFO>(GetWorld(), spawnVelocity);
        newUFO.lock()->SetActorLocation(spawnLocation);
        newUFO.lock()->SetTeamId(2);

        if(++mCurrentSpawnCount == mSpawnAmount)
        {
            FinishStage();
        }
    }
}
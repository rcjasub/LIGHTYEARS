#pragma once

#include "GameStage.hpp"
#include "TimerManager.hpp"
#include "Vector2D.hpp"

namespace ly
{

class TwinBladeStage final : public GameStage
{
public:
    explicit TwinBladeStage(World* world);

    void StartStage() override;

private:
    void SpawnTwinBlade();
    void StageFinished() override;

    float mSpawnInterval;
    float mSpawnDistanceToCenter;

    Vector2Df mLeftSpawnLocation;
    Vector2Df mRightSpawnLocation;
    Vector2Df mSpawnLocation;

    int mSpawnAmount;
    int mCurrentSpawnCount;

    TimerHandle mSpawnTimerHandle;
};

}



#pragma once
#include "GameStage.hpp"
#include "TimerManager.hpp"
#include "Vector2D.hpp"

namespace ly
{

class VanguardStage final : public GameStage
{
public:
    explicit VanguardStage(World* world);
    void StartStage() override;

private:
    float mSpawnInterval;
    float mSwitchInterval;
    float mSpawnDistanceToEdge;

    Vector2Df mLeftSpawnLocation;
    Vector2Df mRightSpawnLocation;
    Vector2Df mSpawnLocation;

    TimerHandle mSpawnTimerHandle;
    TimerHandle mSwitchTimerHandle;

    int mRowsToSpawn;
    int mRowSpawnCount;

    int mVanguardsPerRow;
    int mCurrentRowVanguardCount;

    void StageFinished() override;
    void SpawnVanguard();
    void SwitchRow();
};

}

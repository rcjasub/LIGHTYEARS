
#pragma once
#include "GameStage.hpp"
#include "TimerManager.hpp"
#include "Vector2D.hpp"

namespace ly
{

class ChaosStage final : public GameStage
{
public:
    explicit ChaosStage(World* world);
    void StartStage() override;

protected:
    void StageFinished() override;

private:
    void SpawnVanguard();
    void SpawnTwinBlade();
    void SpawnOctoGun();
    void SpawnUFO();
    void IncreaseDifficulty();
    void StageDurationReached();

    Vector2Df GetRandomSpawnPositionTop() const;
    Vector2Df GetRandomSpawnPositionSide() const;

    float mSpawnInterval;
    float mMinSpawnInterval;

    float mSpawnIntervalDecrement;
    float mSpawnIntervalDecrementInterval;

    float mStageDuration;
    TimerHandle mDifficultTimerHandle;
    TimerHandle mSpawnTimer;
};

}

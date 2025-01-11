
#pragma once
#include "GameStage.hpp"
#include "TimerManager.hpp"
#include "Vector2D.hpp"

namespace ly
{

class UfoStage final : public GameStage
{
public:
    explicit UfoStage(World *world, unsigned int spawnAmount);
    ~UfoStage() override = default;
    void StartStage() override;

protected:
    void StageFinished() override;
    Vector2Df GetRandomSpawnLocation();
    void SpawnUFO();

    float mSpawnInterval;
    unsigned int mSpawnAmount;
    unsigned int mCurrentSpawnCount;
    float mUfoSpeed;

    TimerHandle mSpawnTimer;
};

}



#pragma once
#include "GameStage.hpp"
#include "TimerManager.hpp"
#include "Vector2D.hpp"

namespace ly
{

class OctagonStage final : public GameStage
{
public:
    explicit OctagonStage(World *world);

    void StartStage() override;

private:
    void StageFinished() override;
    void SpawnOctagon();

    float mSpawnInterval;
    float mSideSpawnOffset;
    unsigned int mSpawnGroupAmount;
    unsigned int mSpawnCurrentCount;

    Vector2Df mMidSpawnLocation;
    Vector2Df mLeftSpawnLocation;
    Vector2Df mRightSpawnLocation;

    TimerHandle mSpawnTimer;
};

}

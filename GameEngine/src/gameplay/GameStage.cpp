

#include "GameStage.hpp"

#include <utility>

namespace ly {
    GameStage::GameStage(std::string stageName, World *world) :
        Object{stageName},
        mWorld{world},
        mStageFinished{false},
        mStageName{std::move(stageName)}
    {
    }

    void GameStage::StartStage()
    {
        LOG("%s Stage Started", mStageName.c_str());
    }

    void GameStage::TickStage(float deltaTime)
    {
        // LOG("%s Stage Ticking", mStageName.c_str());
    }

    void GameStage::FinishStage()
    {
        mStageFinished = true;
        StageFinished();
        onStageFinished.Broadcast();
    }

    void GameStage::StageFinished()
    {
        LOG("%s Stage Finished", mStageName.c_str());
    }
}
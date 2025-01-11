

#pragma once

#include "Object.hpp"
#include <string>

namespace ly
{

class World;
class GameStage : public Object
{
public:
    explicit GameStage(std::string stageName, World* world);
    ~GameStage() override = default;
    const World* GetWorld() const { return mWorld; }
    World* GetWorld() { return mWorld; }

    Delegate<> onStageFinished;

    virtual void StartStage();
    virtual void TickStage(float deltaTime);
    virtual void FinishStage();
    bool IsStageFinished() const { return mStageFinished; };

protected:
    virtual void StageFinished();

private:
    World* mWorld;
    bool mStageFinished;
    std::string mStageName;
};

}


#pragma once
#include "GameStage.hpp"

namespace ly
{

class WaitStage final : public GameStage
{
public:
    explicit WaitStage(World *world, float waitDuration = 5.0f);

    void StartStage() override;

private:
    float mWaitDuration;
};

}

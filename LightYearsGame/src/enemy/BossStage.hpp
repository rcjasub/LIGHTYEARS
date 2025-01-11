
#pragma once
#include "GameStage.hpp"

namespace ly {
    class Actor;
}

namespace ly
{

class BossStage final : public GameStage
{
public:
    explicit BossStage(World* world);

    void StartStage() override;

    void BossDestroyed(Actor* bossActor);
};

}

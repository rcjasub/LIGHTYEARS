
#include "BossStage.hpp"
#include "Boss.hpp"

namespace ly
{
    BossStage::BossStage(World *world):
    GameStage{"Boss Stage", world}
    {
    }

    void BossStage::StartStage()
    {
        GameStage::StartStage();
        const weak<Boss> boss{GetWorld()->SpawnActor<Boss>(GetWorld())};
        const auto windowSize{GetWorld()->GetWindowSize()};
        boss.lock()->SetActorLocation({static_cast<float>(windowSize.GetX()) / 2.0f, 200.0f});
        boss.lock()->onActorDestroyed.BindAction(GetSelfWeakSRef(), &BossStage::BossDestroyed);
    }

    void BossStage::BossDestroyed(Actor* bossActor)
    {
        FinishStage();
    }
}
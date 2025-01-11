
#include "WaitStage.hpp"

#include "TimerManager.hpp"

namespace ly
{
    WaitStage::WaitStage(World *world, const float waitDuration):
        GameStage{"Wait Stage", world},
        mWaitDuration{waitDuration}
    {
    }

    void WaitStage::StartStage()
    {
        GameStage::StartStage();
        TimerManager::Get().SetTimer(GetSelfWeakSRef(), &WaitStage::FinishStage, mWaitDuration);
    }
}

#include "GamePlay/WaitStage.hpp"
#include "framework/TimerManager.hpp"

namespace ly
{
	WaitStage::WaitStage(World* world, float waitDuration)
		:GameStage{world},
		mWaitDuratioin{waitDuration}
	{
	}

	void WaitStage::StartStage()
	{
		TimerManager::Get().SetTimer(GetWeakRef(), &WaitStage::FinishStage, mWaitDuratioin);
	}
}
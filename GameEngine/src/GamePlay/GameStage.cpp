#include"GamePlay/GameStage.hpp"
#include"framework/core.hpp"

namespace ly
{
	GameStage::GameStage(World* world)
		:mWorld{world},
		mStageFinish{false}
	{
	}

	void GameStage::StartStage()
	{
		LOG("Stage Started");
	}

	void GameStage::TickStage(float deltaTime)
	{
		
	}
	void GameStage::FinishStage()
	{
		mStageFinish = true;
		StageFinished();
		onStageFinish.BroadCast();
	}

	void GameStage::StageFinished()
	{
		LOG("Stage Finish");
	}
}
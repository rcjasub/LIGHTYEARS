#pragma once

#include"GamePlay/GameStage.h"

namespace ly
{
	class WaitStage : public GameStage
	{
	public:
		WaitStage(World* world, float waitDuration = 5.f);
		
		virtual void StartStage() override;

	private:
		float mWaitDuratioin;

	};
	
}
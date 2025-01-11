#pragma once

#include"framework/Object.h"
#include"framework/Delegate.h"

namespace ly
{
	class World;
	class GameStage : public Object
	{
	public:
		GameStage(World* world);
		const World* GetWorld() const { return mWorld; }
		World* GetWorld() { return mWorld; }

		DeLegate<> onStageFinish;

		virtual void StartStage();
		virtual void TickStage(float deltaTime);
		void FinishStage();
		bool IsStageFinish() const { return mStageFinish; }

	private:
		World* mWorld;
		bool mStageFinish;
		virtual void StageFinished();
	};
}

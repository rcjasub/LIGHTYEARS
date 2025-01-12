#pragma once

#include"framework/world.hpp"
#include"framework/TimerManager.hpp"

namespace ly
{
	class PlayerSpaceShip;
	class GameLevelOne : public World
	{
	 public:
		 GameLevelOne(Application* owningApp);

	private:
		virtual void BeginPlay() override;
		weak<PlayerSpaceShip> testPlayerSpaceShip;

		TimerHandle timerHandle_Test;
		virtual void InitGameStages() override;
	};
}
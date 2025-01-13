#pragma once

#include"framework/world.hpp"
#include"framework/TimerManager.hpp"

namespace ly
{
	class PlayerSpaceShip;
	class GamePlayHUD;
	class GameLevelOne : public World
	{
	public:
		GameLevelOne(Application* owningApp);

	private:
		virtual void BeginPlay() override;
		weak<PlayerSpaceShip> mPlayerSpaceShip;
		weak<GamePlayHUD> mGameplayHUD;
		void PlayerSpaceShipDestroy(Actor* destroyPlayerSpaceShip);
		TimerHandle timerHandle_Test;
		virtual void InitGameStages() override;
		void GameOver();
	};
}
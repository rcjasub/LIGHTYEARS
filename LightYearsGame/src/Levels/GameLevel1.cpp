#include "GameLevel1.hpp"
#include "framework/world.hpp"
#include "framework/Actor.hpp"
#include "framework/AssetsManager.hpp"
#include "Player/PlayerSpaceShip.hpp"
#include "Enemy/Vanguard.hpp"
#include "framework/TimerManager.hpp"
#include "GamePlay/GameStage.hpp"
#include "GamePlay/WaitStage.hpp"
#include "Enemy/VanguardStage.hpp"
#include "Enemy/TwinBladeStage.hpp"
#include "Enemy/HexagonStage.hpp"
#include "Enemy/UFOStage.hpp"
#include "Player/PlayerManager.hpp"

namespace ly
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		:World{owningApp}
	{
	
	}

	void GameLevelOne::BeginPlay()
	{
		Player newPlayer = PlayerManager::Get().CreateNewPlayer();
		newPlayer.SpawnSpaceShip(this);
	}

	void GameLevelOne::InitGameStages()
	{
	/*	AddStage(shared<WaitStage>{new WaitStage{ this, 5.f }});*/
		AddStage(shared<UFOStage>{new UFOStage{ this }});
		
		AddStage(shared<WaitStage>{new WaitStage{ this, 5.f }});
		AddStage(shared<VanguardStage>{new VanguardStage{ this }});

		AddStage(shared<WaitStage>{new WaitStage{ this , 15.f }});
		AddStage(shared<TwinBladeStage>{new TwinBladeStage{ this }});

		AddStage(shared<WaitStage>{new WaitStage{ this , 15.f }});
		AddStage(shared<HexagonStage>{new HexagonStage{ this }});
	}
}
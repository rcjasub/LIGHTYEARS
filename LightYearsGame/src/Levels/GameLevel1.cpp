#include "GameLevel1.h"
#include "framework/world.h"
#include "framework/Actor.h"
#include "framework/AssetsManager.h"
#include "Player/PlayerSpaceShip.h"
#include "Enemy/Vanguard.h"
#include "framework/TimerManager.h"
#include "GamePlay/GameStage.h"
#include "GamePlay/WaitStage.h"
#include "Enemy/VanguardStage.h"
#include "Enemy/TwinBladeStage.h"
#include "Enemy/HexagonStage.h"
#include "Enemy/UFOStage.h"
#include "Player/PlayerManager.h"

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
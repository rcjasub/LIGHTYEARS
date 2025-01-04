#include "Levels/GameLevel1.h"
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

namespace ly
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		:World{owningApp}
	{
		testPlayerSpaceShip = SpamActor<PlayerSpaceShip>();
		testPlayerSpaceShip.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
		testPlayerSpaceShip.lock()->setActorRotation(0.f);

		
	}

	void GameLevelOne::BeginPlay()
	{
	
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
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
#include "Widgets/GamePlayHUD.hpp"

namespace ly
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		:World{owningApp}
	{

	}

	void GameLevelOne::BeginPlay()
	{
		Player newPlayer = PlayerManager::Get().CreateNewPlayer();
		mPlayerSpaceShip = newPlayer.SpawnSpaceShip(this);
		mPlayerSpaceShip.lock()->OnActorDestroy.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceShipDestroy);
		mGameplayHUD = SpawnHUD<GamePlayHUD>();
	}

	void GameLevelOne::PlayerSpaceShipDestroy(Actor* destroyPlayerSpaceShip)
	{
		mPlayerSpaceShip = PlayerManager::Get().GetPlayer(0)->SpawnSpaceShip(this);
		if (!mPlayerSpaceShip.expired())
		{
			mPlayerSpaceShip.lock()->OnActorDestroy.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceShipDestroy);
		}
		else
		{
			GameOver();
		}

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

	void GameLevelOne::GameOver()
	{
		LOG("Game Over =================================");
	}
}
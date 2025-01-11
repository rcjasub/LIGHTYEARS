

#include "GameLevelOne.hpp"
#include "BackDropActor.hpp"
#include "BackGroundLayer.hpp"
#include "BossStage.hpp"
#include "ChaosStage.hpp"
#include "VanguardStage.hpp"
#include "WaitStage.hpp"
#include "TwinBladeStage.hpp"
#include "Vanguard.hpp"
#include "OctagonStage.hpp"
#include "Player.hpp"
#include "PlayerManager.hpp"
#include "PlayerSpaceship.hpp"
#include "UfoStage.hpp"

namespace ly
{
    class PlayerSpaceship;

    GameLevelOne::GameLevelOne(Application *owningApp):
        World{owningApp}
    {
    }

    void GameLevelOne::AllGameStagesFinished()
    {
        mGameplayHUD.lock()->GameFinished(true);
    }

    void GameLevelOne::BeginPlay()
    {
        SpawnCosmetics();
        World::BeginPlay();
        Player* newPlayer = PlayerManager::GetInstance().CreateNewPlayer();
        mPlayerSpaceship = newPlayer->SpawnPlayerSpaceship(this);
        mPlayerSpaceship.lock()->onActorDestroyed.BindAction(GetSelfWeakSRef(), &GameLevelOne::PlayerSpaceshipDestroyed);
        mGameplayHUD = SpawnHUD<GameplayHUD>();
        mGameplayHUD.lock()->onQuitBtnClicked.BindAction(GetSelfWeakSRef(), &GameLevelOne::QuitGame);
        mGameplayHUD.lock()->onRestartBtnClicked.BindAction(GetSelfWeakSRef(), &GameLevelOne::Restart);
    }

    void GameLevelOne::QuitGame()
    {
        GetApp()->QuitApplication();
    }

    void GameLevelOne::Restart()
    {
        PlayerManager::GetInstance().Reset();
        GetApp()->LoadWorld<GameLevelOne>();
    }

    void GameLevelOne::GameOver()
    {
        LOG("GAME OVER!! =====================================================================");
        mGameplayHUD.lock()->GameFinished(false);
    }

    void GameLevelOne::PlayerSpaceshipDestroyed(Actor *destroyedPlayerSpaceship)
    {
        mPlayerSpaceship = PlayerManager::GetInstance().GetPlayer()->SpawnPlayerSpaceship(this);
        if(!mPlayerSpaceship.expired())
        {
            mPlayerSpaceship.lock()->onActorDestroyed.BindAction(GetSelfWeakSRef(), &GameLevelOne::PlayerSpaceshipDestroyed);
        }
        else
        {
            GameOver();
        }
    }

    void GameLevelOne::InitGameStages()
    {
        AddStage(std::make_shared<WaitStage>(WaitStage{this, 5.0f}));
        AddStage(std::make_shared<VanguardStage>(VanguardStage{this}));
        AddStage(std::make_shared<UfoStage>(UfoStage{this, 6}));

        AddStage(std::make_shared<WaitStage>(WaitStage{this, 5.0f}));
        AddStage(std::make_shared<TwinBladeStage>(TwinBladeStage{this}));
        AddStage(std::make_shared<UfoStage>(UfoStage{this, 2}));

        AddStage(std::make_shared<WaitStage>(WaitStage{this, 5.0f}));
        AddStage(std::make_shared<OctagonStage>(OctagonStage{this}));
        AddStage(std::make_shared<UfoStage>(UfoStage{this, 2}));

        AddStage(std::make_shared<WaitStage>(WaitStage{this, 5.0f}));
        AddStage(std::make_shared<ChaosStage>(ChaosStage{this}));

        AddStage(std::make_shared<WaitStage>(WaitStage{this, 5.0f}));
        AddStage(std::make_shared<BossStage>(BossStage{this}));
    }

    void GameLevelOne::SpawnCosmetics()
    {
        auto backDropActor{SpawnActor<BackDropActor>(this,"SpaceShooterRedux/Backgrounds/purple.png")};
        const weak<BackGroundLayer> planets{SpawnActor<BackGroundLayer>(this)};
        planets.lock()->SetAssets
        ({
            "SpaceShooterRedux/PNG/Planets/Planet1.png",
            "SpaceShooterRedux/PNG/Planets/Planet2.png",
            "SpaceShooterRedux/PNG/Planets/Planet3.png",
            "SpaceShooterRedux/PNG/Planets/Planet4.png",
            "SpaceShooterRedux/PNG/Planets/Planet5.png",
            "SpaceShooterRedux/PNG/Planets/Planet6.png",
            "SpaceShooterRedux/PNG/Planets/Planet7.png",
        });
        planets.lock()->SetSpriteCount(1);
        planets.lock()->SetSizes(1.0, 1.5);
        planets.lock()->SetVelocities({0.0f, 30.0f},{0.0f, 80.0f});

        const weak<BackGroundLayer> meteors{SpawnActor<BackGroundLayer>(this)};
        planets.lock()->SetAssets
        ({
            "SpaceShooterRedux/PNG/Meteors/meteorBrown_big1.png",
            "SpaceShooterRedux/PNG/Meteors/meteorBrown_big2.png",
            "SpaceShooterRedux/PNG/Meteors/meteorBrown_big3.png",
            "SpaceShooterRedux/PNG/Meteors/meteorBrown_big4.png",
            "SpaceShooterRedux/PNG/Meteors/meteorBrown_med1.png",
            "SpaceShooterRedux/PNG/Meteors/meteorBrown_med3.png",
            "SpaceShooterRedux/PNG/Meteors/meteorBrown_small1.png",
            "SpaceShooterRedux/PNG/Meteors/meteorBrown_small2.png",
            "SpaceShooterRedux/PNG/Meteors/meteorBrown_tiny1.png",
            "SpaceShooterRedux/PNG/Meteors/meteorBrown_tiny2.png",
            "SpaceShooterRedux/PNG/Meteors/meteorGrey_big1.png",
            "SpaceShooterRedux/PNG/Meteors/meteorGrey_big2.png",
            "SpaceShooterRedux/PNG/Meteors/meteorGrey_big3.png",
            "SpaceShooterRedux/PNG/Meteors/meteorGrey_big4.png",
            "SpaceShooterRedux/PNG/Meteors/meteorGrey_med1.png",
            "SpaceShooterRedux/PNG/Meteors/meteorGrey_med2.png",
            "SpaceShooterRedux/PNG/Meteors/meteorGrey_small1.png",
            "SpaceShooterRedux/PNG/Meteors/meteorGrey_small2.png",
            "SpaceShooterRedux/PNG/Meteors/meteorGrey_tiny1.png",
            "SpaceShooterRedux/PNG/Meteors/meteorGrey_tiny2.png",
        });
        meteors.lock()->SetSpriteCount(20);
        meteors.lock()->SetSizes(0.20, 0.5);
        // meteors.lock()->SetVelocities({0.0f, 30.0f},{0.0f, 80.0f});
    }
}

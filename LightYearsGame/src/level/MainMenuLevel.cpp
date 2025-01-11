
#include "MainMenuLevel.hpp"
#include "GameLevelOne.hpp"
#include "MainMenuHUD.hpp"

namespace ly {
    MainMenuLevel::MainMenuLevel(Application *owningApplication) :
        World{owningApplication}
    {
        mMainMenuHUD = SpawnHUD<MainMenuHUD>();
    }

    void MainMenuLevel::BeginPlay()
    {
        World::BeginPlay();
        mMainMenuHUD.lock()->onStartButtonClick.BindAction(GetSelfWeakSRef(), &MainMenuLevel::StartGame);
        mMainMenuHUD.lock()->onQuitButtonClick.BindAction(GetSelfWeakSRef(), &MainMenuLevel::EndGame);
    }

    void MainMenuLevel::StartGame()
    {
        GetApp()->LoadWorld<GameLevelOne>();
    }

    void MainMenuLevel::EndGame()
    {
        GetApp()->QuitApplication();
    }
}

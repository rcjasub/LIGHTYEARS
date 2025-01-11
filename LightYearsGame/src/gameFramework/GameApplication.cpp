#include "GameApplication.hpp"
#include "GameLevelOne.hpp"
#include "Actor.hpp"
#include "AssetManager.hpp"
#include "config.h"
#include "MainMenuLevel.hpp"

ly::Application* GetApplication()
{
	return new ly::GameApplication{};
}

namespace ly
{
	GameApplication::GameApplication():
		Application{600, 980, "Light Years", sf::Style::Titlebar | sf::Style::Close}
	{
		AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
		// const weak<GameLevelOne> newWorld = LoadWorld<GameLevelOne>();
		const weak<MainMenuLevel> newWorld = LoadWorld<MainMenuLevel>();
		// newWorld.lock()->SpawnActor<Actor>("Background", newWorld.lock().get(), "background.png");
	}
    void GameApplication::Tick(const float deltaTime)
    {
		Application::Tick(deltaTime);
    }
}
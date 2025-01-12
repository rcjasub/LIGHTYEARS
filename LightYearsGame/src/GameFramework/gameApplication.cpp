#include "GameFramework/gameApplication.hpp"
#include "Levels/GameLevel1.hpp"
#include "config.hpp"
#include "framework/AssetsManager.hpp"

ly::Application* GetApplication()
{
	return  new ly::GameApplication{};
}

namespace ly
{
	GameApplication::GameApplication()
		: Application{ 600, 980,"Light Years", sf::Style::Titlebar | sf::Style::Close }
	{
		AssetsManager::Get().setAssetsRootDirectory(GetResourceDir());

		weak<GameLevelOne> newWorld = LoadWorld<GameLevelOne>();

	}

}
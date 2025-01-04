#include "GameFramework/gameApplication.h"
#include "Levels/GameLevel1.h"
#include "config.h"
#include "framework/AssetsManager.h"

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
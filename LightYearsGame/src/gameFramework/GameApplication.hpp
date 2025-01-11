#pragma once
#include "Application.hpp"

namespace ly
{
	class PlayerSpaceship;
	class Actor;
	class GameApplication final : public Application
	{
	public:
		GameApplication();
		void Tick(float deltaTime) final;
	private:
		weak<PlayerSpaceship> testPlayerSpawnSpaceship;
	};
}
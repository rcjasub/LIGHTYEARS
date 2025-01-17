#pragma once
#include<SFML/Graphics.hpp>
#include "framework/core.h"


namespace ly
{
	class World;
	class Application 
	{
	public:
		Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style);
		void Run();

		template<typename WorldType>
		weak<WorldType> LoadWorld();

		sf::Vector2u GetWindowSize() const;

	private:
		void TickInternal(float deltaTime);
		void RenderInternal();


		virtual void Render();
		virtual void Tick(float deltaTime);

		sf::RenderWindow mWindow;

		float mTargetFrameRate;
		sf::Clock mTickClock;

		shared<World> currentWorld;
		sf::Clock mCleanCycleClock;
		float mCleanCycleInterval;

	};

	template<typename WorldType>
	weak<WorldType> Application::LoadWorld()
	{
		shared<WorldType> newWorld{ new WorldType{this} };
		currentWorld = newWorld;
		if (currentWorld)
		{
			currentWorld->BeginPlayInternal();
		}
		return newWorld;
	}
}


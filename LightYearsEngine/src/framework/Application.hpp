#pragma once

#include <SFML/Graphics.hpp>
#include "Core.hpp"
#include "Vector2D.hpp"
#include "World.hpp"

namespace ly
{
	class World;
	class Application
	{
	public:
		Application() = delete;
		Application(unsigned int mWindowWidth, unsigned int mWindowHeight, const std::string& title, sf::Uint32 style);
		virtual ~Application();

		void Run();

		sf::RenderWindow& GetWindow() {return mWindow;}
		const sf::RenderWindow& GetWindow() const {return mWindow;}
		Vector2Du GetWindowSize() const;

		template<typename WorldType>
		weak<WorldType> LoadWorld();

		void QuitApplication();
	protected:
		virtual void Tick(float deltaTime);
		virtual void Render();
	private:
		void TickInternal(float deltaTime);
		void RenderInternal();
		bool DispatchEvent(const sf::Event & event) const;
		
		sf::RenderWindow mWindow;
		float mTargetFrameRate;

		shared<World> mCurrentWorld;
		shared<World> mPendingWorld;
		sf::Clock mCleanCycleClock;
		float mCleanCycleInterval;
	};


    template <typename WorldType>
    inline weak<WorldType> Application::LoadWorld()
    {
		shared<WorldType> newWorld{std::make_shared<WorldType>(this)};
		mPendingWorld = newWorld;
        return newWorld;
    }
}
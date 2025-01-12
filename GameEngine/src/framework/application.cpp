#include "framework/application.hpp"
#include "framework/core.hpp"
#include "framework/world.hpp"
#include "framework/AssetsManager.hpp"
#include "framework/PhysicsSystem.hpp"
#include "framework/TimerManager.hpp"

#include <chrono>
#include <thread>


namespace ly
{
	Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style)
		: mWindow{ sf::VideoMode(windowWidth, windowHeight), title, style },
		mTargetFrameRate{ 120.f },
		mTickClock{},
		currentWorld{ nullptr },
	mCleanCycleClock{},
		mCleanCycleInterval(2.f)

	{
	}

	void Application::Run()
	{
		/*mTickClock.restart();
		float accumulatedTime = 0.f;
		float TargetDeltaTime = 1.f / mTargetFrameRate;*/

		const auto expected_ms_per_frame{ 1000.0f / mTargetFrameRate };
		const std::chrono::milliseconds expected_step_time_ms{ static_cast<uint32_t>(expected_ms_per_frame) };
		constexpr auto nanos_in_milli{ 1.0 * 1000000 };
		constexpr std::chrono::nanoseconds buffer{ static_cast<uint32_t>(nanos_in_milli / 2) };
		constexpr std::chrono::nanoseconds extraTime{ 0 };
		const float targetDeltaTime = 1.0f / mTargetFrameRate;
		sf::Event windowEvent{};

		//

		while (mWindow.isOpen())
		{
			const auto start{ std::chrono::steady_clock::now() };

			sf::Event windowEvent;
			while (mWindow.pollEvent(windowEvent))
			{
				if (windowEvent.type == sf::Event::EventType::Closed)
				{
					mWindow.close();
				}
			}

			TickInternal(targetDeltaTime);
			RenderInternal();

			const auto end = std::chrono::steady_clock::now();
			const std::chrono::duration<double> elapsed_seconds = end - start;
			const auto sleep_duration = expected_step_time_ms - std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_seconds) - buffer;

			if (sleep_duration > std::chrono::milliseconds(0))
			{
				std::this_thread::sleep_for(sleep_duration);
			}
		}

		LOG("App Stopped!!");
	}

	sf::Vector2u Application::GetWindowSize() const
	{
		return mWindow.getSize();
	}

	void Application::TickInternal(float deltaTime)
	{

		Tick(deltaTime);

		if (currentWorld)
		{
			currentWorld->TickInternal(deltaTime);
		}
		
		TimerManager::Get().UpdateTimer(deltaTime);

		PhysicsSystem::Get().Step(deltaTime);

		if (mCleanCycleClock.getElapsedTime().asSeconds() >= mCleanCycleInterval)
		{
			mCleanCycleClock.restart();
			AssetsManager::Get().CleanCycle();

			if (currentWorld)
			{
				currentWorld->CleanCycle();
			}
		}
	}
	
	void Application::RenderInternal()
	{
		mWindow.clear();

		Render();

		mWindow.display(); 
	}

	void Application::Render()
	{
		if (currentWorld)
		{
			currentWorld->Render(mWindow);
		}
	}

	void Application::Tick(float deltaTime)
	{
		
	}
}

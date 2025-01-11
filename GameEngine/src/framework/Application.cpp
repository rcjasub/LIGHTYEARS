#include "Core.hpp"
#include "Application.hpp"
#include "AssetManager.hpp"
#include "World.hpp"
#include "PhysicsSystem.hpp"
#include "TimerManager.hpp"
#include "Vector2D.hpp"
#include <thread>

namespace ly
{
	Application::~Application() = default;
	Application::Application(unsigned int mWindowWidth, unsigned int mWindowHeight, const std::string &title, sf::Uint32 style):
		mWindow{sf::VideoMode(mWindowWidth,mWindowHeight), title, style},
		mTargetFrameRate{60.0f},
		mCurrentWorld{nullptr},
		mCleanCycleClock{},
		mCleanCycleInterval{3}
	{

	}

	void Application::Run()
	{
		const auto expected_ms_per_frame{1000.0f / mTargetFrameRate};
		const std::chrono::milliseconds expected_step_time_ms{static_cast<uint32_t>(expected_ms_per_frame)};
		constexpr auto nanos_in_milli{1.0*1000000};
		constexpr std::chrono::nanoseconds buffer{static_cast<uint32_t>(nanos_in_milli/2)};
		constexpr std::chrono::nanoseconds extraTime{0};

		const float targetDeltaTime = 1.0f/mTargetFrameRate;
		sf::Event windowEvent{};
		while (mWindow.isOpen())
		{
			const auto start{std::chrono::steady_clock::now()};
			while (mWindow.pollEvent(windowEvent))
			{
				if(windowEvent.type == sf::Event::EventType::Closed)
				{
					QuitApplication();
				}
				else
				{
					DispatchEvent(windowEvent); //todo
				}
			}

			TickInternal(targetDeltaTime);
			RenderInternal();

			auto end = std::chrono::steady_clock::now();
			std::chrono::duration<double> elapsed_seconds = end-start;
			std::this_thread::sleep_until(start + ((expected_step_time_ms - elapsed_seconds) - buffer) + extraTime);
		}
		LOG("App Stopped!!");
	}

	Vector2Du Application::GetWindowSize() const
	{
		auto windowSize {mWindow.getSize()};
		return {windowSize.x,windowSize.y};
	};

	void Application::TickInternal(const float deltaTime)
	{
		Tick(deltaTime);
		if(mCurrentWorld)
		{
			mCurrentWorld->BeginPlayInternal();
			mCurrentWorld->TickInternal(deltaTime);
		}

		TimerManager::Get().UpdateTimer(deltaTime);
		PhysicsSystem::GetInstance().Step(deltaTime);

		if(mCleanCycleClock.getElapsedTime().asSeconds() >= mCleanCycleInterval)
		{
			mCleanCycleClock.restart();
			AssetManager::Get().CleanCycle();
			if(mCurrentWorld)
			{
				mCurrentWorld->CleanCycle();
			}
		}
		if(mPendingWorld != nullptr && mPendingWorld != mCurrentWorld)
		{
			mCurrentWorld = mPendingWorld;
			PhysicsSystem::Cleanup();
			mCurrentWorld->BeginPlayInternal();
		}
	}

	void Application::QuitApplication()
	{
		 mWindow.close();
	}

    void Application::Tick(const float deltaTime)
    {
		// uncomment to measure target vs. actual
		/*
		static auto last{std::chrono::steady_clock::now()};
		const auto current{std::chrono::steady_clock::now()};

		const std::chrono::duration<double> elapsed_duration = (current-last);
		const auto elapsed_sec = elapsed_duration.count();

		LOG("Target/Actual Framerate: %.2f/%.2f", 1.0f/deltaTime, 1000.0f/(elapsed_sec * 1000) );
		last = std::chrono::steady_clock::now();
		*/
    }
	
    void Application::RenderInternal()
    {
		mWindow.clear();
		Render();
		mWindow.display();
    }

    bool Application::DispatchEvent(const sf::Event &event) const
	{
		if(mCurrentWorld)
		{
			return mCurrentWorld->DispatchEvent(event);
		}
		return false;
    }

    void Application::Render()
	{
		if(mCurrentWorld)
		{
			mCurrentWorld->Render(mWindow);
		}
	}
}
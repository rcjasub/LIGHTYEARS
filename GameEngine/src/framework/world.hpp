#pragma once
#include"framework/core.hpp"
#include <SFML/Graphics.hpp>
#include"framework/Object.hpp"


namespace ly
{
	class HUD;
	class GameStage;
	class Actor;
	class Application;
	class World : public Object
	{
	public:
		World(Application* owningApp);

		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		void Render(sf::RenderWindow& window);

		virtual ~World();

		template<typename ActorType, typename... Args>
		weak<ActorType> SpamActor(Args... args);

		template<typename HUDType, typename... Args>
		weak<HUDType> SpawnHUD(Args... arg);

		sf::Vector2u GetWindowSize() const;
		void CleanCycle();

		void AddStage(const shared<GameStage>& newStage);
		void StartStages();

		bool DispathEvent(const sf::Event& event);

	private:

		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		void RenderHUD(sf::RenderWindow& window);
		Application* mOwningApp;
		bool mBeganPlay;

		list<shared<Actor>> mActors;

		list<shared<Actor>> mPendingActors;

		list<shared<GameStage>> mGameStage;

		list<shared<GameStage>>::iterator mCurrentStage;

		shared<HUD> mHUD;

		virtual void InitGameStages();
		virtual void AllGameStageFinish();
		void NextGameStage();

	};

	template<typename ActorType, typename... Args>
	weak<ActorType> World::SpamActor(Args... args)
	{
		shared<ActorType> newActor{ new ActorType( this, args...) };
		mPendingActors.push_back(newActor);
		return newActor;
	}

	template<typename HUDType, typename ...Args>
	inline weak<HUDType> World::SpawnHUD(Args ...arg)
	{
		shared<HUDType> newHUD{ new HUDType(arg...) };
		mHUD = newHUD;
		return newHUD;
	}
}

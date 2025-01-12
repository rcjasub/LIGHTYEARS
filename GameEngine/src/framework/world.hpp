#pragma once
#include"framework/core.hpp"
#include <SFML/Graphics.hpp>
#include"framework/Object.hpp"


namespace ly
{
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

		sf::Vector2u GetWindowSize() const;
		void CleanCycle();

		void AddStage(const shared<GameStage>& newStage);
		virtual void BeginPlay();
		void StartStages();

	private:

	/*	virtual void BeginPlay();*/
		virtual void Tick(float deltaTime);
		Application* mOwningApp;  
		bool mBeganPlay;

		list<shared<Actor>> mActors;

		list<shared<Actor>> mPendingActors;

		list<shared<GameStage>> mGameStage;
		
		list<shared<GameStage>>::iterator mCurrentStage;

		virtual void InitGameStages();
		virtual void AllGameStageFinish();
		void NextGameStage();

	/*	void StartStages();*/

	};

	template<typename ActorType, typename... Args>
	weak<ActorType> World::SpamActor(Args... args)
	{
		shared<ActorType> newActor{ new ActorType( this, args...) };
		mPendingActors.push_back(newActor);
		return newActor;
	}
}

#include "framework/world.hpp"
#include "framework/core.hpp"
#include "framework/Actor.hpp"
#include "framework/application.hpp"
#include "GamePlay/GameStage.hpp"

namespace ly
{
	// Constructor definition with proper initialization list
	World::World(Application* owningApp)
		: mOwningApp{ owningApp },
		mBeganPlay{ false },
		mActors{},
		mPendingActors{},
		mGameStage{},
		mCurrentStage{mGameStage.end()}
	{
		
	}

	void World::BeginPlayInternal()
	{
		if (!mBeganPlay)
		{
			mBeganPlay = true;
			
			BeginPlay();
			InitGameStages();
			StartStages();
			
		}
	}

	void World::TickInternal(float deltaTime)
	{

		for (shared<Actor> actor : mPendingActors)
		{
			if (actor)
			{
				mActors.push_back(actor);
				actor->BeginPlayInternal(); // Initialize the actor
			}
		}
		mPendingActors.clear();

		for (auto iter = mActors.begin(); iter != mActors.end();)
		{
			iter->get()->TickInternal(deltaTime);
			++iter;
		}
        
		if (mCurrentStage != mGameStage.end())
		{
			mCurrentStage->get()->TickStage(deltaTime);
		}

		Tick(deltaTime);
	}

	void World::Render(sf::RenderWindow& window)
	{
		for (const auto& actor : mActors)
		{
			actor->Render(window);
		}
	}

	World::~World()
	{
	}

	sf::Vector2u World::GetWindowSize() const
	{
		return mOwningApp->GetWindowSize();
	}

	void World::CleanCycle()
	{
		for (auto iter = mActors.begin(); iter != mActors.end();)
		{
			if (iter->get()->IsPendingDestroy())
			{
				iter = mActors.erase(iter);
			}

			else
			{
				++iter;
			}
		}

		
	}

	void World::AddStage(const shared<GameStage>& newStage)
	{
		mGameStage.push_back(newStage);
	}

	void World::BeginPlay()
	{
		
	}

	void World::Tick(float deltaTime)
	{
		
	}

	void World::InitGameStages()
	{
		
	}

	void World::AllGameStageFinish()
	{
		LOG("all stage Finish");
	}

	void World::NextGameStage()
	{
		++mCurrentStage;
		
		mCurrentStage = mGameStage.erase(mCurrentStage);

		if (mCurrentStage != mGameStage.end())
		{
			mCurrentStage->get()->StartStage();
			mCurrentStage->get()->onStageFinish.BindAction(GetWeakRef(), &World::NextGameStage);
		}

		else
		{
			AllGameStageFinish();
		}
	}

	void World::StartStages()
	{
		mCurrentStage = mGameStage.begin();
		if (mCurrentStage != mGameStage.end())
		{
			mCurrentStage->get()->StartStage();
			mCurrentStage->get()->onStageFinish.BindAction(GetWeakRef(), &World::NextGameStage);
		}
		
	}

}

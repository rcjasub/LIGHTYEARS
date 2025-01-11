#include "World.hpp"
#include "Core.hpp"
#include "Actor.hpp"
#include "GameStage.hpp"
#include "HUD.hpp"

namespace ly
{
    World::World(Application *owningApp):
        Object{"World"},
        mOwningApp{owningApp},
        mBeganPlay{false},
        mActors{},
        mPendingActors{},
        mGameStages{},
        mCurrentStage{mGameStages.end()}
    {
    }

    World::~World()= default;

    void World::BeginPlayInternal()
    {
        if(!mBeganPlay)
        {
            mBeganPlay = true;
            BeginPlay();
            InitGameStages();
            StartStages();
        }
    }

    void World::TickInternal(const float deltaTime)
    {
        for(const auto& actor: mPendingActors)
        {
            mActors.push_back(actor);
            actor->BeginPlayInternal();
        }

        mPendingActors.clear();

        for(auto iter = mActors.begin(); iter != mActors.end();)
        {
                iter->get()->Tick(deltaTime);
                iter = std::next(iter);
        }

        if(mCurrentStage != mGameStages.end())
        {
            mCurrentStage->get()->TickStage(deltaTime);
        }

        Tick(deltaTime);

        if(mHUD)
        {
            if(!mHUD->Initialized())
            {
                mHUD->NativeInit(mOwningApp->GetWindow());
            }
            mHUD->Tick(deltaTime);
        }
    }

    void World::RenderHud(sf::RenderWindow &window) const
    {
        if(mHUD)
        {
            mHUD->Draw(window );
        }
    }

    void World::Render(sf::RenderWindow &window) const
    {
        for(const auto& actor : mActors)
        {
            actor->Render(window);
        }
        RenderHud(window);
    }

    Vector2Du World::GetWindowSize() const
    {
        return mOwningApp->GetWindowSize();
    }

    void World::CleanCycle()
    {
        for(auto iter = mActors.begin(); iter != mActors.end();)
        {
            if(iter->get()->IsPendingDestroy())
            {
                iter = mActors.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }

    void World::AddStage(const shared<GameStage> &newStage)
    {
        mGameStages.push_back(newStage);
    }

    bool World::DispatchEvent(const sf::Event &event) const
    {
        if(mHUD)
        {
            mHUD->HandleEvent(event);
        }
        return false;
    }

    void World::BeginPlay()
    {
        LOG("Began Play");
    }
    void World::Tick(float deltaTime)
    {
        // LOG("ticking at framerate: %.3f", 1.0f/ deltaTime);
    }

    void World::InitGameStages()
    {

    }

    void World::AllGameStagesFinished()
    {
        LOG("All Game Stages Finished!!");
    }

    void World::NextGameStage()
    {
        mCurrentStage = mGameStages.erase(mCurrentStage);
        if(mCurrentStage != mGameStages.end())
        {
            mCurrentStage->get()->onStageFinished.BindAction<>(GetSelfWeakSRef(), &World::NextGameStage);
            mCurrentStage->get()->StartStage();
        }
        else
        {
            AllGameStagesFinished();
        }
    }

    void World::StartStages()
    {
        mCurrentStage = mGameStages.begin();
        if(mCurrentStage != mGameStages.end())
        {
            mCurrentStage->get()->StartStage();
            mCurrentStage->get()->onStageFinished.BindAction<>(GetSelfWeakSRef(), &World::NextGameStage);
        }
    }
}

#pragma once

#include "Application.hpp"
#include "Core.hpp"
#include "Object.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include "HUD.hpp"

namespace ly
{
    class HUD;
    class Actor;
    class Application;
    class GameStage;
    class World: public Object
    {
        public:
            explicit World(Application* owningApp);
            ~World() override;

            void BeginPlayInternal();
            void TickInternal(float deltaTime);

            template <typename ActorType, typename... Args>
            weak<ActorType> SpawnActor(Args... args);

            void RenderHud(sf::RenderWindow & window) const;
            void Render(sf::RenderWindow& window) const;

            Vector2Du GetWindowSize() const;
            void CleanCycle();
            void AddStage(const shared<GameStage>& newStage);
            bool DispatchEvent(const sf::Event & event) const;
            Application* GetApp() {return mOwningApp;}
            const Application* GetApp() const {return mOwningApp;}
        protected:
            virtual void BeginPlay();
            virtual void Tick(float deltaTime);
        template <typename HUDType, typename... Args>
        weak<HUDType> SpawnHUD(Args... args);
        private:
            Application* mOwningApp;
            bool mBeganPlay;

            List<shared<Actor>> mActors;
            List<shared<Actor>> mPendingActors;
            List<shared<GameStage>> mGameStages;
            List<shared<GameStage>>::iterator mCurrentStage;
            virtual void InitGameStages();
            virtual void AllGameStagesFinished();
            void NextGameStage();
            void StartStages();

            shared<HUD> mHUD;
    };

    template <typename ActorType, typename... Args>
    inline weak<ActorType> World::SpawnActor(Args... args)
    {
        shared<ActorType> newActor{std::make_shared<ActorType>(args...)};
        mPendingActors.push_back(newActor);
        return newActor;
    }

    template<typename HUDType, typename ... Args>
    weak<HUDType> World::SpawnHUD(Args... args)
    {
        shared<HUDType> newHUD{std::make_shared<HUDType>(args...)};
        mHUD = newHUD;
        return newHUD;
    }
}

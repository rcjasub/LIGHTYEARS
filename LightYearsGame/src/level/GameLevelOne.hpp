

#pragma once

#include "GameplayHUD.hpp"
#include "World.hpp"
#include "TimerManager.hpp"

namespace ly
{

class PlayerSpaceship;
class GameLevelOne final : public World
{
public:
    explicit GameLevelOne(Application* owningApp);
private:
    void AllGameStagesFinished() override;
    void BeginPlay() override;
    weak<PlayerSpaceship> mPlayerSpaceship;
    weak<GameplayHUD> mGameplayHUD;
    TimerHandle mTimerHandleTest;
    void QuitGame();
    void Restart();
    void GameOver();
    void PlayerSpaceshipDestroyed(Actor* destroyedPlayerSpaceship);
    void InitGameStages() override;
    void SpawnCosmetics();
};

}

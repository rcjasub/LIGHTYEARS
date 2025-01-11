

#pragma once
#include "World.hpp"

namespace ly
{
class MainMenuHUD;
class MainMenuLevel final : public World
{
public:
    MainMenuLevel() = delete;
    explicit MainMenuLevel(Application* owningApplication);

protected:
    void BeginPlay() override;

private:
    weak<MainMenuHUD> mMainMenuHUD;
    void StartGame();
    void EndGame();
};

}

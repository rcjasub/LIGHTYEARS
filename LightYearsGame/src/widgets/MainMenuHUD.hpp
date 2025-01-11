
#pragma once
#include "Button.hpp"
#include "HUD.hpp"
#include "TextWidget.hpp"

namespace ly
{

class MainMenuHUD : public HUD
{
public:
    MainMenuHUD();
    void Draw(sf::RenderWindow &windowRef) override;
    bool HandleEvent(const sf::Event &event) override;
    Delegate<> onStartButtonClick;
    Delegate<> onQuitButtonClick;
private:
    TextWidget mTitleText;
    Button mStartButton;
    Button mQuitButton;

    void Init(sf::RenderWindow &windowRef) override;
    void StartButtonClicked();
    void QuitButtonClicked();
};

}

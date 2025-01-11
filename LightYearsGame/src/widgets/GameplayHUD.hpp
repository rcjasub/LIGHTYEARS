#pragma once
#include "Button.hpp"
#include "HUD.hpp"
#include "ImageWidget.hpp"
#include "TextWidget.hpp"
#include "ValueGauge.hpp"

namespace ly
{
    class Actor;
class GameplayHUD : public HUD
{
public:
    GameplayHUD();
    ~GameplayHUD() override = default;

    void Tick(float deltaTime) override;
    void GameFinished(bool playerWon);
    Delegate<> onRestartBtnClicked;
    Delegate<> onQuitBtnClicked;

    bool HandleEvent(const sf::Event &event) override;
private:
    void Draw(sf::RenderWindow &windowRef) override;
    void ConnectPlayerStatus();
    void Init(sf::RenderWindow &windowRef) override;
    void RefreshHealthBar();
    void PlayerSpaceshipDestroyed(Actor* actor);
    void PlayerHealthUpdated(float amt, float currentHealth, float maxHealth);
    void PlayerLifeCountUpdated(int amount);
    void PlayerScoreUpdated(int newScore);

    TextWidget mFrameText;
    ImageWidget mPlayerLifeIcon;
    TextWidget mPlayerLifeText;
    ImageWidget mPlayerScoreIcon;
    TextWidget mPlayerScoreText;
    ValueGauge mPLayerHealthBar;
    sf::Color mHealthyBarColor;
    sf::Color mCriticalBarColor;
    float mCriticalThreshold;
    float mWidgetSpacing;

    TextWidget mWindLoseText;
    TextWidget mFinalScoreText;

    Button mRestart;
    Button mExit;

    void RestartButtonClicked();
    void QuitButtonClicked();

    Vector2Du mWindowSize;
};

}

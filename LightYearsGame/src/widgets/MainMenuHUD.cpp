
#include "MainMenuHUD.hpp"

namespace ly {
    MainMenuHUD::MainMenuHUD() :
    HUD{"MainMenuHUD"},
    mTitleText{"Light Years"},
    mStartButton{"Start"},
    mQuitButton{"Quit"}
    {
        mTitleText.SetTextSize(40);
        mStartButton.SetTextSize(40);
        mQuitButton.SetTextSize(40);
    }

    void MainMenuHUD::Draw(sf::RenderWindow &windowRef)
    {
        mTitleText.NativeDraw(windowRef);
        mStartButton.NativeDraw(windowRef);
        mQuitButton.NativeDraw(windowRef);
    }

    bool MainMenuHUD::HandleEvent(const sf::Event &event)
    {
        return HUD::HandleEvent(event) || mStartButton.HandleEvent(event) || mQuitButton.HandleEvent(event);
    }

    void MainMenuHUD::Init(sf::RenderWindow &windowRef)
    {
        const auto size{windowRef.getSize()};
        const Vector2Du windowSize{size.x, size.y};
        mTitleText.SetWidgetLocation({static_cast<float>(windowSize.GetX()) / 2.0f - mTitleText.GetBound().width/2.0f, 100});
        mStartButton.SetWidgetLocation({static_cast<float>(windowSize.GetX()) / 2.0f - mStartButton.GetBound().width/2.0f, static_cast<float>(windowSize.GetY()) /2.0f});
        mQuitButton.SetWidgetLocation(mStartButton.GetWidgetLocation() + Vector2Df{0.0f, 50.0f});
        mStartButton.onClick.BindAction(GetSelfWeakSRef(), &MainMenuHUD::StartButtonClicked);
        mQuitButton.onClick.BindAction(GetSelfWeakSRef(), &MainMenuHUD::QuitButtonClicked);
    }

    void MainMenuHUD::StartButtonClicked()
    {
        onStartButtonClick.Broadcast();
    }

    void MainMenuHUD::QuitButtonClicked()
    {
        onQuitButtonClick.Broadcast();
    }
}



#include "GameplayHUD.hpp"
#include "HealthComponent.hpp"
#include "PlayerManager.hpp"
#include "PlayerSpaceship.hpp"
#include "Actor.hpp"

namespace ly {
    GameplayHUD::GameplayHUD():
    HUD{"GamePlayHud"},
    mFrameText{"Frame Rate: "},
    mPlayerLifeIcon{"SpaceShooterRedux/PNG/pickups/playerLife1_blue.png"},
    mPlayerLifeText{""},
    mPlayerScoreIcon{"SpaceShooterRedux/PNG/Power-ups/star_gold.png"},
    mPlayerScoreText{"Score"},
    mPLayerHealthBar{},
    mHealthyBarColor{128, 255, 128, 255},
    mCriticalBarColor{255, 0, 0, 255},
    mCriticalThreshold{0.3f},
    mWidgetSpacing{10},
    mWindLoseText{""},
    mFinalScoreText{""},
    mRestart{"Restart"},
    mExit{"Quit"},
    mWindowSize{}
    {
        mWindLoseText.SetVisibility(false);
        mFinalScoreText.SetVisibility(false);
        mRestart.SetVisibility(false);
        mExit.SetVisibility(false);
    }

    bool GameplayHUD::HandleEvent(const sf::Event &event)
    {
        if(mRestart.HandleEvent(event)) return true;
        if(mExit.HandleEvent(event)) return true;
        return HUD::HandleEvent(event);
    }

    void GameplayHUD::Draw(sf::RenderWindow &windowRef)
    {
        mFrameText.NativeDraw(windowRef);
        mPLayerHealthBar.NativeDraw(windowRef);
        mPlayerLifeIcon.NativeDraw(windowRef);
        mPlayerLifeText.NativeDraw(windowRef);
        mPlayerScoreIcon.NativeDraw(windowRef);
        mPlayerScoreText.NativeDraw(windowRef);

        mWindLoseText.NativeDraw(windowRef);
        mFinalScoreText.NativeDraw(windowRef);
        mRestart.NativeDraw(windowRef);
        mExit.NativeDraw(windowRef);
    }

    void GameplayHUD::ConnectPlayerStatus()
    {
        if(const auto player {PlayerManager::GetInstance().GetPlayer()})
        {
            const auto lifeCount{player->GetLifeCount()};
            mPlayerLifeText.SetString(std::to_string(lifeCount));
            player->onLifeChanged.BindAction(GetSelfWeakSRef(), &GameplayHUD::PlayerLifeCountUpdated);

            auto playerScore{player->GetScore()};
            mPlayerScoreText.SetString(std::to_string(playerScore));
            player->onScoreChanged.BindAction(GetSelfWeakSRef(), &GameplayHUD::PlayerScoreUpdated);
        }
    }

    void GameplayHUD::Init(sf::RenderWindow &windowRef)
    {
        LOG("Initializing HUD ");
        auto const size{windowRef.getSize()};
        mWindowSize = {size.x, size.y};
        mFrameText.SetTextSize(30);
        mPlayerLifeText.SetTextSize(20);
        mPlayerScoreText.SetTextSize(20);
        const auto windowSize = windowRef.getSize();
        mPLayerHealthBar.SetWidgetLocation({10, static_cast<float>(windowSize.y) - 50.0f});

        Vector2Df nextWidgetPosition = mPLayerHealthBar.GetWidgetLocation();

        nextWidgetPosition += Vector2Df{mPLayerHealthBar.GetBound().width + mWidgetSpacing, 0.0f};
        mPlayerLifeIcon.SetWidgetLocation(nextWidgetPosition);

        nextWidgetPosition += Vector2Df{mPlayerLifeIcon.GetBound().width + mWidgetSpacing, 0.0f};
        mPlayerLifeText.SetWidgetLocation(nextWidgetPosition);

        nextWidgetPosition += Vector2Df{mPlayerLifeText.GetBound().width + mWidgetSpacing * 4, -2.0f};
        mPlayerScoreIcon.SetWidgetLocation(nextWidgetPosition);

        nextWidgetPosition += Vector2Df{mPlayerScoreIcon.GetBound().width + mWidgetSpacing, 0.0f};
        mPlayerScoreText.SetWidgetLocation(nextWidgetPosition);

        RefreshHealthBar();
        ConnectPlayerStatus();
        mWindLoseText.SetTextSize(40);
        // mWindLoseText.SetString("You Win");
        mWindLoseText.SetWidgetLocation({windowSize.x / 2.0f - mWindLoseText.GetBound().width/2.0f, 100.0f});
        mFinalScoreText.SetTextSize(40);
        mFinalScoreText.SetWidgetLocation({windowSize.x / 2.0f - mWindLoseText.GetBound().width/2.0f, 200.0f});

        mRestart.SetWidgetLocation({static_cast<float>(windowSize.x) / 2.0f - mRestart.GetBound().width/2.0f, static_cast<float>(windowSize.y) /2.0f});
        mExit.SetWidgetLocation(mRestart.GetWidgetLocation() + Vector2Df{0.0f, 50.0f});

        mRestart.onClick.BindAction(GetSelfWeakSRef(), &GameplayHUD::RestartButtonClicked);
        mExit.onClick.BindAction(GetSelfWeakSRef(), &GameplayHUD::QuitButtonClicked);
    }

    void GameplayHUD::RefreshHealthBar()
    {
        mPLayerHealthBar.SetForeGroundColor(mHealthyBarColor);
        const auto player {PlayerManager::GetInstance().GetPlayer()};
        if(player != nullptr && !player->GetCurrentPlayerSpaceship().expired())
        {
            const weak<PlayerSpaceship> playerSpaceship {player->GetCurrentPlayerSpaceship()};
            playerSpaceship.lock()->onActorDestroyed.BindAction(GetSelfWeakSRef(), &GameplayHUD::PlayerSpaceshipDestroyed);
            HealthComponent& healthComp = player->GetCurrentPlayerSpaceship().lock()->GetHealthComponent();
            healthComp.OnHealthChanged.BindAction(GetSelfWeakSRef(), &GameplayHUD::PlayerHealthUpdated);
            mPLayerHealthBar.UpdateValue(healthComp.GetHealth(), healthComp.GetMaxHealth());
        }
    }

    void GameplayHUD::PlayerSpaceshipDestroyed(Actor *actor)
    {
        RefreshHealthBar();
    }

    void GameplayHUD::PlayerHealthUpdated(const float amt, const float currentHealth, const float maxHealth)
    {
        std::ignore = amt;
        mPLayerHealthBar.UpdateValue(currentHealth, maxHealth);
        LOG("Threshold: %.2f/Critical Threshold: %2f", currentHealth / maxHealth, mCriticalThreshold);
        if(currentHealth / maxHealth <= mCriticalThreshold)
        {
            mPLayerHealthBar.SetForeGroundColor(mCriticalBarColor);
        }
        else {
            mPLayerHealthBar.SetForeGroundColor(mHealthyBarColor);
        }
    }

    void GameplayHUD::PlayerLifeCountUpdated(const int amount)
    {
        mPlayerLifeText.SetString(std::to_string(amount));
    }

    void GameplayHUD::PlayerScoreUpdated(int newScore)
    {
        mPlayerScoreText.SetString(std::to_string(newScore));
    }

    void GameplayHUD::RestartButtonClicked()
    {
        onRestartBtnClicked.Broadcast();
    }

    void GameplayHUD::QuitButtonClicked()
    {
        onQuitBtnClicked.Broadcast();
    }

    void GameplayHUD::GameFinished(bool playerWon)
    {
        mWindLoseText.SetVisibility(true);
        mFinalScoreText.SetVisibility(true);
        mRestart.SetVisibility(true);
        mExit.SetVisibility(true);

        auto score{PlayerManager::GetInstance().GetPlayer()->GetScore()};
        mFinalScoreText.SetString("Score: " + std::to_string(score));
        mFinalScoreText.SetTextSize(30);
        if(playerWon)
        {
            mWindLoseText.SetString("You Win!");
        }
        else
        {
            mWindLoseText.SetString("You Lose!");
        }
        // mWindLoseText.SetWidgetLocation({mWindowSize.x / 2.0f, mWindowSize.y / 2.0f});
        mWindLoseText.SetWidgetLocation({static_cast<float>(mWindowSize.GetX()) / 2.0f - mWindLoseText.GetBound().width/2.0f, 100});
        mFinalScoreText.SetWidgetLocation({static_cast<float>(mWindowSize.GetX()) / 2.0f - mWindLoseText.GetBound().width/2.0f, 200});
    }

    void GameplayHUD::Tick(const float deltaTime)
    {
        HUD::Tick(deltaTime);
        const auto frameRate = static_cast<unsigned int>(1.0f/deltaTime);
        const std::string frameRateString = "Frame Rate: " + std::to_string(frameRate);
        mFrameText.SetString(frameRateString);
    }
}

//
// Created by wbowen on 11/16/24.
//

#include "ValueGauge.hpp"

#include "AssetManager.hpp"

namespace ly {
    ValueGauge::ValueGauge(const Vector2Df &size, float initialValue, float min, float max, sf::Color foregroundColor, sf::Color backgroundColor) :
        Widget{"ValueGuage"},
        mTextFont{AssetManager::Get().LoadFont("SpaceShooterRedux/Bonus/kenvector_future.ttf")},
        mText{"",*mTextFont.get()},
        mBarFront{{size.GetX(), size.GetY()}},
        mBarBack{{size.GetX(), size.GetY()}},
        mForegroundColor{foregroundColor},
        mBackgroundColor{backgroundColor},
        mValue{initialValue},
        mValueMin{min},
        mValueMax{max}
    {
        mBarBack.setFillColor(backgroundColor);
        mBarFront.setFillColor(foregroundColor);
        SetTextSize(20);
    }

    void ValueGauge::UpdateValue(const float value)
    {
        mValue = std::clamp(value, mValueMin, mValueMax);
        const std::string displayStr = std::to_string(static_cast<int>(mValue)) + "/" + std::to_string(static_cast<int>(mValueMax));
        mText.setString(displayStr);

        const auto size = mBarBack.getSize();
        const Vector2Df barSize = {size.x, size.y};
        mBarFront.setSize({barSize.GetX() * (mValue / mValueMax), barSize.GetY()});
        CenterText();
    }

    void ValueGauge::UpdateValue(float value, const float maxHealth)
    {
        mValueMax = maxHealth;
        UpdateValue(value);
    }

    sf::FloatRect ValueGauge::GetBound() const
    {
        return mBarBack.getGlobalBounds();
    }

    void ValueGauge::SetTextSize(unsigned int newSize)
    {
        mText.setCharacterSize(newSize);
    }

    void ValueGauge::SetForeGroundColor(const sf::Color newColor)
    {
        mForegroundColor = newColor;
        mBarFront.setFillColor(newColor);
    }

    void ValueGauge::SetBackGroundColor(const sf::Color newColor)
    {
        mBackgroundColor = newColor;
        mBarBack.setFillColor(newColor);
    }

    void ValueGauge::CenterText()
    {
        const auto widgetCenter = GetCenterPosition();
        const sf::FloatRect textRect = mText.getGlobalBounds();
        mText.setPosition(widgetCenter.GetX() - textRect.width / 2, widgetCenter.GetY() - textRect.height);
    }

    void ValueGauge::LocationUpdated(const Vector2Df &newLocation)
    {
        mBarBack.setPosition({newLocation.GetX(), newLocation.GetY()});
        mBarFront.setPosition({newLocation.GetX(), newLocation.GetY()});
        CenterText();
    }

    void ValueGauge::RotationUpdated(const float newRotation)
    {
        mBarBack.setRotation(newRotation);
        mBarFront.setRotation(newRotation);
        mText.setRotation(newRotation);
    }

    void ValueGauge::Draw(sf::RenderWindow &window) const
    {
        window.draw(mBarBack);
        window.draw(mBarFront);
        window.draw(mText);
    }
}


#include "Button.hpp"

#include "AssetManager.hpp"

namespace ly
{
    Button::Button(const std::string &textString, const std::string &buttonTexturePath) :
    Widget{"Button"},
    mTexture{AssetManager::Get().LoadTexture(buttonTexturePath)},
    mSprite{*mTexture.get()},
    mFont{AssetManager::Get().LoadFont("SpaceShooterRedux/Bonus/kenvector_future.ttf")},
    mText{textString, *mFont.get()},
    mColor{128, 128, 128, 255},
    mPressDownColor{64, 64, 64, 255},
    mHoverColor{190, 190, 190, 255},
    mIsPressedDown{false}
    {
        mSprite.setColor(mColor);
        CenterText();
    }

    void Button::SetText(const std::string &textString)
    {
        mText.setString(textString);
        CenterText();
    }

    void Button::SetTextSize(const uint8 textSize)
    {
        mText.setCharacterSize(textSize);
        CenterText();
    }

    bool Button::HandleEvent(const sf::Event &event)
    {
        if(!GetVisibility())
        {
            return false;
        }
        bool handled = false;
        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if(mSprite.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)) && mIsPressedDown)
                {
                    onClick.Broadcast();
                    handled = true;
                }
            }
            PressedUp();
        }
        else if(event.type == sf::Event::MouseButtonPressed)
        {
            if (mSprite.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
            {
                PressedDown();
                handled = true;
            }
        }
        else if(event.type == sf::Event::MouseMoved)
        {
            if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(mSprite.getGlobalBounds().contains(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))
                {
                    MouseHovered();
                }
                else
                {
                    PressedUp();
                }
            }
        }
        return handled || Widget::HandleEvent(event);
    }

    void Button::Draw(sf::RenderWindow &window) const
    {
        window.draw(mSprite);
        window.draw(mText);
    }

    void Button::LocationUpdated(const Vector2Df &newLocation)
    {
        mSprite.setPosition({newLocation.GetX(), newLocation.GetY()});
        // mText.setPosition(newLocation);
        CenterText();
    }

    void Button::RotationUpdated(const float newRotation)
    {
        mSprite.setRotation(newRotation);
        mText.setRotation(newRotation);
    }

    sf::FloatRect Button::GetBound() const
    {
        return mSprite.getGlobalBounds();
    }

    void Button::PressedUp()
    {
        mIsPressedDown = false;
        mSprite.setColor(mColor);
    }

    void Button::PressedDown()
    {
        mIsPressedDown = true;
        mSprite.setColor(mPressDownColor);
    }

    void Button::MouseHovered()
    {
        mSprite.setColor(mHoverColor);
    }

    void Button::CenterText()
    {
        const auto widgetCenter = GetCenterPosition();
        const sf::FloatRect textRect = mText.getGlobalBounds();
        mText.setPosition(widgetCenter.GetX() - textRect.width / 2, widgetCenter.GetY() - textRect.height);
    }
}

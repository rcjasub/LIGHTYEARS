#pragma once
#include "Widget.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"

namespace ly {

class Button: public Widget
{
public:
    Button() = delete;
    explicit Button(const std::string& textString = "Button", const std::string& buttonTexturePath = "SpaceShooterRedux/PNG/UI/buttonBlue.png");
    void SetText(const std::string& textString);
    void SetTextSize(uint8 textSize);
    sf::FloatRect GetBound() const override;

    bool HandleEvent(const sf::Event &event) override;
    Delegate<> onClick;
private:
    void Draw(sf::RenderWindow &window) const override;
    void LocationUpdated(const Vector2Df &newLocation) override;
    void RotationUpdated(const float newRotation) override;

    void PressedUp();
    void PressedDown();
    void MouseHovered();
    void CenterText();

    shared<sf::Texture> mTexture;
    sf::Sprite mSprite;

    shared<sf::Font> mFont;
    sf::Text mText;

    sf::Color mColor;
    sf::Color mPressDownColor;
    sf::Color mHoverColor;

    bool mIsPressedDown;
};

}

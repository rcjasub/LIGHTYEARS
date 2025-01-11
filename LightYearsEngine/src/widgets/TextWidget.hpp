

#pragma once
#include "Widget.hpp"
#include "SFML/Graphics/Text.hpp"

namespace ly {

class TextWidget final : public Widget
{
public:
    TextWidget() = delete;
    explicit TextWidget(const std::string& textStr, const std::string& fontPath = "SpaceShooterRedux/Bonus/kenvector_future.ttf", unsigned int fontSize = 10);
    ~TextWidget() override = default;

    void SetString(const std::string& newString );
    void SetTextSize(const unsigned int newSize );

    sf::FloatRect GetBound() const override;
private:
    void LocationUpdated(const Vector2Df &newLocation) override;
    void RotationUpdated(const float newLocation) override;
    void Draw(sf::RenderWindow &window) const override;

    shared<sf::Font> mFont;
    sf::Text mText;
};

}



#pragma once
#include "Widget.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"

namespace ly
{

class ValueGauge: public Widget
{
public:
    explicit ValueGauge(const Vector2Df& size = Vector2Df{200.0f, 40.0f},
                        float initialValue = 0, float min = 0.0f, float max = 100.0f,
                        sf::Color backgroundColor = sf::Color{128, 255, 128, 255},
                        sf::Color foregroundColor = sf::Color{128, 128, 128, 255});

    void UpdateValue(float value);
    void UpdateValue(float value, float maxHealth);

    sf::FloatRect GetBound() const override;
    void SetTextSize(unsigned int newSize);
    void SetForeGroundColor(const sf::Color newColor);
    void SetBackGroundColor(const sf::Color newColor);
private:
    void CenterText();
    void LocationUpdated(const Vector2Df &newLocation) override;
    void RotationUpdated(const float newRotation) override;
    void Draw(sf::RenderWindow &window) const override;

    shared<sf::Font> mTextFont;
    sf::Text mText;

    sf::RectangleShape mBarFront;
    sf::RectangleShape mBarBack;

    sf::Color mForegroundColor;
    sf::Color mBackgroundColor;

    float mValue;
    float mValueMax;
    float mValueMin;
};

}

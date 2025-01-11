

#pragma once
#include "Widget.hpp"
#include "SFML/Graphics/Sprite.hpp"

namespace ly
{

class ImageWidget: public Widget
{
public:
    ImageWidget() = delete;
    explicit ImageWidget(const std::string& imagePath);
    void SetImage(const shared<sf::Texture>& newTexture);
    sf::FloatRect GetBound() const override;

protected:
private:
    shared<sf::Texture> mTexture;
    sf::Sprite mSprite;

    void LocationUpdated(const Vector2Df &newLocation) override;
    void RotationUpdated(const float newRotation) override;
    void Draw(sf::RenderWindow &window) const override;
};

}


#include "ImageWidget.hpp"

#include "AssetManager.hpp"

namespace ly {
    ImageWidget::ImageWidget(const std::string& imagePath):
    Widget{"ImageWidget"},
    mTexture{AssetManager::Get().LoadTexture(imagePath)},
    mSprite{*mTexture.get()}
    {

    }

    void ImageWidget::SetImage(const shared<sf::Texture> &newTexture)
    {
        if(newTexture != nullptr)
        {
            mTexture = newTexture;
            mSprite.setTexture(*newTexture.get());
        }
    }

    sf::FloatRect ImageWidget::GetBound() const
    {
        return mSprite.getGlobalBounds();
    }

    void ImageWidget::LocationUpdated(const Vector2Df &newLocation)
    {
        mSprite.setPosition({newLocation.GetX(), newLocation.GetY()});
    }

    void ImageWidget::RotationUpdated(const float newRotation)
    {
        mSprite.setRotation(newRotation);
    }

    void ImageWidget::Draw(sf::RenderWindow &window) const
    {
         window.draw(mSprite);
    }
}



#include "TextWidget.hpp"

#include "AssetManager.hpp"

namespace ly
{
    TextWidget::TextWidget(const std::string &textStr, const std::string &fontPath, unsigned int fontSize):
        Widget{"TextWidget"},
        mFont{AssetManager::Get().LoadFont(fontPath)},
        mText{textStr, *mFont.get(), fontSize}
    {
    }

    void TextWidget::SetString(const std::string &newString)
    {
        mText.setString(newString);
    }

    void TextWidget::SetTextSize(const unsigned int newSize)
    {
        mText.setCharacterSize(newSize);
    }

    sf::FloatRect TextWidget::GetBound() const
    {
        return mText.getGlobalBounds();
    }

    void TextWidget::LocationUpdated(const Vector2Df &newLocation)
    {
        mText.setPosition({newLocation.GetX(), newLocation.GetY()});
    }

    void TextWidget::RotationUpdated(const float newLocation)
    {
        mText.setRotation(newLocation);
    }

    void TextWidget::Draw(sf::RenderWindow &window) const
    {
        window.draw(mText);
    }
}

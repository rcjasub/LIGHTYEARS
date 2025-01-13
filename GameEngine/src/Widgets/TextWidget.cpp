#include "Widgets/TextWidget.hpp"
#include "framework/AssetsManager.hpp"

namespace ly
{
	TextWidget::TextWidget(const std::string& textStr, const std::string& fontPath, unsigned int characterSize)
		: m_font{AssetsManager::Get().LoadFont(fontPath)},
		m_text{ textStr, *(m_font.get()), characterSize }
	{
	}

	void TextWidget::SetString(const std::string& newStr)
	{
		m_text.setString(newStr);
	}

	void TextWidget::SetTextSize(unsigned int newSize)
	{
		m_text.setCharacterSize(newSize);
	}

	void TextWidget::LocationUpdated(const sf::Vector2f& newLocation)
	{
		m_text.setPosition(newLocation);
	}

	void TextWidget::RotationUpdated(float newRotation)
	{
		m_text.setRotation(newRotation);
	}

	void TextWidget::Draw(sf::RenderWindow& windowRef)
	{
		windowRef.draw(m_text);
	}
		

}
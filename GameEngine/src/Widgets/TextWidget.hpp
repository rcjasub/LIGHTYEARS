#pragma once

#include "framework/core.hpp"
#include "Widgets/Widget.hpp"

namespace ly
{
	class TextWidget : public Widget
	{
	public:
		TextWidget(const std::string& textStr, const std::string& fontPath
			= "SpaceShooterRedux/Bonus/kenvector_future.ttf",
			unsigned int characterSize = 10
		);

		void SetString(const std::string& newStr);
		void SetTextSize(unsigned int newSize);

	private:
		virtual void LocationUpdated(const sf::Vector2f& newLocation) override;
		virtual void RotationUpdated(float newRotation) override;
		virtual void Draw(sf::RenderWindow& windowRef) override;
		shared<sf::Font> m_font;
		sf::Text m_text;
		
	};

}
#pragma once 

#include <SFML/Graphics.hpp>
#include "framework/Object.hpp"

namespace ly
{
	class Widget : public Object
	{
	public:
		void NativeDraw(sf::RenderWindow& windowRef);
		virtual bool HandleEvent(const sf::Event& event);
		void SetWidgetLocation(const sf::Vector2f& newLocation);
		void SetWidgetRotation(float newRotation);

		sf::Vector2f GetWidgetLocation() const { return widgetTransform.getPosition(); }
		float GetWidgetRotation() const { return widgetTransform.getRotation(); }

		void SetVisible(bool isVisible);
		bool GetVisible() const { return mIsVisible; }

	protected:
		Widget();

	private:
		virtual void Draw(sf::RenderWindow& windowRef);
		virtual void LocationUpdated(const sf::Vector2f& newLocation);
		virtual void RotationUpdated(float newRotation);

		sf::Transformable widgetTransform;
		bool mIsVisible;
	};
}
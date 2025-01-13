#include "Widgets/Widget.hpp"

namespace ly
{
	void Widget::NativeDraw(sf::RenderWindow& windowRef)
	{
		if (mIsVisible)
		{
			Draw(windowRef);
		}
	}

	bool Widget::HandleEvent(const sf::Event& event)
	{
		return false;
	}

	void Widget::SetWidgetLocation(const sf::Vector2f& newLocation)
	{
		widgetTransform.setPosition(newLocation);
		LocationUpdated(newLocation);
	}

	void Widget::SetWidgetRotation(float newRotation)
	{
		widgetTransform.setRotation(newRotation);
		RotationUpdated(newRotation);
	}

	void Widget::SetVisible(bool isVisible)
	{
		mIsVisible = isVisible;
	}

	Widget::Widget()
		: mIsVisible{true},
		widgetTransform{}
	{
	}

	void Widget::Draw(sf::RenderWindow& windowRef)
	{

	}

	void Widget::LocationUpdated(const sf::Vector2f& newLocation)
	{

	}

	void Widget::RotationUpdated(float newRotation)
	{

	}

	
}
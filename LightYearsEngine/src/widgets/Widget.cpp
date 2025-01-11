//
// Created by wbowen on 11/15/24.
//

#include "Widget.hpp"

namespace ly {
    void Widget::NativeDraw(sf::RenderWindow &window) const
    {
        if(mIsVisible)
        {
            Draw(window);
        }
    }

    void Widget::NativeUpdate(sf::RenderWindow &window)
    {
    }

    bool Widget::HandleEvent(const sf::Event &event)
    {
        return false;
    }

    void Widget::SetWidgetLocation(const Vector2Df newLocation)
    {
        mWidgetTransform.setPosition({newLocation.GetX(), newLocation.GetY()});
        LocationUpdated(newLocation);
    }

    void Widget::SetWidgetRotation(float newRotation)
    {
        mWidgetTransform.setRotation(newRotation);
        RotationUpdated(newRotation);
    }

    Vector2Df Widget::GetWidgetLocation() const
    {
        auto const pos = mWidgetTransform.getPosition();
        return Vector2Df{pos.x, pos.y};
    }

    void Widget::SetVisibility(const bool newVisibility)
    {
        mIsVisible = newVisibility;
    }

    Vector2Df Widget::GetCenterPosition() const
    {
        const sf::FloatRect bounds = GetBound();
        return Vector2Df{bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f};
    }

    Widget::Widget(const std::string& name):
    Object{name},
    mIsVisible{true},
    mWidgetTransform{}
    {
    }

    void Widget::Draw(sf::RenderWindow &window) const
    {
    }

    void Widget::LocationUpdated(const Vector2Df &newLocation)
    {
    }

    void Widget::RotationUpdated(const float newRotation)
    {
    }
} // ly
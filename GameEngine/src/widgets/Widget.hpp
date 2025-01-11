

#pragma once
#include "Object.hpp"
#include "Vector2D.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Transformable.hpp"

namespace ly
{

class Widget : public Object
{
public:
    ~Widget() override = default;
    void NativeDraw(sf::RenderWindow& window) const;
    virtual void NativeUpdate(sf::RenderWindow& window);
    virtual bool HandleEvent(const sf::Event& event);
    void SetWidgetLocation(Vector2Df newLocation);
    void SetWidgetRotation(float newRotation);

    Vector2Df GetWidgetLocation() const;
    float GetWidgetRotation() const {return mWidgetTransform.getRotation();};

    void SetVisibility(bool newVisibility);
    bool GetVisibility() const {return mIsVisible;}

    virtual sf::FloatRect GetBound() const = 0;
    virtual Vector2Df GetCenterPosition() const;
protected:
    Widget() = delete;
    explicit Widget(const std::string& name);
private:
    bool mIsVisible;
    sf::Transformable mWidgetTransform;

    virtual void Draw(sf::RenderWindow& window) const;
    virtual void LocationUpdated(const Vector2Df& newLocation);
    virtual void RotationUpdated(const float newRotation);
};

}

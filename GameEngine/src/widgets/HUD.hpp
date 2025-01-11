

#pragma once
#include "Object.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

namespace ly
{

class HUD: public Object
{
public:
    ~HUD() override = default;
    virtual void Draw(sf::RenderWindow& windowRef) = 0;
    void NativeInit(sf::RenderWindow& windowRef); // todo, make const
    bool Initialized() const {return mIsInitialized;}
    virtual bool HandleEvent(const sf::Event& event);
    virtual void Tick(float deltaTime);
protected:
    HUD() = delete;
    explicit HUD(const std::string& name);
private:
    virtual void Init(sf::RenderWindow& windowRef) = 0;
    bool mIsInitialized;
};

}

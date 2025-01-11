

#pragma once
#include "Actor.hpp"

namespace ly
{

class Particle final : public Actor
{
public:
    Particle() = delete;

    Particle(const std::string &name, World *owningWorld, const std::string &texturePath);

    void Tick(const float deltaTime) override;

    void RandomVelocity(float minSpeed, float maxSpeed);
    void RandomSize(float minSize, float maxSize);
    void RandomLifetime(float minLifetime, float maxLifetime);

private:
    void Move(float delta_time);
    void Fade(float delta_time);
    Vector2Df mVelocity;
    float mLifeTime;
    sf::Clock mTimer;

};

}

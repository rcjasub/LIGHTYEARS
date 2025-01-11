
#pragma once
#include "Actor.hpp"

namespace ly {

class BackDropActor : public Actor
{
public:
    BackDropActor(World* owningWorld, const std::string& texturePath, const Vector2Df& velocity = Vector2Df{0.0f, -50.0f });

    void Tick(const float deltaTime) override;
private:
    Vector2Df mMovingVelocity;
    float mLeftShift;
    float mTopShift;

};

}

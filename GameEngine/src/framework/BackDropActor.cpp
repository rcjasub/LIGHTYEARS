
#include "BackDropActor.hpp"
#include "World.hpp"

namespace ly {
    BackDropActor::BackDropActor(World *owningWorld, const std::string &texturePath, const Vector2Df &velocity):
        Actor{"BackDropActor", owningWorld, texturePath},
        mMovingVelocity{velocity},
        mLeftShift{0},
        mTopShift{0}
    {
        const auto windowSize{owningWorld->GetWindowSize()};
        GetSprite().setOrigin(0.0f,0.0f);
        GetSprite().setTextureRect(sf::IntRect{{0,0 }, {static_cast<int>(windowSize.GetX()), static_cast<int>(windowSize.GetY())}});
        SetTextureRepeated(true);
    }

    void BackDropActor::Tick(const float deltaTime)
    {
        Actor::Tick(deltaTime);

        mLeftShift += mMovingVelocity.GetX() * deltaTime;
        mTopShift += mMovingVelocity.GetY() * deltaTime;

        sf::IntRect currentRect{GetSprite().getTextureRect()};
        currentRect.left = static_cast<int>(mLeftShift);
        currentRect.top = static_cast<int>(mTopShift);

        GetSprite().setTextureRect(currentRect);
    }
}

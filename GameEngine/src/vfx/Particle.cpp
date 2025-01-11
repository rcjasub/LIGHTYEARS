

#include "Particle.hpp"
#include "MathUtility.hpp"

namespace ly
{
    Particle::Particle(const std::string &name, World *owningWorld, const std::string &texturePath):
        Actor{name, owningWorld, texturePath},
        mVelocity{0.0f, 0.0f},
        mLifeTime{1.0f},
        mTimer{}
    {
    }

    void Particle::Tick(const float deltaTime)
    {
        Actor::Tick(deltaTime);
        Move(deltaTime);
        Fade(deltaTime);

        if(mTimer.getElapsedTime().asSeconds() >= mLifeTime)
        {
            Destroy();
        }
    }

    void Particle::RandomVelocity(const float minSpeed, const float maxSpeed)
    {
        mVelocity = MathUtility::RandomUnitVector() * MathUtility::RandomRange(minSpeed, maxSpeed);
    }

    void Particle::RandomSize(const float minSize, const float maxSize)
    {
        const float randomScale = MathUtility::RandomRange(minSize, maxSize);
        GetSprite().setScale(randomScale, randomScale);
    }

    void Particle::RandomLifetime(const float minLifetime, const float maxLifetime)
    {
        mLifeTime = MathUtility::RandomRange(minLifetime, maxLifetime);
    }

    void Particle::Move(const float delta_time)
    {
        AddActorLocationOffset(mVelocity * delta_time);
    }

    void Particle::Fade(const float delta_time)
    {
        const float elapsedTime = mTimer.getElapsedTime().asSeconds();
        GetSprite().setColor(MathUtility::LerpColor(GetSprite().getColor(), sf::Color{255, 255, 255, 0}, elapsedTime/mLifeTime));
        const auto scale{GetSprite().getScale()};
        const auto lerp{MathUtility::LerpVector(Vector2Df{scale.x, scale.y}, Vector2Df{0.0f, 0.0f}, elapsedTime/mLifeTime)};
        GetSprite().setScale({lerp.GetX(), lerp.GetY()});
    }


}

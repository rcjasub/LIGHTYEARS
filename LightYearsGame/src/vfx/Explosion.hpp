

#pragma once

#include <string>

#include "Core.hpp"
#include "Vector2D.hpp"
#include "SFML/Graphics/Color.hpp"

namespace ly
{
class World;
class Explosion
{
public:
    explicit Explosion(int particleAmt = 20,
              float lifetimeMin = 0.5f,
              float lifetimeMax = 2.5f,
              float sizeMin = 1,
              float sizeMax = 4,
              float speedMin = 200,
              float speedMax = 400,
              sf::Color particleColor = sf::Color{255, 128, 0, 255},
              std::initializer_list<std::string> paths =
              {
              "SpaceShooterRedux/PNG/Effects/star1.png",
                "SpaceShooterRedux/PNG/Effects/star2.png",
                "SpaceShooterRedux/PNG/Effects/star3.png"
              }
             );

    void SpawnExplosion(World *world, const Vector2Df &location) const;
private:
    int mParticleAmt;
    float mLifetimeMin;
    float mLifetimeMax;
    float mSizeMin;
    float mSizeMax;
    float mSpeedMin;
    float mSpeedMax;
    sf::Color mParticleColor;
    List<std::string> mParticleImagesPaths;
};

}

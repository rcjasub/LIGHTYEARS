#pragma once

#include "framework/core.hpp"
#include <string>
#include <SFML/Graphics.hpp>

namespace ly
{
    class World;

    class Explosion
    {
    public:
        Explosion(
            int particleAmt = 20,
            float LifeTimeMin = 0.5f,
            float LifeTimeMax = 1.f,
            float SizeMin = 1,
            float SizeMax = 2,
            float SpeedMin = 200,
            float SpeedMax = 400,
            const sf::Color& particleColor = sf::Color{ 255, 128, 0, 255 },
            const std::vector<std::string>& ParticleImagePaths =
            {
                "SpaceShooterRedux/PNG/Effects/star1.png",
                "SpaceShooterRedux/PNG/Effects/star2.png",
                "SpaceShooterRedux/PNG/Effects/star3.png"
            }
        );

        void SpawnExplosion(World* world, const sf::Vector2f& location);

    private:
        int mParticleAmt;
        float mLifeTimeMin;
        float mLifeTimeMax;
        float mSizeMin;
        float mSizeMax;
        float mSpeedMin;
        float mSpeedMax;
        sf::Color mParticleColor;

        list<std::string> mParticleImagePaths;
    };
}

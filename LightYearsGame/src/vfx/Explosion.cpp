


#include "Explosion.hpp"
#include "MathUtility.hpp"
#include "World.hpp"
#include "Particle.hpp"

namespace ly
{
    Explosion::Explosion(const int particleAmt,
                         const float lifetimeMin,
                         const float lifetimeMax,
                         const float sizeMin,
                         const float sizeMax,
                         const float speedMin,
                         const float speedMax,
                         const sf::Color particleColor,
                         const std::initializer_list<std::string> paths):
        mParticleAmt{particleAmt},
        mLifetimeMin{lifetimeMin},
        mLifetimeMax{lifetimeMax},
        mSizeMin{sizeMin},
        mSizeMax{sizeMax},
        mSpeedMin{speedMin},
        mSpeedMax{speedMax},
        mParticleColor{particleColor},
        mParticleImagesPaths{paths}
    {
    }

    void Explosion::SpawnExplosion(World *world, const Vector2Df& location) const
    {
        if(!world)
        {
            LOG("No world passed to SpawnExplosion!!!");
            return;
        }
        for (int i = 0; i < mParticleAmt; i++)
        {
            const std::string particlePath = mParticleImagesPaths[static_cast<std::size_t>(MathUtility::RandomRange(0.0f, static_cast<float>(mParticleImagesPaths.size())))];
            weak<Particle> newParticle = world->SpawnActor<Particle>("Explosion Particle", world,particlePath);

            newParticle.lock()->RandomLifetime(mLifetimeMin, mLifetimeMax);
            newParticle.lock()->SetActorLocation(location);
            newParticle.lock()->RandomSize(mSizeMin, mSizeMax);
            newParticle.lock()->RandomVelocity(mSpeedMin, mSpeedMax);
            newParticle.lock()->GetSprite().setColor(mParticleColor);
        }
    }
}

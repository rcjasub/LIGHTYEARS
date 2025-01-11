#include "VFX/Explosion.h"
#include "framework/world.h"
#include "VFX/Particle.h"
#include "framework/MessUtility.h" 

namespace ly
{
    Explosion::Explosion(
        int particleAmt,
        float LifeTimeMin,
        float LifeTimeMax,
        float SizeMin,
        float SizeMax,
        float SpeedMin,
        float SpeedMax,
        const sf::Color& particleColor,
        const std::vector<std::string>& ParticleImagePaths
    )
        : mParticleAmt{ particleAmt },
        mLifeTimeMin{ LifeTimeMin },
        mLifeTimeMax{ LifeTimeMax },
        mSizeMin{ SizeMin },
        mSizeMax{ SizeMax },
        mSpeedMin{ SpeedMin },
        mSpeedMax{ SpeedMax },
        mParticleColor{ particleColor },
        mParticleImagePaths{ ParticleImagePaths }
    {
    }

    void Explosion::SpawnExplosion(World* world, const sf::Vector2f& location)
    {
        if (!world)
        {
            return; // Early exit if no world or no image paths
        }

        for (int i = 0; i < mParticleAmt; ++i)
        {
            // Choose a random particle image path
            std::string particleImagePath = mParticleImagePaths[(int)RandomRange(0, mParticleImagePaths.size())];

            // Spawn a new particle
            weak<Particle> newParticle = world->SpamActor<Particle>(particleImagePath);
            auto lockedParticle = newParticle.lock();

            if (lockedParticle) // Only proceed if the particle is valid
            {
                // Set random values for the particle
                lockedParticle->RandomLifeTime(mLifeTimeMin, mLifeTimeMax);
                lockedParticle->SetActorLocation(location);
                lockedParticle->RandomSize(mSizeMin, mSizeMax);
                lockedParticle->RandomVelocity(mSpeedMin, mSpeedMax);
                lockedParticle->GetSprite().setColor(mParticleColor);
            }
        }
    }
}
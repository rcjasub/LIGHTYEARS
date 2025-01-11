

#include "Spaceship.hpp"
#include "MathUtility.hpp"
#include "Explosion.hpp"

namespace ly
{
    Spaceship::~Spaceship()
    {
        LOG("Spaceship Destroyed");
    }

    Spaceship::Spaceship(const std::string& name, World *owningWorld, const std::string &texturePath):
        Actor{name, owningWorld, texturePath},
        mVelocity{},
        mHealthComponent{100.0f, 100.0f},
        mBLinkTime{0.0f},
        mBLinkDuration{0.2f},
        mBlinkColorOffset{255, 0, 0}
    {
    }

    void Spaceship::Tick(const float deltaTime)
    {
        Actor::Tick(deltaTime);
        AddActorLocationOffset(GetVelocity() * deltaTime);
        UpdateBlink(deltaTime);
    }

    void Spaceship::Shoot()
    {
    }

    void Spaceship::BeginPlay()
    {
        Actor::BeginPlay();
        SetEnablePhysics(true);
        mHealthComponent.OnHealthChanged.BindAction(GetSelfWeakSRef(), &Spaceship::OnHealthChanged);
        mHealthComponent.OnTakenDamage.BindAction(GetSelfWeakSRef(), &Spaceship::OnTakenDamage);
        mHealthComponent.OnHealthEmpty.BindAction(GetSelfWeakSRef(), &Spaceship::Blow);
    }

    void Spaceship::ApplyDamage(const float damage)
    {
        mHealthComponent.ChangeHealth(-damage);
    }

    void Spaceship::OnHealthChanged(float amt, float health, float maxHealth)
    {
        LOG("The health changed by %.1f, and is now %.1f/%.1f", amt, health, maxHealth);
    }

    void Spaceship::OnTakenDamage(float amt, float health, float maxHealth)
    {
        Blink();
    }

    void Spaceship::UpdateBlink(float deltaTime)
    {
        if(mBLinkTime > 0.0f)
        {
            mBLinkTime -= deltaTime;
            mBLinkTime = mBLinkTime > 0.0f ? mBLinkTime : 0.0f;

            GetSprite().setColor(MathUtility::LerpColor(sf::Color::White, mBlinkColorOffset, mBLinkTime));
        }
    }

    void Spaceship::Blink()
    {
        if(mBLinkTime == 0.0f)
        {
            mBLinkTime = mBLinkDuration;
        }
    }

    void Spaceship::Blow()
    {
        const auto exp = std::make_unique<Explosion>();
        exp->SpawnExplosion(GetWorld(), GetActorLocation());
        Blew();
        Destroy();
        // delete exp; // shouldn't be needed
    }

    void Spaceship::Blew()
    {
    }
}

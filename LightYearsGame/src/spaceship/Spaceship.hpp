
#pragma once
#include "Actor.hpp"
#include "HealthComponent.hpp"

namespace ly
{
    class Spaceship: public Actor
    {
    public:
        ~Spaceship() override;
        Spaceship() = delete;
        Spaceship(const std::string& name, World* owningWorld, const std::string& texturePath);
        void Tick(float deltaTime) override;

        Vector2Df GetVelocity() const {return mVelocity;}
        void SetVelocity(const Vector2Df &m_velocity){mVelocity = m_velocity;}

        virtual void Shoot();
        void BeginPlay() override;

        void ApplyDamage(float damage) override;
        HealthComponent& GetHealthComponent() {return mHealthComponent;}
    private:
        void OnHealthChanged(float amt, float health, float maxHealth);
        void OnTakenDamage(float amt, float health, float maxHealth);
        void UpdateBlink(float deltaTime);
        void Blink();
        void Blow();
        virtual void Blew();
        Vector2Df mVelocity;
        HealthComponent mHealthComponent;

        float mBLinkTime;
        float mBLinkDuration;
        sf::Color mBlinkColorOffset;
    };
}

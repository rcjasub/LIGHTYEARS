
#include "HealthComponent.hpp"
#include "Core.hpp"

namespace ly
{
    HealthComponent::HealthComponent(const float health, const float maxHealth):
        mHealth{health},
        mMaxHealth{maxHealth}
    {
    }

    void HealthComponent::SetInitialHealth(float health, float maxHealth)
    {
        mHealth = health;
        mMaxHealth = maxHealth;
    }

    void HealthComponent::ChangeHealth(float amt)
    {
        if(amt == 0) return;
        if(mHealth == 0) return;

        mHealth += amt;
        if(mHealth < 0)
        {
            mHealth = 0;
        }

        if(mHealth > mMaxHealth)
        {
            mHealth = mMaxHealth;
        }

        OnHealthChanged.Broadcast(amt, mHealth, mMaxHealth);

        if(amt < 0 )
        {
            TakeDamage(-amt);
            if(mHealth <= 0)
            {
                HealthEmpty();
            }
        }
        else
        {
            HealthRegen(amt);
        }
    }

    void HealthComponent::TakeDamage(const float amt)
    {
        LOG("Took damage: %.1f, now health os: %.1f/%.1f )", amt, mHealth, mMaxHealth);
        OnTakenDamage.Broadcast(amt, mHealth, mMaxHealth);
    }

    void HealthComponent::HealthEmpty()
    {
        LOG("Health empty");
        OnHealthEmpty.Broadcast();
    }

    void HealthComponent::HealthRegen(const float amt)
    {
        LOG("Took regained: %f, now health os: %f/%f )", amt, mHealth, mMaxHealth);
    }
}




#pragma once
#include "Delegate.hpp"

namespace ly
{
    class HealthComponent
    {
    public:
        ~HealthComponent() = default;
        HealthComponent(float health, float maxHealth);

        void SetInitialHealth(float health, float maxHealth);
        void ChangeHealth(float amt);
        [[nodiscard]] float GetHealth() const {return mHealth;}
        [[nodiscard]] float GetMaxHealth() const {return mMaxHealth;}

        Delegate<float,float,float> OnHealthChanged;
        Delegate<float,float,float> OnTakenDamage;
        Delegate<> OnHealthEmpty;
    private:
        void TakeDamage(float amt);
        void HealthEmpty();
        void HealthRegen(float amt);
        float mHealth;
        float mMaxHealth;
    };
}

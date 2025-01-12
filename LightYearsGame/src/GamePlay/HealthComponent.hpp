#pragma once

#include "framework/Delegate.hpp"

namespace ly
{

	class HealthComponent
	{
	public:

       HealthComponent(float health, float maxHealth);
	   void ChangeHealth(float amt);
	   float GetHealth() const { return mHealth; }
	   float GetMaxHealth() const { return mMaxHealth; }

	   DeLegate<float, float, float> onHealthChanged;
	   DeLegate<float, float, float> onTakenDamge;
	   DeLegate<> onHealthEmpty;

	private:

		void TakenDamage(float amt);
		void HealthEmpty();

		float mHealth;
		float mMaxHealth;

		
	};


}
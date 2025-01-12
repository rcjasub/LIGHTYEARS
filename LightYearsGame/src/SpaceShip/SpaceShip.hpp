#pragma once

#include"framework/Actor.hpp"
#include"framework/AssetsManager.hpp"
#include"GamePlay/HealthComponent.hpp"
#include"Weapon/Weapon.hpp"


namespace ly
{
	class SpaceShip : public Actor
	{
	public:
		SpaceShip(World* owningWorld, const std::string& textPack = "");
		virtual void Tick(float deltaTime) override;
		void setVelocity(const sf::Vector2f& newVel);
		sf::Vector2f GetVelocity() const { return mVelocity; }

		virtual void Shoot();
		virtual void BeganPlay() override;

		virtual void ApplyDamage(float amt) override;

		HealthComponent& GetHealthComponent() { return mHealthComp; }

	private:
		
		void Blink();

		void UpdateBlink(float deltaTime);

		virtual void OnHealthChanged(float amt, float health, float maxHealth);
	    virtual	void onTakenDamage(float amt, float health, float maxHealth);
	    void Blow();
		virtual void Blew();

		sf::Vector2f mVelocity;
		HealthComponent mHealthComp;

		float mBlinkTime;
		float mBlinkDuration;
	    sf::Color mBlinkColorOffset;
	};
}
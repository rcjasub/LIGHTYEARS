#include "SpaceShip/SpaceShip.h"
#include "framework/MessUtility.h"
#include "VFX/Explosion.h"

namespace ly {

	SpaceShip::SpaceShip(World* owningWorld, const std::string& textPack)
		:Actor{owningWorld, textPack},
		mVelocity{},
		mHealthComp{100.f, 100.f},
		mBlinkTime{0.f},
		mBlinkDuration{0.2f},
		mBlinkColorOffset{ 255, 0, 0, 255 }
	{

	}

	void SpaceShip::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		addActorLocationOffset(GetVelocity() * deltaTime);
		UpdateBlink(deltaTime);
	}

	void SpaceShip::setVelocity(const sf::Vector2f& newVel)
	{
		mVelocity = newVel;
	}

	void SpaceShip::Shoot()
	{

	}

	void SpaceShip::BeganPlay()
	{
		Actor::BeganPlay();
		setEnablePhysics(true);

		mHealthComp.onHealthChanged.BindAction(GetWeakRef(), &SpaceShip::OnHealthChanged);
		mHealthComp.onTakenDamge.BindAction(GetWeakRef(), &SpaceShip::onTakenDamage);
		mHealthComp.onHealthEmpty.BindAction(GetWeakRef(), &SpaceShip::Blow);

	}

	void SpaceShip::ApplyDamage(float amt)
	{
		mHealthComp.ChangeHealth(-amt);
	}

	void SpaceShip::Blink()
	{
		if (mBlinkTime == 0)
		{
			mBlinkTime = mBlinkDuration;
		}
	}

	void SpaceShip::UpdateBlink(float deltaTime)
	{
		if (mBlinkTime > 0)
		{
			mBlinkTime -= deltaTime;
			mBlinkTime = mBlinkTime > 0 ? mBlinkTime : 0.f;

			GetSprite().setColor(lerpColor(sf::Color::White, mBlinkColorOffset, mBlinkTime));
		}
	}

	void SpaceShip::OnHealthChanged(float amt, float health, float maxHealth)
	{
		
	}

	void SpaceShip::onTakenDamage(float amt, float health, float maxHealth)
	{
		Blink();
	}

	void SpaceShip::Blow()
	{
		/*Explosion* exp = new Explosion();
		exp->SpawnExplosion(GetWorld(), GetActorLocation());
		Destroy();
		delete exp;*/
		Blew();
		Destroy();
	}

	void SpaceShip::Blew()
	{
	}

}
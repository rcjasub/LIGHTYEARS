#pragma once

#include"framework/Actor.hpp"

namespace ly
{
	class Bullet : public Actor
	{
	public:
		Bullet(World* world, Actor* owner, const std::string& texturePath, float speed = 500.f, float damage = 10.f);
		
		void SetSpeed(float newSpeed);
		void SetDamage(float newDamage);

		float GetDamage() const { return mDamage; }

		virtual void Tick(float deltaTime) override;
		virtual void BeganPlay() override;

	private:

		virtual void OnActorBeginOverlap(Actor* other) override;

		void Move(float deltaTime);

		Actor* mOwner;
		float mSpeed;
		float mDamage;


	};
}

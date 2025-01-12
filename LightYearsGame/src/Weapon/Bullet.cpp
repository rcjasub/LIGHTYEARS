#include "Bullet.hpp"
#include "framework/core.hpp"

namespace ly
{
	Bullet::Bullet(World* world, Actor* owner, const std::string& texturePath, float speed, float damage)
		: Actor{ world, texturePath },
		mOwner{ owner },
		mSpeed{ speed },
		mDamage{ damage }

	{
		setTeamId(owner->GetTeamId());
	}

	void Bullet::SetSpeed(float newSpeed)
	{
		mSpeed = newSpeed;
	}

	void Bullet::SetDamage(float newDamage)
	{
		mDamage = newDamage;
	}

	void Bullet::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		Move(deltaTime);

		if (isActorIsOutOfWindowBound())
		{
			Destroy();
		}
	}

	void Bullet::BeganPlay()
	{
		Actor::BeganPlay();
		setEnablePhysics(true);
	}

	void Bullet::OnActorBeginOverlap(Actor* other)
	{
		if (IsOtherHostile(other))
		{
			other->ApplyDamage(GetDamage());
			Destroy();
		}
	}

	void Bullet::Move(float deltaTime)
	{
		addActorLocationOffset(getActorForwardDirection() * mSpeed * deltaTime);
	}
}


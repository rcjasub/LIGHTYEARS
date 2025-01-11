
#include "Bullet.hpp"
#include "MathUtility.hpp"

namespace ly
{
    Bullet::Bullet(World *world, Actor const * const owner, const std::string &texturePath, const float speed, const float damage):
        Actor{"Bullet", world, texturePath},
        mOwner{owner},
        mSpeed{speed},
        mDamage{damage}
    {
        SetTeamId(owner->GetTeamId());
    }

    void Bullet::Move(const float delta_time)
    {
        AddActorLocationOffset(GetActorForwardDirection() * mSpeed * delta_time);
    }

    void Bullet::Tick(const float deltaTime)
    {
        Actor::Tick(deltaTime);
        Move(deltaTime);
        // This is source of potential bug if pending destroy not checked. Bounds check can be triggered multiple times and issue destroy multiple times which can lead to crashes
        if(IsActorOutOfWindowBounds() && !IsPendingDestroy())
        {
            // LOG("Bullet::Tick: Actor %s out of bounds", GetActorName().c_str());
            Destroy();
        }
    }

    void Bullet::BeginPlay()
    {
        Actor::BeginPlay();
        SetEnablePhysics(true);
    }

    void Bullet::OnActorBeginOverlap(Actor *other)
    {
        if(IsOtherHostile(other))
        {
            other->ApplyDamage(GetDamage());
            Destroy();
        }
    }
}

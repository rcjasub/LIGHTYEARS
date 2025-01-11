

#pragma once


#include "Actor.hpp"

namespace ly
{
    class Bullet: public Actor
    {
      public:
        explicit Bullet(World* world, Actor const * const owner, const std::string& texturePath, float speed, float damage);

        void SetSpeed(const float newspeed) { this->mSpeed = newspeed; }
        void SetDamage(const float damage) { this->mDamage = damage; }
        float GetDamage() const { return this->mDamage; }

        void Move(float delta_time);
        void Tick(float deltaTime) override;

        void BeginPlay() override;

    private:
        void OnActorBeginOverlap(Actor *other) override;
        Actor const * const mOwner;
        float mSpeed;
        float mDamage;
    };
}
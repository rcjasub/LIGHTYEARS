

#pragma once
#include "Spaceship.hpp"
#include "BulletShooter.hpp"
#include "TimerManager.hpp"

namespace ly
{
    class PlayerSpaceship final : public Spaceship
    {
    public:
        ~PlayerSpaceship() override;
        PlayerSpaceship() = delete;
        explicit PlayerSpaceship(const std::string &name, World* owningWorld, const std::string& path);

        void Tick(float deltaTime) override;
        void SetSpeed(float newSpeed);
        float GetSpeed() const;
        void Shoot() override;
        void SetShooter(unique<Shooter>&& newShooter);
    private:
        Vector2Df mMoveInput;
        float mSpeed;
        unique<Shooter> mShooter;
        void StopInvulnerable();
        void UpdateInvulnerable(float deltaTime);
        void ApplyDamage(float damage) override;
        void BeginPlay() override;

        void HandleInput();
        void NormalizeInput();
        void ClampInputOnEdge();
        void ConsumeInput(float deltaTime);

        float mInvulnerableTime;
        TimerHandle mInvulnerableTimer;
        bool mInvulnerable;

        float mInvulnerableFlashInterval;
        float mInvulnerableFlashTimer;
        float mInvulnerableFlashDirection;
    };
}

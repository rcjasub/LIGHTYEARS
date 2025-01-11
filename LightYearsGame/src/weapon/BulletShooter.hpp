
#pragma once

#include "Shooter.hpp"
#include "Vector2D.hpp"
#include <SFML/System.hpp>

namespace ly
{
    class BulletShooter : public Shooter
    {
    public:
        explicit BulletShooter(const Actor* owner,
                               float cooldownTime, Vector2Df localPositionOffset = {0,0},
                               float localRotationOffset = 0.0f,
                               const std::string& bulletTexturePath = "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
        [[nodiscard]] bool IsOnCooldown() const override;
        void IncrementCurrentLevel(unsigned amount) override;
        void SetBulletTexturePath(const std::string& bulletTexturePath);
    private:
        void ShootImpl() override;
        sf::Clock mCooldownClock;
        float mCooldownTime;
        Vector2Df mLocalPositionOffset;
        float mLocalRotationOffset;
        std::string mBulletTexturePath;
    };

}

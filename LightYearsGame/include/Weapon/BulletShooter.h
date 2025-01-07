#pragma once
#include"Weapon/Weapon.h"
#include<SFML/System.hpp>

namespace ly
{
	class BulletShooter : public Shooter
	{
	public:
		BulletShooter(Actor* owner, 
			float CoolDowntime = 1.f, 
			const sf::Vector2f LocalPositionOffset= {0.f, 0.f}, 
			float LocalRotationOffset = 0.f,
			const std::string& bulletTexturePath =  "SpaceShooterRedux/PNG/Lasers/laserBlue01.png"
			);
		virtual bool IsOnCoolDown() const override;
		virtual void IncrementLevel(int amt) override;
		void setBulletTexturePath(const std::string& bulletTexturePath);

	private:

		virtual void ShootImpl() override;
        sf::Clock mCoolDownClock;
		float mCoolDownTime;

		sf::Vector2f mLocalPositionOffset;
		float mLocalRotationOffset;
		std::string mBulletTexturePath;
	};

}

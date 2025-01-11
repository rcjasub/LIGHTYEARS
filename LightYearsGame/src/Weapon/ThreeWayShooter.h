#pragma once 

#include <SFML/Graphics.hpp>
#include "BulletShooter.h"

namespace ly
{
	class ThreeWayShooter : public Shooter
	{
	public:
		ThreeWayShooter(Actor* owner, float coolDonwTime = .3f, const sf::Vector2f& localOffset = { 0.f, 0.f });

		BulletShooter mShooterLeft;
		BulletShooter mShooterMid;
	    BulletShooter mShooterRight;

		BulletShooter mTopLevelShooterLeft;
		BulletShooter mTopLevelShooterRight;

		virtual void IncrementLevel(int amt) override;
	private:

		virtual void ShootImpl() override;
	};
}
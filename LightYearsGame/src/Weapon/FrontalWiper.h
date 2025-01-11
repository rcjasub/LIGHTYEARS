#pragma once 

#include <SFML/Graphics.hpp>
#include "BulletShooter.h"

namespace ly
{
	class FrontalWiper : public Shooter
	{
	public:
		FrontalWiper(Actor* owner,
			float coolDonwTime = 0.3f,
			const sf::Vector2f& localOffset = { 0.f, 0.f },
			float Width = 60.f
		);

		virtual void IncrementLevel(int amt) override;	
	private:

		virtual void ShootImpl() override;

		float mWidth;

		BulletShooter mShooter1;
		BulletShooter mShooter2;
		BulletShooter mShooter3;
		BulletShooter mShooter4;

		BulletShooter mShooter5;
		BulletShooter mShooter6;
		
	};
}
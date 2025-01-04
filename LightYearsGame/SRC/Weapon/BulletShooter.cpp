#include "Weapon/BulletShooter.h"
#include "framework/core.h"
#include "Weapon/Bullet.h"
#include "framework/world.h"

namespace ly
{
	BulletShooter::BulletShooter(Actor* owner, float CoolDowntime, const sf::Vector2f LocalPositionOffset, float LocalRotationOffset, const std::string& bulletTexturePath)
		: Shooter{ owner },
		mCoolDownClock{},
		mCoolDownTime{ CoolDowntime },
		mLocalPositionOffset{ LocalPositionOffset },
		mLocalRotationOffset{ LocalRotationOffset },
		mBulletTexturePath { bulletTexturePath }
	{
	}

	bool BulletShooter::IsOnCoolDown() const
	{
		if (mCoolDownClock.getElapsedTime().asSeconds() > mCoolDownTime)
		{
			return false;
		}

		return true;
	}

	void BulletShooter::setBulletTexturePath(const std::string& bulletTexturePath)
	{
		mBulletTexturePath = bulletTexturePath;
	}

	void BulletShooter::ShootImpl()
	{  

		sf::Vector2f ownerForwardDir = GetOwner()->getActorForwardDirection();
		sf::Vector2f ownerRightDir = GetOwner()->getActorRightDirection();

		mCoolDownClock.restart();
		weak<Bullet> newBullet = GetOwner()->GetWorld()->SpamActor<Bullet>(GetOwner(), mBulletTexturePath);
		newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation() + ownerForwardDir * mLocalPositionOffset.x + ownerRightDir * mLocalPositionOffset.y);
		newBullet.lock()->setActorRotation(GetOwner()->GetActorRotation() + mLocalRotationOffset);

	}
}
#pragma once

#include "framework/Actor.hpp"

namespace ly
{
	class Actor;
	class Shooter
	{
	public:
		void Shoot();

		virtual bool CanShot() const { return true; }
		virtual bool IsOnCoolDown() const { return false; }
		Actor* GetOwner() const { return mOwner; }

		int GetCurrentLevel() const { return mCurrentLevel; }
		int GetMaxLevel() const { return mMaxLevel; }

		virtual void IncrementLevel(int amt = 1);
	
	protected:
		Shooter(Actor* owner);

	private:
		virtual void ShootImpl() = 0;
		Actor* mOwner;

		int mCurrentLevel;
		int mMaxLevel;
	};

}
#pragma once

#include "framework/Object.h"
#include "framework/Delegate.h"

namespace ly
{
	class PlayerSpaceShip;
	class World;
	class Player : public Object
	{
	public:
		Player();
		weak<PlayerSpaceShip> SpawnSpaceShip(World* world);
		const weak<PlayerSpaceShip> GetCurrentPlayerSpaceShip() const { return mCurrentPlayerSpaceShip; }

		void AddLifeCount(unsigned int count);
		int GetLifeCount() const { return mLifeCount; }

		void AddScore(unsigned int amt);
		int GetScore() const { return mScore; }
	
		DeLegate<int> OnLifeChange;
		DeLegate<int> OnScoreChange;
		DeLegate<> OnLifeExhausted;

	private:
		unsigned int mLifeCount;
		unsigned int mScore;
		weak<PlayerSpaceShip> mCurrentPlayerSpaceShip;
	};
}
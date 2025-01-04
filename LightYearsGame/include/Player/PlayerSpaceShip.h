#pragma once
#include "SpaceShip/SpaceShip.h"

namespace ly {

	class Shooter;
	class PlayerSpaceShip : public SpaceShip
	{
	public:
		PlayerSpaceShip(World* owningWorld, const std::string& Path = "SpaceShooterRedux/PNG/playerShip1_blue.png");
		virtual void Tick(float deltaTime) override;
		void setSpeed(float newSpeed) { mSpeed = newSpeed; }
		float getSpeed() const { return mSpeed; }
		virtual void Shoot() override;
		
		void SetShooter(unique<Shooter>&& newShooter);

	private:
		void HandleInput();
		void NormalizeInput();
		void ClampInputEdge();
		void consumeInput(float deltaTime);
		sf::Vector2f mMoveInput;
		float mSpeed;

		unique<Shooter> mShooter;

	};

}
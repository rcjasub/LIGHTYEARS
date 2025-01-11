#include "Player/PlayerSpaceShip.h"
#include <SFML/System.hpp>
#include "framework/MessUtility.h"
#include "Weapon/BulletShooter.h"
#include "Weapon/ThreeWayShooter.h"
#include "Weapon/FrontalWiper.h"

namespace ly
{
	PlayerSpaceShip::PlayerSpaceShip(World* owningWorld, const std::string& Path)
		: SpaceShip(owningWorld, Path),
		mMoveInput{},
		mSpeed{ 500.f },
		mShooter{ new BulletShooter{this, .1f, {50.f, 0.f}} }
	{
		setTeamId(1);
	}

	void PlayerSpaceShip::Tick(float deltaTime)
	{
		SpaceShip::Tick(deltaTime);
		HandleInput();
		consumeInput(deltaTime);
	}
	void PlayerSpaceShip::Shoot()
	{
		if (mShooter)
		{
			mShooter->Shoot();
		}
	}

	void PlayerSpaceShip::SetShooter(unique<Shooter>&& newShooter)
	{
		if (mShooter && typeid(*mShooter.get()) == typeid(*newShooter.get()))
		{
			mShooter->IncrementLevel();
			return;
		}

		mShooter = std::move(newShooter);
	}

	void PlayerSpaceShip::HandleInput()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			mMoveInput.y = -1.f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			mMoveInput.y = 1.f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			mMoveInput.x = -1.f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			mMoveInput.x = 1.f;
		}

		ClampInputEdge();
		NormalizeInput();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			Shoot();
		}
	
	}
	void PlayerSpaceShip::NormalizeInput()
	{
		Normalize(mMoveInput);
	}

	void PlayerSpaceShip::ClampInputEdge()
	{
		sf::Vector2f actorLocation = GetActorLocation();
		if (actorLocation.x < 0 && mMoveInput.x == -1.f)
		{
			mMoveInput.x = 0.f;
		}

		if (actorLocation.x > GetWindowSize().x && mMoveInput.x == 1.f)
		{
			mMoveInput.x = 0.f;
		}

		if (actorLocation.y < 0 && mMoveInput.y == -1.f)
		{
			mMoveInput.y = 0.f;
		}
		
		if (actorLocation.y > GetWindowSize().y && mMoveInput.y == 1.f)
		{
			mMoveInput.y = 0.f;
		}
	}

	void PlayerSpaceShip::consumeInput(float deltaTime)
	{
		setVelocity(mMoveInput * mSpeed);
		mMoveInput.x = mMoveInput.y = 0.f;
		setActorRotation(270.f);
	}
}
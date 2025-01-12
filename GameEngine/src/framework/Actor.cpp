#include <box2d/b2_body.h>

#include"framework/Actor.hpp"
#include"framework/core.hpp"
#include"framework/AssetsManager.hpp"
#include"framework/MathUtility.hpp"
#include"framework/world.hpp"
#include"framework/PhysicsSystem.hpp"

namespace ly
{
	Actor::Actor(World* owningWorld, const std::string& texturePack)
		: mOwningWorld(owningWorld),
		mHasBeganPlay{false},
		mSprite{},
		mTexture{},
		mPhysicsBody{nullptr},
		mPhysicsEnable{false},
		mTeamID{GetNeturalTeamId()}
	{
		SetTexture(texturePack);
	}

	Actor::~Actor()
	{
		
	}

	void Actor::BeginPlayInternal()
	{
		if (!mHasBeganPlay)
		{
			mHasBeganPlay = true;
			BeganPlay();
		}
	}

	void Actor::TickInternal(float deltaTime)
	{
		if (!IsPendingDestroy())
		{
			Tick(deltaTime);
		}
	}

	void Actor::BeganPlay()
	{
		
	}

	void Actor::Tick(float deltaTime)
	{
		
	}

	void Actor::SetTexture(const std::string& texturePack)
	{
		AssetsManager& assetsManager = AssetsManager::Get();

		mTexture = assetsManager.LoadTexture(texturePack);
		if (!mTexture) return;
		mSprite.setTexture(*mTexture);
		
		int textureWidth = mTexture->getSize().x;
		int textureHeight = mTexture->getSize().y;

		mSprite.setTextureRect(sf::IntRect{ sf::Vector2i{}, sf::Vector2i{textureWidth, textureHeight} });
		CenterPivot();
	}

	void Actor::Render(sf::RenderWindow& Window)
	{
		if (IsPendingDestroy())
		{
			return;
		}
		
		Window.draw(mSprite);
	}
	void Actor::SetActorLocation(const sf::Vector2f& newLoc)
	{
		mSprite.setPosition(newLoc);
		UpdatePhysicsTransform();
		

	}
	float Actor::GetActorRotation() const
	{
		return mSprite.getRotation();

	}
	void Actor::setActorRotation(float newRot)
	{
		mSprite.setRotation(newRot);
		UpdatePhysicsTransform();
	} 
	void Actor::addActorLocationOffset(const sf::Vector2f& offsetAmt)
	{
		SetActorLocation(GetActorLocation() + offsetAmt);
	}
	void Actor::addActorRotationOffset(float offsetAmt)     
	{
		setActorRotation(GetActorRotation() + offsetAmt);
	}
	sf::Vector2f Actor::GetActorLocation() const   
	{
		return mSprite.getPosition();
	}
	sf::Vector2f Actor::getActorForwardDirection() const 
	{
		return RotationVector(GetActorRotation());
	}
	sf::Vector2f Actor::getActorRightDirection() const
	{
		return RotationVector(GetActorRotation());
	} 
	sf::FloatRect Actor::GetActorGlobalBounds() const
	{
		return mSprite.getGlobalBounds();
	}

	sf::Vector2u Actor::GetWindowSize() const
	{
		return mOwningWorld->GetWindowSize();
	}

	bool Actor::isActorIsOutOfWindowBound(float allowance) const
	{
		float windowWidth = GetWorld()->GetWindowSize().x;
		float windowHeight = GetWorld()->GetWindowSize().y;

		float width = GetActorGlobalBounds().width;
		float height = GetActorGlobalBounds().height;

		sf::Vector2f actorPos = GetActorLocation();

		if (actorPos.x < -width - allowance)
		{
			return true;
		}

	    if (actorPos.x > windowWidth + width + allowance)
		{
			return false;
		}

		if (actorPos.y < -height - allowance)
		{
			return true;
		}

		if (actorPos.y > windowHeight + height + allowance)
		{
			return false;
		}

		return false;
	}

	void Actor::setEnablePhysics(bool enable)
	{
		mPhysicsEnable = enable;

		if (mPhysicsEnable)
		{
			InitializePhysics();
		}
		else
		{
			UnInitializePhysics();
		}

	}

	void Actor::OnActorBeginOverlap(Actor* other)
	{
		
	}

	void Actor::OnActorEndOverlap(Actor* other)
	{
		
	}

	void Actor::Destroy()
	{
		UnInitializePhysics();
		Object::Destroy();
	}

	bool Actor::IsOtherHostile(Actor* other) const
	{
		if (other == nullptr) return false;

		if (GetTeamId() == GetNeturalTeamId() || other->GetTeamId() == GetNeturalTeamId())
		{
			return false;
		}

		return GetTeamId() != other->GetTeamId();
	}

	void Actor::ApplyDamage(float amt)
	{

	}

	void Actor::InitializePhysics()
	{
		if (!mPhysicsBody)
		{
			mPhysicsBody = PhysicsSystem::Get().addListener(this);
		}
	}

	void Actor::UnInitializePhysics()
	{
		if (mPhysicsBody)
		{
			PhysicsSystem::Get().removeListener(mPhysicsBody);
			mPhysicsBody = nullptr;
		}
	}

	void Actor::UpdatePhysicsTransform()
	{
		if (mPhysicsBody )
		{
			float physicsScale = PhysicsSystem::Get().GetPhysicsScale();
			b2Vec2 pos{ GetActorLocation().x * physicsScale, GetActorLocation().y * physicsScale };
			float rotation = DegreesToRadiant(GetActorRotation());

			mPhysicsBody->SetTransform(pos, rotation);
		}
	}

	void Actor::CenterPivot()
	{
		sf::FloatRect bound = mSprite.getGlobalBounds();
		mSprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
	}
}
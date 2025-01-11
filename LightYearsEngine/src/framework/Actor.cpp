#include "Actor.hpp"
#include "AssetManager.hpp"
#include "Core.hpp"
#include "MathUtility.hpp"
#include "PhysicsSystem.hpp"
#include "World.hpp"
#include <SFML/Graphics/Texture.hpp>

namespace ly
{
    Actor::Actor(const std::string& name, World *owningWorld, const std::string &texturePath):
        Object{name},
        mOwningWorld{owningWorld},
        mHasBeganPlay{false},
        mSprite{},
        mTexture{},
        mPhysicsBody{nullptr},
        mPhysicsEnabled{false},
        mTeamId{GetNeutralTeamId()}
    {
        SetTexture(texturePath);
    }
    void Actor::BeginPlayInternal()
    {
        if(!mHasBeganPlay)
        {
            mHasBeganPlay = true;
            BeginPlay();
        }
    }
    void Actor::BeginPlay()
    {
        // LOG("Actor %s begin Play", mName.c_str());
    }
    
    void Actor::Tick(float deltaTime)
    {
        // LOG("Actor %s Ticking", mName.c_str());
    }

    void Actor::TickInternal(const float deltaTime)
    {
        if(!IsPendingDestroy())
        {
            Tick(deltaTime);
        }
    }

    void Actor::SetTexture(const std::string &texturePath)
    {
        mTexture = AssetManager::Get().LoadTexture(texturePath);
        if(!mTexture)
        {
            return;
        }
        mSprite.setTexture(*mTexture);

        const int textureWidth = static_cast<int>(mTexture->getSize().x);
        const int textureHeight = static_cast<int>(mTexture->getSize().y);
        mSprite.setTextureRect(sf::IntRect{{}, {textureWidth, textureHeight}});
        CenterPivot();
    }

    void Actor::Render(sf::RenderWindow &window) const
    {
        if(!IsPendingDestroy())
        {
            window.draw(mSprite);
        }
    }

    void Actor::SetActorLocation(const Vector2Df &newLoc)
    {
        mSprite.setPosition({newLoc.GetX(), newLoc.GetY()});
        UpdatePhysicsBodyTransform();
    }

    void Actor::SetActorRotation_degrees(const float newRot_degrees)
    {
        mSprite.setRotation(newRot_degrees);
        UpdatePhysicsBodyTransform();
    }

    Vector2Df Actor::GetActorLocation() const
    {
        const auto pos {mSprite.getPosition()};
        return Vector2Df{pos.x, pos.y};
    }

    float Actor::GetActorRotation_rad() const
    {
        return mSprite.getRotation();
    }

    void Actor::AddActorLocationOffset(const Vector2Df &offSet)
    {
        SetActorLocation(GetActorLocation() + offSet);
    }

    void Actor::AddActorRotationOffset(const float newOffset)
    {
        SetActorRotation_degrees(GetActorRotation_rad() + newOffset);
    }

    Vector2Df Actor::GetActorForwardDirection() const
    {
        return MathUtility::RotationToVector(GetActorRotation_rad());
    }

    Vector2Df Actor::GetActorRightDirection() const
    {
        return MathUtility::RotationToVector(GetActorRotation_rad() + 90.0f);
    }

    sf::FloatRect Actor::GetActorGlobalBounds() const
    {
        return mSprite.getGlobalBounds();
    }

    Vector2Du Actor::GetWidowSize() const
    {
        return mOwningWorld->GetWindowSize();
    }

    bool Actor::IsActorOutOfWindowBounds(const float allowance) const
    {
        const float windowWidth = static_cast<float>(mOwningWorld->GetWindowSize().GetX());
        const float windowHeight = static_cast<float>(mOwningWorld->GetWindowSize().GetY());

        const float width = GetActorGlobalBounds().width;
        const float height = GetActorGlobalBounds().height;

        const auto actorLocation = GetActorLocation();

        if(actorLocation.GetX() < -width - allowance)
        {
            return true;
        }

        if(actorLocation.GetX() > windowWidth + width + allowance)
        {
            return true;
        }

        if(actorLocation.GetY() < -height - allowance)
        {
            return true;
        }

        if(actorLocation.GetY() > windowHeight + height + allowance)
        {
            return true;
        }

        return false;

    }

    void Actor::SetEnablePhysics(const bool enable)
    {
        mPhysicsEnabled = enable;
        if(mPhysicsEnabled)
        {
            InitializePhysics();
        }
        else
        {
            UnInitializePhysics();
        }
    }

    void Actor::OnActorBeginOverlap(Actor *other)
    {
        // LOG("Overlapped Begin Me: %s/Other: %s", mName.data(), other->mName.data());
    }

    void Actor::OnActorEndOverlap(Actor *other)
    {
        // LOG("Overlap End Me: %s/Other: %s", mName.data(), other->mName.data());
    }

    void Actor::Destroy()
    {
        UnInitializePhysics();
        onActorDestroyed.Broadcast(this);
        Object::Destroy();
    }

    bool Actor::IsOtherHostile(Actor *other) const
    {
        if(other == nullptr)
        {
            return false;
        }

        if(GetTeamId() == GetNeutralTeamId() || other->GetTeamId() == GetNeutralTeamId())
        {
            return false;
        }

        return GetTeamId() != other->GetTeamId();
    }

    void Actor::SetTextureRepeated(const bool repeated) const
    {
        mTexture->setRepeated(repeated);
    }

    void Actor::InitializePhysics()
    {
        if(mPhysicsBody == nullptr)
        {
            mPhysicsBody = PhysicsSystem::GetInstance().AddListener(this);
        }
    }

    void Actor::UnInitializePhysics()
    {
        if(mPhysicsBody != nullptr)
        {
            PhysicsSystem::GetInstance().RemoveListener(mPhysicsBody);
            // this prevents multiple removals of same object if caller errantly calls destroy on same object more than once
            mPhysicsBody = nullptr;
        }
    }

    void Actor::UpdatePhysicsBodyTransform() const
    {
        if(mPhysicsBody)
        {
            const float physicsScale = PhysicsSystem::GetInstance().GetPhysicsScale();
            const b2Vec2 pos{GetActorLocation().GetX() * physicsScale, GetActorLocation().GetY() * physicsScale};
            const float rotation_rad = MathUtility::DegreesToRadians(GetActorRotation_rad());  // todo - figure out whether angle utility functions are degrees or radians, something fishy in use cases
            mPhysicsBody->SetTransform(pos, rotation_rad);
        }
    }

    void Actor::CenterPivot()
    {
        const sf::FloatRect bound = mSprite.getGlobalBounds();
        mSprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
    }
}

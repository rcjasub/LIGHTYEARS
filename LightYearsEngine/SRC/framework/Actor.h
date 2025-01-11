#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Object.h"
#include "framework/core.h"

class b2Body;

namespace ly
{
    class World;
    class Actor : public Object
    {
    public:
        Actor(World* owningWorld, const std::string& textturePack = "");
        virtual ~Actor();
        void BeginPlayInternal();
        void TickInternal(float deltaTime);
        virtual void BeganPlay();
        virtual void Tick(float deltaTime);
        void SetTexture(const std::string& texturePack);
        void Render(sf::RenderWindow& Window);

        void SetActorLocation(const sf::Vector2f& newloc);
        void setActorRotation(float newRowt);
        void addActorLocationOffset(const sf::Vector2f& offsetAmt);
        void addActorRotationOffset(float offsetAmt);

        sf::Vector2f GetActorLocation() const;
        float GetActorRotation() const;
        sf::Vector2f getActorForwardDirection() const;
        sf::Vector2f getActorRightDirection() const;
        sf::FloatRect GetActorGlobalBounds() const;

        sf::Vector2u GetWindowSize() const;

        const World* GetWorld() const { return mOwningWorld;  }
        World* GetWorld() { return mOwningWorld; }

        bool isActorIsOutOfWindowBound(float allowance = 10.f) const;

        void setEnablePhysics(bool enable);
        virtual void OnActorBeginOverlap(Actor* other);
        virtual void OnActorEndOverlap(Actor* other);
        virtual void Destroy() override;

        static uint8 GetNeturalTeamId() { return neutralTeamID; }

        void setTeamId(uint8 teamId) { mTeamID = teamId; }
        uint8 GetTeamId() const { return mTeamID; }

        bool IsOtherHostile(Actor* other) const;
 
        virtual void ApplyDamage(float amt);

        sf::Sprite& GetSprite() { return mSprite; }
        const sf::Sprite& GetSprite() const { return mSprite; }

    private:

        void InitializePhysics();
        void UnInitializePhysics();
        void UpdatePhysicsTransform();
        void CenterPivot();

        World* mOwningWorld;
        bool mHasBeganPlay;

        sf::Sprite mSprite;  
        shared<sf::Texture> mTexture;

        b2Body* mPhysicsBody;
        bool mPhysicsEnable;

        uint8 mTeamID;

        const static uint8 neutralTeamID = 255;
    };
}
